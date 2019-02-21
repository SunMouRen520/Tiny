#
#TODO
#1.     On windows, Graphics module must be compiled with GLFW supported.
#       But on android, appearantly GLFW is not needed. so we will see.
#2.

set(Graphics_RenderSystem_SRC
    RenderSystem.h
    RenderSystem.cpp
    Memory.h
)

set(Texture_FILES
    Texture/TextureData.h
    Texture/TextureData.cpp
    Texture/ImageData.h
    Texture/ImageData.cpp
    Texture/Definition.h
)

set(GL_FILES
    GL/Buffer.cpp
    GL/Buffer.h
    GL/Context.h
    GL/Definition.h
    GL/OpenGL.h
)

set(Renderer_FILES
  Renderer/Renderer.h
  Renderer/Command.h
  Renderer/Renderer.cpp

  Renderer/Object/AbstractObject.h
  Renderer/Object/Buffer.h
  Renderer/Object/Buffer.cpp
)

set(SCENE_FILES
    Scene/Camera.h
    Scene/Camera.cpp
    Scene/Light.h
    Scene/Light.cpp
)

set(Graphics_SRC
    ${Graphics_RenderSystem_SRC}
    ${Texture_FILES}
    ${GL_FILES}
    ${SCENE_FILES}
    ${Renderer_FILES}
)

add_library(Graphics ${Graphics_SRC})
set_target_properties(Graphics PROPERTIES FOLDER "Tiny")
target_link_libraries(Graphics PRIVATE IronBranch)
target_include_directories(Graphics PUBLIC
$<TARGET_PROPERTY:TinyCore,INTERFACE_INCLUDE_DIRECTORIES>)


if(BUILD_TARGET_MSVC)
    find_package(gl3w REQUIRED)
    find_package(glfw3 REQUIRED)
    target_link_libraries(Graphics PRIVATE gl3w PRIVATE glfw3)
endif()

#add msvc filter group
source_group("GL" FILES ${GL_FILES})
source_group("Texture" FILES ${Texture_FILES})
source_group("RenderSystem" FILES ${Graphics_RenderSystem_SRC})
source_group("Scene" FILES ${SCENE_FILES})
source_group("Renderer" FILES ${Renderer_FILES})
