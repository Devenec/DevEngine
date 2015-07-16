/**
 * @file platform/opengl/OpenGL.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Copyright (c) 2013-2014 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and/or associated documentation files (the
 * "Materials"), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 */

#pragma once

#include <core/Types.h>
#include <platform/PlatformInternal.h>

#if DE_COMPILER == DE_COMPILER_MSVC
	#define DE_CALL_OPENGL DE_INTERNAL_CALL_STDCALL
#else
	#define DE_CALL_OPENGL
#endif

// Version 1.0

using GLbitfield = Uint32;
using GLboolean	 = Uint8;
using GLdouble	 = Float64;
using GLenum	 = Uint32;
using GLfloat	 = Float32;
using GLint		 = Int32;
using GLsizei	 = Int32;
using GLubyte	 = Uint8;
using GLuint	 = Uint32;

using GLBlendFunc = void (DE_CALL_OPENGL*)(GLenum sfactor, GLenum dfactor);
using GLClear = void (DE_CALL_OPENGL*)(GLbitfield mask);
using GLClearColor = void (DE_CALL_OPENGL*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
using GLClearDepth = void (DE_CALL_OPENGL*)(GLdouble depth);
using GLClearStencil = void (DE_CALL_OPENGL*)(GLint s);
using GLColorMask = void (DE_CALL_OPENGL*)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
using GLCullFace = void (DE_CALL_OPENGL*)(GLenum mode);
using GLDepthFunc = void (DE_CALL_OPENGL*)(GLenum func);
using GLDepthMask = void (DE_CALL_OPENGL*)(GLboolean flag);
using GLDepthRange = void (DE_CALL_OPENGL*)(GLdouble near, GLdouble far);
using GLDisable = void (DE_CALL_OPENGL*)(GLenum cap);
using GLDrawBuffer = void (DE_CALL_OPENGL*)(GLenum buf);
using GLEnable = void (DE_CALL_OPENGL*)(GLenum cap);
using GLFinish = void (DE_CALL_OPENGL*)();
using GLFlush = void (DE_CALL_OPENGL*)();
using GLFrontFace = void (DE_CALL_OPENGL*)(GLenum mode);
using GLGetBooleanV = void (DE_CALL_OPENGL*)(GLenum pname, GLboolean* data);
using GLGetDoubleV = void (DE_CALL_OPENGL*)(GLenum pname, GLdouble* data);
using GLGetError = GLenum (DE_CALL_OPENGL*)();
using GLGetFloatV = void (DE_CALL_OPENGL*)(GLenum pname, GLfloat* data);
using GLGetIntegerV = void (DE_CALL_OPENGL*)(GLenum pname, GLint* data);
using GLGetString = const GLubyte* (DE_CALL_OPENGL*)(GLenum name);
using GLGetTexImage = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum format, GLenum type, Void* pixels);
using GLGetTexLevelParameterFV = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum pname, GLfloat* params);
using GLGetTexLevelParameterIV = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum pname, GLint* params);
using GLGetTexParameterFV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLfloat* params);
using GLGetTexParameterIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint* params);
using GLHint = void (DE_CALL_OPENGL*)(GLenum target, GLenum mode);
using GLIsEnabled = GLboolean (DE_CALL_OPENGL*)(GLenum cap);
using GLLineWidth = void (DE_CALL_OPENGL*)(GLfloat width);
using GLLogicOp = void (DE_CALL_OPENGL*)(GLenum opcode);
using GLPixelStoreF = void (DE_CALL_OPENGL*)(GLenum pname, GLfloat param);
using GLPixelStoreI = void (DE_CALL_OPENGL*)(GLenum pname, GLint param);
using GLPointSize = void (DE_CALL_OPENGL*)(GLfloat size);
using GLPolygonMode = void (DE_CALL_OPENGL*)(GLenum face, GLenum mode);
using GLReadBuffer = void (DE_CALL_OPENGL*)(GLenum src);

using GLReadPixels = void (DE_CALL_OPENGL*)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format,
	GLenum type, Void* pixels);

using GLScissor = void (DE_CALL_OPENGL*)(GLint x, GLint y, GLsizei width, GLsizei height);
using GLStencilFunc = void (DE_CALL_OPENGL*)(GLenum func, GLint ref, GLuint mask);
using GLStencilMask = void (DE_CALL_OPENGL*)(GLuint mask);
using GLStencilOp = void (DE_CALL_OPENGL*)(GLenum fail, GLenum zfail, GLenum zpass);

using GLTexImage1D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint internalformat, GLsizei width,
	GLint border, GLenum format, GLenum type, const Void* pixels);

using GLTexImage2D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint internalformat, GLsizei width,
	GLsizei height, GLint border, GLenum format, GLenum type, const Void* pixels);

using GLTexParameterF = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLfloat param);
using GLTexParameterFV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, const GLfloat* params);
using GLTexParameterI = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint param);
using GLTexParameterIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, const GLint* params);
using GLViewport = void (DE_CALL_OPENGL*)(GLint x, GLint y, GLsizei width, GLsizei height);


// Version 1.1

#define GL_FALSE				   0
#define GL_TRUE					   1
#define GL_NONE					   0
#define GL_ZERO					   0
#define GL_ONE					   1
#define GL_POINTS				   0x0000
#define GL_LINES				   0x0001
#define GL_LINE_LOOP			   0x0002
#define GL_LINE_STRIP			   0x0003
#define GL_TRIANGLES			   0x0004
#define GL_TRIANGLE_STRIP		   0x0005
#define GL_TRIANGLE_FAN			   0x0006
#define GL_QUADS				   0x0007
#define GL_DEPTH_BUFFER_BIT		   0x0100
#define GL_STENCIL_BUFFER_BIT	   0x0400
#define GL_COLOR_BUFFER_BIT		   0x4000
#define GL_NEVER				   0x0200
#define GL_LESS					   0x0201
#define GL_EQUAL				   0x0202
#define GL_LEQUAL				   0x0203
#define GL_GREATER				   0x0204
#define GL_NOTEQUAL				   0x0205
#define GL_GEQUAL				   0x0206
#define GL_ALWAYS				   0x0207
#define GL_SRC_COLOR			   0x0300
#define GL_ONE_MINUS_SRC_COLOR	   0x0301
#define GL_SRC_ALPHA			   0x0302
#define GL_ONE_MINUS_SRC_ALPHA	   0x0303
#define GL_DST_ALPHA			   0x0304
#define GL_ONE_MINUS_DST_ALPHA	   0x0305
#define GL_DST_COLOR			   0x0306
#define GL_ONE_MINUS_DST_COLOR	   0x0307
#define GL_SRC_ALPHA_SATURATE	   0x0308
#define GL_FRONT_LEFT			   0x0400
#define GL_FRONT_RIGHT			   0x0401
#define GL_BACK_LEFT			   0x0402
#define GL_BACK_RIGHT			   0x0403
#define GL_FRONT				   0x0404
#define GL_BACK					   0x0405
#define GL_LEFT					   0x0406
#define GL_RIGHT				   0x0407
#define GL_FRONT_AND_BACK		   0x0408
#define GL_NO_ERROR				   0x0000
#define GL_INVALID_ENUM			   0x0500
#define GL_INVALID_VALUE		   0x0501
#define GL_INVALID_OPERATION	   0x0502
#define GL_STACK_OVERFLOW		   0x0503
#define GL_STACK_UNDERFLOW		   0x0504
#define GL_OUT_OF_MEMORY		   0x0505
#define GL_CW					   0x0900
#define GL_CCW					   0x0901
#define GL_POINT_SIZE			   0x0B11
#define GL_POINT_SIZE_RANGE		   0x0B12
#define GL_POINT_SIZE_GRANULARITY  0x0B13
#define GL_LINE_SMOOTH			   0x0B20
#define GL_LINE_WIDTH			   0x0B21
#define GL_LINE_WIDTH_RANGE		   0x0B22
#define GL_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_POLYGON_MODE			   0x0B40
#define GL_POLYGON_SMOOTH		   0x0B41
#define GL_CULL_FACE			   0x0B44
#define GL_CULL_FACE_MODE		   0x0B45
#define GL_FRONT_FACE			   0x0B46
#define GL_DEPTH_RANGE			   0x0B70
#define GL_DEPTH_TEST			   0x0B71
#define GL_DEPTH_WRITEMASK		   0x0B72
#define GL_DEPTH_CLEAR_VALUE	   0x0B73
#define GL_DEPTH_FUNC			   0x0B74
#define GL_STENCIL_TEST			   0x0B90
#define GL_STENCIL_CLEAR_VALUE	   0x0B91
#define GL_STENCIL_FUNC			   0x0B92
#define GL_STENCIL_VALUE_MASK	   0x0B93
#define GL_STENCIL_FAIL			   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#define GL_STENCIL_REF			   0x0B97
#define GL_STENCIL_WRITEMASK	   0x0B98
#define GL_VIEWPORT				   0x0BA2
#define GL_DITHER				   0x0BD0
#define GL_BLEND_DST			   0x0BE0
#define GL_BLEND_SRC			   0x0BE1
#define GL_BLEND				   0x0BE2
#define GL_LOGIC_OP_MODE		   0x0BF0
#define GL_COLOR_LOGIC_OP		   0x0BF2
#define GL_DRAW_BUFFER			   0x0C01
#define GL_READ_BUFFER			   0x0C02
#define GL_SCISSOR_BOX			   0x0C10
#define GL_SCISSOR_TEST			   0x0C11
#define GL_COLOR_CLEAR_VALUE	   0x0C22
#define GL_COLOR_WRITEMASK		   0x0C23
#define GL_DOUBLEBUFFER			   0x0C32
#define GL_STEREO				   0x0C33
#define GL_LINE_SMOOTH_HINT		   0x0C52
#define GL_POLYGON_SMOOTH_HINT	   0x0C53
#define GL_UNPACK_SWAP_BYTES	   0x0CF0
#define GL_UNPACK_LSB_FIRST		   0x0CF1
#define GL_UNPACK_ROW_LENGTH	   0x0CF2
#define GL_UNPACK_SKIP_ROWS		   0x0CF3
#define GL_UNPACK_SKIP_PIXELS	   0x0CF4
#define GL_UNPACK_ALIGNMENT		   0x0CF5
#define GL_PACK_SWAP_BYTES		   0x0D00
#define GL_PACK_LSB_FIRST		   0x0D01
#define GL_PACK_ROW_LENGTH		   0x0D02
#define GL_PACK_SKIP_ROWS		   0x0D03
#define GL_PACK_SKIP_PIXELS		   0x0D04
#define GL_PACK_ALIGNMENT		   0x0D05
#define GL_MAX_TEXTURE_SIZE		   0x0D33
#define GL_MAX_VIEWPORT_DIMS	   0x0D3A
#define GL_SUBPIXEL_BITS		   0x0D50
#define GL_TEXTURE_1D			   0x0DE0
#define GL_TEXTURE_2D			   0x0DE1
#define GL_TEXTURE_WIDTH		   0x1000
#define GL_TEXTURE_HEIGHT		   0x1001
#define GL_TEXTURE_INTERNAL_FORMAT 0x1003
#define GL_TEXTURE_BORDER_COLOR	   0x1004
#define GL_DONT_CARE			   0x1100
#define GL_FASTEST				   0x1101
#define GL_NICEST				   0x1102
#define GL_BYTE					   0x1400
#define GL_UNSIGNED_BYTE		   0x1401
#define GL_SHORT				   0x1402
#define GL_UNSIGNED_SHORT		   0x1403
#define GL_INT					   0x1404
#define GL_UNSIGNED_INT			   0x1405
#define GL_FLOAT				   0x1406
#define GL_DOUBLE				   0x140A
#define GL_CLEAR				   0x1500
#define GL_AND					   0x1501
#define GL_AND_REVERSE			   0x1502
#define GL_COPY					   0x1503
#define GL_AND_INVERTED			   0x1504
#define GL_NOOP					   0x1505
#define GL_XOR					   0x1506
#define GL_OR					   0x1507
#define GL_NOR					   0x1508
#define GL_EQUIV				   0x1509
#define GL_INVERT				   0x150A
#define GL_OR_REVERSE			   0x150B
#define GL_COPY_INVERTED		   0x150C
#define GL_OR_INVERTED			   0x150D
#define GL_NAND					   0x150E
#define GL_SET					   0x150F
#define GL_TEXTURE				   0x1702
#define GL_COLOR				   0x1800
#define GL_DEPTH				   0x1801
#define GL_STENCIL				   0x1802
#define GL_STENCIL_INDEX		   0x1901
#define GL_DEPTH_COMPONENT		   0x1902
#define GL_RED					   0x1903
#define GL_GREEN				   0x1904
#define GL_BLUE					   0x1905
#define GL_ALPHA				   0x1906
#define GL_RGB					   0x1907
#define GL_RGBA					   0x1908
#define GL_POINT				   0x1B00
#define GL_LINE					   0x1B01
#define GL_FILL					   0x1B02
#define GL_KEEP					   0x1E00
#define GL_REPLACE				   0x1E01
#define GL_INCR					   0x1E02
#define GL_DECR					   0x1E03
#define GL_VENDOR				   0x1F00
#define GL_RENDERER				   0x1F01
#define GL_VERSION				   0x1F02
#define GL_EXTENSIONS			   0x1F03
#define GL_NEAREST				   0x2600
#define GL_LINEAR				   0x2601
#define GL_NEAREST_MIPMAP_NEAREST  0x2700
#define GL_LINEAR_MIPMAP_NEAREST   0x2701
#define GL_NEAREST_MIPMAP_LINEAR   0x2702
#define GL_LINEAR_MIPMAP_LINEAR	   0x2703
#define GL_TEXTURE_MAG_FILTER	   0x2800
#define GL_TEXTURE_MIN_FILTER	   0x2801
#define GL_TEXTURE_WRAP_S		   0x2802
#define GL_TEXTURE_WRAP_T		   0x2803
#define GL_REPEAT				   0x2901
#define GL_POLYGON_OFFSET_UNITS	   0x2A00
#define GL_POLYGON_OFFSET_POINT	   0x2A01
#define GL_POLYGON_OFFSET_LINE	   0x2A02
#define GL_POLYGON_OFFSET_FILL	   0x8037
#define GL_POLYGON_OFFSET_FACTOR   0x8038
#define GL_R3_G3_B2				   0x2A10
#define GL_RGB4					   0x804F
#define GL_RGB5					   0x8050
#define GL_RGB8					   0x8051
#define GL_RGB10				   0x8052
#define GL_RGB12				   0x8053
#define GL_RGB16				   0x8054
#define GL_RGBA2				   0x8055
#define GL_RGBA4				   0x8056
#define GL_RGB5_A1				   0x8057
#define GL_RGBA8				   0x8058
#define GL_RGB10_A2				   0x8059
#define GL_RGBA12				   0x805A
#define GL_RGBA16				   0x805B
#define GL_TEXTURE_RED_SIZE		   0x805C
#define GL_TEXTURE_GREEN_SIZE	   0x805D
#define GL_TEXTURE_BLUE_SIZE	   0x805E
#define GL_TEXTURE_ALPHA_SIZE	   0x805F
#define GL_PROXY_TEXTURE_1D		   0x8063
#define GL_PROXY_TEXTURE_2D		   0x8064
#define GL_TEXTURE_BINDING_1D	   0x8068
#define GL_TEXTURE_BINDING_2D	   0x8069
#define GL_VERTEX_ARRAY			   0x8074

using GLBindTexture = void (DE_CALL_OPENGL*)(GLenum target, GLuint texture);

using GLCopyTexImage1D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
	GLsizei width, GLint border);

using GLCopyTexImage2D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
	GLsizei width, GLsizei height, GLint border);

using GLCopyTexSubImage1D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y,
	GLsizei width);

using GLCopyTexSubImage2D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x,
	GLint y, GLsizei width, GLsizei height);

using GLDeleteTextures = void (DE_CALL_OPENGL*)(GLsizei n, const GLuint* textures);
using GLDrawArrays = void (DE_CALL_OPENGL*)(GLenum mode, GLint first, GLsizei count);
using GLDrawElements = void (DE_CALL_OPENGL*)(GLenum mode, GLsizei count, GLenum type, const Void* indices);
using GLGenTextures = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* textures);
using GLGetPointerV = void (DE_CALL_OPENGL*)(GLenum pname, Void** params);
using GLIsTexture = GLboolean (DE_CALL_OPENGL*)(GLuint texture);
using GLPolygonOffset = void (DE_CALL_OPENGL*)(GLfloat factor, GLfloat units);

using GLTexSubImage1D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLsizei width,
	GLenum format, GLenum type, const Void* pixels);

using GLTexSubImage2D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
	GLsizei height, GLenum format, GLenum type, const Void* pixels);


// Version 1.2

