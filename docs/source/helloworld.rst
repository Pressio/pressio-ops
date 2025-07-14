
Hello world
===========


1. Clone pressio-ops and download `Eigen-3.4 <https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz>`_

2. Inside `pressio-ops/examples` you can find `hello_world.cpp`:

.. literalinclude:: ../../examples/hello_world.cpp
   :language: cpp

3. Build and run (requires C++17):

.. code-block:: bash

   g++ -D PRESSIO_ENABLE_TPL_EIGEN -I <path-to-pressio-ops>/include/ -I <path-to-eigen>/eigen-3.4.0 hello_world.cpp
   ./a.out


For more details about configuring and option, see `here <configuration.html>`_.
