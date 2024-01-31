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

#include "simd_basic_simd.h"
#include "simd_basic_simd_mask.h"
#include "simd_abi.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	template<typename T, typename V> struct rebind_simd;
	template<typename T, typename U, typename Abi0>
	struct rebind_simd<T, basic_simd<U, Abi0>>
	{
		using Abi1 = details::simd_abi::deduce_t<T, basic_simd<U, Abi0>::size, Abi0>;
		using type = basic_simd<T, Abi1>;
	};
	template<typename T, typename U, typename Abi0>
	struct rebind_simd<T, basic_simd_mask<U, Abi0>>
	{
		using Abi1 = details::simd_abi::deduce_t<T, basic_simd_mask<U, Abi0>::size, Abi0>;
		using type = basic_simd_mask<T, Abi1>;
	};
	template<typename T, typename V>
	using rebind_simd_t = rebind_simd<T, V>::type;

	template<details::size_type N, typename V> struct resize_simd;
	template<details::size_type N, typename T, typename Abi0>
	struct resize_simd<N, basic_simd<T, Abi0>>
	{
		using Abi1 = details::simd_abi::deduce_t<T, N, Abi0>;
		using type = basic_simd<T, Abi1>;
	};
	template<details::size_type N, typename T, typename Abi0>
	struct resize_simd<N, basic_simd_mask<T, Abi0>>
	{
		using Abi1 = details::simd_abi::deduce_t<T, N, Abi0>;
		using type = basic_simd_mask<T, Abi1>;
	};
	template<details::size_type N, typename V>
	using resize_simd_t = resize_simd<N, V>::type;
}

#ifdef VCL_NAMESPACE
}
#endif