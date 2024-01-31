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
		// The vector class library has a specific mask type for each Vec type; e.g.,
		// `Vec16ib` "for use with" `Vec16i` and `Vec16ui`.  To implement that, 
		// the basic_simd_mask<> template is changed from `size_t Bytes`
		// to `typename T`; that keeps the type around long enough to
		// pick the right Vec mask for the given Vec.
		template<typename Vec> // this is e.g., `Vec16i`, **not** `Vec16ib`
		class Vec_basic_simd_mask {
			using T = Vec_elementtype_t<Vec::elementtype()>; // e.g., `int32_t`
		public:
			static constexpr auto Bytes = sizeof(T); // sizeof(int32_t) == sizeof(uint32_t)
			using Vec_type = Vecb_abi<Vec>::Boolean_vector_class; // e.g, Vec_type=Vec16ib for Vec=Vec16i
			using value_type = bool;
			//using reference = see below;
			using abi_type = details::simd_abi::fixed_size<Vec_type::size()>;
			//using abi_type = details::Vcl_native_abi<Vec::size(), T>;

			static constexpr auto size = basic_simd<details::integer_from<Bytes>, abi_type>::size;
			static_assert(Vec_type::size() == basic_simd<details::integer_from<Bytes>, abi_type>::size());

			constexpr Vec_basic_simd_mask() noexcept = default;

			// [simd.ctor]
			template<typename U> constexpr Vec_basic_simd_mask(U&& value) noexcept : v_(value) {}
			template<typename UVec_b, typename UAbi>
			constexpr explicit Vec_basic_simd_mask(const basic_simd_mask<UVec_b, UAbi>& other) noexcept : v_(other.v_) {}
			template<typename UVec_b>
			constexpr explicit Vec_basic_simd_mask(const Vec_basic_simd_mask<UVec_b>& other) noexcept : v_(other.v_) {}
			template<typename G> constexpr explicit Vec_basic_simd_mask(G&& gen, std::nullptr_t /*TODO: remove*/) noexcept;

			// "Implementations should enable explicit conversion from and to implementation-defined types."
			constexpr explicit operator Vec_type() const { return v_; }
			constexpr explicit Vec_basic_simd_mask(const Vec_type& init) : v_(init) {}
			Vec_type v_;
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