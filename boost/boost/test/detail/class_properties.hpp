//  (C) Copyright Gennadiy Rozental 2001-2003.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : simple facility that mimmic notion of read-only read-write 
//  properties in C++ classes. Original idea by Henrik Ravn.
// ***************************************************************************

#ifndef BOOST_TEST_CLASS_PROPERTIES_HPP
#define BOOST_TEST_CLASS_PROPERTIES_HPP

// BOOST
#include <boost/preprocessor/repetition/repeat.hpp> 
#include <boost/preprocessor/array/elem.hpp>

// ************************************************************************** //
// **************               readonly_property              ************** //
// ************************************************************************** //

#define DECLARE_FRIEND( z, count, array ) friend class BOOST_PP_ARRAY_ELEM(count, array);

#define BOOST_READONLY_PROPERTY( property_type, friends_num, friends )                                              \
class BOOST_JOIN( readonly_property, __LINE__ )                                                                     \
{                                                                                                                   \
    BOOST_PP_REPEAT( friends_num, DECLARE_FRIEND, (friends_num, friends) )                                          \
public:                                                                                                             \
    explicit BOOST_JOIN( readonly_property, __LINE__ )( property_type const& init_value  ) : value( init_value ) {} \
                                                                                                                    \
    operator                property_type const &() const       { return value; }                                   \
    property_type const&    get() const                         { return value; }                                   \
private:                                                                                                            \
    property_type           value;                                                                                  \
}

// ************************************************************************** //
// **************              readwrite_property              ************** //
// ************************************************************************** //

#define BOOST_READWRITE_PROPERTY( property_type )                                                                   \
class BOOST_JOIN( readwrite_property, __LINE__ )                                                                    \
{                                                                                                                   \
public:                                                                                                             \
             BOOST_JOIN( readwrite_property, __LINE__ )()        {}                                                 \
    explicit BOOST_JOIN( readwrite_property, __LINE__ )( property_type const& init_value  ) : value( init_value ) {}\
                                                                                                                    \
    operator                property_type const &() const       { return value; }                                   \
    property_type const&    get() const                         { return value; }                                   \
    void                    set( property_type const& v )       { value = v; }                                      \
private:                                                                                                            \
    property_type value;                                                                                            \
}

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.10  2003/06/09 08:39:28  rogeeff
//  1.30.beta1
//

// ***************************************************************************

#endif // BOOST_TEST_CLASS_PROPERTIES_HPP
