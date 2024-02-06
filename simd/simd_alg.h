/***************************  simd_alg.h   *********************************
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

#include "simd.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	template<size_t Bytes, typename Abi, typename T, typename U>
	constexpr T simd_select(const basic_simd_mask<Bytes, Abi>& c, const T& a, const U& b)
	{
		using Vec_b = basic_simd_mask<Bytes, Abi>::Vec;
		using Vec_t = T::Vec;
		using Vec_u = U::Vec;
		return select(static_cast<Vec_b>(c), static_cast<Vec_t>(a), static_cast<Vec_u>(b));
	}

	template<size_t Bytes, typename Abi>
	constexpr bool any_of(const basic_simd_mask<Bytes, Abi>& m)
	{
		using Vec_b = basic_simd_mask<Bytes, Abi>::Vec;
		return horizontal_or(static_cast<Vec_b>(m));
	}
}

#ifdef VCL_NAMESPACE
}
#endif