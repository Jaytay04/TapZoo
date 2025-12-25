#include "gl_loader.h"
#include "funlib.h"   // FN_ASSERT (optional)
#include "platform.h" // platform_load_gl_function

// #############################################################################
//                           OpenGL Function Pointer Definitions
// #############################################################################
PFNGLCREATEPROGRAMPROC glCreateProgram_ptr = nullptr;
PFNGLDELETETEXTURESPROC glDeleteTextures_ptr = nullptr;
PFNGLGENTEXTURESPROC glGenTextures_ptr = nullptr;
PFNGLBINDTEXTUREPROC glBindTexture_ptr = nullptr;
PFNGLDRAWBUFFERPROC glDrawBuffer_ptr = nullptr;
PFNGLDRAWARRAYSPROC glDrawArrays_ptr = nullptr;
PFNGLCREATESHADERPROC glCreateShader_ptr = nullptr;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_ptr = nullptr;
PFNGLUNIFORM1FPROC glUniform1f_ptr = nullptr;
PFNGLUNIFORM2FVPROC glUniform2fv_ptr = nullptr;
PFNGLUNIFORM3FVPROC glUniform3fv_ptr = nullptr;
PFNGLUNIFORM1IPROC glUniform1i_ptr = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv_ptr = nullptr;
PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor_ptr = nullptr;
PFNGLACTIVETEXTUREPROC glActiveTexture_ptr = nullptr;
PFNGLBUFFERSUBDATAPROC glBufferSubData_ptr = nullptr;
PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced_ptr = nullptr;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer_ptr = nullptr;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus_ptr = nullptr;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers_ptr = nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D_ptr = nullptr;
PFNGLDRAWBUFFERSPROC glDrawBuffers_ptr = nullptr;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers_ptr = nullptr;
PFNGLBLENDFUNCIPROC glBlendFunci_ptr = nullptr;
PFNGLBLENDEQUATIONPROC glBlendEquation_ptr = nullptr;
PFNGLCLEARBUFFERFVPROC glClearBufferfv_ptr = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource_ptr = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader_ptr = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv_ptr = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_ptr = nullptr;
PFNGLATTACHSHADERPROC glAttachShader_ptr = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram_ptr = nullptr;
PFNGLVALIDATEPROGRAMPROC glValidateProgram_ptr = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv_ptr = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_ptr = nullptr;
PFNGLGENBUFFERSPROC glGenBuffers_ptr = nullptr;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays_ptr = nullptr;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation_ptr = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray_ptr = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer_ptr = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer_ptr = nullptr;
PFNGLBINDBUFFERBASEPROC glBindBufferBase_ptr = nullptr;
PFNGLBUFFERDATAPROC glBufferData_ptr = nullptr;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv_ptr = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram_ptr = nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays_ptr = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers_ptr = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram_ptr = nullptr;
PFNGLDETACHSHADERPROC glDetachShader_ptr = nullptr;
PFNGLDELETESHADERPROC glDeleteShader_ptr = nullptr;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced_ptr = nullptr;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap_ptr = nullptr;
PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback_ptr = nullptr;

// Additional explicitly-used funcs
PFNGLTEXIMAGE2DPROC glTexImage2D_ptr = nullptr;
PFNGLTEXPARAMETERIPROC glTexParameteri_ptr = nullptr;

PFNGLCLEARPROC glClear_ptr = nullptr;
PFNGLCLEARCOLORPROC glClearColor_ptr = nullptr;
PFNGLCLEARDEPTHPROC glClearDepth_ptr = nullptr;

PFNGLREADBUFFERPROC glReadBuffer_ptr = nullptr;
PFNGLDEPTHMASKPROC glDepthMask_ptr = nullptr;
PFNGLDISABLEPROC glDisable_ptr = nullptr;
PFNGLENABLEPROC glEnable_ptr = nullptr;
PFNGLSCISSORPROC glScissor_ptr = nullptr;
PFNGLVIEWPORTPROC glViewport_ptr = nullptr;
PFNGLDEPTHFUNCPROC glDepthFunc_ptr = nullptr;

