#pragma once

#include <memory>
#include "IronBranch/Utility/Log.h"
#include "Tiny/Core/FrameManager.h"
#include "Tiny/Core/Time/Time.h"

namespace Tiny{
    /*
        FixME: Maybe this is not the right way to organizing code.

        @brief  The main purpose of serivce
            1. to provice global access for object.
            2. control initialization of global object.
            3. avoid singleton.

        @caution Service is just kind of global variable, which should avoid as much as possible.
    */
    class Service{
    public:
        static IronBranch::Utility::Logger& Log();
        static FrameManager& FrameManager();
        static Time& Time();

        static void SetLogger(std::unique_ptr<IronBranch::Utility::Logger> logger);
        static void SetFrameManager(std::unique_ptr<Tiny::FrameManager> fm);
        static void SetTime(std::unique_ptr<Tiny::Time> t);

    private:
        static std::unique_ptr<IronBranch::Utility::Logger> _logger;
        static std::unique_ptr<Tiny::FrameManager> _frameMgr;
        static std::unique_ptr<Tiny::Time>        _time;
	};
}
