/**
 * @file platform/wgl/WGLTemporaryGraphicsContext.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Types.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/Windows.h>

namespace Platform
{
	class TemporaryGraphicsContext final : public GraphicsContextBase
	{
	public:

		explicit TemporaryGraphicsContext(HWND windowHandle);

		TemporaryGraphicsContext(const TemporaryGraphicsContext& temporaryGraphicsContext) = delete;
		TemporaryGraphicsContext(TemporaryGraphicsContext&& temporaryGraphicsContext) = delete;

		~TemporaryGraphicsContext() = default;

		void deinitialise();

		void initialise();

		TemporaryGraphicsContext& operator =(const TemporaryGraphicsContext& temporaryGraphicsContext) = delete;
		TemporaryGraphicsContext& operator =(TemporaryGraphicsContext&& temporaryGraphicsContext) = delete;

	private:

		using Base = GraphicsContextBase;

		static constexpr Int32 MIN_SUPPORTED_OPENGL_VERSION_MAJOR = 4;
		static constexpr Int32 MIN_SUPPORTED_OPENGL_VERSION_MINOR = 5;

		static const Char8* COMPONENT_TAG;

		void initialisePixelFormat() const;
		void createContext();
		Int32 choosePixelFormat(const PIXELFORMATDESCRIPTOR& pixelFormatDescriptor) const;
		void validatePixelFormat(const Int32 pixelFormatIndex) const;

		static void validateOpenGLVersion();
		static PIXELFORMATDESCRIPTOR createPixelFormatDescriptor();
	};
}
