//  boost cast.hpp header file  ----------------------------------------------//

//  (C) Copyright boost.org 1999. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  02 Apr 01  Removed BOOST_NO_LIMITS workarounds and included 
//             <boost/limits.hpp> instead (the workaround did not 
//             actually compile when BOOST_NO_LIMITS was defined in 
//             any case, so we loose nothing). (John Maddock)
//  21 Jan 01  Undid a bug I introduced yesterday. numeric_cast<> never
//             worked with stock GCC; trying to get it to do that broke
//             vc-stlport.
//  20 Jan 01  Moved BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS to config.hpp.
//             Removed unused BOOST_EXPLICIT_TARGET macro. Moved
//             boost::detail::type to boost/type.hpp. Made it compile with
//             stock gcc again (Dave Abrahams)
//  29 Nov 00  Remove nested namespace cast, cleanup spacing before Formal
//             Review (Beman Dawes)
//  19 Oct 00  Fix numeric_cast for floating-point types (Dave Abrahams)
//  15 Jul 00  Suppress numeric_cast warnings for GCC, Borland and MSVC
//             (Dave Abrahams)
//  30 Jun 00  More MSVC6 wordarounds.  See comments below.  (Dave Abrahams)
//  28 Jun 00  Removed implicit_cast<>.  See comment below. (Beman Dawes)
//  27 Jun 00  More MSVC6 workarounds 
//  15 Jun 00  Add workarounds for MSVC6
//   2 Feb 00  Remove bad_numeric_cast ";" syntax error (Doncho Angelov)
//  26 Jan 00  Add missing throw() to bad_numeric_cast::what(0 (Adam Levar)
//  29 Dec 99  Change using declarations so usages in other namespaces work
//             correctly (Dave Abrahams)
//  23 Sep 99  Change polymorphic_downcast assert to also detect M.I. errors
//             as suggested Darin Adler and improved by Valentin Bonnard.  
//   2 Sep 99  Remove controversial asserts, simplify, rename.
//  30 Aug 99  Move to cast.hpp, replace value_cast with numeric_cast,
//             place in nested namespace.
//   3 Aug 99  Initial version

#ifndef BOOST_CAST_HPP
#define BOOST_CAST_HPP

# include <boost/config.hpp>
# include <cassert>
# include <typeinfo>
# include <boost/type.hpp>
# include <boost/limits.hpp>

//  It has been demonstrated numerous times that MSVC 6.0 fails silently at link
//  time if you use a template function which has template parameters that don't
//  appear in the function's argument list.
//
//  TODO: Add this to config.hpp?
# if defined(BOOST_MSVC) && BOOST_MSVC <= 1200 // 1200 = VC6
#  define BOOST_EXPLICIT_DEFAULT_TARGET , ::boost::type<Target>* = 0
# else
#  define BOOST_EXPLICIT_DEFAULT_TARGET
# endif

namespace boost
{
//  See the documentation for descriptions of how to choose between
//  static_cast<>, dynamic_cast<>, polymorphic_cast<> and polymorphic_downcast<>

//  polymorphic_cast  --------------------------------------------------------//

    //  Runtime checked polymorphic downcasts and crosscasts.
    //  Suggested in The C++ Programming Language, 3rd Ed, Bjarne Stroustrup, 
    //  section 15.8 exercise 1, page 425.

    template <class Target, class Source>
    inline Target polymorphic_cast(Source* x BOOST_EXPLICIT_DEFAULT_TARGET)
    {
        Target tmp = dynamic_cast<Target>(x);
        if ( tmp == 0 ) throw std::bad_cast();
        return tmp;
    }

//  polymorphic_downcast  ----------------------------------------------------//

    //  assert() checked polymorphic downcast.  Crosscasts prohibited.

    //  WARNING: Because this cast uses assert(), it violates the One Definition
    //  Rule if NDEBUG is inconsistently defined across translation units.

    //  Contributed by Dave Abrahams

    template <class Target, class Source>
    inline Target polymorphic_downcast(Source* x BOOST_EXPLICIT_DEFAULT_TARGET)
    {
        assert( dynamic_cast<Target>(x) == x );  // detect logic error
        return static_cast<Target>(x);
    }

//  implicit_cast  -----------------------------------------------------------//
//
//  Removed due to uncertain purpose.  Use either numeric_cast (see below)
//  or static_cast according to the need. 

//  numeric_cast and related exception  --------------------------------------//

//  Contributed by Kevlin Henney

//  bad_numeric_cast  --------------------------------------------------------//

    // exception used to indicate runtime numeric_cast failure
    class bad_numeric_cast : public std::bad_cast
    {
    public:
        // constructors, destructors and assignment operator defaulted

        // function inlined for brevity and consistency with rest of library
        virtual const char *what() const throw()
        {
            return "bad numeric cast: loss of range in numeric_cast";
        }
    };

//  numeric_cast  ------------------------------------------------------------//

#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
  
    namespace detail
    {
       template <bool is_signed> struct numeric_min_select;
    
       template<>
       struct numeric_min_select<true>
       {
         template <class T>
         struct limits : std::numeric_limits<T>
         {
    	   static inline T min()
# ifndef __GNUC__ // bug workaround courtesy Jens Maurer
             {
                 return std::numeric_limits<T>::min() >= 0
                     // unary minus causes integral promotion, thus the static_cast<>
                     ? static_cast<T>(-std::numeric_limits<T>::max())
                     : std::numeric_limits<T>::min();
             }
# else
                 ;
# endif
	       };
       };

# ifdef __GNUC__ // bug workaround courtesy Jens Maurer
      template<> template<class T>
      inline T numeric_min_select<true>::limits<T>::min()
      {
           return std::numeric_limits<T>::min() >= 0
               // unary minus causes integral promotion, thus the static_cast<>
               ? static_cast<T>(-std::numeric_limits<T>::max())
               : std::numeric_limits<T>::min();
      }
# endif
    
