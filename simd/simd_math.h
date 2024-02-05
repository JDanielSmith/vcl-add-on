/***************************  simd_math.h   *********************************
* Author:        Agner Fog
* Date created:  2024-02-02
* Last modified: 2024-02-02
* Version:       2.02.00
* Project:       Extension to vector class library
* Description:
* Allow client code using the vector class library to look more like it was using `std::simd::simd`.
* https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p1928r8.pdf
*
* © Copyright 2012-2024. Apache License version 2.0 or later
******************************************************************************/
#pragma once

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100) // '...': unreferenced formal parameter
#pragma warning(disable: 4127) // conditional expression is constant
#pragma warning(disable: 4244) // '...': conversion from '...' to '...', possible loss of data
#pragma warning(disable: 4723) // potential divide by 0
#endif
#include "vectorclass.h"
#include "vectormath_trig.h"
#if _MSC_VER
#pragma warning(pop)
#endif

#include "simd.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	template<typename T, int N>
	inline auto round(const basic_simd<T, N>& v)
	{
		using Vec = basic_simd<T, N>::Vec;
		return basic_simd<T, N>(round(static_cast<Vec>(v)));
	}

	template<typename T, int N>
	inline auto lround(const basic_simd<T, N>& v)
	{
		using Vec = basic_simd<T, N>::Vec;

		const auto result = roundi(static_cast<Vec>(v));

		return basic_simd<int, N>(result);
	}

	template<typename T, int N>
	inline auto atan2(const basic_simd<T, N>& y, const basic_simd<T, N>& x)
	{
		using Vec = basic_simd<T, N>::Vec;
		return basic_simd<T, N>(atan2(static_cast<Vec>(y), static_cast<Vec>(x)));
	}
}

#ifdef VCL_NAMESPACE
}
#endif