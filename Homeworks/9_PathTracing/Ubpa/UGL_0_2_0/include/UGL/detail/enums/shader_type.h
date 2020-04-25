/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#if 0\
|| (defined(GL_COMPUTE_SHADER))\
|| (defined(GL_VERTEX_SHADER))\
|| (defined(GL_GEOMETRY_SHADER))\
|| (defined(GL_FRAGMENT_SHADER))\
|| (defined(GL_TESS_CONTROL_SHADER))\
|| (defined(GL_TESS_EVALUATION_SHADER))
namespace Ubpa::gl {
	enum class ShaderType : GLenum {
#ifdef GL_COMPUTE_SHADER
		ComputeShader = GL_COMPUTE_SHADER,
#endif
#ifdef GL_VERTEX_SHADER
		VertexShader = GL_VERTEX_SHADER,
#endif
#ifdef GL_GEOMETRY_SHADER
		GeometryShader = GL_GEOMETRY_SHADER,
#endif
#ifdef GL_FRAGMENT_SHADER
		FragmentShader = GL_FRAGMENT_SHADER,
#endif
#ifdef GL_TESS_CONTROL_SHADER
		TessControlShader = GL_TESS_CONTROL_SHADER,
#endif
#ifdef GL_TESS_EVALUATION_SHADER
		TessEvaluationShader = GL_TESS_EVALUATION_SHADER,
#endif
	};
}
#endif
