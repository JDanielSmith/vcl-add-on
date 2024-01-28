#pragma once

#include <memory>

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
    namespace details
    {
        // Table 2.3 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
        template <size_t elements_per_vector, typename For_use_with> struct Vec_N_b;
        template<> struct Vec_N_b<16, int8_t> final { using type = Vec16cb; };
        template<> struct Vec_N_b<16, uint8_t> final { using type = Vec16cb; };
        template<> struct Vec_N_b<8, int16_t> final { using type = Vec8sb; };
        template<> struct Vec_N_b<8, uint16_t> final { using type = Vec8sb; };
        template<> struct Vec_N_b<4, int32_t> final { using type = Vec4ib; };
        template<> struct Vec_N_b<4, uint32_t> final { using type = Vec4ib; };
        template<> struct Vec_N_b<2, int64_t> final { using type = Vec2qb; };
        template<> struct Vec_N_b<2, uint64_t> final { using type = Vec2qb; };
        template<> struct Vec_N_b<32, int8_t> final { using type = Vec32cb; };
        template<> struct Vec_N_b<32, uint8_t> final { using type = Vec32cb; };
        template<> struct Vec_N_b<16, int16_t> final { using type = Vec16sb; };
        template<> struct Vec_N_b<16, uint16_t> final { using type = Vec16sb; };
        template<> struct Vec_N_b<8, int32_t> final { using type = Vec8ib; };
        template<> struct Vec_N_b<8, uint32_t> final { using type = Vec8ib; };
        template<> struct Vec_N_b<4, int64_t> final { using type = Vec4qb; };
        template<> struct Vec_N_b<4, uint64_t> final { using type = Vec4qb; };
        template<> struct Vec_N_b<64, int8_t> final { using type = Vec64cb; };
        template<> struct Vec_N_b<64, uint8_t> final { using type = Vec64cb; };
        template<> struct Vec_N_b<32, int16_t> final { using type = Vec32sb; };
        template<> struct Vec_N_b<32, uint16_t> final { using type = Vec32sb; };
        template<> struct Vec_N_b<16, int32_t> final { using type = Vec16ib; };
        template<> struct Vec_N_b<16, uint32_t> final { using type = Vec16ib; };
        template<> struct Vec_N_b<8, int64_t> final { using type = Vec8qb; };
        template<> struct Vec_N_b<8, uint64_t> final { using type = Vec8qb; };
        template<> struct Vec_N_b<4, float> final { using type = Vec4fb; };
        template<> struct Vec_N_b<2, double> final { using type = Vec2db; };
        template<> struct Vec_N_b<8, float> final { using type = Vec8fb; };
        template<> struct Vec_N_b<4, double> final { using type = Vec4db; };
        template<> struct Vec_N_b<16, float> final { using type = Vec16fb; };
        template<> struct Vec_N_b<8, double> final { using type = Vec8db; };
    }

    /*
    template<size_t Bytes, class Abi = native-abi<T>> class basic_simd_mask;
    */
    // TODO: template<size_t Bytes, typename Abi = details::simd_abi::native_abi<T>> class basic_simd_mask { ???
	template<typename T, typename Abi = details::simd_abi::native_abi<T>> class basic_simd_mask {
	public:
		using value_type = bool;
		//using reference = see below;
		using abi_type = Abi;

        static constexpr auto size = basic_simd<details::integer_from<sizeof(T)>, Abi>::size;

		constexpr basic_simd_mask() noexcept = default;

        // [simd.mask.ctor]
        constexpr explicit basic_simd_mask(value_type v) noexcept;
        template<typename U, class UAbi>// TODO: template<size_t UBytes, class UAbi>
        constexpr explicit basic_simd_mask(const basic_simd_mask<U, UAbi>& other) noexcept;
        template<typename G> constexpr explicit basic_simd_mask(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;
	};

    namespace details
    {
        template<typename T, typename Abi>
        class Vec_basic_simd_mask {
        public:
            using value_type = bool;
            //using reference = see below;
            using abi_type = Abi;

            static constexpr auto size = basic_simd<details::integer_from<sizeof(T)>, Abi>::size; // TODO: basic_simd<details::integer_from<Bytes>, Abi>::size;

            constexpr Vec_basic_simd_mask() noexcept = default;

            // [simd.ctor]
            template<typename U> constexpr Vec_basic_simd_mask(U&& value) noexcept {}
            template<typename U, typename UAbi>
            constexpr explicit Vec_basic_simd_mask(const basic_simd<U, UAbi>& other) noexcept;
            template<typename G> constexpr explicit Vec_basic_simd_mask(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;
        };
    }

    // "... The specialization basic_simd_mask<T, Abi> is supported if ... Abi is simd_abi::fixed_size<N>, ..."
    template<> class basic_simd_mask<float, details::simd_abi::fixed_size<16>> 
    : public details::Vec_basic_simd_mask<float, details::simd_abi::fixed_size<16>> {
    public:
    };

    /*
    template<class T, simd-size-type N = basic_simd_mask<sizeof(T)>::size()>
    using simd_mask = basic_simd_mask<sizeof(T), deduce-t<T, N>>;
    */
	template<typename T, details::size_type N = basic_simd_mask<T>::size()>
	using simd_mask = basic_simd_mask<T, details::simd_abi::deduce_t<T, N>>; // TODO: sizeof(T)
}

#ifdef VCL_NAMESPACE
}
#endif