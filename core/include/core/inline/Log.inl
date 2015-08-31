/**
 * @file core/inline/Log.inl
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

// Public

LogLevel Log::filterLevel() const
{
	return _filterLevel;
}

void Log::setfilterLevel(const LogLevel& level)
{
	_filterLevel = level;
}

// Operators

Log& Log::operator <<(const Float32 floatingPoint)
{
	return operator <<(static_cast<Float64>(floatingPoint));
}

Log& Log::operator <<(const Char8* characters)
{
	_streamBuffer.appendCharacters(characters, LogBuffer::NON_POSITION);
	return *this;
}

Log& Log::operator <<(const String8& string)
{
	_streamBuffer.appendCharacters(string.c_str(), string.length());
	return *this;
}

Log& Log::operator <<(const LogLevel& streamLevel)
{
	_streamLevel = streamLevel;
	appendStreamLevel(_streamLevel);

	return *this;
}

Log& Log::operator <<(const StreamFormat& streamFormat)
{
	_streamFormat = streamFormat;
	return *this;
}

// Private

// Static

template<typename... Parameters>
Uint32 Log::toString(const Char8* format, Char8* buffer, const Uint32 bufferSize, Parameters... parameters)
{
	const Uint32 charactersWritten = std::snprintf(buffer, bufferSize, format, parameters...);

	if(charactersWritten < bufferSize)
		return charactersWritten;
	else
		return bufferSize;
}


// Core

StreamFormat operator &(StreamFormat streamFormatA, const StreamFormat& streamFormatB)
{
	streamFormatA &= streamFormatB;
	return streamFormatA;
}

StreamFormat& operator &=(StreamFormat& streamFormatA, const StreamFormat& streamFormatB)
{
	streamFormatA = static_cast<StreamFormat>(static_cast<Int32>(streamFormatA) & static_cast<Int32>(streamFormatB));
	return streamFormatA;
}

StreamFormat operator |(StreamFormat streamFormatA, const StreamFormat& streamFormatB)
{
	streamFormatA |= streamFormatB;
	return streamFormatA;
}

StreamFormat& operator |=(StreamFormat& streamFormatA, const StreamFormat& streamFormatB)
{
	streamFormatA = static_cast<StreamFormat>(static_cast<Int32>(streamFormatA) | static_cast<Int32>(streamFormatB));
	return streamFormatA;
}