#define GL_SMOOTH_POINT_SIZE_RANGE		 0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY 0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE		 0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY 0x0B23
#define GL_UNSIGNED_BYTE_3_3_2			 0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4		 0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1		 0x8034
#define GL_UNSIGNED_INT_8_8_8_8			 0x8035
#define GL_UNSIGNED_INT_10_10_10_2		 0x8036
#define GL_TEXTURE_BINDING_3D			 0x806A
#define GL_PACK_SKIP_IMAGES				 0x806B
#define GL_PACK_IMAGE_HEIGHT			 0x806C
#define GL_UNPACK_SKIP_IMAGES			 0x806D
#define GL_UNPACK_IMAGE_HEIGHT			 0x806E
#define GL_TEXTURE_3D					 0x806F
#define GL_PROXY_TEXTURE_3D				 0x8070
#define GL_TEXTURE_DEPTH				 0x8071
#define GL_TEXTURE_WRAP_R				 0x8072
#define GL_MAX_3D_TEXTURE_SIZE			 0x8073
#define GL_BGR							 0x80E0
#define GL_BGRA							 0x80E1
#define GL_MAX_ELEMENTS_VERTICES		 0x80E8
#define GL_MAX_ELEMENTS_INDICES			 0x80E9
#define GL_CLAMP_TO_EDGE				 0x812F
#define GL_TEXTURE_MIN_LOD				 0x813A
#define GL_TEXTURE_MAX_LOD				 0x813B
#define GL_TEXTURE_BASE_LEVEL			 0x813C
#define GL_TEXTURE_MAX_LEVEL			 0x813D
#define GL_UNSIGNED_BYTE_2_3_3_REV		 0x8362
#define GL_UNSIGNED_SHORT_5_6_5			 0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV		 0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV	 0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV	 0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV		 0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV	 0x8368
#define GL_ALIASED_LINE_WIDTH_RANGE		 0x846E

using GLCopyTexSubImage3D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset,
	GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

using GLDrawRangeElements = void (DE_CALL_OPENGL*)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type,
	const Void* indices);

using GLTexImage3D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint internalformat, GLsizei width,
	GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const Void* pixels);

using GLTexSubImage3D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
	GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const Void* pixels);


// Version 1.3

#define GL_MULTISAMPLE					  0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE		  0x809E
#define GL_SAMPLE_ALPHA_TO_ONE			  0x809F
#define GL_SAMPLE_COVERAGE				  0x80A0
#define GL_SAMPLE_BUFFERS				  0x80A8
#define GL_SAMPLES						  0x80A9
#define GL_SAMPLE_COVERAGE_VALUE		  0x80AA
#define GL_SAMPLE_COVERAGE_INVERT		  0x80AB
#define GL_CLAMP_TO_BORDER				  0x812D
#define GL_TEXTURE0						  0x84C0
#define GL_TEXTURE1						  0x84C1
#define GL_TEXTURE2						  0x84C2
#define GL_TEXTURE3						  0x84C3
#define GL_TEXTURE4						  0x84C4
#define GL_TEXTURE5						  0x84C5
#define GL_TEXTURE6						  0x84C6
#define GL_TEXTURE7						  0x84C7
#define GL_TEXTURE8						  0x84C8
#define GL_TEXTURE9						  0x84C9
#define GL_TEXTURE10					  0x84CA
#define GL_TEXTURE11					  0x84CB
#define GL_TEXTURE12					  0x84CC
#define GL_TEXTURE13					  0x84CD
#define GL_TEXTURE14					  0x84CE
#define GL_TEXTURE15					  0x84CF
#define GL_TEXTURE16					  0x84D0
#define GL_TEXTURE17					  0x84D1
#define GL_TEXTURE18					  0x84D2
#define GL_TEXTURE19					  0x84D3
#define GL_TEXTURE20					  0x84D4
#define GL_TEXTURE21					  0x84D5
#define GL_TEXTURE22					  0x84D6
#define GL_TEXTURE23					  0x84D7
#define GL_TEXTURE24					  0x84D8
#define GL_TEXTURE25					  0x84D9
#define GL_TEXTURE26					  0x84DA
#define GL_TEXTURE27					  0x84DB
#define GL_TEXTURE28					  0x84DC
#define GL_TEXTURE29					  0x84DD
#define GL_TEXTURE30					  0x84DE
#define GL_TEXTURE31					  0x84DF
#define GL_ACTIVE_TEXTURE				  0x84E0
#define GL_COMPRESSED_RGB				  0x84ED
#define GL_COMPRESSED_RGBA				  0x84EE
#define GL_TEXTURE_COMPRESSION_HINT		  0x84EF
#define GL_TEXTURE_CUBE_MAP				  0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP		  0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X	  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X	  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y	  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z	  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	  0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP		  0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE	  0x851C
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED			  0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS	  0x86A3

using GLActiveTexture = void (DE_CALL_OPENGL*)(GLenum texture);

using GLCompressedTexImage1D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum internalformat, GLsizei width,
	GLint border, GLsizei imageSize, const Void* data);

using GLCompressedTexImage2D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum internalformat, GLsizei width,
	GLsizei height, GLint border, GLsizei imageSize, const Void* data);

using GLCompressedTexImage3D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum internalformat, GLsizei width,
	GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const Void* data);

using GLCompressedTexSubImage1D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLsizei width,
	GLenum format, GLsizei imageSize, const Void* data);

using GLCompressedTexSubImage2D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const Void* data);

using GLCompressedTexSubImage3D = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLint xoffset, GLint yoffset,
	GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const Void* data);

using GLGetCompressedTexImage = void (DE_CALL_OPENGL*)(GLenum target, GLint level, Void* img);
using GLSampleCoverage = void (DE_CALL_OPENGL*)(GLfloat value, GLboolean invert);


// Version 1.4

#define GL_CONSTANT_COLOR			 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR	 0x8002
#define GL_CONSTANT_ALPHA			 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA	 0x8004
#define GL_FUNC_ADD					 0x8006
#define GL_MIN						 0x8007
#define GL_MAX						 0x8008
#define GL_FUNC_SUBTRACT			 0x800A
#define GL_FUNC_REVERSE_SUBTRACT	 0x800B
#define GL_BLEND_DST_RGB			 0x80C8
#define GL_BLEND_SRC_RGB			 0x80C9
#define GL_BLEND_DST_ALPHA			 0x80CA
#define GL_BLEND_SRC_ALPHA			 0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE 0x8128
#define GL_DEPTH_COMPONENT16		 0x81A5
#define GL_DEPTH_COMPONENT24		 0x81A6
#define GL_DEPTH_COMPONENT32		 0x81A7
#define GL_MIRRORED_REPEAT			 0x8370
#define GL_MAX_TEXTURE_LOD_BIAS		 0x84FD
#define GL_TEXTURE_LOD_BIAS			 0x8501
#define GL_INCR_WRAP				 0x8507
#define GL_DECR_WRAP				 0x8508
#define GL_TEXTURE_DEPTH_SIZE		 0x884A
#define GL_TEXTURE_COMPARE_MODE		 0x884C
#define GL_TEXTURE_COMPARE_FUNC		 0x884D

using GLBlendColor = void (DE_CALL_OPENGL*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
using GLBlendEquation = void (DE_CALL_OPENGL*)(GLenum mode);

using GLBlendFuncSeparate = void (DE_CALL_OPENGL*)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha,
	GLenum dfactorAlpha);

using GLMultiDrawArrays = void (DE_CALL_OPENGL*)(GLenum mode, const GLint* first, const GLsizei* count,
	GLsizei drawcount);

using GLMultiDrawElements = void (DE_CALL_OPENGL*)(GLenum mode, const GLsizei* count, GLenum type,
	const Void* const* indices, GLsizei drawcount);

using GLPointParameterF = void (DE_CALL_OPENGL*)(GLenum pname, GLfloat param);
using GLPointParameterFV = void (DE_CALL_OPENGL*)(GLenum pname, const GLfloat* params);
using GLPointParameterI = void (DE_CALL_OPENGL*)(GLenum pname, GLint param);
using GLPointParameterIV = void (DE_CALL_OPENGL*)(GLenum pname, const GLint* params);


// Version 1.5

using GLintptr	 = Int32;
using GLsizeiptr = Int32;

#define GL_SRC1_ALPHA						  0x8589
#define GL_BUFFER_SIZE						  0x8764
#define GL_BUFFER_USAGE						  0x8765
#define GL_QUERY_COUNTER_BITS				  0x8864
#define GL_CURRENT_QUERY					  0x8865
#define GL_QUERY_RESULT						  0x8866
#define GL_QUERY_RESULT_AVAILABLE			  0x8867
#define GL_ARRAY_BUFFER						  0x8892
#define GL_ELEMENT_ARRAY_BUFFER				  0x8893
#define GL_ARRAY_BUFFER_BINDING				  0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING		  0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_READ_ONLY						  0x88B8
#define GL_WRITE_ONLY						  0x88B9
#define GL_READ_WRITE						  0x88BA
#define GL_BUFFER_ACCESS					  0x88BB
#define GL_BUFFER_MAPPED					  0x88BC
#define GL_BUFFER_MAP_POINTER				  0x88BD
#define GL_STREAM_DRAW						  0x88E0
#define GL_STREAM_READ						  0x88E1
#define GL_STREAM_COPY						  0x88E2
#define GL_STATIC_DRAW						  0x88E4
#define GL_STATIC_READ						  0x88E5
#define GL_STATIC_COPY						  0x88E6
#define GL_DYNAMIC_DRAW						  0x88E8
#define GL_DYNAMIC_READ						  0x88E9
#define GL_DYNAMIC_COPY						  0x88EA
#define GL_SAMPLES_PASSED					  0x8914

using GLBeginQuery = void (DE_CALL_OPENGL*)(GLenum target, GLuint id);
using GLBindBuffer = void (DE_CALL_OPENGL*)(GLenum target, GLuint buffer);
using GLBufferData = void (DE_CALL_OPENGL*)(GLenum target, GLsizeiptr size, const Void* data, GLenum usage);
using GLBufferSubData = void (DE_CALL_OPENGL*)(GLenum target, GLintptr offset, GLsizeiptr size, const Void* data);
using GLDeleteBuffers = void (DE_CALL_OPENGL*)(GLsizei n, const GLuint* buffers);
using GLDeleteQueries = void (DE_CALL_OPENGL*)(GLsizei n, const GLuint* ids);
using GLEndQuery = void (DE_CALL_OPENGL*)(GLenum target);
using GLGenBuffers = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* buffers);
using GLGenQueries = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* ids);
using GLGetBufferParameterIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint* params);
using GLGetBufferPointerV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, Void** params);
using GLGetBufferSubData = void (DE_CALL_OPENGL*)(GLenum target, GLintptr offset, GLsizeiptr size, Void* data);
using GLGetQueryIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint* params);
using GLGetQueryObjectIV = void (DE_CALL_OPENGL*)(GLuint id, GLenum pname, GLint* params);
using GLGetQueryObjectUIV = void (DE_CALL_OPENGL*)(GLuint id, GLenum pname, GLuint* params);
using GLIsBuffer = GLboolean (DE_CALL_OPENGL*)(GLuint buffer);
using GLIsQuery = GLboolean (DE_CALL_OPENGL*)(GLuint id);
using GLMapBuffer = Void* (DE_CALL_OPENGL*)(GLenum target, GLenum access);
using GLUnmapBuffer = GLboolean (DE_CALL_OPENGL*)(GLenum target);


// Version 2.0

using GLbyte   = Int8;
using GLchar   = Char8;
using GLshort  = Int16;
using GLushort = Uint16;

#define GL_BLEND_EQUATION_RGB				0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED		0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE			0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE		0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE			0x8625
#define GL_CURRENT_VERTEX_ATTRIB			0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE		0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER		0x8645
#define GL_STENCIL_BACK_FUNC				0x8800
#define GL_STENCIL_BACK_FAIL				0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL		0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS		0x8803
#define GL_MAX_DRAW_BUFFERS					0x8824
#define GL_DRAW_BUFFER0						0x8825
#define GL_DRAW_BUFFER1						0x8826
#define GL_DRAW_BUFFER2						0x8827
#define GL_DRAW_BUFFER3						0x8828
#define GL_DRAW_BUFFER4						0x8829
#define GL_DRAW_BUFFER5						0x882A
#define GL_DRAW_BUFFER6						0x882B
#define GL_DRAW_BUFFER7						0x882C
#define GL_DRAW_BUFFER8						0x882D
#define GL_DRAW_BUFFER9						0x882E
#define GL_DRAW_BUFFER10					0x882F
#define GL_DRAW_BUFFER11					0x8830
#define GL_DRAW_BUFFER12					0x8831
#define GL_DRAW_BUFFER13					0x8832
#define GL_DRAW_BUFFER14					0x8833
#define GL_DRAW_BUFFER15					0x8834
#define GL_BLEND_EQUATION_ALPHA				0x883D
#define GL_MAX_VERTEX_ATTRIBS				0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED	0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS			0x8872
#define GL_FRAGMENT_SHADER					0x8B30
#define GL_VERTEX_SHADER					0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS	0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS	0x8B4A
#define GL_MAX_VARYING_FLOATS				0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS	0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE						0x8B4F
#define GL_FLOAT_VEC2						0x8B50
#define GL_FLOAT_VEC3						0x8B51
#define GL_FLOAT_VEC4						0x8B52
#define GL_INT_VEC2							0x8B53
#define GL_INT_VEC3							0x8B54
#define GL_INT_VEC4							0x8B55
#define GL_BOOL								0x8B56
#define GL_BOOL_VEC2						0x8B57
#define GL_BOOL_VEC3						0x8B58
#define GL_BOOL_VEC4						0x8B59
#define GL_FLOAT_MAT2						0x8B5A
#define GL_FLOAT_MAT3						0x8B5B
#define GL_FLOAT_MAT4						0x8B5C
#define GL_SAMPLER_1D						0x8B5D
#define GL_SAMPLER_2D						0x8B5E
#define GL_SAMPLER_3D						0x8B5F
#define GL_SAMPLER_CUBE						0x8B60
#define GL_SAMPLER_1D_SHADOW				0x8B61
#define GL_SAMPLER_2D_SHADOW				0x8B62
#define GL_DELETE_STATUS					0x8B80
#define GL_COMPILE_STATUS					0x8B81
#define GL_LINK_STATUS						0x8B82
#define GL_VALIDATE_STATUS					0x8B83
#define GL_INFO_LOG_LENGTH					0x8B84
#define GL_ATTACHED_SHADERS					0x8B85
#define GL_ACTIVE_UNIFORMS					0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH		0x8B87
#define GL_SHADER_SOURCE_LENGTH				0x8B88
#define GL_ACTIVE_ATTRIBUTES				0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH		0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT	0x8B8B
#define GL_SHADING_LANGUAGE_VERSION			0x8B8C
#define GL_CURRENT_PROGRAM					0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN		0x8CA0
#define GL_LOWER_LEFT						0x8CA1
#define GL_UPPER_LEFT						0x8CA2
#define GL_STENCIL_BACK_REF					0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK			0x8CA4
#define GL_STENCIL_BACK_WRITEMASK			0x8CA5

using GLAttachShader = void (DE_CALL_OPENGL*)(GLuint program, GLuint shader);
using GLBindAttribLocation = void (DE_CALL_OPENGL*)(GLuint program, GLuint index, const GLchar* name);
using GLBlendEquationSeparate = void (DE_CALL_OPENGL*)(GLenum modeRGB, GLenum modeAlpha);
using GLCompileShader = void (DE_CALL_OPENGL*)(GLuint shader);
using GLCreateProgram = GLuint (DE_CALL_OPENGL*)();
using GLCreateShader = GLuint (DE_CALL_OPENGL*)(GLenum type);
using GLDeleteProgram = void (DE_CALL_OPENGL*)(GLuint program);
using GLDeleteShader = void (DE_CALL_OPENGL*)(GLuint shader);
using GLDetachShader = void (DE_CALL_OPENGL*)(GLuint program, GLuint shader);
using GLDisableVertexAttribArray = void (DE_CALL_OPENGL*)(GLuint index);
using GLDrawBuffers = void (DE_CALL_OPENGL*)(GLsizei n, const GLenum* bufs);
using GLEnableVertexAttribArray = void (DE_CALL_OPENGL*)(GLuint index);

using GLGetActiveAttrib = void (DE_CALL_OPENGL*)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length,
	GLint* size, GLenum* type, GLchar* name);

using GLGetActiveUniform = void (DE_CALL_OPENGL*)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length,
	GLint* size, GLenum* type, GLchar* name);

using GLGetAttachedShaders = void (DE_CALL_OPENGL*)(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
using GLGetAttribLocation = GLint (DE_CALL_OPENGL*)(GLuint program, const GLchar* name);
using GLGetProgramInfoLog = void (DE_CALL_OPENGL*)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
using GLGetProgramIV = void (DE_CALL_OPENGL*)(GLuint program, GLenum pname, GLint* params);
using GLGetShaderInfoLog = void (DE_CALL_OPENGL*)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
using GLGetShaderIV = void (DE_CALL_OPENGL*)(GLuint shader, GLenum pname, GLint* params);
using GLGetShaderSource = void (DE_CALL_OPENGL*)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);
using GLGetUniformFV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLfloat* params);
using GLGetUniformIV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLint* params);
using GLGetUniformLocation = GLint (DE_CALL_OPENGL*)(GLuint program, const GLchar* name);
using GLGetVertexAttribDV = void (DE_CALL_OPENGL*)(GLuint index, GLenum pname, GLdouble* params);
using GLGetVertexAttribFV = void (DE_CALL_OPENGL*)(GLuint index, GLenum pname, GLfloat* params);
using GLGetVertexAttribIV = void (DE_CALL_OPENGL*)(GLuint index, GLenum pname, GLint* params);
using GLGetVertexAttribPointerV = void (DE_CALL_OPENGL*)(GLuint index, GLenum pname, Void** pointer);
using GLIsProgram = GLboolean (DE_CALL_OPENGL*)(GLuint program);
using GLIsShader = GLboolean (DE_CALL_OPENGL*)(GLuint shader);
using GLLinkProgram = void (DE_CALL_OPENGL*)(GLuint program);

