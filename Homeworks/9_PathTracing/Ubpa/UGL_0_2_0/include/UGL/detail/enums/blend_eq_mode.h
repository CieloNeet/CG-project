/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#if 0\
|| (defined(GL_FUNC_ADD))\
|| (defined(GL_FUNC_SUBTRACT))\
|| (defined(GL_FUNC_REVERSE_SUBTRACT))\
|| (defined(GL_MIN))\
|| (defined(GL_MAX))
namespace Ubpa::gl {
	enum class BlendEqMode : GLenum {
#ifdef GL_FUNC_ADD
		FuncAdd = GL_FUNC_ADD,
#endif
#ifdef GL_FUNC_SUBTRACT
		FuncSubtract = GL_FUNC_SUBTRACT,
#endif
#ifdef GL_FUNC_REVERSE_SUBTRACT
		FuncReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
#endif
#ifdef GL_MIN
		Min = GL_MIN,
#endif
#ifdef GL_MAX
		Max = GL_MAX,
#endif
	};
}
#endif
