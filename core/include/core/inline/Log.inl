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

Log& Log::operator <<(const Char16* characters)
{
	DE_ASSERT(characters != nullptr);
	_stream << toString8(characters);

	return *this;
}

Log& Log::operator <<(const LogLevel& logLevel)
{
	_streamLevel = logLevel;
	return *this;
}

template<typename T>
Log& Log::operator <<(const T& value)
{
	_stream << value;
	return *this;
}
