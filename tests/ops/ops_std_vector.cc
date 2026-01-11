// @HEADER
// ************************************************************************
//
// ops_std_vector.cc
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
// @HEADER

#include <gtest/gtest.h>
#include <cmath>
#include <vector>

#include "pressio/ops.hpp"

using Vec = std::vector<double>;

TEST(ops_std_vector, clone)
{
  Vec a(6);
  for (std::size_t i = 0; i < a.size(); ++i) {
    a[i] = static_cast<double>(i);
  }

  auto b = pressio::ops::clone(a);
  ASSERT_EQ(b.size(), 6u);
  EXPECT_DOUBLE_EQ(b[0], 0.0);
  EXPECT_DOUBLE_EQ(a[0], 0.0);
  b[0] = 10.0;
  EXPECT_DOUBLE_EQ(a[0], 0.0);
}

TEST(ops_std_vector, extent)
{
  Vec x(6);
  EXPECT_EQ(pressio::ops::extent(x, 0), 6u);
  EXPECT_EQ(pressio::ops::extent(x, 1), 1u);
}

TEST(ops_std_vector, abs)
{
  Vec x(6);
  for (std::size_t i = 0; i < x.size(); ++i) {
    x[i] = -static_cast<double>(i);
  }

  Vec y(6);
  pressio::ops::abs(y, x);

  EXPECT_DOUBLE_EQ(y[0], 0.0);
  EXPECT_DOUBLE_EQ(y[1], 1.0);
  EXPECT_DOUBLE_EQ(y[2], 2.0);
  EXPECT_DOUBLE_EQ(y[3], 3.0);
  EXPECT_DOUBLE_EQ(y[4], 4.0);
  EXPECT_DOUBLE_EQ(y[5], 5.0);
}

TEST(ops_std_vector, scale)
{
  Vec a(6, 2.0);
  pressio::ops::scale(a, 3.0);
  for (const auto & value : a) {
    EXPECT_DOUBLE_EQ(value, 6.0);
  }

  pressio::ops::fill(a, std::nan("0"));
  pressio::ops::scale(a, 0.0);
  for (const auto & value : a) {
    EXPECT_DOUBLE_EQ(value, 0.0);
  }
}

TEST(ops_std_vector, setzero)
{
  Vec a(6, 11.0);
  pressio::ops::set_zero(a);
  for (const auto & value : a) {
    EXPECT_DOUBLE_EQ(value, 0.0);
  }
}

TEST(ops_std_vector, fill)
{
  Vec a(6);
  pressio::ops::fill(a, 44.88);
  for (const auto & value : a) {
    EXPECT_DOUBLE_EQ(value, 44.88);
  }
}

TEST(ops_std_vector, deep_copy)
{
  Vec a(6, 44.0);
  Vec b(6);
  pressio::ops::deep_copy(b, a);
  for (const auto & value : b) {
    EXPECT_DOUBLE_EQ(value, 44.0);
  }
}

TEST(ops_std_vector, min_max)
{
  Vec a = {100.0, 95.0, 90.0, 85.0, 80.0, 75.0};
  EXPECT_DOUBLE_EQ(pressio::ops::min(a), 75.0);
  EXPECT_DOUBLE_EQ(pressio::ops::max(a), 100.0);
}

TEST(ops_std_vector, norm1)
{
  Vec a(6);
  for (std::size_t i = 0; i < a.size(); ++i) {
    a[i] = static_cast<double>(i);
  }
  EXPECT_DOUBLE_EQ(pressio::ops::norm1(a), 15.0);
}

TEST(ops_std_vector, norm2)
{
  Vec a(6);
  for (std::size_t i = 0; i < a.size(); ++i) {
    a[i] = static_cast<double>(i);
  }
  EXPECT_DOUBLE_EQ(pressio::ops::norm2(a), 7.416198487095663);
}

TEST(ops_std_vector, dot)
{
  Vec a(6, 1.0);
  Vec b(6, 2.0);
  EXPECT_DOUBLE_EQ(pressio::ops::dot(a, b), 12.0);
  double result = 0.0;
  pressio::ops::dot(a, b, result);
  EXPECT_DOUBLE_EQ(result, 12.0);
}

TEST(ops_std_vector, pow)
{
  Vec a(6);
  for (std::size_t i = 0; i < a.size(); ++i) {
    a[i] = static_cast<double>(i);
  }
  pressio::ops::pow(a, 2.0);
  EXPECT_DOUBLE_EQ(a[0], 0.0);
  EXPECT_DOUBLE_EQ(a[1], 1.0);
  EXPECT_DOUBLE_EQ(a[2], 4.0);
  EXPECT_DOUBLE_EQ(a[3], 9.0);
  EXPECT_DOUBLE_EQ(a[4], 16.0);
  EXPECT_DOUBLE_EQ(a[5], 25.0);
}

TEST(ops_std_vector, absPowPos)
{
  Vec x(6);
  for (std::size_t i = 0; i < x.size(); ++i) {
    x[i] = -static_cast<double>(i);
  }
  Vec y(6);
  pressio::ops::abs_pow(y, x, 3.0);
  EXPECT_DOUBLE_EQ(y[0], 0.0);
  EXPECT_DOUBLE_EQ(y[1], 1.0);
  EXPECT_DOUBLE_EQ(y[2], 8.0);
  EXPECT_DOUBLE_EQ(y[3], 27.0);
  EXPECT_DOUBLE_EQ(y[4], 64.0);
  EXPECT_DOUBLE_EQ(y[5], 125.0);
}

TEST(ops_std_vector, absPowNeg)
{
  Vec x(6);
  for (std::size_t i = 0; i < x.size(); ++i) {
    x[i] = -static_cast<double>(i);
  }
  Vec y(6);
  pressio::ops::abs_pow(y, x, -3.0, 0.00001);
  EXPECT_DOUBLE_EQ(y[0], 1.0/0.00001);
  EXPECT_DOUBLE_EQ(y[1], 1.0);
  EXPECT_DOUBLE_EQ(y[2], 1.0/8.0);
  EXPECT_DOUBLE_EQ(y[3], 1.0/27.0);
  EXPECT_DOUBLE_EQ(y[4], 1.0/64.0);
  EXPECT_DOUBLE_EQ(y[5], 1.0/125.0);
}

TEST(ops_std_vector, elementwiseMultiply)
{
  Vec y = {1.0, 2.0, 3.0};
  Vec x = {2.0, 3.0, 4.0};
  Vec z = {3.0, 4.0, 5.0};

  pressio::ops::elementwise_multiply(1.0, x, z, 1.0, y);
  EXPECT_DOUBLE_EQ(y[0], 7.0);
  EXPECT_DOUBLE_EQ(y[1], 14.0);
  EXPECT_DOUBLE_EQ(y[2], 23.0);

  y[0] = std::nan("0");
  pressio::ops::elementwise_multiply(1.0, x, z, 0.0, y);
  EXPECT_DOUBLE_EQ(y[0], 6.0);
  EXPECT_DOUBLE_EQ(y[1], 12.0);
  EXPECT_DOUBLE_EQ(y[2], 20.0);
}

TEST(ops_std_vector, elementwiseReciprocal)
{
  Vec y = {0.0, 0.0, 0.0};
  Vec z = {3.0, 4.0, 5.0};

  pressio::ops::elementwise_reciprocal(z, y);
  EXPECT_DOUBLE_EQ(y[0], 1.0/3.0);
  EXPECT_DOUBLE_EQ(y[1], 1.0/4.0);
  EXPECT_DOUBLE_EQ(y[2], 1.0/5.0);
}
