#ifndef TINY_GRAPHICS_GL_DEFINITION_H
#define TINY_GRAPHICS_GL_DEFINITION_H


namespace Tiny{ namespace GL{
    enum class ObjectState : unsigned char{
        Created = 0,
        DeleteOnDestruction = 1,
    };
} }

#endif
