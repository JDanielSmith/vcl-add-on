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

#include "simd.h"

#ifndef VECTORMATH_EXP_H
#include "vectormath_exp.h"
#endif

#ifndef VECTORMATH_TRIG_H
#include "vectormath_trig.h"
#endif

#ifndef VECTORMATH_TRIG_H
#include "vectormath_trig.h"
#endif

#ifndef VECTORMATH_HYP_H
#include "vectormath_hyp.h"
#endif

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	#define VECTORCLASS_basic_simd_math1(func_) \
		template<typename T, typename Abi> inline basic_simd<T, Abi> func_(const basic_simd<T, Abi>& v) { \
			using Vec = typename basic_simd<T, Abi>::native_type; return func_(static_cast<Vec>(v)); }
	#define VECTORCLASS_basic_simd_math2(func_) \
		template<typename T, typename Abi> inline basic_simd<T, Abi> func_(const basic_simd<T, Abi>& a, const basic_simd<T, Abi>& b) { \
			using Vec = typename basic_simd<T, Abi>::native_type; return func_(static_cast<Vec>(a), static_cast<Vec>(b)); }

	VECTORCLASS_basic_simd_math1(abs);
	VECTORCLASS_basic_simd_math1(round);
	template<typename T, typename Abi>
	inline basic_simd<int, Abi> lround(const basic_simd<T, Abi>& v) // TODO: `long`, not `int`
	{
		using Vec = typename basic_simd<T, Abi>::native_type;
		return roundi(static_cast<Vec>(v));
	}
	VECTORCLASS_basic_simd_math1(sqrt);
	VECTORCLASS_basic_simd_math1(ceil);
	VECTORCLASS_basic_simd_math1(floor);

	VECTORCLASS_basic_simd_math1(sin);
	VECTORCLASS_basic_simd_math1(cos);
	VECTORCLASS_basic_simd_math1(tan);
	VECTORCLASS_basic_simd_math1(asin);
	VECTORCLASS_basic_simd_math1(acos);
	VECTORCLASS_basic_simd_math1(atan);
	VECTORCLASS_basic_simd_math2(atan2);
	VECTORCLASS_basic_simd_math1(sinh);
	VECTORCLASS_basic_simd_math1(cosh);
	VECTORCLASS_basic_simd_math1(tanh);
	VECTORCLASS_basic_simd_math1(asinh);
	VECTORCLASS_basic_simd_math1(acosh);
	VECTORCLASS_basic_simd_math1(atanh);

	#undef VECTORCLASS_basic_simd_math1
	#undef VECTORCLASS_basic_simd_math
}
#ifdef VCL_NAMESPACE
}
#endif