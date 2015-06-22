/**
 * @file platform/wgl/inline/WGLGraphicsContextBase.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

GraphicsContextBase::GraphicsContextBase(HWND windowHandle)
	: _deviceContextHandle(nullptr),
	  _graphicsContextHandle(nullptr)
{
	DE_ASSERT(windowHandle != nullptr);
	initialiseDeviceContext(windowHandle);
}

GraphicsContextBase::~GraphicsContextBase()
{
	if(_deviceContextHandle != nullptr)
	{
		makeNonCurrent();
		destroyContext();
	}
}

void GraphicsContextBase::swapBuffers() const
{
	const Int32 result = SwapBuffers(_deviceContextHandle);
	DE_ASSERT(result != 0);
}
