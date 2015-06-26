/**
 * @file platform/wgl/inline/WGLGraphicsContextBase.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

HDC GraphicsContextBase::deviceContextHandle() const
{
	return _deviceContextHandle;
}

void GraphicsContextBase::swapBuffers() const
{
	const Int32 result = SwapBuffers(_deviceContextHandle);
	DE_ASSERT(result != 0);
}
