set(Input_SRC
    Input/InputEvent.h
    Input/InputsData.h
    Input/InputSystem.h
    Input/InputSystem.cpp
    Input/WindowsInputSystem.h
    Input/WindowsInputSystem.cpp
    Input/Interface/Data.h
    Input/Interface/Input.cpp
    Input/Interface/Input.h

    Core/Time.h
    Core/Engine.h
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

set(TINY_CORE_SOURCES
    Application.h
    Application.cpp
    Types.h

    ${Input_SRC}
    ${Plugin_SRC}
    ${FileSystem_SRC}
    ${Resource_SRC}
)

add_library(TinyCore ${TINY_CORE_SOURCES})
set_target_properties(TinyCore PROPERTIES FOLDER "Tiny")
target_include_directories(TinyCore PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(TinyCore IronBranch)

source_group(Input FILES ${Input_SRC})
source_group(Plugin FILES ${Plugin_SRC})
source_group(FileSystem FILES ${FileSystem_SRC})
source_group(Resource FILES ${Resource_SRC})

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
