
#include <gtest/gtest.h>
#include "pressio/ops.hpp"

using vec_t = Eigen::VectorXd;
using mat_t = Eigen::MatrixXd;

TEST(ops_eigen_diag, extent)
{
  mat_t a(5,5);
  auto ex = pressio::diagonal(a);
  ASSERT_TRUE(pressio::ops::extent(ex,0)==5);
  ASSERT_TRUE(pressio::ops::extent(ex,1)==1); // check extent over the rank
}

TEST(ops_eigen_diag, abs)
{
  mat_t a(5,5);
  a.setConstant(-1);
  auto ex = pressio::diagonal(a);

  vec_t y(5);
  pressio::ops::abs(y,ex);
  ASSERT_DOUBLE_EQ(y(0),1.);
  ASSERT_DOUBLE_EQ(y(1),1.);
  ASSERT_DOUBLE_EQ(y(2),1.);
  ASSERT_DOUBLE_EQ(y(3),1.);
  ASSERT_DOUBLE_EQ(y(4),1.);
}

TEST(ops_eigen_diag, scale)
{
  using T = Eigen::MatrixXd;
  T a(5,5);
  a.setConstant(1.);

  auto exp = pressio::diagonal(a);

  pressio::ops::scale(exp, 3.);
  ASSERT_DOUBLE_EQ(a(0,0),3.);
  ASSERT_DOUBLE_EQ(a(0,1),1.);
  ASSERT_DOUBLE_EQ(a(0,2),1.);
  ASSERT_DOUBLE_EQ(a(0,3),1.);
  ASSERT_DOUBLE_EQ(a(0,4),1.);

  ASSERT_DOUBLE_EQ(a(1,0),1.);
  ASSERT_DOUBLE_EQ(a(1,1),3.);
  ASSERT_DOUBLE_EQ(a(1,2),1.);
  ASSERT_DOUBLE_EQ(a(1,3),1.);
  ASSERT_DOUBLE_EQ(a(1,4),1.);

  ASSERT_DOUBLE_EQ(a(2,0),1.);
  ASSERT_DOUBLE_EQ(a(2,1),1.);
  ASSERT_DOUBLE_EQ(a(2,2),3.);
  ASSERT_DOUBLE_EQ(a(2,3),1.);
  ASSERT_DOUBLE_EQ(a(2,4),1.);

  ASSERT_DOUBLE_EQ(a(3,0),1.);
  ASSERT_DOUBLE_EQ(a(3,1),1.);
  ASSERT_DOUBLE_EQ(a(3,2),1.);
  ASSERT_DOUBLE_EQ(a(3,3),3.);
  ASSERT_DOUBLE_EQ(a(3,4),1.);

  ASSERT_DOUBLE_EQ(a(4,0),1.);
  ASSERT_DOUBLE_EQ(a(4,1),1.);
  ASSERT_DOUBLE_EQ(a(4,2),1.);
  ASSERT_DOUBLE_EQ(a(4,3),1.);
  ASSERT_DOUBLE_EQ(a(4,4),3.);
}

TEST(ops_eigen_diag, set_zero)
{
  using T = Eigen::MatrixXd;
  T a(5,5);
  a.setConstant(1.);

  auto exp = pressio::diagonal(a);

  pressio::ops::set_zero(exp);
  ASSERT_DOUBLE_EQ(a(0,0),0.);
  ASSERT_DOUBLE_EQ(a(0,1),1.);
  ASSERT_DOUBLE_EQ(a(0,2),1.);
  ASSERT_DOUBLE_EQ(a(0,3),1.);
  ASSERT_DOUBLE_EQ(a(0,4),1.);

  ASSERT_DOUBLE_EQ(a(1,0),1.);
  ASSERT_DOUBLE_EQ(a(1,1),0.);
  ASSERT_DOUBLE_EQ(a(1,2),1.);
  ASSERT_DOUBLE_EQ(a(1,3),1.);
  ASSERT_DOUBLE_EQ(a(1,4),1.);

  ASSERT_DOUBLE_EQ(a(2,0),1.);
  ASSERT_DOUBLE_EQ(a(2,1),1.);
  ASSERT_DOUBLE_EQ(a(2,2),0.);
  ASSERT_DOUBLE_EQ(a(2,3),1.);
  ASSERT_DOUBLE_EQ(a(2,4),1.);

  ASSERT_DOUBLE_EQ(a(3,0),1.);
  ASSERT_DOUBLE_EQ(a(3,1),1.);
  ASSERT_DOUBLE_EQ(a(3,2),1.);
  ASSERT_DOUBLE_EQ(a(3,3),0.);
  ASSERT_DOUBLE_EQ(a(3,4),1.);

  ASSERT_DOUBLE_EQ(a(4,0),1.);
  ASSERT_DOUBLE_EQ(a(4,1),1.);
  ASSERT_DOUBLE_EQ(a(4,2),1.);
  ASSERT_DOUBLE_EQ(a(4,3),1.);
  ASSERT_DOUBLE_EQ(a(4,4),0.);
}

