Class ``ptr_deque``
--------------------

A ``ptr_deque<T>`` is a pointer container that uses an underlying ``std:deque<void*>``
to store the pointers. 

**See also:**

- reversible_ptr_container_
- ptr_sequence_adapter_

.. _reversible_ptr_container: reversible_ptr_container.html 
.. _ptr_map: ptr_map.html

**Navigate:**

- `home <ptr_container.html>`_
- `reference <reference.html>`_


**Synopsis:**

.. parsed-literal::  
           
        namespace boost
        {      
        
            template
            < 
                class T, 
                class CloneAllocator = heap_clone_allocator
                class Allocator      = std::allocator<void*>
            >
            class ptr_deque : public ptr_sequence_adapter
                                     <
                                        T,
                                        std::deque<void*,Allocator>,
                                        CloneAllocator
                                     >
            {

            public: // `element access`_
                T&        operator[]( size_type n );
                const T&  operator[]( size_type n ) const;
                T&        at( size_type n );
                const T&  at( size_type n ) const;
    
            public: // modifiers_
                void      push_front( T* x );
                auto_type pop_front();

            public: // `pointer container requirements`_
               auto_type replace( size_type idx, T* x );    
               bool      is_null( size_type idx ) const;   
    
            };

        } // namespace 'boost'  


.. _`reversible_ptr_container`: reversible_ptr_container.html 

.. _`ptr_sequence_adapter`: ptr_sequence_adapter.html

Semantics
---------

.. _modifiers:
 
Semantics: modifiers
^^^^^^^^^^^^^^^^^^^^

- ``void push_front( T* x );``

    - Requirements: ``x != 0``

    - Effects: Inserts the pointer into container and takes ownership of it
    
    - Throws: ``bad_pointer`` if ``x == 0``

    - Exception safety: Strong guarantee


.. 
        - ``void push_front( const T& x );``
    
        - Effects: push_front( allocate_clone( x ) );
    
        - Exception safety: Strong guarantee

- ``auto_type pop_front():``

    - Requirements:``not empty()``
    
    - Effects: Removes the first element in the container

    - Postconditions: ``size()`` is one less

    - Throws: ``bad_ptr_container_operation`` if ``empty() == true``
    
    - Exception safety: Strong guarantee


.. _`element access`:

Semantics: element access
^^^^^^^^^^^^^^^^^^^^^^^^^

- ``T& operator[]( size_type n );``
- ``const T& operator[]( size_type n ) const;``

    - Requirements: ``n < size()``

    - Effects: Returns a reference to the ``n``'th element

    - Throws: Nothing

- ``T& at( size_type n );``
- ``const T& at( size_type n ) const;``

    - Requirements: ``n < size()``

    - Effects: Returns a reference to the ``n``'th element

    - Throws: ``bad_index`` if ``n >=size()``


.. _`pointer container requirements`:

Semantics: pointer container requirements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- ``auto_type replace( size_type idx, T* x );``    

    - Requirements: `` x != 0 and idx < size()``

    - Effects: returns the object indexed by ``idx`` and replaces it with ``x``.

    - Throws: ``bad_index`` if ``idx >= size()`` and ``bad_pointer`` if ``x == 0``.

    - Exception safety: Strong guarantee

- ``bool is_null( size_type idx ) const;``

    - Requirements: ``idx < size()``

    - Effects: returns whether the pointer at index ``idx`` is null

    - Exception safety: Nothrow guarantee

