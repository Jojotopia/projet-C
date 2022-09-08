Rules project
==============

Installation
------------

Use ``brew`` and not ``apt`` if you are on macos!

.. code:: bash

   $ sudo apt install cmake gcc lcov python-pip valgrind doxygen dot
   $ [sudo] pip install [--user] -r rules/docs/requirements.txt

Usage
-----

Compilation
~~~~~~~~~~~

.. code:: bash

   $ mkdir build
   $ cd build
   $ cmake ../rules -DUSE_VALGRIND=1
   $ make

Run app
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: bash

   $ src/rules --rules <rules_file> --facts <facts_file> --output <output_file>

Run test
~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: bash

   $ make test

Check style
~~~~~~~~~~~

.. code:: bash

   $ make cclint

Build the docs
~~~~~~~~~~~~~~

.. code:: bash

   $ make docs

Create archives
~~~~~~~~~~~~~~~

.. code:: bash

   $ make package
   $ make package_source

Install package
~~~~~~~~~~~~~~~

.. code:: bash

   $ make install