PFNGLGETERRORPROC glGetError_ptr = nullptr;

// Helper
static void *load_gl(const char *name) {
  return platform_load_gl_function((char *)name);
}

// #############################################################################
//                           OpenGL Function Loader
// #############################################################################
void load_gl_functions() {
  // Program/shader pipeline
  glCreateProgram_ptr = (PFNGLCREATEPROGRAMPROC)load_gl("glCreateProgram");
  glCreateShader_ptr = (PFNGLCREATESHADERPROC)load_gl("glCreateShader");
  glShaderSource_ptr = (PFNGLSHADERSOURCEPROC)load_gl("glShaderSource");
  glCompileShader_ptr = (PFNGLCOMPILESHADERPROC)load_gl("glCompileShader");
  glGetShaderiv_ptr = (PFNGLGETSHADERIVPROC)load_gl("glGetShaderiv");
  glGetShaderInfoLog_ptr =
      (PFNGLGETSHADERINFOLOGPROC)load_gl("glGetShaderInfoLog");
  glAttachShader_ptr = (PFNGLATTACHSHADERPROC)load_gl("glAttachShader");
  glLinkProgram_ptr = (PFNGLLINKPROGRAMPROC)load_gl("glLinkProgram");
  glValidateProgram_ptr =
      (PFNGLVALIDATEPROGRAMPROC)load_gl("glValidateProgram");
  glGetProgramiv_ptr = (PFNGLGETPROGRAMIVPROC)load_gl("glGetProgramiv");
  glGetProgramInfoLog_ptr =
      (PFNGLGETPROGRAMINFOLOGPROC)load_gl("glGetProgramInfoLog");
  glDetachShader_ptr = (PFNGLDETACHSHADERPROC)load_gl("glDetachShader");
  glDeleteShader_ptr = (PFNGLDELETESHADERPROC)load_gl("glDeleteShader");
  glUseProgram_ptr = (PFNGLUSEPROGRAMPROC)load_gl("glUseProgram");
  glDeleteProgram_ptr = (PFNGLDELETEPROGRAMPROC)load_gl("glDeleteProgram");

  // Uniforms
  glGetUniformLocation_ptr =
      (PFNGLGETUNIFORMLOCATIONPROC)load_gl("glGetUniformLocation");
  glUniform1f_ptr = (PFNGLUNIFORM1FPROC)load_gl("glUniform1f");
  glUniform2fv_ptr = (PFNGLUNIFORM2FVPROC)load_gl("glUniform2fv");
  glUniform3fv_ptr = (PFNGLUNIFORM3FVPROC)load_gl("glUniform3fv");
  glUniform1i_ptr = (PFNGLUNIFORM1IPROC)load_gl("glUniform1i");
  glUniformMatrix4fv_ptr =
      (PFNGLUNIFORMMATRIX4FVPROC)load_gl("glUniformMatrix4fv");

  // Vertex / VAO
  glGenVertexArrays_ptr =
      (PFNGLGENVERTEXARRAYSPROC)load_gl("glGenVertexArrays");
  glBindVertexArray_ptr =
      (PFNGLBINDVERTEXARRAYPROC)load_gl("glBindVertexArray");
  glDeleteVertexArrays_ptr =
      (PFNGLDELETEVERTEXARRAYSPROC)load_gl("glDeleteVertexArrays");
  glGetAttribLocation_ptr =
      (PFNGLGETATTRIBLOCATIONPROC)load_gl("glGetAttribLocation");
  glEnableVertexAttribArray_ptr =
      (PFNGLENABLEVERTEXATTRIBARRAYPROC)load_gl("glEnableVertexAttribArray");
  glVertexAttribPointer_ptr =
      (PFNGLVERTEXATTRIBPOINTERPROC)load_gl("glVertexAttribPointer");
  glGetVertexAttribPointerv_ptr =
      (PFNGLGETVERTEXATTRIBPOINTERVPROC)load_gl("glGetVertexAttribPointerv");
  glVertexAttribDivisor_ptr =
      (PFNGLVERTEXATTRIBDIVISORPROC)load_gl("glVertexAttribDivisor");

  // Buffers
  glGenBuffers_ptr = (PFNGLGENBUFFERSPROC)load_gl("glGenBuffers");
  glBindBuffer_ptr = (PFNGLBINDBUFFERPROC)load_gl("glBindBuffer");
  glBindBufferBase_ptr = (PFNGLBINDBUFFERBASEPROC)load_gl("glBindBufferBase");
  glBufferData_ptr = (PFNGLBUFFERDATAPROC)load_gl("glBufferData");
  glBufferSubData_ptr = (PFNGLBUFFERSUBDATAPROC)load_gl("glBufferSubData");
  glDeleteBuffers_ptr = (PFNGLDELETEBUFFERSPROC)load_gl("glDeleteBuffers");

  // Textures
  glGenTextures_ptr = (PFNGLGENTEXTURESPROC)load_gl("glGenTextures");
  glDeleteTextures_ptr = (PFNGLDELETETEXTURESPROC)load_gl("glDeleteTextures");
  glBindTexture_ptr = (PFNGLBINDTEXTUREPROC)load_gl("glBindTexture");
  glActiveTexture_ptr = (PFNGLACTIVETEXTUREPROC)load_gl("glActiveTexture");

  // These were explicitly used in your renderer (tex upload + params)
  glTexImage2D_ptr = (PFNGLTEXIMAGE2DPROC)load_gl("glTexImage2D");
  glTexParameteri_ptr = (PFNGLTEXPARAMETERIPROC)load_gl("glTexParameteri");
  glGenerateMipmap_ptr = (PFNGLGENERATEMIPMAPPROC)load_gl("glGenerateMipmap");

  // Draw
  glDrawBuffer_ptr = (PFNGLDRAWBUFFERPROC)load_gl("glDrawBuffer");
  glDrawArrays_ptr = (PFNGLDRAWARRAYSPROC)load_gl("glDrawArrays");
  glDrawArraysInstanced_ptr =
      (PFNGLDRAWARRAYSINSTANCEDPROC)load_gl("glDrawArraysInstanced");
  glDrawElementsInstanced_ptr =
      (PFNGLDRAWELEMENTSINSTANCEDPROC)load_gl("glDrawElementsInstanced");

  // Framebuffers
  glBindFramebuffer_ptr =
      (PFNGLBINDFRAMEBUFFERPROC)load_gl("glBindFramebuffer");
  glCheckFramebufferStatus_ptr =
      (PFNGLCHECKFRAMEBUFFERSTATUSPROC)load_gl("glCheckFramebufferStatus");
  glGenFramebuffers_ptr =
      (PFNGLGENFRAMEBUFFERSPROC)load_gl("glGenFramebuffers");
  glFramebufferTexture2D_ptr =
      (PFNGLFRAMEBUFFERTEXTURE2DPROC)load_gl("glFramebufferTexture2D");
  glDrawBuffers_ptr = (PFNGLDRAWBUFFERSPROC)load_gl("glDrawBuffers");
  glDeleteFramebuffers_ptr =
      (PFNGLDELETEFRAMEBUFFERSPROC)load_gl("glDeleteFramebuffers");

  // Blend / clears
  glBlendFunci_ptr = (PFNGLBLENDFUNCIPROC)load_gl("glBlendFunci");
  glBlendEquation_ptr = (PFNGLBLENDEQUATIONPROC)load_gl("glBlendEquation");
  glClearBufferfv_ptr = (PFNGLCLEARBUFFERFVPROC)load_gl("glClearBufferfv");

  // Core state functions explicitly used
  glClear_ptr = (PFNGLCLEARPROC)load_gl("glClear");
  glClearColor_ptr = (PFNGLCLEARCOLORPROC)load_gl("glClearColor");
  glClearDepth_ptr = (PFNGLCLEARDEPTHPROC)load_gl("glClearDepth");
  glViewport_ptr = (PFNGLVIEWPORTPROC)load_gl("glViewport");
  glEnable_ptr = (PFNGLENABLEPROC)load_gl("glEnable");
  glDisable_ptr = (PFNGLDISABLEPROC)load_gl("glDisable");
  glDepthFunc_ptr = (PFNGLDEPTHFUNCPROC)load_gl("glDepthFunc");
  glGetError_ptr = (PFNGLGETERRORPROC)load_gl("glGetError");

  // Optional state you had in comment block (load them if you want)
  glReadBuffer_ptr = (PFNGLREADBUFFERPROC)load_gl("glReadBuffer");
  glDepthMask_ptr = (PFNGLDEPTHMASKPROC)load_gl("glDepthMask");
  glScissor_ptr = (PFNGLSCISSORPROC)load_gl("glScissor");

  // Debug callback (optional)
  glDebugMessageCallback_ptr =
      (PFNGLDEBUGMESSAGECALLBACKPROC)load_gl("glDebugMessageCallback");
}

