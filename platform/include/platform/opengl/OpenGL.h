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

// Version 1.0

using GLbitfield = Uint32;
using GLboolean	 = Uint8;
using GLdouble	 = Float64;
using GLenum	 = Uint32;
using GLfloat	 = Float32;
using GLint		 = Int32;
using GLsizei	 = Int32;
using GLubyte	 = Byte;
using GLuint	 = Uint32;

using GLBlendFunc = void (*)(GLenum sfactor, GLenum dfactor);
using GLClear = void (*)(GLbitfield mask);
using GLClearColor = void (*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
using GLClearDepth = void (*)(GLdouble depth);
using GLClearStencil = void (*)(GLint s);
using GLColorMask = void (*)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
using GLCullFace = void (*)(GLenum mode);
using GLDepthFunc = void (*)(GLenum func);
using GLDepthMask = void (*)(GLboolean flag);
using GLDepthRange = void (*)(GLdouble near, GLdouble far);
using GLDisable = void (*)(GLenum cap);
using GLDrawBuffer = void (*)(GLenum buf);
using GLEnable = void (*)(GLenum cap);
using GLFinish = void (*)();
using GLFlush = void (*)();
using GLFrontFace = void (*)(GLenum mode);
using GLGetBooleanV = void (*)(GLenum pname, GLboolean* data);
using GLGetDoubleV = void (*)(GLenum pname, GLdouble* data);
using GLGetError = GLenum (*)();
using GLGetFloatV = void (*)(GLenum pname, GLfloat* data);
using GLGetIntegerV = void (*)(GLenum pname, GLint* data);
using GLGetString = const GLubyte* (*)(GLenum name);
using GLGetTexImage = void (*)(GLenum target, GLint level, GLenum format, GLenum type, Void* pixels);
using GLGetTexLevelParameterFV = void (*)(GLenum target, GLint level, GLenum pname, GLfloat* params);
using GLGetTexLevelParameterIV = void (*)(GLenum target, GLint level, GLenum pname, GLint* params);
using GLGetTexParameterFV = void (*)(GLenum target, GLenum pname, GLfloat* params);
using GLGetTexParameterIV = void (*)(GLenum target, GLenum pname, GLint* params);
using GLHint = void (*)(GLenum target, GLenum mode);
using GLIsEnabled = GLboolean (*)(GLenum cap);
using GLLineWidth = void (*)(GLfloat width);
using GLLogicOp = void (*)(GLenum opcode);
using GLPixelStoreF = void (*)(GLenum pname, GLfloat param);
using GLPixelStoreI = void (*)(GLenum pname, GLint param);
using GLPointSize = void (*)(GLfloat size);
using GLPolygonMode = void (*)(GLenum face, GLenum mode);
using GLReadBuffer = void (*)(GLenum src);

using GLReadPixels = void (*)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type,
	Void* pixels);

using GLScissor = void (*)(GLint x, GLint y, GLsizei width, GLsizei height);
using GLStencilFunc = void (*)(GLenum func, GLint ref, GLuint mask);
using GLStencilMask = void (*)(GLuint mask);
using GLStencilOp = void (*)(GLenum fail, GLenum zfail, GLenum zpass);

using GLTexImage1D = void (*)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border,
	GLenum format, GLenum type, const Void* pixels);

using GLTexImage2D = void (*)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
	GLint border, GLenum format, GLenum type, const Void* pixels);

using GLTexParameterF = void (*)(GLenum target, GLenum pname, GLfloat param);
using GLTexParameterFV = void (*)(GLenum target, GLenum pname, const GLfloat* params);
using GLTexParameterI = void (*)(GLenum target, GLenum pname, GLint param);
using GLTexParameterIV = void (*)(GLenum target, GLenum pname, const GLint* params);
using GLViewport = void (*)(GLint x, GLint y, GLsizei width, GLsizei height);


// Version 1.1

using GLclampf = Float32;
using GLclampd = Float64;

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

using GLBindTexture = void (*)(GLenum target, GLuint texture);

using GLCopyTexImage1D = void (*)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width,
	GLint border);

using GLCopyTexImage2D = void (*)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width,
	GLsizei height, GLint border);

using GLCopyTexSubImage1D = void (*)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);

using GLCopyTexSubImage2D = void (*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y,
	GLsizei width, GLsizei height);

