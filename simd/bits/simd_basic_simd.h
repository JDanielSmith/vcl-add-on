#pragma once

#include <memory>
#include <type_traits>

#include "simd.h"
#include "simd_abi.h"

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
	/*
	template<class T, class Abi = native-abi<T>> class basic_simd;
	*/
	template<typename T, typename Abi = details::simd_abi::native_abi<T>>
	class basic_simd {
	public:
		using value_type = T;
		//using reference = see below;
		using mask_type = basic_simd_mask<T, Abi>; // TODO: basic_simd_mask<sizeof(T), Abi>; ???
		using abi_type = Abi;

		// "This member is present even if the particular basic_simd specialization is not supported."
		static constexpr std::integral_constant<details::size_type, -1> size;
		 
		constexpr basic_simd() noexcept = default;

		// [simd.ctor]
		template<typename U> constexpr basic_simd(U&& value) noexcept;
		template<typename U, typename UAbi>
		constexpr explicit basic_simd(const basic_simd<U, UAbi>& other) noexcept;
		template<typename G> constexpr explicit basic_simd(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;
		//template<typename It, typename... Flags>
		//constexpr basic_simd(It first, simd_flags<Flags...> = {});
		//template<typename It, typename... Flags>
		//constexpr basic_simd(It first, const mask_type& mask, simd_flags<Flags...> = {});

		// [simd.copy]
		template<typename It, typename... Flags>
		constexpr void copy_from(It first, simd_flags<Flags...> f = {});
		template<typename It, typename... Flags>
		constexpr void copy_from(It first, const mask_type& mask, simd_flags<Flags...> f = {});
		template<typename Out, typename... Flags>
		constexpr void copy_to(Out first, simd_flags<Flags...> f = {}) const;
		template<typename Out, typename... Flags>
		constexpr void copy_to(Out first, const mask_type& mask, simd_flags<Flags...> f = {}) const;

		// [simd.subscr]
		constexpr auto& operator[](details::size_type)&;
		constexpr value_type operator[](details::size_type) const&;

		// [simd.unary]
		constexpr basic_simd& operator++() noexcept;
		constexpr basic_simd operator++(int) noexcept;
		constexpr basic_simd& operator--() noexcept;
		constexpr basic_simd operator--(int) noexcept;
		constexpr mask_type operator!() const noexcept;
		constexpr basic_simd operator~() const noexcept;
		constexpr basic_simd operator+() const noexcept;
		constexpr basic_simd operator-() const noexcept;

		// [simd.binary]
		friend constexpr basic_simd operator+(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator-(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator*(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator/(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator%(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator&(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator|(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator^(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator<<(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator>>(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd operator<<(const basic_simd&, details::size_type) noexcept;
		friend constexpr basic_simd operator>>(const basic_simd&, details::size_type) noexcept;

		// [simd.cassign]
		friend constexpr basic_simd& operator+=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator-=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator*=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator/=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator%=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator&=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator|=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator^=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator<<=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator>>=(basic_simd&, const basic_simd&) noexcept;
		friend constexpr basic_simd& operator<<=(basic_simd&, details::size_type) noexcept;
		friend constexpr basic_simd& operator>>=(basic_simd&, details::size_type) noexcept;

		// [simd.comparison]
		friend constexpr mask_type operator==(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr mask_type operator!=(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr mask_type operator>=(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr mask_type operator<=(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr mask_type operator>(const basic_simd&, const basic_simd&) noexcept;
		friend constexpr mask_type operator<(const basic_simd&, const basic_simd&) noexcept;
	};

	namespace details
	{
		// The proposal calls for explicit specializations of `basic_simd`; that's because
		// normal implementations will need code specific to each specialization.
		// Since this is built on VCL, that work has already been done, it's
		// just called `Vec4i` instead of `basic_simd<int, 4>`.
		template<typename Vec>
		class Vec_basic_simd {
		public:
			using Vec_type = Vec;
			using value_type = Vec_value_type<Vec_type::elementtype()>;
			//using reference = see below;
			using abi_type = details::simd_abi::fixed_size<Vec_type::size()>;
			using mask_type = basic_simd_mask<value_type, abi_type>; // TODO: basic_simd_mask<sizeof(T), Abi>; ???

			static constexpr std::integral_constant<details::size_type, Vec::size()> size;

			constexpr Vec_basic_simd() noexcept = default;

			// [simd.ctor]
			template<typename U> constexpr Vec_basic_simd(U&& value) noexcept : v_(value) {}
			template<typename UVec>
			constexpr explicit Vec_basic_simd(const Vec_basic_simd<UVec>& other) noexcept : v_(other.v_) {}
			template<typename G> constexpr explicit Vec_basic_simd(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;
			//template<typename It, typename... Flags>
			//constexpr Vec_basic_simd(It first, simd_flags<Flags...> f = {})
			//{
			//	copy_from(first, f);
			//}
			//template<class It, class... Flags>
			//constexpr basic_simd(It first, const mask_type& mask, simd_flags<Flags...> = {});

			// "Implementations should enable explicit conversion from and to implementation-defined types."
			constexpr explicit operator Vec_type() const { return v_; }
			constexpr explicit Vec_basic_simd(const Vec_type& init) : v_(init) {}

			// [simd.copy]
			template<typename It, typename... Flags>
			constexpr void copy_from(It first, simd_flags<Flags...> = {})
			{
				// TODO: look at simd_flags
				// However, section 2.4 states "There is hardly any difference in efficiency
				// between `load` and `load_a` on newer microprocessors."

				// "`It` satisfies contiguous_iterator."
				const auto mem = &(*first);
				v_.load(mem);
			}
			//template<typename It, typename... Flags>
			//constexpr void copy_from(It first, const mask_type& mask, simd_flags<Flags...> f = {});
			template<typename Out, typename... Flags>
			constexpr void copy_to(Out first, simd_flags<Flags...> = {}) const
			{
				// TODO: look at simd_flags
				// However, section 2.5 states "There is hardly any difference in efficiency
				// between `store` and `store_a` on newer microprocessors."

				// "`It` satisfies contiguous_iterator."
				auto mem = &(*first);
				v_.store(mem);
			}
			//template<typename Out, typename... Flags>
			//constexpr void copy_to(Out first, const mask_type& mask, simd_flags<Flags...> f = {}) const;

			// [simd.subscr]
			// Section 2.5 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
			// "Note that you can read a vector element with the[] operator, but not write an element."
			constexpr value_type& operator[](details::size_type) & = delete;
			constexpr value_type operator[](details::size_type i) const& { return v_[i]; }
			Vec_type v_;
		};
	}

	#define VECTORCLASS_basic_simd(type_, size_) \
	template<> class basic_simd<type_, details::simd_abi::fixed_size<size_>> : public details::Vec_basic_simd<details::Vec<size_, type_>> { }

	// "... The specialization basic_simd<T, Abi> is supported if ... Abi is simd_abi::fixed_size<N>, ..."
	// 128 Total bits
	VECTORCLASS_basic_simd(int8_t, 16);
	VECTORCLASS_basic_simd(uint8_t, 16);
	VECTORCLASS_basic_simd(int16_t, 8);
	VECTORCLASS_basic_simd(uint16_t, 8);
	VECTORCLASS_basic_simd(int32_t, 4);
	VECTORCLASS_basic_simd(uint32_t, 4);
	VECTORCLASS_basic_simd(int64_t, 2);
	VECTORCLASS_basic_simd(uint64_t, 2);
	VECTORCLASS_basic_simd(float, 4);
	VECTORCLASS_basic_simd(double, 2);
	// 256 Total bits
	VECTORCLASS_basic_simd(int8_t, 32);
	VECTORCLASS_basic_simd(uint8_t, 32);
	VECTORCLASS_basic_simd(int16_t, 16);
	VECTORCLASS_basic_simd(uint16_t, 16);
	VECTORCLASS_basic_simd(int32_t, 8);
	VECTORCLASS_basic_simd(uint32_t, 8);
	VECTORCLASS_basic_simd(int64_t, 4);
	VECTORCLASS_basic_simd(uint64_t, 4);
	VECTORCLASS_basic_simd(float, 8);
	VECTORCLASS_basic_simd(double, 4);
	// 512 Total bits
	VECTORCLASS_basic_simd(int8_t, 64);
	VECTORCLASS_basic_simd(uint8_t, 64);
	VECTORCLASS_basic_simd(int16_t, 32);
	VECTORCLASS_basic_simd(uint16_t, 32);
	VECTORCLASS_basic_simd(int32_t, 16);
	VECTORCLASS_basic_simd(uint32_t, 16);
	VECTORCLASS_basic_simd(int64_t, 8);
	VECTORCLASS_basic_simd(uint64_t, 8);
	VECTORCLASS_basic_simd(float, 16);
	VECTORCLASS_basic_simd(double, 8);

	#undef VECTORCLASS_basic_simd

	/*
	template<class T, simd-size-type N = basic_simd<T>::size()>
	using simd = basic_simd<T, deduce-t<T, N>>;
	*/
	template<typename T, details::size_type N = basic_simd<T>::size()>
	using simd = basic_simd<T, details::simd_abi::deduce_t<T, N>>;
}

#ifdef VCL_NAMESPACE
}
#endif