
Hello world
===========


1. Clone pressio-ops and download `Eigen-3.4 <https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz>`_

2. Create a `main.cpp` with the following content:

.. code-block:: cpp

   #include <pressio/ops.hpp>
   #include <Eigen/Dense>
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

3. Build and run (requires C++17):

.. code-block:: bash

   g++ -D PRESSIO_ENABLE_TPL_EIGEN -I <path-to-pressio-ops>/include/ -I <path-to-eigen>/eigen-3.4.0 main.cc
   ./a.out



For more details about configuring and option, see `here <configuration.html>`_.
