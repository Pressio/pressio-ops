.. include:: ../../mydefs.rst

``abs``
=======

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template<class T1, class T2>
  void abs(T1 & x, const T2 & y);

  }} // end namespace pressio::ops

Description
-----------

* Computes the element-wise absolute value of each element
  in the operand x and stores the result in y.

* ``T1`` and ``T2`` must be one-dimensional containers with compatible scalar types:

  * an Eigen vector

  * a Kokkos rank-1 view

  * a Tpetra vector

  * a Tpetra block vector

  * a Pressio expression, i.e. ``pressio::diag``, ``pressio::span``, ``pressio::subspan``, based on Eigen or Kokkos container
