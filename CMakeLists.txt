#[[
    TODO:
    Source files under src directory should be re-organized.
    Currently the structure is
    Tiny
        src
            DebugTool
            Graphics
    Should be refacted to
    Tiny
        src
            Tiny
                DebugTool
                Graphics
    In this way, we can keep the head include path fixed in develop environment and deploy environment.
]]

cmake_minimum_required(VERSION 3.12.4)

set(TINY_MAJOR_VERSION 0)
set(TINY_MINOR_VERSION 0)
set(TINY_PATCH_VERSION 0)

set(TINY_VERSION "${TINY_MAJOR_VERSION}.${TINY_MINOR_VERSION}.${TINY_PATCH_VERSION}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#here we define compile target for MSVC and android.
#2018/12/3, appearantly we do nothing android at all for now. so we set MSVC default ON.
set(BUILD_TARGET_MSVC ON)
set(BUILD_TARGET_ANDROID OFF)

find_package(IronBranch REQUIRED)
find_package(RapidJSON REQUIRED)

#include cmake utilities
# include(support/CMakeUtility.cmake)
include(support/macro.cmake)

project(Tiny)

# do not know
configure_file(support/config.h.in ${PROJECT_SOURCE_DIR}/src/Tiny/config.h )

#we only have GLFW for now.
# option(BUILDING_GLFW "Build with GLFW" ON)

option(PACKAGE_TESTS "Build the tests" OFF)

if(PACKAGE_TESTS)
    message("Tiny Test is ON")

    #setup testing
    include(CTest)
    enable_testing()
    macro(package_add_test TESTNAME fold file)
        add_executable(${TESTNAME} ${file})
        target_link_libraries(${TESTNAME} gtest gmock gtest_main)
        add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
        set_target_properties(${TESTNAME} PROPERTIES FOLDER ${fold})
        #this is ugly
        target_include_directories(${TESTNAME} PRIVATE ${PROJECT_SOURCE_DIR}/extern/googletest/googletest/include)
         #this is ugly
        target_include_directories(${TESTNAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
    endmacro()

    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
    set_target_properties(gtest PROPERTIES FOLDER extern)
    set_target_properties(gtest_main PROPERTIES FOLDER extern)
    set_target_properties(gmock PROPERTIES FOLDER extern)
    set_target_properties(gmock_main PROPERTIES FOLDER extern)

endif()


#enable folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


add_subdirectory(src)

# add_subdirectory(plugin/STB)


#
#
#
#
