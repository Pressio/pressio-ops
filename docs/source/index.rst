.. role:: raw-html-m2r(raw)
   :format: html

.. include:: mydefs.rst

pressio-ops
===========

This C++ library aims to provide a unified free-function-based interface
to facilitate usability and interoperability of widely-used linear
algebra software libraries.

Motivation
----------

Linear algebra underpins many applications fundamental to science and industry.
Currently, there are multiple open-source libraries offering shared- and distributed-memory
linear algebra data structures (vectors, matrices, etc.) and/or kernel operations to manipulate them.
For example, Trilinos, PETSc, Kokkos/Kokkos-kernels, Eigen, Blitz++, Armadillo, mlpack, BLAS/LAPACK.
These libraries serve as foundations to many applications.
Compound this mutiplicity of efforts by the lack of interest and/or resources
to improve their usability and inteoperabability, and the result is a plethora
of linear algebra libraries that shared some key aspects:

- **Diverse API**: every library has its own custom API for doing, after all, the same set of operations.
  This poses a major limitation to existing software stacks relying on them because
  it inhibits an easy transition to a different choice.
  What would happen if one of these fundamental libraries were discontinued?
  It would lead to *many* applications having to be refactored,
  a huge investment of resouces and development hours.
  Also, this constitutes a problem for any new application that will being
  developed, since one would need to choose one library from the start
  and stick to it, or reimplemnet support for multiple backends from scratch every time.

- **Hard-to-use API**: some of these libraries adopt an API that closely adheres to the BLAS standard,
  thus making them harder to use for a generic user. It is well-known and accepted that the BLAS standard defines
  an API is hard to read and use: one reason is that its API defines functions accepting several arguments,
  with adjacent parameters that can be invoked by the same arguments in either order with different meaning.
  This makes them hard to be used correctly---this was also a key motivation of
  the standardization effort that led to the C++26 stdBLAS feature.

- **Hard to extend/customize**: in some cases, e.g. Trilinos, the design is such that operations to manipulate data
  are methods of the data structures classes themselves rather than free fucntions. In C++, such design precludes
  the flexibility of doing user-level overloading or specialization of these "operations".

- **Minimal or non-existent interoperability**: the intoperability between some of these libraries
  is minimal or even non-existent. Several factors contributed to this, inlcuding that some
  of the libraries were intended for heterogenous hardware, while some only work for CPUs;
  some only operate on a single node while others support distributed memory.
  This makes it really hard to couple different applications, exchange data,
  and operated on-line on different data structures.

What does pressio-ops offer?
----------------------------

A unified free-function-based interface to facilitate
usability and interoperability of widely-used linear algebra software libraries.
The supported capabilities are shown in the table below and in the expanded sidebar.

Each component/level of the stack depends on the ones below it.

.. list-table::
   :widths: 10 48 42
   :header-rows: 1
   :align: left

   * -
     - Description
     - Header(s)

   * - ``ops``
     - shared-memory/distributed linear algebra kernels wrappers
     - ``<pressio/ops.hpp>``

   * - ``expressions``
     - expressions templates, e.g.: span, diagonal, subspan
     - ``<pressio/expressions.hpp>``

   * - ``type_traits``
     - type traits and detection
     - ``<pressio/type_traits.hpp>``

   * - ``mpl``
     - metaprogramming functionalities
     - ``<pressio/mpl.hpp>``


Get Started
-----------

* `Read here <configuration.html>`_

* `Hello world <helloworld.html>`_


License and Citation
--------------------

The full license (BSD-3) is available `here <https://github.com/Pressio/pressio-ops/blob/main/LICENSE>`_.

Sooner or later we will publish this... in the meantime, you can find on arXiv
an (outdated) preprint at: https://arxiv.org/abs/2003.07798

Questions?
----------

Find us on Slack: https://pressioteam.slack.com or
open an issue on `github <https://github.com/Pressio/pressio-ops>`_.


.. toctree::
   :maxdepth: 1
   :hidden:

   configuration
   helloworld

.. toctree::
   :caption: ops
   :maxdepth: 1
   :hidden:

   ./components/ops/abs
   ./components/ops/add_to_diagonal
   ./components/ops/clone
   ./components/ops/deep_copy
   ./components/ops/dot
   ./components/ops/elementwise_multiply
   ./components/ops/elementwise_reciprocal
   ./components/ops/extent
   ./components/ops/fill
   ./components/ops/min_max
   ./components/ops/norms
   ./components/ops/pow
   ./components/ops/matrix_matrix_product
   ./components/ops/matrix_vector_product
   ./components/ops/resize
   ./components/ops/scale
   ./components/ops/set_zero
   ./components/ops/update

.. toctree::
   :caption: expressions
   :maxdepth: 1
   :hidden:

   ./components/expressions/span
   ./components/expressions/subspan
   ./components/expressions/diag
   ./components/expressions/column
   ./components/expressions/is_expression

.. toctree::
   :caption: type_traits
   :maxdepth: 1
   :hidden:

   ./components/type_traits


.. toctree::
   :caption: mpl
   :maxdepth: 1
   :hidden:

   ./components/mpl


.. toctree::
   :caption: Miscellanea
   :maxdepth: 1
   :hidden:

   GitHub Repo <https://github.com/Pressio/pressio-ops>
   Open an issue/feature req. <https://github.com/Pressio/pressio-ops/issues>
   license
