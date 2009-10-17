.. Copyright David Abrahams 2006. Distributed under the Boost
.. Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

Boost.Build_ is a text-based system for developing, testing, and
installing software.  To use it, you'll need an executable called
``bjam``.

.. |precompiled-bjam| replace:: download a pre-built ``bjam`` executable


.. _precompiled-bjam: http://sourceforge.net/project/showfiles.php?group_id=7586&package_id=72941
.. .. _Boost.Jam documentation: Boost.Jam_
.. _Boost.Build: ../../tools/build/index.html
.. _Boost.Jam: ../../tools/jam/index.html
.. _Boost.Build documentation: Boost.Build_

Get ``bjam``
............

``bjam`` is the |command-line tool| that drives the Boost Build
system.  To build Boost binaries, you'll invoke ``bjam`` from the
Boost root.  

We suggest you |precompiled-bjam|_ for your platform.
Alternatively, you can build ``bjam`` yourself using `these
instructions`__.

__ `building bjam`_

Move the ``bjam`` executable into a directory in your PATH.  You can
see the list of directories in your PATH, separated by |pathsep|\ s,
by typing “\ |path|\ ” at the command prompt.

.. _toolset:
.. _toolset-name:

Identify Your Toolset
.....................

First, find the toolset corresponding to your compiler in the
following table (an up-to-date list is always available `in the
Boost.Build documentation`__).

__ http://www.boost.org/boost-build2/doc/html/bbv2/reference/tools.html

.. Note:: If you previously chose a toolset for the purposes of
  `building bjam`_, you should assume it won't work and instead
  choose newly from the table below.

.. _building bjam: ../../doc/html/jam/building.html

+-----------+--------------------+-----------------------------+
|Toolset    |Vendor              |Notes                        |
|Name       |                    |                             |
+===========+====================+=============================+
|``acc``    |Hewlett Packard     |Only very recent versions are|
|           |                    |known to work well with Boost|
+-----------+--------------------+-----------------------------+
|``borland``|Borland             |                             |
+-----------+--------------------+-----------------------------+
|``como``   |Comeau Computing    |Using this toolset may       |
|           |                    |require configuring__ another|
|           |                    |toolset to act as its backend|
+-----------+--------------------+-----------------------------+
|``cw``     |Metrowerks/Freescale|The CodeWarrior compiler.  We|
|           |                    |have not tested versions of  |
|           |                    |this compiler produced since |
|           |                    |it was sold to Freescale.    |
+-----------+--------------------+-----------------------------+
|``dmc``    |Digital Mars        |As of this Boost release, no |
|           |                    |version of dmc is known to   |
|           |                    |handle Boost well.           |
+-----------+--------------------+-----------------------------+
|``darwin`` |Apple Computer      |Apple's version of the GCC   |
|           |                    |toolchain with support for   |
|           |                    |Darwin and MacOS X features  |
|           |                    |such as frameworks.          |
+-----------+--------------------+-----------------------------+
|``gcc``    |The Gnu Project     |Includes support for Cygwin  |
|           |                    |and MinGW compilers.         |
+-----------+--------------------+-----------------------------+
|``hp_cxx`` |Hewlett Packard     |Targeted at the Tru64        |
|           |                    |operating system.            |
+-----------+--------------------+-----------------------------+
|``intel``  |Intel               |                             |
+-----------+--------------------+-----------------------------+
|``msvc``   |Microsoft           |                             |
+-----------+--------------------+-----------------------------+
|``qcc``    |QNX Software Systems|                             |
+-----------+--------------------+-----------------------------+
|``sun``    |Sun                 |Only very recent versions are|
|           |                    |known to work well with      |
|           |                    |Boost.                       |
+-----------+--------------------+-----------------------------+
|``vacpp``  |IBM                 |The VisualAge C++ compiler.  |
+-----------+--------------------+-----------------------------+

__ Boost.Build_

If you have multiple versions of a particular compiler installed,
you can append the version number to the toolset name, preceded by
a hyphen, e.g. ``intel-9.0`` or
``borland-5.4.3``. |windows-version-name-caveat|


.. _build directory:
.. _build-directory:

Select a Build Directory
........................

Boost.Build_ will place all intermediate files it generates while
building into the **build directory**.  If your Boost root
directory is writable, this step isn't strictly necessary: by
default Boost.Build will create a ``bin.v2/`` subdirectory for that
purpose in your current working directory.

Invoke ``bjam``
...............

.. |build-directory| replace:: *build-directory*
.. |toolset-name| replace:: *toolset-name*

Change your current directory to the Boost root directory and
invoke ``bjam`` as follows:

.. parsed-literal::

  bjam **--build-dir=**\ |build-directory|_ **toolset=**\ |toolset-name|_ |build-type-complete| stage

For a complete description of these and other invocation options,
please see the `Boost.Build documentation`__.

__ http://www.boost.org/boost-build2/doc/html/bbv2/advanced/invocation.html

