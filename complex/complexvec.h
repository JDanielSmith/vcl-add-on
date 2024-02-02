/***************************  complexvec.h   *********************************
* Author:        Agner Fog
* Date created:  2024-02-02
* Last modified: 2024-02-02
* Version:       2.02.00
* Project:       Extension to vector class library
* Description:
* Generic (template) wrappers around Complex classes.
*
* This file defines operators and functions for these classes
* See complexvec_manual.pdf for detailed instructions.
*
* (c) Copyright 2012-2022. Apache License version 2.0 or later
******************************************************************************/

#pragma once

#include "complexvec1.h"

#ifdef VCL_NAMESPACE
namespace VCL_NAMESPACE {
#endif

// Table 1.1 of https://github.com/vectorclass/add-on/blob/master/complex/complexvec_manual.pdf
template<int Complex_elements_per_vector, typename T> struct ComplexNt;
template<> struct ComplexNt<1, float> { using Complex_vector_class = Complex1f; };
template<> struct ComplexNt<2, float> { using Complex_vector_class = Complex2f; };
template<> struct ComplexNt<4, float> { using Complex_vector_class = Complex4f; };
template<> struct ComplexNt<8, float> { using Complex_vector_class = Complex8f; };
template<> struct ComplexNt<1, double> { using Complex_vector_class = Complex1d; };
template<> struct ComplexNt<2, double> { using Complex_vector_class = Complex2d; };
template<> struct ComplexNt<4, double> { using Complex_vector_class = Complex4d; };

// Complex<4, float> = Complex4f
template<int Complex_elements_per_vector, typename T> struct Complex
	: public ComplexNt< Complex_elements_per_vector, T>::Complex_vector_class
{
	//using Complex_vector_class = ComplexNt<Complex_elements_per_vector, T>::Complex_vector_class; // e.g., Complex4f
	//explicit operator Complex_vector_class() const { return *this; }
	//explicit Complex(const Complex_vector_class& init) { *this = init; }
};

// Complexf<4> = Complex4f
template<int Complex_elements_per_vector>
using Complexf = Complex<Complex_elements_per_vector, float>;
template<int Complex_elements_per_vector>
using Complexd = Complex<Complex_elements_per_vector, double>;

// Complex4<float> = Complex4f
template<typename T>
using Complex1 = Complex<1, T>;
template<typename T>
using Complex2 = Complex<2, T>;
template<typename T>
using Complex4 = Complex<4, T>;
template<typename T>
using Complex8 = Complex<8, T>;

/*****************************************************************************
*
*          Functions for ComplexNt
*
*****************************************************************************/

// https://en.cppreference.com/w/cpp/numeric/complex/arg
template<int Complex_elements_per_vector, typename T>
inline auto arg(const Complex<Complex_elements_per_vector, T>& z)
{
	// > `std::atan2(std::imag(z), std::real(z))`
	return atan2(z.imag(), z.real()); // arg()
}

// free functions to aid in generic programming
template<int Complex_elements_per_vector, typename T>
static inline auto real(const Complex<Complex_elements_per_vector, T>& z)
{
	return z.real();
}
template<int Complex_elements_per_vector, typename T>
static inline auto imag(const Complex<Complex_elements_per_vector, T>& z)
{
	return z.imag();
}

template<int Complex_elements_per_vector, typename T>
static inline constexpr size_t size(const Complex<Complex_elements_per_vector, T>& z)
{
	return z.size();
}
template<int Complex_elements_per_vector, typename T>
static inline constexpr ptrdiff_t ssize(const Complex<Complex_elements_per_vector, T>& z)
{
	return z.size();
}

#ifdef VCL_NAMESPACE
}
#endif

