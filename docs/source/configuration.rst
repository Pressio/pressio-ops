.. role:: raw-html-m2r(raw)
   :format: html

Configuration and Dependencies
==============================

Configuration
-------------

.. tip::

    pressio-ops is header-only, so it does not need to be precompiled and linked to.
    However, since we use preprocessor directives to conditionally
    enable/disable code based on target third-party libraries,
    one needs to account for this. See below for the details.

.. warning::

    To use pressio-ops, you need at least a C++17 compiler.

Dependencies
------------

Some parts contain code that are specific to third-party libraries (TPLs).
Currently, the list of TPLs supported is shown below:

.. list-table::
   :header-rows: 1
   :widths: 10 50 40
   :align: left

   * - TPL Name
     - Optional/Required
     - Version Known to Work/run in CI
   * - Eigen
     - Required
     - 3.4.0
   * - Trilinos
     - Optional
     - commits: 0dc4553, 5bbda25
   * - MPI
     - Optional
     - --
   * - Kokkos
     - Optional
     - 4.4.01
   * - BLAS
     - Optional
     - --
   * - LAPACK
     - Optional
     - --
   * - GoogleTest
     - Optional
     - 1.14.0

Eigen is the only required dependency because it is the
default choice for instantiating the ROM data structures
and solving the (dense) ROM problem used in `pressio <https://github.com/Pressio/pressio>`_.

CMake Keywords
~~~~~~~~~~~~~~

Enabling/disabling specific dependencies can be done via the following cmake variables:

.. list-table::
   :widths: 30 60 10
   :header-rows: 1
   :align: left

   * - Variable
     - Description
     - Default

   * - ``PRESSIO_ENABLE_TPL_EIGEN``
     - self-explanatory
     - ``ON``

   * - ``PRESSIO_ENABLE_TPL_TRILINOS``
     - self-explanatory
     - ``OFF``

   * - ``PRESSIO_ENABLE_TPL_MPI``
     - self-explanatory
     - ``OFF`` but automatically ``ON`` if ``PRESSIO_ENABLE_TPL_TRILINOS=ON``

   * - ``PRESSIO_ENABLE_TPL_KOKKOS``
     - self-explanatory
     - ``OFF`` but automatically ``ON`` if ``PRESSIO_ENABLE_TPL_TRILINOS=ON``

   * - ``PRESSIO_ENABLE_TEUCHOS_TIMERS``
     - self-explanatory
     - ``OFF`` but automatically ``ON`` if ``PRESSIO_ENABLE_TPL_TRILINOS=ON``


Obviously, the choice of which TPLs to enable is related to
your application's dependency requirements.
For example, if you have an application that relies on
Trilinos data structures and want to use ``pressio``\ ,
then it makes sense to enable the Trilinos dependency.
On the contrary, if you have an application that relies only on
Eigen data structures, then it makes sense to only leave only Eigen on
and disable the rest.

Also, we note that some of the cmake variables listed above are connected
and cannot be turned on individualy.
For example, if we enable Trilinos then ``pressio`` automatically
enables also Kokkos, BLAS, LAPACK and MPI.


.. important::

   All CMake keywords are prefixed with ``PRESSIO_`` which is case-sensitive.

   Recall that to set a keyword in CMake you used the syntax ``-Dkeyword_name``.
