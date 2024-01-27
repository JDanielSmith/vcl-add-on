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
        // Vec_N_T<8, int32_t> == Vec8i
        // https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
        template <size_t elements_per_vector, typename T> struct Vec_N_T;

        // Table 2.1 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
        // 128 Total bits
        template<> struct Vec_N_T<16, int8_t> final { using type = Vec16c; };
        template<> struct Vec_N_T<16, uint8_t> final { using type = Vec16uc; };
        template<> struct Vec_N_T<8, int16_t> final { using type = Vec8s; };
        template<> struct Vec_N_T<8, uint16_t> final { using type = Vec8us; };
        template<> struct Vec_N_T<4, int32_t> final { using type = Vec4i; };
        template<> struct Vec_N_T<4, uint32_t> final { using type = Vec4ui; };
        template<> struct Vec_N_T<2, int64_t> final { using type = Vec2q; };
        template<> struct Vec_N_T<2, uint64_t> final { using type = Vec2uq; };
        // 256 Total bits
        template<> struct Vec_N_T<32, int8_t> final { using type = Vec32c; };
        template<> struct Vec_N_T<32, uint8_t> final { using type = Vec32uc; };
        template<> struct Vec_N_T<16, int16_t> final { using type = Vec16s; };
        template<> struct Vec_N_T<16, uint16_t> final { using type = Vec16us; };
        template<> struct Vec_N_T<8, int32_t> final { using type = Vec8i; };
        template<> struct Vec_N_T<8, uint32_t> final { using type = Vec8ui; };
        template<> struct Vec_N_T<4, int64_t> final { using type = Vec4q; };
        template<> struct Vec_N_T<4, uint64_t> final { using type = Vec4uq; };
        // 512 Total bits
        template<> struct Vec_N_T<64, int8_t> final { using type = Vec64c; };
        template<> struct Vec_N_T<64, uint8_t> final { using type = Vec64uc; };
        template<> struct Vec_N_T<32, int16_t> final { using type = Vec32s; };
        template<> struct Vec_N_T<32, uint16_t> final { using type = Vec32us; };
        template<> struct Vec_N_T<16, int32_t> final { using type = Vec16i; };
        template<> struct Vec_N_T<16, uint32_t> final { using type = Vec16ui; };
        template<> struct Vec_N_T<8, int64_t> final { using type = Vec8q; };
        template<> struct Vec_N_T<8, uint64_t> final { using type = Vec8uq; };

        // Table 2.2 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
        // 128 Total bits
        template<> struct Vec_N_T<4, float> final { using type = Vec4f; };
        template<> struct Vec_N_T<2, double> final { using type = Vec2d; };
        // 256 Total bits
        template<> struct Vec_N_T<8, float> final { using type = Vec8f; };
        template<> struct Vec_N_T<4, double> final { using type = Vec4d; };
        // 512 Total bits
        template<> struct Vec_N_T<16, float> final { using type = Vec16f; };
        template<> struct Vec_N_T<8, double> final { using type = Vec8d; };
    }

	namespace details
	{
		namespace simd_abi
		{           
            template<typename T, size_type N> struct Vec_tag {};
            // See table 2.1 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
            // See table 2.2 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
            // 128 Total bits
            template<> struct Vec_tag<int8_t, 128> { static constexpr size_type size = 16; using type = Vec16c; };
            template<> struct Vec_tag<uint8_t, 128> { static constexpr size_type size = 16; using type = Vec16uc; };
            template<> struct Vec_tag<int16_t, 128> { static constexpr size_type size = 8; using type = Vec8s; };
            template<> struct Vec_tag<uint16_t, 128> { static constexpr size_type size = 8; using type = Vec8us; };
            template<> struct Vec_tag<int32_t, 128> { static constexpr size_type size = 4; using type = Vec4i; };
            template<> struct Vec_tag<uint32_t, 128> { static constexpr size_type size = 4; using type = Vec4ui; };
            template<> struct Vec_tag<int64_t, 128> { static constexpr size_type size = 2; using type = Vec2q; };
            template<> struct Vec_tag<uint64_t, 128> { static constexpr size_type size = 2; using type = Vec2uq; };
            template<> struct Vec_tag<float, 128> { static constexpr size_type size = 4; using type = Vec4f; };
            template<> struct Vec_tag<double, 128> { static constexpr size_type size = 2; using type = Vec2d; };
            // 256 Total bits
            template<> struct Vec_tag<int8_t, 256> { static constexpr size_type size = 32; using type = Vec32c; };
            template<> struct Vec_tag<uint8_t, 256> { static constexpr size_type size = 32; using type = Vec32uc; };
            template<> struct Vec_tag<int16_t, 256> { static constexpr size_type size = 16; using type = Vec16s; };
            template<> struct Vec_tag<uint16_t, 256> { static constexpr size_type size = 16; using type = Vec16us; };
            template<> struct Vec_tag<int32_t, 256> { static constexpr size_type size = 8; using type = Vec8i; };
            template<> struct Vec_tag<uint32_t, 256> { static constexpr size_type size = 8; using type = Vec8ui; };
            template<> struct Vec_tag<int64_t, 256> { static constexpr size_type size = 4; using type = Vec4q; };
            template<> struct Vec_tag<uint64_t, 256> { static constexpr size_type size = 4; using type = Vec4uq; };
            template<> struct Vec_tag<float, 256> { static constexpr size_type size = 8; using type = Vec8f; };
            template<> struct Vec_tag<double, 256> { static constexpr size_type size = 4; using type = Vec4d; };
            // 512 Total bits
            template<> struct Vec_tag<int8_t, 512> { static constexpr size_type size = 64; using type = Vec64c; };
            template<> struct Vec_tag<uint8_t, 512> { static constexpr size_type size = 64; using type = Vec64uc; };
            template<> struct Vec_tag<int16_t, 512> { static constexpr size_type size = 32; using type = Vec32s; };
            template<> struct Vec_tag<uint16_t, 512> { static constexpr size_type size = 32; using type = Vec32us; };
            template<> struct Vec_tag<int32_t, 512> { static constexpr size_type size = 16; using type = Vec16i; };
            template<> struct Vec_tag<uint32_t, 512> { static constexpr size_type size = 16; using type = Vec16ui; };
            template<> struct Vec_tag<int64_t, 512> { static constexpr size_type size = 8; using type = Vec8q; };
            template<> struct Vec_tag<uint64_t, 512> { static constexpr size_type size = 8; using type = Vec8uq; };
            template<> struct Vec_tag<float, 512> { static constexpr size_type size = 16; using type = Vec16f; };
            template<> struct Vec_tag<double, 512> { static constexpr size_type size = 8; using type = Vec8d; };

            template<typename T, size_type N> using deduce_t = Vec_tag<T, N>;

            #if MAX_VECTOR_SIZE >= 512
            constexpr size_type max_vector_size = 512;
            #elif MAX_VECTOR_SIZE >= 256
            constexpr size_type max_vector_size = 256;
            #else
            constexpr size_type max_vector_size = 128;
            #endif

            template<typename T>
            using native_abi = Vec_tag<T, max_vector_size>;

			template<size_type N> struct fixed_size
			{
				static constexpr size_type size = N;
			};
		} // simd_abi
	}
}

#ifdef VCL_NAMESPACE
}
#endif