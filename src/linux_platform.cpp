#include "funlib.h"
#include "input.h"
#include "platform.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <GL/glx.h>
#include <GL/glxext.h>

#include <cstdio>

static Display *g_display = nullptr;
static Window g_window = 0;
static Colormap g_colormap = 0;
static GLXContext g_glxContext = nullptr;
static Atom g_wmDelete = 0;

static PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT_ptr = nullptr;

bool running = true;

static void platform_destroy_window_internal();

static GLXFBConfig choose_fb_config(Display *dpy, int screen) {
  int fbAttribs[] = {GLX_X_RENDERABLE,
                     True,
                     GLX_DRAWABLE_TYPE,
                     GLX_WINDOW_BIT,
                     GLX_RENDER_TYPE,
                     GLX_RGBA_BIT,
                     GLX_X_VISUAL_TYPE,
                     GLX_TRUE_COLOR,

                     GLX_RED_SIZE,
                     8,
                     GLX_GREEN_SIZE,
                     8,
                     GLX_BLUE_SIZE,
                     8,
                     GLX_ALPHA_SIZE,
                     8,
                     GLX_DEPTH_SIZE,
                     24,
                     GLX_STENCIL_SIZE,
                     8,

                     GLX_DOUBLEBUFFER,
                     True,
                     None};

  int count = 0;
  GLXFBConfig *configs = glXChooseFBConfig(dpy, screen, fbAttribs, &count);
  if (!configs || count == 0)
    return nullptr;

  GLXFBConfig chosen = configs[0];
  XFree(configs);
  return chosen;
}

static GLXContext create_glx_context(Display *dpy, GLXFBConfig fbc) {
  auto glXCreateContextAttribsARB =
      (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress(
          (const GLubyte *)"glXCreateContextAttribsARB");

  if (!glXCreateContextAttribsARB) {
    XVisualInfo *vi = glXGetVisualFromFBConfig(dpy, fbc);
    if (!vi)
      return nullptr;
    GLXContext ctx = glXCreateContext(dpy, vi, 0, True);
    XFree(vi);
    return ctx;
  }

  int attribs43[] = {GLX_CONTEXT_MAJOR_VERSION_ARB,
                     4,
                     GLX_CONTEXT_MINOR_VERSION_ARB,
                     3,
                     GLX_CONTEXT_PROFILE_MASK_ARB,
                     GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
                     None};

  GLXContext ctx = glXCreateContextAttribsARB(dpy, fbc, 0, True, attribs43);
  if (ctx)
    return ctx;

  int attribs33[] = {GLX_CONTEXT_MAJOR_VERSION_ARB,
                     3,
                     GLX_CONTEXT_MINOR_VERSION_ARB,
                     3,
                     GLX_CONTEXT_PROFILE_MASK_ARB,
                     GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
                     None};

  ctx = glXCreateContextAttribsARB(dpy, fbc, 0, True, attribs33);
  return ctx;
}

bool platform_create_window(int width, int height, char *title) {
  g_display = XOpenDisplay(nullptr);
  if (!g_display) {
    std::fprintf(stderr, "XOpenDisplay failed\n");
    return false;
  }

  int screen = DefaultScreen(g_display);

  GLXFBConfig fbc = choose_fb_config(g_display, screen);
  if (!fbc) {
    std::fprintf(stderr, "glXChooseFBConfig failed\n");
    platform_destroy_window_internal();
    return false;
  }

  XVisualInfo *vi = glXGetVisualFromFBConfig(g_display, fbc);
  if (!vi) {
    std::fprintf(stderr, "glXGetVisualFromFBConfig failed\n");
    platform_destroy_window_internal();
    return false;
  }

  g_colormap = XCreateColormap(g_display, RootWindow(g_display, screen),
                               vi->visual, AllocNone);

  XSetWindowAttributes swa{};
  swa.colormap = g_colormap;
  swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                   ButtonPressMask | ButtonReleaseMask | StructureNotifyMask;

  g_window =
      XCreateWindow(g_display, RootWindow(g_display, screen), 10, 10,
                    (unsigned)width, (unsigned)height, 0, vi->depth,
                    InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

  XFree(vi);

  if (!g_window) {
    std::fprintf(stderr, "XCreateWindow failed\n");
    platform_destroy_window_internal();
    return false;
  }

  XStoreName(g_display, g_window, title);
  XMapWindow(g_display, g_window);

  g_wmDelete = XInternAtom(g_display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(g_display, g_window, &g_wmDelete, 1);

  g_glxContext = create_glx_context(g_display, fbc);
  if (!g_glxContext) {
    std::fprintf(stderr, "Failed to create GLX context\n");
    platform_destroy_window_internal();
    return false;
  }

  if (!glXMakeCurrent(g_display, g_window, g_glxContext)) {
    std::fprintf(stderr, "glXMakeCurrent failed\n");
    platform_destroy_window_internal();
    return false;
  }

  glXSwapIntervalEXT_ptr = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress(
      (const GLubyte *)"glXSwapIntervalEXT");
  if (glXSwapIntervalEXT_ptr) {
    glXSwapIntervalEXT_ptr(g_display, g_window, 1);
  }

  input.screenSizeX = width;
  input.screenSizeY = height;

  return true;
}

void platform_update_window() {
  while (XPending(g_display) > 0) {
    XEvent e{};
    XNextEvent(g_display, &e);

    switch (e.type) {
    case ClientMessage:
      if ((Atom)e.xclient.data.l[0] == g_wmDelete)
        running = false;
      break;

    case DestroyNotify:
      running = false;
      break;

    case ConfigureNotify:
      input.screenSizeX = e.xconfigure.width;
      input.screenSizeY = e.xconfigure.height;
      break;

    case KeyPress: {
      KeySym sym = XLookupKeysym(&e.xkey, 0);
      if (sym == XK_Escape)
        running = false;
    } break;

    default:
      break;
    }
  }
}

void platform_swap_buffers() { glXSwapBuffers(g_display, g_window); }

static void platform_destroy_window_internal() {
  if (!g_display)
    return;

  if (g_glxContext) {
    glXMakeCurrent(g_display, None, nullptr);
    glXDestroyContext(g_display, g_glxContext);
    g_glxContext = nullptr;
  }

  if (g_window) {
    XDestroyWindow(g_display, g_window);
    g_window = 0;
  }

  if (g_colormap) {
    XFreeColormap(g_display, g_colormap);
    g_colormap = 0;
  }

  XCloseDisplay(g_display);
  g_display = nullptr;
}

void platform_destroy_window() { platform_destroy_window_internal(); }

void *platform_load_gl_function(char *funName) {
  void *proc = (void *)glXGetProcAddress((const GLubyte *)funName);
  if (!proc) {
    FN_ASSERT(0, "Failed to load OpenGL Function: %s", funName);
  }

  return proc;
}