TEST(ops_eigen_diag, fill)
{
  using T = Eigen::MatrixXd;
  T a(5,5);
  a.setConstant(1.);

  auto exp = pressio::diagonal(a);

  pressio::ops::fill(exp, 44.);
  ASSERT_DOUBLE_EQ(a(0,0),44.);
  ASSERT_DOUBLE_EQ(a(0,1),1.);
  ASSERT_DOUBLE_EQ(a(0,2),1.);
  ASSERT_DOUBLE_EQ(a(0,3),1.);
  ASSERT_DOUBLE_EQ(a(0,4),1.);

  ASSERT_DOUBLE_EQ(a(1,0),1.);
  ASSERT_DOUBLE_EQ(a(1,1),44.);
  ASSERT_DOUBLE_EQ(a(1,2),1.);
  ASSERT_DOUBLE_EQ(a(1,3),1.);
  ASSERT_DOUBLE_EQ(a(1,4),1.);

  ASSERT_DOUBLE_EQ(a(2,0),1.);
  ASSERT_DOUBLE_EQ(a(2,1),1.);
  ASSERT_DOUBLE_EQ(a(2,2),44.);
  ASSERT_DOUBLE_EQ(a(2,3),1.);
  ASSERT_DOUBLE_EQ(a(2,4),1.);

  ASSERT_DOUBLE_EQ(a(3,0),1.);
  ASSERT_DOUBLE_EQ(a(3,1),1.);
  ASSERT_DOUBLE_EQ(a(3,2),1.);
  ASSERT_DOUBLE_EQ(a(3,3),44.);
  ASSERT_DOUBLE_EQ(a(3,4),1.);

  ASSERT_DOUBLE_EQ(a(4,0),1.);
  ASSERT_DOUBLE_EQ(a(4,1),1.);
  ASSERT_DOUBLE_EQ(a(4,2),1.);
  ASSERT_DOUBLE_EQ(a(4,3),1.);
  ASSERT_DOUBLE_EQ(a(4,4),44.);
}

TEST(ops_eigen_diag, deep_copy)
{
  using T = Eigen::MatrixXd;
  T a(6, 6);
  auto exp = pressio::diagonal(a);
  ::pressio::ops::fill(exp, 44.);

  // copy to native vector
  Eigen::VectorXd b(6);
  pressio::ops::deep_copy(b, exp);
  for (int i = 0; i < 6; ++i){
    ASSERT_DOUBLE_EQ(b(i), 44.);
  }

  // copy to expression
  T a2(6, 6);
  auto exp2 = pressio::diagonal(a2);
  pressio::ops::deep_copy(exp2, exp);
  for (int i = 0; i < 6; ++i){
    ASSERT_DOUBLE_EQ(exp2(i), 44.);
  }
}

TEST(ops_eigen_diag, min_max)
{
  using T = Eigen::MatrixXd;
  T a(5,5);

  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a(i,j) = v;
    v+=1.;
   }
  }
  auto exp = pressio::diagonal(a);
  ASSERT_DOUBLE_EQ(pressio::ops::min(exp), 0.);
  ASSERT_DOUBLE_EQ(pressio::ops::max(exp), 24.);
}

