/***************************  simdvec.h   *********************************
* Author:        Agner Fog
* Date created:  2024-02-02
* Last modified: 2024-02-02
* Version:       2.02.00
* Project:       Extension to vector class library
* Description:
* Allow client code using the vector class library to look more like it was using `std::simd::simd`.
* https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p1928r8.pdf
*
* (c) Copyright 2012-2022. Apache License version 2.0 or later
******************************************************************************/

#pragma once
#include "vectorclass.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

//
// These templates "grab" too much, but it's easier than a bunch of overloads.
//

template<typename VecF>
inline auto lround(VecF const a)
{
    return roundi(a); // TODO: `long`, not `int`
}

template<typename VecB, typename VecT>
inline VecT simd_select(VecB const s, VecT const a, VecT const b) {
    return select(s, a, b);
}

template<typename VecB>
inline bool any_of(VecB const m)
{
    return horizontal_or(m);
}

template<typename VecB>
inline bool all_of(VecB const m)
{
    return horizontal_and(m);
}

#ifdef VCL_NAMESPACE
}
#endif
