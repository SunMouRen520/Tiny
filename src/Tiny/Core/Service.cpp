#include "Tiny/Core/Service.h"

#include "Tiny/config.h"

namespace Tiny{
    std::unique_ptr<IronBranch::Utility::Logger> Service::_logger = nullptr;
    std::unique_ptr<Tiny::FrameManager> Service::_frameMgr = nullptr;
    std::unique_ptr<Time>        Service::_time = nullptr;

    void Service::SetLogger(std::unique_ptr<IronBranch::Utility::Logger> logger){
        _logger = std::move(logger);
    }
    IronBranch::Utility::Logger& Service::Log() {
#ifdef TINY_DEBUG
        if(!_logger)
            assert(false);
#endif

        return *_logger;
    }

    void Service::SetFrameManager(std::unique_ptr<Tiny::FrameManager> fm){
        _frameMgr = std::move(fm);
    }

    FrameManager& Service::FrameManager(){
#ifdef TINY_DEBUG
        if(!_frameMgr)
            assert(false);
#endif
        return *_frameMgr;
    }

    void Service::SetTime(std::unique_ptr<Tiny::Time> t){
        _time = std::move(t);
    }

    Time& Service::Time(){
#ifdef TINY_DEBUG
        if(!_time)
            assert(false);
#endif
        return *_time;
    }
}
