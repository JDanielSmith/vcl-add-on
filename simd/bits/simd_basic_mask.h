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
        // Table 2.3 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
        template <size_t elements_per_vector, typename For_use_with> struct Vec_N_b;
        template<> struct Vec_N_b<16, int8_t> final { using type = Vec16cb; };
        template<> struct Vec_N_b<16, uint8_t> final { using type = Vec16cb; };
        template<> struct Vec_N_b<8, int16_t> final { using type = Vec8sb; };
        template<> struct Vec_N_b<8, uint16_t> final { using type = Vec8sb; };
        template<> struct Vec_N_b<4, int32_t> final { using type = Vec4ib; };
        template<> struct Vec_N_b<4, uint32_t> final { using type = Vec4ib; };
        template<> struct Vec_N_b<2, int64_t> final { using type = Vec2qb; };
        template<> struct Vec_N_b<2, uint64_t> final { using type = Vec2qb; };
        template<> struct Vec_N_b<32, int8_t> final { using type = Vec32cb; };
        template<> struct Vec_N_b<32, uint8_t> final { using type = Vec32cb; };
        template<> struct Vec_N_b<16, int16_t> final { using type = Vec16sb; };
        template<> struct Vec_N_b<16, uint16_t> final { using type = Vec16sb; };
        template<> struct Vec_N_b<8, int32_t> final { using type = Vec8ib; };
        template<> struct Vec_N_b<8, uint32_t> final { using type = Vec8ib; };
        template<> struct Vec_N_b<4, int64_t> final { using type = Vec4qb; };
        template<> struct Vec_N_b<4, uint64_t> final { using type = Vec4qb; };
        template<> struct Vec_N_b<64, int8_t> final { using type = Vec64cb; };
        template<> struct Vec_N_b<64, uint8_t> final { using type = Vec64cb; };
        template<> struct Vec_N_b<32, int16_t> final { using type = Vec32sb; };
        template<> struct Vec_N_b<32, uint16_t> final { using type = Vec32sb; };
        template<> struct Vec_N_b<16, int32_t> final { using type = Vec16ib; };
        template<> struct Vec_N_b<16, uint32_t> final { using type = Vec16ib; };
        template<> struct Vec_N_b<8, int64_t> final { using type = Vec8qb; };
        template<> struct Vec_N_b<8, uint64_t> final { using type = Vec8qb; };
        template<> struct Vec_N_b<4, float> final { using type = Vec4fb; };
        template<> struct Vec_N_b<2, double> final { using type = Vec2db; };
        template<> struct Vec_N_b<8, float> final { using type = Vec8fb; };
        template<> struct Vec_N_b<4, double> final { using type = Vec4db; };
        template<> struct Vec_N_b<16, float> final { using type = Vec16fb; };
        template<> struct Vec_N_b<8, double> final { using type = Vec8db; };
    }

	// 	template<size_t Bytes, typename Abi = details::simd_abi::fixed_size<4>> class basic_simd_mask {
	template<typename T, typename Abi = details::simd_abi::fixed_size<4>> class basic_simd_mask {
	public:
		using value_type = bool;
		//using reference = see below;
		using abi_type = Abi;

		static constexpr auto size = basic_simd<T, Abi>::size; // TODO: basic_simd<details::integer_from<Bytes>, Abi>::size;

		constexpr basic_simd_mask() noexcept = default;

        // [simd.mask.ctor]
        constexpr explicit basic_simd_mask(value_type v) noexcept : v_(v) {}
        template<typename U, class UAbi>// TODO: template<size_t UBytes, class UAbi>
        constexpr explicit basic_simd_mask(const basic_simd_mask<U, UAbi>& other) noexcept : v_(other.v_) {}
        template<typename G> constexpr explicit basic_simd_mask(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept
        {
        }

	private:
		using vcl_type_b = details::Vec_N_b<size, T>::type; // e.g., Vec4ib
        vcl_type_b v_;
	};

	template<typename T, details::size_type N = basic_simd_mask<T>::size>
	using simd_mask = basic_simd_mask<T, details::simd_abi::fixed_size<N>>; // TODO: sizeof(T)
}

#ifdef VCL_NAMESPACE
}
#endif