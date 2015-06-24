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

		void initialisePixelFormat() const;
		void createContext();
		void validateOpenGLVersion() const;
		Int32 choosePixelFormat(const PIXELFORMATDESCRIPTOR& pixelFormatDescriptor) const;
		void validatePixelFormat(const Int32 pixelFormatIndex) const;

		static PIXELFORMATDESCRIPTOR createPixelFormatDescriptor();
	};
}
