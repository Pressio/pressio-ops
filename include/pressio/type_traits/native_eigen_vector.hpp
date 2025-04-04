/*
//@HEADER
// ************************************************************************
//
// native_eigen_vector.hpp
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

#ifndef PRESSIOOPS_TYPE_TRAITS_NATIVE_EIGEN_VECTOR_HPP_
#define PRESSIOOPS_TYPE_TRAITS_NATIVE_EIGEN_VECTOR_HPP_

#ifdef PRESSIO_ENABLE_TPL_EIGEN
#include <Eigen/Dense>
#endif

namespace pressio{ 

template <typename T, typename enable = void>
struct is_dynamic_row_vector_eigen : std::false_type {};

#ifdef PRESSIO_ENABLE_TPL_EIGEN
template <typename T>
struct is_dynamic_row_vector_eigen<
  T,
  std::enable_if_t<
    std::is_same< 
      typename std::remove_cv<T>::type,
		  Eigen::Matrix<typename T::Scalar,1, Eigen::Dynamic>
		 >::value
    >
  > : std::true_type{};
#endif
//----------------------------------------------

template <typename T, typename enable = void>
struct is_static_row_vector_eigen : std::false_type {};

#ifdef PRESSIO_ENABLE_TPL_EIGEN
template <typename T>
struct is_static_row_vector_eigen<
  T,
  std::enable_if_t<
    std::is_same<
     typename std::remove_cv<T>::type,
		 Eigen::Matrix<typename T::Scalar, 1, T::ColsAtCompileTime>
		 >::value and
    !is_dynamic_row_vector_eigen<T>::value
    >
  > : std::true_type{};
#endif
//----------------------------------------------

template <typename T, typename enable = void>
struct is_dynamic_column_vector_eigen : std::false_type {};


#ifdef PRESSIO_ENABLE_TPL_EIGEN
template <typename T>
struct is_dynamic_column_vector_eigen<
  T,
  std::enable_if_t<
    std::is_same<
     typename std::remove_cv<T>::type,
		 Eigen::Matrix<typename T::Scalar, Eigen::Dynamic, 1>
		 >::value
    >
  > : std::true_type{};
#endif
//----------------------------------------------

template <typename T, typename enable = void>
struct is_static_column_vector_eigen : std::false_type {};


#ifdef PRESSIO_ENABLE_TPL_EIGEN
template <typename T>
struct is_static_column_vector_eigen<
  T,
  std::enable_if_t<
    std::is_same<
     typename std::remove_cv<T>::type,
		 Eigen::Matrix<typename T::Scalar, T::RowsAtCompileTime,1>
		 >::value and
    !is_dynamic_column_vector_eigen<T>::value
    >
  > : std::true_type{};
#endif
//----------------------------------------------

template <typename T, typename enable = void>
struct is_static_vector_eigen : std::false_type {};


#ifdef PRESSIO_ENABLE_TPL_EIGEN
template <typename T>
struct is_static_vector_eigen<
  T,
  std::enable_if_t<
    is_static_row_vector_eigen<T>::value ||
    is_static_column_vector_eigen<T>::value
    >
  > : std::true_type{};
#endif
//----------------------------------------------

template <typename T, typename enable = void>
struct is_dynamic_vector_eigen : std::false_type {};


#ifdef PRESSIO_ENABLE_TPL_EIGEN
template <typename T>
struct is_dynamic_vector_eigen<
  T,
  std::enable_if_t<
    is_dynamic_row_vector_eigen<T>::value or
    is_dynamic_column_vector_eigen<T>::value
    >
  > : std::true_type{};
#endif
//----------------------------------------------

template <typename T, typename enable = void>
struct is_vector_eigen : std::false_type {};

#ifdef PRESSIO_ENABLE_TPL_EIGEN
template <typename T>
struct is_vector_eigen<
  T,
  std::enable_if_t<
    is_dynamic_vector_eigen<T>::value or
    is_static_vector_eigen<T>::value
    >
  > : std::true_type{};
#endif

}//end namespace 
#endif  // PRESSIOOPS_TYPE_TRAITS_NATIVE_EIGEN_VECTOR_HPP_
