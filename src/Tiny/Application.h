#pragma once

#include "Tiny/Core/Engine.h"

#include "Tiny/Math/Vector2.h"

namespace Tiny {
	/*
		@brief	cross-platform application interface
	*/

	class Application {
	public:
		// virtual void OnCreate() = 0;
		//
		// virtual void OnQuit() = 0;

		virtual void SetResolution(int x, int y) = 0;

		virtual Math::Vector2i GetResolution() = 0;

		virtual const std::string& GetAppPath() const = 0;

		virtual void OnResolutionChanged(int lastX, int lastXy) = 0;
		virtual void OnRenderFrameDone() = 0;
		virtual void OnFrameDone() = 0;

	protected:
		Engine _engine;
	};

}
