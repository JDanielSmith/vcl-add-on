#pragma once

#include <type_traits>

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

#include "simd_instrset.h"

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
		constexpr size_type detect_vector_size()
		{
			if constexpr (detected_instrset <= instrset::SSE2) return 128;
			if constexpr (detected_instrset <= instrset::AVX2) return 256;
			return 512;
		}
		static constexpr auto detected_vector_size = detect_vector_size();

		// See �2.5 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<int elementtype> struct Vec_value_type_;
		//template<> struct Vec_value_type_<2> { using type = bool; }; // compact
		//template<> struct Vec_value_type_<3> { using type = bool; }; // broad
		template<> struct Vec_value_type_<4> { using type = std::int8_t; };
		template<> struct Vec_value_type_<5> { using type = std::uint8_t; };
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

		// See tables 2.1 and 2.2 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<size_type N, typename T> struct vector_class_;
		template<size_type N, typename T, typename Vec> struct vector_class_base_
		{
			using Vector_class = Vec;
			static constexpr auto elements_per_vector = N; // aka "width" or "elements per vector"
			using type = T; // e.g., `int32_t` or `float`
			static constexpr auto total_bits = elements_per_vector * sizeof(type) * 8;

			static_assert(std::is_same_v<type, Vec_value_type<Vector_class::elementtype()>>);
			static_assert(elements_per_vector == Vector_class::size());
			static_assert(total_bits <= max_vector_size);
		};

		#define VECTORCLASS_vector_class_(N_, type_, suffix_) \
			template<> struct vector_class_<N_, type_> : public vector_class_base_<N_, type_, Vec ## N_ ## suffix_> { }
		#define VECTORCLASS_vector_class_integer(N_, bits_, suffix_) \
			VECTORCLASS_vector_class_(N_, int ## bits_ ## _t, suffix_); 	VECTORCLASS_vector_class_(N_, uint ## bits_ ## _t, u ## suffix_)

		// 128 Total bits
		VECTORCLASS_vector_class_integer(16, 8, c); // i.e., Vec16c and Vec16uc
		VECTORCLASS_vector_class_integer(8, 16, s); // i.e., Vec8s and Vec8us
		VECTORCLASS_vector_class_integer(4, 32, i); // i.e., Vec4i and Vec4ui
		VECTORCLASS_vector_class_integer(2, 64, q); // i.e., Vec2q and Vec2uq
		VECTORCLASS_vector_class_(4, float, f); // i.e., Vec4f
		VECTORCLASS_vector_class_(2, double, d); // i.e., Vec2d
		// 256 Total bits
		VECTORCLASS_vector_class_integer(32, 8, c); // i.e., Vec32c and Vec32uc
		VECTORCLASS_vector_class_integer(16, 16, s); // i.e., Vec16s and Vec16us
		VECTORCLASS_vector_class_integer(8, 32, i); // i.e., Vec8i and Vec8ui
		VECTORCLASS_vector_class_integer(4, 64, q); // i.e., Vec4q and Vec4uq
		VECTORCLASS_vector_class_(8, float, f); // i.e., Vec8f
		VECTORCLASS_vector_class_(4, double, d); // i.e., Vec4d
		// 512 Total bits
		VECTORCLASS_vector_class_integer(64, 8, c); // i.e., Vec64c and Vec64uc
		VECTORCLASS_vector_class_integer(32, 16, s); // i.e., Vec32s and Vec32us
		VECTORCLASS_vector_class_integer(16, 32, i); // i.e., Vec16i and Vec16ui
		VECTORCLASS_vector_class_integer(8, 64, q); // i.e., Vec8q and Vec8uq
		VECTORCLASS_vector_class_(16, float, f); // i.e., Vec16f
		VECTORCLASS_vector_class_(8, double, d); // i.e., Vec8d
		#undef VECTORCLASS_vector_class_integer
		#undef VECTORCLASS_vector_class_

		template<size_type N, typename T>
		using Vec = vector_class_<N, T>::Vector_class;

		// See tables 2.3 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<typename Vec> struct for_use_with_;
		#define VECTORCLASS_for_use_with_(N_, suffix_) \
			template<> struct for_use_with_<Vec ## N_ ## suffix_> { using Vector_class = Vec ## N_ ## suffix_ ## b; }; \
			template<> struct for_use_with_<Vec ## N_ ## u ## suffix_> { using Vector_class = Vec ## N_ ## suffix_ ## b; }
		// 128 Total bits
		VECTORCLASS_for_use_with_(16, c); // i.e., Vec16cb
		VECTORCLASS_for_use_with_(8, s); // i.e., Vec8sb
		VECTORCLASS_for_use_with_(4, i); // i.e., Vec4ib
		VECTORCLASS_for_use_with_(2, q); // i.e., Vec2qb
		template<> struct for_use_with_<Vec4f> { using Vector_class = Vec4fb; };
		template<> struct for_use_with_<Vec2d> { using Vector_class = Vec2db; };
		// 256 Total bits
		VECTORCLASS_for_use_with_(32, c); // i.e., Vec32cb
		VECTORCLASS_for_use_with_(16, s); // i.e., Vec16sb
		VECTORCLASS_for_use_with_(8, i); // i.e., Vec8ib
		VECTORCLASS_for_use_with_(4, q); // i.e., Vec4qb
		template<> struct for_use_with_<Vec8f> { using Vector_class = Vec8fb; };
		template<> struct for_use_with_<Vec4d> { using Vector_class = Vec4db; };
		// 512 Total bits
		VECTORCLASS_for_use_with_(64, c); // i.e., Vec64cb
		VECTORCLASS_for_use_with_(32, s); // i.e., Vec32sb
		VECTORCLASS_for_use_with_(16, i); // i.e., Vec16ib
		VECTORCLASS_for_use_with_(8, q); // i.e., Vec8qb
		template<> struct for_use_with_<Vec16f> { using Vector_class = Vec16fb; };
		template<> struct for_use_with_<Vec8d> { using Vector_class = Vec8db; };
		#undef VECTORCLASS_for_use_with_
		template<typename Vec>
		using for_use_with = for_use_with_<Vec>::Vector_class;

		template<size_type width> struct fixed_size_;
		template<> struct fixed_size_<2> { static constexpr size_type vector_size = 128; };
		template<> struct fixed_size_<4> { static constexpr size_type vector_size = 256; /* or 128 */ };
		template<> struct fixed_size_<8> { static constexpr size_type vector_size = max_vector_size; /* or 128 or 256 */ };
		template<> struct fixed_size_<16> { static constexpr size_type vector_size = max_vector_size; /* or 128 or 256 */ };
		template<> struct fixed_size_<32> { static constexpr size_type vector_size = max_vector_size; /* or 256 */ };
		template<> struct fixed_size_<64> { static constexpr size_type vector_size = max_vector_size; };

		template <typename T, size_type vector_size> struct native_abi_ {};
		// See tables 2.1 and 2.2 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		// 128 Total bits
		template<> struct native_abi_<int8_t, 128> { using fixed_size = fixed_size_<16>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<uint8_t, 128> { using fixed_size = fixed_size_<16>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<int16_t, 128> { using fixed_size = fixed_size_<8>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<uint16_t, 128> { using fixed_size = fixed_size_<8>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<int32_t, 128> { using fixed_size = fixed_size_<4>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<uint32_t, 128> { using fixed_size = fixed_size_<4>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<int64_t, 128> { using fixed_size = fixed_size_<2>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<uint64_t, 128> { using fixed_size = fixed_size_<2>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<float, 128> { using fixed_size = fixed_size_<4>; static constexpr size_type vector_size = 128; };
		template<> struct native_abi_<double, 128> { using fixed_size = fixed_size_<2>; static constexpr size_type vector_size = 128; };
		// 256 Total bits
		template<> struct native_abi_<int8_t, 256> { using fixed_size = fixed_size_<32>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<uint8_t, 256> { using fixed_size = fixed_size_<32>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<int16_t, 256> { using fixed_size = fixed_size_<16>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<uint16_t, 256> { using fixed_size = fixed_size_<16>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<int32_t, 256> { using fixed_size = fixed_size_<8>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<uint32_t, 256> { using fixed_size = fixed_size_<8>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<int64_t, 256> { using fixed_size = fixed_size_<4>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<uint64_t, 256> { using fixed_size = fixed_size_<4>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<float, 256> { using fixed_size = fixed_size_<8>; static constexpr size_type vector_size = 256; };
		template<> struct native_abi_<double, 256> { using fixed_size = fixed_size_<4>; static constexpr size_type vector_size = 256; };
		// 512 Total bits
		template<> struct native_abi_<int8_t, 512> { using fixed_size = fixed_size_<64>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<uint8_t, 512> { using fixed_size = fixed_size_<64>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<int16_t, 512> { using fixed_size = fixed_size_<32>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<uint16_t, 512> { using fixed_size = fixed_size_<32>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<int32_t, 512> { using fixed_size = fixed_size_<16>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<uint32_t, 512> { using fixed_size = fixed_size_<16>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<int64_t, 512> { using fixed_size = fixed_size_<8>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<uint64_t, 512> { using fixed_size = fixed_size_<8>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<float, 512> { using fixed_size = fixed_size_<16>; static constexpr size_type vector_size = 512; };
		template<> struct native_abi_<double, 512> { using fixed_size = fixed_size_<8>; static constexpr size_type vector_size = 512; };

		template <typename T, size_type vector_size, size_type N> struct deduce_t_ {};
		// See tables 2.1 and 2.2 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		// 128 Total bits
		template<> struct deduce_t_<int8_t, 128, 16> { using fixed_size = fixed_size_<16>; };
		template<> struct deduce_t_<uint8_t, 128, 16> { using fixed_size = fixed_size_<16>; };
		template<> struct deduce_t_<int16_t, 128, 8> { using fixed_size = fixed_size_<8>; };
		template<> struct deduce_t_<uint16_t, 128, 8> { using fixed_size = fixed_size_<8>; };
		template<> struct deduce_t_<int32_t, 128, 4> { using fixed_size = fixed_size_<4>; };
		template<> struct deduce_t_<uint32_t, 128, 4> { using fixed_size = fixed_size_<4>; };
		template<> struct deduce_t_<int64_t, 128, 2> { using fixed_size = fixed_size_<2>; };
		template<> struct deduce_t_<uint64_t, 128, 2> { using fixed_size = fixed_size_<2>; };
		template<> struct deduce_t_<float, 128, 4> { using fixed_size = fixed_size_<4>; };
		template<> struct deduce_t_<double, 128, 2> { using fixed_size = fixed_size_<2>; };
		// 256 Total bits
		template<> struct deduce_t_<int8_t, 256, 32> { using fixed_size = fixed_size_<32>; };
		template<> struct deduce_t_<uint8_t, 256, 32> { using fixed_size = fixed_size_<32>; };
		template<> struct deduce_t_<int16_t, 256, 16> { using fixed_size = fixed_size_<16>; };
		template<> struct deduce_t_<uint16_t, 256, 16> { using fixed_size = fixed_size_<16>; };
		template<> struct deduce_t_<int32_t, 256, 8> { using fixed_size = fixed_size_<8>; };
		template<> struct deduce_t_<uint32_t, 256, 8> { using fixed_size = fixed_size_<8>; };
		template<> struct deduce_t_<int64_t, 256, 4> { using fixed_size = fixed_size_<4>; };
		template<> struct deduce_t_<uint64_t, 256, 4> { using fixed_size = fixed_size_<4>; };
		template<> struct deduce_t_<float, 256, 8> { using fixed_size = fixed_size_<8>; };
		template<> struct deduce_t_<double, 256, 4> { using fixed_size = fixed_size_<4>; };
		// 512 Total bits
		template<> struct deduce_t_<int8_t, 512, 64> { using fixed_size = fixed_size_<64>; };
		template<> struct deduce_t_<uint8_t, 512, 64> { using fixed_size = fixed_size_<64>; };
		template<> struct deduce_t_<int16_t, 512, 32> { using fixed_size = fixed_size_<32>; };
		template<> struct deduce_t_<uint16_t, 512, 32> { using fixed_size = fixed_size_<32>; };
		template<> struct deduce_t_<int32_t, 512, 16> { using fixed_size = fixed_size_<16>; };
		template<> struct deduce_t_<uint32_t, 512, 16> { using fixed_size = fixed_size_<16>; };
		template<> struct deduce_t_<int64_t, 512, 8> { using fixed_size = fixed_size_<8>; };
		template<> struct deduce_t_<uint64_t, 512, 8> { using fixed_size = fixed_size_<8>; };
		template<> struct deduce_t_<float, 512, 16> { using fixed_size = fixed_size_<16>; };
		template<> struct deduce_t_<double, 512, 8> { using fixed_size = fixed_size_<8>; };

		namespace simd_abi
		{
			template<size_type N>
			using fixed_size = fixed_size_<N>;

			template<typename T>
			using native_abi = native_abi_<T, max_vector_size>::fixed_size;

			template<typename T, size_type N, typename Abi = native_abi_<T, max_vector_size>>
			using deduce_t = deduce_t_<T, Abi::vector_size, N>::fixed_size;
		}
	}
}

#ifdef VCL_NAMESPACE
}
#endif