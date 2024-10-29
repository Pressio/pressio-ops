.. include:: ../../mydefs.rst

``subspan``
===========

Header: ``<pressio/expressions.hpp>``

API
---

.. code-block:: cpp

  namespace pressio {

  template<class T>
  /*impl defined*/ subspan(T & operand,
			   std::pair<std::size_t, std::size_t> rowsRange,
			   std::pair<std::size_t, std::size_t> colsRange);

  } // end namespace pressio

Description
-----------

* Takes in an ``operand``, as well as the ``rowsRange`` and ``colsRange`` intervals that will be used in each dimension

  * ``operand`` is either:

    * an Eigen dense matrix, ``pressio::is_dense_matrix_eigen<T>::value == true``

    * a Kokkos rank-2 view, i.e. ``pressio::is_dense_matrix_kokkos<T>::value == true``

* Returns an expression object that represents a subspan of the ``operand``.
