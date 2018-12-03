#
#TODO
#1.     On windows, Graphics module must be compiled with GLFW supported.
#       But on android, appearantly GLFW is not needed. so we will see.
#2.

set(Graphics_RenderSystem_SRC
    RenderSystem.h
    RenderSystem.cpp
)

set(Texture_FILES
    Texture/TextureData.h
    Texture/TextureData.cpp
    Texture/ImageData.h
    Texture/ImageData.cpp
)

set(GL_FILES
    GL/Buffer.cpp
    GL/Buffer.h
    GL/Context.h
    GL/Commondef.h
)

set(Graphics_SRC
    ${Graphics_RenderSystem_SRC}
    ${Texture_FILES}
    ${GL_FILES}
)

add_library(Graphics ${Graphics_SRC})
target_link_libraries(Graphics PRIVATE IronBranch)

if(BUILD_TARGET_MSVC)
    find_package(gl3w REQUIRED)
    find_package(glfw3 REQUIRED)
    target_link_libraries(Graphics PRIVATE gl3w PRIVATE glfw3)
endif()

#add msvc filter group
source_group("GL" FILES ${GL_FILES})
source_group("Texture" FILES ${Texture_FILES})
source_group("RenderSystem" FILES ${Graphics_RenderSystem_SRC})
