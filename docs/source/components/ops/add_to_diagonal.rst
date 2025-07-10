.. include:: ../../mydefs.rst

``add_to_diagonal``
===================

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template<class T1, class ScalarType>
  void add_to_diagonal(T1 & operand, const ScalarType & value);

  }} // end namespace pressio::ops

Description
-----------

* Adds the specified scalar ``value`` to each diagonal element of ``operand``

* ``T`` must be a rank-2 Eigen matrix

* ``ScalarType`` must be convertible to ``pressio::Traits<T>::scalar_type``

Notes
-----

* If the diagonal entries of ``operand`` are written, then all diagonal entries must already exist.
