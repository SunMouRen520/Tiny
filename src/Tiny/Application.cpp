#include "Application.h"
#include "Tiny/Graphics/RenderSystem.h"
#include "Tiny/Core/Plugin/PluginManager.h"
#include "Tiny/FileSystem/FileSystem.h"
#include "Tiny/Core/Resource/ResourceManager.h"

namespace Tiny {
	void Application::StartUp(){
		PLUGIN::Init();
		ResourceLoader::Instance().Init();


		FileSystem::SetBaseDir(FileSystem::GetExePath() + "../../gl_practice/resource/");
	}

	void Application::Update(double dt) {
		Graphics::RenderSystem::Instance().Update(dt);
	}
}
