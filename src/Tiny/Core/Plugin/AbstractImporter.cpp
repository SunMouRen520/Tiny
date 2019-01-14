#include "Tiny/Core/Plugin/AbstractImporter.h"

namespace Tiny{ namespace PLUGIN {
	Graphics::ImageData2D AbstractImporter::Image2D(const std::string& path) {
		return DoImage2D(path);
	}

	Graphics::ImageData2D AbstractImporter::DoImage2D(const std::string& path) {
		assert(false);
	}
}
}