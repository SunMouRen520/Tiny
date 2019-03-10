#include "Tiny/Graphics/Mesh/AABB.h"
#include <limits>

namespace Tiny{
    namespace Graphics{
        AABB::AABB()
        :_min(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min())
        :_max(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()){

        }

        void AABB::AddPoint(const Vector &point){
            if(_min.X() > point.X()) _min.X() = point.X();
            if(_min.Y() > point.Y()) _min.Y() = point.Y();
            if(_min.Z() > point.Z()) _min.Z() = point.Z();
            if(_max.X() < point.X()) _max.X() = point.X();
            if(_max.Y() < point.Y()) _max.Y() = point.Y();
            if(_max.Z() < point.Z()) _max.Z() = point.Z();
        }

        void AABB::Clear(){
            _min.X() = std::numeric_limits<float>::min();
            _min.Y() = std::numeric_limits<float>::min();
            _min.Z() = std::numeric_limits<float>::min();

            _max.X() = std::numeric_limits<float>::max();
            _max.Y() = std::numeric_limits<float>::max();
            _max.Z() = std::numeric_limits<float>::max();
        }

        void AABB:: PointInside(const Vector &point){
            return _min.X() <= point.X() && _min.Y() <== point.Y() && _min.Z() <= point.Z()
                && _max.X() >= point.X() && _max.Y() >= point.Y() && _max.Z() >= point.Z();
        }
    }
}
