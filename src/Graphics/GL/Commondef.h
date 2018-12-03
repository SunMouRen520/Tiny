#ifndef TINY_GRAPHICS_GL_COMMONDEF_H
#define TINY_GRAPHICS_GL_COMMONDEF_H

namespace Tiny{ namespace Graphics{ namespace GL{
    enum class ObjectState : unsigned char{
        Created = 0,
        DeleteOnDestruction = 1,
    };
} } }

#endif
