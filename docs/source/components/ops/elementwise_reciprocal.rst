.. include:: ../../mydefs.rst

``elementwise_reciprocal``
========================

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template <class T1, class T2>
  void elementwise_multiply(const T1 & z, T2 & y);

  }} // end namespace pressio::ops

Description
-----------

* Computes the elementwise reciprocal of ``z`` and stores it in ``y``

* ``T1`` and ``T2`` must be one-dimensional containers with compatible scalar types. They may be:

  * Eigen vectors or Pressio expressions built from Eigen rank-1 containers

  * Kokkos rank-1 views or Pressio expressions built from Kokkos rank-1 containers

  * Tpetra vectors or column expressions

  * Tpetra block vectors or column expressions

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking that ``T1`` and ``T2`` have the correct types.
