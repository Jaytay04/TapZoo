#pragma once

// Use system glcorearb for types + PFN* typedefs.
// If your include path is "GL/glcorearb.h" instead, change this include.
#include <GL/glcorearb.h>

// platform_load_gl_function(char* name) lives in platform.h/linux_platform.cpp
void load_gl_functions();

// #############################################################################
//                           OpenGL Function Pointers
// #############################################################################
extern PFNGLCREATEPROGRAMPROC glCreateProgram_ptr;
extern PFNGLDELETETEXTURESPROC glDeleteTextures_ptr;
extern PFNGLGENTEXTURESPROC glGenTextures_ptr;
extern PFNGLBINDTEXTUREPROC glBindTexture_ptr;
extern PFNGLDRAWBUFFERPROC glDrawBuffer_ptr;
extern PFNGLDRAWARRAYSPROC glDrawArrays_ptr;
extern PFNGLCREATESHADERPROC glCreateShader_ptr;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_ptr;
extern PFNGLUNIFORM1FPROC glUniform1f_ptr;
extern PFNGLUNIFORM2FVPROC glUniform2fv_ptr;
extern PFNGLUNIFORM3FVPROC glUniform3fv_ptr;
extern PFNGLUNIFORM1IPROC glUniform1i_ptr;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv_ptr;
extern PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor_ptr;
extern PFNGLACTIVETEXTUREPROC glActiveTexture_ptr;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData_ptr;
extern PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced_ptr;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer_ptr;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus_ptr;
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers_ptr;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D_ptr;
extern PFNGLDRAWBUFFERSPROC glDrawBuffers_ptr;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers_ptr;
extern PFNGLBLENDFUNCIPROC glBlendFunci_ptr;
extern PFNGLBLENDEQUATIONPROC glBlendEquation_ptr;
extern PFNGLCLEARBUFFERFVPROC glClearBufferfv_ptr;
extern PFNGLSHADERSOURCEPROC glShaderSource_ptr;
extern PFNGLCOMPILESHADERPROC glCompileShader_ptr;
extern PFNGLGETSHADERIVPROC glGetShaderiv_ptr;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_ptr;
extern PFNGLATTACHSHADERPROC glAttachShader_ptr;
extern PFNGLLINKPROGRAMPROC glLinkProgram_ptr;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram_ptr;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv_ptr;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_ptr;
extern PFNGLGENBUFFERSPROC glGenBuffers_ptr;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays_ptr;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation_ptr;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray_ptr;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer_ptr;
extern PFNGLBINDBUFFERPROC glBindBuffer_ptr;
extern PFNGLBINDBUFFERBASEPROC glBindBufferBase_ptr;
extern PFNGLBUFFERDATAPROC glBufferData_ptr;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv_ptr;
extern PFNGLUSEPROGRAMPROC glUseProgram_ptr;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays_ptr;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers_ptr;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram_ptr;
extern PFNGLDETACHSHADERPROC glDetachShader_ptr;
extern PFNGLDELETESHADERPROC glDeleteShader_ptr;
extern PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced_ptr;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap_ptr;
extern PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback_ptr;

// -----------------------------------------------------------------------------
// Additional functions you explicitly use (from the project snippets)
// -----------------------------------------------------------------------------
extern PFNGLTEXIMAGE2DPROC glTexImage2D_ptr;
extern PFNGLTEXPARAMETERIPROC glTexParameteri_ptr;

extern PFNGLCLEARPROC glClear_ptr;
extern PFNGLCLEARCOLORPROC glClearColor_ptr;
extern PFNGLCLEARDEPTHPROC glClearDepth_ptr;

extern PFNGLREADBUFFERPROC
    glReadBuffer_ptr; // optional but you had wrapper in comment
extern PFNGLDEPTHMASKPROC
    glDepthMask_ptr; // optional but you had wrapper in comment
extern PFNGLDISABLEPROC glDisable_ptr;
extern PFNGLENABLEPROC glEnable_ptr;
extern PFNGLSCISSORPROC
    glScissor_ptr; // optional but you had wrapper in comment
extern PFNGLVIEWPORTPROC glViewport_ptr;
extern PFNGLDEPTHFUNCPROC glDepthFunc_ptr;

