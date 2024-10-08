/*
//@HEADER
// ************************************************************************
//
// fwd.hpp
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

#ifndef PRESSIOOPS_EXPRESSIONS_FWD_HPP_
#define PRESSIOOPS_EXPRESSIONS_FWD_HPP_

namespace pressio{

namespace expressions{ namespace impl{
template <class T, class enable = void> class SpanExpr;
template <class T, class enable = void> class SpanTraits;
template <class T, class enable = void> class SubspanExpr;
template <class T, class enable = void> class SubSpanTraits;
template <class T, class enable = void> class DiagonalExpr;
template <class T, class enable = void> class DiagonalTraits;
template <class T, class enable = void> class ColumnExpr;
template <class T, class enable = void> class ColumnTraits;
}}//end namespace expressions::impl

template<class T>
struct Traits<expressions::impl::SpanExpr<T>>
  : expressions::impl::SpanTraits< expressions::impl::SpanExpr<T> >{};

template<class T>
struct Traits<expressions::impl::SubspanExpr<T>>
  : expressions::impl::SubSpanTraits< expressions::impl::SubspanExpr<T> >{};

template<class T>
struct Traits<expressions::impl::DiagonalExpr<T>>
  : expressions::impl::DiagonalTraits< expressions::impl::DiagonalExpr<T> >{};

template<class T>
struct Traits<expressions::impl::ColumnExpr<T>>
  : expressions::impl::ColumnTraits< expressions::impl::ColumnExpr<T> >{};

}//end namespace pressio
#endif  // PRESSIOOPS_EXPRESSIONS_FWD_HPP_
