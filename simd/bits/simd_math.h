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
	inline basic_simd<T, Abi> atan2(basic_simd<T, Abi> y, basic_simd<T, Abi> x)
	{
		using Vec_type = basic_simd<T, Abi>::Vec_type;
		return atan2(Vec_type(y), Vec_type(x));
	}
}

#ifdef VCL_NAMESPACE
}
#endif