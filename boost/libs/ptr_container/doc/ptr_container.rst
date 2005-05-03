
++++++++++++++++++++++++++++++++++
 |Boost| Pointer Container Library
++++++++++++++++++++++++++++++++++
 
.. |Boost| image:: cboost.gif
   


:Authors:       Thorsten Ottosen
:Contact:       nesotto@cs.auc.dk
:organizations: `Department of Computer Science`_, Aalborg University, and `Dezide Aps`_
:date:          3rd of May 2005
:copyright:     Thorsten Ottosen 2004-2005. Use, modification and distribution is subject to the Boost Software License, Version 1.0 (see LICENSE_1_0.txt__).

__ http://www.boost.org/LICENSE_1_0.txt
 
.. _`Department of Computer Science`: http://www.cs.auc.dk
.. _`Dezide Aps`: http://www.dezide.com

========
Overview
========

Boost.Pointer Container provides containers for holding heap-allocated
objects in an exception-safe manner and with minimal overhead. 
The aim of the library is in particular to make OO programming
easier in C++ by establishing a standard set of classes, methods 
and designs for dealing with OO specific problems

* Motivation_
* Tutorial_
* Reference_

  - `Conventions <reference.html#conventions>`_
  - `The Clonable Concept <reference.html#the-clonable-concept>`_ 
  - `The Clone Allocator Concept <reference.html#the-clone-allocator-concept>`_ 
  - `Pointer container adapters <reference.html#pointer-container-adapters>`_ 
  - `Sequence container classes <reference.html#sequence-containers>`_

    - `ptr_vector <ptr_vector.html>`_
    - `ptr_deque <ptr_deque.html>`_
    - `ptr_list <ptr_list.html>`_
    - `ptr_array <ptr_array.html>`_
  - `Associative container classes  <reference.html#associative-containers>`_

    - `ptr_set <ptr_set.html>`_
    - `ptr_multiset <ptr_multiset.html>`_
    - `ptr_map <ptr_map.html>`_
    - `ptr_multimap <ptr_multimap.html>`_   
  - `Indirected functions <indirect_fun.html>`_ 
  - `Class nullable <reference.html#class-nullable>`_
  - `Exception classes <reference.html#exception-classes>`_         
* `Usage guidelines`_
* Examples_
* `Library headers`_
* FAQ_
* Acknowledgements_ 
* References_ 


.. _Tutorial: tutorial.html


.. _Reference: reference.html

.. _`Usage guidelines`: guidelines.html

.. _Examples: examples.html

.. _`Library headers`: headers.html

.. _FAQ: faq.html 


==========
Motivation
==========

Whenever a programmer wants to have a container of pointers to 
heap-allocated objects, there is usually only one exception-safe way:
to make a container of pointer pointers like ``boost::shared_ptr``.
This approach is suboptimal if

1. the stored objects are not shared, but owned exclusively, or
2. the overhead implied by pointer pointers is inappropriate

This library therefore provides standard-like containers that are for storing 
heap-allocated or `cloned <reference.html#the-clonable-concept>`_ objects (or in case of a map, the mapped object must be 
a heap-allocated or cloned object). For each of the standard 
containers there is a pointer container equivalent that takes ownership of 
the objects in an exception safe manner.  In this respect the library is intended 
to solve the so-called 
`polymorphic class problem <faq.html#what-is-the-polymorphic-class-problem>`_. 


The advantages of pointer containers are

1. Exception-safe pointer storage and manipulation.
2. Notational convenience compared to the use of containers of pointers.
3. Can be used for types that are neither Assignable nor Copy Constructible. 
4. No memory-overhead as containers of pointer pointers can have (see [11]_ and [12]_).
5. Usually faster than using containers of pointer pointers (see [11]_ and [12]_). 
6. The interface is slightly changed towards the domain of pointers  
   instead of relying on the normal value-based interface. For example,
   now it is possible for ``pop_back()`` to return the removed element. 

The disadvantages are

1. Less flexible than containers of pointer pointers
  
================
Acknowledgements
================

The following people have been helpful:

- Bj�rn D. Rasmussen for showing me his cr**** code that motivated me to start this library
- Pavel Vozenilek for asking me to make the adapters
- David Abrahams for the ``indirect_fun`` design
- Pavol Droba for being review manager
- Ross Boylan for trying out a prototype for real
- Felipe Magno de Almeida for giving fedback based on using the
  library in production code even before the library was part of boost  
- Jonathan Turkanis for supplying his ``move_ptr`` framework 
  which is used internally
- Stefan Slapeta and Howard Hinnant for Metrowerks support

==========
References
==========

.. [1] Matt Austern: `"The Standard Librarian: Containers of Pointers"`__ , C/C++ Users Journal Experts Forum.

__ http://www.cuj.com/documents/s=7990/cujcexp1910austern/

.. [2] Bjarne Stroustrup, "The C++ Programming Language", `Appendix E: "Standard-Library Exception Safety"`__

__ http://www.research.att.com/~bs/3rd_safe.pdf

.. [3] Herb Sutter, "Exceptional C++".
.. [4] Herb Sutter, "More Exceptional C++".
.. [5] Kevlin Henney: `"From Mechanism to Method: The Safe Stacking of Cats"`__ , C++ Experts Forum, February 2002.

__ http://www.cuj.com/documents/s=7986/cujcexp2002henney/henney.htm

.. [6] Some of the few earlier attempts of pointer containers I have seen are the rather interesting NTL_ and the 
       pointainer_. 
       As of this writing both libraries are not exceptions-safe and can leak.

.. [7] INTERNATIONAL STANDARD, Programming languages --- C++, ISO/IEC 14882, 1998. See section 23 in particular.
.. [8] C++ Standard Library Closed Issues List (Revision 27), 
       Item 218, `Algorithms do not use binary predicate objects for default comparisons`__.

__ http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/lwg-closed.html#218       
 
.. [9] C++ Standard Library Active Issues List (Revision 27), 
       Item 226, `User supplied specializations or overloads of namespace std function templates`__. 

__ http://gcc.gnu.org/onlinedocs/libstdc++/ext/lwg-active.html#226

.. [10] Harald Nowak, "A remove_if for vector", C/C++ Users Journal, July 2001.
.. [11] Boost smart pointer timings__

__ http://www.boost.org/libs/smart_ptr/smarttests.htm
 
.. [12] NTL_: Array vs std::vector and boost::shared_ptr 
.. [13] Kevlin Henney, `Null Object`__, 2002.

__ http://www.two-sdg.demon.co.uk/curbralan/papers/europlop/NullObject.pdf

.. _NTL: http://www.ntllib.org/asp.html
.. _pointainer: http://ootips.org/yonat/4dev/pointainer.h 


:copyright:     Thorsten Ottosen 2004-2005. 

