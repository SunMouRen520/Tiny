set(Input_SRC
    Input/Def.h
    Input/InputEvent.h
    Input/InputForward.h
    Input/InputSystem.h
    Input/InputSystem.cpp
    Input/Module/InputModule.h
    Input/Module/InputQueue.h
    Input/Module/JoypadModule.h
    Input/Module/JoypadModule.cpp
    Input/Module/KeyboardMouseModule.h
    Input/Module/KeyboardMouseModule.cpp
)

set(Plugin_SRC
    Core/Plugin/AbstractImporter.h
    Core/Plugin/PluginManager.h
    Core/Plugin/PluginManager.cpp
)

set(FileSystem_SRC
    FileSystem/CFileWrapper.h
    FileSystem/FileSystem.h
    FileSystem/FileSystem.cpp
    FileSystem/Utility.h
)

set(Resource_SRC
    Core/Resource/ResourceManager.h
    Core/Resource/ResourceManager.cpp
)

set(Platform_SRC
    Platform/Win/AppWindows.cpp
    Platform/Win/GLFWKeyMap.cpp
    Platform/Win/GLFWKeyMap.h
)

set(TINY_CORE_SOURCES
    Application.h
    Application.cpp
    Types.h
    Def.h

    Core/Time/Time.h
    Core/Time/Time.cpp
    Core/Time/Timeline.h
    Core/Time/Timeline.cpp
    Core/Engine.h
    Core/Engine.cpp
    Core/Service.h
    Core/Service.cpp
    Core/FrameManager.h
    Core/FrameManager.cpp

    ${Input_SRC}
    ${Plugin_SRC}
    ${FileSystem_SRC}
    ${Resource_SRC}
    ${Platform_SRC}
)

add_library(TinyCore ${TINY_CORE_SOURCES})
set_target_properties(TinyCore PROPERTIES FOLDER "Tiny")
target_include_directories(TinyCore PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(TinyCore IronBranch gl3w assimp::assimp)

source_group(Input FILES ${Input_SRC})
source_group(Plugin FILES ${Plugin_SRC})
source_group(FileSystem FILES ${FileSystem_SRC})
source_group(Resource FILES ${Resource_SRC})
source_group(Platform FILES ${Platform_SRC})

add_subdirectory(Math)
add_subdirectory(DebugTool)
add_subdirectory(Graphics)
add_subdirectory(Platform)

add_custom_target(copy_plugin_def
  # todo: check if debug and release folder exist
  # debug version
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/plugin/ImporterDef.json         ${CMAKE_SOURCE_DIR}/bin/plugin/ImporterDef.json
)

set_target_properties(copy_plugin_def PROPERTIES FOLDER "Tiny")
target_link_libraries(TinyCore Graphics Math)

add_dependencies(TinyCore copy_plugin_def)

set(TinyApp_SRC
    Platform/Win/AppWindows.cpp
    Platform/Win/GLFWKeyMap.h
    Platform/Win/GLFWKeyMap.cpp
)

add_executable(TinyApp ${TinyApp_SRC})
target_link_libraries(TinyApp TinyCore glfw)
