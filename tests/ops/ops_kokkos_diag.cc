
#include <gtest/gtest.h>
#include "pressio/ops.hpp"

using vec_t = Kokkos::View<double*>;
using mat_t = Kokkos::View<double**>;

TEST(ops_kokkos_diag, extent)
{
  mat_t a("a", 5,5);
  auto ex = pressio::diagonal(a);
  ASSERT_TRUE(pressio::ops::extent(ex,0)==5);
  ASSERT_TRUE(pressio::ops::extent(ex,1)==1); // check extent over the rank
}

TEST(ops_kokkos_diag, abs)
{
  mat_t a("a",5,5);
  KokkosBlas::fill(a, -1.);
  auto ex = pressio::diagonal(a);
  vec_t y("y", 5);
  pressio::ops::abs(y,ex);

  auto y_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), y);
  ASSERT_DOUBLE_EQ(y_h(0),1.);
  ASSERT_DOUBLE_EQ(y_h(1),1.);
  ASSERT_DOUBLE_EQ(y_h(2),1.);
  ASSERT_DOUBLE_EQ(y_h(3),1.);
  ASSERT_DOUBLE_EQ(y_h(4),1.);
}

TEST(ops_kokkos_diag, scale)
{
  mat_t a("a",5,5);
  KokkosBlas::fill(a, 1.);
  auto exp = pressio::diagonal(a);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  pressio::ops::scale(exp, 3.);
  ASSERT_DOUBLE_EQ(a_h(0,0),3.);
  ASSERT_DOUBLE_EQ(a_h(0,1),1.);
  ASSERT_DOUBLE_EQ(a_h(0,2),1.);
  ASSERT_DOUBLE_EQ(a_h(0,3),1.);
  ASSERT_DOUBLE_EQ(a_h(0,4),1.);
  ASSERT_DOUBLE_EQ(a_h(1,0),1.);
  ASSERT_DOUBLE_EQ(a_h(1,1),3.);
  ASSERT_DOUBLE_EQ(a_h(1,2),1.);
  ASSERT_DOUBLE_EQ(a_h(1,3),1.);
  ASSERT_DOUBLE_EQ(a_h(1,4),1.);
  ASSERT_DOUBLE_EQ(a_h(2,0),1.);
  ASSERT_DOUBLE_EQ(a_h(2,1),1.);
  ASSERT_DOUBLE_EQ(a_h(2,2),3.);
  ASSERT_DOUBLE_EQ(a_h(2,3),1.);
  ASSERT_DOUBLE_EQ(a_h(2,4),1.);
  ASSERT_DOUBLE_EQ(a_h(3,0),1.);
  ASSERT_DOUBLE_EQ(a_h(3,1),1.);
  ASSERT_DOUBLE_EQ(a_h(3,2),1.);
  ASSERT_DOUBLE_EQ(a_h(3,3),3.);
  ASSERT_DOUBLE_EQ(a_h(3,4),1.);
  ASSERT_DOUBLE_EQ(a_h(4,0),1.);
  ASSERT_DOUBLE_EQ(a_h(4,1),1.);
  ASSERT_DOUBLE_EQ(a_h(4,2),1.);
  ASSERT_DOUBLE_EQ(a_h(4,3),1.);
  ASSERT_DOUBLE_EQ(a_h(4,4),3.);
}

