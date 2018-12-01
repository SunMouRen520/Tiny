set(Graphics_IDE_FILES
    RenderSystem.h
    RenderSystem.cpp
)

set(Texture_IDE_FILES
    Texture/TextureData.h
    Texture/TextureData.cpp
    Texture/ImageData.h
    Texture/ImageData.cpp
)

set(GL_IDE_FILES
    GL/Buffer.cpp
    GL/Buffer.h
)

set(IDE_FILES
    ${Graphics_IDE_FILES}
    ${Texture_IDE_FILES}
    ${GL_IDE_FILES}
)

IDE("Graphics" "${IDE_FILES}" "Tiny/Graphics")

#add msvc filter group
source_group("Texture" FILES ${Texture_IDE_FILES})
source_group("Graphics" FILES ${Graphics_IDE_FILES})
source_group("GL" FILES ${GL_IDE_FILES})
