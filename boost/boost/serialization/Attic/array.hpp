#ifndef BOOST_SERIALIZATION_ARRAY_HPP
#define BOOST_SERIALIZATION_ARRAY_HPP

// (C) Copyright 2005 Matthias Troyer and Dave Abrahams
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/serialization/nvp.hpp>
#include <iostream>

namespace boost { namespace serialization {

template<class T>
class array
 : public traits<array<T>, object_serializable, track_never>
{
public:    
    explicit array(T* t, std::size_t s) :
        m_t(t),
        m_element_count(s)
    {}
    
    // default implementation
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) const
    {
      // default implemention does the loop
      std::size_t c = count();
      T * t = address();
      while(0 < c--)
            ar & make_nvp("item", *t++);
    }
    
    T* address() const
    {
      return m_t;
    }

    std::size_t count() const
    {
      return m_element_count;
    }
    
    
private:
    T* m_t;
    std::size_t const m_element_count;
};

template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
array<T> make_array( T* t, std::size_t s){
    return array<T>(t, s);
}

} } // end namespace boost::serialization

#endif //BOOST_SERIALIZATION_ARRAY_HPP
