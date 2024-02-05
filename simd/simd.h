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

#include "simd_abi.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	template<typename T, details::size_type N> struct basic_simd_mask 
	{
		using Vec = details::Boolean_vector_class<N, T>; // e.g., Vec4ib

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

	//private:
		Vec v_;
	};

	template<typename T, typename Abi = details::simd_abi::native_abi<T>> struct basic_simd
	{
		using abi_type = Abi;
		static constexpr auto N = abi_type::N;
		using Vec = details::VecNt<N, T>::Vector_class; // e.g., Vec4i

		using value_type = T;
		using mask_type = basic_simd_mask<T, N>; // e.g., Vec4ib

		static constexpr std::integral_constant<details::size_type, Vec::size()> size;

		constexpr basic_simd() noexcept = default;

		// [simd.ctor]
		template<typename U> constexpr basic_simd(U&& value) noexcept : v_(value) {}
		template<typename U, typename UAbi>
		constexpr explicit basic_simd(const basic_simd<U, UAbi>& other) noexcept : v_(other.v_) {}
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

	//private:
		Vec v_;
	};

	template<typename T, details::size_type N = basic_simd<T>::size()>
	using simd = basic_simd<T, details::simd_abi::deduce_t<T, N>>;
}


#ifdef VCL_NAMESPACE
}
#endif
