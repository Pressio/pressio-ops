.. include:: ../../mydefs.rst

``span``
========

Header: ``<pressio/expressions.hpp>``

API
---

.. code-block:: cpp

  namespace pressio {

  template<class T>
  /*impl defined*/ span(T & operand,
                        std::pair<std::size_t, std::size_t> indexRange);

  } // end namespace pressio

Description
-----------

* Takes in an ``operand`` and an ``indexRange``

  * ``operand`` is either:

    * an Eigen vector object: ``pressio::is_vector_eigen<T>::value == true``

    * a Kokkos rank-1 view, i.e. ``pressio::is_vector_kokkos<T>::value == true``

  * ``indexRange`` is a std::pairidentifying an interval ``[a, b)`` where the second index is exclusive


* Returns an expression that represents the target span of the ``operand``.

