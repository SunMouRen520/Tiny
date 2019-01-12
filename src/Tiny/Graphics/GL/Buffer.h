#ifndef TINY_GRAPHICS_GL_BUFFER_H
#define TINY_GRAPHICS_GL_BUFFER_H

#include "Tiny/Graphics/GL/OpenGL.h"
#include "Tiny/Graphics/GL/Definition.h"

namespace Tiny{ namespace Graphics{ namespace GL{
    /*
        @brief  Wrap class for OpenGL Buffer object.
        Currently, only OpenGL 4.5 is supported, which means all operations are DSA supported.
        For buffer objects with DSA supported,  BO can be directly modified without having to bind to GL context.
        Without DSA, BO must be bound to specific binding point. And after that, BO can be modified indirectly.
        So ideally, GL interface with and without DSA should not be uesed mixed up.
    */

    class Buffer{
		static const int EMPTY = -1;

    public:
		/*
			@brief	UsageHint for mutable storage in OpenGL server side. As literally meaning, this is just a hint for OpenGL server side.
			Purpose:
				1.	Draw: Client side will write into buffer, server side drawing.
				2.	Read: Used as destination of OpenGL commands, client side reading.
				3.	Copy: Client side will never read or write with buffer, which means this buffer is used by serve side internal.
			Frequency:
				1.	Static: user side set the data once.
				2.	Dynamic: uset set the data occasionally.
				3.	Stream:	user set the data almost every use.
			Usagehint can be any combination of Purpose and Frequency.
		*/
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

		/*
			@brief	Avaliable binding targets for VBO.
		*/
        enum class BindingTarget{
            INVALID = -1,

			Array = GL_ARRAY_BUFFER,
			ElementArray = GL_ELEMENT_ARRAY_BUFFER,
			CopyRead = GL_COPY_READ_BUFFER,
			CopyWrite = GL_COPY_WRITE_BUFFER,
			PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
			PixelPack = GL_PIXEL_PACK_BUFFER,
			Query = GL_QUERY_BUFFER,
			Texture = GL_TEXTURE_BUFFER,
			TransformFeedback = GL_TRANSFORM_FEEDBACK,
			Uniform = GL_UNIFORM_BUFFER,
			DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
			AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
			DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
			ShaderStorage = GL_SHADER_STORAGE_BUFFER,
		};

        /*
            @brief  Create empty Buffer object, even without GLContext created.
        */
		Buffer():_id(EMPTY), _intentedTarget(BindingTarget::INVALID) { }

		/*
			@brief	Create buffer with intented target
			@caution	target is 
		*/
		Buffer(const BindingTarget& target);

        ~Buffer();

        Buffer(Buffer&&);
        Buffer& operator=(Buffer&&);

        Buffer(const Buffer&) = delete;
        Buffer& operator=(Buffer) = delete;

        void BindTarget(BindingTarget target);

        /*
            @brief	
        */
		void ImmutableStorage();

    private:
		void CreateImpl();
		void CreateImplWithDSA();


    private:
        GLuint _id;
        BindingTarget _intentedTarget;

	};
} } }

#endif
