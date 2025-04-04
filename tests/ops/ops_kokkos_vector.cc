
#include <gtest/gtest.h>
#include "pressio/ops.hpp"

namespace {

template<class T>
void fill1(T v)
{
  using sc_t = typename T::value_type;
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  for (int i=0; i<6; ++i){
   v_h(i) = (sc_t) i;
  }
}

template<class T>
void fill2(T v)
{
  using sc_t = typename T::value_type;
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  for (int i=0; i<6; ++i){
   v_h(i) = -(sc_t) i;
  }
}

template<class T>
void fill3(T v)
{
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  v_h(0) = 1.;
  v_h(1) = 2.;
  v_h(2) = 3.;
}
}//end namespace

TEST(ops_kokkos_vector, vector_clone)
{
  Kokkos::View<double*> a("a", 6);
  fill1(a);
  auto b = pressio::ops::clone(a);
  ASSERT_FALSE( b.data()==a.data());
  ASSERT_EQ(b.extent(0), 6);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  auto b_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), b);
  for (int i=0; i<6; ++i){
    ASSERT_DOUBLE_EQ(b_h(i),a_h(i));
  }
}

TEST(ops_kokkos_vector, vector_extent)
{
  Kokkos::View<double*> a("a", 6);
  ASSERT_TRUE(pressio::ops::extent(a,0)== 6);
  ASSERT_TRUE(pressio::ops::extent(a,1)== 1); // check extent over the rank
}

TEST(ops_kokkos_vector, vector_abs)
{
  Kokkos::View<double*> x("a", 6);
  fill2(x);

  Kokkos::View<double*> y("y",6);
  pressio::ops::abs(y,x);

  auto y_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), y);
  EXPECT_DOUBLE_EQ(y_h(0), 0.);
  EXPECT_DOUBLE_EQ(y_h(1), 1.);
  EXPECT_DOUBLE_EQ(y_h(2), 2.);
  EXPECT_DOUBLE_EQ(y_h(3), 3.);
  EXPECT_DOUBLE_EQ(y_h(4), 4.);
  EXPECT_DOUBLE_EQ(y_h(5), 5.);
}

TEST(ops_kokkos_vector, vector_setzero)
{
  Kokkos::View<double*> x("a", 6);
  fill1(x);

  pressio::ops::set_zero(x);
  auto x_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), x);
  for (int i=0; i<6; ++i){
    ASSERT_DOUBLE_EQ(x_h(i),0.);
  }
}

TEST(ops_kokkos_vector, vector_scale)
{
  Kokkos::View<double*> x("a", 6);
  fill1(x);

  pressio::ops::scale(x, 2.);
  auto x_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), x);
  EXPECT_DOUBLE_EQ(x_h(0), 0.);
  EXPECT_DOUBLE_EQ(x_h(1), 2.);
  EXPECT_DOUBLE_EQ(x_h(2), 4.);
  EXPECT_DOUBLE_EQ(x_h(3), 6.);
  EXPECT_DOUBLE_EQ(x_h(4), 8.);
  EXPECT_DOUBLE_EQ(x_h(5), 10.);

  // check NaN injection with zero scaling
  ::pressio::ops::fill(x, std::nan("0"));
  pressio::ops::scale(x, 0.);
  x_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), x);
  EXPECT_DOUBLE_EQ(x_h(0), 0.);
  EXPECT_DOUBLE_EQ(x_h(1), 0.);
  EXPECT_DOUBLE_EQ(x_h(2), 0.);
  EXPECT_DOUBLE_EQ(x_h(3), 0.);
  EXPECT_DOUBLE_EQ(x_h(4), 0.);
  EXPECT_DOUBLE_EQ(x_h(5), 0.);
}

