//-----------------------------------------------------------------------------
// boost/type_traits/detail/type_trait_def.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

// no include guards, the header is intended for multiple inclusion!

#define BOOST_TT_AUX_TYPE_TRAIT_DEF1(trait,T,result) \
template< typename T > struct trait \
{ \
    typedef result type; \
}; \
/**/

#define BOOST_TT_AUX_TYPE_TRAIT_SPEC1(trait,spec,result) \
template<> struct trait<spec> \
{ \
    typedef result type; \
}; \
/**/

#define BOOST_TT_AUX_TYPE_TRAIT_PARTIAL_SPEC1_1(param,trait,spec,result) \
template< param > struct trait<spec> \
{ \
    typedef result type; \
}; \
/**/

#define BOOST_TT_AUX_TYPE_TRAIT_PARTIAL_SPEC1_2(param1,param2,trait,spec,result) \
template< param1, param2 > struct trait<spec> \
{ \
    typedef result; \
}; \
/**/


#if 0
#define BOOST_TT_AUX_TYPE_TRAIT_PARTIAL_SPEC1_1(param,trait,spec,result) \
template< param > struct trait<spec> \
    : boost::mpl::metafunction<1>
{ \
    typedef spec arg1;
    struct metafunction
    {
        template< typename U > struct apply
        {
            typedef typename trait<U>::type type;
        };
    };

    typedef result type; \
}; \
/**/

#endif
