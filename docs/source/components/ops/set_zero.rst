.. include:: ../../mydefs.rst

``set_zero``
============

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template <typename T>
  void set_zero(T & o);

  }} // end namespace pressio::ops

Description
-----------

* Sets every entry in ``o`` to zero

* ``o`` may be a container of the following types:

  * Eigen (or a Pressio expression acting on an Eigen container)

  * Kokkos (or a Pressio expression acting on a Kokkos container)

  * Teuchos (rank-1 only)

  * Tpetra (or a Pressio expression acting on a Tpetra container)

  * Tpetra Block (or a Pressio expression acting on a Tpetra Block container)
