.. include:: ../../mydefs.rst

``matrix-vector product``
=========================

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  // op(A) = A
  template <
    class A_type, class x_type, class y_type,
    class alpha_t, class beta_t
  >
  void product(::pressio::nontranspose /*unused*/,
	const alpha_t & alpha,
	const A_type & A,
	const x_type & x,
	const beta_t & beta,
	y_type & y);

  // op(A) = A , construct result
  template <
    class y_type, class A_type, class x_type, class alpha_t
  >
  y_type product(::pressio::nontranspose mode,
	const alpha_t & alpha,
	const A_type & A,
	const x_type & x);

  // op(A) = A^T
  template <
    class y_type, class A_type, class x_type, class alpha_t
  >
  void product(::pressio::transpose /*unused*/,
	const alpha_t & alpha,
	const A_type & A,
	const x_type & x,
	const beta_t & beta,
	y_type & y);

  // op(A) = A^T , construct result
  template <class y_type, class A_type, class x_type, class alpha_t>
  y_type product(::pressio::transpose mode,
	const alpha_t & alpha,
	const A_type & A,
	const x_type & x);

  }} // end namespace pressio::ops

Description
-----------

* Performs matrix-vector multiplication according to ``y = beta * y + alpha * op(A) * x``
  * ``op(A)`` indicates either ``A`` or ``A^T``

* ``alpha_t`` and ``beta_t`` are scalar types

* ``x_type`` and ``y_type`` are rank-1 containers

* ``A_type`` is a rank-2 container

* The following combinations of container types are supported for each ``A_type``:

  * Eigen

    * All container types are either Eigen containers or Pressio expressions of Eigen containers,

  * Epetra

    * ``A_type`` is an Epetra rank-2 container
    * Either ``x_type`` or ``y_type`` is a rank-1 Epetra container
    * The other non-Epetra container is a rank-1 Teuchos or Eigen container

  * Kokkos

    * All container types are either Kokkos views or Pressio expressions of Eigen views

  * Teuchos (does not support constructed results)

    * ``A_type`` is a rank-2 Teuchos container
    * ``x_type`` and ``y_type`` are rank-1 Eigen containers

  * Tpetra

    * ``A_type`` is a rank-2 Tpetra container

    * ``x_type`` is a rank-1 Eigen, Kokkos, Teuchos, or Tpetra container

    * ``y_type`` is a rank-1 container.
      If ``x_type`` is Tpetra, it may be either a Kokkos or Eigen container (or a Pressio expression of a Kokkos or Eigen container)
      Otherwise, ``y_type`` is a Tpetra container or a Pressio column expression

  * Tpetra Block

    * ``A_type`` is a rank-2 Tpetra Block container

    * ``x_type`` is a rank-1 Eigen, Kokkos, Teuchos, or Tpetra Block container

    * ``y_type`` is a rank-1 container.
      If ``x_type`` is a Tpetra Block vector, ``y_type`` may be either an Eigen vector or a rank-1 Kokkos view
      Otherwise, ``y_type`` is a Tpetra Block vector or column expression

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking that ``A_type``, ``x_type``, and ``y_type``` have the correct types.
