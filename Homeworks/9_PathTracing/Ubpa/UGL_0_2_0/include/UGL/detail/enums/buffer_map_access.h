/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#if 0\
|| (defined(GL_READ_ONLY))\
|| (defined(GL_WRITE_ONLY))\
|| (defined(GL_READ_WRITE))
namespace Ubpa::gl {
	enum class BufferMapAccess : GLenum {
#ifdef GL_READ_ONLY
		ReadOnly = GL_READ_ONLY,
#endif
#ifdef GL_WRITE_ONLY
		WriteOnly = GL_WRITE_ONLY,
#endif
#ifdef GL_READ_WRITE
		ReadWrite = GL_READ_WRITE,
#endif
	};
}
#endif
