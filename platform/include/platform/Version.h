/**
 * @file platform/Version.h
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

#include <core/String.h>
#include <core/Types.h>

namespace Platform
{
	class Version final
	{
	public:

		Version() = default;

		Version(const Uint32 majorNumber, const Uint32 minorNumber);

		Version(const Version& version) = default;
		Version(Version&& version) = default;

		~Version() = default;

		inline Uint32 majorNumber() const;

		inline Uint32 minorNumber() const;

		inline void setMajorNumber(const Uint32 majorNumber);

		inline void setMinorNumber(const Uint32 minorNumber);

		Version& operator =(const Version& version) = default;
		Version& operator =(Version&& version) = default;

		static Version createFromString(const Core::String8& versionString);

	private:

		Uint32 _majorNumber;
		Uint32 _minorNumber;
	};

	inline Bool operator ==(const Version& versionA, const Version& versionB);

	inline Bool operator !=(const Version& versionA, const Version& versionB);

	Bool operator <(const Version& versionA, const Version& versionB);

#include "inline/Version.inl"
}
