.. include:: ../../mydefs.rst

``resize``
==========

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  // T is rank-1
  template <typename T>
  void resize(T & o, ::pressio::ops::impl::ordinal_t<T> newSize);

  // T is rank-2
  template <typename T>
  void resize(T & o,
    const ::pressio::ops::impl::ordinal_t<T> newRows,
    const ::pressio::ops::impl::ordinal_t<T> newCols);

  }} // end namespace pressio::ops

Description
-----------

* Resizes ``o`` to the specified dimensions

* ``o`` may be either of the following types:

  * A dynamic Eigen container

  * A dynamic Kokkos view