TEST(ops_eigen_diag, norms)
{
  using T = Eigen::MatrixXd;
  T a(5,5);

  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a(i,j) = v;
    v+=1.;
   }
  }

  Eigen::VectorXd gold(5);
  gold << 0.,6.,12.,18.,24.;

  auto exp = pressio::diagonal(a);
  ASSERT_DOUBLE_EQ(pressio::ops::norm1(exp), gold.lpNorm<1>());
  ASSERT_DOUBLE_EQ(pressio::ops::norm2(exp), gold.lpNorm<2>());
}

TEST(ops_eigen_diag, dot_vector)
{
  using T = Eigen::MatrixXd;
  T a(5,5);

  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a(i,j) = v;
    v+=1.;
   }
  }

  Eigen::VectorXd b(5);
  b.setConstant(2.);

  auto exp = pressio::diagonal(a);
  ASSERT_DOUBLE_EQ(pressio::ops::dot(exp,b), 120.);
}

TEST(ops_eigen_diag, dot_diag)
{
  using T = Eigen::MatrixXd;
  T a(5,5);
  // 0,1,2,3,4
  // 5,6,7,8,9
  // 10,11,12,13,14
  // 15,16,17,18,19
  // 20,21,22,23,24
  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a(i,j) = v;
    v+=1.;
   }
  }

  Eigen::VectorXd gold(5);
  gold << 0.,6.,12.,18.,24.;

  auto exp = pressio::diagonal(a);
  ASSERT_DOUBLE_EQ(pressio::ops::dot(exp,exp),1080.);
}

TEST(ops_eigen_diag, pow)
{
  using T = Eigen::MatrixXd;
  T a(5,5);
  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a(i,j) = v;
    v+=1.;
   }
  }

  Eigen::VectorXd gold(5);
  gold << 0.,6.,12.,18.,24.;

  auto exp = pressio::diagonal(a);
  pressio::ops::pow(exp, 2.);

  for (int i=0; i<a.rows(); ++i){
    EXPECT_DOUBLE_EQ(exp(i), gold(i)*gold(i));
  }
}

namespace {
Eigen::MatrixXd createMatrixForUpdate(){
  Eigen::MatrixXd M(3,3);
  M(0,0) = 1.;
  M(1,1) = 2.;
  M(2,2) = 3.;
  return M;
}
}

TEST(ops_eigen_diag, update1)
{
  auto M1 = createMatrixForUpdate();
  auto d1 = pressio::diagonal(M1);
  auto M2 = createMatrixForUpdate();
  auto d2 = pressio::diagonal(M2);

  pressio::ops::update(d1, 1., d2, 1.);
  EXPECT_DOUBLE_EQ( d1(0), 2.0);
  EXPECT_DOUBLE_EQ( d1(1), 4.0);
  EXPECT_DOUBLE_EQ( d1(2), 6.0);

  pressio::ops::update(d1, 0., d2, 1.);
  EXPECT_DOUBLE_EQ( d1(0), 1.0);
  EXPECT_DOUBLE_EQ( d1(1), 2.0);
  EXPECT_DOUBLE_EQ( d1(2), 3.0);
}

// TEST(ops_eigen_diag, update2)
// {
//   auto M1 = createMatrixForUpdate();
//   auto v = pressio::diagonal(M1);
//   auto M2 = createMatrixForUpdate();
//   auto a = pressio::diagonal(M2);
//   auto M3 = createMatrixForUpdate();
//   auto b = pressio::diagonal(M3);

//   pressio::ops::update(v, 1., a, 1., b, 1.);
//   EXPECT_DOUBLE_EQ( v(0), 3.0);
//   EXPECT_DOUBLE_EQ( v(1), 6.0);
//   EXPECT_DOUBLE_EQ( v(2), 9.0);

//   pressio::ops::update(v, 0., a, 1., b, 1.);
//   EXPECT_DOUBLE_EQ( v(0), 2.0);
//   EXPECT_DOUBLE_EQ( v(1), 4.0);
//   EXPECT_DOUBLE_EQ( v(2), 6.0);
// }

