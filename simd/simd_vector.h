/***************************  simd_vector.h   *********************************
* Author:        Agner Fog
* Date created:  2024-02-02
* Last modified: 2024-02-02
* Version:       2.02.00
* Project:       Extension to vector class library
* Description:
* Templates around vector classes.
*
* (c) Copyright 2012-2022. Apache License version 2.0 or later
******************************************************************************/

#pragma once

#include "vectorclass.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

#ifndef VECTORCLASS_NAMESPACE_details
    #ifdef VCL_NAMESPACE
    #define VECTORCLASS_NAMESPACE_details details // e.g., vcl::details
    #else
    #define VECTORCLASS_NAMESPACE_details vcl_details // ::vcl_details
    #endif
#endif // VCL_NAMESPACE_details

namespace VECTORCLASS_NAMESPACE_details
{
    // VecNt<8, int32_t> == Vec8i
    // https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
    template <int Elements_per_vector, typename T> struct VecNt;

    // Table 2.1 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
    // 128 Total bits
    template<> struct VecNt<16, int8_t> { using Vector_class = Vec16c; };
    template<> struct VecNt<16, uint8_t> { using Vector_class = Vec16uc; };
    template<> struct VecNt<8, int16_t> { using Vector_class = Vec8s; };
    template<> struct VecNt<8, uint16_t> { using Vector_class = Vec8us; };
    template<> struct VecNt<4, int32_t> { using Vector_class = Vec4i; };
    template<> struct VecNt<4, uint32_t> { using Vector_class = Vec4ui; };
    template<> struct VecNt<2, int64_t> { using Vector_class = Vec2q; };
    template<> struct VecNt<2, uint64_t> { using Vector_class = Vec2uq; };
    // 256 Total bits
    template<> struct VecNt<32, int8_t> { using Vector_class = Vec32c; };
    template<> struct VecNt<32, uint8_t> { using Vector_class = Vec32uc; };
    template<> struct VecNt<16, int16_t> { using Vector_class = Vec16s; };
    template<> struct VecNt<16, uint16_t> { using Vector_class = Vec16us; };
    template<> struct VecNt<8, int32_t> { using Vector_class = Vec8i; };
    template<> struct VecNt<8, uint32_t> { using Vector_class = Vec8ui; };
    template<> struct VecNt<4, int64_t> { using Vector_class = Vec4q; };
    template<> struct VecNt<4, uint64_t> { using Vector_class = Vec4uq; };
    // 512 Total bits
    template<> struct VecNt<64, int8_t> { using Vector_class = Vec64c; };
    template<> struct VecNt<64, uint8_t> { using Vector_class = Vec64uc; };
    template<> struct VecNt<32, int16_t> { using Vector_class = Vec32s; };
    template<> struct VecNt<32, uint16_t> { using Vector_class = Vec32us; };
    template<> struct VecNt<16, int32_t> { using Vector_class = Vec16i; };
    template<> struct VecNt<16, uint32_t> { using Vector_class = Vec16ui; };
    template<> struct VecNt<8, int64_t> { using Vector_class = Vec8q; };
    template<> struct VecNt<8, uint64_t> { using Vector_class = Vec8uq; };

    // Table 2.2 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
    // 128 Total bits
    template<> struct VecNt<4, float> { using Vector_class = Vec4f; };
    template<> struct VecNt<2, double> { using Vector_class = Vec2d; };
    // 256 Total bits
    template<> struct VecNt<8, float> { using Vector_class = Vec8f; };
    template<> struct VecNt<4, double> { using Vector_class = Vec4d; };
    // 512 Total bits
    template<> struct VecNt<16, float> { using Vector_class = Vec16f; };
    template<> struct VecNt<8, double> { using Vector_class = Vec8d; };

