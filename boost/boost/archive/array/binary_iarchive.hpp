#ifndef BOOST_ARCHIVE_ARRAY_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_ARRAY_BINARY_IARCHIVE_HPP

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// (C) Copyright 2005 Matthias Troyer. 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/archive/array/iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/type_traits/is_fundamental.hpp>

namespace boost { namespace archive { namespace array {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_iarchive_impl instead.  This will
// preserve correct static polymorphism.

class binary_iarchive : 
    public iarchive<binary_iarchive,binary_iarchive_impl<binary_iarchive> > 
{
public:
    binary_iarchive(std::istream & is, unsigned int flags = 0) :
        iarchive<binary_iarchive,binary_iarchive_impl<binary_iarchive> >(is, flags)
    {}
    
    // we provide an optimized load for all fundamental types
    
    typedef is_fundamental<mpl::_1> use_array_optimization;

    // the optimized load_array dispatches to load_binary 
    
    template <class ValueType>
    void load_array(ValueType* p, std::size_t n, unsigned int /* file_version */)
    {
      load_binary(p,n*sizeof(ValueType));
    }
};

} } } // end namespace boost::archive::array

// required by smart_cast for compilers not implementing 
// partial template specialization

BOOST_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION(boost::archive::array::binary_iarchive)

#endif // BOOST_ARCHIVE_ARRAY_BINARY_IARCHIVE_HPP
