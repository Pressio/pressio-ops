
#include <pressio/ops.hpp>
#include <Eigen/Dense>
#include <iostream>

int main(){
 using namespace pressio;

 Eigen::VectorXd x(3), y(3);
 x << 1.0, 2.0, 3.0;
 y.setConstant(2.0);

 // BLAS-like dot
 const auto d = ops::dot(x, y); // 1*2 + 2*2 + 3*2 = 12

 // y = 1.5*x - y, so y becomes [-0.5, 1.0, 2.5]
 ops::update(y, -1., x, 1.5);

 // z = A * x  (matrix–vector product)
 Eigen::MatrixXd A = Eigen::MatrixXd::Identity(3,3);
 Eigen::VectorXd z(3);
 ops::product(pressio::nontranspose{}, 1., A, x, 0., z);

 std::cout << "dot(x,y) = " << d << '\n';
 std::cout << "y after axpby = " << y.transpose() << '\n';
 std::cout << "z = " << z.transpose() << '\n';

 return 0;
}