using GLShaderSource = void (DE_CALL_OPENGL*)(GLuint shader, GLsizei count, const GLchar* const* string,
	const GLint* length);

using GLStencilFuncSeparate = void (DE_CALL_OPENGL*)(GLenum face, GLenum func, GLint ref, GLuint mask);
using GLStencilMaskSeparate = void (DE_CALL_OPENGL*)(GLenum face, GLuint mask);
using GLStencilOpSeparate = void (DE_CALL_OPENGL*)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
using GLUniform1F = void (DE_CALL_OPENGL*)(GLint location, GLfloat v0);
using GLUniform1FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLfloat* value);
using GLUniform1I = void (DE_CALL_OPENGL*)(GLint location, GLint v0);
using GLUniform1IV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLint* value);
using GLUniform2F = void (DE_CALL_OPENGL*)(GLint location, GLfloat v0, GLfloat v1);
using GLUniform2FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLfloat* value);
using GLUniform2I = void (DE_CALL_OPENGL*)(GLint location, GLint v0, GLint v1);
using GLUniform2IV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLint* value);
using GLUniform3F = void (DE_CALL_OPENGL*)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
using GLUniform3FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLfloat* value);
using GLUniform3I = void (DE_CALL_OPENGL*)(GLint location, GLint v0, GLint v1, GLint v2);
using GLUniform3IV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLint* value);
using GLUniform4F = void (DE_CALL_OPENGL*)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
using GLUniform4FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLfloat* value);
using GLUniform4I = void (DE_CALL_OPENGL*)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
using GLUniform4IV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLint* value);

using GLUniformMatrix2FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);

using GLUniformMatrix3FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);

using GLUniformMatrix4FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);

using GLUseProgram = void (DE_CALL_OPENGL*)(GLuint program);
using GLValidateProgram = void (DE_CALL_OPENGL*)(GLuint program);
using GLVertexAttrib1D = void (DE_CALL_OPENGL*)(GLuint index, GLdouble x);
using GLVertexAttrib1DV = void (DE_CALL_OPENGL*)(GLuint index, const GLdouble* v);
using GLVertexAttrib1F = void (DE_CALL_OPENGL*)(GLuint index, GLfloat x);
using GLVertexAttrib1FV = void (DE_CALL_OPENGL*)(GLuint index, const GLfloat* v);
using GLVertexAttrib1S = void (DE_CALL_OPENGL*)(GLuint index, GLshort x);
using GLVertexAttrib1SV = void (DE_CALL_OPENGL*)(GLuint index, const GLshort* v);
using GLVertexAttrib2D = void (DE_CALL_OPENGL*)(GLuint index, GLdouble x, GLdouble y);
using GLVertexAttrib2DV = void (DE_CALL_OPENGL*)(GLuint index, const GLdouble* v);
using GLVertexAttrib2F = void (DE_CALL_OPENGL*)(GLuint index, GLfloat x, GLfloat y);
using GLVertexAttrib2FV = void (DE_CALL_OPENGL*)(GLuint index, const GLfloat* v);
using GLVertexAttrib2S = void (DE_CALL_OPENGL*)(GLuint index, GLshort x, GLshort y);
using GLVertexAttrib2SV = void (DE_CALL_OPENGL*)(GLuint index, const GLshort* v);
using GLVertexAttrib3D = void (DE_CALL_OPENGL*)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
using GLVertexAttrib3DV = void (DE_CALL_OPENGL*)(GLuint index, const GLdouble* v);
using GLVertexAttrib3F = void (DE_CALL_OPENGL*)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
using GLVertexAttrib3FV = void (DE_CALL_OPENGL*)(GLuint index, const GLfloat* v);
using GLVertexAttrib3S = void (DE_CALL_OPENGL*)(GLuint index, GLshort x, GLshort y, GLshort z);
using GLVertexAttrib3SV = void (DE_CALL_OPENGL*)(GLuint index, const GLshort* v);
using GLVertexAttrib4BV = void (DE_CALL_OPENGL*)(GLuint index, const GLbyte* v);
using GLVertexAttrib4D = void (DE_CALL_OPENGL*)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
using GLVertexAttrib4DV = void (DE_CALL_OPENGL*)(GLuint index, const GLdouble* v);
using GLVertexAttrib4F = void (DE_CALL_OPENGL*)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
using GLVertexAttrib4FV = void (DE_CALL_OPENGL*)(GLuint index, const GLfloat* v);
using GLVertexAttrib4IV = void (DE_CALL_OPENGL*)(GLuint index, const GLint* v);
using GLVertexAttrib4NBV = void (DE_CALL_OPENGL*)(GLuint index, const GLbyte* v);
using GLVertexAttrib4NIV = void (DE_CALL_OPENGL*)(GLuint index, const GLint* v);
using GLVertexAttrib4NSV = void (DE_CALL_OPENGL*)(GLuint index, const GLshort* v);
using GLVertexAttrib4NUB = void (DE_CALL_OPENGL*)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
using GLVertexAttrib4NUBV = void (DE_CALL_OPENGL*)(GLuint index, const GLubyte* v);
using GLVertexAttrib4NUIV = void (DE_CALL_OPENGL*)(GLuint index, const GLuint* v);
using GLVertexAttrib4NUSV = void (DE_CALL_OPENGL*)(GLuint index, const GLushort* v);
using GLVertexAttrib4S = void (DE_CALL_OPENGL*)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
using GLVertexAttrib4SV = void (DE_CALL_OPENGL*)(GLuint index, const GLshort* v);
using GLVertexAttrib4UBV = void (DE_CALL_OPENGL*)(GLuint index, const GLubyte* v);
using GLVertexAttrib4UIV = void (DE_CALL_OPENGL*)(GLuint index, const GLuint* v);
using GLVertexAttrib4USV = void (DE_CALL_OPENGL*)(GLuint index, const GLushort* v);

using GLVertexAttribPointer = void (DE_CALL_OPENGL*)(GLuint index, GLint size, GLenum type, GLboolean normalized,
	GLsizei stride, const Void* pointer);


// Version 2.1

#define GL_PIXEL_PACK_BUFFER		   0x88EB
#define GL_PIXEL_UNPACK_BUFFER		   0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING   0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING 0x88EF
#define GL_FLOAT_MAT2x3				   0x8B65
#define GL_FLOAT_MAT2x4				   0x8B66
#define GL_FLOAT_MAT3x2				   0x8B67
#define GL_FLOAT_MAT3x4				   0x8B68
#define GL_FLOAT_MAT4x2				   0x8B69
#define GL_FLOAT_MAT4x3				   0x8B6A
#define GL_SRGB						   0x8C40
#define GL_SRGB8					   0x8C41
#define GL_SRGB_ALPHA				   0x8C42
#define GL_SRGB8_ALPHA8				   0x8C43
#define GL_COMPRESSED_SRGB			   0x8C48
#define GL_COMPRESSED_SRGB_ALPHA	   0x8C49

using GLUniformMatrix2X3FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);

using GLUniformMatrix2X4FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);

using GLUniformMatrix3X2FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);

using GLUniformMatrix3X4FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);

using GLUniformMatrix4X2FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);

using GLUniformMatrix4X3FV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLfloat* value);


// Version 3.0

using GLhalf = Uint16;

#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT			 0x0001
#define GL_MAP_READ_BIT									 0x0001
#define GL_MAP_WRITE_BIT								 0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT						 0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT					 0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT						 0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT						 0x0020
#define GL_INVALID_FRAMEBUFFER_OPERATION				 0x0506
#define GL_MAX_CLIP_DISTANCES							 0x0D32
#define GL_HALF_FLOAT									 0x140B
#define GL_CLIP_DISTANCE0								 0x3000
#define GL_CLIP_DISTANCE1								 0x3001
#define GL_CLIP_DISTANCE2								 0x3002
#define GL_CLIP_DISTANCE3								 0x3003
#define GL_CLIP_DISTANCE4								 0x3004
#define GL_CLIP_DISTANCE5								 0x3005
#define GL_CLIP_DISTANCE6								 0x3006
#define GL_CLIP_DISTANCE7								 0x3007
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING		 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE		 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE				 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE			 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE				 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE			 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE			 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE			 0x8217
#define GL_FRAMEBUFFER_DEFAULT							 0x8218
#define GL_FRAMEBUFFER_UNDEFINED						 0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT						 0x821A
#define GL_MAJOR_VERSION								 0x821B
#define GL_MINOR_VERSION								 0x821C
#define GL_NUM_EXTENSIONS								 0x821D
#define GL_CONTEXT_FLAGS								 0x821E
#define GL_COMPRESSED_RED								 0x8225
#define GL_COMPRESSED_RG								 0x8226
#define GL_RG											 0x8227
#define GL_RG_INTEGER									 0x8228
#define GL_R8											 0x8229
#define GL_R16											 0x822A
#define GL_RG8											 0x822B
#define GL_RG16											 0x822C
#define GL_R16F											 0x822D
#define GL_R32F											 0x822E
#define GL_RG16F										 0x822F
#define GL_RG32F										 0x8230
#define GL_R8I											 0x8231
#define GL_R8UI											 0x8232
#define GL_R16I											 0x8233
#define GL_R16UI										 0x8234
#define GL_R32I											 0x8235
#define GL_R32UI										 0x8236
#define GL_RG8I											 0x8237
#define GL_RG8UI										 0x8238
#define GL_RG16I										 0x8239
#define GL_RG16UI										 0x823A
#define GL_RG32I										 0x823B
#define GL_RG32UI										 0x823C
#define GL_MAX_RENDERBUFFER_SIZE						 0x84E8
#define GL_DEPTH_STENCIL								 0x84F9
#define GL_UNSIGNED_INT_24_8							 0x84FA
#define GL_VERTEX_ARRAY_BINDING							 0x85B5
#define GL_RGBA32F										 0x8814
#define GL_RGB32F										 0x8815
#define GL_RGBA16F										 0x881A
#define GL_RGB16F										 0x881B
#define GL_COMPARE_REF_TO_TEXTURE						 0x884E
#define GL_DEPTH24_STENCIL8								 0x88F0
#define GL_TEXTURE_STENCIL_SIZE							 0x88F1
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER					 0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS						 0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET						 0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET						 0x8905
#define GL_CLAMP_READ_COLOR								 0x891C
#define GL_FIXED_ONLY									 0x891D
#define GL_MAX_VARYING_COMPONENTS						 0x8B4B
#define GL_TEXTURE_RED_TYPE								 0x8C10
#define GL_TEXTURE_GREEN_TYPE							 0x8C11
#define GL_TEXTURE_BLUE_TYPE							 0x8C12
#define GL_TEXTURE_ALPHA_TYPE							 0x8C13
#define GL_TEXTURE_DEPTH_TYPE							 0x8C16
#define GL_UNSIGNED_NORMALIZED							 0x8C17
#define GL_TEXTURE_1D_ARRAY								 0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY						 0x8C19
#define GL_TEXTURE_2D_ARRAY								 0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY						 0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY						 0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY						 0x8C1D
#define GL_R11F_G11F_B10F								 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV					 0x8C3B
#define GL_RGB9_E5										 0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV						 0x8C3E
#define GL_TEXTURE_SHARED_SIZE							 0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH		 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE				 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS	 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS					 0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START				 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE				 0x8C85
#define GL_PRIMITIVES_GENERATED							 0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN		 0x8C88
#define GL_RASTERIZER_DISCARD							 0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS		 0x8C8B
#define GL_INTERLEAVED_ATTRIBS							 0x8C8C
#define GL_SEPARATE_ATTRIBS								 0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER					 0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING			 0x8C8F
#define GL_DRAW_FRAMEBUFFER_BINDING						 0x8CA6
#define GL_FRAMEBUFFER_BINDING							 0x8CA6
#define GL_RENDERBUFFER_BINDING							 0x8CA7
#define GL_READ_FRAMEBUFFER								 0x8CA8
#define GL_DRAW_FRAMEBUFFER								 0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING						 0x8CAA
#define GL_RENDERBUFFER_SAMPLES							 0x8CAB
#define GL_DEPTH_COMPONENT32F							 0x8CAC
#define GL_DEPTH32F_STENCIL8							 0x8CAD
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE			 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME			 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL			 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE	 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER			 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE							 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT			 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT	 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER			 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER			 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED						 0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS						 0x8CDF
#define GL_COLOR_ATTACHMENT0							 0x8CE0
#define GL_COLOR_ATTACHMENT1							 0x8CE1
#define GL_COLOR_ATTACHMENT2							 0x8CE2
#define GL_COLOR_ATTACHMENT3							 0x8CE3
#define GL_COLOR_ATTACHMENT4							 0x8CE4
#define GL_COLOR_ATTACHMENT5							 0x8CE5
#define GL_COLOR_ATTACHMENT6							 0x8CE6
#define GL_COLOR_ATTACHMENT7							 0x8CE7
#define GL_COLOR_ATTACHMENT8							 0x8CE8
#define GL_COLOR_ATTACHMENT9							 0x8CE9
#define GL_COLOR_ATTACHMENT10							 0x8CEA
#define GL_COLOR_ATTACHMENT11							 0x8CEB
#define GL_COLOR_ATTACHMENT12							 0x8CEC
#define GL_COLOR_ATTACHMENT13							 0x8CED
#define GL_COLOR_ATTACHMENT14							 0x8CEE
#define GL_COLOR_ATTACHMENT15							 0x8CEF
#define GL_COLOR_ATTACHMENT16							 0x8CF0
#define GL_COLOR_ATTACHMENT17							 0x8CF1
#define GL_COLOR_ATTACHMENT18							 0x8CF2
#define GL_COLOR_ATTACHMENT19							 0x8CF3
#define GL_COLOR_ATTACHMENT20							 0x8CF4
#define GL_COLOR_ATTACHMENT21							 0x8CF5
#define GL_COLOR_ATTACHMENT22							 0x8CF6
#define GL_COLOR_ATTACHMENT23							 0x8CF7
#define GL_COLOR_ATTACHMENT24							 0x8CF8
#define GL_COLOR_ATTACHMENT25							 0x8CF9
#define GL_COLOR_ATTACHMENT26							 0x8CFA
#define GL_COLOR_ATTACHMENT27							 0x8CFB
#define GL_COLOR_ATTACHMENT28							 0x8CFC
#define GL_COLOR_ATTACHMENT29							 0x8CFD
#define GL_COLOR_ATTACHMENT30							 0x8CFE
#define GL_COLOR_ATTACHMENT31							 0x8CFF
#define GL_DEPTH_ATTACHMENT								 0x8D00
#define GL_STENCIL_ATTACHMENT							 0x8D20
#define GL_FRAMEBUFFER									 0x8D40
#define GL_RENDERBUFFER									 0x8D41
#define GL_RENDERBUFFER_WIDTH							 0x8D42
#define GL_RENDERBUFFER_HEIGHT							 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT					 0x8D44
#define GL_STENCIL_INDEX1								 0x8D46
#define GL_STENCIL_INDEX4								 0x8D47
#define GL_STENCIL_INDEX8								 0x8D48
#define GL_STENCIL_INDEX16								 0x8D49
#define GL_RENDERBUFFER_RED_SIZE						 0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE						 0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE						 0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE						 0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE						 0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE					 0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE			 0x8D56
#define GL_MAX_SAMPLES									 0x8D57
#define GL_RGBA32UI										 0x8D70
#define GL_RGB32UI										 0x8D71
#define GL_RGBA16UI										 0x8D76
#define GL_RGB16UI										 0x8D77
#define GL_RGBA8UI										 0x8D7C
#define GL_RGB8UI										 0x8D7D
#define GL_RGBA32I										 0x8D82
#define GL_RGB32I										 0x8D83
#define GL_RGBA16I										 0x8D88
#define GL_RGB16I										 0x8D89
#define GL_RGBA8I										 0x8D8E
#define GL_RGB8I										 0x8D8F
#define GL_RED_INTEGER									 0x8D94
#define GL_GREEN_INTEGER								 0x8D95
#define GL_BLUE_INTEGER									 0x8D96
#define GL_RGB_INTEGER									 0x8D98
#define GL_RGBA_INTEGER									 0x8D99
#define GL_BGR_INTEGER									 0x8D9A
#define GL_BGRA_INTEGER									 0x8D9B
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV				 0x8DAD
#define GL_FRAMEBUFFER_SRGB								 0x8DB9
#define GL_COMPRESSED_RED_RGTC1							 0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1					 0x8DBC
#define GL_COMPRESSED_RG_RGTC2							 0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2					 0x8DBE
#define GL_SAMPLER_1D_ARRAY								 0x8DC0
#define GL_SAMPLER_2D_ARRAY								 0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW						 0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW						 0x8DC4
#define GL_SAMPLER_CUBE_SHADOW							 0x8DC5
#define GL_UNSIGNED_INT_VEC2							 0x8DC6
#define GL_UNSIGNED_INT_VEC3							 0x8DC7
#define GL_UNSIGNED_INT_VEC4							 0x8DC8
#define GL_INT_SAMPLER_1D								 0x8DC9
#define GL_INT_SAMPLER_2D								 0x8DCA
#define GL_INT_SAMPLER_3D								 0x8DCB
#define GL_INT_SAMPLER_CUBE								 0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY							 0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY							 0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D						 0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D						 0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D						 0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE					 0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY				 0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY				 0x8DD7
#define GL_QUERY_WAIT									 0x8E13
#define GL_QUERY_NO_WAIT								 0x8E14
#define GL_QUERY_BY_REGION_WAIT							 0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT						 0x8E16
#define GL_BUFFER_ACCESS_FLAGS							 0x911F
#define GL_BUFFER_MAP_LENGTH							 0x9120
#define GL_BUFFER_MAP_OFFSET							 0x9121

