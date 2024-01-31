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
		template<int elementtype> struct Vec_elementtype_;
		//template<> struct Vec_elementtype_<2> { using type = bool; }; // compact
		//template<> struct Vec_elementtype_<3> { using type = bool; }; // broad
		template<> struct Vec_elementtype_<4> { using type = std::int8_t; };
		template<> struct Vec_elementtype_<5> { using type = std::uint8_t; };
		template<> struct Vec_elementtype_<6> { using type = std::int16_t; };
		template<> struct Vec_elementtype_<7> { using type = std::uint16_t; };
		template<> struct Vec_elementtype_<8> { using type = std::int32_t; };
		template<> struct Vec_elementtype_<9> { using type = std::uint32_t; };
		template<> struct Vec_elementtype_<10> { using type = std::int64_t; };
		template<> struct Vec_elementtype_<11> { using type = std::uint64_t; };
		//template<> struct Vec_elementtype_<15> { using type = float16_t; };
		template<> struct Vec_elementtype_<16> { using type = float; };
		template<> struct Vec_elementtype_<17> { using type = double; };
		template<int elementtype>
		using Vec_elementtype = Vec_elementtype_<elementtype>::type;

		// https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template <size_t Elements_per_vector, typename T> struct Vec_N_T;
		// Table 2.1 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		// Table 2.2 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		// 128 Total bits
		template<> struct Vec_N_T<16, int8_t> final { using Vector_class = Vec16c; };
		template<> struct Vec_N_T<16, uint8_t> final { using Vector_class = Vec16uc; };
		template<> struct Vec_N_T<8, int16_t> final { using Vector_class = Vec8s; };
		template<> struct Vec_N_T<8, uint16_t> final { using Vector_class = Vec8us; };
		template<> struct Vec_N_T<4, int32_t> final { using Vector_class = Vec4i; };
		template<> struct Vec_N_T<4, uint32_t> final { using Vector_class = Vec4ui; };
		template<> struct Vec_N_T<2, int64_t> final { using Vector_class = Vec2q; };
		template<> struct Vec_N_T<2, uint64_t> final { using Vector_class = Vec2uq; };
		template<> struct Vec_N_T<4, float> final { using Vector_class = Vec4f; };
		template<> struct Vec_N_T<2, double> final { using Vector_class = Vec2d; };
		// 256 Total bits
		template<> struct Vec_N_T<32, int8_t> final { using Vector_class = Vec32c; };
		template<> struct Vec_N_T<32, uint8_t> final { using Vector_class = Vec32uc; };
		template<> struct Vec_N_T<16, int16_t> final { using Vector_class = Vec16s; };
		template<> struct Vec_N_T<16, uint16_t> final { using Vector_class = Vec16us; };
		template<> struct Vec_N_T<8, int32_t> final { using Vector_class = Vec8i; };
		template<> struct Vec_N_T<8, uint32_t> final { using Vector_class = Vec8ui; };
		template<> struct Vec_N_T<4, int64_t> final { using Vector_class = Vec4q; };
		template<> struct Vec_N_T<4, uint64_t> final { using Vector_class = Vec4uq; };
		template<> struct Vec_N_T<8, float> final { using Vector_class = Vec8f; };
		template<> struct Vec_N_T<4, double> final { using Vector_class = Vec4d; };
		// 512 Total bits
		template<> struct Vec_N_T<64, int8_t> final { using Vector_class = Vec64c; };
		template<> struct Vec_N_T<64, uint8_t> final { using Vector_class = Vec64uc; };
		template<> struct Vec_N_T<32, int16_t> final { using Vector_class = Vec32s; };
		template<> struct Vec_N_T<32, uint16_t> final { using Vector_class = Vec32us; };
		template<> struct Vec_N_T<16, int32_t> final { using Vector_class = Vec16i; };
		template<> struct Vec_N_T<16, uint32_t> final { using Vector_class = Vec16ui; };
		template<> struct Vec_N_T<8, int64_t> final { using Vector_class = Vec8q; };
		template<> struct Vec_N_T<8, uint64_t> final { using Vector_class = Vec8uq; };
		template<> struct Vec_N_T<16, float> final { using Vector_class = Vec16f; };
		template<> struct Vec_N_T<8, double> final { using Vector_class = Vec8d; };
		//
		template<size_type N, typename T>  // Vec<8, int32_t> == Vec8i
		using Vec = Vec_N_T<N, T>::Vector_class;

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
		template<typename Vec_N_T> // e.g., Vec4i
		struct Vec_native_abi
		{
			using Vector_class = Vec_N_T; // e.g., Vec4i
			static constexpr auto Elements_per_vector = Vector_class::size(); // aka "width"
			using elementtype = Vec_elementtype<Vector_class::elementtype()>; // e.g., `int32_t
			static constexpr auto Total_bits = Elements_per_vector * sizeof(elementtype) * 8; // 128, 256 or 512
			static_assert(Total_bits <= MAX_VECTOR_SIZE);

			using fixed_size = fixed_size_<Elements_per_vector, Total_bits>;
		};
		template<size_type N, typename T>
		using Vcl_native_abi = Vec_native_abi<Vec<N, T>>;

		// See table 2.3 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template<size_type N, typename Vec> struct Vclb_native_abi;
		template<size_type N, typename Vec, typename Vecb> struct Vclb_native_abi_base
		{
			using Boolean_vector_class = Vecb; // e.g., Vec4ib
			using For_use_with = Vec; // i.e., Vec4i or Vec4ui
			static constexpr auto Elements_per_vector = N; // aka "width"
			using type = bool;
			static constexpr auto Total_bits = Elements_per_vector * sizeof(type) * 8; // 128, 256 or 512

			//static_assert(std::is_same_v<type, Vec_elementtype<Vector_class::elementtype()>>);
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