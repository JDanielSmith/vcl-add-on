#pragma once

#include <memory>
#include <type_traits>

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
	/*
	template<class T, class Abi = native-abi<T>> class basic_simd;
	*/
	template<typename T, typename Abi = details::simd_abi::native_abi<T>>
	class basic_simd {
	public:
		using value_type = T;
		//using reference = see below;
		using mask_type = basic_simd_mask<T, Abi>; // TODO: basic_simd_mask<sizeof(T), Abi>; ???
        using abi_type = Abi;

		// "This member is present even if the particular basic_simd specialization is not supported."
		static constexpr std::integral_constant<details::size_type, -1> size;
		 
		constexpr basic_simd() noexcept = default;

		// [simd.ctor]
		template<typename U> constexpr basic_simd(U&& value) noexcept;
		template<typename U, typename UAbi>
		constexpr explicit basic_simd(const basic_simd<U, UAbi>& other) noexcept;
		template<typename G> constexpr explicit basic_simd(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;
	};

	namespace details
	{
		template<typename T, typename Abi>
		class Vec_basic_simd {
		public:
			using value_type = T;
			//using reference = see below;
			using mask_type = basic_simd_mask<T, Abi>; // TODO: basic_simd_mask<sizeof(T), Abi>; ???
			using abi_type = Abi;

			constexpr Vec_basic_simd() noexcept = default;

			// [simd.ctor]
			template<typename U> constexpr Vec_basic_simd(U&& value) noexcept {}
			template<typename U, typename UAbi>
			constexpr explicit Vec_basic_simd(const Vec_basic_simd<U, UAbi>& other) noexcept {}
			template<typename G> constexpr explicit Vec_basic_simd(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept {}
		};
	}

	// "... The specialization basic_simd<T, Abi> is supported if ... Abi is simd_abi::fixed_size<N>, ..."
	template<> class basic_simd<float, details::simd_abi::fixed_size<16>> 
	: public details::Vec_basic_simd<float, details::simd_abi::fixed_size<16>> {
	public:
		static constexpr std::integral_constant<details::size_type, 16> size;
	};

	/*
	template<class T, simd-size-type N = basic_simd<T>::size()>
	using simd = basic_simd<T, deduce-t<T, N>>;
	*/
	template<typename T, details::size_type N = basic_simd<T>::size()>
	using simd = basic_simd<T, details::simd_abi::deduce_t<T, N>>;
}

#ifdef VCL_NAMESPACE
}
#endif