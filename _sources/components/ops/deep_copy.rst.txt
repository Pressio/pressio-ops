.. include:: ../../mydefs.rst

``deep_copy``
=============

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template<typename T1, typename T2>
  void deep_copy(T2 & dest, const T1 & src);

  template<typename T>
  void deep_copy(T & dest, const T & src);

  }} // end namespace pressio::ops

Description
-----------

* Copies all elements from ``src`` into ``dst``, so that ``dst`` is fully independent of ``src``.

* ``T1`` and ``T2`` must have the same rank, and must be:

  * Two Eigen-based containers (either a native Eigen container or a Pressio expression based on an Eigen container)

  * Two Kokkos-based containers (either a native Kokkos view or a Pressio expression based on a Kokkos container)

* ``T`` must be:

  * a Tpetra vector or multi-vector

  * a Tpetra block vector or multi-vector
