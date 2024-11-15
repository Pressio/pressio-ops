.. include:: ../../mydefs.rst

``min`` & ``max``
=================

Header: ``<pressio/ops.hpp>``

API
---

.. code-block:: cpp

  namespace pressio { namespace ops{

  template <typename T>
  scalar_type max(const T & obj);

  template<typename T>
  scalar_type min(const T & obj);

  }} // end namespace pressio::ops

Description
-----------

* Returns the maximum or minimum value of the given container

* Works for all container types other than Teuchos arrays
