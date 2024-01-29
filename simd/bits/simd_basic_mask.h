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
		template<typename Vec>
		class Vec_basic_simd_mask {
			using T = Vec_value_type<Vec::elementtype()>;
		public:
			static constexpr auto Bytes = sizeof(T);
			using Vec_t = for_use_with<Vec>; // e.g, Vec_t=Vec16fb for Vec=Vec16f
			using value_type = bool;
			//using reference = see below;
			using abi_type = details::simd_abi::fixed_size<Vec_t::size()>;

			static constexpr auto size = basic_simd<details::integer_from<Bytes>, abi_type>::size;
			static_assert(Vec_t::size() == basic_simd<details::integer_from<Bytes>, abi_type>::size());

			constexpr Vec_basic_simd_mask() noexcept = default;

			// [simd.ctor]
			template<typename U> constexpr Vec_basic_simd_mask(U&& value) noexcept : v_(value) {}
			template<typename UVec_b>
			constexpr explicit Vec_basic_simd_mask(const Vec_basic_simd_mask<UVec_b>& other) noexcept : v_(other.v_) {}
			template<typename G> constexpr explicit Vec_basic_simd_mask(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;

			// "Implementations should enable explicit conversion from and to implementation-defined types."
			constexpr explicit operator Vec_t() const { return v_; }
			constexpr explicit Vec_basic_simd_mask(const Vec_t& init) : v_(init) {}
		private:
			Vec_t v_;
		};
	}

	#define VECTORCLASS_basic_simd_mask(type_, size_) \
	template<> class basic_simd_mask<type_, details::simd_abi::fixed_size<size_>> \
		: public details::Vec_basic_simd_mask<details::Vec<size_, type_>> { }

	// "... The specialization basic_simd_mask<T, Abi> is supported if ... Abi is simd_abi::fixed_size<N>, ..."
	// 128 Total bits
	VECTORCLASS_basic_simd_mask(int8_t, 16);
	VECTORCLASS_basic_simd_mask(uint8_t, 16);
	VECTORCLASS_basic_simd_mask(int16_t, 8);
	VECTORCLASS_basic_simd_mask(uint16_t, 8);
	VECTORCLASS_basic_simd_mask(int32_t, 4);
	VECTORCLASS_basic_simd_mask(uint32_t, 4);
	VECTORCLASS_basic_simd_mask(int64_t, 2);
	VECTORCLASS_basic_simd_mask(uint64_t, 2);
	VECTORCLASS_basic_simd_mask(float, 4);
	VECTORCLASS_basic_simd_mask(double, 2);
	// 256 Total bits
	VECTORCLASS_basic_simd_mask(int8_t, 32);
	VECTORCLASS_basic_simd_mask(uint8_t, 32);
	VECTORCLASS_basic_simd_mask(int16_t, 16);
	VECTORCLASS_basic_simd_mask(uint16_t, 16);
	VECTORCLASS_basic_simd_mask(int32_t, 8);
	VECTORCLASS_basic_simd_mask(uint32_t, 8);
	VECTORCLASS_basic_simd_mask(int64_t, 4);
	VECTORCLASS_basic_simd_mask(uint64_t, 4);
	VECTORCLASS_basic_simd_mask(float, 8);
	VECTORCLASS_basic_simd_mask(double, 4);
	// 512 Total bits
	VECTORCLASS_basic_simd_mask(int8_t, 64);
	VECTORCLASS_basic_simd_mask(uint8_t, 64);
	VECTORCLASS_basic_simd_mask(int16_t, 32);
	VECTORCLASS_basic_simd_mask(uint16_t, 32);
	VECTORCLASS_basic_simd_mask(int32_t, 16);
	VECTORCLASS_basic_simd_mask(uint32_t, 16);
	VECTORCLASS_basic_simd_mask(int64_t, 8);
	VECTORCLASS_basic_simd_mask(uint64_t, 8);
	VECTORCLASS_basic_simd_mask(float, 16);
	VECTORCLASS_basic_simd_mask(double, 8);

	#undef VECTORCLASS_basic_simd_mask

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