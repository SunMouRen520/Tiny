#include "Buffer.h"

namespace Tiny{ namespace Graphics{ namespace GL{

    Buffer::~Buffer(){

    }

	void Buffer::CreateImpl() {
		glGenBuffers(1, &_id);
	}

	void Buffer::CreateImplWithDSA() {
		glCreateBuffers(1, &_id);
	}
} } }
