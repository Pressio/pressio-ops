/*
//@HEADER
// ************************************************************************
//
// is_expression.hpp
//                     		  Pressio
//                             Copyright 2019
//    National Technology & Engineering Solutions of Sandia, LLC (NTESS)
//
// Under the terms of Contract DE-NA0003525 with NTESS, the
// U.S. Government retains certain rights in this software.
//
// Pressio is licensed under BSD-3-Clause terms of use:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Francesco Rizzi (fnrizzi@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef PRESSIOOPS_EXPRESSIONS_IS_EXPRESSION_HPP_
#define PRESSIOOPS_EXPRESSIONS_IS_EXPRESSION_HPP_

namespace pressio{

// Macro to define a family of simple trait classes that detect if a type T
// is a specific Pressio expression type.
//
// For a given pair (NAMEA, NAMEB):
//   - It defines a trait named `is_expression_NAMEA`.
//   - By default, the trait inherits from std::false_type.
//   - It specializes the trait to std::true_type if T is:
//
//       ::pressio::expressions::impl::NAMEB##Expr<T>
//       const ::pressio::expressions::impl::NAMEB##Expr<T>
//       ::pressio::expressions::impl::NAMEB##Expr<const T>
//       const ::pressio::expressions::impl::NAMEB##Expr<const T>
//
//   This ensures the trait works for both const and non-const cases.
//
// Example:
//   PRESSIO_IMPL_IS_EXPRESSION(diagonal, Diagonal)
//   defines `is_expression_diagonal` trait for DiagonalExpr<T>.
//
// Usage:
//   static_assert(is_expression_diagonal<DiagonalExpr<MyMatrix>>::value, "...");
//   static_assert(!is_expression_diagonal<int>::value, "...");
//
#define PRESSIO_IMPL_IS_EXPRESSION(NAMEA, NAMEB) \
  template <typename T> struct is_expression_##NAMEA : std::false_type{}; \
  template <typename T> struct is_expression_##NAMEA<			\
    ::pressio::expressions::impl::NAMEB##Expr<T> > : std::true_type{};	\
  template <typename T> struct is_expression_##NAMEA<			\
    const ::pressio::expressions::impl::NAMEB##Expr<T> > : std::true_type{};	\
  template <typename T> struct is_expression_##NAMEA<			\
    ::pressio::expressions::impl::NAMEB##Expr<const T> > : std::true_type{}; \
  template <typename T> struct is_expression_##NAMEA<			\
   const ::pressio::expressions::impl::NAMEB##Expr<const T> > : std::true_type{}; \

PRESSIO_IMPL_IS_EXPRESSION(diagonal, Diagonal)
PRESSIO_IMPL_IS_EXPRESSION(span, Span)
PRESSIO_IMPL_IS_EXPRESSION(subspan, Subspan)
PRESSIO_IMPL_IS_EXPRESSION(column, Column)


// Trait to detect whether a type T is considered an "expression".
// By default, it inherits from std::false_type.
// If T matches any of the sub-traits below, it inherits from std::true_type.
// This is used to enable or disable certain template overloads for expression types.
//
// A type T is considered an expression if any of these are true:
//   - is_expression_span<T>::value
//   - is_expression_diagonal<T>::value
//   - is_expression_subspan<T>::value
//   - is_expression_column<T>::value
//
// Example:
//   static_assert(is_expression<MySpan>::value, "...");
//   static_assert(!is_expression<int>::value, "...");

template <typename T, typename enable = void>
struct is_expression : std::false_type{};

template <typename T>
struct is_expression<
  T,
  std::enable_if_t<
    is_expression_span<T>::value
    || is_expression_diagonal<T>::value
    || is_expression_subspan<T>::value
    || is_expression_column<T>::value
    >
  > : std::true_type{};



#ifdef PRESSIO_ENABLE_TPL_EIGEN

// Primary trait: by default, any type T is NOT an expression acting on an Eigen container.
template <typename T>
struct is_expression_acting_on_eigen : std::false_type {};

// Specialization for DiagonalExpr:
// If the wrapped type T is a native Eigen container, inherit true_type; otherwise false_type.
template <typename T>
struct is_expression_acting_on_eigen<
  ::pressio::expressions::impl::DiagonalExpr<T>
> : std::conditional_t<
      ::pressio::is_native_container_eigen<T>::value,
      std::true_type,
      std::false_type
    > {};

// Specialization for SpanExpr:
// Same logic: acts on Eigen if T is native Eigen.
template <typename T>
struct is_expression_acting_on_eigen<
  ::pressio::expressions::impl::SpanExpr<T>
> : std::conditional_t<
      ::pressio::is_native_container_eigen<T>::value,
      std::true_type,
      std::false_type
    > {};

// Specialization for SubspanExpr:
template <typename T>
struct is_expression_acting_on_eigen<
  ::pressio::expressions::impl::SubspanExpr<T>
> : std::conditional_t<
      ::pressio::is_native_container_eigen<T>::value,
      std::true_type,
      std::false_type
    > {};

// Specialization for ColumnExpr:
template <typename T>
struct is_expression_acting_on_eigen<
  ::pressio::expressions::impl::ColumnExpr<T>
> : std::conditional_t<
      ::pressio::is_native_container_eigen<T>::value,
      std::true_type,
      std::false_type
    > {};

#endif // PRESSIO_ENABLE_TPL_EIGEN



#ifdef PRESSIO_ENABLE_TPL_KOKKOS

// Primary trait: by default, any type T is NOT an expression acting on a Kokkos container.
template <typename T>
struct is_expression_acting_on_kokkos : std::false_type {};

// Specialization for DiagonalExpr:
// True if the wrapped type T is a native Kokkos container.
template <typename T>
struct is_expression_acting_on_kokkos<
  ::pressio::expressions::impl::DiagonalExpr<T>
> : std::conditional_t<
      ::pressio::is_native_container_kokkos<T>::value,
      std::true_type,
      std::false_type
    > {};

// Specialization for SpanExpr:
// True if the wrapped type T is a native Kokkos container.
template <typename T>
struct is_expression_acting_on_kokkos<
  ::pressio::expressions::impl::SpanExpr<T>
> : std::conditional_t<
      ::pressio::is_native_container_kokkos<T>::value,
      std::true_type,
      std::false_type
    > {};

// Specialization for SubspanExpr:
// True if the wrapped type T is a native Kokkos container.
template <typename T>
struct is_expression_acting_on_kokkos<
  ::pressio::expressions::impl::SubspanExpr<T>
> : std::conditional_t<
      ::pressio::is_native_container_kokkos<T>::value,
      std::true_type,
      std::false_type
    > {};

#endif // PRESSIO_ENABLE_TPL_KOKKOS



#ifdef PRESSIO_ENABLE_TPL_TRILINOS

// Primary trait: by default, any type T is NOT an expression acting on a Tpetra MultiVector.
template <typename T>
struct is_expression_acting_on_tpetra : std::false_type {};

// Specialization for ColumnExpr:
// True if the wrapped type T is a Tpetra MultiVector.
template <typename T>
struct is_expression_acting_on_tpetra<
  ::pressio::expressions::impl::ColumnExpr<T>
> : std::conditional_t<
      ::pressio::is_multi_vector_tpetra<T>::value,
      std::true_type,
      std::false_type
    > {};

// Checks if T is a Column expression AND it acts on a Tpetra MultiVector.
// Evaluates to true if both conditions hold.
template <typename T>
struct is_expression_column_acting_on_tpetra
  : std::conditional_t<
      ::pressio::is_expression_column<T>::value &&
      is_expression_acting_on_tpetra<T>::value,
      std::true_type,
      std::false_type
    > {};


// Primary trait: by default, any type T is NOT an expression acting on a Tpetra Block MultiVector.
template <typename T>
struct is_expression_acting_on_tpetra_block : std::false_type {};

// Specialization for ColumnExpr:
// True if the wrapped type T is a Tpetra Block MultiVector.
template <typename T>
struct is_expression_acting_on_tpetra_block<
  ::pressio::expressions::impl::ColumnExpr<T>
> : std::conditional_t<
      ::pressio::is_multi_vector_tpetra_block<T>::value,
      std::true_type,
      std::false_type
    > {};

// Checks if T is a Column expression AND it acts on a Tpetra Block MultiVector.
template <typename T>
struct is_expression_column_acting_on_tpetra_block
  : std::conditional_t<
      ::pressio::is_expression_column<T>::value &&
      is_expression_acting_on_tpetra_block<T>::value,
      std::true_type,
      std::false_type
    > {};

#endif // PRESSIO_ENABLE_TPL_TRILINOS

}
#endif  // PRESSIOOPS_EXPRESSIONS_IS_EXPRESSION_HPP_
