
#include <gtest/gtest.h>
#include "pressio/ops.hpp"
#include "ops_shared_level2.hpp"

#include <Kokkos_Core.hpp>

//-------------------------------------------
// Test implementation
//-------------------------------------------

struct kokkosFixture
  : public ::testing::Test {

  const double          NaN    = std::nan("0");
  static constexpr auto alpha0 = ::pressio::Constants<double>::zero();
  static constexpr auto alpha1 = ::pressio::Constants<double>::one();
  static constexpr auto beta0  = alpha0;
  static constexpr auto beta1  = alpha1;
  static constexpr auto one    = ::pressio::Constants<size_t>::one();

  const size_t x_size = 3;
  const size_t y_size = 4;
  // plain views
  Kokkos::View<double**> A{ "A", y_size, x_size };
  Kokkos::View<double*> x{ "x", x_size };
  Kokkos::View<double*> y{ "y", y_size };
  Kokkos::View<double*> xt{ "xt", y_size };
  Kokkos::View<double*> yt{ "yt", x_size };
  // expression base (data views)
  const size_t input_size_ext = (x_size > y_size ? x_size : y_size) + 2;
  Kokkos::View<double*> x_span_base{ "x_span",  input_size_ext };
  Kokkos::View<double*> y_span_base{ "y_span", input_size_ext };
  Kokkos::View<double**> x_diag_base{ "x_diag", x_size, x_size };
  Kokkos::View<double**> xt_diag_base{ "xt_diag", y_size, y_size };
  Kokkos::View<double**> y_diag_base{ "y_diag", y_size, y_size };
  Kokkos::View<double**> yt_diag_base{ "yt_diag", x_size, x_size };
  Kokkos::View<double**> A_subspan_base{ "A_subspan", y_size + 2, x_size + 2 };
  // expressions
  auto x_span()  { return pressio::span(x_span_base, one, x_size); }
  auto xt_span() { return pressio::span(x_span_base, one, y_size); }
  auto y_span()  { return pressio::span(y_span_base, one, y_size); }
  auto yt_span() { return pressio::span(y_span_base, one, x_size); }
  auto x_diagonal()  { return pressio::diagonal(x_diag_base); }
  auto xt_diagonal() { return pressio::diagonal(xt_diag_base); }
  auto y_diagonal()  { return pressio::diagonal(y_diag_base); }
  auto yt_diagonal() { return pressio::diagonal(yt_diag_base); }
  auto A_subspan() {
    using range_t = std::pair<size_t, size_t>;
    return pressio::subspan(A_subspan_base, range_t{ one, one + y_size }, range_t{ one, one + x_size });
  }

  virtual void SetUp(){
    A(0, 0) = 1.; A(0, 1) = 0.; A(0 ,2) = 2.;
    A(1, 0) = 2.; A(1, 1) = 1.; A(1, 2) = 3.;
    A(2, 0) = 0.; A(2, 1) = 0.; A(2, 2) = 1.;
    A(3, 0) = 2.; A(3, 1) = 3.; A(3, 2) = 4.;
    set_input(x, { 2., 6., 4. });
    set_input(xt, { 4., 2., 6., 3. });
    // expressions
    set_input(x_span_base, { 1., 2., 3., 4., 5., 6. });
    set_matrix(x_diag_base);
    set_matrix(xt_diag_base);
    set_matrix(y_diag_base);
    set_matrix(yt_diag_base);
    set_matrix(A_subspan_base);
  }

  virtual void TearDown(){}

private:

  template <typename ...ViewProps>
  static void set_input(Kokkos::View<ViewProps...> x, const std::vector<double> &values) {
    assert(x.extent(0) == values.size());
    auto x_h = Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace(), x);
    for (size_t i = 0; i < x.extent(0); ++i) {
      x_h(i) = values[i];
    }
    Kokkos::deep_copy(x, x_h);
  }

  // populates input matrix with unique integer values
  template <typename ...ViewProps>
  static void set_matrix(Kokkos::View<ViewProps...> mtx) {
    auto mtx_h = mtx;
    size_t ex0 = mtx.extent(0), ex1 = mtx.extent(1);
    for (size_t i = 0; i < ex0; ++i) {
      for (size_t j = 0; j < ex1; ++j) {
        mtx_h(i, j) = (double)(i * ex1 + j + 1.0);
      }
    }
  }

};

using ops_kokkos = kokkosFixture; // alias for nicer test naming

template <typename TransMode, typename AType, typename XType, typename YType, typename ScalarType>
void test_impl(TransMode trans, ScalarType alpha, AType A, XType x, ScalarType beta, YType y) {
  // copy original values
  Kokkos::View<double*> y_ref("y_ref", y.extent(0));
  for (size_t i = 0; i < y.extent(0); ++i) {
    y_ref(i) = y(i);
  }

  // note: explicit instance needed here because we take ref in ::pressio::ops::product()
  pressio::ops::product(trans, alpha, A, x, beta, y);

  // call reference gemv()
  vanilla_gemv(trans, alpha, A, x, beta, y_ref);

  // compare y and y_ref
  for (size_t i = 0; i < y.extent(0); ++i) {
    EXPECT_DOUBLE_EQ(y(i), y_ref(i));
  }
}

