#ifndef TINY_GRAPHICS_GL_BUFFER_H
#define TINY_GRAPHICS_GL_BUFFER_H

#include <gl/gl.h>

namespace Tiny{ namespace Graphics{ namespace GL{
    /*
        @brief  Wrap class for OpenGL Buffer object.
        Currently, only OpenGL 4.5 is supported, which means all operations are DSA supported.
        For buffer objects with DSA supported,  BO can be directly modified without having to bind to GL context.
        Without DSA, BO must be bound to specific binding point. And after that, BO can be modified indirectly.
        So ideally, GL interface with and without DSA should not be uesed mixed up.


    */
    class Buffer{
    public:
		enum class UsageHint{
            StreamDraw = GL_STREAM_DRAW,
            StreamRead = GL_STREAM_READ,
            StreamCopy = GL_STREAM_COPY,
            StaticDraw = GL_STATIC_DRAW,
            StaticRead = GL_STATIC_COPY,
            StaticCopy = GL_STATIC_COPY,
            DynamicCopy = GL_DYNAMIC_COPY,
            DynamicRead = GL_DYNAMIC_READ,
            DynamicDraw = GL_DYNAMIC_DRAW,
		};

        enum class BindingTarget{
            
        }

        /*
            @brief  Create empty Buffer object, even without GLContext created.
        */
        Buffer();

        ~Buffer();

        Buffer(Buffer&&);
        Buffer& operator=(Buffer&&);

        Buffer(const Buffer&) = delete;
        Buffer& operator=(Buffer) = delete;

        BindTarget(BindingTarget target);

        /*
            @brief
        */
        ImmutableStorage()

    private:

    private:
        GLuint _id;
        BindingTarget _intentedTarget;

	};
} } }

#endif
