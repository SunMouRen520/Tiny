#pragma once

namespace Tiny {
	/*
		@brief	cross-platform application interface
	*/

	class Application {
	public:
		void StartUp();

		void Update(double dt);

		void ShutDown();
	};

}
