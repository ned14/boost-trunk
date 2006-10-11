/*=============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_ATTRIBUTE_TYPEOF_HPP)
#define BOOST_SPIRIT_ATTRIBUTE_TYPEOF_HPP

#include <boost/typeof/typeof.hpp>

#include <boost/spirit/core/typeof.hpp>

#include <boost/spirit/attribute/dynamic_scope_fwd.hpp>

namespace boost { namespace spirit {

    // parametric.hpp
    template<typename ChGenT>                        struct f_chlit;
    template<typename ChGenAT, typename ChGenBT>     struct f_range;
    template<typename IterGenAT, typename IterGenBT> struct f_chseq;
    template<typename IterGenAT, typename IterGenBT> struct f_strlit;

}} // namespace boost::spirit


#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()


// parametric.hpp

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::spirit::f_chlit,1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::spirit::f_range,2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::spirit::f_chseq,2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::spirit::f_strlit,2)


// dynamic_scope.hpp (has forward header)

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::spirit::dynamic_scope,BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::spirit::dynamic_scope_context,1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::spirit::init_dynamic_scope_context,1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::spirit::init_dynamic_scope_parser,2)

#endif

