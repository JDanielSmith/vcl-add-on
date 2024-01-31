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
		// See tables 2.1 and 2.2 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		constexpr size_type detect_vector_size()
		{
			if constexpr (detected_instrset <= instrset::SSE2) return 128;
			if constexpr (detected_instrset <= instrset::AVX2) return 256;
			return 512;
		}
		constexpr auto detected_vector_size = detect_vector_size();

		// See §2.5 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
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

		template<size_type N, size_type Total_bits> struct fixed_size_;
		template<size_type N, size_type Total_bits_> struct fixed_size_base
		{
			static constexpr auto Elements_per_vector = N; // aka "width"
			static constexpr auto Total_bits = Total_bits_;
		};
		#define VECTORCLASS_fixed_size_(N_, bits_) template<> struct fixed_size_<N_, bits_> : public fixed_size_base<N_, bits_> { }
		VECTORCLASS_fixed_size_(2, 128);
		VECTORCLASS_fixed_size_(4, 128); VECTORCLASS_fixed_size_(4, 256);
		VECTORCLASS_fixed_size_(8, 128); VECTORCLASS_fixed_size_(8, 256); VECTORCLASS_fixed_size_(8, 512);
		VECTORCLASS_fixed_size_(16, 128); VECTORCLASS_fixed_size_(16, 256); 	VECTORCLASS_fixed_size_(16, 512);
		VECTORCLASS_fixed_size_(32, 256); VECTORCLASS_fixed_size_(32, 512);
		VECTORCLASS_fixed_size_(64, 512);
		#undef VECTORCLASS_fixed_size_

		// See tables 2.1 and 2.2 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<size_type N, typename T> struct Vcl_native_abi;
		template<size_type N, typename T, typename Vec> struct Vcl_native_abi_base
		{
			using Vector_class = Vec; // e.g., Vec4i
			static constexpr auto Elements_per_vector = N; // aka "width"
			using type = T; // e.g., `int32_t` or `float`
			static constexpr auto Total_bits = Elements_per_vector * sizeof(type) * 8; // 128, 256 or 512

			static_assert(std::is_same_v<type, Vec_value_type<Vector_class::elementtype()>>);
			static_assert(Elements_per_vector == Vector_class::size());
			static_assert(Total_bits <= MAX_VECTOR_SIZE);

			using fixed_size = fixed_size_<Elements_per_vector, Total_bits>;
		};
		#define VECTORCLASS_Vcl_native_abi(N_, type_, suffix_) \
			template<> struct Vcl_native_abi<N_, type_> : public Vcl_native_abi_base<N_, type_, Vec ## N_ ## suffix_> { }
		#define VECTORCLASS_Vcl_native_abi_integer(N_, bits_, suffix_) \
			VECTORCLASS_Vcl_native_abi(N_, int ## bits_ ## _t, suffix_); VECTORCLASS_Vcl_native_abi(N_, uint ## bits_ ## _t, u ## suffix_)
		// 128 Total bits
		VECTORCLASS_Vcl_native_abi_integer(16, 8, c); // i.e., Vec16c and Vec16uc
		VECTORCLASS_Vcl_native_abi_integer(8, 16, s); // i.e., Vec8s and Vec8us
		VECTORCLASS_Vcl_native_abi_integer(4, 32, i); // i.e., Vec4i and Vec4ui
		VECTORCLASS_Vcl_native_abi_integer(2, 64, q); // i.e., Vec2q and Vec2uq
		VECTORCLASS_Vcl_native_abi(4, float, f); // i.e., Vec4f
		VECTORCLASS_Vcl_native_abi(2, double, d); // i.e., Vec2d
		// 256 Total bits
		VECTORCLASS_Vcl_native_abi_integer(32, 8, c); // i.e., Vec32c and Vec32uc
		VECTORCLASS_Vcl_native_abi_integer(16, 16, s); // i.e., Vec16s and Vec16us
		VECTORCLASS_Vcl_native_abi_integer(8, 32, i); // i.e., Vec8i and Vec8ui
		VECTORCLASS_Vcl_native_abi_integer(4, 64, q); // i.e., Vec4q and Vec4uq
		VECTORCLASS_Vcl_native_abi(8, float, f); // i.e., Vec8f
		VECTORCLASS_Vcl_native_abi(4, double, d); // i.e., Vec4d
		// 512 Total bits
		VECTORCLASS_Vcl_native_abi_integer(64, 8, c); // i.e., Vec64c and Vec64uc
		VECTORCLASS_Vcl_native_abi_integer(32, 16, s); // i.e., Vec32s and Vec32us
		VECTORCLASS_Vcl_native_abi_integer(16, 32, i); // i.e., Vec16i and Vec16ui
		VECTORCLASS_Vcl_native_abi_integer(8, 64, q); // i.e., Vec8q and Vec8uq
		VECTORCLASS_Vcl_native_abi(16, float, f); // i.e., Vec16f
		VECTORCLASS_Vcl_native_abi(8, double, d); // i.e., Vec8d
		#undef VECTORCLASS_Vcl_native_abi_integer
		#undef VECTORCLASS_Vcl_native_abi

		template<size_type N, typename T>
		using Vec = Vcl_native_abi<N, T>::Vector_class;

		// See table 2.3 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<size_type N, typename Vec> struct Vclb_native_abi;
		template<size_type N, typename Vec, typename Vecb> struct Vclb_native_abi_base
		{
			using Boolean_vector_class = Vecb; // e.g., Vec4ib
			using For_use_with = Vec; // i.e., Vec4i or Vec4ui
			static constexpr auto Elements_per_vector = N; // aka "width"
			using type = bool;
			static constexpr auto Total_bits = Elements_per_vector * sizeof(type) * 8; // 128, 256 or 512

			//static_assert(std::is_same_v<type, Vec_value_type<Vector_class::elementtype()>>);
			static_assert(Elements_per_vector == Boolean_vector_class::size());
			//static_assert(Elements_per_vector == Vcl_native_abi<N, For_use_with>::Elements_per_vector);
			static_assert(Total_bits <= MAX_VECTOR_SIZE);

			using fixed_size = fixed_size_<Elements_per_vector, Total_bits>;
		};
		#define VECTORCLASS_Vclb_native_abi(N_, suffix_) \
			template<> struct Vclb_native_abi<N_, Vec ## N_ ## suffix_> : public Vclb_native_abi_base<N_, Vec ## N_ ## suffix_, Vec ## N_ ## suffix_ ## b>{}; \
			template<> struct Vclb_native_abi<N_, Vec ## N_ ## u ## suffix_> : public Vclb_native_abi_base<N_, Vec ## N_ ## suffix_, Vec ## N_ ## suffix_ ## b>{}
		// 128 Total bits
		VECTORCLASS_Vclb_native_abi(16, c); // i.e., Vec16cb
		VECTORCLASS_Vclb_native_abi(8, s); // i.e., Vec8sb
		VECTORCLASS_Vclb_native_abi(4, i); // i.e., Vec4ib
		VECTORCLASS_Vclb_native_abi(2, q); // i.e., Vec2qb
		template<> struct Vclb_native_abi<4, Vec4f> : public Vclb_native_abi_base<4, Vec4f, Vec4fb> {};
		template<> struct Vclb_native_abi<2, Vec2d> : public Vclb_native_abi_base<2, Vec2d, Vec2db> {};
		// 256 Total bits
		VECTORCLASS_Vclb_native_abi(32, c); // i.e., Vec32cb
		VECTORCLASS_Vclb_native_abi(16, s); // i.e., Vec16sb
		VECTORCLASS_Vclb_native_abi(8, i); // i.e., Vec8ib
		VECTORCLASS_Vclb_native_abi(4, q); // i.e., Vec4qb
		template<> struct Vclb_native_abi<8, Vec8f> : public Vclb_native_abi_base<8, Vec8f, Vec8fb> {};
		template<> struct Vclb_native_abi<4, Vec4d> : public Vclb_native_abi_base<4, Vec4d, Vec4db> {};
		VECTORCLASS_Vclb_native_abi(64, c); // i.e., Vec64cb
		VECTORCLASS_Vclb_native_abi(32, s); // i.e., Vec32sb
		VECTORCLASS_Vclb_native_abi(16, i); // i.e., Vec16ib
		VECTORCLASS_Vclb_native_abi(8, q); // i.e., Vec8qb
		template<> struct Vclb_native_abi<16, Vec16f> : public Vclb_native_abi_base<16, Vec16f, Vec16fb> {};
		template<> struct Vclb_native_abi<8, Vec8d> : public Vclb_native_abi_base<8, Vec8d, Vec8db> {};
		#undef VECTORCLASS_Vclb_native_abi

		namespace simd_abi
		{
			template<size_type N>
			using fixed_size = fixed_size_<N, detected_vector_size>;

			template <typename T, size_type Total_bits>
			using native_abi_ = Vcl_native_abi<(Total_bits / 8) / sizeof(T), T>;
			template <typename T>
			using native_abi = native_abi_<T, detected_vector_size>::fixed_size;

			template<typename T, size_type N, typename Abi = native_abi_<T, detected_vector_size>>
			using deduce_t = Vcl_native_abi<N, T>::fixed_size;
		}
	}
}

#ifdef VCL_NAMESPACE
}
#endif