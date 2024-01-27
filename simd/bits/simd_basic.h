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
    // The proposal calls for explicit specializations of `basic_simd`; that's because
    // normal implementations will need code specific to each specialization.
    // Since this is built on VCL, that work has already been done, it's
    // just called `Vec4i` instead of `basic_simd<int, 4>`.
	template<typename T, typename Abi = details::simd_abi::native_abi<T>>
	class basic_simd {
	public:
		using value_type = T;
		//using reference = see below;
		//using mask_type = basic_simd_mask<T, Abi>; // TODO: basic_simd_mask<sizeof(T), abi_type>;
        using abi_type = Abi;

		using details_Vec_type_ = typename abi_type::type; // e.g., Vec4i

		static constexpr std::integral_constant<details::size_type, 16> size;
		 
		constexpr basic_simd() noexcept = default;

		// [simd.ctor]
		template<typename U> constexpr basic_simd(U&& value) noexcept : v_(value) {}
		template<typename U, typename UAbi>
		constexpr explicit basic_simd(const basic_simd<U, UAbi>& other) noexcept : v_(other.v_) { }
		template<typename G> constexpr explicit basic_simd(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept
		{

		}

    private:
		details_Vec_type_ v_;
    public:
        // "Implementations should enable explicit conversion from and to implementation-defined types.
        // This adds one or more of the following declarations to class `basic_simd`:"
  		constexpr explicit operator details_Vec_type_() const { return v_; }
		constexpr explicit basic_simd(const details_Vec_type_& init) : v_(init) { }
	};

	template<typename T, details::size_type N = basic_simd<T>::size()>
	using simd = basic_simd<T, details::simd_abi::deduce_t<T, N>>;
}

#ifdef VCL_NAMESPACE
}
#endif