      template<>
      struct numeric_min_select<false>
      {
          template <class T>
          struct limits : std::numeric_limits<T> {};
      };
      
      // Move to namespace boost in utility.hpp?
      template <class T>
      struct fixed_numeric_limits
          : public numeric_min_select<
                       std::numeric_limits<T>::is_signed 
                   >::template limits<T>
      {
      };
    } // namespace detail
  
// less_than_type_min -
  //    x_is_signed should be numeric_limits<X>::is_signed
  //    y_is_signed should be numeric_limits<Y>::is_signed
  //    y_min should be numeric_limits<Y>::min()
  //
  //    check(x, y_min) returns true iff x < y_min without invoking comparisons
  //    between signed and unsigned values.
  //
  //    "poor man's partial specialization" is in use here.
    template <bool x_is_signed, bool y_is_signed>
    struct less_than_type_min
    {
        template <class X, class Y>
        static bool check(X x, Y y_min)
            { return x < y_min; }
    };

    template <>
    struct less_than_type_min<false, true>
    {
        template <class X, class Y>
        static bool check(X, Y)
            { return false; }
    };
    
    template <>
    struct less_than_type_min<true, false>
    {
        template <class X, class Y>
        static bool check(X x, Y)
            { return x < 0; }
    };
    
  // greater_than_type_max -
  //    same_sign should be:
  //            numeric_limits<X>::is_signed == numeric_limits<Y>::is_signed
  //    y_max should be numeric_limits<Y>::max()
  //
  //    check(x, y_max) returns true iff x > y_max without invoking comparisons
  //    between signed and unsigned values.
  //
  //    "poor man's partial specialization" is in use here.
    template <bool same_sign, bool x_is_signed>
    struct greater_than_type_max;

    template<>
    struct greater_than_type_max<true, true>
    {
        template <class X, class Y>
        static inline bool check(X x, Y y_max)
            { return x > y_max; }
    };

    template <>
    struct greater_than_type_max<false, true>
    {
        // What does the standard say about this? I think it's right, and it
        // will work with every compiler I know of.
        template <class X, class Y>
        static inline bool check(X x, Y)
            { return x >= 0 && static_cast<X>(static_cast<Y>(x)) != x; }
    };

    template<>
    struct greater_than_type_max<true, false>
    {
        template <class X, class Y>
        static inline bool check(X x, Y y_max)
            { return x > y_max; }
    };

    template <>
    struct greater_than_type_max<false, false>
    {
        // What does the standard say about this? I think it's right, and it
        // will work with every compiler I know of.
        template <class X, class Y>
        static inline bool check(X x, Y)
            { return static_cast<X>(static_cast<Y>(x)) != x; }
    };
  
#else // use #pragma hacks if available

  namespace detail
  {
# if BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4018)
#  pragma warning(disable : 4146)
#elif defined(__BORLANDC__)
#  pragma option push -w-8041
# endif

       // Move to namespace boost in utility.hpp?
       template <class T>
       struct fixed_numeric_limits : public std::numeric_limits<T>
       {
           static inline T min()
           {
               return std::numeric_limits<T>::is_signed && std::numeric_limits<T>::min() >= 0
                   ? T(-std::numeric_limits<T>::max()) : std::numeric_limits<T>::min();
           }
       };
  
# if BOOST_MSVC
#  pragma warning(pop)
#elif defined(__BORLANDC__)
#  pragma option pop
# endif
  } // namespace detail
  
#endif
  
    template<typename Target, typename Source>
    inline Target numeric_cast(Source arg BOOST_EXPLICIT_DEFAULT_TARGET)
    {
        // typedefs abbreviating respective trait classes
        typedef std::numeric_limits<Source> arg_traits;
        typedef detail::fixed_numeric_limits<Target> result_traits;
        
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
        // typedefs that act as compile time assertions
        // (to be replaced by boost compile time assertions
        // as and when they become available and are stable)
        typedef bool argument_must_be_numeric[arg_traits::is_specialized];
        typedef bool result_must_be_numeric[result_traits::is_specialized];

        const bool arg_is_signed = arg_traits::is_signed;
        const bool result_is_signed = result_traits::is_signed;
        const bool same_sign = arg_is_signed == result_is_signed;

        if (less_than_type_min<arg_is_signed, result_is_signed>::check(arg, result_traits::min())
            || greater_than_type_max<same_sign, arg_is_signed>::check(arg, result_traits::max())
            )
            
#else // We need to use #pragma hacks if available
            
# if BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4018)
#elif defined(__BORLANDC__)
#pragma option push -w-8012
# endif
        if ((arg < 0 && !result_traits::is_signed)  // loss of negative range
             || (arg_traits::is_signed && arg < result_traits::min())  // underflow
             || arg > result_traits::max())            // overflow
# if BOOST_MSVC
#  pragma warning(pop)
#elif defined(__BORLANDC__)
#pragma option pop
# endif
#endif
        {
            throw bad_numeric_cast();
        }
        return static_cast<Target>(arg);
    } // numeric_cast

#  undef BOOST_EXPLICIT_DEFAULT_TARGET

} // namespace boost

#endif  // BOOST_CAST_HPP
