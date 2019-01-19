#ifndef TINY_GRAPHICS_RENDERER_H
#define TINY_GRAPHICS_RENDERER_H

#include "Tiny/Types.h"

#include <string>
#include <vector>

namespace Tiny {
	namespace Graphics {
		//config read from underlying graphics vendor.
		struct RendererConfig {
			UnsignedInt mMaxBufferNum;
		};

		//
		enum class RendererFunction:UnsignedByte{
			ZBuffer,
			Stencil,
			Culling,
			Blending,
		};

		class Renderer {
		public:

		};


		/*
			@brief	Command will be executed on each frame call.
		*/
		class RendererCommand {
		public:
			enum class Command :UnsignedByte {
				CreateBuffer,
			};
		};


		const char* Attribs[] = {
			"Pos",
			"UV",
			"Normal",
			"Color",
		};

		class VertexAttribDesc {
		public:
			enum class AttribType:UnsignedByte {
				UInt8,
				UInt10,
				Int16,
				Half,
				Float,
				Count
			};

			struct AttribDesc {
				int index; //attribute index
				std::string name; //attribtue name in OpenGL
				int num; //element data number per vertex
				AttribType type; //element data type
				int offset; //offset in buffer memory
			};

			AttribDesc& AddAttribDesc(const AttribDesc& desc);
			void Commit();

		private:
			
		};


		/*
			@brief	任何由外部提供给Render的内存资源都必须是ManagerMemory.
			因为render system内部的object的create和bind都是lazy的，
			真正为pipeline feeding stream是在Render::frame中进行，此时内存可能被外部资源释放。
		*/
		class ManagedMemory {
		public:

		};

		/*
			@brief	Stream that will feed into graphics pipeline
		*/
		class Stream {
		public:


		};

		class Buffer {
		public:
			enum class Property:UnsignedByte {
				FixedSize = 1,
				DynamicSize,
			};
			Buffer(UnsignedInt _size);

			void RefStream(const Stream& stream);
			void RefAttr(const VertexAttribDesc& attribDesc);

		private:
			UnsignedInt _size;
			UnsignedShort _stride;
		};

		struct VertexBuffer {
			
		};

		struct IndexBuffer {

		};

		struct UniformDesc {

		};

		void CreateVertexAtributeBuffer();
	}
}

#endif
