#include "Tiny/Core/Time/Time.h"
#include "Tiny/Core/Service.h"

using namespace std::chrono;
namespace Tiny{
    Time::Time()
    :_logicTime(0.0){

    }

    void Time::Init(){
        _startTime = duration_cast< seconds>( system_clock::now().time_since_epoch() );
    }
    double Time::GetTime() const{
        return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    }

    double Time::GetTimeSinceLaunch() const{
		return duration_cast<seconds>(system_clock::now().time_since_epoch() - _startTime).count();
    }

    double Time::GetLogicTimeSinceLaunch() const{
        return _logicTime;
    }

    void Time::Update(){
        _logicTime += Service::FrameManager().GetLogicalFrameDelta();
    }
}
