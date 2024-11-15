.. include:: ../../mydefs.rst

``update``
==========

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  // V = a * V + b * V1
  template<class T, class T1, class a_Type, class b_Type>
  void update(T & v,  const a_Type & a,
       const T1 & v1, const b_Type & b);

  // V = a * V + b * V1 + c * V2
  template<
    class T, class T1, class T2,
    class a_Type, class b_Type, class c_Type
  >
  void update(T & v,  const a_Type &a,
       const T1 & v1, const b_Type &b,
       const T2 & v2, const c_Type &c);

  // V = a * V + b * V1 + c * V2 + d * V3
  template<
    class T, class T1, class T2, class T3,
    class a_Type, class b_Type, class c_Type, class d_Type
  >
  void update(T & v,  const a_Type &a,
       const T1 & v1, const b_Type &b,
       const T2 & v2, const c_Type &c,
       const T3 & v3, const d_Type &d);

  // V = a * V + b * V1 + c * V2 + d * V3 + e * V4
  template<
    class T, class T1, class T2, class T3, class T4,
    class a_Type, class b_Type, class c_Type, class d_Type, class e_Type
  >
  void update(T & v,  const a_Type &a,
       const T1 & v1, const b_Type &b,
       const T2 & v2, const c_Type &c,
       const T3 & v3, const d_Type &d,
       const T4 & v4, const e_Type &e);

  // Rank-2 overload (Eigen and Kokkos only)
  // MV = a * MV + b * MV1
  template<typename T, typename T1, typename alpha_t, typename beta_t>
  void update(T & mv,  const alpha_t &a,
       const T1 & mv1, const beta_t &b)

  }} // end namespace pressio::ops


Description
-----------

* Performs a combined scaling and addition on vector ``v`` using the given scalars (``a``, ``b``, ... , ``e``) and auxiliary vectors (``v1``, ... , ``v4``)

* Stores the result in ``v``

* All vectors should have the same size and the same type. They may be:

  * Rank-1 or Rank-2 (see specific overload) Eigen containers or Pressio expressions of Eigen containers

  * Rank-1 Epetra containers

  * Rank-1 or Rank-2 (see specific overload) Kokkos containers or Pressio expressions of Kokkos containers

  * Rank-1 Tpetra containers or Pressio column expressions acting on Tpetra

  * Rank-1 Tpetra Block containers or Pressio column expressions acting on Tpetra Block

Notes
-----

* See the :doc:`ops homepage <../ops>` for a table of booleans to use when checking for the correct types.