TEST(ops_kokkos_diag, set_zero)
{
  mat_t a("a",5,5);
  KokkosBlas::fill(a, 1.);
  auto exp = pressio::diagonal(a);
  pressio::ops::set_zero(exp);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  ASSERT_DOUBLE_EQ(a_h(0,0),0.);
  ASSERT_DOUBLE_EQ(a_h(0,1),1.);
  ASSERT_DOUBLE_EQ(a_h(0,2),1.);
  ASSERT_DOUBLE_EQ(a_h(0,3),1.);
  ASSERT_DOUBLE_EQ(a_h(0,4),1.);
  ASSERT_DOUBLE_EQ(a_h(1,0),1.);
  ASSERT_DOUBLE_EQ(a_h(1,1),0.);
  ASSERT_DOUBLE_EQ(a_h(1,2),1.);
  ASSERT_DOUBLE_EQ(a_h(1,3),1.);
  ASSERT_DOUBLE_EQ(a_h(1,4),1.);
  ASSERT_DOUBLE_EQ(a_h(2,0),1.);
  ASSERT_DOUBLE_EQ(a_h(2,1),1.);
  ASSERT_DOUBLE_EQ(a_h(2,2),0.);
  ASSERT_DOUBLE_EQ(a_h(2,3),1.);
  ASSERT_DOUBLE_EQ(a_h(2,4),1.);
  ASSERT_DOUBLE_EQ(a_h(3,0),1.);
  ASSERT_DOUBLE_EQ(a_h(3,1),1.);
  ASSERT_DOUBLE_EQ(a_h(3,2),1.);
  ASSERT_DOUBLE_EQ(a_h(3,3),0.);
  ASSERT_DOUBLE_EQ(a_h(3,4),1.);
  ASSERT_DOUBLE_EQ(a_h(4,0),1.);
  ASSERT_DOUBLE_EQ(a_h(4,1),1.);
  ASSERT_DOUBLE_EQ(a_h(4,2),1.);
  ASSERT_DOUBLE_EQ(a_h(4,3),1.);
  ASSERT_DOUBLE_EQ(a_h(4,4),0.);
}

TEST(ops_kokkos_diag, fill)
{
  mat_t a("a",5,5);
  KokkosBlas::fill(a, 1.);
  auto exp = pressio::diagonal(a);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  pressio::ops::fill(exp, 44.);
  ASSERT_DOUBLE_EQ(a_h(0,0),44.);
  ASSERT_DOUBLE_EQ(a_h(0,1),1.);
  ASSERT_DOUBLE_EQ(a_h(0,2),1.);
  ASSERT_DOUBLE_EQ(a_h(0,3),1.);
  ASSERT_DOUBLE_EQ(a_h(0,4),1.);
  ASSERT_DOUBLE_EQ(a_h(1,0),1.);
  ASSERT_DOUBLE_EQ(a_h(1,1),44.);
  ASSERT_DOUBLE_EQ(a_h(1,2),1.);
  ASSERT_DOUBLE_EQ(a_h(1,3),1.);
  ASSERT_DOUBLE_EQ(a_h(1,4),1.);
  ASSERT_DOUBLE_EQ(a_h(2,0),1.);
  ASSERT_DOUBLE_EQ(a_h(2,1),1.);
  ASSERT_DOUBLE_EQ(a_h(2,2),44.);
  ASSERT_DOUBLE_EQ(a_h(2,3),1.);
  ASSERT_DOUBLE_EQ(a_h(2,4),1.);
  ASSERT_DOUBLE_EQ(a_h(3,0),1.);
  ASSERT_DOUBLE_EQ(a_h(3,1),1.);
  ASSERT_DOUBLE_EQ(a_h(3,2),1.);
  ASSERT_DOUBLE_EQ(a_h(3,3),44.);
  ASSERT_DOUBLE_EQ(a_h(3,4),1.);
  ASSERT_DOUBLE_EQ(a_h(4,0),1.);
  ASSERT_DOUBLE_EQ(a_h(4,1),1.);
  ASSERT_DOUBLE_EQ(a_h(4,2),1.);
  ASSERT_DOUBLE_EQ(a_h(4,3),1.);
  ASSERT_DOUBLE_EQ(a_h(4,4),44.);
}

TEST(ops_kokkos_diag, deep_copy)
{
  mat_t a("a", 6, 6);
  auto exp = pressio::diagonal(a);
  pressio::ops::fill(exp, 44.);

  Kokkos::View<double*> b("b", 6);
  pressio::ops::deep_copy(b, exp);
  auto b_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), b);
  for (int i = 0; i < 6; ++i){
    ASSERT_DOUBLE_EQ(b(i), 44.);
  }
}

