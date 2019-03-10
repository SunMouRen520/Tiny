#pragma once

#include "Tiny/Math/Vector3.h"

namespace Tiny{
    namespace Math{

        /*
            @brief  2D point-line signed distance
            Given 2d implicit line L with equation: Ax + By + C = 0 and point P(a, b),
            signed distance from P to L is  A*a + B * b + C / math::sqrt(math::pow(A, 2) + math::pow(B, 2))
        */
        template<typename T>
        float SignedDistance(Vector2<T> p, const T& A, onst T& B, const T& C){
            return (A * p.X() + B * p.Y() + C) / math::sqrt(math::pow(A, 2) + math::pow(B, 2));
        }
    }
}
