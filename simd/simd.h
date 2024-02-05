/***************************  simd.h   *********************************
* Author:        Agner Fog
* Date created:  2024-02-02
* Last modified: 2024-02-02
* Version:       2.02.00
* Project:       Extension to vector class library
* Description:
* Allow client code using the vector class library to look more like it was using `std::simd::simd`.
* https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p1928r8.pdf
*
* © Copyright 2012-2024. Apache License version 2.0 or later
******************************************************************************/
#pragma once

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
		using size_type = int;

		// See tables 2.1 and 2.2 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		constexpr int detect_vector_size()
		{
			if constexpr (detected_instrset <= instrset::SSE2) return 128;
			if constexpr (detected_instrset <= instrset::AVX2) return 256;
			return 512;
		}
		constexpr auto detected_vector_size = detect_vector_size();
		constexpr auto detected_vector_size_bytes = detected_vector_size / 8;

		// VecNt<4, int32_t> == Vec4i
		// https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template <int Elements_per_vector, typename T> struct VecNt;

		// Table 2.1 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		// 128 Total bits
		template<> struct VecNt<16, int8_t> { using Vector_class = Vec16c; };
		template<> struct VecNt<16, uint8_t> { using Vector_class = Vec16uc; };
		template<> struct VecNt<8, int16_t> { using Vector_class = Vec8s; };
		template<> struct VecNt<8, uint16_t> { using Vector_class = Vec8us; };
		template<> struct VecNt<4, int32_t> { using Vector_class = Vec4i; };
		template<> struct VecNt<4, uint32_t> { using Vector_class = Vec4ui; };
		template<> struct VecNt<2, int64_t> { using Vector_class = Vec2q; };
		template<> struct VecNt<2, uint64_t> { using Vector_class = Vec2uq; };
		// 256 Total bits
		template<> struct VecNt<32, int8_t> { using Vector_class = Vec32c; };
		template<> struct VecNt<32, uint8_t> { using Vector_class = Vec32uc; };
		template<> struct VecNt<16, int16_t> { using Vector_class = Vec16s; };
		template<> struct VecNt<16, uint16_t> { using Vector_class = Vec16us; };
		template<> struct VecNt<8, int32_t> { using Vector_class = Vec8i; };
		template<> struct VecNt<8, uint32_t> { using Vector_class = Vec8ui; };
		template<> struct VecNt<4, int64_t> { using Vector_class = Vec4q; };
		template<> struct VecNt<4, uint64_t> { using Vector_class = Vec4uq; };
		// 512 Total bits
		template<> struct VecNt<64, int8_t> { using Vector_class = Vec64c; };
		template<> struct VecNt<64, uint8_t> { using Vector_class = Vec64uc; };
		template<> struct VecNt<32, int16_t> { using Vector_class = Vec32s; };
		template<> struct VecNt<32, uint16_t> { using Vector_class = Vec32us; };
		template<> struct VecNt<16, int32_t> { using Vector_class = Vec16i; };
		template<> struct VecNt<16, uint32_t> { using Vector_class = Vec16ui; };
		template<> struct VecNt<8, int64_t> { using Vector_class = Vec8q; };
		template<> struct VecNt<8, uint64_t> { using Vector_class = Vec8uq; };

		// Table 2.2 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		// 128 Total bits
		template<> struct VecNt<4, float> { using Vector_class = Vec4f; };
		template<> struct VecNt<2, double> { using Vector_class = Vec2d; };
		// 256 Total bits
		template<> struct VecNt<8, float> { using Vector_class = Vec8f; };
		template<> struct VecNt<4, double> { using Vector_class = Vec4d; };
		// 512 Total bits
		template<> struct VecNt<16, float> { using Vector_class = Vec16f; };
		template<> struct VecNt<8, double> { using Vector_class = Vec8d; };

		// Vec<4, int32_t> = Vec4i
		template <int Elements_per_vector, typename T>
		using Vec = VecNt<Elements_per_vector, T>::Vector_class;


		// See table 2.3 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		template <typename For_use_with> struct VecNb;
		// 128 Total bits
		template<> struct VecNb<Vec16c> { using Boolean_vector_class = Vec16cb; };
		template<> struct VecNb<Vec16uc> { using Boolean_vector_class = Vec16cb; };
		template<> struct VecNb<Vec8s> { using Boolean_vector_class = Vec8sb; };
		template<> struct VecNb<Vec8us> { using Boolean_vector_class = Vec8sb; };
		template<> struct VecNb<Vec4i> { using Boolean_vector_class = Vec4ib; };
		template<> struct VecNb<Vec4ui> { using Boolean_vector_class = Vec4ib; };
		template<> struct VecNb<Vec2q> { using Boolean_vector_class = Vec2qb; };
		template<> struct VecNb<Vec2uq> { using Boolean_vector_class = Vec2qb; };
		template<> struct VecNb<Vec4f> { using Boolean_vector_class = Vec4fb; };
		template<> struct VecNb<Vec2d> { using Boolean_vector_class = Vec2db; };
		// 256 Total bits
		template<> struct VecNb<Vec32c> { using Boolean_vector_class = Vec32cb; };
		template<> struct VecNb<Vec32uc> { using Boolean_vector_class = Vec32cb; };
		template<> struct VecNb<Vec16s> { using Boolean_vector_class = Vec16sb; };
		template<> struct VecNb<Vec16us> { using Boolean_vector_class = Vec16sb; };
		template<> struct VecNb<Vec8i> { using Boolean_vector_class = Vec8ib; };
		template<> struct VecNb<Vec8ui> { using Boolean_vector_class = Vec8ib; };
		template<> struct VecNb<Vec4q> { using Boolean_vector_class = Vec4qb; };
		template<> struct VecNb<Vec4uq> { using Boolean_vector_class = Vec4qb; };
		template<> struct VecNb<Vec8f> { using Boolean_vector_class = Vec8fb; };
		template<> struct VecNb<Vec4d> { using Boolean_vector_class = Vec4db; };
		// 512 Total bits
		template<> struct VecNb<Vec64c> { using Boolean_vector_class = Vec64cb; };
		template<> struct VecNb<Vec64uc> { using Boolean_vector_class = Vec64cb; };
		template<> struct VecNb<Vec32s> { using Boolean_vector_class = Vec32sb; };
		template<> struct VecNb<Vec32us> { using Boolean_vector_class = Vec32sb; };
		template<> struct VecNb<Vec16i> { using Boolean_vector_class = Vec16ib; };
		template<> struct VecNb<Vec16ui> { using Boolean_vector_class = Vec16ib; };
		template<> struct VecNb<Vec8q> { using Boolean_vector_class = Vec8qb; };
		template<> struct VecNb<Vec8uq> { using Boolean_vector_class = Vec8qb; };
		template<> struct VecNb<Vec16f> { using Boolean_vector_class = Vec16fb; };
		template<> struct VecNb<Vec8d> { using Boolean_vector_class = Vec8db; };
		
		// Boolean_vector_class<4, i> = Vec4ib
		template <int Elements_per_vector, typename T>
		using Boolean_vector_class = VecNb<Vec<Elements_per_vector, T>>::Boolean_vector_class;
	}

	template<typename T, int N> struct basic_simd_mask 
	{
		using Vec = details::Boolean_vector_class<N, T>; // e.g., Vec4ib
		Vec v_;

		using value_type = bool;

		constexpr basic_simd_mask() noexcept = default;

		// [simd.ctor]
		template<typename U> constexpr basic_simd_mask(U&& value) noexcept : v_(value) {}
		template<typename U, int N>
		constexpr explicit basic_simd_mask(const basic_simd_mask<U, N>& other) noexcept : v_(other.v_) {}
		template<typename G> constexpr explicit basic_simd_mask(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;
		// "Implementations should enable explicit conversion from and to implementation-defined types."
		constexpr explicit operator Vec() const { return v_; }
		constexpr explicit basic_simd_mask(const Vec& init) : v_(init) {}
	};

	template<typename T, int N=-1> struct basic_simd
	{
		using Vec = details::VecNt<N, T>::Vector_class; // e.g., Vec4i
		Vec v_;

		using value_type = T;
		using mask_type = basic_simd_mask<T, N>; // e.g., Vec4ib

		static constexpr std::integral_constant<details::size_type, Vec::size()> size;

		constexpr basic_simd() noexcept = default;

		// [simd.ctor]
		template<typename U> constexpr basic_simd(U&& value) noexcept : v_(value) {}
		template<typename U, int N>
		constexpr explicit basic_simd(const basic_simd<U, N>& other) noexcept : v_(other.v_) {}
		template<typename G> constexpr explicit basic_simd(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept
		{
			for (int i = 0; i < v_.size(); i++)
			{
				v_.insert(i, gen(i));
			}
		}
		//template<typename It, typename... Flags>
		//constexpr Vec_basic_simd(It first, simd_flags<Flags...> f = {})
		//{
		//	copy_from(first, f);
		//}
		//template<class It, class... Flags>
		//constexpr basic_simd(It first, const mask_type& mask, simd_flags<Flags...> = {});

		// "Implementations should enable explicit conversion from and to implementation-defined types."
		constexpr explicit operator Vec() const { return v_; }
		constexpr explicit basic_simd(const Vec& init) : v_(init) {}

		// [simd.copy]
		template<typename It>
		constexpr void copy_from(It first)
		{
			// TODO: look at simd_flags
			// However, §2.4 states "There is hardly any difference in efficiency
			// between `load` and `load_a` on newer microprocessors."

			// "`It` satisfies contiguous_iterator."
			const auto mem = &(*first);
			v_.load(mem);
		}
		//template<typename It, typename... Flags>
		//constexpr void copy_from(It first, const mask_type& mask, simd_flags<Flags...> f = {});
		template<typename Out>
		constexpr void copy_to(Out first) const
		{
			// TODO: look at simd_flags
			// However, §2.5 states "There is hardly any difference in efficiency
			// between `store` and `store_a` on newer microprocessors."

			// "`It` satisfies contiguous_iterator."
			auto mem = &(*first);
			v_.store(mem);
		}
		//template<typename Out, typename... Flags>
		//constexpr void copy_to(Out first, const mask_type& mask, simd_flags<Flags...> f = {}) const;

		// [simd.subscr]
		// §2.5 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		// "Note that you can read a vector element with the[] operator, but not write an element."
		constexpr value_type& operator[](details::size_type) & = delete;
		constexpr value_type operator[](details::size_type i) const& { return v_[i]; }

		// [simd.unary]
		constexpr basic_simd& operator++() noexcept;
		constexpr basic_simd operator++(int) noexcept;
		constexpr basic_simd& operator--() noexcept;
		constexpr basic_simd operator--(int) noexcept;
		constexpr mask_type operator!() const noexcept;
		constexpr basic_simd operator~() const noexcept;
		constexpr basic_simd operator+() const noexcept;
		constexpr basic_simd operator-() const noexcept;
	};

	template<class T>
	using simd = basic_simd<T, details::detected_vector_size_bytes / sizeof(T)>;

	//template<typename T, int N>
	//inline basic_simd<T, N> simd_select(const basic_simd_mask<T, N>& s, const basic_simd<T, N>& a, const basic_simd<T, N>& b) {
	//	return select(s, a, b);
	//}
}


#ifdef VCL_NAMESPACE
}
#endif
