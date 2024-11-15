``expressions``
===============

Defined in header: ``<pressio/expressions.hpp>``

Public namespace: ``pressio``

We refer to these as expressions because each function does not allocate
new memory but only creates an instance of a class that "represents" the given operation.

In all cases, the returned expression remains valid until its operand goes out of scope.
If the operand goes out of scope, the state of the expression is undefined.

.. toctree::
   :maxdepth: 1

   expressions/span
   expressions/subspan
   expressions/diag
   expressions/column
   expressions/is_expression
