/**
 * @file platform/windows/WindowsGraphicsInterfaceManager.h
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
	class GraphicsInterfaceManager final
	{
	public:

		GraphicsInterfaceManager();

		GraphicsInterfaceManager(const GraphicsInterfaceManager& graphicsInterfaceManager) = delete;
		GraphicsInterfaceManager(GraphicsInterfaceManager&& graphicsInterfaceManager) = delete;

		~GraphicsInterfaceManager();

		void initialiseInterface(HWND temporaryWindowHandle) const;

		Bool interfaceRequiresInitialisation() const;

		GraphicsInterfaceManager& operator =(const GraphicsInterfaceManager& graphicsInterfaceManager) =
			delete;

		GraphicsInterfaceManager& operator =(GraphicsInterfaceManager&& graphicsInterfaceManager) = delete;

	private:

		class Implementation;

		Implementation* _implementation;
	};
}