using GLBeginConditionalRender = void (DE_CALL_OPENGL*)(GLuint id, GLenum mode);
using GLBeginTransformFeedback = void (DE_CALL_OPENGL*)(GLenum primitiveMode);
using GLBindBufferBase = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLuint buffer);

using GLBindBufferRange = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLuint buffer, GLintptr offset,
	GLsizeiptr size);

using GLBindFragDataLocation = void (DE_CALL_OPENGL*)(GLuint program, GLuint color, const GLchar* name);
using GLBindFramebuffer = void (DE_CALL_OPENGL*)(GLenum target, GLuint framebuffer);
using GLBindRenderbuffer = void (DE_CALL_OPENGL*)(GLenum target, GLuint renderbuffer);
using GLBindVertexArray = void (DE_CALL_OPENGL*)(GLuint array);

using GLBlitFramebuffer = void (DE_CALL_OPENGL*)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0,
	GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

using GLCheckFramebufferStatus = GLenum (DE_CALL_OPENGL*)(GLenum target);
using GLClampColor = void (DE_CALL_OPENGL*)(GLenum target, GLenum clamp);
using GLClearBufferFI = void (DE_CALL_OPENGL*)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
using GLClearBufferFV = void (DE_CALL_OPENGL*)(GLenum buffer, GLint drawbuffer, const GLfloat* value);
using GLClearBufferIV = void (DE_CALL_OPENGL*)(GLenum buffer, GLint drawbuffer, const GLint* value);
using GLClearBufferUIV = void (DE_CALL_OPENGL*)(GLenum buffer, GLint drawbuffer, const GLuint* value);
using GLColorMaskI = void (DE_CALL_OPENGL*)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
using GLDeleteFramebuffers = void (DE_CALL_OPENGL*)(GLsizei n, const GLuint* framebuffers);
using GLDeleteRenderbuffers = void (DE_CALL_OPENGL*)(GLsizei n, const GLuint* renderbuffers);
using GLDeleteVertexArrays = void (DE_CALL_OPENGL*)(GLsizei n, const GLuint* arrays);
using GLDisableI = void (DE_CALL_OPENGL*)(GLenum target, GLuint index);
using GLEnableI = void (DE_CALL_OPENGL*)(GLenum target, GLuint index);
using GLEndConditionalRender = void (DE_CALL_OPENGL*)();
using GLEndTransformFeedback = void (DE_CALL_OPENGL*)();
using GLFlushMappedBufferRange = void (DE_CALL_OPENGL*)(GLenum target, GLintptr offset, GLsizeiptr length);

using GLFramebufferRenderbuffer = void (DE_CALL_OPENGL*)(GLenum target, GLenum attachment, GLenum renderbuffertarget,
	GLuint renderbuffer);

using GLFramebufferTexture1D = void (DE_CALL_OPENGL*)(GLenum target, GLenum attachment, GLenum textarget,
	GLuint texture, GLint level);

using GLFramebufferTexture2D = void (DE_CALL_OPENGL*)(GLenum target, GLenum attachment, GLenum textarget,
	GLuint texture, GLint level);

using GLFramebufferTexture3D = void (DE_CALL_OPENGL*)(GLenum target, GLenum attachment, GLenum textarget,
	GLuint texture, GLint level, GLint zoffset);

using GLFramebufferTextureLayer = void (DE_CALL_OPENGL*)(GLenum target, GLenum attachment, GLuint texture, GLint level,
	GLint layer);

using GLGenerateMipmap = void (DE_CALL_OPENGL*)(GLenum target);
using GLGenFramebuffers = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* framebuffers);
using GLGenRenderbuffers = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* renderbuffers);
using GLGenVertexArrays = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* arrays);
using GLGetBooleanI_V = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLboolean* data);
using GLGetFragDataLocation = GLint (DE_CALL_OPENGL*)(GLuint program, const GLchar* name);

using GLGetFramebufferAttachmentParameterIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum attachment, GLenum pname,
	GLint* params);

using GLGetIntegerI_V = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLint* data);
using GLGetRenderbufferParameterIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint* params);
using GLGetStringI = const GLubyte* (DE_CALL_OPENGL*)(GLenum name, GLuint index);
using GLGetTexParameterIIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint* params);
using GLGetTexParameterIUIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLuint* params);

using GLGetTransformFeedbackVarying = void (DE_CALL_OPENGL*)(GLuint program, GLuint index, GLsizei bufSize,
	GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);

using GLGetUniformUIV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLuint* params);
using GLGetVertexAttribIIV = void (DE_CALL_OPENGL*)(GLuint index, GLenum pname, GLint* params);
using GLGetVertexAttribIUIV = void (DE_CALL_OPENGL*)(GLuint index, GLenum pname, GLuint* params);
using GLIsEnabledI = GLboolean (DE_CALL_OPENGL*)(GLenum target, GLuint index);
using GLIsFramebuffer = GLboolean (DE_CALL_OPENGL*)(GLuint framebuffer);
using GLIsRenderbuffer = GLboolean (DE_CALL_OPENGL*)(GLuint renderbuffer);
using GLIsVertexArray = GLboolean (DE_CALL_OPENGL*)(GLuint array);
using GLMapBufferRange = Void* (DE_CALL_OPENGL*)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);

using GLRenderbufferStorage = void (DE_CALL_OPENGL*)(GLenum target, GLenum internalformat, GLsizei width,
	GLsizei height);

using GLRenderbufferStorageMultisample = void (DE_CALL_OPENGL*)(GLenum target, GLsizei samples, GLenum internalformat,
	GLsizei width, GLsizei height);

using GLTexParameterIIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, const GLint* params);
using GLTexParameterIUIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, const GLuint* params);

using GLTransformFeedbackVaryings = void (DE_CALL_OPENGL*)(GLuint program, GLsizei count,
	const GLchar* const* varyings, GLenum bufferMode);

using GLUniform1UI = void (DE_CALL_OPENGL*)(GLint location, GLuint v0);
using GLUniform1UIV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLuint* value);
using GLUniform2UI = void (DE_CALL_OPENGL*)(GLint location, GLuint v0, GLuint v1);
using GLUniform2UIV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLuint* value);
using GLUniform3UI = void (DE_CALL_OPENGL*)(GLint location, GLuint v0, GLuint v1, GLuint v2);
using GLUniform3UIV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLuint* value);
using GLUniform4UI = void (DE_CALL_OPENGL*)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
using GLUniform4UIV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLuint* value);
using GLVertexAttribI1I = void (DE_CALL_OPENGL*)(GLuint index, GLint x);
using GLVertexAttribI1IV = void (DE_CALL_OPENGL*)(GLuint index, const GLint* v);
using GLVertexAttribI1UI = void (DE_CALL_OPENGL*)(GLuint index, GLuint x);
using GLVertexAttribI1UIV = void (DE_CALL_OPENGL*)(GLuint index, const GLuint* v);
using GLVertexAttribI2I = void (DE_CALL_OPENGL*)(GLuint index, GLint x, GLint y);
using GLVertexAttribI2IV = void (DE_CALL_OPENGL*)(GLuint index, const GLint* v);
using GLVertexAttribI2UI = void (DE_CALL_OPENGL*)(GLuint index, GLuint x, GLuint y);
using GLVertexAttribI2UIV = void (DE_CALL_OPENGL*)(GLuint index, const GLuint* v);
using GLVertexAttribI3I = void (DE_CALL_OPENGL*)(GLuint index, GLint x, GLint y, GLint z);
using GLVertexAttribI3IV = void (DE_CALL_OPENGL*)(GLuint index, const GLint* v);
using GLVertexAttribI3UI = void (DE_CALL_OPENGL*)(GLuint index, GLuint x, GLuint y, GLuint z);
using GLVertexAttribI3UIV = void (DE_CALL_OPENGL*)(GLuint index, const GLuint* v);
using GLVertexAttribI4BV = void (DE_CALL_OPENGL*)(GLuint index, const GLbyte* v);
using GLVertexAttribI4I = void (DE_CALL_OPENGL*)(GLuint index, GLint x, GLint y, GLint z, GLint w);
using GLVertexAttribI4IV = void (DE_CALL_OPENGL*)(GLuint index, const GLint* v);
using GLVertexAttribI4SV = void (DE_CALL_OPENGL*)(GLuint index, const GLshort* v);
using GLVertexAttribI4UBV = void (DE_CALL_OPENGL*)(GLuint index, const GLubyte* v);
using GLVertexAttribI4UI = void (DE_CALL_OPENGL*)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
using GLVertexAttribI4UIV = void (DE_CALL_OPENGL*)(GLuint index, const GLuint* v);
using GLVertexAttribI4USV = void (DE_CALL_OPENGL*)(GLuint index, const GLushort* v);

using GLVertexAttribIPointer = void (DE_CALL_OPENGL*)(GLuint index, GLint size, GLenum type, GLsizei stride,
	const Void* pointer);


// Version 3.1

#define GL_TEXTURE_RECTANGLE						   0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE				   0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE					   0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE				   0x84F8
#define GL_UNIFORM_BUFFER							   0x8A11
#define GL_UNIFORM_BUFFER_BINDING					   0x8A28
#define GL_UNIFORM_BUFFER_START						   0x8A29
#define GL_UNIFORM_BUFFER_SIZE						   0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS				   0x8A2B
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS				   0x8A2C
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS				   0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS				   0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS				   0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE					   0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS	   0x8A31
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS    0x8A32
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS    0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT			   0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH		   0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS					   0x8A36
#define GL_UNIFORM_TYPE								   0x8A37
#define GL_UNIFORM_SIZE								   0x8A38
#define GL_UNIFORM_NAME_LENGTH						   0x8A39
#define GL_UNIFORM_BLOCK_INDEX						   0x8A3A
#define GL_UNIFORM_OFFSET							   0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE						   0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE					   0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR						   0x8A3E
#define GL_UNIFORM_BLOCK_BINDING					   0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE					   0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH				   0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS			   0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES		   0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER   0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_SAMPLER_2D_RECT							   0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW					   0x8B64
#define GL_TEXTURE_BUFFER							   0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE					   0x8C2B
#define GL_TEXTURE_BINDING_BUFFER					   0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING		   0x8C2D
#define GL_SAMPLER_BUFFER							   0x8DC2
#define GL_INT_SAMPLER_2D_RECT						   0x8DCD
#define GL_INT_SAMPLER_BUFFER						   0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT				   0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_BUFFER				   0x8DD8
#define GL_COPY_READ_BUFFER							   0x8F36
#define GL_COPY_WRITE_BUFFER						   0x8F37
#define GL_R8_SNORM									   0x8F94
#define GL_RG8_SNORM								   0x8F95
#define GL_RGB8_SNORM								   0x8F96
#define GL_RGBA8_SNORM								   0x8F97
#define GL_R16_SNORM								   0x8F98
#define GL_RG16_SNORM								   0x8F99
#define GL_RGB16_SNORM								   0x8F9A
#define GL_RGBA16_SNORM								   0x8F9B
#define GL_SIGNED_NORMALIZED						   0x8F9C
#define GL_PRIMITIVE_RESTART						   0x8F9D
#define GL_PRIMITIVE_RESTART_INDEX					   0x8F9E
#define GL_INVALID_INDEX							   0xFFFFFFFFu

using GLCopyBufferSubData = void (DE_CALL_OPENGL*)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset,
	GLintptr writeOffset, GLsizeiptr size);

using GLDrawArraysInstanced = void (DE_CALL_OPENGL*)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);

using GLDrawElementsInstanced = void (DE_CALL_OPENGL*)(GLenum mode, GLsizei count, GLenum type, const Void* indices,
	GLsizei instancecount);

using GLGetActiveUniformBlockIV = void (DE_CALL_OPENGL*)(GLuint program, GLuint uniformBlockIndex, GLenum pname,
	GLint* params);

using GLGetActiveUniformBlockName = void (DE_CALL_OPENGL*)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize,
	GLsizei* length, GLchar* uniformBlockName);

using GLGetActiveUniformName = void (DE_CALL_OPENGL*)(GLuint program, GLuint uniformIndex, GLsizei bufSize,
	GLsizei* length, GLchar* uniformName);

using GLGetActiveUniformsIV = void (DE_CALL_OPENGL*)(GLuint program, GLsizei uniformCount,
	const GLuint* uniformIndices, GLenum pname, GLint* params);

using GLGetUniformBlockIndex = GLuint (DE_CALL_OPENGL*)(GLuint program, const GLchar* uniformBlockName);

using GLGetUniformIndices = void (DE_CALL_OPENGL*)(GLuint program, GLsizei uniformCount,
	const GLchar* const* uniformNames, GLuint* uniformIndices);

using GLPrimitiveRestartIndex = void (DE_CALL_OPENGL*)(GLuint index);
using GLTexBuffer = void (DE_CALL_OPENGL*)(GLenum target, GLenum internalformat, GLuint buffer);

using GLUniformBlockBinding = void (DE_CALL_OPENGL*)(GLuint program, GLuint uniformBlockIndex,
	GLuint uniformBlockBinding);


// Version 3.2

struct GLsyncStruct;
using GLsync = GLsyncStruct*;

using GLint64  = Int64;
using GLuint64 = Uint64;

#define GL_CONTEXT_CORE_PROFILE_BIT					 0x0001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT		 0x0002
#define GL_SYNC_FLUSH_COMMANDS_BIT					 0x0001
#define GL_LINES_ADJACENCY							 0x000A
#define GL_LINE_STRIP_ADJACENCY						 0x000B
#define GL_TRIANGLES_ADJACENCY						 0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY					 0x000D
#define GL_PROGRAM_POINT_SIZE						 0x8642
#define GL_DEPTH_CLAMP								 0x864F
#define GL_TEXTURE_CUBE_MAP_SEAMLESS				 0x884F
#define GL_GEOMETRY_VERTICES_OUT					 0x8916
#define GL_GEOMETRY_INPUT_TYPE						 0x8917
#define GL_GEOMETRY_OUTPUT_TYPE						 0x8918
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS			 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED			 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS		 0x8DA8
#define GL_GEOMETRY_SHADER							 0x8DD9
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS			 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES				 0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS		 0x8DE1
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION  0x8E4C
#define GL_FIRST_VERTEX_CONVENTION					 0x8E4D
#define GL_LAST_VERTEX_CONVENTION					 0x8E4E
#define GL_PROVOKING_VERTEX							 0x8E4F
#define GL_SAMPLE_POSITION							 0x8E50
#define GL_SAMPLE_MASK								 0x8E51
#define GL_SAMPLE_MASK_VALUE						 0x8E52
#define GL_MAX_SAMPLE_MASK_WORDS					 0x8E59
#define GL_TEXTURE_2D_MULTISAMPLE					 0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE				 0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY				 0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY		 0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE			 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY		 0x9105
#define GL_TEXTURE_SAMPLES							 0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS			 0x9107
#define GL_SAMPLER_2D_MULTISAMPLE					 0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE				 0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE		 0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY				 0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY			 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#define GL_MAX_COLOR_TEXTURE_SAMPLES				 0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES				 0x910F
#define GL_MAX_INTEGER_SAMPLES						 0x9110
#define GL_MAX_SERVER_WAIT_TIMEOUT					 0x9111
#define GL_OBJECT_TYPE								 0x9112
#define GL_SYNC_CONDITION							 0x9113
#define GL_SYNC_STATUS								 0x9114
#define GL_SYNC_FLAGS								 0x9115
#define GL_SYNC_FENCE								 0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE				 0x9117
#define GL_UNSIGNALED								 0x9118
#define GL_SIGNALED									 0x9119
#define GL_ALREADY_SIGNALED							 0x911A
#define GL_TIMEOUT_EXPIRED							 0x911B
#define GL_CONDITION_SATISFIED						 0x911C
#define GL_WAIT_FAILED								 0x911D
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS				 0x9122
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS			 0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS			 0x9124
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS			 0x9125
#define GL_CONTEXT_PROFILE_MASK						 0x9126
#define GL_TIMEOUT_IGNORED							 0xFFFFFFFFFFFFFFFFull

using GLClientWaitSync = GLenum (DE_CALL_OPENGL*)(GLsync sync, GLbitfield flags, GLuint64 timeout);
using GLDeleteSync = void (DE_CALL_OPENGL*)(GLsync sync);

using GLDrawElementsBaseVertex = void (DE_CALL_OPENGL*)(GLenum mode, GLsizei count, GLenum type, const Void* indices,
	GLint basevertex);

