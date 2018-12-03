#Design of Graphics:
    1. Ideally, Graphics system only take render related data as input and has nothing to do with other part of the engine..
    To achieve this, the following facilities must be provided.

        * well-defines render input data-structure..
            For simplicity, every obect that has graphics output owns it's render data and feeds into the render system during render.
        * to be continue
    2. Overview:
        GL submodule provides two-level abstraction of OpenGL:
        - Wrapper of raw OpenGL interface
        - OpenGl state management

        Mesh/Texture(abbr M/T) submodule provides the internal data structure of M/T and provide related utilities. And the internal data structure is also the target of resource loading result.

    3. Subsystems:
        * GL:
            + Design purpose:
                - Provide modern cxx type safe facilities
                    + So we are avoiding using raw OpenGL interface such as glGenBuffer, we shall create GL::Buffer() object instead.
                    + Using modern c++ facilities such as RAII to handle raw OpenGL resources, which makes code-base more robust.
                    + All GL
                - Provide compatibility cross different OpenGL versions
                - OpenGL state management
            + Design Principles:
                - All GL objects should not contain raw-data. such as image data or buffer data. We just wrap around OpenGL interface and holding state inside.

            + Developing State:
                - 2018/12/01 Due to the fact that i'm just newbie to OpenGL, So I decide to only support OpenGL 4.5, which is the OpenGL version of <OpenGl SuperBible 7th>. When OpenGL 4.5 jobs are done, i'll go ahead with OpenGL ES 3.0.

        * Texture:
            + Basically, texture data comprise of two layers: ImageData and TextureData.
                - ImageData defines the raw-input images. And we need some facility to load ImageData from resources.
                - TextureData controls how the ImageData interpreted.
        *

#Basic file organization of Graphics:
    1. Every subfolder under Graphics contains specific data structures and relate tools.
        For example, Texture directory contains texture data structures and texture related tools such as altas, sampler etc.