TEST(ops_kokkos_vector, vector_fill)
{
  Kokkos::View<double*> x("a", 6);
  pressio::ops::fill(x, 44.44);
  auto x_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), x);
  EXPECT_DOUBLE_EQ(x_h(0), 44.44);
  EXPECT_DOUBLE_EQ(x_h(1), 44.44);
  EXPECT_DOUBLE_EQ(x_h(2), 44.44);
  EXPECT_DOUBLE_EQ(x_h(3), 44.44);
  EXPECT_DOUBLE_EQ(x_h(4), 44.44);
  EXPECT_DOUBLE_EQ(x_h(5), 44.44);
}

TEST(ops_kokkos_vector, vector_resize)
{
  Kokkos::View<double*> x("a", 6);
  pressio::ops::resize(x,3);
  ASSERT_EQ(x.extent(0), 3);
}

TEST(ops_kokkos_vector, vector_deep_copy)
{
  Kokkos::View<double*> x("a", 6);
  pressio::ops::fill(x, 44.);

  Kokkos::View<double*> b("b", 6);
  pressio::ops::deep_copy(b,x);
  auto b_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), b);
  for (int i=0; i<6; ++i){
    ASSERT_DOUBLE_EQ(b(i),44.);
  }
}

TEST(ops_kokkos_vector, vector_min_max)
{
  Kokkos::View<double*> x("x", 6);
  auto x_h = Kokkos::create_mirror_view(Kokkos::HostSpace(), x);
  for (int i = 0; i < 6; ++i) {
    x_h(i) = 100 - i * 5;
  }
  Kokkos::deep_copy(x, x_h);

  ASSERT_DOUBLE_EQ(pressio::ops::min(x), 75.);
  ASSERT_DOUBLE_EQ(pressio::ops::max(x), 100.);
}

TEST(ops_kokkos_vector, vector_norm1)
{
  Kokkos::View<double*> x("a", 6);
  fill1(x);
  ASSERT_DOUBLE_EQ(pressio::ops::norm1(x), 15);
}

TEST(ops_kokkos_vector, vector_norm2)
{
  Kokkos::View<double*> x("a", 6);
  fill1(x);
  ASSERT_DOUBLE_EQ(pressio::ops::norm2(x), 7.416198487095663);
}

TEST(ops_kokkos_vector, vector_dot)
{
  Kokkos::View<double*> a("a", 6);
  pressio::ops::fill(a, 1.);
  Kokkos::View<double*> b("b", 6);
  pressio::ops::fill(b, 2.);
  ASSERT_DOUBLE_EQ(pressio::ops::dot(a,b), 12.);
  double result;
  pressio::ops::dot(a,b,result);
  ASSERT_DOUBLE_EQ(result,12.);
}

TEST(ops_kokkos_vector, vector_pow)
{
  Kokkos::View<double*> a("a", 6);
  fill1(a);

  ::pressio::ops::pow(a, 2.);
  auto a_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), a);
  EXPECT_DOUBLE_EQ(a_h(0), 0.);
  EXPECT_DOUBLE_EQ(a_h(1), 1.);
  EXPECT_DOUBLE_EQ(a_h(2), 4.);
  EXPECT_DOUBLE_EQ(a_h(3), 9.);
  EXPECT_DOUBLE_EQ(a_h(4), 16.);
  EXPECT_DOUBLE_EQ(a_h(5), 25.);
}

TEST(ops_kokkos_vector, vector_absPowPos)
{
  Kokkos::View<double*> x("x", 6);
  fill2(x);

  Kokkos::View<double*> y("y", 6);
  ::pressio::ops::abs_pow(y, x, 3.);

  auto y_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), y);
  EXPECT_DOUBLE_EQ(y_h(0), 0.);
  EXPECT_DOUBLE_EQ(y_h(1), 1.);
  EXPECT_DOUBLE_EQ(y_h(2), 8.);
  EXPECT_DOUBLE_EQ(y_h(3), 27.);
  EXPECT_DOUBLE_EQ(y_h(4), 64.);
  EXPECT_DOUBLE_EQ(y_h(5), 125.);
}

