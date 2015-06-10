/**
 * @file graphics/ImageLoader.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <png.h>
#include <content/ContentLoader.h>
#include <core/Types.h>
#include <core/Vector.h>

namespace Core
{
	class FileStream;
}

namespace Graphics
{
	class Image;

	class ImageLoader final : public Content::ContentLoader<Image>
	{
	public:

		ImageLoader(); // TODO: make inline

		ImageLoader(const ImageLoader& imageLoader) = delete;
		ImageLoader(ImageLoader&& imageLoader) = delete;

		~ImageLoader() = default;

		Image* load(Core::FileStream& fileStream) override;

		ImageLoader& operator =(const ImageLoader& imageLoader) = delete;
		ImageLoader& operator =(ImageLoader&& imageLoader) = delete;

	private:

		using PNGReader = png_struct;
		using PNGInfo = png_info;

		PNGInfo* _pngInfo;
		PNGReader* _pngReader;

		void initialisePngReader(Core::FileStream& fileStream);
		void initialisePngInfo();
		Core::Vector<Byte> readImage() const;
		ImageFormat getImageFormat() const;
		void deinitialisePngReader();

		static void validatePngSignature(Core::FileStream& fileStream);
		static void handlePngReaderError(PNGReader* pngReader, const Char8* message);
		static void handlePngReaderWarning(PNGReader* pngReader, const Char8* message);
		static Void* allocatePngReaderMemory(PNGReader* pngReader, Uint32 byteCount);
		static void deallocatePngReaderMemory(PNGReader* pngReader, Void* pointer);
		static void readPngReader(PNGReader* pngReader, Byte* buffer, Uint32 byteCount);
	};
}
