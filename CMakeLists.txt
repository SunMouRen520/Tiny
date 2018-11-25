cmake_minimum_required(VERSION 3.12.4)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Tiny)

option(PACKAGE_TESTS "Build the tests" OFF)
if(PACKAGE_TESTS)

    #setup testing
    macro(package_add_test TESTNAME)
        add_executable(${TESTNAME} ${ARGN})
        target_link_libraries(${TESTNAME} gtest gmock gtest_main)
        add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
        set_target_properties(${TESTNAME} PROPERTIES FOLDER Tiny/Math/Test)
        #SET_TESTS_PROPERTIES(${TESTNAME} PROPERTIES DEPENDS ${TESTNAME})
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

message("TEST is " ${PACKAGE_TESTS})

#enable folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)


#
#
#
#