// #############################################################################
//                           OpenGL Function Wrappers
// #############################################################################

GLAPI GLuint APIENTRY glCreateProgram(void) { return glCreateProgram_ptr(); }

GLAPI void APIENTRY glDeleteTextures(GLsizei n, const GLuint *textures) {
  glDeleteTextures_ptr(n, textures);
}

GLAPI void APIENTRY glGenTextures(GLsizei n, GLuint *textures) {
  glGenTextures_ptr(n, textures);
}

GLAPI void APIENTRY glBindTexture(GLenum target, GLuint texture) {
  glBindTexture_ptr(target, texture);
}

void glDrawBuffer(GLenum buf) { glDrawBuffer_ptr(buf); }

void glDrawArrays(GLenum mode, GLint first, GLsizei count) {
  glDrawArrays_ptr(mode, first, count);
}

GLuint glCreateShader(GLenum shaderType) {
  return glCreateShader_ptr(shaderType);
}

GLint glGetUniformLocation(GLuint program, const GLchar *name) {
  return glGetUniformLocation_ptr(program, name);
}

void glUniform1f(GLint location, GLfloat v0) { glUniform1f_ptr(location, v0); }

void glUniform2fv(GLint location, GLsizei count, const GLfloat *value) {
  glUniform2fv_ptr(location, count, value);
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat *value) {
  glUniform3fv_ptr(location, count, value);
}

