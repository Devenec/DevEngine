/**
 * @file platform/wgl/WGLGraphicsContextBase.h
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <core/Types.h>
#include <platform/windows/WindowsGraphics.h>

namespace Platform
{
	class GraphicsContextBase
	{
	public:

		GraphicsContextBase(const GraphicsContextBase& graphicsContext) = delete;
		GraphicsContextBase(GraphicsContextBase&& graphicsContext) = delete;

		inline HDC deviceContextHandle() const;

		void makeCurrent() const;

		void makeNonCurrent() const;

		void swapBuffers() const;

		GraphicsContextBase& operator =(const GraphicsContextBase& graphicsContext) = delete;
		GraphicsContextBase& operator =(GraphicsContextBase&& graphicsContext) = delete;

	protected:

		HDC _deviceContextHandle;
		HGLRC _graphicsContextHandle;

		explicit GraphicsContextBase(HWND windowHandle);

		~GraphicsContextBase();

		void destroyContext();

		void setConfig(const Int32 configIndex) const;
	};

#include "inline/WGLGraphicsContextBase.inl"
}
