//  (C) Copyright Joel de Guzman 2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies. This
//  software is provided "as is" without express or implied warranty, and
//  with no claim as to its suitability for any purpose.

#ifndef VECTOR_INDEXING_SUITE_JDG20036_HPP
# define VECTOR_INDEXING_SUITE_JDG20036_HPP

# include <boost/python/indexing/indexing_suite.hpp>

namespace boost { namespace python {
            
    // Forward declaration
    template <class Container, bool NoProxy, class DerivedPolicies>
    class vector_indexing_suite;
    
    namespace detail
    {
        template <class Container, bool NoProxy>
        class final 
            : public vector_indexing_suite<Container, 
                NoProxy, final<Container, NoProxy> > {};
    }

    // The vector_indexing_suite class is a predefined indexing_suite derived 
    // class for wrapping std::vector (and std::vector like) classes. It provides
    // all the policies required by the indexing_suite (see indexing_suite).
    // Example usage:
    //
    //  class X {...}
    //
    //  ...
    //
    //      class_<std::vector<X> >("XVec")
    //          .def(vector_indexing_suite<std::vector<X> >())
    //      ;
    //
    // By default indexed elements are returned by proxy. This can be
    // disabled by supplying *true* in the NoProxy template parameter.
    //
    template <
        class Container, 
        bool NoProxy = false,
        class DerivedPolicies = detail::final<Container, NoProxy> >
    class vector_indexing_suite 
        : public indexing_suite<Container, DerivedPolicies, NoProxy>
    {
    public:
    
        typedef typename Container::value_type element_type;
        typedef typename Container::size_type index_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::difference_type difference_type;
        
        static element_type& 
        get_item(Container& container, index_type i)
        { 
            return container[i];
        }

        static object 
        get_slice(Container& container, index_type from, index_type to)
        { 
            return object(Container(container.begin(), container.end()));
        }

        static void 
        set_item(Container& container, index_type i, element_type const& v)
        { 
            container[i] = v;
        }

        static void 
        set_slice(Container& container, index_type from, 
            index_type to, element_type const& v)
        { 
            container.erase(container.begin()+from, container.begin()+to);
            container.insert(container.begin()+from, v);
        }

        template <class Iter>
        static void 
        set_slice(Container& container, index_type from, 
            index_type to, Iter first, Iter last)
        { 
            container.erase(container.begin()+from, container.begin()+to);
            container.insert(container.begin()+from, first, last);
        }

        static void 
        delete_item(Container& container, index_type i)
        { 
            container.erase(container.begin()+i);
        }
        
        static void 
        delete_slice(Container& container, index_type from, index_type to)
        { 
            container.erase(container.begin()+from, container.begin()+to);
        }
        
        static size_t
        size(Container& container)
        {
            return container.size();
        }
        
        static index_type
        convert_index(Container& container, PyObject* i_)
        { 
            extract<long> i(i_);
            if (i.check())
            {
                long index = i();
                if (index < 0)
                    index += DerivedPolicies::size(container);
                if (index >= container.size() || index < 0)
                {
                    PyErr_SetString(PyExc_IndexError, "Index out of range");
                    throw_error_already_set();
                }
                return index;
            }
            
            PyErr_SetString(PyExc_TypeError, "Invalid index type");
            throw_error_already_set();
            return index_type();
        }
        
        static index_type
        adjust_index(index_type current, index_type from, 
            index_type to, size_type len)
        { 
            return current - (difference_type(to) - from - len);
        }
    };
       
}} // namespace boost::python 

#endif // VECTOR_INDEXING_SUITE_JDG20036_HPP
