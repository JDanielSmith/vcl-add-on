#pragma once

#include "simd.h"
#include "simd_abi.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	template<size_t Bytes, typename Abi = details::simd_abi::fixed_size<4>> class basic_simd_mask {
	public:
		using value_type = bool;
		//using reference = see below;
		using abi_type = Abi;

		static constexpr auto size = basic_simd<details::integer_from<Bytes>, Abi>::size;

		constexpr basic_simd_mask() noexcept = default;
	};

	template<typename T, simd::details::size_type N = basic_simd_mask<sizeof(T)>::size>
	using simd_mask = basic_simd_mask<sizeof(T), details::simd_abi::fixed_size<N>>;
}

#ifdef VCL_NAMESPACE
}
#endif