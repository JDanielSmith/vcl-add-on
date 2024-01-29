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

#include "simd_basic.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	#define VECTORCLASS_basic_simd_relop(OPERATOR_) \
		template<typename T, typename Abi> constexpr auto operator OPERATOR_(const basic_simd<T, Abi>& lhs, const basic_simd<T, Abi>& rhs) noexcept { \
			using Vec_t = basic_simd<T, Abi>::Vec_t; \
			const auto result = static_cast<Vec_t>(lhs) OPERATOR_ rhs; \
			return basic_simd<T, Abi>::mask_type(result); } \
		template<typename T, typename Abi, typename U> constexpr auto operator OPERATOR_(const basic_simd<T, Abi>& lhs, const U& rhs) noexcept { \
			using Vec_t = basic_simd<T, Abi>::Vec_t; \
			const auto result = static_cast<Vec_t>(lhs) OPERATOR_ rhs; \
			return basic_simd<T, Abi>::mask_type(result); }
	VECTORCLASS_basic_simd_relop(==);
	VECTORCLASS_basic_simd_relop(!=);
	VECTORCLASS_basic_simd_relop(>=);
	VECTORCLASS_basic_simd_relop(<=);
	VECTORCLASS_basic_simd_relop(>);
	VECTORCLASS_basic_simd_relop(<);
	#undef VECTORCLASS_basic_simd_relop
}

#ifdef VCL_NAMESPACE
}
#endif