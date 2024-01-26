#pragma once

#include "simd.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	namespace details
	{
		namespace simd_abi
		{
			template<simd_size_type N> struct fixed_size
			{
				static constexpr simd_size_type size = N;
			};
		} // simd_abi
	}
}

#ifdef VCL_NAMESPACE
}
#endif