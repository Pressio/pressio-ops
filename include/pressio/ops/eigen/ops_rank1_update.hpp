/*
//@HEADER
// ************************************************************************
//
// ops_rank1_update.hpp
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

#ifndef PRESSIOOPS_OPS_EIGEN_OPS_RANK1_UPDATE_HPP_
#define PRESSIOOPS_OPS_EIGEN_OPS_RANK1_UPDATE_HPP_

namespace pressio{ namespace ops{

/*
   below we constrain in all cases via is_convertible
   because the implementations are using Eigen native operations
   which are based on expressions and require
   coefficients to be convertible to scalar types of the vectors operands
 */

//----------------------------------------------------------------------
// computing:  V = a * V + b * V1
//----------------------------------------------------------------------
template<class T, class T1, class a_Type, class b_Type>
std::enable_if_t<
  // rank-1 update common constraints
     ::pressio::Traits<T>::rank == 1
  && ::pressio::Traits<T1>::rank == 1
  // TPL/container specific
  && (::pressio::is_vector_eigen<T>::value
   || ::pressio::is_expression_acting_on_eigen<T>::value)
  && (::pressio::is_vector_eigen<T1>::value
   || ::pressio::is_expression_acting_on_eigen<T1>::value)
  // scalar compatibility
  && ::pressio::all_have_traits_and_same_scalar<T, T1>::value
  && (std::is_floating_point<typename ::pressio::Traits<T>::scalar_type>::value
   || std::is_integral<typename ::pressio::Traits<T>::scalar_type>::value)
  && std::is_convertible<a_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<b_Type, typename ::pressio::Traits<T>::scalar_type>::value
  >
update(T & v,         const a_Type & a,
       const T1 & v1, const b_Type & b)
{
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v1, 0));

  using sc_t = typename ::pressio::Traits<T>::scalar_type;
  const auto zero = ::pressio::Constants<sc_t>::zero();
  const sc_t a_(a);
  const sc_t b_(b);

  if (b_ == zero) {
    ::pressio::ops::scale(v, a_);
    return;
  }

  auto & v_n = impl::get_native(v);
  const auto & v_n1 = impl::get_native(v1);
  if (a_ == zero) {
    v_n = b_*v_n1;
  } else {
    v_n = a_*v_n + b_*v_n1;
  }
}

//----------------------------------------------------------------------
//  overloads for computing this: V = a * V + b * V1 + c * V2
//----------------------------------------------------------------------
template<
  class T, class T1, class T2,
  class a_Type, class b_Type, class c_Type
  >
std::enable_if_t<
  // rank-1 update common constraints
     ::pressio::Traits<T>::rank == 1
  && ::pressio::Traits<T1>::rank == 1
  && ::pressio::Traits<T2>::rank == 1
  // TPL/container specific
  && (::pressio::is_vector_eigen<T>::value
   || ::pressio::is_expression_acting_on_eigen<T>::value)
  && (::pressio::is_vector_eigen<T1>::value
   || ::pressio::is_expression_acting_on_eigen<T1>::value)
  && (::pressio::is_vector_eigen<T2>::value
   || ::pressio::is_expression_acting_on_eigen<T2>::value)
  // scalar compatibility
  && ::pressio::all_have_traits_and_same_scalar<T, T1, T2>::value
  && (std::is_floating_point<typename ::pressio::Traits<T>::scalar_type>::value
   || std::is_integral<typename ::pressio::Traits<T>::scalar_type>::value)
  && std::is_convertible<a_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<b_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<c_Type, typename ::pressio::Traits<T>::scalar_type>::value
  >
update(T & v,         const a_Type &a,
       const T1 & v1, const b_Type &b,
       const T2 & v2, const c_Type &c)
{
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v1, 0));
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v2, 0));

  using sc_t = typename ::pressio::Traits<T>::scalar_type;
  const auto zero = ::pressio::Constants<sc_t>::zero();
  const sc_t a_(a);
  const sc_t b_(b);
  const sc_t c_(c);

  if (b_ == zero) {
    ::pressio::ops::update(v, a, v2, c);
  } else if (c_ == zero) {
    ::pressio::ops::update(v, a, v1, b);
  } else {
    auto & v_n = impl::get_native(v);
    const auto & v_n1 = impl::get_native(v1);
    const auto & v_n2 = impl::get_native(v2);
    if (a_ == zero) {
      v_n = b_*v_n1 + c_*v_n2;
    } else {
      v_n = a_*v_n + b_*v_n1 + c_*v_n2;
    }
  }
}

//----------------------------------------------------------------------
//  overloads for computing:
//	V = a * V + b * V1 + c * V2 + d * V3
//----------------------------------------------------------------------
template<
  class T, class T1, class T2, class T3,
  class a_Type, class b_Type, class c_Type, class d_Type
  >
std::enable_if_t<
  // rank-1 update common constraints
     ::pressio::Traits<T>::rank == 1
  && ::pressio::Traits<T1>::rank == 1
  && ::pressio::Traits<T2>::rank == 1
  && ::pressio::Traits<T3>::rank == 1
  // TPL/container specific
  && (::pressio::is_vector_eigen<T>::value
   || ::pressio::is_expression_acting_on_eigen<T>::value)
  && (::pressio::is_vector_eigen<T1>::value
   || ::pressio::is_expression_acting_on_eigen<T1>::value)
  && (::pressio::is_vector_eigen<T2>::value
   || ::pressio::is_expression_acting_on_eigen<T2>::value)
  && (::pressio::is_vector_eigen<T3>::value
    || ::pressio::is_expression_acting_on_eigen<T3>::value)
  // scalar compatibility
  && ::pressio::all_have_traits_and_same_scalar<T, T1, T2, T3>::value
  && (std::is_floating_point<typename ::pressio::Traits<T>::scalar_type>::value
   || std::is_integral<typename ::pressio::Traits<T>::scalar_type>::value)
  && std::is_convertible<a_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<b_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<c_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<d_Type, typename ::pressio::Traits<T>::scalar_type>::value
  >
