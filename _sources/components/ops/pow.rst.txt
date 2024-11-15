.. include:: ../../mydefs.rst

``pow``
=======

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  // x^exponent
  template <typename T>
  void pow(T & x, const scalar_type & exponent);

  // y = x^exponent
  template<typename T1, typename T2>
  void pow(T1 & y, const T2 & x, const scalar_type & exponent);

  // y = |x|^exponent (exponent > 0)
  template <class T1, class T2>
  abs_pow(T1 & y,
	const T2 & x,
	const typename ::pressio::Traits<T1>::scalar_type & exponent
  );

  // y = |x|^exponent (exponent < 0)
  template <class T1, class T2>
  abs_pow(T1 & y,
	const T2 & x,
	const typename ::pressio::Traits<T1>::scalar_type & exponent,
	const typename ::pressio::Traits<T1>::scalar_type & eps
  );

  }} // end namespace pressio::ops

Description
-----------

* Raises each element of a rank-1 container ``x`` to the specified power ``exponent``

* Stores the result in ``y`` if provided; otherwise, acts in place on ``x``

* ``x`` may be any type of rank-1 container other than a Teuchos vector
