.. include:: ../../mydefs.rst

``scale``
=========

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template <typename T, class ScalarType>
  void scale(T & o, const ScalarType & value);

  }} // end namespace pressio::ops

Description
-----------

* Multiplies every entry in ``o`` by ``value``

* ``o`` may be a rank-1 or rank-2 container of the following types:

  * Eigen (or a Pressio expression acting on an Eigen container)

  * Kokkos (or a Pressio expression acting on a Kokkos container)

  * Teuchos

  * Tpetra (or a Pressio expression acting on a Tpetra container)

  * Tpetra Block (or a Pressio expression acting on a Tpetra Block container)

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking for the correct types.