void glUniform1i(GLint location, GLint v0) { glUniform1i_ptr(location, v0); }

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                        const GLfloat *value) {
  glUniformMatrix4fv_ptr(location, count, transpose, value);
}

void glVertexAttribDivisor(GLuint index, GLuint divisor) {
  glVertexAttribDivisor_ptr(index, divisor);
}

void glActiveTexture(GLenum texture) { glActiveTexture_ptr(texture); }

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size,
                     const void *data) {
  glBufferSubData_ptr(target, offset, size, data);
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count,
                           GLsizei instanceCount) {
  glDrawArraysInstanced_ptr(mode, first, count, instanceCount);
}

void glBindFramebuffer(GLenum target, GLuint framebuffer) {
  glBindFramebuffer_ptr(target, framebuffer);
}

GLenum glCheckFramebufferStatus(GLenum target) {
  return glCheckFramebufferStatus_ptr(target);
}

void glGenFramebuffers(GLsizei n, GLuint *framebuffers) {
  glGenFramebuffers_ptr(n, framebuffers);
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget,
                            GLuint texture, GLint level) {
  glFramebufferTexture2D_ptr(target, attachment, textarget, texture, level);
}

void glDrawBuffers(GLsizei n, const GLenum *bufs) {
  glDrawBuffers_ptr(n, bufs);
}

void glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers) {
  glDeleteFramebuffers_ptr(n, framebuffers);
}

void glBlendFunci(GLuint buf, GLenum src, GLenum dst) {
  glBlendFunci_ptr(buf, src, dst);
}

void glBlendEquation(GLenum mode) { glBlendEquation_ptr(mode); }

void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value) {
  glClearBufferfv_ptr(buffer, drawbuffer, value);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar *const *strings,
                    const GLint *lengths) {
  glShaderSource_ptr(shader, count, strings, lengths);
}

void glCompileShader(GLuint shader) { glCompileShader_ptr(shader); }

void glGetShaderiv(GLuint shader, GLenum pname, GLint *params) {
  glGetShaderiv_ptr(shader, pname, params);
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length,
                        GLchar *infoLog) {
  glGetShaderInfoLog_ptr(shader, bufSize, length, infoLog);
}