update(T & v,         const a_Type &a,
       const T1 & v1, const b_Type &b,
       const T2 & v2, const c_Type &c,
       const T3 & v3, const d_Type &d)
{
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v1, 0));
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v2, 0));
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v3, 0));

  using sc_t = typename ::pressio::Traits<T>::scalar_type;
  const auto zero = ::pressio::Constants<sc_t>::zero();
  const sc_t a_(a);
  const sc_t b_(b);
  const sc_t c_(c);
  const sc_t d_(d);

  if (b_ == zero) {
    ::pressio::ops::update(v, a, v2, c, v3, d);
  } else if (c_ == zero) {
    ::pressio::ops::update(v, a, v1, b, v3, d);
  } else if (d_ == zero) {
    ::pressio::ops::update(v, a, v1, b, v2, c);
  } else {
    auto & v_n = impl::get_native(v);
    const auto & v_n1 = impl::get_native(v1);
    const auto & v_n2 = impl::get_native(v2);
    const auto & v_n3 = impl::get_native(v3);
    if (a_ == zero) {
      v_n = b_*v_n1 + c_*v_n2 + d_*v_n3;
    } else {
      v_n = a_*v_n + b_*v_n1 + c_*v_n2 + d_*v_n3;
    }
  }
}

//----------------------------------------------------------------------
//  overloads for computing:
//	V = a * V + b * V1 + c * V2 + d * V3 + e * V4
//----------------------------------------------------------------------
template<
  class T, class T1, class T2, class T3, class T4,
  class a_Type, class b_Type, class c_Type, class d_Type, class e_Type
  >
std::enable_if_t<
  // rank-1 update common constraints
     ::pressio::Traits<T>::rank == 1
  && ::pressio::Traits<T1>::rank == 1
  && ::pressio::Traits<T2>::rank == 1
  && ::pressio::Traits<T3>::rank == 1
  && ::pressio::Traits<T4>::rank == 1
  // TPL/container specific
  && (::pressio::is_vector_eigen<T>::value
   || ::pressio::is_expression_acting_on_eigen<T>::value)
  && (::pressio::is_vector_eigen<T1>::value
   || ::pressio::is_expression_acting_on_eigen<T1>::value)
  && (::pressio::is_vector_eigen<T2>::value
   || ::pressio::is_expression_acting_on_eigen<T2>::value)
  && (::pressio::is_vector_eigen<T3>::value
    || ::pressio::is_expression_acting_on_eigen<T3>::value)
  && (::pressio::is_vector_eigen<T4>::value
    || ::pressio::is_expression_acting_on_eigen<T4>::value)
  // scalar compatibility
  && ::pressio::all_have_traits_and_same_scalar<T, T1, T2, T3, T4>::value
  && (std::is_floating_point<typename ::pressio::Traits<T>::scalar_type>::value
   || std::is_integral<typename ::pressio::Traits<T>::scalar_type>::value)
  && std::is_convertible<a_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<b_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<c_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<d_Type, typename ::pressio::Traits<T>::scalar_type>::value
  && std::is_convertible<e_Type, typename ::pressio::Traits<T>::scalar_type>::value
  >
update(T & v,         const a_Type &a,
       const T1 & v1, const b_Type &b,
       const T2 & v2, const c_Type &c,
       const T3 & v3, const d_Type &d,
       const T4 & v4, const e_Type &e)
{
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v1, 0));
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v2, 0));
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v3, 0));
  assert(::pressio::ops::extent(v, 0) == ::pressio::ops::extent(v4, 0));

  using sc_t = typename ::pressio::Traits<T>::scalar_type;
  const auto zero = ::pressio::Constants<sc_t>::zero();
  const sc_t a_(a);
  const sc_t b_(b);
  const sc_t c_(c);
  const sc_t d_(d);
  const sc_t e_(e);

  if (b_ == zero) {
    ::pressio::ops::update(v, a, v2, c, v3, d, v4, e);
  } else if (c_ == zero) {
    ::pressio::ops::update(v, a, v1, b, v3, d, v4, e);
  } else if (d_ == zero) {
    ::pressio::ops::update(v, a, v1, b, v2, c, v4, e);
  } else if (e_ == zero) {
    ::pressio::ops::update(v, a, v1, b, v2, c, v3, d);
  } else {
    auto & v_n = impl::get_native(v);
    const auto & v_n1 = impl::get_native(v1);
    const auto & v_n2 = impl::get_native(v2);
    const auto & v_n3 = impl::get_native(v3);
    const auto & v_n4 = impl::get_native(v4);
    if (a_ == zero) {
      v_n = b_*v_n1 + c_*v_n2 + d_*v_n3 + e_*v_n4;
    } else {
      v_n = a_*v_n + b_*v_n1 + c_*v_n2 + d_*v_n3 + e_*v_n4;
    }
  }
}

}}//end namespace pressio::ops
#endif  // PRESSIOOPS_OPS_EIGEN_OPS_RANK1_UPDATE_HPP_
