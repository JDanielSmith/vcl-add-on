#pragma once

#include <memory>

#include "simd.h"
#include "simd_abi.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	namespace details
	{
        // Vec_N_T<8, int32_t> == Vec8i
        // https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
        template <size_t elements_per_vector, typename T> struct Vec_N_T;

        // Table 2.1 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
        // 128 Total bits
        template<> struct Vec_N_T<16, int8_t> final { using type = Vec16c; };
        template<> struct Vec_N_T<16, uint8_t> final { using type = Vec16uc; };
        template<> struct Vec_N_T<8, int16_t> final { using type = Vec8s; };
        template<> struct Vec_N_T<8, uint16_t> final { using type = Vec8us; };
        template<> struct Vec_N_T<4, int32_t> final { using type = Vec4i; };
        template<> struct Vec_N_T<4, uint32_t> final { using type = Vec4ui; };
        template<> struct Vec_N_T<2, int64_t> final { using type = Vec2q; };
        template<> struct Vec_N_T<2, uint64_t> final { using type = Vec2uq; };
        // 256 Total bits
        template<> struct Vec_N_T<32, int8_t> final { using type = Vec32c; };
        template<> struct Vec_N_T<32, uint8_t> final { using type = Vec32uc; };
        template<> struct Vec_N_T<16, int16_t> final { using type = Vec16s; };
        template<> struct Vec_N_T<16, uint16_t> final { using type = Vec16us; };
        template<> struct Vec_N_T<8, int32_t> final { using type = Vec8i; };
        template<> struct Vec_N_T<8, uint32_t> final { using type = Vec8ui; };
        template<> struct Vec_N_T<4, int64_t> final { using type = Vec4q; };
        template<> struct Vec_N_T<4, uint64_t> final { using type = Vec4uq; };
        // 512 Total bits
        template<> struct Vec_N_T<64, int8_t> final { using type = Vec64c; };
        template<> struct Vec_N_T<64, uint8_t> final { using type = Vec64uc; };
        template<> struct Vec_N_T<32, int16_t> final { using type = Vec32s; };
        template<> struct Vec_N_T<32, uint16_t> final { using type = Vec32us; };
        template<> struct Vec_N_T<16, int32_t> final { using type = Vec16i; };
        template<> struct Vec_N_T<16, uint32_t> final { using type = Vec16ui; };
        template<> struct Vec_N_T<8, int64_t> final { using type = Vec8q; };
        template<> struct Vec_N_T<8, uint64_t> final { using type = Vec8uq; };

        // Table 2.2 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
        // 128 Total bits
        template<> struct Vec_N_T<4, float> final { using type = Vec4f; };
        template<> struct Vec_N_T<2, double> final { using type = Vec2d; };
        // 256 Total bits
        template<> struct Vec_N_T<8, float> final { using type = Vec8f; };
        template<> struct Vec_N_T<4, double> final { using type = Vec4d; };
        // 512 Total bits
        template<> struct Vec_N_T<16, float> final { using type = Vec16f; };
        template<> struct Vec_N_T<8, double> final { using type = Vec8d; };
	}

	template<typename T, typename Abi = details::simd_abi::fixed_size<4>>
	class basic_simd {
	public:
		using value_type = T;
		//using reference = see below;

		static constexpr details::size_type size = Abi::size;
		 
		constexpr basic_simd() noexcept = default;

		// [simd.ctor], basic_simd constructors
		template<typename U> constexpr basic_simd(U&& value) noexcept : v_(value) {}
		template<typename U, typename UAbi>
		constexpr explicit basic_simd(const basic_simd<U, UAbi>& other) noexcept : v_(other.v_) { }
		template<typename G> constexpr explicit basic_simd(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept
		{

		}

    private:
        using vcl_type = details::Vec_N_T<size, T>::type; // e.g., Vec4i
        vcl_type v_;
	};

	template<typename T, details::size_type N = basic_simd<T>::size>
	using simd = basic_simd<T, details::simd_abi::fixed_size<N>>;
}

#ifdef VCL_NAMESPACE
}
#endif