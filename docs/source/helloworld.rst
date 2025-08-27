
Hello world
===========


Basic example using Eigen only
--------------------------------

1. Clone pressio-ops and download `Eigen-3.4 <https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz>`_

2. Copy the snippet below into a `main.cpp` somewhere:

  .. literalinclude:: ../../tests/ops/hello_world_1.cc
     :language: cpp


3. Build/run (requires C++17):

  .. code-block:: bash

     g++ -D PRESSIO_ENABLE_TPL_EIGEN -I <path-to-pressio-ops>/include/ -I <path-to-eigen>/eigen-3.4.0 main.cpp
     ./a.out


For more details about configuring and option, see `here <configuration.html>`_.


Basic example using Trilinos
----------------------------

This assumes you have trilinos installed somewhere. 

  .. literalinclude:: ../../tests/ops/hello_world_2.cc
     :language: cpp