void glAttachShader(GLuint program, GLuint shader) {
  glAttachShader_ptr(program, shader);
}

void glLinkProgram(GLuint program) { glLinkProgram_ptr(program); }

void glValidateProgram(GLuint program) { glValidateProgram_ptr(program); }

void glGetProgramiv(GLuint program, GLenum pname, GLint *params) {
  glGetProgramiv_ptr(program, pname, params);
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length,
                         GLchar *infoLog) {
  glGetProgramInfoLog_ptr(program, bufSize, length, infoLog);
}

void glGenBuffers(GLsizei n, GLuint *buffers) { glGenBuffers_ptr(n, buffers); }

void glGenVertexArrays(GLsizei n, GLuint *arrays) {
  glGenVertexArrays_ptr(n, arrays);
}

GLint glGetAttribLocation(GLuint program, const GLchar *name) {
  return glGetAttribLocation_ptr(program, name);
}

void glBindVertexArray(GLuint array) { glBindVertexArray_ptr(array); }

void glEnableVertexAttribArray(GLuint index) {
  glEnableVertexAttribArray_ptr(index);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type,
                           GLboolean normalized, GLsizei stride,
                           const void *pointer) {
  glVertexAttribPointer_ptr(index, size, type, normalized, stride, pointer);
}

void glBindBuffer(GLenum target, GLuint buffer) {
  glBindBuffer_ptr(target, buffer);
}

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer) {
  glBindBufferBase_ptr(target, index, buffer);
}

void glBufferData(GLenum target, GLsizeiptr size, const void *data,
                  GLenum usage) {
  glBufferData_ptr(target, size, data, usage);
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer) {
  glGetVertexAttribPointerv_ptr(index, pname, pointer);
}

void glUseProgram(GLuint program) { glUseProgram_ptr(program); }

void glDeleteVertexArrays(GLsizei n, const GLuint *arrays) {
  glDeleteVertexArrays_ptr(n, arrays);
}

void glDeleteBuffers(GLsizei n, const GLuint *buffers) {
  glDeleteBuffers_ptr(n, buffers);
}

void glDeleteProgram(GLuint program) { glDeleteProgram_ptr(program); }

void glDetachShader(GLuint program, GLuint shader) {
  glDetachShader_ptr(program, shader);
}

void glDeleteShader(GLuint shader) { glDeleteShader_ptr(shader); }

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type,
                             const void *indices, GLsizei instancecount) {
  glDrawElementsInstanced_ptr(mode, count, type, indices, instancecount);
}

void glGenerateMipmap(GLenum target) { glGenerateMipmap_ptr(target); }

void glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam) {
  if (glDebugMessageCallback_ptr)
    glDebugMessageCallback_ptr(callback, userParam);
}

// Explicitly-used core funcs (texture upload + state + clear)
GLAPI void APIENTRY glTexImage2D(GLenum target, GLint level,
                                 GLint internalformat, GLsizei width,
                                 GLsizei height, GLint border, GLenum format,
                                 GLenum type, const void *pixels) {
  glTexImage2D_ptr(target, level, internalformat, width, height, border, format,
                   type, pixels);
}

GLAPI void APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param) {
  glTexParameteri_ptr(target, pname, param);
}

GLAPI void APIENTRY glClear(GLbitfield mask) { glClear_ptr(mask); }

GLAPI void APIENTRY glClearColor(GLfloat red, GLfloat green, GLfloat blue,
                                 GLfloat alpha) {
  glClearColor_ptr(red, green, blue, alpha);
}

GLAPI void APIENTRY glClearDepth(GLdouble depth) { glClearDepth_ptr(depth); }

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
  glViewport_ptr(x, y, width, height);
}

void glEnable(GLenum cap) { glEnable_ptr(cap); }
void glDisable(GLenum cap) { glDisable_ptr(cap); }
void glDepthFunc(GLenum func) { glDepthFunc_ptr(func); }

GLenum glGetError(void) {
  return glGetError_ptr ? glGetError_ptr() : GL_NO_ERROR;
}
