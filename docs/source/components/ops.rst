
.. include:: ../mydefs.rst

``ops``
=======

Header: ``<pressio/ops.hpp>``

Public namespace: ``pressio::ops``

Pressio operations are generalized to work on a variety of container types and backends.

Types
-----

The following table holds both the types supported throughout the ``ops`` directory and the
built-in booleans that confirm if a given type ``T`` is the expected type.

All expressions are within the ``pressio`` namespace.

.. list-table::
   :widths: 10 20 20
   :header-rows: 1
   :align: left

   * - Container Type
     - Rank-1 Check
     - Rank-2 Check

   * - Eigen
     - ``is_vector_eigen<T>::value``
     - ``is_sparse_matrix_eigen<T>::value``, ``is_dense_matrix_eigen<T>::value``

   * - Kokkos
     - ``is_vector_kokkos<T>::value``
     - ``is_dense_matrix_kokkos<T>::value``,   ``is_sparse_matrix_kokkos<T>::value``

   * - Epetra
     - ``is_vector_epetra<T>::value``
     - ``is_multi_vector_epetra<T>::value``

   * - Tpetra
     - ``is_vector_tpetra<T>::value``
     - ``is_multi_vector_tpetra<T>::value``

   * - Tpetra Block
     - ``is_vector_tpetra_block<T>::value``
     - ``is_multi_vector_tpetra_block<T>::value``

   * - Teuchos
     - ``is_dense_vector_teuchos<T>::value``
     - ``is_dense_matrix_teuchos<T>::value``

Additionally, because Pressio features expressions for containers built on Eigen, Kokkos, and Tpetra, you can check whether or not a container is native with:

.. list-table::
   :widths: 10 20 20
   :header-rows: 1
   :align: left

   * - Container Type
     - Native
     - Pressio Expression

   * - Eigen
     - ``is_native_container_eigen<T>::value``
     - ``is_expression_acting_on_eigen<T>::value``

   * - Kokkos
     - ``is_native_container_kokkos<T>::value``
     - ``is_expression_acting_on_kokkos<T>::value``

   * - Tpetra
     -
     - ``is_expression_column_acting_on_tpetra<T>::value``

Navigation
----------

Use the links below to view details about each operation.

.. toctree::
    :maxdepth: 1

    ops/abs
    ops/add_to_diagonal
    ops/clone
    ops/deep_copy
    ops/dot
    ops/elementwise_multiply
    ops/extent
    ops/fill
    ops/min_max
    ops/norms
    ops/pow
    ops/matrix_matrix_product
    ops/matrix_vector_product
    ops/resize
    ops/scale
    ops/set_zero
    ops/update
