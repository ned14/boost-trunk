+++++++++++++++++++
 Counting Iterator
+++++++++++++++++++

:Author: David Abrahams, Jeremy Siek, Thomas Witt
:Contact: dave@boost-consulting.com, jsiek@osl.iu.edu, witt@ive.uni-hannover.de
:organization: `Boost Consulting`_, Indiana University `Open Systems
               Lab`_, University of Hanover `Institute for Transport
               Railway Operation and Construction`_
:date: $Date$
:copyright: Copyright David Abrahams, Jeremy Siek, and Thomas Witt 2003. All rights reserved

.. _`Boost Consulting`: http://www.boost-consulting.com
.. _`Open Systems Lab`: http://www.osl.iu.edu
.. _`Institute for Transport Railway Operation and Construction`: http://www.ive.uni-hannover.de

:abstract: How would you fill up a vector with the numbers zero
  through one hundred using ``std::copy()``?  The only iterator
  operation missing from builtin integer types is an
  ``operator*()`` that returns the current value of the integer.
  The counting iterator adaptor adds this crucial piece of
  functionality to whatever type it wraps.  One can use the
  counting iterator adaptor not only with integer types, but with
  any type that is **Incrementable** (see type requirements
  below).

.. include:: counting_iterator_abstract.rst

.. contents:: Table of Contents

``counting_iterator`` synopsis
..............................

.. include:: counting_iterator_ref.rst
.. include:: make_counting_iterator.rst

.. include:: counting_iterator_eg.rst