TEST(ops_kokkos_vector, vector_absPowNeg)
{
  Kokkos::View<double*> x("x", 6);
  fill2(x);
  Kokkos::View<double*> y("y", 6);
  ::pressio::ops::abs_pow(y, x, -3., 0.00001);

  auto y_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), y);
  EXPECT_DOUBLE_EQ(y_h(0), 1./0.00001); // because we guard against diving by zero0.);
  EXPECT_DOUBLE_EQ(y_h(1), 1.);
  EXPECT_DOUBLE_EQ(y_h(2), 1./8.);
  EXPECT_DOUBLE_EQ(y_h(3), 1./27.);
  EXPECT_DOUBLE_EQ(y_h(4), 1./64.);
  EXPECT_DOUBLE_EQ(y_h(5), 1./125.);
}

TEST(ops_kokkos_vector, vector_update1)
{
  Kokkos::View<double*> v("v", 3);
  Kokkos::View<double*> a("a", 3);
  fill3(v);
  fill3(a);

  pressio::ops::update(v, 1., a, 1.);
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ( v_h(0), 2.0);
  EXPECT_DOUBLE_EQ( v_h(1), 4.0);
  EXPECT_DOUBLE_EQ( v_h(2), 6.0);

  pressio::ops::update(v, 0., a, 1.);
  auto v_h2 = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ( v_h2(0), 1.0);
  EXPECT_DOUBLE_EQ( v_h2(1), 2.0);
  EXPECT_DOUBLE_EQ( v_h2(2), 3.0);
}

TEST(ops_kokkos_vector, vector_update2)
{
  Kokkos::View<double*> v("v", 3);
  Kokkos::View<double*> a("a", 3);
  Kokkos::View<double*> b("b", 3);
  fill3(v);
  fill3(a);
  fill3(b);

  pressio::ops::update(v, 1., a, 1., b, 1.);
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ( v_h(0), 3.0);
  EXPECT_DOUBLE_EQ( v_h(1), 6.0);
  EXPECT_DOUBLE_EQ( v_h(2), 9.0);

  pressio::ops::update(v, 0., a, 1., b, 1.);
  auto v_h2 = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ( v_h2(0), 2.0);
  EXPECT_DOUBLE_EQ( v_h2(1), 4.0);
  EXPECT_DOUBLE_EQ( v_h2(2), 6.0);
}

TEST(ops_kokkos_vector, vector_update3)
{
  Kokkos::View<double*> v("v", 3);
  Kokkos::View<double*> a("a", 3);
  Kokkos::View<double*> b("b", 3);
  Kokkos::View<double*> c("b", 3);
  fill3(v);
  fill3(a);
  fill3(b);
  fill3(c);

  pressio::ops::update(v, 1., a, 1., b, 1., c, 1.);
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ( v_h(0), 4.0);
  EXPECT_DOUBLE_EQ( v_h(1), 8.0);
  EXPECT_DOUBLE_EQ( v_h(2), 12.0);

  pressio::ops::update(v, 0., a, 1., b, 1., c, 1.);
  auto v_h2 = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ( v_h2(0), 3.0);
  EXPECT_DOUBLE_EQ( v_h2(1), 6.0);
  EXPECT_DOUBLE_EQ( v_h2(2), 9.0);
}

TEST(ops_kokkos_vector, vector_update4)
{
  Kokkos::View<double*> v("v", 3);
  Kokkos::View<double*> a("a", 3);
  Kokkos::View<double*> b("b", 3);
  Kokkos::View<double*> c("b", 3);
  Kokkos::View<double*> d("b", 3);
  fill3(v);
  fill3(a);
  fill3(b);
  fill3(c);
  fill3(d);

  pressio::ops::update(v, 1., a, 1., b, 1., c, 1., d, 1.);
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ( v_h(0), 5.0);
  EXPECT_DOUBLE_EQ( v_h(1), 10.0);
  EXPECT_DOUBLE_EQ( v_h(2), 15.0);

  pressio::ops::update(v, 0., a, 1., b, 1., c, 1., d, 1.);
  auto v_h2 = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ( v_h2(0), 4.0);
  EXPECT_DOUBLE_EQ( v_h2(1), 8.0);
  EXPECT_DOUBLE_EQ( v_h2(2), 12.0);
}

