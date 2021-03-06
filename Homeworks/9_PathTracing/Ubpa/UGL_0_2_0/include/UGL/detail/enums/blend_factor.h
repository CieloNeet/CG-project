/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#if 0\
|| (defined(GL_ZERO))\
|| (defined(GL_ONE))\
|| (defined(GL_SRC_COLOR))\
|| (defined(GL_ONE_MINUS_SRC_COLOR))\
|| (defined(GL_DST_COLOR))\
|| (defined(GL_ONE_MINUS_DST_COLOR))\
|| (defined(GL_SRC_ALPHA))\
|| (defined(GL_ONE_MINUS_SRC_ALPHA))\
|| (defined(GL_DST_ALPHA))\
|| (defined(GL_ONE_MINUS_DST_ALPHA))\
|| (defined(GL_CONSTANT_COLOR))\
|| (defined(GL_ONE_MINUS_CONSTANT_COLOR))\
|| (defined(GL_CONSTANT_ALPHA))\
|| (defined(GL_ONE_MINUS_CONSTANT_ALPHA))\
|| (defined(GL_SRC_ALPHA_SATURATE))\
|| (defined(GL_SRC1_COLOR))\
|| (defined(GL_ONE_MINUS_SRC1_COLOR))\
|| (defined(GL_SRC1_ALPHA))\
|| (defined(GL_ONE_MINUS_SRC1_ALPHA))
namespace Ubpa::gl {
	enum class BlendFactor : GLenum {
#ifdef GL_ZERO
		Zero = GL_ZERO,
#endif
#ifdef GL_ONE
		One = GL_ONE,
#endif
#ifdef GL_SRC_COLOR
		SrcColor = GL_SRC_COLOR,
#endif
#ifdef GL_ONE_MINUS_SRC_COLOR
		OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
#endif
#ifdef GL_DST_COLOR
		DstColor = GL_DST_COLOR,
#endif
#ifdef GL_ONE_MINUS_DST_COLOR
		OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
#endif
#ifdef GL_SRC_ALPHA
		SrcAlpha = GL_SRC_ALPHA,
#endif
#ifdef GL_ONE_MINUS_SRC_ALPHA
		OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
#endif
#ifdef GL_DST_ALPHA
		DstAlpha = GL_DST_ALPHA,
#endif
#ifdef GL_ONE_MINUS_DST_ALPHA
		OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
#endif
#ifdef GL_CONSTANT_COLOR
		ConstantColor = GL_CONSTANT_COLOR,
#endif
#ifdef GL_ONE_MINUS_CONSTANT_COLOR
		OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
#endif
#ifdef GL_CONSTANT_ALPHA
		ConstantAlpha = GL_CONSTANT_ALPHA,
#endif
#ifdef GL_ONE_MINUS_CONSTANT_ALPHA
		OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
#endif
#ifdef GL_SRC_ALPHA_SATURATE
		SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE,
#endif
#ifdef GL_SRC1_COLOR
		Src1Color = GL_SRC1_COLOR,
#endif
#ifdef GL_ONE_MINUS_SRC1_COLOR
		OneMinusSrc1Color = GL_ONE_MINUS_SRC1_COLOR,
#endif
#ifdef GL_SRC1_ALPHA
		Src1Alpha = GL_SRC1_ALPHA,
#endif
#ifdef GL_ONE_MINUS_SRC1_ALPHA
		OneMinusSrc1Alpha = GL_ONE_MINUS_SRC1_ALPHA,
#endif
	};
}
#endif

