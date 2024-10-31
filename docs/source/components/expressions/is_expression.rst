.. include:: ../../mydefs.rst

``is_expression``
=================

Header: ``<pressio/expressions.hpp>``

API
---

.. code-block:: cpp

  namespace pressio {

  // For a given type T
  bool eigen = is_expression_acting_on_eigen<T>::value;

  bool kokkos = is_expression_acting_on_kokkos<T>::value;

  bool tpetra = is_expression_acting_on_tpetra<T>::value;
  bool tpetra = is_expression_column_acting_on_tpetra<T>::value;

  bool tpetra_block = is_expression_acting_on_tpetra_block<T>::value;
  bool tpetra_block = is_expression_column_acting_on_tpetra_block<T>::value;

  } // end namespace pressio

Description
-----------

* Returns a boolean to indicate if the given type ``T`` is the specified expression type