using GLDeleteTextures = void (*)(GLsizei n, const GLuint* textures);
using GLDrawArrays = void (*)(GLenum mode, GLint first, GLsizei count);
using GLDrawElements = void (*)(GLenum mode, GLsizei count, GLenum type, const Void* indices);
using GLGenTextures = void (*)(GLsizei n, GLuint* textures);
using GLGetPointerV = void (*)(GLenum pname, Void** params);
using GLIsTexture = GLboolean (*)(GLuint texture);
using GLPolygonOffset = void (*)(GLfloat factor, GLfloat units);

using GLTexSubImage1D = void (*)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type,
	const Void* pixels);

using GLTexSubImage2D = void (*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
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

using GLCopyTexSubImage3D = void (*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
	GLint x, GLint y, GLsizei width, GLsizei height);

using GLDrawRangeElements = void (*)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type,
	const Void* indices);

using GLTexImage3D = void (*)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
	GLsizei depth, GLint border, GLenum format, GLenum type, const Void* pixels);

using GLTexSubImage3D = void (*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
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

using GLActiveTexture = void (*)(GLenum texture);

using GLCompressedTexImage1D = void (*)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border,
	GLsizei imageSize, const Void* data);

using GLCompressedTexImage2D = void (*)(GLenum target, GLint level, GLenum internalformat, GLsizei width,
	GLsizei height, GLint border, GLsizei imageSize, const Void* data);

using GLCompressedTexImage3D = void (*)(GLenum target, GLint level, GLenum internalformat, GLsizei width,
	GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const Void* data);

using GLCompressedTexSubImage1D = void (*)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format,
	GLsizei imageSize, const Void* data);

using GLCompressedTexSubImage2D = void (*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
	GLsizei height, GLenum format, GLsizei imageSize, const Void* data);

using GLCompressedTexSubImage3D = void (*)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
	GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const Void* data);

using GLGetCompressedTexImage = void (*)(GLenum target, GLint level, Void* img);
using GLSampleCoverage = void (*)(GLfloat value, GLboolean invert);


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

using GLBlendColor = void (*)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
using GLBlendEquation = void (*)(GLenum mode);
using GLBlendFuncSeparate = void (*)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
using GLMultiDrawArrays = void (*)(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount);

using GLMultiDrawElements = void (*)(GLenum mode, const GLsizei* count, GLenum type, const Void* const* indices,
	GLsizei drawcount);

using GLPointParameterF = void (*)(GLenum pname, GLfloat param);
using GLPointParameterFV = void (*)(GLenum pname, const GLfloat* params);
using GLPointParameterI = void (*)(GLenum pname, GLint param);
using GLPointParameterIV = void (*)(GLenum pname, const GLint* params);


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

using GLBeginQuery = void (*)(GLenum target, GLuint id);
using GLBindBuffer = void (*)(GLenum target, GLuint buffer);
using GLBufferData = void (*)(GLenum target, GLsizeiptr size, const Void* data, GLenum usage);
using GLBufferSubData = void (*)(GLenum target, GLintptr offset, GLsizeiptr size, const Void* data);
using GLDeleteBuffers = void (*)(GLsizei n, const GLuint* buffers);
using GLDeleteQueries = void (*)(GLsizei n, const GLuint* ids);
using GLEndQuery = void (*)(GLenum target);
using GLGenBuffers = void (*)(GLsizei n, GLuint* buffers);
using GLGenQueries = void (*)(GLsizei n, GLuint* ids);
using GLGetBufferParameterIV = void (*)(GLenum target, GLenum pname, GLint* params);
using GLGetBufferPointerV = void (*)(GLenum target, GLenum pname, Void** params);
using GLGetBufferSubData = void (*)(GLenum target, GLintptr offset, GLsizeiptr size, Void* data);
using GLGetQueryIV = void (*)(GLenum target, GLenum pname, GLint* params);
using GLGetQueryObjectIV = void (*)(GLuint id, GLenum pname, GLint* params);
using GLGetQueryObjectUIV = void (*)(GLuint id, GLenum pname, GLuint* params);
using GLIsBuffer = GLboolean (*)(GLuint buffer);
using GLIsQuery = GLboolean (*)(GLuint id);
using GLMapBuffer = Void* (*)(GLenum target, GLenum access);
using GLUnmapBuffer = GLboolean (*)(GLenum target);


// Version 2.0

using GLbyte   = Char8;
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