extern PFNGLGETERRORPROC glGetError_ptr;

// #############################################################################
//                           OpenGL Function Wrappers
// #############################################################################
// NOTE: These wrappers will conflict with <GL/gl.h> declarations.
// Only include this header in TUs that do NOT include <GL/gl.h> / <GL/glx.h>.

GLAPI GLuint APIENTRY glCreateProgram(void);
GLAPI void APIENTRY glDeleteTextures(GLsizei n, const GLuint *textures);
GLAPI void APIENTRY glGenTextures(GLsizei n, GLuint *textures);
GLAPI void APIENTRY glBindTexture(GLenum target, GLuint texture);

void glDrawBuffer(GLenum buf);
void glDrawArrays(GLenum mode, GLint first, GLsizei count);

GLuint glCreateShader(GLenum shaderType);
void glShaderSource(GLuint shader, GLsizei count, const GLchar *const *strings,
                    const GLint *lengths);
void glCompileShader(GLuint shader);
void glGetShaderiv(GLuint shader, GLenum pname, GLint *params);
void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length,
                        GLchar *infoLog);
void glAttachShader(GLuint program, GLuint shader);
void glLinkProgram(GLuint program);
void glValidateProgram(GLuint program);
void glGetProgramiv(GLuint program, GLenum pname, GLint *params);
void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length,
                         GLchar *infoLog);
void glDetachShader(GLuint program, GLuint shader);
void glDeleteShader(GLuint shader);
void glUseProgram(GLuint program);
void glDeleteProgram(GLuint program);

GLint glGetUniformLocation(GLuint program, const GLchar *name);
void glUniform1f(GLint location, GLfloat v0);
void glUniform2fv(GLint location, GLsizei count, const GLfloat *value);
void glUniform3fv(GLint location, GLsizei count, const GLfloat *value);
void glUniform1i(GLint location, GLint v0);
void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                        const GLfloat *value);

void glVertexAttribDivisor(GLuint index, GLuint divisor);
GLint glGetAttribLocation(GLuint program, const GLchar *name);
void glEnableVertexAttribArray(GLuint index);
void glVertexAttribPointer(GLuint index, GLint size, GLenum type,
                           GLboolean normalized, GLsizei stride,
                           const void *pointer);
void glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer);

void glActiveTexture(GLenum texture);

void glGenVertexArrays(GLsizei n, GLuint *arrays);
void glBindVertexArray(GLuint array);
void glDeleteVertexArrays(GLsizei n, const GLuint *arrays);

void glGenBuffers(GLsizei n, GLuint *buffers);
void glBindBuffer(GLenum target, GLuint buffer);
void glBindBufferBase(GLenum target, GLuint index, GLuint buffer);
void glBufferData(GLenum target, GLsizeiptr size, const void *data,
                  GLenum usage);
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size,
                     const void *data);
void glDeleteBuffers(GLsizei n, const GLuint *buffers);

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count,
                           GLsizei instanceCount);
void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type,
                             const void *indices, GLsizei instancecount);

void glGenerateMipmap(GLenum target);

void glBindFramebuffer(GLenum target, GLuint framebuffer);
GLenum glCheckFramebufferStatus(GLenum target);
void glGenFramebuffers(GLsizei n, GLuint *framebuffers);
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget,
                            GLuint texture, GLint level);
void glDrawBuffers(GLsizei n, const GLenum *bufs);
void glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers);

void glBlendFunci(GLuint buf, GLenum src, GLenum dst);
void glBlendEquation(GLenum mode);
void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value);

void glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam);

// Extra wrappers you explicitly use in renderer
GLAPI void APIENTRY glTexImage2D(GLenum target, GLint level,
                                 GLint internalformat, GLsizei width,
                                 GLsizei height, GLint border, GLenum format,
                                 GLenum type, const void *pixels);

GLAPI void APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param);

GLAPI void APIENTRY glClear(GLbitfield mask);
GLAPI void APIENTRY glClearColor(GLfloat red, GLfloat green, GLfloat blue,
                                 GLfloat alpha);
GLAPI void APIENTRY glClearDepth(GLdouble depth);

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
void glEnable(GLenum cap);
void glDisable(GLenum cap);
void glDepthFunc(GLenum func);

GLenum glGetError(void);
