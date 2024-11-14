/*
//@HEADER
// ************************************************************************
//
// ops_add_to_diagonal.hpp
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

#ifndef PRESSIOOPS_OPS_KOKKOS_OPS_ADD_TO_DIAGONAL_HPP_
#define PRESSIOOPS_OPS_KOKKOS_OPS_ADD_TO_DIAGONAL_HPP_

namespace pressio{ namespace ops{

/*
  stand-in function to prevent build errors
  when Eigen is disabled
*/
template <typename T, class ScalarType>
std::enable_if_t<
  ::pressio::is_native_container_kokkos<T>::value
  && std::is_convertible<ScalarType, typename ::pressio::Traits<T>::scalar_type>::value
  >
add_to_diagonal(T & o, const ScalarType & value)
{
  // Prior to the definition of this function,
  // add_to_diagonal was only enabled for Eigen containers
  // (see ops/eigen/add_to_diagonal.hpp).
  //
  // In Pressio PR 708 (https://github.com/Pressio/pressio/pull/708),
  // we added a Kokkos-only CI pipeline. However, disabling Eigen
  // caused a build error because add_to_diagonal was still called
  // by Pressio's discrete_jacobian function.
  //
  // This function therefore serves as a placeholder so that when Eigen
  // is disabled, the function still exists and the code can compile.
  //
  // Note: This change is temporary, and this function
  // should be implemented properly in the future.
  throw std::runtime_error("missing implementation");
}

}} //end namespace pressio::ops
#endif  // PRESSIOOPS_OPS_KOKKOS_OPS_ADD_TO_DIAGONAL_HPP_
