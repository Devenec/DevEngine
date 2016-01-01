/**
 * @file graphics/PNGReader.h
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

#include <png.h>
#include <core/Types.h>
#include <core/Vector.h>

namespace Core
{
	class FileStream;
}

namespace Graphics
{
	enum class ImageFormat;

	using ByteData = Core::Vector<Uint8>;

	class PNGReader final
	{
	public:

		PNGReader();

		PNGReader(const PNGReader& pngReader) = delete;
		PNGReader(PNGReader&& pngReader) = delete;

		~PNGReader();

		ImageFormat imageFormat() const;

		inline const Uint32 imageHeight() const;

		inline const Uint32 imageWidth() const;

		ByteData readImage(Core::FileStream& fileStream);

		PNGReader& operator =(const PNGReader& pngReader) = delete;
		PNGReader& operator =(PNGReader&& pngReader) = delete;

	private:

		png_info* _pngInfo;
		png_struct* _pngStructure;

		void initialiseStructure();
		void initialiseInfo();
		void validateSignature(Core::FileStream& fileStream);
	};

#include "inline/PNGReader.inl"
}
