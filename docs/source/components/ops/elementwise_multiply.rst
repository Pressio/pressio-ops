.. include:: ../../mydefs.rst

``elementwise_multiply``
========================

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template <class T, class T1, class T2, class alpha_t, class beta_t>
  void elementwise_multiply(
      const alpha_t & alpha,
      const T & x,
      const T1 & z,
      const beta_t & beta,
      T2 & y
  );

  }} // end namespace pressio::ops

Description
-----------

* Computes ``y = beta * y + alpha * (x ⊙ z)``, where ``⊙`` denotes element-wise multiplication, and stores the result in y

* ``T``, ``T1``, and ``T2`` must be one-dimensional containers with compatible scalar types:

  * an Eigen vector

  * a Kokkos rank-1 view

  * a Tpetra vector

  * a Tpetra block vector

  * a pressio expression, i.e. ``pressio::diag``, ``pressio::span``, ``pressio::subspan``, based on Eigen or Kokkos container

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking that ``T``, ``T1``, and ``T2`` have the correct types.
