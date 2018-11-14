cmake_minimum_required(VERSION 3.12.4)

project(Tiny)

#setup testing
macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(${TESTNAME} ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER Tiny/Math/Test)
    target_include_directories(${TESTNAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
endmacro()

option(PACKAGE_TESTS "Build the tests" OFF)
if(PACKAGE_TESTS)
    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
    set_target_properties(gtest PROPERTIES FOLDER extern)
    set_target_properties(gtest_main PROPERTIES FOLDER extern)
    set_target_properties(gmock PROPERTIES FOLDER extern)
    set_target_properties(gmock_main PROPERTIES FOLDER extern)

    enable_testing()
    #find_package(GTest REQUIRED)
    #include_directories(${GTEST_INCLUDE_DIR})
endif()

message("TEST is " ${PACKAGE_TESTS})

#enable folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)


#
#
#
#