// Important (Thread Safety): modifications on A and y inputs for NaN injection simulation
// breaks thread-safety and assumes sequential execution. It's fine until we introduce threads.
template <typename FixtureType, typename TransMode, typename AType, typename XType, typename YType>
void test_impl(const FixtureType &test, TransMode trans, AType A, XType x, YType y) {
  // alpha = 1, beta = 0, simulate NaN injection in uninitialized y
  auto y_nan = y;
  ::pressio::ops::fill(y_nan, test.NaN);
  test_impl(trans, test.alpha1, A, x, test.beta0, y_nan);

  // alpha = 1, beta = 1, reuse values in y
  test_impl(trans, test.alpha1, A, x, test.beta1, y);

  // alpha = 0, beta = 1, simulate NaN in input
  const auto original = A(0, 0);
  A(0, 0) = test.NaN;
  test_impl(trans, test.alpha0, A, x, test.beta1, y);

  // alpha = 0, beta = 0, NaN in both input and result
  ::pressio::ops::fill(y_nan, test.NaN);
  test_impl(trans, test.alpha0, A, x, test.beta0, y_nan);

  // restore original A
  A(0, 0) = original;
}

//-------------------------------------------
// Test plain Kokkos views
//-------------------------------------------

TEST_F(ops_kokkos, dense_mat_vec_vec_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x, y);
}

TEST_F(ops_kokkos, dense_mat_vec_vec_T)
{
  test_impl(*this, pressio::transpose(), A, xt, yt);
}

//-------------------------------------------
// Test plain matrix, x as expression and plain y vector
//-------------------------------------------

TEST_F(ops_kokkos, dense_mat_span_vec_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x_span(), y);
}

TEST_F(ops_kokkos, dense_mat_span_vec_T)
{
  test_impl(*this, pressio::transpose(), A, xt_span(), yt);
}

TEST_F(ops_kokkos, dense_mat_diag_vec_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x_diagonal(), y);
}

TEST_F(ops_kokkos, dense_mat_diag_vec_T)
{
  test_impl(*this, pressio::transpose(), A, xt_diagonal(), yt);
}

//-------------------------------------------
// Test plain matrix, plain x vector and y as expression
//-------------------------------------------

TEST_F(ops_kokkos, dense_mat_vec_span_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x, y_span());
}

TEST_F(ops_kokkos, dense_mat_vec_span_T)
{
  test_impl(*this, pressio::transpose(), A, xt, yt_span());
}

TEST_F(ops_kokkos, dense_mat_vec_diag_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x, y_diagonal());
}

TEST_F(ops_kokkos, dense_mat_vec_diag_T)
{
  test_impl(*this, pressio::transpose(), A, xt, yt_diagonal());
}

//-------------------------------------------
// Test plain matrix with x and y as expressions
//-------------------------------------------

TEST_F(ops_kokkos, dense_mat_span_span_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x_span(), y_span());
}

TEST_F(ops_kokkos, dense_mat_span_span_T)
{
  test_impl(*this, pressio::transpose(), A, xt_span(), yt_span());
}

TEST_F(ops_kokkos, dense_mat_span_diag_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x_span(), y_diagonal());
}

TEST_F(ops_kokkos, dense_mat_span_diag_T)
{
  test_impl(*this, pressio::transpose(), A, xt_span(), yt_diagonal());
}

TEST_F(ops_kokkos, dense_mat_diag_span_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x_diagonal(), y_span());
}

TEST_F(ops_kokkos, dense_mat_diag_span_T)
{
  test_impl(*this, pressio::transpose(), A, xt_diagonal(), yt_span());
}

TEST_F(ops_kokkos, dense_mat_diag_diag_NT)
{
  test_impl(*this, pressio::nontranspose(), A, x_diagonal(), y_diagonal());
}

TEST_F(ops_kokkos, dense_mat_diag_diag_T)
{
  test_impl(*this, pressio::transpose(), A, xt_diagonal(), yt_diagonal());
}

//-------------------------------------------
// Test A matrix as expression with x, y as plain vectors
//-------------------------------------------

TEST_F(ops_kokkos, dense_submat_vec_vec_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x, y);
}

TEST_F(ops_kokkos, dense_submat_vec_vec_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt, yt);
}

//-------------------------------------------
// Test A matrix as expression with x as expression and plain y vector
//-------------------------------------------

TEST_F(ops_kokkos, dense_submat_span_vec_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x_span(), y);
}

TEST_F(ops_kokkos, dense_submat_span_vec_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt_span(), yt);
}

TEST_F(ops_kokkos, dense_submat_diag_vec_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x_diagonal(), y);
}

TEST_F(ops_kokkos, dense_submat_diag_vec_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt_diagonal(), yt);
}

//-------------------------------------------
// Test A matrix as expression with plain x vector and y as expression
//-------------------------------------------

TEST_F(ops_kokkos, dense_submat_vec_span_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x, y_span());
}

TEST_F(ops_kokkos, dense_submat_vec_span_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt, yt_span());
}

TEST_F(ops_kokkos, dense_submat_vec_diag_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x, y_diagonal());
}

TEST_F(ops_kokkos, dense_submat_vec_diag_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt, yt_diagonal());
}

//-------------------------------------------
// Test A matrix, x and y as expressions
//-------------------------------------------

TEST_F(ops_kokkos, dense_submat_span_span_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x_span(), y_span());
}

TEST_F(ops_kokkos, dense_submat_span_span_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt_span(), yt_span());
}

TEST_F(ops_kokkos, dense_submat_span_diag_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x_span(), y_diagonal());
}

TEST_F(ops_kokkos, dense_submat_span_diag_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt_span(), yt_diagonal());
}

TEST_F(ops_kokkos, dense_submat_diag_span_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x_diagonal(), y_span());
}

TEST_F(ops_kokkos, dense_submat_diag_span_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt_diagonal(), yt_span());
}

TEST_F(ops_kokkos, dense_submat_diag_diag_NT)
{
  test_impl(*this, pressio::nontranspose(), A_subspan(), x_diagonal(), y_diagonal());
}

TEST_F(ops_kokkos, dense_submat_diag_diag_T)
{
  test_impl(*this, pressio::transpose(), A_subspan(), xt_diagonal(), yt_diagonal());
}
