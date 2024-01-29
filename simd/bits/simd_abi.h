#pragma once

#include "simd.h"

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

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	namespace details
	{
		#if MAX_VECTOR_SIZE >= 512
		constexpr size_type max_vector_size = 512;
		#elif MAX_VECTOR_SIZE >= 256
		constexpr size_type max_vector_size = 256;
		#else
		constexpr size_type max_vector_size = 128;
		#endif

		// See tables 2.1 and 2.2 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<size_type N, typename T> struct Vec_N_T;
		// 128 Total bits
		template<> struct Vec_N_T<16, int8_t> { using type = Vec16c; };
		template<> struct Vec_N_T<16, uint8_t> { using type = Vec16uc; };
		template<> struct Vec_N_T<8, int16_t> { using type = Vec8s; };
		template<> struct Vec_N_T<8, uint16_t> { using type = Vec8us; };
		template<> struct Vec_N_T<4, int32_t> { using type = Vec4i; };
		template<> struct Vec_N_T<4, uint32_t> { using type = Vec4ui; };
		template<> struct Vec_N_T<2, int64_t> { using type = Vec2q; };
		template<> struct Vec_N_T<2, uint64_t> { using type = Vec2uq; };
		template<> struct Vec_N_T<4, float> { using type = Vec4f; };
		template<> struct Vec_N_T<2, double> { using type = Vec2d; };
		// 256 Total bits
		template<> struct Vec_N_T<32, int8_t> { using type = Vec32c; };
		template<> struct Vec_N_T<32, uint8_t> { using type = Vec32uc; };
		template<> struct Vec_N_T<16, int16_t> { using type = Vec16s; };
		template<> struct Vec_N_T<16, uint16_t> { using type = Vec16us; };
		template<> struct Vec_N_T<8, int32_t> { using type = Vec8i; };
		template<> struct Vec_N_T<8, uint32_t> { using type = Vec8ui; };
		template<> struct Vec_N_T<4, int64_t> { using type = Vec4q; };
		template<> struct Vec_N_T<4, uint64_t> { using type = Vec4uq; };
		template<> struct Vec_N_T<8, float> { using type = Vec8f; };
		template<> struct Vec_N_T<4, double> { using type = Vec4d; };
		// 512 Total bits
		template<> struct Vec_N_T<64, int8_t> { using type = Vec64c; };
		template<> struct Vec_N_T<64, uint8_t> { using type = Vec64uc; };
		template<> struct Vec_N_T<32, int16_t> { using type = Vec32s; };
		template<> struct Vec_N_T<32, uint16_t> { using type = Vec32us; };
		template<> struct Vec_N_T<16, int32_t> { using type = Vec16i; };
		template<> struct Vec_N_T<16, uint32_t> { using type = Vec16ui; };
		template<> struct Vec_N_T<8, int64_t> { using type = Vec8q; };
		template<> struct Vec_N_T<8, uint64_t> { using type = Vec8uq; };
		template<> struct Vec_N_T<16, float> { using type = Vec16f; };
		template<> struct Vec_N_T<8, double> { using type = Vec8d; };
		template<size_type N, typename T>
		using Vec = Vec_N_T<N, T>::type;

		// See tables 2.3 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<typename Vec> struct for_use_with_;
		// 128 Total bits
		template<> struct for_use_with_<Vec16c> { using type = Vec16cb; };
		template<> struct for_use_with_<Vec16uc> { using type = Vec16cb; };
		template<> struct for_use_with_<Vec8s> { using type = Vec8sb; };
		template<> struct for_use_with_<Vec8us> { using type = Vec8sb; };
		template<> struct for_use_with_<Vec4i> { using type = Vec4ib; };
		template<> struct for_use_with_<Vec4ui> { using type = Vec4ib; };
		template<> struct for_use_with_<Vec2q> { using type = Vec2qb; };
		template<> struct for_use_with_<Vec2uq> { using type = Vec2qb; };
		template<> struct for_use_with_<Vec4f> { using type = Vec4fb; };
		template<> struct for_use_with_<Vec2d> { using type = Vec2db; };
		// 256 Total bits
		template<> struct for_use_with_<Vec32c> { using type = Vec32cb; };
		template<> struct for_use_with_<Vec32uc> { using type = Vec32cb; };
		template<> struct for_use_with_<Vec16s> { using type = Vec16sb; };
		template<> struct for_use_with_<Vec16us> { using type = Vec16sb; };
		template<> struct for_use_with_<Vec8i> { using type = Vec8ib; };
		template<> struct for_use_with_<Vec8ui> { using type = Vec8ib; };
		template<> struct for_use_with_<Vec4q> { using type = Vec4qb; };
		template<> struct for_use_with_<Vec4uq> { using type = Vec4qb; };
		template<> struct for_use_with_<Vec8f> { using type = Vec8fb; };
		template<> struct for_use_with_<Vec4d> { using type = Vec4db; };
		// 512 Total bits
		template<> struct for_use_with_<Vec64c> { using type = Vec64cb; };
		template<> struct for_use_with_<Vec64uc> { using type = Vec64cb; };
		template<> struct for_use_with_<Vec32s> { using type = Vec32sb; };
		template<> struct for_use_with_<Vec32us> { using type = Vec32sb; };
		template<> struct for_use_with_<Vec16i> { using type = Vec16ib; };
		template<> struct for_use_with_<Vec16ui> { using type = Vec16ib; };
		template<> struct for_use_with_<Vec8q> { using type = Vec8qb; };
		template<> struct for_use_with_<Vec8uq> { using type = Vec8qb; };
		template<> struct for_use_with_<Vec16f> { using type = Vec16fb; };
		template<> struct for_use_with_<Vec8d> { using type = Vec8db; };
		template<typename Vec>
		using for_use_with = for_use_with_<Vec>::type;

		// See section 2.5 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<int elementtype> struct Vec_value_type_;
		//template<> struct Vec_value_type_<2> { using type = bool; }; // compact
		//template<> struct Vec_value_type_<3> { using type = bool; }; // broad
		template<> struct Vec_value_type_<4> { using type = std::int8_t; };
		template<> struct Vec_value_type_<5> { using type =  std::uint8_t; };
		template<> struct Vec_value_type_<6> { using type = std::int16_t; };
		template<> struct Vec_value_type_<7> { using type = std::uint16_t; };
		template<> struct Vec_value_type_<8> { using type = std::int32_t; };
		template<> struct Vec_value_type_<9> { using type = std::uint32_t; };
		template<> struct Vec_value_type_<10> { using type = std::int64_t; };
		template<> struct Vec_value_type_<11> { using type = std::uint64_t; };
		//template<> struct Vec_value_type_<15> { using type = float16_t; };
		template<> struct Vec_value_type_<16> { using type = float; };
		template<> struct Vec_value_type_<17> { using type = double; };
		template<int elementtype>
		using Vec_value_type = Vec_value_type_<elementtype>::type;

		namespace simd_abi
		{
			template<size_type width> struct fixed_size_;
			template<> struct fixed_size_<16> { };
			template<size_type N> using fixed_size = fixed_size_<N>;

			template<typename T> using native_abi = fixed_size<16>;

			// "The implementation-defined maximum for N is no smaller than 64."
			template<typename T, size_type N>
			using deduce_t = fixed_size<N>;
		}
	}
}

#ifdef VCL_NAMESPACE
}
#endif