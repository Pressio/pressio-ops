.. include:: ../../mydefs.rst

``column``
==========

Header: ``<pressio/expressions.hpp>``

API
---

.. code-block:: cpp

  namespace pressio {

  template <class T, class IndexType>
  /*impl defined*/ column(T & operand, IndexType colIndex);

  } // end namespace pressio

Description
-----------

* Takes in an ``operand``, as well as the index of the specified column ``colIndex``

  * ``operand`` is either:

    * an Eigen dense matrix

    * a Tpetra or Tpetra Block multivector

* Returns an expression object that represents the specified column from the ``operand``.