using GLAttachShader = void (*)(GLuint program, GLuint shader);
using GLBindAttribLocation = void (*)(GLuint program, GLuint index, const GLchar* name);
using GLBlendEquationSeparate = void (*)(GLenum modeRGB, GLenum modeAlpha);
using GLCompileShader = void (*)(GLuint shader);
using GLCreateProgram = GLuint (*)();
using GLCreateShader = GLuint (*)(GLenum type);
using GLDeleteProgram = void (*)(GLuint program);
using GLDeleteShader = void (*)(GLuint shader);
using GLDetachShader = void (*)(GLuint program, GLuint shader);
using GLDisableVertexAttribArray = void (*)(GLuint index);
using GLDrawBuffers = void (*)(GLsizei n, const GLenum* bufs);
using GLEnableVertexAttribArray = void (*)(GLuint index);

using GLGetActiveAttrib = void (*)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size,
	GLenum* type, GLchar* name);

using GLGetActiveUniform = void (*)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size,
	GLenum* type, GLchar* name);

using GLGetAttachedShaders = void (*)(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
using GLGetAttribLocation = GLint (*)(GLuint program, const GLchar* name);
using GLGetProgramInfoLog = void (*)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
using GLGetProgramIV = void (*)(GLuint program, GLenum pname, GLint* params);
using GLGetShaderInfoLog = void (*)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
using GLGetShaderIV = void (*)(GLuint shader, GLenum pname, GLint* params);
using GLGetShaderSource = void (*)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);
using GLGetUniformFV = void (*)(GLuint program, GLint location, GLfloat* params);
using GLGetUniformIV = void (*)(GLuint program, GLint location, GLint* params);
using GLGetUniformLocation = GLint (*)(GLuint program, const GLchar* name);
using GLGetVertexAttribDV = void (*)(GLuint index, GLenum pname, GLdouble* params);
using GLGetVertexAttribFV = void (*)(GLuint index, GLenum pname, GLfloat* params);
using GLGetVertexAttribIV = void (*)(GLuint index, GLenum pname, GLint* params);
using GLGetVertexAttribPointerV = void (*)(GLuint index, GLenum pname, Void** pointer);
using GLIsProgram = GLboolean (*)(GLuint program);
using GLIsShader = GLboolean (*)(GLuint shader);
using GLLinkProgram = void (*)(GLuint program);
using GLShaderSource = void (*)(GLuint shader, GLsizei count, const GLchar* const*string, const GLint* length);
using GLStencilFuncSeparate = void (*)(GLenum face, GLenum func, GLint ref, GLuint mask);
using GLStencilMaskSeparate = void (*)(GLenum face, GLuint mask);
using GLStencilOpSeparate = void (*)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
using GLUniform1F = void (*)(GLint location, GLfloat v0);
using GLUniform1FV = void (*)(GLint location, GLsizei count, const GLfloat* value);
using GLUniform1I = void (*)(GLint location, GLint v0);
using GLUniform1IV = void (*)(GLint location, GLsizei count, const GLint* value);
using GLUniform2F = void (*)(GLint location, GLfloat v0, GLfloat v1);
using GLUniform2FV = void (*)(GLint location, GLsizei count, const GLfloat* value);
using GLUniform2I = void (*)(GLint location, GLint v0, GLint v1);
using GLUniform2IV = void (*)(GLint location, GLsizei count, const GLint* value);
using GLUniform3F = void (*)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
using GLUniform3FV = void (*)(GLint location, GLsizei count, const GLfloat* value);
using GLUniform3I = void (*)(GLint location, GLint v0, GLint v1, GLint v2);
using GLUniform3IV = void (*)(GLint location, GLsizei count, const GLint* value);
using GLUniform4F = void (*)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
using GLUniform4FV = void (*)(GLint location, GLsizei count, const GLfloat* value);
using GLUniform4I = void (*)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
using GLUniform4IV = void (*)(GLint location, GLsizei count, const GLint* value);
using GLUniformMatrix2FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
using GLUniformMatrix3FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
using GLUniformMatrix4FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
using GLUseProgram = void (*)(GLuint program);
using GLValidateProgram = void (*)(GLuint program);
using GLVertexAttrib1D = void (*)(GLuint index, GLdouble x);
using GLVertexAttrib1DV = void (*)(GLuint index, const GLdouble* v);
using GLVertexAttrib1F = void (*)(GLuint index, GLfloat x);
using GLVertexAttrib1FV = void (*)(GLuint index, const GLfloat* v);
using GLVertexAttrib1S = void (*)(GLuint index, GLshort x);
using GLVertexAttrib1SV = void (*)(GLuint index, const GLshort* v);
using GLVertexAttrib2D = void (*)(GLuint index, GLdouble x, GLdouble y);
using GLVertexAttrib2DV = void (*)(GLuint index, const GLdouble* v);
using GLVertexAttrib2F = void (*)(GLuint index, GLfloat x, GLfloat y);
using GLVertexAttrib2FV = void (*)(GLuint index, const GLfloat* v);
using GLVertexAttrib2S = void (*)(GLuint index, GLshort x, GLshort y);
using GLVertexAttrib2SV = void (*)(GLuint index, const GLshort* v);
using GLVertexAttrib3D = void (*)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
using GLVertexAttrib3DV = void (*)(GLuint index, const GLdouble* v);
using GLVertexAttrib3F = void (*)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
using GLVertexAttrib3FV = void (*)(GLuint index, const GLfloat* v);
using GLVertexAttrib3S = void (*)(GLuint index, GLshort x, GLshort y, GLshort z);
using GLVertexAttrib3SV = void (*)(GLuint index, const GLshort* v);
using GLVertexAttrib4BV = void (*)(GLuint index, const GLbyte* v);
using GLVertexAttrib4D = void (*)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
using GLVertexAttrib4DV = void (*)(GLuint index, const GLdouble* v);
using GLVertexAttrib4F = void (*)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
using GLVertexAttrib4FV = void (*)(GLuint index, const GLfloat* v);
using GLVertexAttrib4IV = void (*)(GLuint index, const GLint* v);
using GLVertexAttrib4NBV = void (*)(GLuint index, const GLbyte* v);
using GLVertexAttrib4NIV = void (*)(GLuint index, const GLint* v);
using GLVertexAttrib4NSV = void (*)(GLuint index, const GLshort* v);
using GLVertexAttrib4NUB = void (*)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
using GLVertexAttrib4NUBV = void (*)(GLuint index, const GLubyte* v);
using GLVertexAttrib4NUIV = void (*)(GLuint index, const GLuint* v);
using GLVertexAttrib4NUSV = void (*)(GLuint index, const GLushort* v);
using GLVertexAttrib4S = void (*)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
using GLVertexAttrib4SV = void (*)(GLuint index, const GLshort* v);
using GLVertexAttrib4UBV = void (*)(GLuint index, const GLubyte* v);
using GLVertexAttrib4UIV = void (*)(GLuint index, const GLuint* v);
using GLVertexAttrib4USV = void (*)(GLuint index, const GLushort* v);