using GLDrawElementsInstancedBaseVertex = void (DE_CALL_OPENGL*)(GLenum mode, GLsizei count, GLenum type,
	const Void* indices, GLsizei instancecount, GLint basevertex);

using GLDrawRangeElementsBaseVertex = void (DE_CALL_OPENGL*)(GLenum mode, GLuint start, GLuint end, GLsizei count,
	GLenum type, const Void* indices, GLint basevertex);

using GLFenceSync = GLsync (DE_CALL_OPENGL*)(GLenum condition, GLbitfield flags);
using GLFramebufferTexture = void (DE_CALL_OPENGL*)(GLenum target, GLenum attachment, GLuint texture, GLint level);
using GLGetBufferParameterI64V = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint64* params);
using GLGetInteger64I_V = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLint64* data);
using GLGetInteger64V = void (DE_CALL_OPENGL*)(GLenum pname, GLint64* data);
using GLGetMultisampleFV = void (DE_CALL_OPENGL*)(GLenum pname, GLuint index, GLfloat* val);
using GLGetSyncIV = void (DE_CALL_OPENGL*)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values);
using GLIsSync = GLboolean (DE_CALL_OPENGL*)(GLsync sync);

using GLMultiDrawElementsBaseVertex = void (DE_CALL_OPENGL*)(GLenum mode, const GLsizei* count, GLenum type,
	const Void* const* indices, GLsizei drawcount, const GLint* basevertex);

using GLProvokingVertex = void (DE_CALL_OPENGL*)(GLenum mode);
using GLSampleMaskI = void (DE_CALL_OPENGL*)(GLuint maskNumber, GLbitfield mask);

using GLTexImage2DMultisample = void (DE_CALL_OPENGL*)(GLenum target, GLsizei samples, GLenum internalformat,
	GLsizei width, GLsizei height, GLboolean fixedsamplelocations);

using GLTexImage3DMultisample = void (DE_CALL_OPENGL*)(GLenum target, GLsizei samples, GLenum internalformat,
	GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);

using GLWaitSync = void (DE_CALL_OPENGL*)(GLsync sync, GLbitfield flags, GLuint64 timeout);


// Version 3.3

#define GL_TIME_ELAPSED                   0x88BF
#define GL_SRC1_COLOR                     0x88F9
#define GL_ONE_MINUS_SRC1_COLOR           0x88FA
#define GL_ONE_MINUS_SRC1_ALPHA           0x88FB
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS   0x88FC
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR    0x88FE
#define GL_SAMPLER_BINDING                0x8919
#define GL_ANY_SAMPLES_PASSED             0x8C2F
#define GL_INT_2_10_10_10_REV             0x8D9F
#define GL_TIMESTAMP                      0x8E28
#define GL_TEXTURE_SWIZZLE_R              0x8E42
#define GL_TEXTURE_SWIZZLE_G              0x8E43
#define GL_TEXTURE_SWIZZLE_B              0x8E44
#define GL_TEXTURE_SWIZZLE_A              0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA           0x8E46
#define GL_RGB10_A2UI                     0x906F

using GLBindFragDataLocationIndexed = void (DE_CALL_OPENGL*)(GLuint program, GLuint colorNumber, GLuint index,
	const GLchar* name);

using GLBindSampler = void (DE_CALL_OPENGL*)(GLuint unit, GLuint sampler);
using GLDeleteSamplers = void (DE_CALL_OPENGL*)(GLsizei count, const GLuint* samplers);
using GLGenSamplers = void (DE_CALL_OPENGL*)(GLsizei count, GLuint* samplers);
using GLGetFragDataIndex = GLint (DE_CALL_OPENGL*)(GLuint program, const GLchar* name);
using GLGetQueryObjectI64V = void (DE_CALL_OPENGL*)(GLuint id, GLenum pname, GLint64* params);
using GLGetQueryObjectUI64V = void (DE_CALL_OPENGL*)(GLuint id, GLenum pname, GLuint64* params);
using GLGetSamplerParameterFV = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, GLfloat* params);
using GLGetSamplerParameterIIV = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, GLint* params);
using GLGetSamplerParameterIUIV = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, GLuint* params);
using GLGetSamplerParameterIV = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, GLint* params);
using GLIsSampler = GLboolean (DE_CALL_OPENGL*)(GLuint sampler);
using GLQueryCounter = void (DE_CALL_OPENGL*)(GLuint id, GLenum target);
using GLSamplerParameterF = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, GLfloat param);
using GLSamplerParameterFV = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, const GLfloat* param);
using GLSamplerParameterI = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, GLint param);
using GLSamplerParameterIV = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, const GLint* param);
using GLSamplerParameterIIV = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, const GLint* param);
using GLSamplerParameterIUIV = void (DE_CALL_OPENGL*)(GLuint sampler, GLenum pname, const GLuint* param);
using GLVertexAttribDivisor = void (DE_CALL_OPENGL*)(GLuint index, GLuint divisor);
using GLVertexAttribP1UI = void (DE_CALL_OPENGL*)(GLuint index, GLenum type, GLboolean normalized, GLuint value);

using GLVertexAttribP1UIV = void (DE_CALL_OPENGL*)(GLuint index, GLenum type, GLboolean normalized,
	const GLuint* value);

using GLVertexAttribP2UI = void (DE_CALL_OPENGL*)(GLuint index, GLenum type, GLboolean normalized, GLuint value);

using GLVertexAttribP2UIV = void (DE_CALL_OPENGL*)(GLuint index, GLenum type, GLboolean normalized,
	const GLuint* value);

using GLVertexAttribP3UI = void (DE_CALL_OPENGL*)(GLuint index, GLenum type, GLboolean normalized, GLuint value);

using GLVertexAttribP3UIV = void (DE_CALL_OPENGL*)(GLuint index, GLenum type, GLboolean normalized,
	const GLuint* value);

using GLVertexAttribP4UI = void (DE_CALL_OPENGL*)(GLuint index, GLenum type, GLboolean normalized, GLuint value);

using GLVertexAttribP4UIV = void (DE_CALL_OPENGL*)(GLuint index, GLenum type, GLboolean normalized,
	const GLuint* value);


// Version 4.0

#define GL_PATCHES											  0x000E
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER	  0x84F0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS				  0x886C
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS				  0x886D
#define GL_GEOMETRY_SHADER_INVOCATIONS						  0x887F
#define GL_SAMPLE_SHADING									  0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE							  0x8C37
#define GL_ACTIVE_SUBROUTINES								  0x8DE5
#define GL_ACTIVE_SUBROUTINE_UNIFORMS						  0x8DE6
#define GL_MAX_SUBROUTINES									  0x8DE7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS					  0x8DE8
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS		  0x8E1E
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS	  0x8E1F
#define GL_TRANSFORM_FEEDBACK								  0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED					  0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE					  0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING						  0x8E25
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS				  0x8E47
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH						  0x8E48
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH				  0x8E49
#define GL_NUM_COMPATIBLE_SUBROUTINES						  0x8E4A
#define GL_COMPATIBLE_SUBROUTINES							  0x8E4B
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS					  0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET				  0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET				  0x8E5C
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS				  0x8E5D
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET				  0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET				  0x8E5F
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS					  0x8E70
#define GL_MAX_VERTEX_STREAMS								  0x8E71
#define GL_PATCH_VERTICES									  0x8E72
#define GL_PATCH_DEFAULT_INNER_LEVEL						  0x8E73
#define GL_PATCH_DEFAULT_OUTER_LEVEL						  0x8E74
#define GL_TESS_CONTROL_OUTPUT_VERTICES						  0x8E75
#define GL_TESS_GEN_MODE									  0x8E76
#define GL_TESS_GEN_SPACING									  0x8E77
#define GL_TESS_GEN_VERTEX_ORDER							  0x8E78
#define GL_TESS_GEN_POINT_MODE								  0x8E79
#define GL_ISOLINES											  0x8E7A
#define GL_FRACTIONAL_ODD									  0x8E7B
#define GL_FRACTIONAL_EVEN									  0x8E7C
#define GL_MAX_PATCH_VERTICES								  0x8E7D
#define GL_MAX_TESS_GEN_LEVEL								  0x8E7E
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS				  0x8E7F
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS			  0x8E80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS				  0x8E81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS			  0x8E82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS				  0x8E83
#define GL_MAX_TESS_PATCH_COMPONENTS						  0x8E84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS			  0x8E85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS			  0x8E86
#define GL_TESS_EVALUATION_SHADER							  0x8E87
#define GL_TESS_CONTROL_SHADER								  0x8E88
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS					  0x8E89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS				  0x8E8A
#define GL_DRAW_INDIRECT_BUFFER								  0x8F3F
#define GL_DRAW_INDIRECT_BUFFER_BINDING						  0x8F43
#define GL_DOUBLE_MAT2										  0x8F46
#define GL_DOUBLE_MAT3										  0x8F47
#define GL_DOUBLE_MAT4										  0x8F48
#define GL_DOUBLE_MAT2x3									  0x8F49
#define GL_DOUBLE_MAT2x4									  0x8F4A
#define GL_DOUBLE_MAT3x2									  0x8F4B
#define GL_DOUBLE_MAT3x4									  0x8F4C
#define GL_DOUBLE_MAT4x2									  0x8F4D
#define GL_DOUBLE_MAT4x3									  0x8F4E
#define GL_DOUBLE_VEC2										  0x8FFC
#define GL_DOUBLE_VEC3										  0x8FFD
#define GL_DOUBLE_VEC4										  0x8FFE
#define GL_TEXTURE_CUBE_MAP_ARRAY							  0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY					  0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY						  0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY							  0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW					  0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY						  0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY				  0x900F

using GLBeginQueryIndexed = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLuint id);
using GLBindTransformFeedback = void (DE_CALL_OPENGL*)(GLenum target, GLuint id);
using GLBlendEquationI = void (DE_CALL_OPENGL*)(GLuint buf, GLenum mode);
using GLBlendEquationSeparateI = void (DE_CALL_OPENGL*)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
using GLBlendFuncI = void (DE_CALL_OPENGL*)(GLuint buf, GLenum src, GLenum dst);

using GLBlendFuncSeparateI = void (DE_CALL_OPENGL*)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha,
	GLenum dstAlpha);

using GLDeleteTransformFeedbacks = void (DE_CALL_OPENGL*)(GLsizei n, const GLuint* ids);
using GLDrawArraysIndirect = void (DE_CALL_OPENGL*)(GLenum mode, const Void* indirect);
using GLDrawElementsIndirect = void (DE_CALL_OPENGL*)(GLenum mode, GLenum type, const Void* indirect);
using GLDrawTransformFeedback = void (DE_CALL_OPENGL*)(GLenum mode, GLuint id);
using GLDrawTransformFeedbackStream = void (DE_CALL_OPENGL*)(GLenum mode, GLuint id, GLuint stream);
using GLEndQueryIndexed = void (DE_CALL_OPENGL*)(GLenum target, GLuint index);
using GLGenTransformFeedbacks = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* ids);

using GLGetActiveSubroutineName = void (DE_CALL_OPENGL*)(GLuint program, GLenum shadertype, GLuint index,
	GLsizei bufsize, GLsizei* length, GLchar* name);

using GLGetActiveSubroutineUniformIV = void (DE_CALL_OPENGL*)(GLuint program, GLenum shadertype, GLuint index,
	GLenum pname, GLint* values);

using GLGetActiveSubroutineUniformName = void (DE_CALL_OPENGL*)(GLuint program, GLenum shadertype, GLuint index,
	GLsizei bufsize, GLsizei* length, GLchar* name);

using GLGetProgramStageIV = void (DE_CALL_OPENGL*)(GLuint program, GLenum shadertype, GLenum pname, GLint* values);
using GLGetQueryIndexedIV = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLenum pname, GLint* params);
using GLGetSubroutineIndex = GLuint (DE_CALL_OPENGL*)(GLuint program, GLenum shadertype, const GLchar* name);
using GLGetSubroutineUniformLocation = GLint (DE_CALL_OPENGL*)(GLuint program, GLenum shadertype, const GLchar* name);
using GLGetUniformDV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLdouble* params);
using GLGetUniformSubroutineUIV = void (DE_CALL_OPENGL*)(GLenum shadertype, GLint location, GLuint* params);
using GLIsTransformFeedback = GLboolean (DE_CALL_OPENGL*)(GLuint id);
using GLMinSampleShading = void (DE_CALL_OPENGL*)(GLfloat value);
using GLPatchParameterFV = void (DE_CALL_OPENGL*)(GLenum pname, const GLfloat* values);
using GLPatchParameterI = void (DE_CALL_OPENGL*)(GLenum pname, GLint value);
using GLPauseTransformFeedback = void (DE_CALL_OPENGL*)();
using GLResumeTransformFeedback = void (DE_CALL_OPENGL*)();
using GLUniform1D = void (DE_CALL_OPENGL*)(GLint location, GLdouble x);
using GLUniform1DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLdouble* value);
using GLUniform2D = void (DE_CALL_OPENGL*)(GLint location, GLdouble x, GLdouble y);
using GLUniform2DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLdouble* value);
using GLUniform3D = void (DE_CALL_OPENGL*)(GLint location, GLdouble x, GLdouble y, GLdouble z);
using GLUniform3DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLdouble* value);
using GLUniform4D = void (DE_CALL_OPENGL*)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
using GLUniform4DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, const GLdouble* value);

using GLUniformMatrix2DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformMatrix2X3DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformMatrix2X4DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformMatrix3DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformMatrix3X2DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformMatrix3X4DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformMatrix4DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformMatrix4X2DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformMatrix4X3DV = void (DE_CALL_OPENGL*)(GLint location, GLsizei count, GLboolean transpose,
	const GLdouble* value);

using GLUniformSubroutineSUIV = void (DE_CALL_OPENGL*)(GLenum shadertype, GLsizei count, const GLuint* indices);


// Version 4.1

#define GL_VERTEX_SHADER_BIT				0x00000001
#define GL_FRAGMENT_SHADER_BIT				0x00000002
#define GL_GEOMETRY_SHADER_BIT				0x00000004
#define GL_TESS_CONTROL_SHADER_BIT			0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT		0x00000010
#define GL_ALL_SHADER_BITS					0xFFFFFFFF
#define GL_FIXED							0x140C
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT	0x8257
#define GL_PROGRAM_SEPARABLE				0x8258
#define GL_ACTIVE_PROGRAM					0x8259
#define GL_PROGRAM_PIPELINE_BINDING			0x825A
#define GL_MAX_VIEWPORTS					0x825B
#define GL_VIEWPORT_SUBPIXEL_BITS			0x825C
#define GL_VIEWPORT_BOUNDS_RANGE			0x825D
#define GL_LAYER_PROVOKING_VERTEX			0x825E
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX	0x825F
#define GL_UNDEFINED_VERTEX					0x8260
#define GL_PROGRAM_BINARY_LENGTH			0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS		0x87FE
#define GL_PROGRAM_BINARY_FORMATS			0x87FF
#define GL_IMPLEMENTATION_COLOR_READ_TYPE	0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_RGB565							0x8D62
#define GL_LOW_FLOAT						0x8DF0
#define GL_MEDIUM_FLOAT						0x8DF1
#define GL_HIGH_FLOAT						0x8DF2
#define GL_LOW_INT							0x8DF3
#define GL_MEDIUM_INT						0x8DF4
#define GL_HIGH_INT							0x8DF5
#define GL_SHADER_BINARY_FORMATS			0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS		0x8DF9
#define GL_SHADER_COMPILER					0x8DFA
#define GL_MAX_VERTEX_UNIFORM_VECTORS		0x8DFB
#define GL_MAX_VARYING_VECTORS				0x8DFC
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS		0x8DFD

using GLActiveShaderProgram = void (DE_CALL_OPENGL*)(GLuint pipeline, GLuint program);
using GLBindProgramPipeline = void (DE_CALL_OPENGL*)(GLuint pipeline);
using GLClearDepthF = void (DE_CALL_OPENGL*)(GLfloat d);
using GLCreateShaderProgramV = GLuint (DE_CALL_OPENGL*)(GLenum type, GLsizei count, const GLchar* const* strings);
using GLDeleteProgramPipelines = void (DE_CALL_OPENGL*)(GLsizei n, const GLuint* pipelines);
using GLDepthRangeArrayV = void (DE_CALL_OPENGL*)(GLuint first, GLsizei count, const GLdouble* v);
using GLDepthRangeF = void (DE_CALL_OPENGL*)(GLfloat n, GLfloat f);
using GLDepthRangeIndexed = void (DE_CALL_OPENGL*)(GLuint index, GLdouble n, GLdouble f);
using GLGenProgramPipelines = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* pipelines);
using GLGetDoubleI_V = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLdouble* data);
using GLGetFloatI_V = void (DE_CALL_OPENGL*)(GLenum target, GLuint index, GLfloat* data);

using GLGetProgramBinary = void (DE_CALL_OPENGL*)(GLuint program, GLsizei bufSize, GLsizei* length,
	GLenum* binaryFormat, Void* binary);

using GLGetProgramPipelineInfoLog = void (DE_CALL_OPENGL*)(GLuint pipeline, GLsizei bufSize, GLsizei* length,
	GLchar* infoLog);

