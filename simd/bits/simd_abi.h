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