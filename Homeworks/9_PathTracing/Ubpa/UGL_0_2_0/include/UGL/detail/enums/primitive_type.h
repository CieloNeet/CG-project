/*
* Generated by python
* Any changes to this file will be overwritten by the next python run
*/

#pragma once

#include "../../config.h"
#if 0\
|| (defined(GL_POINTS))\
|| (defined(GL_LINES))\
|| (defined(GL_LINE_STRIP))\
|| (defined(GL_LINE_LOOP))\
|| (defined(GL_TRIANGLES))\
|| (defined(GL_TRIANGLE_STRIP))\
|| (defined(GL_TRIANGLE_FAN))\
|| (defined(GL_LINES_ADJACENCY))\
|| (defined(GL_LINE_STRIP_ADJACENCY))\
|| (defined(GL_TRIANGLES_ADJACENCY))\
|| (defined(GL_TRIANGLE_STRIP_ADJACENCY))\
|| (defined(GL_PATCHES))
namespace Ubpa::gl {
	enum class PrimitiveType : GLenum {
#ifdef GL_POINTS
		Points = GL_POINTS,
#endif
#ifdef GL_LINES
		Lines = GL_LINES,
#endif
#ifdef GL_LINE_STRIP
		LineStrip = GL_LINE_STRIP,
#endif
#ifdef GL_LINE_LOOP
		LineLoop = GL_LINE_LOOP,
#endif
#ifdef GL_TRIANGLES
		Triangles = GL_TRIANGLES,
#endif
#ifdef GL_TRIANGLE_STRIP
		TriangleStrip = GL_TRIANGLE_STRIP,
#endif
#ifdef GL_TRIANGLE_FAN
		TriangleFan = GL_TRIANGLE_FAN,
#endif
#ifdef GL_LINES_ADJACENCY
		LinesAdjacency = GL_LINES_ADJACENCY,
#endif
#ifdef GL_LINE_STRIP_ADJACENCY
		LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
#endif
#ifdef GL_TRIANGLES_ADJACENCY
		TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
#endif
#ifdef GL_TRIANGLE_STRIP_ADJACENCY
		TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
#endif
#ifdef GL_PATCHES
		Patches = GL_PATCHES,
#endif
	};
}
#endif

