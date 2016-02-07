/**
 * @file platform/Version.cpp
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

#include <cstdlib>
#include <platform/Version.h>

using namespace Core;
using namespace Platform;

// Public

Version::Version(const Uint32 majorNumber, const Uint32 minorNumber)
	: _majorNumber(majorNumber),
	  _minorNumber(minorNumber) { }

// Static

Version Version::createFromString(const String8& versionString)
{
	const Uint firstDelimiterPosition = versionString.find('.');
	const String8 majorString = versionString.substr(0u, firstDelimiterPosition);

	const Uint secondDelimiterPosition =
		versionString.find_first_not_of("0123456789", firstDelimiterPosition + 1u);

	const Uint minorStringLength = secondDelimiterPosition - (firstDelimiterPosition + 1);
	const String8 minorString = versionString.substr(firstDelimiterPosition + 1, minorStringLength);
	const Uint32 majorNumber = static_cast<Uint32>(std::strtol(majorString.c_str(), nullptr, 10));
	const Uint32 minorNumber = static_cast<Uint32>(std::strtol(minorString.c_str(), nullptr, 10));
	
	return Version(majorNumber, minorNumber);
}


// Platform

Bool Platform::operator <(const Version& versionA, const Version& versionB)
{
	if(versionA.majorNumber() < versionB.majorNumber())
		return true;
	else if(versionA.majorNumber() == versionB.majorNumber())
		return versionA.minorNumber() < versionA.minorNumber();

	return false;
}
