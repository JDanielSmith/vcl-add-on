#pragma once

#include <memory>

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
    template<size_t Bytes, class Abi = native-abi<T>> class basic_simd_mask;
    */
    // TODO: template<size_t Bytes, typename Abi = details::simd_abi::native_abi<T>> class basic_simd_mask { ???
	template<typename T, typename Abi = details::simd_abi::native_abi<T>> class basic_simd_mask {
	public:
		using value_type = bool;
		//using reference = see below;
		using abi_type = Abi;

        static constexpr auto size = basic_simd<details::integer_from<sizeof(T)>, Abi>::size;

		constexpr basic_simd_mask() noexcept = default;

        // [simd.mask.ctor]
        constexpr explicit basic_simd_mask(value_type v) noexcept;
        template<typename U, class UAbi>// TODO: template<size_t UBytes, class UAbi>
        constexpr explicit basic_simd_mask(const basic_simd_mask<U, UAbi>& other) noexcept;
        template<typename G> constexpr explicit basic_simd_mask(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;
	};

    namespace details
    {
        template<typename Vec_b>
        class Vec_basic_simd_mask {
        public:
            using value_type = bool;
            //using reference = see below;
            using abi_type = details::simd_abi::fixed_size<Vec_b::size()>;

            using T = Vec_type<Vec_b>;
            static constexpr auto size = basic_simd<details::integer_from<sizeof(T)>, abi_type>::size; // TODO: basic_simd<details::integer_from<Bytes>, Abi>::size;

            constexpr Vec_basic_simd_mask() noexcept = default;

            // [simd.ctor]
            template<typename U> constexpr Vec_basic_simd_mask(U&& value) noexcept : v_(value) {}
            template<typename UVec_b>
            constexpr explicit Vec_basic_simd_mask(const Vec_basic_simd_mask<UVec_b>& other) noexcept : v_(other.v_) {}
            template<typename G> constexpr explicit Vec_basic_simd_mask(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;

            // "Implementations should enable explicit conversion from and to implementation-defined types."
            constexpr explicit operator Vec_b() const { return v_; }
            constexpr explicit Vec_basic_simd_mask(const Vec_b& init) : v_(init) {}
            Vec_b v_;
        };
    }

    #define VECTORCLASS_basic_simd_mask(type_, size_) \
	template<> class basic_simd_mask<type_, details::simd_abi::fixed_size<size_>> \
        : public details::Vec_basic_simd_mask<details::VecNb<size_, type_>> { }

    // "... The specialization basic_simd_mask<T, Abi> is supported if ... Abi is simd_abi::fixed_size<N>, ..."
    VECTORCLASS_basic_simd_mask(std::int32_t, 16);
    VECTORCLASS_basic_simd_mask(float, 16);

    /*
    template<class T, simd-size-type N = basic_simd_mask<sizeof(T)>::size()>
    using simd_mask = basic_simd_mask<sizeof(T), deduce-t<T, N>>;
    */
	template<typename T, details::size_type N = basic_simd_mask<T>::size()>
	using simd_mask = basic_simd_mask<T, details::simd_abi::deduce_t<T, N>>; // TODO: sizeof(T)
}

#ifdef VCL_NAMESPACE
}
#endif