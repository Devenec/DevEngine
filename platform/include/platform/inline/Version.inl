/**
 * @file platform/inline/Version.inl
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

// Public

Uint32 Version::majorNumber() const
{
	return _majorNumber;
}

Uint32 Version::minorNumber() const
{
	return _minorNumber;
}

void Version::setMajorNumber(const Uint32 majorNumber)
{
	_majorNumber = majorNumber;
}

void Version::setMinorNumber(const Uint32 minorNumber)
{
	_minorNumber = minorNumber;
}


// Platform

Bool operator ==(const Version& versionA, const Version& versionB)
{
	return
		versionA.majorNumber() == versionB.majorNumber() && versionA.minorNumber() == versionB.minorNumber();
}

Bool operator !=(const Version& versionA, const Version& versionB)
{
	return !(versionA == versionB);
}