TEST(ops_kokkos_vector, vector_update_nan1)
{
  Kokkos::View<double*> v("v", 3);
  Kokkos::View<double*> a("a", 3);
  Kokkos::View<double*> vecOfNans("nan", 3);
  pressio::ops::fill(v, 1.);
  pressio::ops::fill(a, 1.);
  pressio::ops::fill(vecOfNans, std::nan("0"));

  // Note: this test covers just enough nan/non-nan combinations
  // to trigger and verify all execution paths in our update()
  // implementations, which include anti-NaN-injection variants
  pressio::ops::update(v, 1., vecOfNans, 0.);
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 1.0);

  pressio::ops::update(v, 1., vecOfNans, 0., vecOfNans, 0.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 1.0);
  pressio::ops::update(v, 1., a, 1., vecOfNans, 0.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 2.);

  pressio::ops::update(v, 1., vecOfNans, 0., vecOfNans, 0., vecOfNans, 0.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 2.0);
  pressio::ops::update(v, 1., a, 1., vecOfNans, 0., a, 1.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 4.);
  pressio::ops::update(v, 1., a, 1., a, 1., vecOfNans, 0.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 6.);

  pressio::ops::update(v, 1., vecOfNans, 0., vecOfNans, 0., vecOfNans, 0., vecOfNans, 0.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 6.0);
  pressio::ops::update(v, 1., a, 1., vecOfNans, 0., a, 1., a, 1.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 9.);
  pressio::ops::update(v, 1., a, 1., a, 1., vecOfNans, 0., a, 1.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 12.);
  pressio::ops::update(v, 1., a, 1., a, 1., a, 1., vecOfNans, 0.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 15.);
}

// injects NaN through the updated vector
TEST(ops_kokkos_vector, vector_update_nan2)
{
  const auto nan = std::nan("0");
  Kokkos::View<double*> v("v", 3);
  Kokkos::View<double*> a("a", 3);
  pressio::ops::fill(a, 1.);

  pressio::ops::fill(v, nan);
  pressio::ops::update(v, 0., a, 1.);
  auto v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 1.0);

  pressio::ops::fill(v, nan);
  pressio::ops::update(v, 0., a, 0.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 0.0);

  pressio::ops::fill(v, nan);
  pressio::ops::update(v, 0., a, 1., a, 1.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 2.0);

  pressio::ops::fill(v, nan);
  pressio::ops::update(v, 0., a, 1., a, 1., a, 1.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 3.0);

  pressio::ops::fill(v, nan);
  pressio::ops::update(v, 0., a, 1., a, 1., a, 1., a, 1.);
  v_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), v);
  EXPECT_DOUBLE_EQ(v_h(0), 4.0);
}

TEST(ops_kokkos_vector, vector_update_expr_span)
{
  Kokkos::View<double*> v0("v_span", 5);
  Kokkos::View<double*> a0("a_span", 5);
  auto v = pressio::span(v0, 1, 3);
  auto a = pressio::span(a0, 1, 3);
  pressio::ops::fill(v, 10.);
  pressio::ops::fill(a, 1.);

  pressio::ops::update(v, 1., a, 1.);
  pressio::ops::update(v, 1., a, 1., a, 2.);
  pressio::ops::update(v, 1., a, 1., a, 2., a, 3.);
  pressio::ops::update(v, 1., a, 1., a, 2., a, 3., a, 4.);

  // Note: just check the final result as this test is more about
  //       whether expressions compile and work than computation itself
  auto v_h = Kokkos::create_mirror_view_and_copy(
                Kokkos::HostSpace(), pressio::ops::impl::get_native(v));
  EXPECT_DOUBLE_EQ( v_h(0), 30.0);
  EXPECT_DOUBLE_EQ( v_h(1), 30.0);
  EXPECT_DOUBLE_EQ( v_h(2), 30.0);
}

