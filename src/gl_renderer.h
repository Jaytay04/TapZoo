#pragma once
#include "funlib.h"
#include <GL/glcorearb.h>

struct GLContext {
  GLuint programID;
  GLuint textureID;
  GLuint transformSBOID;
  GLint screenSizeID;
  GLuint orthoProjectionID;
};
extern GLContext glContext;
bool gl_init(BumpAllocator *transientStorage);
void gl_render();
