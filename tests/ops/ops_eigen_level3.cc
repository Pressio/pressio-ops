
#include <gtest/gtest.h>
#include "pressio/ops.hpp"

//-------------------------------------------
// Test implementation and utilities
//-------------------------------------------

class ops_eigen
  : public ::testing::Test
{
public:
  using mat_t = Eigen::MatrixXd;
  using vec_t = Eigen::VectorXd;

  // containers
  const size_t m = 4;
  const size_t n = 3;
  const size_t k = 2;
  mat_t A;  // m x k
  mat_t B;  // k x n
  mat_t Bt; // m x n

  virtual void SetUp(){
    A = mat_t(m, k);
    B = mat_t(k, n);
    Bt = mat_t(m, n);
    fillOperand(A);
    fillOperand(B);
    fillOperand(Bt);
  }

  virtual void TearDown(){}

private:
  void fillOperand(mat_t & M, double v0 = 1.0)
  {
    const std::size_t num_rows = ::pressio::ops::extent(M, 0);
    const std::size_t num_cols = ::pressio::ops::extent(M, 1);
    for (std::size_t i = 0; i < num_rows; ++i){
      for (std::size_t j = 0; j < num_cols; ++j){
        M(i, j) = (double)(i * num_cols + j + v0);
      }
    }
  }
};

template <
  typename TransModeA,
  typename AType,
  typename BType,
  typename CType,
  typename ScalarType
  >
void vanilla_gemm(TransModeA /* tA */, ScalarType alpha,
                  const AType &A, const BType &B,
                  ScalarType beta, CType &C) {
  const bool trans_a = std::is_same<TransModeA, ::pressio::transpose>::value;
  const std::size_t num_rows = ::pressio::ops::extent(C, 0);
  const std::size_t num_cols = ::pressio::ops::extent(C, 1);
  const std::size_t b_rows = ::pressio::ops::extent(B, 0);
  EXPECT_EQ(::pressio::ops::extent(A, trans_a ? 1 : 0), num_rows);
  EXPECT_EQ(::pressio::ops::extent(A, trans_a ? 0 : 1), b_rows);
  EXPECT_EQ(::pressio::ops::extent(B, 1), num_cols);

  if (beta == 0.) ::pressio::ops::set_zero(C);
  else ::pressio::ops::scale(C, beta);
  if (alpha == 0.) return;

  for (size_t i = 0; i < num_rows; ++i) {
    for (size_t k = 0; k < b_rows; ++k) {
      const auto a_val = trans_a ? A(k, i) : A(i, k);
      for (size_t j = 0; j < num_cols; ++j) {
        C(i, j) += alpha * a_val * B(k, j);
      }
    }
  }
}

template <typename CType, typename CRefType>
void compare_results(const CType &C, const CRefType &C0) {
  const std::size_t num_rows = ::pressio::ops::extent(C, 0);
  const std::size_t num_cols = ::pressio::ops::extent(C, 1);
  ASSERT_EQ(num_rows, ::pressio::ops::extent(C0, 0));
  ASSERT_EQ(num_cols, ::pressio::ops::extent(C0, 1));
  for (size_t i = 0; i < num_rows; ++i) {
    for (size_t j = 0; j < num_cols; ++j) {
      ASSERT_DOUBLE_EQ(C0(i, j), C(i, j));
    }
  }
}

template <typename TransModeA, typename AType, typename BType, typename CType, typename ScalarType, typename ProdFunc>
void test_impl(TransModeA trans_a, ScalarType alpha, const AType &A, const BType &B, ScalarType beta, CType &C, ProdFunc F) {
  // get reference results
  auto C0 = ::pressio::ops::clone(C);

  // obtain reference results
  vanilla_gemm(trans_a, alpha, A, B, beta, C0);

  // run tested routine
  F(trans_a, pressio::nontranspose(), alpha, A, B, beta, C);

  // compare result
  compare_results(C, C0);
}

template <typename TransModeA, typename AType, typename BType>
void test_impl(TransModeA trans_A, const AType &A, const BType &B) {
  const auto nan = std::nan("0");
  const auto product = []( // regular product
      auto trans_a, auto trans_b,
      auto alpha, auto &&A, auto &&B,
      auto beta, auto &&C) {
    pressio::ops::product(trans_a, trans_b, alpha, A, B, beta, C);
  };

  const auto num_rows = ::pressio::ops::extent(A,
      std::is_same<TransModeA, ::pressio::transpose>::value ? 1 : 0);
  ops_eigen::mat_t C(num_rows, ::pressio::ops::extent(B, 1));
  ::pressio::ops::fill(C, nan); /* simulate NaN in uninitialized output */

  constexpr auto beta0  = ::pressio::Constants<double>::zero();
  constexpr auto alpha1 = ::pressio::Constants<double>::one();
  test_impl(trans_A, alpha1, A, B, beta0, C, product);

  /* also cover non-zero beta */
  constexpr auto beta1 = ::pressio::Constants<double>::one();
  test_impl(trans_A, alpha1, A, B, beta1, C, product);
}

// self product: C = A^T x A
template <typename AType>
void test_impl(const AType &A) {
  const auto nan = std::nan("0");
  const auto self_product = []( // self product (ignore B)
      auto trans_a, auto trans_b,
      auto alpha, auto &&A, auto &&B,
      auto beta, auto &&C) {
    pressio::ops::product(trans_a, trans_b, alpha, A, beta, C);
  };

  const auto size = ::pressio::ops::extent(A, 1);
  ops_eigen::mat_t C(size, size);
  ::pressio::ops::fill(C, nan); /* simulate NaN in uninitialized output */

  constexpr auto beta0  = ::pressio::Constants<double>::zero();
  constexpr auto alpha1 = ::pressio::Constants<double>::one();
  test_impl(::pressio::transpose(), alpha1, A, A, beta0, C, self_product);

  /* also cover non-zero beta */
  constexpr auto beta1 = ::pressio::Constants<double>::one();
  test_impl(::pressio::transpose(), alpha1, A, A, beta1, C, self_product);
}

//-------------------------------------------
// Test Eigen containers
//-------------------------------------------

TEST_F(ops_eigen, dense_matrix_dense_matrix_prod)
{
  test_impl(::pressio::nontranspose(), A, B);
}

TEST_F(ops_eigen, dense_matrix_T_dense_matrix_prod)
{
  test_impl(::pressio::transpose(), A, Bt);
}

TEST_F(ops_eigen, dense_matrix_T_self_prod)
{
  test_impl(A);
}
