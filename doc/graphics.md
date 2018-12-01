#Design of Graphics:
    1. Idealy, Graphics system only take render related data as input and has nothing to do with other part of the engine..
    To achieve this, the folowing facilities must be provided.

        * well-defines render input data-structure..
        For navie implementation, every obect that has graphics output owns it's render data and feeds into the render system during render.
        * to be continue
    2. Overview:
        GL submodule provides the abstraction of raw opengl interface.
        
        Mesh/Texture(abbr M/T) submodule provides the interal data structure of M/T and provide related utilities. And the internal data structure is also the target of resource loading result.

    3. Subsystems:
        * GL:
            + Design purpose:
                - Prodive modern cxx type safe facilities
                    + So we are avoiding using raw opengl interface such as glGenBuffer, we shall create GL::Buffer() object instead.
                    + Using modern c++ facilities such as RAII to handle raw opengl resources, which makes code-base more robust.
                    + All GL
                - Provide compatiblity cross different opengl versions
            + Design Pricinples:
                - All GL objects should not contain raw-data. such as image data or buffer data. We just wrapp around opengl interface and holding state inside.

            + Developing State:
                - 2018/12/01 Due to the fact that i'm just newbee to OpenGL, So I decide to only support openGL 4.5, which is the OpenGL version of <OpenGl SuperBible 7th>

        * Texture:
            + Basically, texture data comprise of two layers: ImageData and TextureData.
                - ImageData defines the raw-input images. And we need some facility to load ImageData from resources.
                - TextureData controls how the ImageData interpreted.
        *

#Basic file organization of Graphics:
    1. Every subfolder under Graphics contains specific data structures and relate tools.
        For example, Texture directory contains texture data structes and texture related tools such as altas, sampler etc.