TEST(ops_kokkos_diag, min_max)
{
  mat_t A("A", 5, 5);
  auto A_h = Kokkos::create_mirror_view(Kokkos::HostSpace(), A);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      A_h(i, j) = 100 - i * 5 - j;
    }
  }
  Kokkos::deep_copy(A, A_h);
  auto d = pressio::diagonal(A_h);
  ASSERT_DOUBLE_EQ(pressio::ops::min(d), 76.);
  ASSERT_DOUBLE_EQ(pressio::ops::max(d), 100.);
}

TEST(ops_kokkos_diag, norms)
{
  mat_t a("a",5,5);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a_h(i,j) = v;
    v+=1.;
   }
  }
  Kokkos::deep_copy(a, a_h);

  std::vector<double> gold = {0.,6.,12.,18.,24.};
  double l1norm = 0;
  double l2norm = 0;
  std::for_each(gold.begin(), gold.end(), [&](double v){
    l1norm += std::abs(v);
    l2norm += v*v;
  });
  l2norm = std::sqrt(l2norm);

  auto e = pressio::diagonal(a);
  ASSERT_DOUBLE_EQ(pressio::ops::norm1(e), l1norm);
  ASSERT_DOUBLE_EQ(pressio::ops::norm2(e), l2norm);
}

TEST(ops_kokkos_diag, dot_vector)
{
  mat_t a("a",5,5);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a_h(i,j) = v;
    v+=1.;
   }
  }
  Kokkos::deep_copy(a, a_h);

  vec_t b("b", 5);
  KokkosBlas::fill(b,2.);

  auto exp = pressio::diagonal(a);
  ASSERT_DOUBLE_EQ(pressio::ops::dot(exp,b), 120.);
}

TEST(ops_kokkos_diag, dot_diag)
{
  // 0,1,2,3,4
  // 5,6,7,8,9
  // 10,11,12,13,14
  // 15,16,17,18,19
  // 20,21,22,23,24
  mat_t a("a",5,5);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a_h(i,j) = v;
    v+=1.;
   }
  }
  Kokkos::deep_copy(a, a_h);

  auto exp = pressio::diagonal(a);
  ASSERT_DOUBLE_EQ(pressio::ops::dot(exp,exp), 1080.);
}

TEST(ops_kokkos_diag, pow)
{
  mat_t a("a",5,5);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  double v = 0;
  for (int i=0; i<5; ++i){
   for (int j=0; j<5; ++j){
    a_h(i,j) = v;
    v+=1.;
   }
  }
  Kokkos::deep_copy(a, a_h);

  auto exp = pressio::diagonal(a);
  pressio::ops::pow(exp, 2.);

  Kokkos::deep_copy(a,a_h);
  EXPECT_DOUBLE_EQ(a_h(0,0), 0);
  EXPECT_DOUBLE_EQ(a_h(1,1), 6.*6.);
  EXPECT_DOUBLE_EQ(a_h(2,2), 12*12.);
  EXPECT_DOUBLE_EQ(a_h(3,3), 18*18.);
  EXPECT_DOUBLE_EQ(a_h(4,4), 24.*24.);
}

namespace {
mat_t createMatrixForUpdate(){
  mat_t M("M", 3,3);
  auto M_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M);
  M_h(0,0) = 1.;
  M_h(1,1) = 2.;
  M_h(2,2) = 3.;
  Kokkos::deep_copy(M, M_h);
  return M;
}
}

TEST(ops_kokkos_diag, update1)
{
  auto M1 = createMatrixForUpdate();
  auto d1 = pressio::diagonal(M1);
  auto M2 = createMatrixForUpdate();
  auto d2 = pressio::diagonal(M2);

  pressio::ops::update(d1, 1., d2, 1.);
  auto M1_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 2.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 4.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 6.0);

  pressio::ops::update(d1, 0., d2, 1.);
  Kokkos::deep_copy(M1_h, M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 1.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 2.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 3.0);
}

