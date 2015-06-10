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
#include <graphics/ImageFormat.h>

namespace Core
{
	class FileStream;
}

namespace Graphics
{
	class PNGReader
	{
	public:

		inline PNGReader();

		PNGReader(const PNGReader& pngReader) = delete;
		PNGReader(PNGReader&& pngReader) = delete;

		inline ~PNGReader();

		ImageFormat imageFormat() const;

		inline const Uint32 imageHeight() const;

		inline const Uint32 imageWidth() const;

		Core::Vector<Byte> readImage(Core::FileStream& fileStream);

		PNGReader& operator =(const PNGReader& pngReader) = delete;
		PNGReader& operator =(PNGReader&& pngReader) = delete;

	private:

		using PNGInfo = png_info;
		using PNGStructure = png_struct;

		PNGInfo* _pngInfo;
		PNGStructure* _pngStructure;

		void initialiseStructure();
		void initialiseInfo();
		void validateSignature(Core::FileStream& fileStream);

		static void handleError(PNGStructure* pngReader, const Char8* message);
		static void handleWarning(PNGStructure* pngReader, const Char8* message);
		static Void* allocateMemory(PNGStructure* pngReader, Uint32 byteCount);
		static void deallocateMemory(PNGStructure* pngReader, Void* pointer);
		static void readData(PNGStructure* pngReader, Byte* buffer, Uint32 byteCount);
	};

#include "inline/PNGReader.inl"
}
