set(MATH_HEADERS
    Angle.h
    Vector.h
    Vector2.h
    Vector3.h
    Vector4.h
    RectangularMatrix.h
    Matrix.h
    Matrix3.h
    Matrix4.h
    Tools.h
    MathForward.h
)
IDE(Math "${MATH_HEADERS}" "Tiny/Math")

if(PACKAGE_TESTS)
    add_subdirectory(Test)
endif()
