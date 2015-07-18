/**
 * @file platform/wgl/WGL.cpp
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
 */

#include <platform/wgl/WGL.h>
#include <platform/windows/Windows.h>

using namespace Platform;

// Public

// Standard

WGL::CreateContext WGL::createContext = wglCreateContext;
WGL::DeleteContext WGL::deleteContext = wglDeleteContext;
WGL::GetCurrentContext WGL::getCurrentContext = wglGetCurrentContext;
WGL::GetProcAddress WGL::getProcAddress = wglGetProcAddress;
WGL::MakeCurrent WGL::makeCurrent = wglMakeCurrent;

// WGL_ARB_create_context

WGL::CreateContextAttribsARB WGL::createContextAttribsARB = nullptr;

// WGL_ARB_extensions_string

WGL::GetExtensionsStringARB WGL::getExtensionsStringARB = nullptr;

// WGL_ARB_pixel_format

WGL::ChoosePixelFormatARB WGL::choosePixelFormatARB = nullptr;
WGL::GetPixelFormatAttribFVARB WGL::getPixelFormatAttribfvARB = nullptr;
WGL::GetPixelFormatAttribIVARB WGL::getPixelFormatAttribivARB = nullptr;

// WGL_EXT_swap_control

WGL::GetSwapIntervalEXT WGL::getSwapIntervalEXT = nullptr;
WGL::SwapIntervalEXT WGL::swapIntervalEXT = nullptr;
