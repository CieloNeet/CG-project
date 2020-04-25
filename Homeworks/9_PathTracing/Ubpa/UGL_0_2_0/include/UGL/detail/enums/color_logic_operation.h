/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#if 0\
|| (defined(GL_CLEAR))\
|| (defined(GL_SET))\
|| (defined(GL_INVERT))\
|| (defined(GL_NOOP))\
|| (defined(GL_AND))\
|| (defined(GL_AND_REVERSE))\
|| (defined(GL_AND_INVERTED))\
|| (defined(GL_NAND))\
|| (defined(GL_OR))\
|| (defined(GL_OR_REVERSE))\
|| (defined(GL_OR_INVERTED))\
|| (defined(GL_XOR))\
|| (defined(GL_NOR))\
|| (defined(GL_COPY))\
|| (defined(GL_COPY_INVERTED))\
|| (defined(GL_EQUIV))
namespace Ubpa::gl {
	enum class ColorLogicOperation : GLenum {
#ifdef GL_CLEAR
		Clear = GL_CLEAR,
#endif
#ifdef GL_SET
		Set = GL_SET,
#endif
#ifdef GL_INVERT
		Invert = GL_INVERT,
#endif
#ifdef GL_NOOP
		Noop = GL_NOOP,
#endif
#ifdef GL_AND
		And = GL_AND,
#endif
#ifdef GL_AND_REVERSE
		AndReverse = GL_AND_REVERSE,
#endif
#ifdef GL_AND_INVERTED
		AndInverted = GL_AND_INVERTED,
#endif
#ifdef GL_NAND
		Nand = GL_NAND,
#endif
#ifdef GL_OR
		Or = GL_OR,
#endif
#ifdef GL_OR_REVERSE
		OrReverse = GL_OR_REVERSE,
#endif
#ifdef GL_OR_INVERTED
		OrInverted = GL_OR_INVERTED,
#endif
#ifdef GL_XOR
		Xor = GL_XOR,
#endif
#ifdef GL_NOR
		Nor = GL_NOR,
#endif
#ifdef GL_COPY
		Copy = GL_COPY,
#endif
#ifdef GL_COPY_INVERTED
		CopyInverted = GL_COPY_INVERTED,
#endif
#ifdef GL_EQUIV
		Equiv = GL_EQUIV,
#endif
	};
}
#endif
