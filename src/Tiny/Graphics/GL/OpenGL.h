#ifndef TINY_GRAPHICS_GL_OPENGL_H
#define TINY_GRAPHICS_GL_OPENGL_H

/*
    This file is intended to solve OpenGL headers difference on different platforms
*/

//TODO:Remove this
#define TINY_PLATFORM_WINDOWS 1

#ifdef TINY_PLATFORM_WINDOWS
#include "gl3w/GL/gl3w.h"
#endif

#endif
