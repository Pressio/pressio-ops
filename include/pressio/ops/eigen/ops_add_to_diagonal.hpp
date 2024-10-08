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

#ifndef PRESSIOOPS_OPS_EIGEN_OPS_ADD_TO_DIAGONAL_HPP_
#define PRESSIOOPS_OPS_EIGEN_OPS_ADD_TO_DIAGONAL_HPP_

namespace pressio{

namespace impl{

template<class T>
bool _eigen_matrix_has_diagonal_elements(T & M) {
  using value_type = typename ::pressio::Traits<T>::scalar_type;

  /*
    https://eigen.tuxfamily.org/dox-devel/classEigen_1_1SparseMatrix.html#ae6f4db56c76e4d374eb8507fbef5bdb5

    If the diagonal entries are written, then all diagonal entries must already exist, 
    otherwise an assertion will be raised.
    Since we do not catch the assertion, the program terminates which is what we want.
    Note that we need to add zero here so that if M is satisfies the condition, 
    then its values are not changed.
  */
  const volatile value_type zero = value_type(0);
  auto d = M.diagonal();
  for (int i=0; i<M.rows(); i++) {
    d(i) += zero;
  }
  return true;
}
} // end namespace impl

namespace ops{

/*
  constrained via is_convertible because the impl is using
  identity.coeffs() which returns an Eigen expression and for "*= value"
  to work, value has to be convertible to the the scalar type of ide
*/
template <typename T, class ScalarType>
std::enable_if_t<
  ::pressio::is_sparse_matrix_eigen<T>::value
  && std::is_convertible<ScalarType, typename ::pressio::Traits<T>::scalar_type>::value
  >
add_to_diagonal(T & o, const ScalarType & value)
{
  assert(::pressio::impl::_eigen_matrix_has_diagonal_elements(o));
  o.diagonal().array() += value;
}

/*
  constrained by checking directly if the operation is well-formed
  since below I am doing the loop myself so I just need to check that
  operation is well-formed
*/
template <typename T, class ScalarType>
std::enable_if_t<
  ::pressio::is_dense_matrix_eigen<T>::value
  && std::is_assignable<
    decltype( std::declval<T>()(0,0) ),
    decltype( std::declval<T>()(0,0) + std::declval<ScalarType>() )
    >::value
  >
add_to_diagonal(T & o, const ScalarType & value)
{
  assert(o.rows() == o.cols());
  for ( decltype(o.rows()) i=0; i<o.rows(); ++i){
    o(i,i) = o(i,i) + value;
  }
}

}}//end namespace pressio::ops
#endif  // PRESSIOOPS_OPS_EIGEN_OPS_ADD_TO_DIAGONAL_HPP_
