/**
 * @file platform/wgl/inline/WGLGraphicsExtensionManager.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Private

template<typename T>
T GraphicsExtensionManager::getExtensionFunction(const Char8* functionName)
{
	return reinterpret_cast<T>(wglGetProcAddress(functionName));
}
