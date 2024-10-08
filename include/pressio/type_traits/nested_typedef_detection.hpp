/*
//@HEADER
// ************************************************************************
//
// nested_typedef_detection.hpp
//                          Pressio
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

#ifndef PRESSIOOPS_TYPE_TRAITS_NESTED_TYPEDEF_DETECTION_HPP_
#define PRESSIOOPS_TYPE_TRAITS_NESTED_TYPEDEF_DETECTION_HPP_

namespace pressio{

#define PRESSIO_IMPL_HAS_NESTED_TYPEDEF(NAME) \
  template <typename T, typename enable = void>\
  struct has_##NAME##_typedef : std::false_type{};\
  template <typename T>\
  struct has_##NAME##_typedef<T,\
  std::enable_if_t< !std::is_void<typename T::NAME##_type>::value > \
  > : std::true_type{};\

PRESSIO_IMPL_HAS_NESTED_TYPEDEF(scalar)            // usage: generic concepts
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(jacobian)          // usage: ode,      solvers_nonlinear
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(residual)          // usage: ode, rom, solvers_nonlinear
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(right_hand_side)   // usage: ode, rom
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(rhs)		   // usage: ode, rom
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(discrete_residual) // usage: ode, rom
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(state)             // usage: ode, rom, solvers_nonlinear
// usage: ode
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(mass_matrix)
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(discrete_jacobian)
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(independent_variable)
// usage: solvers_nonlinear
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(matrix)
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(hessian)
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(gradient)
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(residual_norm)
// usage: rom
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(time)
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(full_state)
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(reduced_state)
PRESSIO_IMPL_HAS_NESTED_TYPEDEF(basis_matrix)

}//end namespace
#endif  // PRESSIOOPS_TYPE_TRAITS_NESTED_TYPEDEF_DETECTION_HPP_
