// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_CONVERTER_DWA200221_HPP
# define TO_PYTHON_CONVERTER_DWA200221_HPP

# include <boost/python/converter/registry.hpp>
# include <boost/python/converter/to_python_function.hpp>
# include <boost/python/converter/type_id.hpp>

namespace boost { namespace python { 

template <class T, class Derived>
struct to_python_converter
{
    to_python_converter();
};

//
// implementation
//

template <class T, class Derived>
to_python_converter<T,Derived>::to_python_converter()
{
    typedef converter::as_to_python_value_function<
        T, Derived
        > normalized;
        
    converter::registry::insert(
        &normalized::convert
        , converter::undecorated_type_id<T>());
}

}} // namespace boost::python

#endif // TO_PYTHON_CONVERTER_DWA200221_HPP
