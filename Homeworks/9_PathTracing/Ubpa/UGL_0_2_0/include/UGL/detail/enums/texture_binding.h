/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#include "texture_type.h"
#if 0\
|| (defined(GL_TEXTURE_BINDING_1D))\
|| (defined(GL_TEXTURE_BINDING_2D))\
|| (defined(GL_TEXTURE_BINDING_3D))\
|| (defined(GL_TEXTURE_BINDING_RECTANGLE))\
|| (defined(GL_TEXTURE_BINDING_1D_ARRAY))\
|| (defined(GL_TEXTURE_BINDING_2D_ARRAY))\
|| (defined(GL_TEXTURE_BINDING_CUBE_MAP))
namespace Ubpa::gl {
	enum class TextureBinding : GLenum {
#ifdef GL_TEXTURE_BINDING_1D
		TextureBinding1D = GL_TEXTURE_BINDING_1D,
#endif
#ifdef GL_TEXTURE_BINDING_2D
		TextureBinding2D = GL_TEXTURE_BINDING_2D,
#endif
#ifdef GL_TEXTURE_BINDING_3D
		TextureBinding3D = GL_TEXTURE_BINDING_3D,
#endif
#ifdef GL_TEXTURE_BINDING_RECTANGLE
		TextureBindingRectangle = GL_TEXTURE_BINDING_RECTANGLE,
#endif
#ifdef GL_TEXTURE_BINDING_1D_ARRAY
		TextureBinding1DArray = GL_TEXTURE_BINDING_1D_ARRAY,
#endif
#ifdef GL_TEXTURE_BINDING_2D_ARRAY
		TextureBinding2DArray = GL_TEXTURE_BINDING_2D_ARRAY,
#endif
#ifdef GL_TEXTURE_BINDING_CUBE_MAP
		TextureBindingCubeMap = GL_TEXTURE_BINDING_CUBE_MAP,
#endif
	};
}
#endif

#if 0\
|| (defined(GL_TEXTURE_BINDING_1D) && defined(GL_TEXTURE_1D))\
|| (defined(GL_TEXTURE_BINDING_2D) && defined(GL_TEXTURE_2D))\
|| (defined(GL_TEXTURE_BINDING_3D) && defined(GL_TEXTURE_3D))\
|| (defined(GL_TEXTURE_BINDING_RECTANGLE) && defined(GL_TEXTURE_RECTANGLE))\
|| (defined(GL_TEXTURE_BINDING_1D_ARRAY) && defined(GL_TEXTURE_1D_ARRAY))\
|| (defined(GL_TEXTURE_BINDING_2D_ARRAY) && defined(GL_TEXTURE_2D_ARRAY))\
|| (defined(GL_TEXTURE_BINDING_CUBE_MAP) && defined(GL_TEXTURE_CUBE_MAP))
namespace Ubpa::gl {
	inline TextureBinding BindOf(TextureType type) {
		switch (type) {
#if defined(GL_TEXTURE_BINDING_1D) && defined(GL_TEXTURE_1D)
		case TextureType::Texture1D:
			return TextureBinding::TextureBinding1D;
#endif
#if defined(GL_TEXTURE_BINDING_2D) && defined(GL_TEXTURE_2D)
		case TextureType::Texture2D:
			return TextureBinding::TextureBinding2D;
#endif
#if defined(GL_TEXTURE_BINDING_3D) && defined(GL_TEXTURE_3D)
		case TextureType::Texture3D:
			return TextureBinding::TextureBinding3D;
#endif
#if defined(GL_TEXTURE_BINDING_RECTANGLE) && defined(GL_TEXTURE_RECTANGLE)
		case TextureType::TextureRectangle:
			return TextureBinding::TextureBindingRectangle;
#endif
#if defined(GL_TEXTURE_BINDING_1D_ARRAY) && defined(GL_TEXTURE_1D_ARRAY)
		case TextureType::Texture1DArray:
			return TextureBinding::TextureBinding1DArray;
#endif
#if defined(GL_TEXTURE_BINDING_2D_ARRAY) && defined(GL_TEXTURE_2D_ARRAY)
		case TextureType::Texture2DArray:
			return TextureBinding::TextureBinding2DArray;
#endif
#if defined(GL_TEXTURE_BINDING_CUBE_MAP) && defined(GL_TEXTURE_CUBE_MAP)
		case TextureType::TextureCubeMap:
			return TextureBinding::TextureBindingCubeMap;
#endif
		}
	}
}
#endif
