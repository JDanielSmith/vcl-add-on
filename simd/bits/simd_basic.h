#pragma once

#include "simd.h"
#include "simd_abi.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	template<typename T, typename Abi = details::simd_abi::fixed_size<4>>
	class basic_simd {
	public:
		using value_type = T;
		using reference = see below;
		using mask_type = basic_simd_mask;


		static constexpr simd_size_type size = typename Abi::size;
	};

	template<typename T, simd_size_type N = basic_simd<T>::size()>
	using simd = basic_simd<T, details::simd_abi::fixed_size<N>>;

}

#ifdef VCL_NAMESPACE
}
#endif