TEST(ops_kokkos_diag, update2)
{
  auto M1 = createMatrixForUpdate();
  auto v = pressio::diagonal(M1);
  auto M2 = createMatrixForUpdate();
  auto a = pressio::diagonal(M2);
  auto M3 = createMatrixForUpdate();
  auto b = pressio::diagonal(M3);

  pressio::ops::update(v, 1., a, 1., b, 1.);
  auto M1_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 3.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 6.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 9.0);

  pressio::ops::update(v, 0.,  a, 1., b, 1.);
  Kokkos::deep_copy(M1_h, M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 2.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 4.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 6.0);
}

TEST(ops_kokkos_diag, update3)
{
  auto M1 = createMatrixForUpdate();
  auto v = pressio::diagonal(M1);
  auto M2 = createMatrixForUpdate();
  auto a = pressio::diagonal(M2);
  auto M3 = createMatrixForUpdate();
  auto b = pressio::diagonal(M3);
  auto M4 = createMatrixForUpdate();
  auto c = pressio::diagonal(M4);

  pressio::ops::update(v, 1., a, 1., b, 1., c, 1.);
  auto M1_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 4.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 8.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 12.0);

  pressio::ops::update(v, 0., a, 1., b, 1., c, 1.);
  Kokkos::deep_copy(M1_h, M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 3.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 6.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 9.0);
}

TEST(ops_kokkos_diag, update4)
{
  auto M1 = createMatrixForUpdate();
  auto v = pressio::diagonal(M1);
  auto M2 = createMatrixForUpdate();
  auto a = pressio::diagonal(M2);
  auto M3 = createMatrixForUpdate();
  auto b = pressio::diagonal(M3);
  auto M4 = createMatrixForUpdate();
  auto c = pressio::diagonal(M4);
  auto M5 = createMatrixForUpdate();
  auto d = pressio::diagonal(M5);

  pressio::ops::update(v, 1., a, 1., b, 1., c, 1., d, 1.);
  auto M1_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 5.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 10.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 15.0);

  pressio::ops::update(v, 0., a, 1., b, 1., c, 1., d, 1.);
  Kokkos::deep_copy(M1_h, M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 4.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 8.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 12.0);
}

TEST(ops_kokkos_diag, elementwiseMultiply)
{
  mat_t M1("M1",3,3);
  mat_t M2("M2",3,3);
  mat_t M3("M3",3,3);
  auto M1_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M1);
  auto M2_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M2);
  auto M3_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M3);

  M1_h(0,0)=1.; M1_h(1,1)=2.; M1_h(2,2)=3.;
  M2_h(0,0)=2.; M2_h(1,1)=3.; M2_h(2,2)=4.;
  M3_h(0,0)=3.; M3_h(1,1)=4.; M3_h(2,2)=5.;
  Kokkos::deep_copy(M1, M1_h);
  Kokkos::deep_copy(M2, M2_h);
  Kokkos::deep_copy(M3, M3_h);

  auto y = pressio::diagonal(M1);
  const auto x = pressio::diagonal(M2);
  const auto z = pressio::diagonal(M3);

  pressio::ops::elementwise_multiply(1., x, z, 1., y);
  Kokkos::deep_copy(M1_h, M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 7.0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 14.0);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 23.0);
}


TEST(ops_kokkos_diag, elementwiseReciprocal)
{
  mat_t M1("M1",3,3);
  mat_t M3("M3",3,3);

  const auto z0 = 3.;
  const auto z1 = 4.;
  const auto z2 = 5.;

  auto M1_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M1);
  auto M3_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), M3);
  M3_h(0,0)=z0; M3_h(1,1)=z1; M3_h(2,2)=z2;

  Kokkos::deep_copy(M1, M1_h);
  Kokkos::deep_copy(M3, M3_h);

  auto y = pressio::diagonal(M1);
  const auto z = pressio::diagonal(M3);

  pressio::ops::elementwise_reciprocal(z, y);
  Kokkos::deep_copy(M1_h, M1);
  EXPECT_DOUBLE_EQ( M1_h(0,0), 1 / z0);
  EXPECT_DOUBLE_EQ( M1_h(1,1), 1 / z1);
  EXPECT_DOUBLE_EQ( M1_h(2,2), 1 / z2);
}
