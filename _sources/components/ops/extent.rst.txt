.. include:: ../../mydefs.rst

``extent``
==========

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template<class T, class IndexType>
  std::size_t extent(const T & objectIn, const IndexType i);

  }} // end namespace pressio::ops

Description
-----------

* Returns the size or dimension of a container ``objectIn`` along a specified axis ``i``

* ``T`` must be one of the following:

  * an Eigen vector or matrix object

  * a Kokkos view

  * a Teuchos vector

  * a Tpetra vector or multi-vector

  * a Tpetra block vector or multi-vector

  * a pressio expression, i.e. ``pressio::diag``, ``pressio::span``, ``pressio::subspan``, based on an Eigen, Tpetra Block, or Kokkos container

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking that ``T`` has the correct type.
