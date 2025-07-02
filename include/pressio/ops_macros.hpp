/*
//@HEADER
// ************************************************************************
//
// ops_macros.hpp
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

#ifndef PRESSIOOPS_OPS_MACROS_HPP
#define PRESSIOOPS_OPS_MACROS_HPP

#define PRESSIO_OPS_MAJOR_VERSION 0
#define PRESSIO_OPS_MINOR_VERSION 16
#define PRESSIO_OPS_PATCH_VERSION 0

// ----------------------------------------
// compiler version
// ----------------------------------------
#ifdef _MSVC_LANG
#define _PRESSIO_CPLUSPLUS _MSVC_LANG
#else
#define _PRESSIO_CPLUSPLUS __cplusplus
#endif

#define PRESSIO_CXX_STD_17 201703L
#define PRESSIO_CXX_STD_20 202002L
static_assert(_PRESSIO_CPLUSPLUS >= PRESSIO_CXX_STD_17, "PRESSIO requires C++17 or greater.");

// ----------------------------------------
// TPL macros
// ----------------------------------------
#if defined PRESSIO_ENABLE_TPL_TRILINOS
// if trilinos enabled, kokkos and MPI should be too
#if !defined PRESSIO_ENABLE_TPL_KOKKOS
#define PRESSIO_ENABLE_TPL_KOKKOS
#endif
#if !defined PRESSIO_ENABLE_TPL_MPI
#define PRESSIO_ENABLE_TPL_MPI
#endif
#endif

#endif
