#include "Tiny/Core/Time/Time.h"
#include "Tiny/Core/Service.h"

using namespace std::chrono;
namespace Tiny{
    Time::Time()
    :_logicTime(0.0){

    }

    void Time::Init(){
        _startTimeSec = duration_cast<seconds>( system_clock::now().time_since_epoch() );
        _startTimeMilliSec = duration_cast<milliseconds>( system_clock::now().time_since_epoch() );
        _startTimeMacroSec = duration_cast<microseconds>( system_clock::now().time_since_epoch() );
    }

    Long Time::GetTime(TimePrecision p) const{
         Long result;
         switch (p) {
             case TimePrecision::SEC:
             result = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
             break;
             case TimePrecision::MILLISEC:
             result = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
             break;
             case TimePrecision::MICROSEC:
             result = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
             break;
         }
         return result;
    }

    Long Time::GetTimeSinceLaunch(TimePrecision p) const{
		Long result;
        switch (p) {
            case TimePrecision::SEC:
            result = duration_cast<seconds>(system_clock::now().time_since_epoch() - _startTimeSec).count();
            break;
            case TimePrecision::MILLISEC:
            result = duration_cast<milliseconds>(system_clock::now().time_since_epoch() - _startTimeMilliSec).count();
            break;
            case TimePrecision::MICROSEC:
            result = duration_cast<microseconds>(system_clock::now().time_since_epoch() - _startTimeMacroSec).count();
            break;
        }
        return result;
    }

    double Time::GetLogicTimeSinceLaunch() const{
        return _logicTime;
    }

    void Time::Update(){
        _logicTime += Service::FrameManager().GetLogicalFrameDelta();
    }
}
