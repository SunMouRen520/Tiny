#include "Buffer.h"

namespace Tiny{ namespace Graphics{ namespace GL{
    Buffer::Buffer(){
        glCreateBuffers(1, &_id);
    }

    Buffer::~Buffer(){

    }
} } }