using GLVertexAttribPointer = void (*)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
	const Void* pointer);


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

using GLUniformMatrix2x3FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
using GLUniformMatrix2x4FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
using GLUniformMatrix3x2FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
using GLUniformMatrix3x4FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
using GLUniformMatrix4x2FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
using GLUniformMatrix4x3FV = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);


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

using GLBeginConditionalRender = void (*)(GLuint id, GLenum mode);
using GLBeginTransformFeedback = void (*)(GLenum primitiveMode);
using GLBindBufferBase = void (*)(GLenum target, GLuint index, GLuint buffer);
using GLBindBufferRange = void (*)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
using GLBindFragDataLocation = void (*)(GLuint program, GLuint color, const GLchar* name);
using GLBindFramebuffer = void (*)(GLenum target, GLuint framebuffer);
using GLBindRenderbuffer = void (*)(GLenum target, GLuint renderbuffer);
using GLBindVertexArray = void (*)(GLuint array);

using GLBlitFramebuffer = void (*)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0,
	GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

using GLCheckFramebufferStatus = GLenum (*)(GLenum target);
using GLClampColor = void (*)(GLenum target, GLenum clamp);
using GLClearBufferFV = void (*)(GLenum buffer, GLint drawbuffer, const GLfloat* value);
using GLClearBufferI = void (*)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
using GLClearBufferIV = void (*)(GLenum buffer, GLint drawbuffer, const GLint* value);
using GLClearBufferUIV = void (*)(GLenum buffer, GLint drawbuffer, const GLuint* value);
using GLColorMaskI = void (*)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
using GLDeleteFramebuffers = void (*)(GLsizei n, const GLuint* framebuffers);
using GLDeleteRenderbuffers = void (*)(GLsizei n, const GLuint* renderbuffers);
using GLDeleteVertexArrays = void (*)(GLsizei n, const GLuint* arrays);
using GLDisableI = void (*)(GLenum target, GLuint index);
using GLEnableI = void (*)(GLenum target, GLuint index);
using GLEndConditionalRender = void (*)();
using GLEndTransformFeedback = void (*)();
using GLFlushMappedBufferRange = void (*)(GLenum target, GLintptr offset, GLsizeiptr length);