using GLGetProgramPipelineIV = void (DE_CALL_OPENGL*)(GLuint pipeline, GLenum pname, GLint* params);

using GLGetShaderPrecisionFormat = void (DE_CALL_OPENGL*)(GLenum shadertype, GLenum precisiontype, GLint* range,
	GLint* precision);

using GLGetVertexAttribLDV = void (DE_CALL_OPENGL*)(GLuint index, GLenum pname, GLdouble* params);
using GLIsProgramPipeline = GLboolean (DE_CALL_OPENGL*)(GLuint pipeline);

using GLProgramBinary = void (DE_CALL_OPENGL*)(GLuint program, GLenum binaryFormat, const Void* binary,
	GLsizei length);

using GLProgramParameterI = void (DE_CALL_OPENGL*)(GLuint program, GLenum pname, GLint value);
using GLProgramUniform1D = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLdouble v0);

using GLProgramUniform1DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLdouble* value);

using GLProgramUniform1F = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLfloat v0);

using GLProgramUniform1FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLfloat* value);

using GLProgramUniform1I = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLint v0);
using GLProgramUniform1IV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count, const GLint* value);
using GLProgramUniform1UI = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLuint v0);

using GLProgramUniform1UIV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLuint* value);

using GLProgramUniform2D = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLdouble v0, GLdouble v1);

using GLProgramUniform2DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLdouble* value);

using GLProgramUniform2F = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLfloat v0, GLfloat v1);

using GLProgramUniform2FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLfloat* value);

using GLProgramUniform2I = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLint v0, GLint v1);
using GLProgramUniform2IV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count, const GLint* value);
using GLProgramUniform2UI = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLuint v0, GLuint v1);

using GLProgramUniform2UIV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLuint* value);

using GLProgramUniform3D = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLdouble v0, GLdouble v1,
	GLdouble v2);

using GLProgramUniform3DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLdouble* value);

using GLProgramUniform3F = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);

using GLProgramUniform3FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLfloat* value);

using GLProgramUniform3I = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
using GLProgramUniform3IV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count, const GLint* value);
using GLProgramUniform3UI = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);

using GLProgramUniform3UIV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLuint* value);

using GLProgramUniform4D = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLdouble v0, GLdouble v1,
	GLdouble v2, GLdouble v3);

using GLProgramUniform4DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLdouble* value);

using GLProgramUniform4F = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2,
	GLfloat v3);

using GLProgramUniform4FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLfloat* value);

using GLProgramUniform4I = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2,
	GLint v3);

using GLProgramUniform4IV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count, const GLint* value);

using GLProgramUniform4UI = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2,
	GLuint v3);

using GLProgramUniform4UIV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	const GLuint* value);

using GLProgramUniformMatrix2DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix2FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLProgramUniformMatrix2X3DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix2X3FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLProgramUniformMatrix2X4DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix2X4FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLProgramUniformMatrix3DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix3FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLProgramUniformMatrix3X2DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix3X2FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLProgramUniformMatrix3X4DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix3X4FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLProgramUniformMatrix4DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix4FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLProgramUniformMatrix4X2DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix4X2FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLProgramUniformMatrix4X3DV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLdouble* value);

using GLProgramUniformMatrix4X3FV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei count,
	GLboolean transpose, const GLfloat* value);

using GLReleaseShaderCompiler = void (DE_CALL_OPENGL*)();

using GLShaderBinary = void (DE_CALL_OPENGL*)(GLsizei count, const GLuint* shaders, GLenum binaryformat,
	const Void* binary, GLsizei length);

using GLScissorArrayV = void (DE_CALL_OPENGL*)(GLuint first, GLsizei count, const GLint* v);
using GLScissorIndexed = void (DE_CALL_OPENGL*)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
using GLScissorIndexedV = void (DE_CALL_OPENGL*)(GLuint index, const GLint* v);
using GLUseProgramStages = void (DE_CALL_OPENGL*)(GLuint pipeline, GLbitfield stages, GLuint program);
using GLValidateProgramPipeline = void (DE_CALL_OPENGL*)(GLuint pipeline);
using GLVertexAttribL1D = void (DE_CALL_OPENGL*)(GLuint index, GLdouble x);
using GLVertexAttribL1DV = void (DE_CALL_OPENGL*)(GLuint index, const GLdouble* v);
using GLVertexAttribL2D = void (DE_CALL_OPENGL*)(GLuint index, GLdouble x, GLdouble y);
using GLVertexAttribL2DV = void (DE_CALL_OPENGL*)(GLuint index, const GLdouble* v);
using GLVertexAttribL3D = void (DE_CALL_OPENGL*)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
using GLVertexAttribL3DV = void (DE_CALL_OPENGL*)(GLuint index, const GLdouble* v);
using GLVertexAttribL4D = void (DE_CALL_OPENGL*)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
using GLVertexAttribL4DV = void (DE_CALL_OPENGL*)(GLuint index, const GLdouble* v);

using GLVertexAttribLPointer = void (DE_CALL_OPENGL*)(GLuint index, GLint size, GLenum type, GLsizei stride,
	const Void* pointer);

using GLViewportArrayV = void (DE_CALL_OPENGL*)(GLuint first, GLsizei count, const GLfloat* v);
using GLViewportIndexedF = void (DE_CALL_OPENGL*)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
using GLViewportIndexedFV = void (DE_CALL_OPENGL*)(GLuint index, const GLfloat* v);


// Version 4.2

#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT							  0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT								  0x00000002
#define GL_UNIFORM_BARRIER_BIT										  0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT								  0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT							  0x00000020
#define GL_COMMAND_BARRIER_BIT										  0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT									  0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT								  0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT								  0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT									  0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT							  0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT								  0x00001000
#define GL_ALL_BARRIER_BITS											  0xFFFFFFFF
#define GL_TRANSFORM_FEEDBACK_ACTIVE								  0x8E24
#define GL_TRANSFORM_FEEDBACK_PAUSED								  0x8E23
#define GL_COMPRESSED_RGBA_BPTC_UNORM								  0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM							  0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT							  0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT						  0x8E8F
#define GL_COPY_READ_BUFFER_BINDING									  0x8F36
#define GL_COPY_WRITE_BUFFER_BINDING								  0x8F37
#define GL_MAX_IMAGE_UNITS											  0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS			  0x8F39
#define GL_IMAGE_BINDING_NAME										  0x8F3A
#define GL_IMAGE_BINDING_LEVEL										  0x8F3B
#define GL_IMAGE_BINDING_LAYERED									  0x8F3C
#define GL_IMAGE_BINDING_LAYER										  0x8F3D
#define GL_IMAGE_BINDING_ACCESS										  0x8F3E
#define GL_IMAGE_1D													  0x904C
#define GL_IMAGE_2D													  0x904D
#define GL_IMAGE_3D													  0x904E
#define GL_IMAGE_2D_RECT											  0x904F
#define GL_IMAGE_CUBE												  0x9050
#define GL_IMAGE_BUFFER												  0x9051
#define GL_IMAGE_1D_ARRAY											  0x9052
#define GL_IMAGE_2D_ARRAY											  0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY										  0x9054
#define GL_IMAGE_2D_MULTISAMPLE										  0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY								  0x9056
#define GL_INT_IMAGE_1D												  0x9057
#define GL_INT_IMAGE_2D												  0x9058
#define GL_INT_IMAGE_3D												  0x9059
#define GL_INT_IMAGE_2D_RECT										  0x905A
#define GL_INT_IMAGE_CUBE											  0x905B
#define GL_INT_IMAGE_BUFFER											  0x905C
#define GL_INT_IMAGE_1D_ARRAY										  0x905D
#define GL_INT_IMAGE_2D_ARRAY										  0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY									  0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE									  0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY							  0x9061
#define GL_UNSIGNED_INT_IMAGE_1D									  0x9062
#define GL_UNSIGNED_INT_IMAGE_2D									  0x9063
#define GL_UNSIGNED_INT_IMAGE_3D									  0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT								  0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE									  0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER								  0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY								  0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY								  0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY						  0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE						  0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY					  0x906C
#define GL_MAX_IMAGE_SAMPLES										  0x906D
#define GL_IMAGE_BINDING_FORMAT										  0x906E
#define GL_MIN_MAP_BUFFER_ALIGNMENT									  0x90BC
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE							  0x90C7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE						  0x90C8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS						  0x90C9
#define GL_MAX_VERTEX_IMAGE_UNIFORMS								  0x90CA
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS							  0x90CB
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS						  0x90CC
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS								  0x90CD
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS								  0x90CE
#define GL_MAX_COMBINED_IMAGE_UNIFORMS								  0x90CF
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH							  0x9127
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT							  0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH							  0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE								  0x912A
#define GL_PACK_COMPRESSED_BLOCK_WIDTH								  0x912B
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT								  0x912C
#define GL_PACK_COMPRESSED_BLOCK_DEPTH								  0x912D
#define GL_PACK_COMPRESSED_BLOCK_SIZE								  0x912E
#define GL_TEXTURE_IMMUTABLE_FORMAT									  0x912F
#define GL_ATOMIC_COUNTER_BUFFER									  0x92C0
#define GL_ATOMIC_COUNTER_BUFFER_BINDING							  0x92C1
#define GL_ATOMIC_COUNTER_BUFFER_START								  0x92C2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE								  0x92C3
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE							  0x92C4
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS				  0x92C5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES		  0x92C6
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER		  0x92C7
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER	  0x92C8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92C9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER		  0x92CA
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER		  0x92CB
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS						  0x92CC
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS					  0x92CD
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS				  0x92CE
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS						  0x92CF
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS						  0x92D0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS						  0x92D1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS								  0x92D2
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS							  0x92D3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS						  0x92D4
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS								  0x92D5
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS								  0x92D6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS								  0x92D7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE							  0x92D8
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS							  0x92D9
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX						  0x92DA
#define GL_UNSIGNED_INT_ATOMIC_COUNTER								  0x92DB
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS						  0x92DC
#define GL_NUM_SAMPLE_COUNTS										  0x9380

using GLBindImageTexture = void (DE_CALL_OPENGL*)(GLuint unit, GLuint texture, GLint level, GLboolean layered,
	GLint layer, GLenum access, GLenum format);

using GLDrawArraysInstancedBaseInstance = void (DE_CALL_OPENGL*)(GLenum mode, GLint first, GLsizei count,
	GLsizei instancecount, GLuint baseinstance);

using GLDrawElementsInstancedBaseInstance = void (DE_CALL_OPENGL*)(GLenum mode, GLsizei count, GLenum type,
	const Void* indices, GLsizei instancecount, GLuint baseinstance);

using GLDrawElementsInstancedBaseVertexBaseInstance = void (DE_CALL_OPENGL*)(GLenum mode, GLsizei count, GLenum type,
	const Void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);

using GLDrawTransformFeedbackInstanced = void (DE_CALL_OPENGL*)(GLenum mode, GLuint id, GLsizei instancecount);

using GLDrawTransformFeedbackStreamInstanced = void (DE_CALL_OPENGL*)(GLenum mode, GLuint id, GLuint stream,
	GLsizei instancecount);

using GLGetActiveAtomicCounterBufferIV = void (DE_CALL_OPENGL*)(GLuint program, GLuint bufferIndex, GLenum pname,
	GLint* params);

using GLGetInternalformatIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum internalformat, GLenum pname,
	GLsizei bufSize, GLint* params);

using GLMemoryBarrier = void (DE_CALL_OPENGL*)(GLbitfield barriers);
using GLTexStorage1D = void (DE_CALL_OPENGL*)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);

using GLTexStorage2D = void (DE_CALL_OPENGL*)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width,
	GLsizei height);

using GLTexStorage3D = void (DE_CALL_OPENGL*)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width,
	GLsizei height, GLsizei depth);


// Version 4.3

