
#include <gtest/gtest.h>
#include <pressio/ops.hpp>
#include <Eigen/Dense>

TEST(ops_hello_world, t1){
 using namespace pressio;

 Eigen::VectorXd x(3), y(3);
 x << 1.0, 2.0, 3.0;
 y.setConstant(2.0);

 // BLAS-like dot
 const auto d = ops::dot(x, y); // 1*2 + 2*2 + 3*2 = 12
 EXPECT_DOUBLE_EQ(d, 12.);

 // y = 1.5*x - y, so y becomes [-0.5, 1.0, 2.5]
 ops::update(y, -1., x, 1.5);
 EXPECT_DOUBLE_EQ(y[0], -0.5);
 EXPECT_DOUBLE_EQ(y[1],  1.0);
 EXPECT_DOUBLE_EQ(y[2],  2.5);

 // z = A * x  (matrix–vector product)
 Eigen::MatrixXd A = Eigen::MatrixXd::Identity(3,3);
 Eigen::VectorXd z(3);
 ops::product(pressio::nontranspose{}, 1., A, x, 0., z);
 EXPECT_DOUBLE_EQ(z[0], 1.);
 EXPECT_DOUBLE_EQ(z[1], 2.);
 EXPECT_DOUBLE_EQ(z[2], 3.);
}
