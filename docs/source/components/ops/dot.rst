.. include:: ../../mydefs.rst

``dot``
=======

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template<typename T1, typename T2, typename DotResult>
  void dot(const T1 & vecA, const T2 & vecB, DotResult & result);

  template<typename T1, typename T2>
  scalar_type dot(const T1 & vecA, const T2 & vecB);

  }} // end namespace pressio::ops

Description
-----------

* Computes the dot product of two compatible vectors (``vecA`` and ``vecB``)

  * Stores the result in ``result`` if provided; otherwise, returns the result

* ``T1`` and ``T2`` must be one-dimensional containers with compatible scalar types:

  * an Eigen vector

  * a Kokkos rank-1 view

  * a Tpetra vector

  * a Tpetra block vector

  * a Epetra vector

  * a pressio expression, i.e. ``pressio::diag``, ``pressio::span``, ``pressio::subspan``, based on Eigen or Kokkos container

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking that ``T1`` and ``T2`` have the correct types.
