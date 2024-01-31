#pragma once

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100) // '...': unreferenced formal parameter
#pragma warning(disable: 4127) // conditional expression is constant
#pragma warning(disable: 4244) // '...': conversion from '...' to '...', possible loss of data
#pragma warning(disable: 4723) // potential divide by 0
#endif
#include "vectorclass.h"
#include "instrset.h"
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
		// See section 9.9 of https://github.com/vectorclass/manual/raw/master/vcl_manual.pdf
		enum class instrset
		{
			X386 = 0,
			SSE = 1,
			SSE2 = 2,
			SSE3 = 3,
			SSSE3 = 4, // Supplementary SSE3
			SSE4_1 = 5, // SSE4.1
			SSE4_2 = 6,
			AVX = 7,
			AVX2 = 8,
			AVX512F = 9,
			AVX512VL = 10, AVX512BW = 10, AVX512DQ = 10,

			// From **instrset.h**: "In the future, INSTRSET = 11 may include AVX512VBMI and AVX512VBMI2 ..."
			// AVX512VBMI = 11, AVX512VBMI2 = 11,
		};
		static constexpr auto detected_instrset = static_cast<instrset>(INSTRSET);

		inline instrset instrset_detect() // runtime—not compile-time—value
		{
			#ifdef VCL_NAMESPACE
			const auto result = VCL_NAMESPACE ::instrset_detect();
			#else
			const auto result = ::instrset_detect();
			#endif
			return static_cast<instrset>(result); // may not be the same as compile-time *detected_instrset*
		}

		//// "Additional instruction set extensions are not necessarily part of a linear sequence."
		//enum class instrset_extensions
		//{
		//	FMA3,
		//	AVX512ER,
		//	AVX512VBMI,
		//	AVX512VBMI2,
		//	F16C,
		//	AVX512FP16
		//};
	}
}

#ifdef VCL_NAMESPACE
}
#endif