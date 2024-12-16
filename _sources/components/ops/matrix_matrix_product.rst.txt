.. include:: ../../mydefs.rst

``product`` (matrix-matrix)
===========================

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  // op(A) = A^T and op(B) = B
  template <
    class A_type, class B_type, class C_type,
    class alpha_t, class beta_t
  >
  void product(::pressio::transpose /*unused*/,
	::pressio::nontranspose /*unused*/,
	const alpha_t & alpha,
	const A_type & A,
	const B_type & B,
	const beta_t & beta,
	C_type & C);

  // op(A) = A and op(B) = B
  template <
    class A_type, class B_type, class C_type,
    class alpha_t, class beta_t
  >
  void product(::pressio::nontranspose /*unused*/,
	::pressio::nontranspose /*unused*/,
	const alpha_t & alpha,
	const A_type & A,
	const B_type & B,
	const beta_t & beta,
	C_type & C);

  // A == B and op(A) = A^T
  template <class A_type, class C_type, class alpha_t, class beta_t>
  void product(::pressio::transpose /*unused*/,
	::pressio::nontranspose /*unused*/,
	const alpha_t & alpha,
	const A_type & A,
	const beta_t & beta,
	C_type & C);

  // Construct result
  template <class C_type, class A_type, class alpha_t>
  C_type product(::pressio::transpose modeA,
	::pressio::nontranspose modeB,
	const alpha_t & alpha,
	const A_type & A);

  }} // end namespace pressio::ops

Description
-----------

* Performs matrix-vector multiplication according to ``C = beta * C + alpha * op(A) * op(B)``

  * ``op(X)`` indicates either ``X`` or ``X^T``

* ``alpha_t`` and ``beta_t`` are scalar types

* ``A_type``, ``B_type``, and ``C_type`` are rank-2 containers

Types
-----

The matrix-matrix product works for the following matrix types:

* Eigen (all containers are rank-2 Eigen matrices)

* Kokkos (all containers are rank-2 Kokkos views)

* Tpetra (``A`` and ``B`` are Tpetra multi-vectors; ``C`` is either a rank-2 Eigen matrix or a rank-2 Kokkos view)

* Tpetra Block (``A`` and ``B`` are Tpetra Block multi-vectors; ``C`` is either a rank-2 Eigen matrix or a rank-2 Kokkos view)

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking that ``A``, ``B``, and ``C``` have the correct types.
