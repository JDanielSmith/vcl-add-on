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

#include "simd_basic_mask.h"
#include "simd_basic.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
    // 	VECTORCLASS_basic_simd_(c, 8, 16); // Vec16c, Vec16uc

 //   // Table 2.3 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
 //   template <size_t elements_per_vector, typename For_use_with> struct Vec_N_b;
 //   template<> struct Vec_N_b<16, int8_t> final { using type = Vec16cb; };

    template<> class basic_simd_mask<int8_t, details::simd_abi::fixed_size<16>> { Vec16cb v_; public:
          constexpr explicit operator Vec16cb() const { return v_; }
          constexpr explicit basic_simd_mask(const Vec16cb& init) : v_(init) { }
    };

    template<> class basic_simd_mask<float, details::simd_abi::fixed_size<4>> { Vec4fb v_; public:
        using abi_type = details::simd_abi::fixed_size<4>;
        static constexpr auto size = basic_simd<float, abi_type>::size; // TODO: basic_simd<details::integer_from<Bytes>, Abi>::size;
        basic_simd_mask() = default;
        constexpr explicit operator Vec4fb() const { return v_; }
        constexpr explicit basic_simd_mask(const Vec4fb& init) : v_(init) { }
    };
    template<> class basic_simd_mask<float, details::simd_abi::fixed_size<8>> { Vec8fb v_; public:
          constexpr explicit operator Vec8fb() const { return v_; }
          constexpr explicit basic_simd_mask(const Vec8fb& init) : v_(init) { }
    };


	//#define VECTORCLASS_basic_simd_mask(vec_, type_, size_) \
	//template<> class basic_simd_mask<type_, details::simd_abi::fixed_size<size_>> { public: vec_ v_; \
	//	static constexpr details::size_type size = size_; \
	//	constexpr explicit operator vec_() const { return v_; } \
	//	constexpr explicit basic_simd(const vec_& init) : v_(init) { } }
	//#define VECTORCLASS_basic_simd_mask_(suffix_, size_bits_, size_) 	VECTORCLASS_basic_simd_mask(Vec ## size_ ## suffix_, std::int ## size_bits_ ## _t, size_); \
	//	VECTORCLASS_basic_simd(Vec ## size_ ## u ## suffix_, std::uint ## size_bits_ ## _t, size_)

    //// Table 2.3 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
    //template <size_t elements_per_vector, typename For_use_with> struct Vec_N_b;
    //template<> struct Vec_N_b<16, int8_t> final { using type = Vec16cb; };
    //template<> struct Vec_N_b<16, uint8_t> final { using type = Vec16cb; };
    //template<> struct Vec_N_b<8, int16_t> final { using type = Vec8sb; };
    //template<> struct Vec_N_b<8, uint16_t> final { using type = Vec8sb; };
    //template<> struct Vec_N_b<4, int32_t> final { using type = Vec4ib; };
    //template<> struct Vec_N_b<4, uint32_t> final { using type = Vec4ib; };
    //template<> struct Vec_N_b<2, int64_t> final { using type = Vec2qb; };
    //template<> struct Vec_N_b<2, uint64_t> final { using type = Vec2qb; };
    //template<> struct Vec_N_b<32, int8_t> final { using type = Vec32cb; };
    //template<> struct Vec_N_b<32, uint8_t> final { using type = Vec32cb; };
    //template<> struct Vec_N_b<16, int16_t> final { using type = Vec16sb; };
    //template<> struct Vec_N_b<16, uint16_t> final { using type = Vec16sb; };
    //template<> struct Vec_N_b<8, int32_t> final { using type = Vec8ib; };
    //template<> struct Vec_N_b<8, uint32_t> final { using type = Vec8ib; };
    //template<> struct Vec_N_b<4, int64_t> final { using type = Vec4qb; };
    //template<> struct Vec_N_b<4, uint64_t> final { using type = Vec4qb; };
    //template<> struct Vec_N_b<64, int8_t> final { using type = Vec64cb; };
    //template<> struct Vec_N_b<64, uint8_t> final { using type = Vec64cb; };
    //template<> struct Vec_N_b<32, int16_t> final { using type = Vec32sb; };
    //template<> struct Vec_N_b<32, uint16_t> final { using type = Vec32sb; };
    //template<> struct Vec_N_b<16, int32_t> final { using type = Vec16ib; };
    //template<> struct Vec_N_b<16, uint32_t> final { using type = Vec16ib; };
    //template<> struct Vec_N_b<8, int64_t> final { using type = Vec8qb; };
    //template<> struct Vec_N_b<8, uint64_t> final { using type = Vec8qb; };
    //template<> struct Vec_N_b<4, float> final { using type = Vec4fb; };
    //template<> struct Vec_N_b<2, double> final { using type = Vec2db; };
    //template<> struct Vec_N_b<8, float> final { using type = Vec8fb; };
    //template<> struct Vec_N_b<4, double> final { using type = Vec4db; };
    //template<> struct Vec_N_b<16, float> final { using type = Vec16fb; };
    //template<> struct Vec_N_b<8, double> final { using type = Vec8db; };
}

#ifdef VCL_NAMESPACE
}
#endif