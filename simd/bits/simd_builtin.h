#pragma once

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100) // '...': unreferenced formal parameter
#pragma warning(disable: 4127) // conditional expression is constant
#pragma warning(disable: 4244) // '...': conversion from '...' to '...', possible loss of data
#pragma warning(disable: 4723) // potential divide by 0
#endif
#include "vectorclass.h"
#include "vectormath_trig.h"
#if _MSC_VER
#pragma warning(pop)
#endif

#include "simd_basic.h"
#include "simd_basic_mask.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	template<typename T, typename Abi>
	constexpr basic_simd<T, Abi>& basic_simd<T, Abi>::operator++() noexcept
	{
		++(this->v_);
		return *this;
	}
	template<typename T, typename Abi>
	constexpr basic_simd<T, Abi> basic_simd<T, Abi>::operator++(int) noexcept
	{
		auto old = *this; // copy old value
		operator++();  // prefix increment
		return old;    // return old value
	}
	template<typename T, typename Abi>
	constexpr basic_simd<T, Abi>& basic_simd<T, Abi>::operator--() noexcept
	{
		--(this->v_);
		return *this;
	}
	template<typename T, typename Abi>
	constexpr basic_simd<T, Abi> basic_simd<T, Abi>::operator--(int) noexcept
	{
		auto old = *this; // copy old value
		operator--();  // prefix decrement
		return old;    // return old value
	}
	template<typename T, typename Abi>
	constexpr basic_simd<T, Abi>::mask_type basic_simd<T, Abi>::operator!() const noexcept
	{
		return !(this->v_);
	}
	template<typename T, typename Abi>
	constexpr basic_simd<T, Abi> basic_simd<T, Abi>::operator~() const noexcept
	{
		return ~(this->v_);
	}
	template<typename T, typename Abi>
	constexpr basic_simd<T, Abi> basic_simd<T, Abi>::operator+() const noexcept
	{
		return +(this->v_);
	}
	template<typename T, typename Abi>
	constexpr basic_simd<T, Abi> basic_simd<T, Abi>::operator-() const noexcept
	{
		return -(this->v_);
	}

	#define VECTORCLASS_basic_simd_binary(OPERATOR_) \
		template<typename T, typename Abi> constexpr auto operator OPERATOR_(const basic_simd<T, Abi>& lhs, const basic_simd<T, Abi>& rhs) noexcept { \
			using Vec_type = basic_simd<T, Abi>::Vec_type; \
			auto result = static_cast<Vec_type>(lhs) OPERATOR_ static_cast<Vec_type>(rhs); \
			return basic_simd<T, Abi>(result); } \
		template<typename T, typename Abi, typename U> constexpr auto operator OPERATOR_(const basic_simd<T, Abi>& lhs, const U& rhs) noexcept { \
			using Vec_type = basic_simd<T, Abi>::Vec_type; \
			auto result = static_cast<Vec_type>(lhs) OPERATOR_ rhs; \
			return basic_simd<T, Abi>(result); }
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
	template<typename T, typename Abi>
	constexpr auto operator<<(const basic_simd<T, Abi>& lhs, details::size_type rhs) noexcept
	{
		using Vec_type = basic_simd<T, Abi>::Vec_type;
		auto result = static_cast<Vec_type>(lhs) << rhs;
		return basic_simd<T, Abi>(result);
	}
	template<typename T, typename Abi>
	constexpr auto operator>>(const basic_simd<T, Abi>& lhs, details::size_type rhs) noexcept
	{
		using Vec_type = basic_simd<T, Abi>::Vec_type;
		auto result = static_cast<Vec_type>(lhs) >> rhs;
		return basic_simd<T, Abi>(result);
	}
	#undef VECTORCLASS_basic_simd_binary

	#define VECTORCLASS_basic_simd_comparison(OPERATOR_) \
		template<typename T, typename Abi> constexpr auto operator OPERATOR_(const basic_simd<T, Abi>& lhs, const basic_simd<T, Abi>& rhs) noexcept { \
			using Vec_type = basic_simd<T, Abi>::Vec_type; \
			auto result = static_cast<Vec_type>(lhs) OPERATOR_ static_cast<Vec_type>(rhs); \
			return basic_simd<T, Abi>::mask_type(result); } \
		template<typename T, typename Abi, typename U> constexpr auto operator OPERATOR_(const basic_simd<T, Abi>& lhs, const U& rhs) noexcept { \
			using Vec_type = basic_simd<T, Abi>::Vec_type; \
			auto result = static_cast<Vec_type>(lhs) OPERATOR_ rhs; \
			return basic_simd<T, Abi>::mask_type(result); }
	VECTORCLASS_basic_simd_comparison(==);
	VECTORCLASS_basic_simd_comparison(!=);
	VECTORCLASS_basic_simd_comparison(>=);
	VECTORCLASS_basic_simd_comparison(<=);
	VECTORCLASS_basic_simd_comparison(>);
	VECTORCLASS_basic_simd_comparison(<);
	#undef VECTORCLASS_basic_simd_comparison

	template<typename TMask, typename Abi, typename T, typename U>
	constexpr auto simd_select(const basic_simd_mask<TMask, Abi>& c, const T& a, const U& b)
	{
		using Vec_t_b = basic_simd_mask<TMask, Abi>::Vec_type;
		using Vec_type = T::Vec_type;
		using Vec_u = U::Vec_type;
		auto result = select(static_cast<Vec_t_b>(c), static_cast<Vec_type>(a), static_cast<Vec_u>(b));
		return T(result);
	}
}

#ifdef VCL_NAMESPACE
}
#endif