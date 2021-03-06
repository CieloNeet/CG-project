/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#include "renderbuffer_type.h"
#if 0\
|| (defined(GL_RENDERBUFFER_BINDING))
namespace Ubpa::gl {
	enum class RenderbufferBinding : GLenum {
#ifdef GL_RENDERBUFFER_BINDING
		RenderbufferBinding = GL_RENDERBUFFER_BINDING,
#endif
	};
}
#endif

#if 0\
|| (defined(GL_RENDERBUFFER_BINDING) && defined(GL_RENDERBUFFER))
namespace Ubpa::gl {
	inline RenderbufferBinding BindOf(RenderbufferType type) {
		switch (type) {
#if defined(GL_RENDERBUFFER_BINDING) && defined(GL_RENDERBUFFER)
		case RenderbufferType::Renderbuffer:
			return RenderbufferBinding::RenderbufferBinding;
#endif
		}
	}
}
#endif
