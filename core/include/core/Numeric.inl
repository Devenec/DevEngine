/**
 * @file core/Numeric.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

// Static

template<>
DE_CONSTEXPR Int8 Numeric<Int8>::maximum()
{
	return 127;
}

template<>
DE_CONSTEXPR Int8 Numeric<Int8>::minimum()
{
	return -128;
}

template<>
DE_CONSTEXPR Uint8 Numeric<Uint8>::maximum()
{
	return 255u;
}

template<>
DE_CONSTEXPR Uint8 Numeric<Uint8>::minimum()
{
	return 0u;
}

template<>
DE_CONSTEXPR Int16 Numeric<Int16>::maximum()
{
	return 32767;
}

template<>
DE_CONSTEXPR Int16 Numeric<Int16>::minimum()
{
	return -32768;
}

template<>
DE_CONSTEXPR Uint16 Numeric<Uint16>::maximum()
{
	return 65535u;
}

template<>
DE_CONSTEXPR Uint16 Numeric<Uint16>::minimum()
{
	return 0u;
}

template<>
DE_CONSTEXPR Int32 Numeric<Int32>::maximum()
{
	return 2147483647;
}

template<>
DE_CONSTEXPR Int32 Numeric<Int32>::minimum()
{
	return -2147483647 - 1;
}

template<>
DE_CONSTEXPR Uint32 Numeric<Uint32>::maximum()
{
	return 4294967295u;
}

template<>
DE_CONSTEXPR Uint32 Numeric<Uint32>::minimum()
{
	return 0u;
}

template<>
DE_CONSTEXPR Int64 Numeric<Int64>::maximum()
{
	return 9223372036854775807;
}

template<>
DE_CONSTEXPR Int64 Numeric<Int64>::minimum()
{
	return -9223372036854775807 - 1;
}

template<>
DE_CONSTEXPR Uint64 Numeric<Uint64>::maximum()
{
	return 18446744073709551615u;
}

template<>
DE_CONSTEXPR Uint64 Numeric<Uint64>::minimum()
{
	return 0u;
}

template<>
DE_CONSTEXPR Float32 Numeric<Float32>::epsilon()
{
	return 1.192092896e-07f;
}

template<>
DE_CONSTEXPR Float32 Numeric<Float32>::maximum()
{
	return 3.402823466e+38f;
}

template<>
DE_CONSTEXPR Float32 Numeric<Float32>::minimum()
{
	return 1.175494351e-38f;
}

template<>
DE_CONSTEXPR Float64 Numeric<Float64>::epsilon()
{
	return 2.2204460492503131e-016;
}

template<>
DE_CONSTEXPR Float64 Numeric<Float64>::maximum()
{
	return 1.7976931348623158e+308;
}

template<>
DE_CONSTEXPR Float64 Numeric<Float64>::minimum()
{
	return 2.2250738585072014e-308;
}