using GLFramebufferRenderbuffer = void (*)(GLenum target, GLenum attachment, GLenum renderbuffertarget,
	GLuint renderbuffer);

using GLFramebufferTexture1D = void (*)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
	GLint level);

using GLFramebufferTexture2D = void (*)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
	GLint level);

using GLFramebufferTexture3D = void (*)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
	GLint level, GLint zoffset);

using GLFramebufferTextureLayer = void (*)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
using GLGenerateMipmap = void (*)(GLenum target);
using GLGenFramebuffers = void (*)(GLsizei n, GLuint* framebuffers);
using GLGenRenderbuffers = void (*)(GLsizei n, GLuint* renderbuffers);
using GLGenVertexArrays = void (*)(GLsizei n, GLuint* arrays);
using GLGetBooleanI_V = void (*)(GLenum target, GLuint index, GLboolean* data);
using GLGetFragDataLocation = GLint (*)(GLuint program, const GLchar* name);
using GLGetFramebufferAttachmentParameterIV = void (*)(GLenum target, GLenum attachment, GLenum pname, GLint* params);
using GLGetIntegerI_V = void (*)(GLenum target, GLuint index, GLint* data);
using GLGetRenderbufferParameterIV = void (*)(GLenum target, GLenum pname, GLint* params);
using GLGetStringI = const GLubyte* (*)(GLenum name, GLuint index);
using GLGetTexParameterIIV = void (*)(GLenum target, GLenum pname, GLint* params);
using GLGetTexParameterIUIV = void (*)(GLenum target, GLenum pname, GLuint* params);

using GLGetTransformFeedbackVarying = void (*)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length,
	GLsizei* size, GLenum* type, GLchar* name);

using GLGetUniformUIV = void (*)(GLuint program, GLint location, GLuint* params);
using GLGetVertexAttribIIV = void (*)(GLuint index, GLenum pname, GLint* params);
using GLGetVertexAttribIUIV = void (*)(GLuint index, GLenum pname, GLuint* params);
using GLIsEnabledI = GLboolean (*)(GLenum target, GLuint index);
using GLIsFramebuffer = GLboolean (*)(GLuint framebuffer);
using GLIsRenderbuffer = GLboolean (*)(GLuint renderbuffer);
using GLIsVertexArray = GLboolean (*)(GLuint array);
using GLMapBufferRange = Void* (*)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
using GLRenderbufferStorage = void (*)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);

using GLRenderbufferStorageMultisample = void (*)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width,
	GLsizei height);

using GLTexParameterIIV = void (*)(GLenum target, GLenum pname, const GLint* params);
using GLTexParameterIUIV = void (*)(GLenum target, GLenum pname, const GLuint* params);

using GLTransformFeedbackVaryings = void (*)(GLuint program, GLsizei count, const GLchar* const*varyings,
	GLenum bufferMode);

using GLUniform1UI = void (*)(GLint location, GLuint v0);
using GLUniform1UIV = void (*)(GLint location, GLsizei count, const GLuint* value);
using GLUniform2UI = void (*)(GLint location, GLuint v0, GLuint v1);
using GLUniform2UIV = void (*)(GLint location, GLsizei count, const GLuint* value);
using GLUniform3UI = void (*)(GLint location, GLuint v0, GLuint v1, GLuint v2);
using GLUniform3UIV = void (*)(GLint location, GLsizei count, const GLuint* value);
using GLUniform4UI = void (*)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
using GLUniform4UIV = void (*)(GLint location, GLsizei count, const GLuint* value);
using GLVertexAttribI1I = void (*)(GLuint index, GLint x);
using GLVertexAttribI1IV = void (*)(GLuint index, const GLint* v);
using GLVertexAttribI1UI = void (*)(GLuint index, GLuint x);
using GLVertexAttribI1UIV = void (*)(GLuint index, const GLuint* v);
using GLVertexAttribI2I = void (*)(GLuint index, GLint x, GLint y);
using GLVertexAttribI2IV = void (*)(GLuint index, const GLint* v);
using GLVertexAttribI2UI = void (*)(GLuint index, GLuint x, GLuint y);
using GLVertexAttribI2UIV = void (*)(GLuint index, const GLuint* v);
using GLVertexAttribI3I = void (*)(GLuint index, GLint x, GLint y, GLint z);
using GLVertexAttribI3IV = void (*)(GLuint index, const GLint* v);
using GLVertexAttribI3UI = void (*)(GLuint index, GLuint x, GLuint y, GLuint z);
using GLVertexAttribI3UIV = void (*)(GLuint index, const GLuint* v);
using GLVertexAttribI4BV = void (*)(GLuint index, const GLbyte* v);
using GLVertexAttribI4I = void (*)(GLuint index, GLint x, GLint y, GLint z, GLint w);
using GLVertexAttribI4IV = void (*)(GLuint index, const GLint* v);
using GLVertexAttribI4SV = void (*)(GLuint index, const GLshort* v);
using GLVertexAttribI4UBV = void (*)(GLuint index, const GLubyte* v);
using GLVertexAttribI4UI = void (*)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
using GLVertexAttribI4UIV = void (*)(GLuint index, const GLuint* v);
using GLVertexAttribI4USV = void (*)(GLuint index, const GLushort* v);
using GLVertexAttribIPointer = void (*)(GLuint index, GLint size, GLenum type, GLsizei stride, const Void* pointer);


