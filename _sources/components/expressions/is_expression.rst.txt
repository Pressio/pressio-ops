.. include:: ../../mydefs.rst

``is_expression``
=================

Header: ``<pressio/expressions.hpp>``


This page summarizes the main type traits for detecting Pressio expressions and how they interact with native containers from supported backends.

Core Expression Type Traits
----------------------------

+----------------------------------------------+--------------------------------------------------------------+
| Trait                                        | Description                                                  |
+==============================================+==============================================================+
| ``pressio::is_expression<T>``                | Checks if ``T`` is any recognized Pressio expression (span,  |
|                                              | diagonal, subspan, or column).                               |
+----------------------------------------------+--------------------------------------------------------------+
| ``pressio::is_expression_span<T>``           | True if ``T`` is a SpanExpr.                                 |
+----------------------------------------------+--------------------------------------------------------------+
| ``pressio::is_expression_diagonal<T>``       | True if ``T`` is a DiagonalExpr.                             |
+----------------------------------------------+--------------------------------------------------------------+
| ``pressio::is_expression_subspan<T>``        | True if ``T`` is a SubspanExpr.                              |
+----------------------------------------------+--------------------------------------------------------------+
| ``pressio::is_expression_column<T>``         | True if ``T`` is a ColumnExpr.                               |
+----------------------------------------------+--------------------------------------------------------------+

Backend-Specific Expression Traits
-----------------------------------

These traits refine the detection to check whether a recognized expression type wraps a native container from a specific backend.

+------------------------------------------------------------+---------------------------------------------------------------------+
| Trait                                                      | Description                                                         |
+============================================================+=====================================================================+
| ``pressio::is_expression_acting_on_eigen<T>``              | True if ``T`` is a supported expression whose underlying container  |
|                                                            | is an Eigen type.                                                   |
+------------------------------------------------------------+---------------------------------------------------------------------+
| ``pressio::is_expression_acting_on_kokkos<T>``             | True if ``T`` is a supported expression whose underlying container  |
|                                                            | is a Kokkos type.                                                   |
+------------------------------------------------------------+---------------------------------------------------------------------+
| ``pressio::is_expression_acting_on_tpetra<T>``             | True if ``T`` is a ColumnExpr that wraps a Tpetra MultiVector.      |
+------------------------------------------------------------+---------------------------------------------------------------------+
| ``pressio::is_expression_column_acting_on_tpetra<T>``      | True if ``T`` is both a ColumnExpr and acts on a Tpetra MultiVector.|
+------------------------------------------------------------+---------------------------------------------------------------------+
| ``pressio::is_expression_acting_on_tpetra_block<T>``       | True if ``T`` is a ColumnExpr that wraps a Tpetra Block MultiVector.|
+------------------------------------------------------------+---------------------------------------------------------------------+
| ``pressio::is_expression_column_acting_on_tpetra_block<T>``| True if ``T`` is both a ColumnExpr and acts on a Tpetra Block       |
|                                                            | MultiVector.                                                        |
+------------------------------------------------------------+---------------------------------------------------------------------+

Notes
-----

- Each trait inherits from ``std::true_type`` or ``std::false_type`` and exposes a ``.value`` member for compile-time checks.
- These traits automatically handle ``const``-qualified types.
