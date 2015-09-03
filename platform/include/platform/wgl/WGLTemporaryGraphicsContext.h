/**
 * @file platform/wgl/WGLTemporaryGraphicsContext.h
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

#pragma once

#include <core/Types.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/WindowsGraphics.h>

namespace Platform
{
	class TemporaryGraphicsContext final : public GraphicsContextBase
	{
	public:

		explicit TemporaryGraphicsContext(HWND windowHandle);

		TemporaryGraphicsContext(const TemporaryGraphicsContext& temporaryGraphicsContext) = delete;
		TemporaryGraphicsContext(TemporaryGraphicsContext&& temporaryGraphicsContext) = delete;

		~TemporaryGraphicsContext() = default;

		TemporaryGraphicsContext& operator =(const TemporaryGraphicsContext& temporaryGraphicsContext) = delete;
		TemporaryGraphicsContext& operator =(TemporaryGraphicsContext&& temporaryGraphicsContext) = delete;

	private:

		using Base = GraphicsContextBase;

		void initialisePixelFormat() const;
		void createContext();
		Int32 choosePixelFormat(const PIXELFORMATDESCRIPTOR& pixelFormatDescriptor) const;
		void checkPixelFormat(const Int32 pixelFormatIndex) const;
	};
}
