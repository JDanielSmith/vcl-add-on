#pragma once

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

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

namespace simd
{
	namespace details
	{
        #if MAX_VECTOR_SIZE >= 512
        constexpr size_type max_vector_size = 512;
        #elif MAX_VECTOR_SIZE >= 256
        constexpr size_type max_vector_size = 256;
        #else
        constexpr size_type max_vector_size = 128;
        #endif

        template<size_type N, typename T> struct Vec_N_T;
        template<> struct Vec_N_T<16, int32_t> { using type = Vec16i; };
        template<> struct Vec_N_T<16, float> { using type = Vec16f; };
        template<size_type N, typename T>
        using Vec = Vec_N_T<N, T>::type;

        template<size_type N, typename T> struct Vec_N_b;
        template<> struct Vec_N_b<16, int32_t> { using type = Vec16ib; };
        template<> struct Vec_N_b<16, float> { using type = Vec16fb; };
        template<size_type N, typename T>
        using VecNb = Vec_N_b<N, T>::type;

        template<typename T> struct Vec_type_;
        template<> struct Vec_type_<Vec16i> { using type = int32_t; };
        template<> struct Vec_type_<Vec16f> { using type = float; };
        template<> struct Vec_type_<Vec16ib> { using type = int32_t; };
        template<> struct Vec_type_<Vec16fb> { using type = float; };
        template<typename T>
        using Vec_type = Vec_type_<T>::type;

        namespace simd_abi
        {
            template<size_type width> struct fixed_size_;
            template<> struct fixed_size_<16> { };
            template<size_type N> using fixed_size = fixed_size_<N>;

            template<typename T> using native_abi = fixed_size<16>;

            // "The implementation-defined maximum for N is no smaller than 64."
            template<typename T, size_type N>
            using deduce_t = fixed_size<N>;
        }
	}
}

#ifdef VCL_NAMESPACE
}
#endif