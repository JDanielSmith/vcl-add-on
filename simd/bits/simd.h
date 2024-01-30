#pragma once

#include <cstdint>

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	namespace details
	{
		using size_type = int;  // "simd-size-type is an exposition-only alias for a signed integer type"

		//template <typename T> constexpr size_t mask_element_size;

		// "a signed integer type T so that sizeof(T) == Bytes."
		template <size_t Bytes> struct integer_from_;
		template<> struct integer_from_<1> { using type = std::int8_t; };
		template<> struct integer_from_<2> { using type = std::int16_t; };
		template<> struct integer_from_<4> { using type = std::int32_t; };
		template<> struct integer_from_<8> { using type = std::int64_t; };
		template <size_t Bytes>
		using integer_from = typename integer_from_<Bytes>::type;
	}

	// [simd.traits]
	template<typename T, typename U = typename T::value_type> struct simd_alignment;
	template<typename T, typename U = typename T::value_type>
		inline constexpr size_t simd_alignment_v = simd_alignment<T, U>::value;

	//template<typename T, typename V> struct rebind_simd;
	//template<typename T, typename V> using rebind_simd_t = typename rebind_simd<T, V>::type;
	//template<details::size_type N, typename V> struct resize_simd;
	//template<details::size_type N, typename V> using resize_simd_t = typename resize_simd<N, V>::type;

	// [simd.flags]
	template <typename... Flags> struct simd_flags;
	//inline constexpr simd_flags<> simd_flag_default{};
	//inline constexpr simd_flags<see below> simd_flag_convert{};
	//inline constexpr simd_flags<see below> simd_flag_aligned{};

	// [simd.class]
	/*
	template<class T, class Abi = native-abi<T>> class basic_simd;
	*/
	template<typename T, typename Abi> class basic_simd;

	// [simd.mask]
	/*
	template<size_t Bytes, class Abi = native-abi<T>> class basic_simd_mask;
	*/
	//TODO: template<size_t Bytes, typename Abi> class basic_simd_mask; ???
	template<typename T, typename Abi> class basic_simd_mask;

	// [simd.creation]
	// [simd.mask.reductions]
	// [simd.reductions]
	// [simd.alg]
	template<typename TMask, typename Abi, typename T, typename U>
	constexpr auto simd_select(const basic_simd_mask<TMask, Abi>& c, const T& a, const U& b)
		noexcept -> decltype(simd_select_impl(c, a, b));
}

#ifdef VCL_NAMESPACE
}
#endif