#define GL_CONTEXT_FLAG_DEBUG_BIT							  0x00000002
#define GL_COMPUTE_SHADER_BIT								  0x00000020
#define GL_SHADER_STORAGE_BARRIER_BIT						  0x00002000
#define GL_DEBUG_OUTPUT_SYNCHRONOUS							  0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH					  0x8243
#define GL_DEBUG_CALLBACK_FUNCTION							  0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM						  0x8245
#define GL_DEBUG_SOURCE_API									  0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM						  0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER						  0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY							  0x8249
#define GL_DEBUG_SOURCE_APPLICATION							  0x824A
#define GL_DEBUG_SOURCE_OTHER								  0x824B
#define GL_DEBUG_TYPE_ERROR									  0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR					  0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR					  0x824E
#define GL_DEBUG_TYPE_PORTABILITY							  0x824F
#define GL_DEBUG_TYPE_PERFORMANCE							  0x8250
#define GL_DEBUG_TYPE_OTHER									  0x8251
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE					  0x8262
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS					  0x8263
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS				  0x8264
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS						  0x8265
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS			  0x8266
#define GL_COMPUTE_WORK_GROUP_SIZE							  0x8267
#define GL_DEBUG_TYPE_MARKER								  0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP							  0x8269
#define GL_DEBUG_TYPE_POP_GROUP								  0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION						  0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH						  0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH							  0x826D
#define GL_MAX_UNIFORM_LOCATIONS							  0x826E
#define GL_INTERNALFORMAT_SUPPORTED							  0x826F
#define GL_INTERNALFORMAT_PREFERRED							  0x8270
#define GL_INTERNALFORMAT_RED_SIZE							  0x8271
#define GL_INTERNALFORMAT_GREEN_SIZE						  0x8272
#define GL_INTERNALFORMAT_BLUE_SIZE							  0x8273
#define GL_INTERNALFORMAT_ALPHA_SIZE						  0x8274
#define GL_INTERNALFORMAT_DEPTH_SIZE						  0x8275
#define GL_INTERNALFORMAT_STENCIL_SIZE						  0x8276
#define GL_INTERNALFORMAT_SHARED_SIZE						  0x8277
#define GL_INTERNALFORMAT_RED_TYPE							  0x8278
#define GL_INTERNALFORMAT_GREEN_TYPE						  0x8279
#define GL_INTERNALFORMAT_BLUE_TYPE							  0x827A
#define GL_INTERNALFORMAT_ALPHA_TYPE						  0x827B
#define GL_INTERNALFORMAT_DEPTH_TYPE						  0x827C
#define GL_INTERNALFORMAT_STENCIL_TYPE						  0x827D
#define GL_MAX_WIDTH										  0x827E
#define GL_MAX_HEIGHT										  0x827F
#define GL_MAX_DEPTH										  0x8280
#define GL_MAX_LAYERS										  0x8281
#define GL_MAX_COMBINED_DIMENSIONS							  0x8282
#define GL_COLOR_COMPONENTS									  0x8283
#define GL_DEPTH_COMPONENTS									  0x8284
#define GL_STENCIL_COMPONENTS								  0x8285
#define GL_COLOR_RENDERABLE									  0x8286
#define GL_DEPTH_RENDERABLE									  0x8287
#define GL_STENCIL_RENDERABLE								  0x8288
#define GL_FRAMEBUFFER_RENDERABLE							  0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED					  0x828A
#define GL_FRAMEBUFFER_BLEND								  0x828B
#define GL_READ_PIXELS										  0x828C
#define GL_READ_PIXELS_FORMAT								  0x828D
#define GL_READ_PIXELS_TYPE									  0x828E
#define GL_TEXTURE_IMAGE_FORMAT								  0x828F
#define GL_TEXTURE_IMAGE_TYPE								  0x8290
#define GL_GET_TEXTURE_IMAGE_FORMAT							  0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE							  0x8292
#define GL_MIPMAP											  0x8293
#define GL_MANUAL_GENERATE_MIPMAP							  0x8294
#define GL_AUTO_GENERATE_MIPMAP								  0x8295
#define GL_COLOR_ENCODING									  0x8296
#define GL_SRGB_READ										  0x8297
#define GL_SRGB_WRITE										  0x8298
#define GL_FILTER											  0x829A
#define GL_VERTEX_TEXTURE									  0x829B
#define GL_TESS_CONTROL_TEXTURE								  0x829C
#define GL_TESS_EVALUATION_TEXTURE							  0x829D
#define GL_GEOMETRY_TEXTURE									  0x829E
#define GL_FRAGMENT_TEXTURE									  0x829F
#define GL_COMPUTE_TEXTURE									  0x82A0
#define GL_TEXTURE_SHADOW									  0x82A1
#define GL_TEXTURE_GATHER									  0x82A2
#define GL_TEXTURE_GATHER_SHADOW							  0x82A3
#define GL_SHADER_IMAGE_LOAD								  0x82A4
#define GL_SHADER_IMAGE_STORE								  0x82A5
#define GL_SHADER_IMAGE_ATOMIC								  0x82A6
#define GL_IMAGE_TEXEL_SIZE									  0x82A7
#define GL_IMAGE_COMPATIBILITY_CLASS						  0x82A8
#define GL_IMAGE_PIXEL_FORMAT								  0x82A9
#define GL_IMAGE_PIXEL_TYPE									  0x82AA
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST				  0x82AC
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST			  0x82AD
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE				  0x82AE
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE			  0x82AF
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH					  0x82B1
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT					  0x82B2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE					  0x82B3
#define GL_CLEAR_BUFFER										  0x82B4
#define GL_TEXTURE_VIEW										  0x82B5
#define GL_VIEW_COMPATIBILITY_CLASS							  0x82B6
#define GL_FULL_SUPPORT										  0x82B7
#define GL_CAVEAT_SUPPORT									  0x82B8
#define GL_IMAGE_CLASS_4_X_32								  0x82B9
#define GL_IMAGE_CLASS_2_X_32								  0x82BA
#define GL_IMAGE_CLASS_1_X_32								  0x82BB
#define GL_IMAGE_CLASS_4_X_16								  0x82BC
#define GL_IMAGE_CLASS_2_X_16								  0x82BD
#define GL_IMAGE_CLASS_1_X_16								  0x82BE
#define GL_IMAGE_CLASS_4_X_8								  0x82BF
#define GL_IMAGE_CLASS_2_X_8								  0x82C0
#define GL_IMAGE_CLASS_1_X_8								  0x82C1
#define GL_IMAGE_CLASS_11_11_10								  0x82C2
#define GL_IMAGE_CLASS_10_10_10_2							  0x82C3
#define GL_VIEW_CLASS_128_BITS								  0x82C4
#define GL_VIEW_CLASS_96_BITS								  0x82C5
#define GL_VIEW_CLASS_64_BITS								  0x82C6
#define GL_VIEW_CLASS_48_BITS								  0x82C7
#define GL_VIEW_CLASS_32_BITS								  0x82C8
#define GL_VIEW_CLASS_24_BITS								  0x82C9
#define GL_VIEW_CLASS_16_BITS								  0x82CA
#define GL_VIEW_CLASS_8_BITS								  0x82CB
#define GL_VIEW_CLASS_S3TC_DXT1_RGB							  0x82CC
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA						  0x82CD
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA						  0x82CE
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA						  0x82CF
#define GL_VIEW_CLASS_RGTC1_RED								  0x82D0
#define GL_VIEW_CLASS_RGTC2_RG								  0x82D1
#define GL_VIEW_CLASS_BPTC_UNORM							  0x82D2
#define GL_VIEW_CLASS_BPTC_FLOAT							  0x82D3
#define GL_VERTEX_ATTRIB_BINDING							  0x82D4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET					  0x82D5
#define GL_VERTEX_BINDING_DIVISOR							  0x82D6
#define GL_VERTEX_BINDING_OFFSET							  0x82D7
#define GL_VERTEX_BINDING_STRIDE							  0x82D8
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET				  0x82D9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS						  0x82DA
#define GL_TEXTURE_VIEW_MIN_LEVEL							  0x82DB
#define GL_TEXTURE_VIEW_NUM_LEVELS							  0x82DC
#define GL_TEXTURE_VIEW_MIN_LAYER							  0x82DD
#define GL_TEXTURE_VIEW_NUM_LAYERS							  0x82DE
#define GL_TEXTURE_IMMUTABLE_LEVELS							  0x82DF
#define GL_BUFFER											  0x82E0
#define GL_SHADER											  0x82E1
#define GL_PROGRAM											  0x82E2
#define GL_QUERY											  0x82E3
#define GL_PROGRAM_PIPELINE									  0x82E4
#define GL_SAMPLER											  0x82E6
#define GL_MAX_LABEL_LENGTH									  0x82E8
#define GL_NUM_SHADING_LANGUAGE_VERSIONS					  0x82E9
#define GL_VERTEX_ATTRIB_ARRAY_LONG							  0x874E
#define GL_PRIMITIVE_RESTART_FIXED_INDEX					  0x8D69
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE					  0x8D6A
#define GL_MAX_ELEMENT_INDEX								  0x8D6B
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES				  0x8F39
#define GL_VERTEX_BINDING_BUFFER							  0x8F4F
#define GL_SHADER_STORAGE_BUFFER							  0x90D2
#define GL_SHADER_STORAGE_BUFFER_BINDING					  0x90D3
#define GL_SHADER_STORAGE_BUFFER_START						  0x90D4
#define GL_SHADER_STORAGE_BUFFER_SIZE						  0x90D5
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS					  0x90D6
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS				  0x90D7
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS			  0x90D8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS		  0x90D9
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS				  0x90DA
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS				  0x90DB
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS				  0x90DC
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS				  0x90DD
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE					  0x90DE
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT			  0x90DF
#define GL_DEPTH_STENCIL_TEXTURE_MODE						  0x90EA
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS				  0x90EB
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER		  0x90EC
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ED
#define GL_DISPATCH_INDIRECT_BUFFER							  0x90EE
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING					  0x90EF
#define GL_MAX_DEBUG_MESSAGE_LENGTH							  0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES						  0x9144
#define GL_DEBUG_LOGGED_MESSAGES							  0x9145
#define GL_DEBUG_SEVERITY_HIGH								  0x9146
#define GL_DEBUG_SEVERITY_MEDIUM							  0x9147
#define GL_DEBUG_SEVERITY_LOW								  0x9148
#define GL_TEXTURE_BUFFER_OFFSET							  0x919D
#define GL_TEXTURE_BUFFER_SIZE								  0x919E
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT					  0x919F
#define GL_COMPUTE_SHADER									  0x91B9
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS						  0x91BB
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS					  0x91BC
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS						  0x91BD
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT						  0x91BE
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE						  0x91BF
#define GL_COMPRESSED_R11_EAC								  0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC						  0x9271
#define GL_COMPRESSED_RG11_EAC								  0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC						  0x9273
#define GL_COMPRESSED_RGB8_ETC2								  0x9274
#define GL_COMPRESSED_SRGB8_ETC2							  0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2			  0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2		  0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC						  0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC					  0x9279
#define GL_DEBUG_OUTPUT										  0x92E0
#define GL_UNIFORM											  0x92E1
#define GL_UNIFORM_BLOCK									  0x92E2
#define GL_PROGRAM_INPUT									  0x92E3
#define GL_PROGRAM_OUTPUT									  0x92E4
#define GL_BUFFER_VARIABLE									  0x92E5
#define GL_SHADER_STORAGE_BLOCK								  0x92E6
#define GL_IS_PER_PATCH										  0x92E7
#define GL_VERTEX_SUBROUTINE								  0x92E8
#define GL_TESS_CONTROL_SUBROUTINE							  0x92E9
#define GL_TESS_EVALUATION_SUBROUTINE						  0x92EA
#define GL_GEOMETRY_SUBROUTINE								  0x92EB
#define GL_FRAGMENT_SUBROUTINE								  0x92EC
#define GL_COMPUTE_SUBROUTINE								  0x92ED
#define GL_VERTEX_SUBROUTINE_UNIFORM						  0x92EE
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM					  0x92EF
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM				  0x92F0
#define GL_GEOMETRY_SUBROUTINE_UNIFORM						  0x92F1
#define GL_FRAGMENT_SUBROUTINE_UNIFORM						  0x92F2
#define GL_COMPUTE_SUBROUTINE_UNIFORM						  0x92F3
#define GL_TRANSFORM_FEEDBACK_VARYING						  0x92F4
#define GL_ACTIVE_RESOURCES									  0x92F5
#define GL_MAX_NAME_LENGTH									  0x92F6
#define GL_MAX_NUM_ACTIVE_VARIABLES							  0x92F7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES					  0x92F8
#define GL_NAME_LENGTH										  0x92F9
#define GL_TYPE												  0x92FA
#define GL_ARRAY_SIZE										  0x92FB
#define GL_OFFSET											  0x92FC
#define GL_BLOCK_INDEX										  0x92FD
#define GL_ARRAY_STRIDE										  0x92FE
#define GL_MATRIX_STRIDE									  0x92FF
#define GL_IS_ROW_MAJOR										  0x9300
#define GL_ATOMIC_COUNTER_BUFFER_INDEX						  0x9301
#define GL_BUFFER_BINDING									  0x9302
#define GL_BUFFER_DATA_SIZE									  0x9303
#define GL_NUM_ACTIVE_VARIABLES								  0x9304
#define GL_ACTIVE_VARIABLES									  0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER						  0x9306
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER				  0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER				  0x9308
#define GL_REFERENCED_BY_GEOMETRY_SHADER					  0x9309
#define GL_REFERENCED_BY_FRAGMENT_SHADER					  0x930A
#define GL_REFERENCED_BY_COMPUTE_SHADER						  0x930B
#define GL_TOP_LEVEL_ARRAY_SIZE								  0x930C
#define GL_TOP_LEVEL_ARRAY_STRIDE							  0x930D
#define GL_LOCATION											  0x930E
#define GL_LOCATION_INDEX									  0x930F
#define GL_FRAMEBUFFER_DEFAULT_WIDTH						  0x9310
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT						  0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS						  0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES						  0x9313
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS		  0x9314
#define GL_MAX_FRAMEBUFFER_WIDTH							  0x9315
#define GL_MAX_FRAMEBUFFER_HEIGHT							  0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS							  0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES							  0x9318

using GLDebug = void (DE_CALL_OPENGL*)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const Void* userParam);

using GLBindVertexBuffer = void (DE_CALL_OPENGL*)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);

using GLClearBufferData = void (DE_CALL_OPENGL*)(GLenum target, GLenum internalformat, GLenum format, GLenum type,
	const Void* data);

using GLClearBufferSubData = void (DE_CALL_OPENGL*)(GLenum target, GLenum internalformat, GLintptr offset,
	GLsizeiptr size, GLenum format, GLenum type, const Void* data);

using GLCopyImageSubData = void (DE_CALL_OPENGL*)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX,
	GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ,
	GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);

using GLDispatchCompute = void (DE_CALL_OPENGL*)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
using GLDispatchComputeIndirect = void (DE_CALL_OPENGL*)(GLintptr indirect);
using GLDebugMessageCallback = void (DE_CALL_OPENGL*)(GLDebug callback, const Void* userParam);

using GLDebugMessageControl = void (DE_CALL_OPENGL*)(GLenum source, GLenum type, GLenum severity, GLsizei count,
	const GLuint* ids, GLboolean enabled);

using GLDebugMessageInsert = void (DE_CALL_OPENGL*)(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* buf);

using GLFramebufferParameterI = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint param);

using GLGetDebugMessageLog = GLuint(DE_CALL_OPENGL*)(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types,
	GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog);

using GLGetFramebufferParameterIV = void (DE_CALL_OPENGL*)(GLenum target, GLenum pname, GLint* params);

using GLGetInternalformatI64V = void (DE_CALL_OPENGL*)(GLenum target, GLenum internalformat, GLenum pname,
	GLsizei bufSize, GLint64* params);

using GLGetObjectLabel = void (DE_CALL_OPENGL*)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length,
	GLchar* label);

using GLGetObjectPtrLabel = void (DE_CALL_OPENGL*)(const Void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label);

using GLGetProgramInterfaceIV = void (DE_CALL_OPENGL*)(GLuint program, GLenum programInterface, GLenum pname,
	GLint* params);

using GLGetProgramResourceIndex = GLuint (DE_CALL_OPENGL*)(GLuint program, GLenum programInterface,
	const GLchar* name);

using GLGetProgramResourceIV = void (DE_CALL_OPENGL*)(GLuint program, GLenum programInterface, GLuint index,
	GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params);

using GLGetProgramResourceLocation = GLint (DE_CALL_OPENGL*)(GLuint program, GLenum programInterface,
	const GLchar* name);

using GLGetProgramResourceLocationIndex = GLint (DE_CALL_OPENGL*)(GLuint program, GLenum programInterface,
	const GLchar* name);

using GLGetProgramResourceName = void (DE_CALL_OPENGL*)(GLuint program, GLenum programInterface, GLuint index,
	GLsizei bufSize, GLsizei* length, GLchar* name);

using GLInvalidateBufferData = void (DE_CALL_OPENGL*)(GLuint buffer);
using GLInvalidateBufferSubData = void (DE_CALL_OPENGL*)(GLuint buffer, GLintptr offset, GLsizeiptr length);

using GLInvalidateFramebuffer = void (DE_CALL_OPENGL*)(GLenum target, GLsizei numAttachments,
	const GLenum* attachments);

using GLInvalidateSubFramebuffer = void (DE_CALL_OPENGL*)(GLenum target, GLsizei numAttachments,
	const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);

using GLInvalidateTexImage = void (DE_CALL_OPENGL*)(GLuint texture, GLint level);

using GLInvalidateTexSubImage = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);

using GLMultiDrawArraysIndirect = void (DE_CALL_OPENGL*)(GLenum mode, const Void* indirect, GLsizei drawcount,
	GLsizei stride);

using GLMultiDrawElementsIndirect = void (DE_CALL_OPENGL*)(GLenum mode, GLenum type, const Void* indirect,
	GLsizei drawcount, GLsizei stride);

using GLObjectLabel = void (DE_CALL_OPENGL*)(GLenum identifier, GLuint name, GLsizei length, const GLchar* label);
using GLObjectPtrLabel = void (DE_CALL_OPENGL*)(const Void* ptr, GLsizei length, const GLchar* label);
using GLPopDebugGroup = void (DE_CALL_OPENGL*)();
using GLPushDebugGroup = void (DE_CALL_OPENGL*)(GLenum source, GLuint id, GLsizei length, const GLchar* message);

using GLShaderStorageBlockBinding = void (DE_CALL_OPENGL*)(GLuint program, GLuint storageBlockIndex,
	GLuint storageBlockBinding);

using GLTexBufferRange = void (DE_CALL_OPENGL*)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset,
	GLsizeiptr size);

using GLTexStorage2DMultisample = void (DE_CALL_OPENGL*)(GLenum target, GLsizei samples, GLenum internalformat,
	GLsizei width, GLsizei height, GLboolean fixedsamplelocations);

using GLTexStorage3DMultisample = void (DE_CALL_OPENGL*)(GLenum target, GLsizei samples, GLenum internalformat,
	GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);

using GLTextureView = void (DE_CALL_OPENGL*)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat,
	GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);

using GLVertexAttribBinding = void (DE_CALL_OPENGL*)(GLuint attribindex, GLuint bindingindex);

using GLVertexAttribFormat = void (DE_CALL_OPENGL*)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized,
	GLuint relativeoffset);

using GLVertexAttribIFormat = void (DE_CALL_OPENGL*)(GLuint attribindex, GLint size, GLenum type,
	GLuint relativeoffset);

using GLVertexAttribLFormat = void (DE_CALL_OPENGL*)(GLuint attribindex, GLint size, GLenum type,
	GLuint relativeoffset);

using GLVertexBindingDivisor = void (DE_CALL_OPENGL*)(GLuint bindingindex, GLuint divisor);


// Version 4.4

#define GL_MAP_PERSISTENT_BIT					   0x0040
#define GL_MAP_COHERENT_BIT						   0x0080
#define GL_DYNAMIC_STORAGE_BIT					   0x0100
#define GL_CLIENT_STORAGE_BIT					   0x0200
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT		   0x00004000
#define GL_QUERY_BUFFER_BARRIER_BIT				   0x00008000
#define GL_BUFFER_IMMUTABLE_STORAGE				   0x821F
#define GL_BUFFER_STORAGE_FLAGS					   0x8220
#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#define GL_MAX_VERTEX_ATTRIB_STRIDE				   0x82E5
#define GL_MIRROR_CLAMP_TO_EDGE					   0x8743
#define GL_TEXTURE_BUFFER_BINDING				   0x8C2A
#define GL_QUERY_BUFFER							   0x9192
#define GL_QUERY_BUFFER_BINDING					   0x9193
#define GL_QUERY_RESULT_NO_WAIT					   0x9194
#define GL_LOCATION_COMPONENT					   0x934A
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX		   0x934B
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE		   0x934C
#define GL_CLEAR_TEXTURE						   0x9365

using GLBindBuffersBase = void (DE_CALL_OPENGL*)(GLenum target, GLuint first, GLsizei count, const GLuint* buffers);

using GLBindBuffersRange = void (DE_CALL_OPENGL*)(GLenum target, GLuint first, GLsizei count, const GLuint* buffers,
	const GLintptr* offsets, const GLsizeiptr* sizes);

using GLBindImageTextures = void (DE_CALL_OPENGL*)(GLuint first, GLsizei count, const GLuint* textures);
using GLBindSamplers = void (DE_CALL_OPENGL*)(GLuint first, GLsizei count, const GLuint* samplers);
using GLBindTextures = void (DE_CALL_OPENGL*)(GLuint first, GLsizei count, const GLuint* textures);

using GLBindVertexBuffers = void (DE_CALL_OPENGL*)(GLuint first, GLsizei count, const GLuint* buffers,
	const GLintptr* offsets, const GLsizei* strides);

using GLBufferStorage = void (DE_CALL_OPENGL*)(GLenum target, GLsizeiptr size, const Void* data, GLbitfield flags);

using GLClearTexImage = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLenum format, GLenum type,
	const Void* data);

using GLClearTexSubImage = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const Void* data);


// Version 4.5

