#include "Application.h"
#include "Graphics/RenderSystem.h"

namespace Tiny {
	void Application::Update(double dt) {
		Graphics::RenderSystem::Instance().Update(dt);
	}
}