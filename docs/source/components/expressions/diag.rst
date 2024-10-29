.. include:: ../../mydefs.rst

``diagonal``
============

Header: ``<pressio/expressions.hpp>``

API
---

.. code-block:: cpp

  namespace pressio {

  template<class T>
  /*impl defined*/ diagonal(T & operand);

  } // end namespace pressio

Description
-----------

* Takes in an ``operand`` that is either:

  * a square Eigen dense matrix, ``pressio::is_dense_matrix_eigen<T>::value == true``

  * a square Kokkos rank-2 view, i.e. ``pressio::is_dense_matrix_kokkos<T>::value == true``

* Returns an expression that represents that diagonal of ``operand``
