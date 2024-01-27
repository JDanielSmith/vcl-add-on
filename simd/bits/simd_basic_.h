#pragma once

#include <cstdint>

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100) // '...': unreferenced formal parameter
#pragma warning(disable: 4127) // conditional expression is constant
#pragma warning(disable: 4244) // '...': conversion from '...' to '...', possible loss of data
#pragma warning(disable: 4723) // potential divide by 0
#endif
#include "vectorclass.h"
#if _MSC_VER
#pragma warning(pop)
#endif

#include "simd_basic.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	#define VECTORCLASS_basic_simd(vec_, type_, size_) \
	template<> class basic_simd<type_, details::simd_abi::fixed_size<size_>> { vec_ v_; public: \
		using abi_type = details::simd_abi::fixed_size<size_>; \
		using mask_type = basic_simd_mask<type_, abi_type>; /* TODO: basic_simd_mask<sizeof(T), abi_type>; */ \
		static constexpr details::size_type size = size_; \
		constexpr explicit operator vec_() const { return v_; } \
		constexpr explicit basic_simd(const vec_& init) : v_(init) { } }
	#define VECTORCLASS_basic_simd_(suffix_, size_bits_, size_) 	VECTORCLASS_basic_simd(Vec ## size_ ## suffix_, std::int ## size_bits_ ## _t, size_); \
		VECTORCLASS_basic_simd(Vec ## size_ ## u ## suffix_, std::uint ## size_bits_ ## _t, size_)

	// Table 2.1 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
	// 128 Total bits
	VECTORCLASS_basic_simd_(c, 8, 16); // Vec16c, Vec16uc
	VECTORCLASS_basic_simd_(s, 16, 8); // Vec8s, Vec8us
	VECTORCLASS_basic_simd_(i, 32, 4); // Vec4i, Vec4ui
	VECTORCLASS_basic_simd_(q, 64, 2); // Vec2q, Vec2uq
	// 256 Total bits
	VECTORCLASS_basic_simd_(c, 8, 32); // Vec32c, Vec32uc
	VECTORCLASS_basic_simd_(s, 16, 16); // Vec16s, Vec16us
	VECTORCLASS_basic_simd_(i, 32, 8); // Vec8i, Vec8ui
	VECTORCLASS_basic_simd_(q, 64, 4); // Vec4q, Vec4uq
	// 512 Total bits
	VECTORCLASS_basic_simd_(c, 8, 64); // Vec64c, Vec64uc
	VECTORCLASS_basic_simd_(s, 16, 32); // Vec32s, Vec32us
	VECTORCLASS_basic_simd_(i, 32, 16); // Vec16i, Vec16ui
	VECTORCLASS_basic_simd_(q, 64, 8); // Vec8q, Vec8uq

	// Table 2.2 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
	// 128 Total bits
	VECTORCLASS_basic_simd(Vec4f, float, 4);
	VECTORCLASS_basic_simd(Vec2d, double, 2);
	// 256 Total bits
	VECTORCLASS_basic_simd(Vec8f, float, 8);
	VECTORCLASS_basic_simd(Vec4d, double, 4);
	// 512 Total bits
	VECTORCLASS_basic_simd(Vec16f, float, 16);
	VECTORCLASS_basic_simd(Vec8d, double, 8);
}

#ifdef VCL_NAMESPACE
}
#endif