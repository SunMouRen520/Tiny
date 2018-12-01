#ifndef TINY_APPLICATION_H
#define TINY_APPLICATION_H

namespace Tiny {
	/*
		@brief	cross-platform application interface
	*/

	class Application {
	public:
		virtual void StartUp();

		void Update(double dt);
		
		virtual void ShutDown();
	};

}

#endif // !TINY_APPLICATION_H
