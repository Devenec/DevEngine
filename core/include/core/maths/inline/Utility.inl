/**
 * @file core/maths/inline/Utility.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// Maths

Int32 absolute(const Int32 value)
{
	return std::abs(value);
}

Float32 absolute(const Float32 value)
{
	return std::abs(value);
}

Float32 arcCosine(const Float32 value)
{
	return std::acos(value);
}

Float32 arcSine(const Float32 value)
{
	return std::asin(value);
}

Float32 arcTangent(const Float32 value)
{
	return std::atan(value);
}

Float32 arcTangentAngle(const Float32 y, const Float32 x)
{
	return std::atan2(y, x);
}

Float32 ceiling(const Float32 value)
{
	return std::ceil(value);
}

Int32 clamp(const Int32 value, const Int32 min, const Int32 max)
{
	if(value < min)
		return min;
	else if(value > max)
		return max;
	else
		return value;
}

Uint32 clamp(const Uint32 value, const Uint32 min, const Uint32 max)
{
	if(value < min)
		return min;
	else if(value > max)
		return max;
	else
		return value;
}

Float32 clamp(const Float32 value, const Float32 min, const Float32 max)
{
	if(value < min)
		return min;
	else if(value > max)
		return max;
	else
		return value;
}

Float32 cosine(const Float32 value)
{
	return std::cos(value);
}

Float32 floor(const Float32 value)
{
	return std::floor(value);
}

Float32 lerp(const Float32 valueA, const Float32 valueB, const Float32 weight)
{
	return weight * (valueB - valueA) + valueA;
}

Int32 maximum(const Int32 valueA, const Int32 valueB)
{
	return valueA < valueB ? valueB : valueA;
}

Uint32 maximum(const Uint32 valueA, const Uint32 valueB)
{
	return valueA < valueB ? valueB : valueA;
}

Float32 maximum(const Float32 valueA, const Float32 valueB)
{
	return valueA < valueB ? valueB : valueA;
}

Int32 minimum(const Int32 valueA, const Int32 valueB)
{
	return valueA < valueB ? valueA : valueB;
}

Uint32 minimum(const Uint32 valueA, const Uint32 valueB)
{
	return valueA < valueB ? valueA : valueB;
}

Float32 minimum(const Float32 valueA, const Float32 valueB)
{
	return valueA < valueB ? valueA : valueB;
}

Float32 power(const Float32 base, const Float32 exponent)
{
	return std::pow(base, exponent);
}

Float32 round(const Float32 value)
{
	return std::round(value);
}

Float32 squareRoot(const Float32 value)
{
	DE_ASSERT(value >= 0.0f);
	return std::sqrt(value);
}

Int32 sign(const Int32 value)
{
	if(value < 0)
		return -1;
	else if(value > 0)
		return 1;
	else
		return 0;
}

Float32 sign(const Float32 value)
{
	if(value < 0.0f)
		return -1.0f;
	else if(value > 0.0f)
		return 1.0f;
	else
		return 0.0f;
}

Float32 sine(const Float32 value)
{
	return std::sin(value);
}

Float32 tangent(const Float32 value)
{
	return std::tan(value);
}

Float32 toDegrees(const Float32 angle)
{
	return 180.0f / PI * angle;
}

Float32 toRadians(const Float32 angle)
{
	return PI / 180.0f * angle;
}

Float32 wrapAngle(const Float32 angle)
{
	return clamp(angle, -PI, PI);
}
