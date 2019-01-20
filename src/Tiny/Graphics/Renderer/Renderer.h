#ifndef TINY_GRAPHICS_RENDERER_H
#define TINY_GRAPHICS_RENDERER_H

#include "Tiny/Types.h"

#include "IronBranch/Notion/Tags.h"

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

		


		/*
			@brief	任何由外部提供给Render的内存资源都必须是ManagerMemory.
			因为render system内部的object的create和bind都是lazy的，
			真正为pipeline feeding stream是在Render::frame中进行，非ManagedMemory可能被外部资源释放。
			ManagedMemory should be used in data traforming between users and RenderSystem.
		*/
		class ManagedMemory {
		public:

		private:
			UnsignedLong _size;
			UnsignedByte* _data;
		};

		/*
			@brief	Stream that will feed into graphics pipeline
			Stream should be treated as rew memory block with no data format informtion.
			How streams should be interpreted shall be decided by render pipeline. 
			Stream should be used in feeding data from RenderSystem to render pipeline.
		*/
		class Stream {
		public:

		};


		struct UniformDesc {

		};
	}
}

#endif
