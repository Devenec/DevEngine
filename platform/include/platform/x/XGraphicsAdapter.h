/**
 * @file platform/x/XGraphicsAdapter.h
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
#include <graphics/GraphicsAdapter.h>
#include <platform/x/X.h>

namespace Graphics
{
	class GraphicsAdapter::Implementation final
	{
	public:

		Implementation(const Uint32 adapterIndex, const Core::String8& name,
			const DisplayModeList& supportedDisplayModes, const Uint32 currentDisplayModeIndex,
			XRRScreenConfiguration* config);

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation();

		inline const DisplayMode& currentDisplayMode() const;

		inline Core::String8 name() const;

		void setDisplayMode(const DisplayMode& mode);

		inline const DisplayModeList& supportedDisplayModes() const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		Core::String8 _name;
		DisplayModeList _supportedDisplayModes;
		XRRScreenConfiguration* _config;
		Time _configTimestamp;
		Window _rootWindowHandle;
		Uint32 _currentDisplayModeIndex;
		Uint32 _initialDisplayModeIndex;

		DisplayModeList::const_iterator findDisplayMode(const DisplayMode& mode, Uint32& resolutionIndex)
			const;
	};

#include "inline/XGraphicsAdapter.inl"
}
