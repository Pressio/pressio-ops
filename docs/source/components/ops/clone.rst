.. include:: ../../mydefs.rst

.. role:: cpp(code)
   :language: cpp

``clone``
=========

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template<class T>
  T clone(const T & operand);

  }} // end namespace pressio::ops

Description
-----------

* Creates and returns a new instance of :cpp:`T` by making a new allocation
  and *copying* all values from :cpp:`operand` into it.

  * It is an exact but independent clone of :cpp:`operand`.

* ``T`` must be:

  * an Eigen vector or matrix object

  * a Kokkos view

  * a Teuchos vector

  * or a Tpetra vector or multi-vector

  * or a Tpetra block vector or multi-vector

Notes
-----

* This is a blocking operation, i.e. the kernel completes before returning.

* This kernel has value semantics, even for types that, by default,
  have view semantics like Kokkos, Tpetra or TpetraBlock.
  This means the following:
  let :cpp:`auto result = clone(operand)`, then any operation applied
  to :cpp:`operand` *after* calling clone will NOT
  have any impact on ``result``.
  And any operation applied to ``result`` will not have any impact on ``operand``.

* For types that have value semantics, for example ``Eigen::Matrix<...>``,
  this kernel can be implemented by calling the copy constructor
  and returning the copy

* For Kokkos, Tpetra, or TpetraBlock data types, which by default have view semantics
  (i.e. a copy is a shallow copy), the operation can be implemented by first making a new
  object with extents identical to ``operand``, followed by a deep copy, and then return the result.
