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
	template<typename T, typename Abi>
	inline auto atan2(const basic_simd<T, Abi>& y, const basic_simd<T, Abi>& x)
	{
		using Vec_t = basic_simd<T, Abi>::Vec_t;
		return basic_simd<T, Abi>(atan2(Vec_t(y), Vec_t(x)));
	}
}

#ifdef VCL_NAMESPACE
}
#endif