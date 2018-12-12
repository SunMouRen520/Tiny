set(MATH_HEADERS
    Angle.h
    Quaternion.h
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
    Tags.h
)


add_library(Math ${MATH_HEADERS} dummy.cpp)
set_target_properties(Math PROPERTIES FOLDER "Tiny/Math")
target_include_directories(Math PRIVATE ${CMAKE_SOURCE_DIR}/src)

# IDE(Math "${MATH_HEADERS}" "Tiny/Math")

if(PACKAGE_TESTS)
    add_subdirectory(Test)
endif()
