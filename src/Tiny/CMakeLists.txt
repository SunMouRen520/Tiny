set(Input_SRC
    Core/Input/InputEvent.h
    Core/Input/InputsData.h
    Core/Input/InputSystem.h
    Core/Input/InputSystem.cpp
    Core/Input/WindowsInputSystem.h
    Core/Input/WindowsInputSystem.cpp
)

set(Plugin_SRC
    Core/Plugin/AbstractImporter.h
    Core/Plugin/AbstractImporter.cpp
    Core/Plugin/PluginManager.h
)

set(FileSystem_SRC
    FileSystem/CFileWrapper.h
    FileSystem/FileSystem.h
    FileSystem/FileSystem.cpp
)

set(TINY_CORE_SOURCES
    Application.h
    Application.cpp
    Types.h

    ${Input_SRC}
    ${Plugin_SRC}
    ${FileSystem_SRC}
)

add_library(TinyCore ${TINY_CORE_SOURCES})
set_target_properties(TinyCore PROPERTIES FOLDER "Tiny")
target_link_libraries(TinyCore IronBranch)
#target_link_libraries(TinyCore fmt-header-only)

source_group(Input FILES ${Input_SRC})
source_group(Plugin FILES ${Plugin_SRC})
source_group(FileSystem FILES ${FileSystem_SRC})

add_subdirectory(Math)
add_subdirectory(DebugTool)
add_subdirectory(Graphics)
add_subdirectory(Platform)
