/**
 * @file platform/glx/GLXGraphicsContext.h
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
#include <platform/GraphicsContext.h>
#include <platform/glx/GLX.h>
#include <platform/x/X.h>

namespace Platform
{
	class GraphicsContext::Implementation final
	{
	public:

		Implementation(const Window windowHandle, GLX::FBConfig configHandle);

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation();

		void makeCurrent() const;

		void makeNonCurrent() const;

		void swapBuffers() const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		GLX::Context _graphicsContextHandle;
		Window _windowHandle;

		void checkContext() const;
	};
}
