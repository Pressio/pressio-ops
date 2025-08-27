
#include <gtest/gtest.h>
#include <pressio/ops.hpp>
#include <Eigen/Dense>
#include <Tpetra_Core.hpp>
#include <Tpetra_Map.hpp>
#include <Tpetra_Vector.hpp>
#include <Tpetra_MultiVector.hpp>
#include <Teuchos_RCP.hpp>
#include <iostream>

TEST(ops_hello_world, t2)
{
   using map_t = Tpetra::Map<>;
   using vec_t = Tpetra::Vector<>;
   using mv_t  = Tpetra::MultiVector<>;

   auto comm = Tpetra::getDefaultComm();

   // Global problem size N (distributed across ranks)
   const Tpetra::global_size_t N = 9;

   // Create a contiguous, uniformly distributed map
   using LO = map_t::local_ordinal_type;
   using GO = map_t::global_ordinal_type;
   auto map = Tpetra::createUniformContigMap<LO,GO>(N, comm);

   // vectors
   vec_t x(map), y(map), z(map);
   pressio::ops::fill(x, 1.0);
   pressio::ops::fill(y, 2.0);
   pressio::ops::fill(z, 1.0);

   // Global dot product via pressio-ops
   const auto d = pressio::ops::dot(x, y);

   // MultiVector with 2 columns (row map as x,y,z)
   mv_t MV(map, 2);

   // Obtain column views (each behaves like a Vector in ops)
   auto col0 = pressio::column(MV, 0);
   auto col1 = pressio::column(MV, 1);
   // these modify the underlying MV because are mutable views
   pressio::ops::fill(col0, 3.);
   pressio::ops::fill(col1, 4.);

   // dot between cols
   const auto dcols = pressio::ops::dot(col0, col1);

   // z = z + 0.5 * col1
   pressio::ops::update(z, 1., col1, 0.5);
   auto dotz = pressio::ops::dot(col0, z);

   EXPECT_NEAR(d, 18., 1e-8);
   EXPECT_NEAR(dcols, 12.*9., 1e-8);
   EXPECT_NEAR(dotz, 9.*9., 1e-8);

   // perform mat-vec, storing result into Eigen vector
   // v0 = MV^T * z
   Eigen::VectorXd v0(2);
   pressio::ops::fill(v0, 0.);
   pressio::ops::product(pressio::transpose{}, 1., MV, z, 0., v0);
   EXPECT_NEAR(v0[0], 81., 1e-8);
   EXPECT_NEAR(v0[1], 12.*9., 1e-8);
}
