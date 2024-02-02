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

// These are member-functions on `basic_simd` and `basic_simd_mask`.
template<typename It, typename VecT>
inline void copy_from(VecT& this_, It first)
{
    // TODO: look at simd_flags
    // However, §2.4 states "There is hardly any difference in efficiency
    // between `load` and `load_a` on newer microprocessors."

    // "`It` satisfies contiguous_iterator."
    const auto mem = &(*first);
    this_.load(mem);
}
template<typename Out, typename VecT>
constexpr void copy_to(const VecT& this_, Out first)
{
    // TODO: look at simd_flags
    // However, §2.5 states "There is hardly any difference in efficiency
    // between `store` and `store_a` on newer microprocessors."

    // "`It` satisfies contiguous_iterator."
    auto mem = &(*first);
    this_.store(mem);
}

#ifdef VCL_NAMESPACE
}
#endif
