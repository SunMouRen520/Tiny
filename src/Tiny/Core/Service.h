#pragma once

#include "IronBranch/Utility/Log.h"

#include <memory>

namespace IronBranch{
    namespace Utility{
        class Logger;
    }
}

namespace Tiny{
    class Service{
    public:
        static void SetLogger()

    private:
        static std::unique_ptr<IronBranch::Utility::Logger> _logger;
    }
}
