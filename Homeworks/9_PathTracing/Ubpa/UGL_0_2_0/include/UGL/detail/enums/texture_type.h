/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#if 0\
|| (defined(GL_TEXTURE_1D))\
|| (defined(GL_TEXTURE_2D))\
|| (defined(GL_TEXTURE_3D))\
|| (defined(GL_TEXTURE_RECTANGLE))\
|| (defined(GL_TEXTURE_1D_ARRAY))\
|| (defined(GL_TEXTURE_2D_ARRAY))\
|| (defined(GL_TEXTURE_CUBE_MAP))
namespace Ubpa::gl {
	enum class TextureType : GLenum {
#ifdef GL_TEXTURE_1D
		Texture1D = GL_TEXTURE_1D,
#endif
#ifdef GL_TEXTURE_2D
		Texture2D = GL_TEXTURE_2D,
#endif
#ifdef GL_TEXTURE_3D
		Texture3D = GL_TEXTURE_3D,
#endif
#ifdef GL_TEXTURE_RECTANGLE
		TextureRectangle = GL_TEXTURE_RECTANGLE,
#endif
#ifdef GL_TEXTURE_1D_ARRAY
		Texture1DArray = GL_TEXTURE_1D_ARRAY,
#endif
#ifdef GL_TEXTURE_2D_ARRAY
		Texture2DArray = GL_TEXTURE_2D_ARRAY,
#endif
#ifdef GL_TEXTURE_CUBE_MAP
		TextureCubeMap = GL_TEXTURE_CUBE_MAP,
#endif
	};
}
#endif

