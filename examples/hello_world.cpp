
#include <Eigen/Dense>
#include <pressio/ops.hpp>
#include <iostream>

int main(){
  namespace pops = pressio::ops;

  using vec_t = Eigen::VectorXd;
  vec_t v1 = vec_t::Random(43);
  vec_t v2 = vec_t::Random(43);
  std::cout << pops::dot(v1, v2) << "\n";

  using mat_t = Eigen::MatrixXd;
  mat_t M = mat_t::Random(43, 5);
  auto c0 = pressio::column(M, 0);
  auto c3 = pressio::column(M, 3);
  std::cout << pops::dot(c0, c3) << "\n";

  std::cout << pops::dot(c0, v1) << "\n";

  return 0;
}
