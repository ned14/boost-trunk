// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BOOST_INDIRECT_ITERATOR_23022003THW_HPP
#define BOOST_INDIRECT_ITERATOR_23022003THW_HPP

#include <boost/iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/iterator/iterator_traits.hpp>

#include <boost/python/detail/indirect_traits.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/has_xxx.hpp>

#ifdef BOOST_NO_MPL_AUX_HAS_XXX
# include <boost/shared_ptr.hpp>
# include <boost/scoped_ptr.hpp>
# include <boost/mpl/bool.hpp>
# include <memory>
#endif 

#include <boost/iterator/detail/config_def.hpp> // must be last #include

namespace boost
{
  template <class Iter, class Value, class Category, class Reference, class Difference>
  struct indirect_iterator;

  namespace detail
  {
    struct unspecified {};

    //
    // Detection for whether a type has a nested `element_type'
    // typedef. Used to detect smart pointers. For compilers not
    // supporting mpl's has_xxx, we supply specializations. However, we
    // really ought to have a specializable is_pointer template which
    // can be used instead with something like
    // boost/python/pointee.hpp to find the value_type.
    //
# ifndef BOOST_NO_MPL_AUX_HAS_XXX
    namespace aux
    {
      BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)
    }

    template <class T>
    struct has_element_type
        : mpl::bool_<
              mpl::if_<
                  is_class<T>
                , ::boost::detail::aux::has_element_type<T>
                , mpl::false_
              >::type::value
          >
    {
    };
# else
    template <class T>
    struct has_element_type
        : mpl::false_ {};
    
    template <class T>
    struct has_element_type<boost::shared_ptr<T> >
        : mpl::true_ {};
    
    template <class T>
    struct has_element_type<boost::scoped_ptr<T> >
        : mpl::true_ {};
    
    template <class T>
    struct has_element_type<std::auto_ptr<T> >
        : mpl::true_ {};
# endif 
  
    // Metafunction returning the nested element_type typedef
    template <class T>
    struct smart_pointer_value : remove_const<typename T::element_type>
    {};

    template <class T>
    struct iterator_is_mutable
        : mpl::not_<
              boost::python::detail::is_reference_to_const<
                 typename iterator_reference<T>::type
              >
          >
    {
    };

    template <class T>
    struct not_int_impl
    {
        template <class U>
        struct apply {
            typedef T type;
        };
    };

    template <>
    struct not_int_impl<int> {};
    
    template <class T, class U>
    struct not_int
        : not_int_impl<T>::template apply<U> {};

    // If the Value parameter is unspecified, we use this metafunction
    // to deduce the default types
    template <class Iter, class Value, class Category, class Reference, class Difference>
    struct indirect_base
    {
        typedef typename iterator_value<Iter>::type dereferenceable;

        typedef mpl::and_<
            is_class<dereferenceable>
          , has_element_type<dereferenceable>
        > is_smart_ptr;

        typedef typename mpl::apply_if<
            is_smart_ptr
          , smart_pointer_value<dereferenceable>
          , iterator_value<dereferenceable>
        >::type value_type;

        typedef typename mpl::if_<
            mpl::or_<
                is_smart_ptr
              , iterator_is_mutable<dereferenceable>
            >
          , value_type
          , value_type const
        >::type cv_value_type;
           
        typedef iterator_adaptor<
            indirect_iterator<Iter, Value, Category, Reference, Difference>
          , Iter
          , cv_value_type
          , Category
          , Reference
          , Difference
        > type;
    };

    template <>
    struct indirect_base<int, int, int, int, int> {};
  } // namespace detail

  template <
      class Iterator
    , class Value = use_default
    , class Category = use_default
    , class Reference = use_default
    , class Difference = use_default
  >
  class indirect_iterator
    : public detail::indirect_base<
        Iterator, Value, Category, Reference, Difference
      >::type
  {
      typedef typename detail::indirect_base<
          Iterator, Value, Category, Reference, Difference
      >::type super_t;

      friend class iterator_core_access;

   public:
      indirect_iterator() {}

      indirect_iterator(Iterator iter)
        : super_t(iter) {}

      template <
          class Iterator2, class Value2, class Category2
        , class Reference2, class Difference2
      >
      indirect_iterator(
          indirect_iterator<
               Iterator2, Value2, Category2, Reference2, Difference2
          > const& y
        , typename enable_if_convertible<Iterator2, Iterator>::type* = 0
      )
        : super_t(y.base())
      {}

  private:    
      typename super_t::reference dereference() const
      {
# if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
          return const_cast<super_t::reference>(**this->base());
# else
          return **this->base();
# endif 
      }
  };

  template <class Iter>
  inline
  indirect_iterator<Iter> make_indirect_iterator(Iter x)
  {
    return indirect_iterator<Iter>(x);
  }

  template <class Traits, class Iter>
  inline
  indirect_iterator<Iter,Traits> make_indirect_iterator(Iter x, Traits* = 0)
  {
    return indirect_iterator<Iter, Traits>(x);
  }

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_INDIRECT_ITERATOR_23022003THW_HPP