// TEST(ops_eigen_diag, update3)
// {
//   auto M1 = createMatrixForUpdate();
//   auto v = pressio::diagonal(M1);
//   auto M2 = createMatrixForUpdate();
//   auto a = pressio::diagonal(M2);
//   auto M3 = createMatrixForUpdate();
//   auto b = pressio::diagonal(M3);
//   auto M4 = createMatrixForUpdate();
//   auto c = pressio::diagonal(M4);

//   pressio::ops::update(v, 1., a, 1., b, 1., c, 1.);
//   EXPECT_DOUBLE_EQ( v(0), 4.0);
//   EXPECT_DOUBLE_EQ( v(1), 8.0);
//   EXPECT_DOUBLE_EQ( v(2), 12.0);

//   pressio::ops::update(v, 0., a, 1., b, 1., c, 1.);
//   EXPECT_DOUBLE_EQ( v(0), 3.0);
//   EXPECT_DOUBLE_EQ( v(1), 6.0);
//   EXPECT_DOUBLE_EQ( v(2), 9.0);
// }

// TEST(ops_eigen_diag, update4)
// {
//   auto M1 = createMatrixForUpdate();
//   auto v = pressio::diagonal(M1);
//   auto M2 = createMatrixForUpdate();
//   auto a = pressio::diagonal(M2);
//   auto M3 = createMatrixForUpdate();
//   auto b = pressio::diagonal(M3);
//   auto M4 = createMatrixForUpdate();
//   auto c = pressio::diagonal(M4);
//   auto M5 = createMatrixForUpdate();
//   auto d = pressio::diagonal(M5);

//   pressio::ops::update(v, 1., a, 1., b, 1., c, 1., d, 1.);
//   EXPECT_DOUBLE_EQ( v(0), 5.0);
//   EXPECT_DOUBLE_EQ( v(1), 10.0);
//   EXPECT_DOUBLE_EQ( v(2), 15.0);

//   pressio::ops::update(v, 0., a, 1., b, 1., c, 1., d, 1.);
//   EXPECT_DOUBLE_EQ( v(0), 4.0);
//   EXPECT_DOUBLE_EQ( v(1), 8.0);
//   EXPECT_DOUBLE_EQ( v(2), 12.0);
// }

TEST(ops_eigen_diag, elementwiseMultiply)
{
  Eigen::MatrixXd M1(3,3);
  M1(0,0)=1.; M1(1,1)=2.; M1(2,2)=3.;
  auto y = pressio::diagonal(M1);

  Eigen::MatrixXd M2(3,3);
  M2(0,0)=2.; M2(1,1)=3.; M2(2,2)=4.;
  const auto x = pressio::diagonal(M2);

  Eigen::MatrixXd M3(3,3);
  M3(0,0)=3.; M3(1,1)=4.; M3(2,2)=5.;
  const auto z = pressio::diagonal(M3);

  pressio::ops::elementwise_multiply(1., x, z, 1., y);
  EXPECT_DOUBLE_EQ( y(0), 7.0);
  EXPECT_DOUBLE_EQ( y(1), 14.0);
  EXPECT_DOUBLE_EQ( y(2), 23.0);
}

TEST(ops_eigen_diag, elementwiseReciprocal)
{
  Eigen::MatrixXd M1(3,3);
  auto y = pressio::diagonal(M1);

  auto z0 = 3.;
  auto z1 = 4.;
  auto z2 = 5.;

  Eigen::MatrixXd M2(3,3);
  M2(0,0)=z0; M2(1,1)=z1; M2(2,2)=z2;
  const auto z = pressio::diagonal(M2);

  auto y0 = 1. / z0;
  auto y1 = 1. / z1;
  auto y2 = 1. / z2;

  pressio::ops::elementwise_reciprocal(z, y);
  EXPECT_DOUBLE_EQ( y(0), y0);
  EXPECT_DOUBLE_EQ( y(1), y1);
  EXPECT_DOUBLE_EQ( y(2), y2);
}
