// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_AUX_DATA_DWA2002128_HPP
# define FROM_PYTHON_AUX_DATA_DWA2002128_HPP

# include <boost/python/detail/char_array.hpp>
# include <boost/mpl/select_type.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/type_traits/alignment_traits.hpp>
# include <boost/type_traits/transform_traits.hpp>
# include <boost/static_assert.hpp>
# include <boost/python/converter/from_python_stage1_data.hpp>

// Keep these for the metaprogram which EDG is choking on.
# if !defined(__EDG__) || (__EDG_VERSION__ > 245)
#  include <boost/mpl/type_list.hpp>
#  include <boost/mpl/for_each.hpp>
#  include <boost/type_traits/composite_traits.hpp>
# else
#  include <boost/type_traits/cv_traits.hpp>
# endif 

namespace boost { namespace python { namespace converter { 

namespace detail
{
  template <class T> struct referent_alignment;
  template <class T> struct referent_size;
  
# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
  
  template <class T>
  struct referent_alignment<T&>
  {
      BOOST_STATIC_CONSTANT(
          std::size_t, value = alignment_of<T>::value);
  };

  template <class T>
  struct referent_size<T&>
  {
      BOOST_STATIC_CONSTANT(
          std::size_t, value = sizeof(T));
  };

# else

  template <class U>
  struct alignment_chars
  {
      BOOST_STATIC_CONSTANT(
          std::size_T, n = alignment_of<U>::value);
      char elements[n + 1];
  };

  template <class T> struct referent_alignment
  {
      template <class U>
      static alignment_chars<U> helper(U&);
  
      static T t;
      
      BOOST_STATIC_CONSTANT(
          std::size_t, value = sizeof(helper(t).elements) - 1);
  };

  
  template <class T> struct referent_size
  {
      static T f();
      BOOST_STATIC_CONSTANT(std::size_t, value = sizeof(f()));
  };
  
# endif

  struct unknown_alignment
  {
      void* p;
  };
  
// EDG is too slow to handle this metaprogram :(  
#if !defined(__EDG__) || (__EDG_VERSION__ > 245)
  struct alignment_dummy;

  template <std::size_t target_alignment>
  struct best_alignment_type
  {
      template <class T1, class T2>
      struct apply
      {
          BOOST_STATIC_CONSTANT(
              std::size_t, align1 = alignment_of<T1>::value);
          
          BOOST_STATIC_CONSTANT(
              std::size_t, align2 = alignment_of<T2>::value);
          
          BOOST_STATIC_CONSTANT(
              bool, aligned2 = (
                  (align2 >= target_alignment)
                  & (align2 % target_alignment == 0))
              );
          
          BOOST_STATIC_CONSTANT(
              bool, choose_t2 = (
                  aligned2 && (
                      is_same<T1,unknown_alignment>::value
                      | (align2 < align1)
                      | (sizeof(T2) < sizeof(T1)))
                  ));
          
          typedef typename mpl::select_type<choose_t2, T2, T1>::type type;
      };
  };

  typedef mpl::type_list<
      char,short,int,long, float,double,long double
      ,void*
      ,void(*)()
      ,void (alignment_dummy::*)()
      , char (alignment_dummy::*)
  >::type
  align_types;
#endif // EDG is too slow  
  template <class Align, std::size_t size>
  union aligned_storage
  {
      Align align;
      char bytes[size
                 // this is just a STATIC_ASSERT. For some reason
                 // MSVC was barfing on the boost one.
                 - (is_same<Align,unknown_alignment>::value ? size : 0)];
  };

  template <class Reference>
  struct referent_storage
  {
// EDG is too slow to handle this metaprogram :(  
#if !defined(__EDG__) || (__EDG_VERSION__ > 245)
      typedef mpl::for_each<
          align_types
          , unknown_alignment
          , best_alignment_type<
          referent_alignment<Reference>::value
      >
      > loop;
    
      typedef typename loop::state align_t;
#else
      typedef typename remove_cv<typename remove_reference<Reference>::type>::type referent;
      
      // The Python source makes the assumption that double has
      // maximal alignment, but that fails on some platforms
      BOOST_STATIC_CONSTANT(
          std::size_t, target_align = alignment_of<referent>::value);

      // Here we make some assumptions and leave out some possible
      // types worth checking, but this should work most of the time.
      typedef typename mpl::select_type<
          is_POD<referent>::value
          , referent
          , typename mpl::select_type< 
              alignment_of<long>::value >= target_align
              , long
              , typename mpl::select_type<
                  alignment_of<double>::value >= target_align
                  , double
                  , long double>::type
          >::type
      >::type align_t;
#endif
      BOOST_STATIC_CONSTANT(std::size_t, alignment1 = alignment_of<align_t>::value);
      BOOST_STATIC_CONSTANT(std::size_t, alignment2 = referent_alignment<Reference>::value);
    
      BOOST_STATIC_ASSERT(alignment1 >= alignment2);
      BOOST_STATIC_ASSERT(alignment1 % alignment2 == 0);
    
      typedef aligned_storage<align_t,referent_size<Reference>::value> type;
  };
  
}

template <class T>
struct rvalue_data
{
    rvalue_stage1_data stage1;
    
    typename detail::referent_storage<
        typename add_reference<T>::type
    >::type storage;
};

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_AUX_DATA_DWA2002128_HPP