    // Table 2.3 from https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
    template <int Elements_per_vector, typename For_use_with> struct VecNb;
    template<> struct VecNb<16, int8_t> { using Boolean_vector_class = Vec16cb; };
    template<> struct VecNb<16, uint8_t> { using Boolean_vector_class = Vec16cb; };
    template<> struct VecNb<8, int16_t> { using Boolean_vector_class = Vec8sb; };
    template<> struct VecNb<8, uint16_t> { using Boolean_vector_class = Vec8sb; };
    template<> struct VecNb<4, int32_t> { using Boolean_vector_class = Vec4ib; };
    template<> struct VecNb<4, uint32_t> { using Boolean_vector_class = Vec4ib; };
    template<> struct VecNb<2, int64_t> { using Boolean_vector_class = Vec2qb; };
    template<> struct VecNb<2, uint64_t> { using Boolean_vector_class = Vec2qb; };
    template<> struct VecNb<32, int8_t> { using Boolean_vector_class = Vec32cb; };
    template<> struct VecNb<32, uint8_t> { using Boolean_vector_class = Vec32cb; };
    template<> struct VecNb<16, int16_t> { using Boolean_vector_class = Vec16sb; };
    template<> struct VecNb<16, uint16_t> { using Boolean_vector_class = Vec16sb; };
    template<> struct VecNb<8, int32_t> { using Boolean_vector_class = Vec8ib; };
    template<> struct VecNb<8, uint32_t> { using Boolean_vector_class = Vec8ib; };
    template<> struct VecNb<4, int64_t> { using Boolean_vector_class = Vec4qb; };
    template<> struct VecNb<4, uint64_t> { using Boolean_vector_class = Vec4qb; };
    template<> struct VecNb<64, int8_t> { using Boolean_vector_class = Vec64cb; };
    template<> struct VecNb<64, uint8_t> { using Boolean_vector_class = Vec64cb; };
    template<> struct VecNb<32, int16_t> { using Boolean_vector_class = Vec32sb; };
    template<> struct VecNb<32, uint16_t> { using Boolean_vector_class = Vec32sb; };
    template<> struct VecNb<16, int32_t> { using Boolean_vector_class = Vec16ib; };
    template<> struct VecNb<16, uint32_t> { using Boolean_vector_class = Vec16ib; };
    template<> struct VecNb<8, int64_t> { using Boolean_vector_class = Vec8qb; };
    template<> struct VecNb<8, uint64_t> { using Boolean_vector_class = Vec8qb; };
    template<> struct VecNb<4, float> { using Boolean_vector_class = Vec4fb; };
    template<> struct VecNb<2, double> { using Boolean_vector_class = Vec2db; };
    template<> struct VecNb<8, float> { using Boolean_vector_class = Vec8fb; };
    template<> struct VecNb<4, double> { using Boolean_vector_class = Vec4db; };
    template<> struct VecNb<16, float> { using Boolean_vector_class = Vec16fb; };
    template<> struct VecNb<8, double> { using Boolean_vector_class = Vec8db; };
} // namespace VECTORCLASS_NAMESPACE_details

// Vec<8, int32_t> == Vec8i
template<int Elements_per_vector, typename T> struct Vec
	: public VECTORCLASS_NAMESPACE_details ::VecNt<Elements_per_vector, T>::Vector_class
{
	using Vector_class = VECTORCLASS_NAMESPACE_details ::VecNt<Elements_per_vector, T>::Vector_class; // e.g., Vec8i
	operator Vector_class() const { return *this; }
	Vec(const Vector_class& init) { *this = init; }
};

// Template wrapper, specify size for a fixed type; e.g., Vec_i<8> == Vec8i; not for `bool`.
template<size_t Elements_per_vector> using Vec_c = Vec<Elements_per_vector, int8_t>;
template<size_t Elements_per_vector> using Vec_uc = Vec<Elements_per_vector, uint8_t>;
template<size_t Elements_per_vector> using Vec_s = Vec<Elements_per_vector, int16_t>;
template<size_t Elements_per_vector> using Vec_us = Vec<Elements_per_vector, uint16_t>;
template<size_t Elements_per_vector> using Vec_i = Vec<Elements_per_vector, int32_t>;
template<size_t Elements_per_vector> using Vec_ui = Vec<Elements_per_vector, uint32_t>;
template<size_t Elements_per_vector> using Vec_q = Vec<Elements_per_vector, int64_t>;
template<size_t Elements_per_vector> using Vec_uq = Vec<Elements_per_vector, uint64_t>;
template<size_t Elements_per_vector> using Vec_f = Vec<Elements_per_vector, float>;
template<size_t Elements_per_vector> using Vec_d = Vec<Elements_per_vector, double>;
//template<size_t Elements_per_vector> using Vec_b = VecNb<Elements_per_vector, bool>;

// Template wrapper, specify type for a fixed size; e.g., Vec8<int32_t> == Vec8i; not for `bool`.
template <typename T> using Vec64 = Vec<64, T>;
template <typename T> using Vec32 = Vec<32, T>;
template <typename T> using Vec16 = Vec<16, T>;
template <typename T> using Vec8 = Vec<8, T>;
template <typename T> using Vec4 = Vec<4, T>;
template <typename T> using Vec2 = Vec<2, T>;

#ifdef VCL_NAMESPACE
}
#endif
