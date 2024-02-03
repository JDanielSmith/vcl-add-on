#pragma once

#include "simd.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	template<typename T, int N>
	constexpr basic_simd<T, N>& basic_simd<T, N>::operator++() noexcept
	{
		++(this->v_);
		return *this;
	}
	template<typename T, int N>
	constexpr basic_simd<T, N> basic_simd<T, N>::operator++(int) noexcept
	{
		auto old = *this; // copy old value
		operator++();  // prefix increment
		return old;    // return old value
	}
	template<typename T, int N>
	constexpr basic_simd<T, N>& basic_simd<T, N>::operator--() noexcept
	{
		--(this->v_);
		return *this;
	}
	template<typename T, int N>
	constexpr basic_simd<T, N> basic_simd<T, N>::operator--(int) noexcept
	{
		auto old = *this; // copy old value
		operator--();  // prefix decrement
		return old;    // return old value
	}
	template<typename T, int N>
	constexpr basic_simd<T, N>::mask_type basic_simd<T, N>::operator!() const noexcept
	{
		return !(this->v_);
	}
	template<typename T, int N>
	constexpr basic_simd<T, N> basic_simd<T, N>::operator~() const noexcept
	{
		return ~(this->v_);
	}
	template<typename T, int N>
	constexpr basic_simd<T, N> basic_simd<T, N>::operator+() const noexcept
	{
		return +(this->v_);
	}
	template<typename T, int N>
	constexpr basic_simd<T, N> basic_simd<T, N>::operator-() const noexcept
	{
		return -(this->v_);
	}

	#define VECTORCLASS_basic_simd_binary(OPERATOR_) \
		template<typename T, int N> constexpr auto operator OPERATOR_(const basic_simd<T, N>& lhs, const basic_simd<T, N>& rhs) noexcept { \
			using Vec = basic_simd<T, N>::Vec; auto result = static_cast<Vec>(lhs) OPERATOR_ static_cast<Vec>(rhs); \
			return basic_simd<T, N>(result); } \
		template<typename T, int N, typename U> constexpr auto operator OPERATOR_(const basic_simd<T, N>& lhs, const U& rhs) noexcept { \
			using Vec = basic_simd<T, N>::Vec; auto result = static_cast<Vec>(lhs) OPERATOR_ rhs; \
			return basic_simd<T, N>(result); }
	VECTORCLASS_basic_simd_binary(+);
	VECTORCLASS_basic_simd_binary(-);
	VECTORCLASS_basic_simd_binary(*);
	VECTORCLASS_basic_simd_binary(/);
	VECTORCLASS_basic_simd_binary(%);
	VECTORCLASS_basic_simd_binary(&);
	VECTORCLASS_basic_simd_binary(|);
	VECTORCLASS_basic_simd_binary(^);
	VECTORCLASS_basic_simd_binary(<<);
	VECTORCLASS_basic_simd_binary(>>);
	template<typename T, int N>
	constexpr auto operator<<(const basic_simd<T, N>& lhs, details::size_type rhs) noexcept
	{
		using Vec = basic_simd<T, N>::Vec;
		auto result = static_cast<Vec>(lhs) << rhs;
		return basic_simd<T, N>(result);
	}
	template<typename T, int N>
	constexpr auto operator>>(const basic_simd<T, N>& lhs, details::size_type rhs) noexcept
	{
		using Vec = basic_simd<T, N>::Vec;
		auto result = static_cast<Vec>(lhs) >> rhs;
		return basic_simd<T, N>(result);
	}
	#undef VECTORCLASS_basic_simd_binary

	#define VECTORCLASS_basic_simd_cassign(OPERATOR_) \
		template<typename T, int N> constexpr auto operator OPERATOR_(basic_simd<T, N>& lhs, const basic_simd<T, N>& rhs) noexcept { \
			lhs.v_ OPERATOR_ rhs.v_; return lhs; } \
		template<typename T, int N, typename U> constexpr auto operator OPERATOR_(basic_simd<T, N>& lhs, const U& rhs) noexcept { \
			lhs.v_ OPERATOR_ rhs; return lhs; }
	VECTORCLASS_basic_simd_cassign(+=);
	VECTORCLASS_basic_simd_cassign(-=);
	VECTORCLASS_basic_simd_cassign(*=);
	VECTORCLASS_basic_simd_cassign(/=);
	VECTORCLASS_basic_simd_cassign(%=);
	VECTORCLASS_basic_simd_cassign(&= );
	VECTORCLASS_basic_simd_cassign(|=);
	VECTORCLASS_basic_simd_cassign(^= );
	VECTORCLASS_basic_simd_cassign(<<= );
	VECTORCLASS_basic_simd_cassign(>>= );
	#undef VECTORCLASS_basic_simd_cassign
	template<typename T, int N, typename U>
	constexpr auto operator<<=(basic_simd<T, N>& lhs, details::size_type rhs) noexcept {
			lhs.v_ <<= rhs;
			return lhs;
	}
	template<typename T, int N, typename U>
	constexpr auto operator>>=(basic_simd<T, N>& lhs, details::size_type rhs) noexcept {
		lhs.v_ >>= rhs;
		return lhs;
	}

	#define VECTORCLASS_basic_simd_comparison(OPERATOR_) \
		template<typename T, int N> constexpr auto operator OPERATOR_(const basic_simd<T, N>& lhs, const basic_simd<T, N>& rhs) noexcept { \
			using Vec = basic_simd<T, N>::Vec; \
			auto result = static_cast<Vec>(lhs) OPERATOR_ static_cast<Vec>(rhs); \
			return basic_simd<T, N>::mask_type(result); } \
		template<typename T, int N, typename U> constexpr auto operator OPERATOR_(const basic_simd<T, N>& lhs, const U& rhs) noexcept { \
			using Vec = basic_simd<T, N>::Vec; \
			auto result = static_cast<Vec>(lhs) OPERATOR_ rhs; \
			return basic_simd<T, N>::mask_type(result); }
	VECTORCLASS_basic_simd_comparison(==);
	VECTORCLASS_basic_simd_comparison(!=);
	VECTORCLASS_basic_simd_comparison(>=);
	VECTORCLASS_basic_simd_comparison(<=);
	VECTORCLASS_basic_simd_comparison(>);
	VECTORCLASS_basic_simd_comparison(<);
	#undef VECTORCLASS_basic_simd_comparison

	template<typename TMask, int N, typename T, typename U>
	constexpr auto simd_select(const basic_simd_mask<TMask, N>& c, const T& a, const U& b)
	{
		using Vec_b = basic_simd_mask<TMask, N>::Vec;
		using Vec_t = T::Vec;
		using Vec_u = U::Vec;
		auto result = select(static_cast<Vec_b>(c), static_cast<Vec_t>(a), static_cast<Vec_u>(b));
		return T(result);
	}

	template<typename TMask, int N>
	constexpr bool any_of(const basic_simd_mask<TMask, N>& m)
	{
		using Vec_b = basic_simd_mask<TMask, N>::Vec;
		return horizontal_or(static_cast<Vec_b>(m));
	}
}

#ifdef VCL_NAMESPACE
}
#endif