/**
 * @file core/Numeric.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

// Static

template<>
inline Byte Numeric<Byte>::max()
{
	return 255u;
}

template<>
inline Byte Numeric<Byte>::min()
{
	return 0u;
}

template<>
inline Int8 Numeric<Int8>::max()
{
	return 127;
}

template<>
inline Int8 Numeric<Int8>::min()
{
	return -128;
}

template<>
inline Uint8 Numeric<Uint8>::max()
{
	return 255u;
}

template<>
inline Uint8 Numeric<Uint8>::min()
{
	return 0u;
}

template<>
inline Int16 Numeric<Int16>::max()
{
	return 32767;
}

template<>
inline Int16 Numeric<Int16>::min()
{
	return -32768;
}

template<>
inline Uint16 Numeric<Uint16>::max()
{
	return 65535u;
}

template<>
inline Uint16 Numeric<Uint16>::min()
{
	return 0u;
}

template<>
inline Int32 Numeric<Int32>::max()
{
	return 2147483647;
}

template<>
inline Int32 Numeric<Int32>::min()
{
	return -2147483647 - 1;
}

template<>
inline Uint32 Numeric<Uint32>::max()
{
	return 4294967295u;
}

template<>
inline Uint32 Numeric<Uint32>::min()
{
	return 0u;
}

template<>
inline Int64 Numeric<Int64>::max()
{
	return 9223372036854775807;
}

template<>
inline Int64 Numeric<Int64>::min()
{
	return -9223372036854775807 - 1;
}

template<>
inline Uint64 Numeric<Uint64>::max()
{
	return 18446744073709551615u;
}

template<>
inline Uint64 Numeric<Uint64>::min()
{
	return 0u;
}

template<>
inline Float32 Numeric<Float32>::epsilon()
{
	return 1.192092896e-07f;
}

template<>
inline Float32 Numeric<Float32>::max()
{
	return 3.402823466e+38f;
}

template<>
inline Float32 Numeric<Float32>::min()
{
	return 1.175494351e-38f;
}

template<>
inline Float64 Numeric<Float64>::epsilon()
{
	return 2.2204460492503131e-016;
}

template<>
inline Float64 Numeric<Float64>::max()
{
	return 1.7976931348623158e+308;
}

template<>
inline Float64 Numeric<Float64>::min()
{
	return 2.2250738585072014e-308;
}
