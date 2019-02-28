#include "Tiny/Core/Time/Timeline.h"
#include "Tiny/Core/Service.h"

namespace Tiny{
    Timeline::ID Timeline::_uniqueID = 0;

    Timeline::ID Timeline::CreateTimeline(TimePrecision prec, float startTime , float timeStep, float endTime, bool loop){
        _timelines.emplace(std::make_pair(_uniqueID, TimelineObj(prec, startTime, timeStep, endTime, loop)));
        return _uniqueID++;
    }

    void Timeline::DeleteTimeline(ID id){
        _timelines.erase(id);
    }

    float Timeline::GetTime(ID id){
        auto iter = _timelines.find(id);
        if(iter == _timelines.end()){
            Service::Log().E("Timeline cannot find ID:{}", id);
            return 0.f;
        }
        return iter->second.currentTime;
    }

    void Timeline::Update(){
        for(auto& tl : _timelines){
            TimelineObj& obj = tl.second;
            if(obj.endTime == 0 || obj.currentTime < obj.endTime){
                obj.currentTime += obj.timeStep;
                if(obj.currentTime > obj.endTime){
                    if(obj.loop)
                        obj.currentTime = obj.startTime;
                    else
                        obj.currentTime = obj.endTime;
                }
            }
        }
    }
}
