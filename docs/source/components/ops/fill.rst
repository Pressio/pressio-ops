.. include:: ../../mydefs.rst

``fill``
========

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template<class T, class ScalarType>
  void fill(T & operand, ScalarType const & value);

  }} // end namespace pressio::ops

Description
-----------

* Overwrites each element of ``operand`` with ``value``.

* ``T`` must be:

  * an Eigen vector or matrix object

  * a Kokkos rank-1 or rank-2 view

  * a Teuchos vector

  * a Tpetra vector or multi-vector

  * a Tpetra block vector or multi-vector

  * a Epetra vector or multi-vector

  * a pressio expression, i.e. ``pressio::diag``, ``pressio::span``, ``pressio::subspan``, based on an Eigen or Kokkos container

* ``ScalarType`` must be convertible to ``pressio::Traits<T>::scalar_type``

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking that ``T1`` and ``T2`` have the correct types.
