set(EXT_SOURCE
    Ext.h
    Ext.cpp

    Loader/ImageLoader.h
    Loader/ImageLoader.cpp
    Loader/stb_image.h
)

add_library(EXT ${EXT_SOURCE})
set_target_properties(EXT PROPERTIES FOLDER "EXT")
target_link_libraries(EXT IronBranch)
