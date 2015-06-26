/**
 * @file graphics/PNGReader.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

		Core::Vector<Byte> readImage(Core::FileStream& fileStream);

		PNGReader& operator =(const PNGReader& pngReader) = delete;
		PNGReader& operator =(PNGReader&& pngReader) = delete;

	private:

		static const Char8* COMPONENT_TAG;

		png_info* _pngInfo;
		png_struct* _pngStructure;

		void initialiseStructure();
		void initialiseInfo();
		void validateSignature(Core::FileStream& fileStream);

		static void handleError(png_struct* pngReader, const Char8* message);
		static void handleWarning(png_struct* pngReader, const Char8* message);
		static Void* allocateMemory(png_struct* pngReader, Uint32 byteCount);
		static void deallocateMemory(png_struct* pngReader, Void* pointer);
		static void readData(png_struct* pngReader, Byte* buffer, Uint32 byteCount);
	};

#include "inline/PNGReader.inl"
}
