#pragma once
#include "funlib.h"
#include <GL/glcorearb.h>

struct GLContext {
  GLuint programID = 0;
  GLuint textureID = 0;
  GLuint transformSBOID = 0;
  GLint screenSizeID = -1;
};
extern GLContext glContext;
bool gl_init(BumpAllocator *transientStorage);
void gl_render();
