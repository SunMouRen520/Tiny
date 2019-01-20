#ifndef TINY_GRAPHICS_BUFFER_H
#define TINY_GRAPHICS_BUFFER_H

#include "Tiny/Graphics/Renderer/Object/AbstractObject.h"

namespace Tiny{ namespace Buffer{
	/*
		TODO:
			For desciption data such as Vertex attributes info, uniform info and texture info,
			the abstract render system and the underlying render system(OpenGL) shares the same knowledge.
			So we need some common facilities to shared these description data instead of copy around.
			facilities like bgfx VertexDeclHandle, UniformHandle and TextureHandle.
	*/
	class VertexAttribsDesc {
	public:
		enum class AttribType:UnsignedByte {
			UInt8,
			UInt10,
			Int16,
			Short,
			Float,
			Count
		};

		struct AttribDesc {
			int index; //attribute index
			std::string name; //attribtue name in OpenGL
			int num; //element data number per vertex
			AttribType type; //element data type
		};

		AttribDesc& Add(const AttribDesc& desc);
		void Commit();

	private:
		UnsignedShort _stride;
	};



	class AbstractBuffer : public AbstractObject {
	public:
		/*
		@brief	ref cpu-side memory with buffer object
		@paramt	mem	Can be used as the data source of buffer object or data destination of buffer object, which decided by buffer object usage.
		*/
		void RefMemory(const ManagedMemory& mem);

	protected:
		/*
		@brief	Create dynamic buffer which will be updated by drawcall
		*/
		explicit AbstractBuffer();
		/*
		@brief	Create static buffer
		*/
		explicit AbstractBuffer(const ManagedMemory& mem);


	private:
		UnsignedInt _size;

	};

	/*
	@brief	vbo with fixed data and attribute desc
	*/
	class StaticVertexBuffer : public AbstractBuffer {
	public:
		explicit StaticVertexBuffer(const ManagedMemory& mem, const VertexAttribsDesc& desc);

	};

	/*
	@brief	index buffer with fixed data.
	*/
	class StaticIndexBuffer : public AbstractBuffer {
	public:
		enum class IndexSize :UnsignedByte {
			Short,
			Int
		};
		explicit StaticIndexBuffer(const ManagedMemory& mem, IndexSize size);

	private:

	};

	/*
	@brief	vbo with dynamic data, dynamic atributes and variable memory size.
	*/
	class DynamicVertexBuffer : public AbstractBuffer {
	public:
		explicit DynamicVertexBuffer(bool variableSize);

		/*
		@brief	Only avaliable when variable size enabled
		*/
		void ChangeSize(UnsignedInt size);

		void RefAttributes(const VertexAttribsDesc& desc);

	private:
		bool	_variableSize;

	};

	class DynamicIndexBuffer : public AbstractBuffer{
	public:
		
	private:

	}

} }

#endif