#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT		0x0004
#define GL_CONTEXT_LOST							0x0507
#define GL_TEXTURE_TARGET						0x1006
#define GL_LOSE_CONTEXT_ON_RESET				0x8252
#define GL_GUILTY_CONTEXT_RESET					0x8253
#define GL_INNOCENT_CONTEXT_RESET				0x8254
#define GL_UNKNOWN_CONTEXT_RESET				0x8255
#define GL_RESET_NOTIFICATION_STRATEGY			0x8256
#define GL_NO_RESET_NOTIFICATION				0x8261
#define GL_QUERY_TARGET							0x82EA
#define GL_MAX_CULL_DISTANCES					0x82F9
#define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 0x82FA
#define GL_CONTEXT_RELEASE_BEHAVIOR				0x82FB
#define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH		0x82FC
#define GL_QUERY_WAIT_INVERTED					0x8E17
#define GL_QUERY_NO_WAIT_INVERTED				0x8E18
#define GL_QUERY_BY_REGION_WAIT_INVERTED		0x8E19
#define GL_QUERY_BY_REGION_NO_WAIT_INVERTED		0x8E1A
#define GL_CLIP_ORIGIN							0x935C
#define GL_CLIP_DEPTH_MODE						0x935D
#define GL_NEGATIVE_ONE_TO_ONE					0x935E
#define GL_ZERO_TO_ONE							0x935F

using GLBindTextureUnit = void (DE_CALL_OPENGL*)(GLuint unit, GLuint texture);

using GLBlitNamedFramebuffer = void (DE_CALL_OPENGL*)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0,
	GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask,
	GLenum filter);

using GLCheckNamedFramebufferStatus = GLenum (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum target);

using GLClearNamedBufferData = void (DE_CALL_OPENGL*)(GLuint buffer, GLenum internalformat, GLenum format, GLenum type,
	const Void* data);

using GLClearNamedBufferSubData = void (DE_CALL_OPENGL*)(GLuint buffer, GLenum internalformat, GLintptr offset,
	GLsizeiptr size, GLenum format, GLenum type, const Void* data);

using GLClearNamedFramebufferFI = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum buffer, const GLfloat depth,
	GLint stencil);

using GLClearNamedFramebufferFV = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum buffer, GLint drawbuffer,
	const GLfloat* value);

using GLClearNamedFramebufferIV = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum buffer, GLint drawbuffer,
	const GLint* value);

using GLClearNamedFramebufferUIV = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum buffer, GLint drawbuffer,
	const GLuint* value);

using GLClipControl = void (DE_CALL_OPENGL*)(GLenum origin, GLenum depth);

using GLCompressedTextureSubImage1D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLsizei width,
	GLenum format, GLsizei imageSize, const Void* data);

using GLCompressedTextureSubImage2D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const Void* data);

using GLCompressedTextureSubImage3D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const Void* data);

using GLCopyNamedBufferSubData = void (DE_CALL_OPENGL*)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset,
	GLintptr writeOffset, GLsizeiptr size);

using GLCopyTextureSubImage1D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y,
	GLsizei width);

using GLCopyTextureSubImage2D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLint x, GLint y, GLsizei width, GLsizei height);

using GLCopyTextureSubImage3D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

using GLCreateBuffers = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* buffers);
using GLCreateFramebuffers = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* framebuffers);
using GLCreateProgramPipelines = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* pipelines);
using GLCreateQueries = void (DE_CALL_OPENGL*)(GLenum target, GLsizei n, GLuint* ids);
using GLCreateRenderbuffers = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* renderbuffers);
using GLCreateSamplers = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* samplers);
using GLCreateTextures = void (DE_CALL_OPENGL*)(GLenum target, GLsizei n, GLuint* textures);
using GLCreateTransformFeedbacks = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* ids);
using GLCreateVertexArrays = void (DE_CALL_OPENGL*)(GLsizei n, GLuint* arrays);
using GLDisableVertexArrayAttrib = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint index);
using GLEnableVertexArrayAttrib = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint index);
using GLFlushMappedNamedBufferRange = void (DE_CALL_OPENGL*)(GLuint buffer, GLintptr offset, GLsizeiptr length);
using GLGenerateTextureMipmap = void (DE_CALL_OPENGL*)(GLuint texture);
using GLGetCompressedTextureImage = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLsizei bufSize, Void* pixels);

using GLGetCompressedTextureSubImage = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset,
	GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, Void* pixels);

using GLGetGraphicsResetStatus = GLenum (DE_CALL_OPENGL*)();
using GLGetNamedBufferParameterI64V = void (DE_CALL_OPENGL*)(GLuint buffer, GLenum pname, GLint64* params);
using GLGetNamedBufferParameterIV = void (DE_CALL_OPENGL*)(GLuint buffer, GLenum pname, GLint* params);
using GLGetNamedBufferPointerV = void (DE_CALL_OPENGL*)(GLuint buffer, GLenum pname, Void** params);
using GLGetNamedBufferSubData = void (DE_CALL_OPENGL*)(GLuint buffer, GLintptr offset, GLsizeiptr size, Void* data);

using GLGetNamedFramebufferAttachmentParameterIV = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum attachment,
	GLenum pname, GLint* params);

using GLGetNamedFramebufferParameterIV = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum pname, GLint* param);
using GLGetNamedRenderbufferParameterIV = void (DE_CALL_OPENGL*)(GLuint renderbuffer, GLenum pname, GLint* params);
using GLGetnCompressedTexImage = void (DE_CALL_OPENGL*)(GLenum target, GLint lod, GLsizei bufSize, Void* pixels);

using GLGetnTexImage = void (DE_CALL_OPENGL*)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize,
	Void* pixels);

using GLGetnUniformDV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei bufSize, GLdouble* params);
using GLGetnUniformFV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei bufSize, GLfloat* params);
using GLGetnUniformIV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei bufSize, GLint* params);
using GLGetnUniformUIV = void (DE_CALL_OPENGL*)(GLuint program, GLint location, GLsizei bufSize, GLuint* params);
using GLGetQueryBufferObjectI64V = void (DE_CALL_OPENGL*)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
using GLGetQueryBufferObjectIV = void (DE_CALL_OPENGL*)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
using GLGetQueryBufferObjectUI64V = void (DE_CALL_OPENGL*)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
using GLGetQueryBufferObjectUIV = void (DE_CALL_OPENGL*)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);

using GLGetTextureImage = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLenum format, GLenum type,
	GLsizei bufSize, Void* pixels);

using GLGetTextureLevelParameterFV = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLenum pname,
	GLfloat* params);

using GLGetTextureLevelParameterIV = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLenum pname, GLint* params);
using GLGetTextureParameterFV = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, GLfloat* params);
using GLGetTextureParameterIIV = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, GLint* params);
using GLGetTextureParameterIV = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, GLint* params);
using GLGetTextureParameterIUIV = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, GLuint* params);

using GLGetTextureSubImage = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize,
	Void* pixels);

using GLGetTransformFeedbackI64_V = void (DE_CALL_OPENGL*)(GLuint xfb, GLenum pname, GLuint index, GLint64* param);
using GLGetTransformFeedbackIV = void (DE_CALL_OPENGL*)(GLuint xfb, GLenum pname, GLint* param);
using GLGetTransformFeedbackI_V = void (DE_CALL_OPENGL*)(GLuint xfb, GLenum pname, GLuint index, GLint* param);
using GLGetVertexArrayIndexed64IV = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint index, GLenum pname, GLint64* param);
using GLGetVertexArrayIndexedIV = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint index, GLenum pname, GLint* param);
using GLGetVertexArrayIV = void (DE_CALL_OPENGL*)(GLuint vaobj, GLenum pname, GLint* param);

using GLInvalidateNamedFramebufferData = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLsizei numAttachments,
	const GLenum* attachments);

using GLInvalidateNamedFramebufferSubData = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLsizei numAttachments,
	const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);

using GLMapNamedBuffer = Void* (DE_CALL_OPENGL*)(GLuint buffer, GLenum access);

using GLMapNamedBufferRange = Void* (DE_CALL_OPENGL*)(GLuint buffer, GLintptr offset, GLsizeiptr length,
	GLbitfield access);

using GLMemoryBarrierByRegion = void (DE_CALL_OPENGL*)(GLbitfield barriers);
using GLNamedBufferData = void (DE_CALL_OPENGL*)(GLuint buffer, GLsizeiptr size, const Void* data, GLenum usage);

using GLNamedBufferStorage = void (DE_CALL_OPENGL*)(GLuint buffer, GLsizeiptr size, const Void* data,
	GLbitfield flags);

using GLNamedBufferSubData = void (DE_CALL_OPENGL*)(GLuint buffer, GLintptr offset, GLsizeiptr size, const Void* data);
using GLNamedFramebufferDrawBuffer = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum buf);
using GLNamedFramebufferDrawBuffers = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLsizei n, const GLenum* bufs);
using GLNamedFramebufferParameterI = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum pname, GLint param);
using GLNamedFramebufferReadBuffer = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum src);

using GLNamedFramebufferRenderbuffer = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum attachment,
	GLenum renderbuffertarget, GLuint renderbuffer);

using GLNamedFramebufferTexture = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum attachment, GLuint texture,
	GLint level);

using GLNamedFramebufferTextureLayer = void (DE_CALL_OPENGL*)(GLuint framebuffer, GLenum attachment, GLuint texture,
	GLint level, GLint layer);

using GLNamedRenderbufferStorage = void (DE_CALL_OPENGL*)(GLuint renderbuffer, GLenum internalformat, GLsizei width,
	GLsizei height);

using GLNamedRenderbufferStorageMultisample = void (DE_CALL_OPENGL*)(GLuint renderbuffer, GLsizei samples,
	GLenum internalformat, GLsizei width, GLsizei height);

using GLReadnPixels = void (DE_CALL_OPENGL*)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format,
	GLenum type, GLsizei bufSize, Void* data);

using GLTransformFeedbackBufferBase = void (DE_CALL_OPENGL*)(GLuint xfb, GLuint index, GLuint buffer);

using GLTransformFeedbackBufferRange = void (DE_CALL_OPENGL*)(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset,
	GLsizeiptr size);

using GLTextureBarrier = void (DE_CALL_OPENGL*)();
using GLTextureBuffer = void (DE_CALL_OPENGL*)(GLuint texture, GLenum internalformat, GLuint buffer);

using GLTextureBufferRange = void (DE_CALL_OPENGL*)(GLuint texture, GLenum internalformat, GLuint buffer,
	GLintptr offset, GLsizeiptr size);

using GLTextureParameterF = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, GLfloat param);
using GLTextureParameterFV = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, const GLfloat* param);
using GLTextureParameterI = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, GLint param);
using GLTextureParameterIIV = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, const GLint* params);
using GLTextureParameterIUIV = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, const GLuint* params);
using GLTextureParameterIV = void (DE_CALL_OPENGL*)(GLuint texture, GLenum pname, const GLint* param);

using GLTextureStorage1D = void (DE_CALL_OPENGL*)(GLuint texture, GLsizei levels, GLenum internalformat,
	GLsizei width);

using GLTextureStorage2D = void (DE_CALL_OPENGL*)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width,
	GLsizei height);

using GLTextureStorage2DMultisample = void (DE_CALL_OPENGL*)(GLuint texture, GLsizei samples, GLenum internalformat,
	GLsizei width, GLsizei height, GLboolean fixedsamplelocations);

using GLTextureStorage3D = void (DE_CALL_OPENGL*)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width,
	GLsizei height, GLsizei depth);

using GLTextureStorage3DMultisample = void (DE_CALL_OPENGL*)(GLuint texture, GLsizei samples, GLenum internalformat,
	GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);

using GLTextureSubImage1D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLsizei width,
	GLenum format, GLenum type, const Void* pixels);

using GLTextureSubImage2D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height, GLenum format, GLenum type, const Void* pixels);

using GLTextureSubImage3D = void (DE_CALL_OPENGL*)(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
	GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const Void* pixels);

using GLUnmapNamedBuffer = GLboolean (DE_CALL_OPENGL*)(GLuint buffer);
using GLVertexArrayAttribBinding = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);

using GLVertexArrayAttribFormat = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
	GLboolean normalized, GLuint relativeoffset);

using GLVertexArrayAttribIFormat = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
	GLuint relativeoffset);

using GLVertexArrayAttribLFormat = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
	GLuint relativeoffset);

using GLVertexArrayBindingDivisor = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint bindingindex, GLuint divisor);
using GLVertexArrayElementBuffer = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint buffer);

using GLVertexArrayVertexBuffer = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint bindingindex, GLuint buffer,
	GLintptr offset, GLsizei stride);

using GLVertexArrayVertexBuffers = void (DE_CALL_OPENGL*)(GLuint vaobj, GLuint first, GLsizei count,
	const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides);


// Function declarations

extern "C"
{
	// Version 1.0

	void DE_CALL_OPENGL glBlendFunc(GLenum sfactor, GLenum dfactor);
	void DE_CALL_OPENGL glClear(GLbitfield mask);
	void DE_CALL_OPENGL glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void DE_CALL_OPENGL glClearDepth(GLdouble depth);
	void DE_CALL_OPENGL glClearStencil(GLint s);
	void DE_CALL_OPENGL glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void DE_CALL_OPENGL glCullFace(GLenum mode);
	void DE_CALL_OPENGL glDepthFunc(GLenum func);
	void DE_CALL_OPENGL glDepthMask(GLboolean flag);
	void DE_CALL_OPENGL glDepthRange(GLdouble near, GLdouble far);
	void DE_CALL_OPENGL glDisable(GLenum cap);
	void DE_CALL_OPENGL glDrawBuffer(GLenum buf);
	void DE_CALL_OPENGL glEnable(GLenum cap);
	void DE_CALL_OPENGL glFinish();
	void DE_CALL_OPENGL glFlush();
	void DE_CALL_OPENGL glFrontFace(GLenum mode);
	void DE_CALL_OPENGL glGetBooleanv(GLenum pname, GLboolean* data);
	void DE_CALL_OPENGL glGetDoublev(GLenum pname, GLdouble* data);
	GLenum DE_CALL_OPENGL glGetError();
	void DE_CALL_OPENGL glGetFloatv(GLenum pname, GLfloat* data);
	void DE_CALL_OPENGL glGetIntegerv(GLenum pname, GLint* data);
	const GLubyte* DE_CALL_OPENGL glGetString(GLenum name);
	void DE_CALL_OPENGL glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, Void* pixels);
	void DE_CALL_OPENGL glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params);
	void DE_CALL_OPENGL glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params);
	void DE_CALL_OPENGL glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params);
	void DE_CALL_OPENGL glGetTexParameteriv(GLenum target, GLenum pname, GLint* params);
	void DE_CALL_OPENGL glHint(GLenum target, GLenum mode);
	GLboolean DE_CALL_OPENGL glIsEnabled(GLenum cap);
	void DE_CALL_OPENGL glLineWidth(GLfloat width);
	void DE_CALL_OPENGL glLogicOp(GLenum opcode);
	void DE_CALL_OPENGL glPixelStoref(GLenum pname, GLfloat param);
	void DE_CALL_OPENGL glPixelStorei(GLenum pname, GLint param);
	void DE_CALL_OPENGL glPointSize(GLfloat size);
	void DE_CALL_OPENGL glPolygonMode(GLenum face, GLenum mode);
	void DE_CALL_OPENGL glReadBuffer(GLenum src);

	void DE_CALL_OPENGL glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type,
		Void* pixels);

	void DE_CALL_OPENGL glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
	void DE_CALL_OPENGL glStencilFunc(GLenum func, GLint ref, GLuint mask);
	void DE_CALL_OPENGL glStencilMask(GLuint mask);
	void DE_CALL_OPENGL glStencilOp(GLenum fail, GLenum zfail, GLenum zpass);

	void DE_CALL_OPENGL glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border,
		GLenum format, GLenum type, const Void* pixels);

	void DE_CALL_OPENGL glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
		GLint border, GLenum format, GLenum type, const Void* pixels);

	void DE_CALL_OPENGL glTexParameterf(GLenum target, GLenum pname, GLfloat param);
	void DE_CALL_OPENGL glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params);
	void DE_CALL_OPENGL glTexParameteri(GLenum target, GLenum pname, GLint param);
	void DE_CALL_OPENGL glTexParameteriv(GLenum target, GLenum pname, const GLint* params);
	void DE_CALL_OPENGL glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	// Version 1.1

	void DE_CALL_OPENGL glBindTexture(GLenum target, GLuint texture);

	void DE_CALL_OPENGL glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
		GLsizei width, GLint border);

	void DE_CALL_OPENGL glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
		GLsizei width, GLsizei height, GLint border);

	void DE_CALL_OPENGL glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y,
		GLsizei width);

	void DE_CALL_OPENGL glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y,
		GLsizei width, GLsizei height);

	void DE_CALL_OPENGL glDeleteTextures(GLsizei n, const GLuint* textures);
	void DE_CALL_OPENGL glDrawArrays(GLenum mode, GLint first, GLsizei count);
	void DE_CALL_OPENGL glDrawElements(GLenum mode, GLsizei count, GLenum type, const Void* indices);
	void DE_CALL_OPENGL glGenTextures(GLsizei n, GLuint* textures);
	void DE_CALL_OPENGL glGetPointerv(GLenum pname, Void** params);
	GLboolean DE_CALL_OPENGL glIsTexture(GLuint texture);
	void DE_CALL_OPENGL glPolygonOffset(GLfloat factor, GLfloat units);

	void DE_CALL_OPENGL glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format,
		GLenum type, const Void* pixels);

	void DE_CALL_OPENGL glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
		GLsizei height, GLenum format, GLenum type, const Void* pixels);
}