// Function declarations

#ifndef APIENTRY
#define APIENTRY __stdcall
#endif

extern "C"
{
	// Version 1.0

	void APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor);
	void APIENTRY glClear(GLbitfield mask);
	void APIENTRY glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void APIENTRY glClearDepth(GLdouble depth);
	void APIENTRY glClearStencil(GLint s);
	void APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void APIENTRY glCullFace(GLenum mode);
	void APIENTRY glDepthFunc(GLenum func);
	void APIENTRY glDepthMask(GLboolean flag);
	void APIENTRY glDepthRange(GLdouble near, GLdouble far);
	void APIENTRY glDisable(GLenum cap);
	void APIENTRY glDrawBuffer(GLenum buf);
	void APIENTRY glEnable(GLenum cap);
	void APIENTRY glFinish();
	void APIENTRY glFlush();
	void APIENTRY glFrontFace(GLenum mode);
	void APIENTRY glGetBooleanv(GLenum pname, GLboolean* data);
	void APIENTRY glGetDoublev(GLenum pname, GLdouble* data);
	GLenum APIENTRY glGetError();
	void APIENTRY glGetFloatv(GLenum pname, GLfloat* data);
	void APIENTRY glGetIntegerv(GLenum pname, GLint* data);
	const GLubyte* APIENTRY glGetString(GLenum name);
	void APIENTRY glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, Void* pixels);
	void APIENTRY glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params);
	void APIENTRY glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params);
	void APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params);
	void APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint* params);
	void APIENTRY glHint(GLenum target, GLenum mode);
	GLboolean APIENTRY glIsEnabled(GLenum cap);
	void APIENTRY glLineWidth(GLfloat width);
	void APIENTRY glLogicOp(GLenum opcode);
	void APIENTRY glPixelStoref(GLenum pname, GLfloat param);
	void APIENTRY glPixelStorei(GLenum pname, GLint param);
	void APIENTRY glPointSize(GLfloat size);
	void APIENTRY glPolygonMode(GLenum face, GLenum mode);
	void APIENTRY glReadBuffer(GLenum src);

	void APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type,
		Void* pixels);

	void APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
	void APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask);
	void APIENTRY glStencilMask(GLuint mask);
	void APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass);

	void APIENTRY glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border,
		GLenum format, GLenum type, const Void* pixels);

	void APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
		GLint border, GLenum format, GLenum type, const Void* pixels);

	void APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param);
	void APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params);
	void APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param);
	void APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint* params);
	void APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	// Version 1.1

	void APIENTRY glBindTexture(GLenum target, GLuint texture);

	void APIENTRY glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width,
		GLint border);

	void APIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width,
		GLsizei height, GLint border);

	void APIENTRY glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);

	void APIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y,
		GLsizei width, GLsizei height);

	void APIENTRY glDeleteTextures(GLsizei n, const GLuint* textures);
	void APIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count);
	void APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const Void* indices);
	void APIENTRY glGenTextures(GLsizei n, GLuint* textures);
	void APIENTRY glGetPointerv(GLenum pname, Void* *params);
	GLboolean APIENTRY glIsTexture(GLuint texture);
	void APIENTRY glPolygonOffset(GLfloat factor, GLfloat units);

	void APIENTRY glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type,
		const Void* pixels);

	void APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
		GLsizei height, GLenum format, GLenum type, const Void* pixels);
}

#undef APIENTRY
