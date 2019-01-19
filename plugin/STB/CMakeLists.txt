cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(IronBranch REQUIRED)

#TODO:temp code,
include_directories(../../src)

project(STB)

set(STB_SOURCE
    ImageLoader.h
    ImageLoader.cpp
    stb_image.h
)

add_library(STBPlugin SHARED ${STB_SOURCE})
set_target_properties(STBPlugin PROPERTIES FOLDER "STBPlugin")
set_target_properties(STBPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin" )
target_link_libraries(STBPlugin IronBranch)

IF( NOT CMAKE_BUILD_TYPE )
   set(CMAKE_BUILD_TYPE DEBUG)
ENDIF()

add_custom_target(Z_copy_plugin_config
  # todo: check if debug and release folder exist
  # debug version
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/plugin/PluginConfig.json ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin/plugin/PluginConfig.json
)

add_dependencies(STBPlugin Z_copy_plugin_config)
