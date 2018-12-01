#ifndef TINY_GRAPHICS_RENDERSYSTEM_H
#define TINY_GRAPHICS_RENDERSYSTEM_H

#include <vector>

namespace Tiny { namespace Graphics {
	/*
		@brief	
	*/
	class RenderSystem {
	public:
		static RenderSystem& Instance() {
			static RenderSystem singleton;
			return singleton;
		}

		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator = (const RenderSystem) = delete;
		RenderSystem(RenderSystem&&) = delete;

		void Update(double dt);

	private:
		RenderSystem();

		~RenderSystem();
	};
} }

#endif // !TINY_GRAPHICS_RENDERSYSTEM_H
