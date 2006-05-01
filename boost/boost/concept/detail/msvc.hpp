// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# include <boost/preprocessor/cat.hpp>

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept/detail/has_constraints.hpp>
#  include <boost/mpl/if.hpp>
# endif


namespace boost { namespace concept {

template <class Model>
struct check
{
    virtual void failed(Model* x)
    {
        x->~Model();
    }
};
  
# ifdef BOOST_OLD_CONCEPT_SUPPORT
  
namespace detail
{
  // No need for a virtual function here, since evaluatiing
  // not_satisfied below will have already instantiated the
  // constraints() member.
  struct constraint {};
}
template <class Model>
struct require
  : mpl::if_c<
        not_satisfied<Model>::value
      , detail::constraint
      , check<Model>
        >::type
{};
      
# else
  
template <class Model>
struct require
  : check<Model>
{};
  
# endif
    
# if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

//
// The iterator library sees some really strange errors unless we
// use partial specialization to extract the model type with
// msvc-7.1
// 
template <class Model>
struct require<void(*)(Model)>
  : require<Model>
{};

# define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )      \
enum                                                \
{                                                   \
    BOOST_PP_CAT(boost_concept_check,__LINE__) =    \
    sizeof(::boost::concept::require<ModelFnPtr>)   \
}
  
# else // Not vc-7.1
  
template <class Model>
require<Model>
require_(void(*)(Model));
  
# define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )          \
enum                                                    \
{                                                       \
    BOOST_PP_CAT(boost_concept_check,__LINE__) =        \
      sizeof(::boost::concept::require_((ModelFnPtr)0)) \
}
  
# endif
}}

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
