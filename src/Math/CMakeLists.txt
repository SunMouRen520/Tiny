set(MATH_HEADERS
    Vector.h
    Vector3.h
    RectangularMatrix.h
    Matrix.h
    Matrix3.h
    Matrix4.h
)

add_custom_target(Math SOURCES ${MATH_HEADERS})
#target_include_directories(Tiny_Math PRIVATE .)
set_target_properties(Math PROPERTIES FOLDER "Tiny/Math")
