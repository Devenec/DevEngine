/**
 * @file platform/wgl/WGL.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <platform/wgl/WGL.h>

WGLChoosePixelFormatARB wglChoosePixelFormatARB = nullptr;
WGLCreateContextAttribsARB wglCreateContextAttribsARB = nullptr;
WGLGetExtensionsStringARB wglGetExtensionsStringARB = nullptr;
WGLGetPixelFormatAttribFVARB wglGetPixelFormatAttribfvARB = nullptr;
WGLGetPixelFormatAttribIVARB wglGetPixelFormatAttribivARB = nullptr;
WGLGetSwapIntervalEXT wglGetSwapIntervalEXT = nullptr;
WGLSwapIntervalEXT wglSwapIntervalEXT = nullptr;
