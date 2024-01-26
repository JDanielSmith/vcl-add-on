#pragma once

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	namespace details
	{
		using size_type = int;  // "simd-size-type is an exposition-only alias for a signed integer type"

		// "a signed integer type T so that sizeof(T) == Bytes."
		template <size_t Bytes> struct integer_from_;
		template<> struct integer_from_<8> { static constexpr size_type size = 1; };
		template<> struct integer_from_<16> { static constexpr size_type size = 2; };
		template<> struct integer_from_<32> { static constexpr size_type size = 4; };
		template<> struct integer_from_<64> { static constexpr size_type size = 8; };
		template <size_t Bytes>
		using integer_from = integer_from_<Bytes>::size;
	}

	// [simd.traits]
	template<typename T, typename U = typename T::value_type> struct simd_alignment;
	template<typename T, typename U = typename T::value_type>
		inline constexpr size_t simd_alignment_v = simd_alignment<T, U>::value;

	// [simd.flags]
	template <typename... Flags> struct simd_flags;
	//inline constexpr simd_flags<> simd_flag_default{};
	//inline constexpr simd_flags<see below> simd_flag_convert{};
	//inline constexpr simd_flags<see below> simd_flag_aligned{};

	// [simd.class]
	template<typename T, typename Abi> class basic_simd;

	// [simd.mask]
	template<size_t Bytes, typename Abi> class basic_simd_mask;
	//template<class T, simd - size - type N = basic_simd_mask<sizeof(T)>::size()>
	//using simd_mask = basic_simd_mask<sizeof(T), deduce - t<T, N>>;

	// [simd.creation]
	// [simd.mask.reductions]
	// [simd.reductions]
	// [simd.alg]
}

#ifdef VCL_NAMESPACE
}
#endif