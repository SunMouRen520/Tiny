cmake_minimum_required(VERSION 3.12.4)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(IronBranch REQUIRED)

message("IronBranch Include Directires: ${IronBranch_INCLUDE_DIRS}")
message("IronBranch Link Directires: ${IronBranch_LINK_DIRS}")
include_directories(${IronBranch_INCLUDE_DIRS})
link_directories(${IronBranch_LINK_DIRS})

#include cmake utilities
include(support/CMakeUtility.cmake)

project(Tiny)


#we only have GLFW for now.
option(BUILDING_GLFW "Build with GLFW" ON)

option(PACKAGE_TESTS "Build the tests" OFF)

if(PACKAGE_TESTS)
    message("Tiny Test is ON")
    #setup testing
    macro(package_add_test TESTNAME fold file)
        add_executable(${TESTNAME} ${file})
        target_link_libraries(${TESTNAME} gtest gmock gtest_main fmtd)
        add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
        set_target_properties(${TESTNAME} PROPERTIES FOLDER ${fold})
        target_include_directories(${TESTNAME} PRIVATE ${PROJECT_SOURCE_DIR}/extern/googletest/googletest/include)
        target_include_directories(${TESTNAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
    endmacro()

    include(CTest)

    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
    set_target_properties(gtest PROPERTIES FOLDER extern)
    set_target_properties(gtest_main PROPERTIES FOLDER extern)
    set_target_properties(gmock PROPERTIES FOLDER extern)
    set_target_properties(gmock_main PROPERTIES FOLDER extern)

    enable_testing()
endif()


#enable folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#smelly
include_directories(src/)

add_subdirectory(src)


#
#
#
#
