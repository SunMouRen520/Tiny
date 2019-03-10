#pragma once

#include "Tiny/Math/Vector3.h"


namespace Tiny{ namespace Graphics{
    /*
        @brief  3D Axis-aligned bounding boxes
    */
    class AABB {
    public:
        using Vector = Math::Vector<3, float>;

        implicit AABB();
        ~AABB() = default;

        /*
            @brief  Add new pointy to aabb
        */
        void AddPoint(const Vector &point);

        /*
            @brief  clear exists data.
        */
        void Clear();

        /*
            @brief  Check if the target point inside 
        */
        bool PointInside(const Vector &point);

    private:
        Vector  _min;
        Vector  _max;
    };
} }
