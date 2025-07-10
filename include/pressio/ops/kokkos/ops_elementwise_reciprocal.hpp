/*
//@HEADER
// ************************************************************************
//
// ops_elementwise_reciprocal.hpp
//                     	         Pressio
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

#ifndef PRESSIOOPS_OPS_KOKKOS_OPS_ELEMENTWISE_RECIPROCAL_HPP_
#define PRESSIOOPS_OPS_KOKKOS_OPS_ELEMENTWISE_RECIPROCAL_HPP_

#include "ops_vector_reciprocal_kokkos_functor.hpp"

namespace pressio{ namespace ops{

//----------------------------------------------------------------------
// computing elementwise:  y = 1/z
//----------------------------------------------------------------------
template <typename T1, typename T2>
std::enable_if_t<
     ::pressio::Traits<T1>::rank == 1
  && ::pressio::Traits<T2>::rank == 1
  // TPL/container specific
  && (::pressio::is_native_container_kokkos<T1>::value
   || ::pressio::is_expression_acting_on_kokkos<T1>::value)
  && (::pressio::is_native_container_kokkos<T2>::value
   || ::pressio::is_expression_acting_on_kokkos<T2>::value)
  // scalar compatibility
  && ::pressio::all_have_traits_and_same_scalar<T1, T2>::value
  && (std::is_floating_point<typename ::pressio::Traits<T1>::scalar_type>::value
   || std::is_integral<typename ::pressio::Traits<T1>::scalar_type>::value)
  >
elementwise_reciprocal(const T1 & z, T2 & y)
{
  assert(z.extent(0) == y.extent(0));

  using t1_t = typename impl::NativeType<T1>::type;
  using t2_t = typename impl::NativeType<T2>::type;
  using scalar_t = typename ::pressio::Traits<T1>::scalar_type;

  using fnctr_t = ::pressio::ops::impl::VectorReciprocalFunctor<t1_t,t2_t,scalar_t>;
  fnctr_t F(impl::get_native(z), impl::get_native(y));
  Kokkos::parallel_for(z.extent(0), F);
}

}}//end namespace pressio::ops
#endif  // PRESSIOOPS_OPS_KOKKOS_OPS_ELEMENTWISE_RECIPROCAL_HPP_
