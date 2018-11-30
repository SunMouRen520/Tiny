set(TINY_CORE_SOURCES
    dummy.cpp
)

add_library(TinyCore ${TINY_CORE_SOURCES})
set_target_properties(TinyCore PROPERTIES FOLDER "Tiny")
#target_link_libraries(TinyCore fmt-header-only)

add_subdirectory(Math)
add_subdirectory(DebugTool)
