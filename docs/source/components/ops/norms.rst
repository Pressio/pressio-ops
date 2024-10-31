.. include:: ../../mydefs.rst

``norms``
=========

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  // L1 Norm
  template <typename T>
  scalar_type norm1(const T & a);

  // L2 Norm
  template <typename T>
  scalar_type norm2(const T & a);

  }} // end namespace pressio::ops

Description
-----------

* Returns the desired norm of the given container ``a``

* L1 norm is given by

.. math::

    \| a \|_1 = \sum_{i} |a_i|

* L2 norm is given by:

.. math::

    \|\mathbf{a}\|_2 = \sqrt{\sum_{i=1}^{n} a_i^2}

* ``a`` must be rank-1 container of any type