TEST(ops_kokkos_vector, vector_update_expr_diag)
{
  Kokkos::View<double**> v0("v_diag", 3, 3);
  Kokkos::View<double**> a0("a_diag", 3, 3);
  auto v = pressio::diagonal(v0);
  auto a = pressio::diagonal(a0);
  pressio::ops::fill(v, 10.);
  pressio::ops::fill(a, 1.);

  pressio::ops::update(v, 1., a, 1.);
  pressio::ops::update(v, 1., a, 1., a, 2.);
  pressio::ops::update(v, 1., a, 1., a, 2., a, 3.);
  pressio::ops::update(v, 1., a, 1., a, 2., a, 3., a, 4.);

  // Note: just check the final result as this test is more about
  //       whether expressions compile and work than computation itself
  auto v_h = Kokkos::create_mirror_view_and_copy(
                Kokkos::HostSpace(), pressio::ops::impl::get_native(v));
  EXPECT_DOUBLE_EQ( v_h(0), 30.0);
  EXPECT_DOUBLE_EQ( v_h(1), 30.0);
  EXPECT_DOUBLE_EQ( v_h(2), 30.0);
}

TEST(ops_kokkos_vector, vector_elementwiseMultiply)
{
  Kokkos::View<double*> y("y", 3);
  Kokkos::View<double*> x("x", 3);
  Kokkos::View<double*> z("z", 3);
  auto y_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), y);
  auto x_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), x);
  auto z_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), z);
  y_h(0) = 1.; y_h(1) = 2.; y_h(2) = 3.;
  x_h(0) = 2.; x_h(1) = 3.; x_h(2) = 4.;
  z_h(0) = 3.; z_h(1) = 4.; z_h(2) = 5.;

  Kokkos::deep_copy(y, y_h);
  Kokkos::deep_copy(x, x_h);
  Kokkos::deep_copy(z, z_h);

  pressio::ops::elementwise_multiply(1., x, z, 1., y);
  Kokkos::deep_copy(y_h, y);
  EXPECT_DOUBLE_EQ( y_h(0), 7.0);
  EXPECT_DOUBLE_EQ( y_h(1), 14.0);
  EXPECT_DOUBLE_EQ( y_h(2), 23.0);

  // test beta=0 with simulated NaN in uninitialized y
  Kokkos::deep_copy(y, std::nan("0"));
  pressio::ops::elementwise_multiply(1., x, z, 0., y);
  Kokkos::deep_copy(y_h, y);
  EXPECT_DOUBLE_EQ( y_h(0), 6.0);
  EXPECT_DOUBLE_EQ( y_h(1), 12.0);
  EXPECT_DOUBLE_EQ( y_h(2), 20.0);
}

TEST(ops_kokkos_vector, vector_elementwiseReciprocal)
{
  Kokkos::View<double*> y("y", 3);
  Kokkos::View<double*> z("z", 3);

  const auto z0 = 3.;
  const auto z1 = 4.;
  const auto z2 = 5.;

  auto y_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), y);
  auto z_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), z);
  z_h(0) = z0; z_h(1) = z1; z_h(2) = z2;

  Kokkos::deep_copy(y, y_h);
  Kokkos::deep_copy(z, z_h);

  pressio::ops::elementwise_reciprocal(z, y);
  Kokkos::deep_copy(y_h, y);
  EXPECT_DOUBLE_EQ( y_h(0), 1 / z0);
  EXPECT_DOUBLE_EQ( y_h(1), 1 / z1);
  EXPECT_DOUBLE_EQ( y_h(2), 1 / z2);
}
