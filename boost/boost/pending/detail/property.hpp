#ifndef BOOST_DETAIL_PROPERTY_HPP
#define BOOST_DETAIL_PROPERTY_HPP

#include <utility> // for std::pair

namespace boost {

  namespace detail {

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class Property1, class Property2>
    struct same_property {
      enum { value = int(property_num<Property1>::value) 
	     == int(property_num<Property2>::value) };
    };
#else
    template <class Property1, class Property2>
    struct same_property {
      enum { value = false };
    };
    template <class Property>
    struct same_property<Property,Property> {
      enum { value = true };
    };
#endif

    struct error_property_not_found { };

    template <int TagMatched>
    struct property_value_dispatch {
      template <class Property, class T, class Tag>
      inline static T& get_value(Property& p, T*, Tag) {
        return p.m_value; 
      }
      template <class Property, class T, class Tag>
      inline static const T& const_get_value(const Property& p, T*, Tag) {
        return p.m_value; 
      }
    };

    template <class Property>
    struct property_value_end {
      template <class T> struct result { typedef T type; };

      template <class T, class Tag>
      inline static T& get_value(Property& p, T* t, Tag tag) {
        typedef typename Property::next_type Next;
        typedef typename Next::tag_type Next_tag;
        enum { match = same_property<Next_tag,Tag>::value };
        return property_value_dispatch<match>
          ::get_value(static_cast<Next&>(p), t, tag);
      }
      template <class T, class Tag>
      inline static const T& const_get_value(const Property& p, T* t, Tag tag) {
        typedef typename Property::next_type Next;
        typedef typename Next::tag_type Next_tag;
        enum { match = same_property<Next_tag,Tag>::value };
        return property_value_dispatch<match>
          ::const_get_value(static_cast<const Next&>(p), t, tag);
      }
    };
    template <>
    struct property_value_end<no_property> {
      template <class T> struct result { 
	typedef detail::error_property_not_found type; 
      };

      // Stop the recursion and return error
      template <class T, class Tag>
      inline static detail::error_property_not_found&
      get_value(no_property&, T*, Tag) {
	static error_property_not_found s_prop_not_found;
        return s_prop_not_found;
      }
      template <class T, class Tag>
      inline static const detail::error_property_not_found&
      const_get_value(const no_property&, T*, Tag) {
	static error_property_not_found s_prop_not_found;
        return s_prop_not_found;
      }
    };

    template <>
    struct property_value_dispatch<0> {
      template <class Property, class T, class Tag>
      inline static typename property_value_end<Property>::template result<T>::type&
      get_value(Property& p, T* t, Tag tag) {
	return property_value_end<Property>::get_value(p, t, tag);
      }
      template <class Property, class T, class Tag>
      inline static const typename property_value_end<Property>::template result<T>::type&
      const_get_value(const Property& p, T* t, Tag tag) {
	return property_value_end<Property>::const_get_value(p, t, tag);
      }
    };

    template <class Property>
    struct build_property_tag_value_alist
    {
      typedef typename Property::next_type NextProperty;
      typedef typename Property::value_type Value;
      typedef typename Property::tag_type Tag;
      typedef typename build_property_tag_value_alist<NextProperty>::type Next;
      typedef std::pair< std::pair<Tag,Value>, Next> type;
    };
    template <>
    struct build_property_tag_value_alist<no_property>
    {
      typedef no_property type;
    };

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <class TagValueAList, class Tag>
    struct extract_value {
      typedef error_property_not_found type;
    };
    template <class Value, class Tag1, class Tag2, class Rest>
    struct extract_value< std::pair<std::pair<Tag1,Value>,Rest>, Tag2> {
      typedef typename extract_value<Rest,Tag2>::type type;
    };
    template <class Value, class Tag, class Rest>
    struct extract_value< std::pair<std::pair<Tag,Value>,Rest>, Tag> {
      typedef Value type;
    };
#else
    // VC++ workaround:
    // The main idea here is to replace partial specialization with
    // nested template member classes. Of course there is the
    // further complication that the outer class of the nested
    // template class cannot itself be a template class.
    // Hence the need for the ev_selector. -JGS

    struct recursive_extract;
    struct end_extract;

    template <class TagValueAList>
    struct ev_selector { typedef recursive_extract type; };
    template <>
    struct ev_selector<no_property> { typedef end_extract type; };

    struct recursive_extract {
      template <class TagValueAList, class Tag1>
      struct bind {
        typedef typename TagValueAList::first_type AListFirst;
        typedef typename AListFirst::first_type Tag2;
        typedef typename AListFirst::second_type Value;
        enum { match = same_property<Tag1,Tag2>::value };
        typedef typename TagValueAList::second_type Next;
        typedef typename ev_selector<Next>::type Extractor;
        typedef typename boost::ct_if< match, Value, 
          typename Extractor::template bind<Next,Tag1>::type
        >::type type;
      };
    };
    struct end_extract {
      template <class AList, class Tag1>
      struct bind {
        typedef error_property_not_found type;
      };
    };
#endif //!defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  } // namespace detail 
} // namespace boost

#endif // BOOST_DETAIL_PROPERTY_HPP
