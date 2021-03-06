/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#if 0\
|| (defined(GL_LEQUAL))\
|| (defined(GL_GEQUAL))\
|| (defined(GL_LESS))\
|| (defined(GL_GREATER))\
|| (defined(GL_EQUAL))\
|| (defined(GL_NOTEQUAL))\
|| (defined(GL_ALWAYS))\
|| (defined(GL_NEVER))
namespace Ubpa::gl {
	enum class CompareFunc : GLenum {
#ifdef GL_LEQUAL
		Lequal = GL_LEQUAL,
#endif
#ifdef GL_GEQUAL
		Gequal = GL_GEQUAL,
#endif
#ifdef GL_LESS
		Less = GL_LESS,
#endif
#ifdef GL_GREATER
		Greater = GL_GREATER,
#endif
#ifdef GL_EQUAL
		Equal = GL_EQUAL,
#endif
#ifdef GL_NOTEQUAL
		Notequal = GL_NOTEQUAL,
#endif
#ifdef GL_ALWAYS
		Always = GL_ALWAYS,
#endif
#ifdef GL_NEVER
		Never = GL_NEVER,
#endif
	};
}
#endif

