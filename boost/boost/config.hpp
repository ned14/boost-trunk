//  Boost config.hpp configuration header file  ------------------------------//

//  (C) Copyright Boost.org 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  Boost config.hpp policy and rationale documentation has been moved to
//  http://www.boost.org/libs/config

//  Revision History (excluding minor changes for specific compilers)
//   29 Mar 01  BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS (Daryle Walker)
//   16 Mar 01  Added BOOST_VERSION (Jens Maurer)
//   06 Mar 01  Refactored EDG checks for Intel C++ (Dave Abrahams)
//   04 Mar 01  Factored EDG checks, added BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
//              for Intel C++ 5.0 (Dave Abrahams)
//   17 Feb 01  BOOST_NO_CV_SPECIALIZATIONS
//              BOOST_NO_CV_VOID_SPECIALIZATIONS (John Maddock)
//   11 Feb 01  Added BOOST_STATIC_CONSTANT (Dave Abrahams)
//   20 Jan 01  BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS moved here from
//              cast.hpp. Added missing BOOST_NO_STRINGSTREAM which some
//              boost code seemed to depend on. (Dave Abrahams)
//   13 Jan 01  SGI MIPSpro and Compaq Tru64 Unix compiler support added
//              (Jens Maurer)
//   13 Jan 01  BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP (Jens Maurer)
//   17 Nov 00  BOOST_NO_AUTO_PTR (John Maddock)
//    4 Oct 00  BOOST_NO_STD_MIN_MAX (Jeremy Siek)
//   29 Sep 00  BOOST_NO_INTEGRAL_INT64_T (Jens Maurer)
//   25 Sep 00  BOOST_NO_STD_ALLOCATOR (Jeremy Siek)
//   18 SEP 00  BOOST_NO_SLIST, BOOST_NO_HASH, 
//              BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
//              BOOST_NO_LIMITS (Jeremy Siek)
//    1 Sep 00  BOOST_NO_PRIVATE_IN_AGGREGATE added. (Mark Rodgers)
//   23 Jul 00  Fixed spelling of BOOST_NO_INCLASS_MEMBER_INITIALIZATION in
//              comment (Dave Abrahams). 
//   10 Jul 00  BOOST_NO_POINTER_TO_MEMBER_CONST added (Mark Rodgers)
//   26 Jun 00  BOOST_NO_STD_ITERATOR, BOOST_MSVC_STD_ITERATOR,
//              BOOST_NO_STD_ITERATOR_TRAITS, BOOST_NO_USING_TEMPLATE,
//              added (Jeremy Siek)
//   20 Jun 00  BOOST_MSVC added (Aleksey Gurtovoy)
//   14 Jun 00  BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS (Jens M.)
//   22 Mar 00  BOOST_MSVC6_MEMBER_TEMPLATES added (Dave Abrahams)
//   18 Feb 00  BOOST_NO_INCLASS_MEMBER_INITIALIZATION added (Jens Maurer)
//   26 Jan 00  Borland compiler support added (John Maddock)
//   26 Jan 00  Sun compiler support added (J�rg Schaible)
//   30 Dec 99  BOOST_NMEMBER_TEMPLATES compatibility moved here from
//              smart_ptr.hpp. (Dave Abrahams)
//   15 Nov 99  BOOST_NO_OPERATORS_IN_NAMESPACE,
//              BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION added (Beman Dawes)
//   11 Oct 99  BOOST_NO_STDC_NAMESPACE refined; <cstddef> supplied
//   29 Sep 99  BOOST_NO_STDC_NAMESPACE added (Ed Brey)
//   24 Sep 99  BOOST_DECL added (Ed Brey)
//   10 Aug 99  Endedness flags added, GNU CC support added
//   22 Jul 99  Initial version
 

#ifndef BOOST_CONFIG_HPP
#define BOOST_CONFIG_HPP

#define BOOST_VERSION 102300

//  BOOST_VERSION % 100 is the sub-minor version
//  BOOST_VERSION / 100 % 1000 is the minor version
//  BOOST_VERSION / 100000 is the major version


//  Conformance Flag Macros  -------------------------------------------------//
//
//  Conformance flag macros should identify the absence of C++ Standard 
//  conformance rather than its presence.  This ensures that standard conforming
//  compilers do not require a lot of configuration flag macros.  It places the
//  burden where it should be, on non-conforming compilers.  In the future,
//  hopefully, less rather than more conformance flags will have to be defined.

//  BOOST_NO_CV_SPECIALIZATIONS: if template specialisations for cv-qualified types
//  conflict with a specialistaion for unqualififed type.

//  BOOST_NO_CV_VOID_SPECIALIZATIONS: if template specialisations for cv-void types
//  conflict with a specialistaion for void.

//  BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP: Compiler does not implement
//  argument-dependent lookup (also named Koenig lookup); see std::3.4.2
//  [basic.koenig.lookup]

//  BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS: Template value
//  parameters cannot have a dependent type, for example
//  "template<class T, typename T::type value> class X { ... };"

//  BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS: Can only use deduced
//  template arguments when calling function template instantiations.

//  BOOST_NO_INCLASS_MEMBER_INITIALIZATION: Compiler violates std::9.4.2/4. 

//  BOOST_NO_INT64_T: <boost/cstdint.hpp> does not support 64-bit integer
//  types.  (Set by <boost/cstdint.hpp> rather than <boost/config.hpp>).

//  BOOST_NO_INTEGRAL_INT64_T: int64_t as defined by <boost/cstdint.hpp> is
//  not an integral type.

//  BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS: constants such as
//  numeric_limits<T>::is_signed are not available for use at compile-time.

//  BOOST_NO_MEMBER_TEMPLATES: Member template functions not fully supported.
//  Also see BOOST_MSVC6_MEMBER_TEMPLATES in the Compiler Control section below.

//  BOOST_NO_MEMBER_TEMPLATE_FRIENDS: Member template friend syntax
//  ("template<class P> friend class frd;") described in the C++ Standard,
//  14.5.3, not supported.

//  BOOST_NO_OPERATORS_IN_NAMESPACE: Compiler requires inherited operator
//  friend functions to be defined at namespace scope, then using'ed to boost.
//  Probably GCC specific.  See boost/operators.hpp for example.

//  BOOST_NO_POINTER_TO_MEMBER_CONST: The compiler does not correctly handle
//  pointers to const member functions, preventing use of these in overloaded 
//  function templates.  See boost/functional.hpp for example.

//  BOOST_NO_PRIVATE_IN_AGGREGATE: The compiler misreads 8.5.1, treating classes
//  as non-aggregate if they contain private or protected member functions. 

//  BOOST_NO_STD_ITERATOR: The C++ implementation fails to provide the
//  std::iterator class.

//  BOOST_NO_STD_ITERATOR_TRAITS: The compiler does not provide a standard
//  compliant implementation of std::iterator_traits. Note that
//  the compiler may still have a non-standard implementation.

//  BOOST_NO_STDC_NAMESPACE: The contents of C++ standard headers for C library
//  functions (the <c...> headers) have not been placed in namespace std.
//  Because the use of std::size_t is so common, a specific workaround for
//  <cstddef> (and thus std::size_t) is provided in this header (see below).
//  For other <c...> headers, a workaround must be provided in the boost header:
//
//    #include <cstdlib>  // for abs
//    #ifdef BOOST_NO_STDC_NAMESPACE
//      namespace std { using ::abs; }
//    #endif

//  BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION. Class template partial
//  specialization (14.5.4 [temp.class.spec]) not supported.

//  BOOST_NO_USING_TEMPLATE: The compiler will not accept a using declaration
//  that imports a template from the global namespace into a named namespace.
//  Probably Borland specific.

//  BOOST_NO_AUTO_PTR: If the compiler / library supplies non-standard or broken
//  std::auto_ptr.

//  BOOST_WEAK_FUNCTION_TEMPLATE_ORDERING: The compiler does not perform 
//  function template ordering or its function template ordering is incorrect.
//  
//  template<typename T> void f(T); // #1
//  template<typename T, typename U> void f(T (*)(U)); // #2
//  void bar(int);
//  f(&bar); // should choose #2. 

//  BOOST_NO_DEPENDENT_NESTED_DERIVATIONS: The compiler fails to compile
//  a nested class that has a dependent base class:
//  template<typename T>
//  struct foo : public T {  
//    template<typename U>
//    struct bar : public T, public U {};
//  };

//  
//  Compiler Control or Information Macros  ----------------------------------//
//
//  Compilers often supply features outside of the C++ Standard which need to be
//  controlled or detected. As usual, reasonable default behavior should occur
//  if any of these macros are not defined.

//  BOOST_DECL:  Certain compilers for Microsoft operating systems require
//  non-standard class and function decoration if dynamic load library linking
//  is desired.  BOOST_DECL supplies that decoration.  Boost does not require
//  use of BOOST_DECL - it is non-standard and to be avoided if practical to do
//  so. Even compilers requiring it for DLL's only require it in certain cases.
//
//    BOOST_DECL_EXPORTS:  User defined, usually via command line or IDE,
//    it causes BOOST_DECL to be defined as __declspec(dllexport).
//
//    BOOST_DECL_IMPORTS:  User defined, usually via command line or IDE,
//    it causes BOOST_DECL to be defined as __declspec(dllimport).
//
//    If neither BOOST_DECL_EXPORTS nor BOOST_DECL_IMPORTS is defined, or if
//    the compiler does not require __declspec() decoration, BOOST_DECL is
//    defined as a null string.

//  BOOST_MSVC6_MEMBER_TEMPLATES:  Microsoft Visual C++ 6.0 has enough member
//  template idiosyncrasies (being polite) that BOOST_NO_MEMBER_TEMPLATES is
//  defined for this compiler. BOOST_MSVC6_MEMBER_TEMPLATES is defined to allow
//  compiler specific workarounds.

//  BOOST_MSVC: defined as _MSC_VER for the Microsoft compiler only. In general,
//  boost headers should test for a specific conformance flag macro (for
//  example, BOOST_NO_MEMBER_TEMPLATE_FRIENDS) rather than a specific compiler.
//  VC++ is a special case, however, since many libraries try to support it yet
//  it has so many conformance issues that sometimes it is just easier to test
//  for it directly. On the other hand, the obvious way to do this doesn't work,
//  as many non-Microsoft compilers define _MSC_VER.  Thus BOOST_MSVC.

//  BOOST_MSVC_STD_ITERATOR: Microsoft's broken version of std::iterator
//  is being used. 

//  BOOST_SYSTEM_HAS_STDINT_H: There are no 1998 C++ Standard headers <stdint.h> 
//  or <cstdint>, although the 1999 C Standard does include <stdint.h>. 
//  If <stdint.h> is present, <boost/stdint.h> can make good use of it,
//  so a flag is supplied (signalling presence; thus the default is not
//  present, conforming to the current C++ standard).

//  BOOST_NO_SLIST: The C++ implementation does not provide the slist class.

//  BOOST_NO_STRINGSTREAM: The C++ implementation does not provide the <sstream> header.

//  BOOST_NO_HASH: The C++ implementation does not provide the hash_set
//  or hash_map classes.

//  BOOST_STD_EXTENSION_NAMESPACE: The name of the namespace in which the slist,
//  hash_set and/or hash_map templates are defined in this implementation (if any).

//  BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS: The standard library does not provide
//  templated iterator constructors for its containers.

//  BOOST_NO_LIMITS: The C++ implementation does not provide the <limits> header.

//  BOOST_NO_INTRINSIC_WCHAR_T: The C++ implementation does not provide wchar_t,
//  or it is really a synonym for another integral type. Use this symbol to
//  decide whether it is appropriate to explicitly specialize a template on
//  wchar_t if there is already a specialization for other integer types.

//  BOOST_NO_STD_ALLOCATOR: The C++ standard library does not provide
//  a standards conforming std::allocator.

//  BOOST_NO_STD_MIN_MAX: The C++ standard library does not provide
//  the min() and max() template functions that should be in <algorithm>.

//  Common compiler front-ends precede all compiler checks  ------------------//

//  Edison Design Group front-ends
# if defined(__EDG_VERSION__)
#   if __EDG_VERSION__ <= 241
#     define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#   endif

# endif

//  Compiler-specific checks -------------------------------------------------//
//  Compilers are listed in alphabetic order by vendor name
//  (except VC++ must be last - see below)

//  Borland ------------------------------------------------------------------//

#if defined __BORLANDC__
#   define BOOST_NO_SLIST
#   define BOOST_NO_HASH
// pull in standard library version:
#   include <memory>
#   if __BORLANDC__ <= 0x0551
#     define BOOST_NO_DEPENDENT_NESTED_DERIVATIONS
#     define BOOST_NO_INTEGRAL_INT64_T
#     define BOOST_NO_PRIVATE_IN_AGGREGATE
#   endif
#   if __BORLANDC__ <= 0x0550
// Borland C++ Builder 4 and 5:
#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     define BOOST_NO_USING_TEMPLATE
#     if __BORLANDC__ == 0x0550
// Borland C++ Builder 5, command-line compiler 5.5:
#       define BOOST_NO_OPERATORS_IN_NAMESPACE
#     endif
#   endif
#   if defined BOOST_DECL_EXPORTS
#     if defined BOOST_DECL_IMPORTS
#       error Not valid to define both BOOST_DECL_EXPORTS and BOOST_DECL_IMPORTS
#     endif
#     define BOOST_DECL __declspec(dllexport)
#   elif defined BOOST_DECL_IMPORTS
#     define BOOST_DECL __declspec(dllimport)
#   else
#     define BOOST_DECL
#   endif
#if (__BORLANDC__ == 0x550) || (__BORLANDC__ == 0x551)
// <climits> is partly broken, some macos define symbols that are really in
// namespace std, so you end up having to use illegal constructs like
// std::DBL_MAX, as a fix we'll just include float.h and have done with:
#include <float.h>
#endif
#   define BOOST_NO_CV_SPECIALIZATIONS
#   define BOOST_NO_CV_VOID_SPECIALIZATIONS

// Comeau C++ ----------------------------------------------------------------//

# elif defined __COMO__
#   if __COMO_VERSION__ <= 4245
#     define BOOST_FUNCTION_USE_VIRTUAL_FUNCTIONS
#   endif

//  Compaq Tru64 Unix cxx ---------------------------------------------------

# elif defined __DECCXX
#   define BOOST_NO_SLIST
#   define BOOST_NO_HASH

//  GNU CC (also known as GCC and G++)  --------------------------------------//

# elif defined __GNUC__
#   if __GNUC__ == 2 && __GNUC_MINOR__ == 91
       // egcs 1.1 won't parse smart_ptr.hpp without this:
#      define BOOST_NO_AUTO_PTR
#   endif
#   if __GNUC__ == 2 && __GNUC_MINOR__ <= 97
#     include <string>  // not sure this is the right way to do this -JGS
#     if defined(__BASTRING__) && !defined(__GLIBCPP__) && !defined(_CXXRT_STD) && !defined(__SGI_STL) // need to ask Dietmar about this -JGS
        // this should only detect the stdlibc++ that ships with gcc, and
        // not any replacements that may be installed...
#       define BOOST_NO_STD_ITERATOR
#       define BOOST_NO_LIMITS
#     endif
#     if !defined(_CXXRT_STD) && !defined(__SGI_STL_OWN_IOSTREAMS)
#       define BOOST_NO_STRINGSTREAM
#     endif
#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     define BOOST_NO_OPERATORS_IN_NAMESPACE
#     define BOOST_WEAK_FUNCTION_TEMPLATE_ORDERING
#   endif
#   if __GNUC__ == 2 && __GNUC_MINOR__ <= 8
#     define BOOST_NO_MEMBER_TEMPLATES
#   endif
#   if __GNUC__ >= 3
#     include <iterator>
#     if defined(__GLIBCPP__)
        // The new GNU C++ library has slist, hash_map, hash_set headers
        // in <ext/*>, but client code assumes they're in <*> --- Jens M. 
#       define BOOST_NO_SLIST
#       define BOOST_NO_HASH
#     endif
#   endif

//  Greenhills C++ -----------------------------------------------------------//

#elif defined __ghs
#   define BOOST_NO_SLIST
#   define BOOST_NO_HASH

//  HP aCC -------------------------------------------------------------------

# elif defined __HP_aCC
#    define BOOST_NO_SLIST
#    define BOOST_NO_HASH
#    define BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#    define BOOST_NO_OPERATORS_IN_NAMESPACE
     // (support for HP aCC is not complete, see the regression test results)

//  Intel on Linux -----------------------------------------------------------//

#elif defined __ICC
#   include <iterator>
#   ifdef _CPPLIB_VER 
      // shipped with Dinkumware 3.10, which has a different hash_map
#     define BOOST_NO_HASH
#   endif

//  Intel on Windows --------------------------------------------------------//

# elif defined __ICL
#   if __ICL <= 500
      // Intel C++ 5.0.1 uses EDG 2.45, but fails to activate Koenig lookup
      // in the frontend even in "strict" mode.  (reported by Kirk Klobe)
#     ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#       define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#     endif
#     define BOOST_WEAK_FUNCTION_TEMPLATE_ORDERING
#     define BOOST_NO_INTRINSIC_WCHAR_T // tentative addition - required for VC6 compatibility? (added by JM 19 Feb 2001)
#   endif
#   include <iterator>  // not sure this is the right way to do this -JGS
#   if __SGI_STL_PORT >= 0x400 || __SGI_STL_PORT >= 0x321 && defined(__STL_USE_NAMESPACES)
        // a perfectly good implementation of std::iterator is supplied
#   elif defined(__SGI_STL_ITERATOR)
#     define BOOST_NO_STD_ITERATOR // No std::iterator in this case
#   elif defined(_CPPLIB_VER) && (_CPPLIB_VER >= 306)
#     // full dinkumware 3.06 and above
#     define BOOST_NO_HASH
#     define BOOST_NO_STD_ITERATOR_TRAITS
#     if !_GLOBAL_USING   // can be defined in yvals.h
#       define BOOST_NO_STDC_NAMESPACE
#     endif
#   else // assume using dinkumware's STL that comes with VC++ 6.0
#     define BOOST_MSVC_STD_ITERATOR
#     define BOOST_NO_STD_ITERATOR_TRAITS
#     define BOOST_NO_STDC_NAMESPACE
#     define BOOST_NO_SLIST
#     define BOOST_NO_HASH
#     define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#     define BOOST_NO_STD_ALLOCATOR
#     define BOOST_NO_STD_MIN_MAX
#   endif

//  Kai C++ ----------------------------------------------------------------

#elif defined __KCC
#   define BOOST_NO_SLIST
#   define BOOST_NO_HASH

#   if __KCC_VERSION <= 4001
      // at least on Sun, the contents of <cwchar> is not in namespace std
#     define BOOST_NO_STDC_NAMESPACE
#   endif
 
//  Metrowerks CodeWarrior  -------------------------------------------------//

# elif defined  __MWERKS__
#   if __MWERKS__ <= 0x2401  // 6.2
#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     define BOOST_WEAK_FUNCTION_TEMPLATE_ORDERING
#   endif
#   if __MWERKS__ <= 0x2301  // 5.3
#     define BOOST_NO_POINTER_TO_MEMBER_CONST
#     define BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#     define BOOST_NO_HASH
#   endif
#   if __MWERKS__ >= 0x2400
#     define BOOST_STD_EXTENSION_NAMESPACE Metrowerks
#   endif
#   if __MWERKS__ >= 0x2300
#     define BOOST_SYSTEM_HAS_STDINT_H
#   endif
#   if defined BOOST_DECL_EXPORTS
#     if defined BOOST_DECL_IMPORTS
#       error Not valid to define both BOOST_DECL_EXPORTS and BOOST_DECL_IMPORTS
#     endif
#     define BOOST_DECL __declspec(dllexport)
#   elif defined BOOST_DECL_IMPORTS
#     define BOOST_DECL __declspec(dllimport)
#   else
#     define BOOST_DECL
#   endif

//  SGI MIPSpro C++ ---------------------------------------------------------//

# elif defined __sgi
    // This is a generic STLport condition and could be moved elsewhere.
#   include <iterator>
#   if defined(__SGI_STL_PORT) && !defined(__STL_MEMBER_TEMPLATE_CLASSES) && !defined(_STLP_MEMBER_TEMPLATE_CLASSES)
#     define BOOST_NO_STD_ALLOCATOR
#   endif

//  Sun Workshop Compiler C++ -----------------------------------------------//

# elif defined  __SUNPRO_CC
#    if __SUNPRO_CC <= 0x520
#      define BOOST_NO_SLIST
#      define BOOST_NO_HASH
#      define BOOST_NO_STD_ITERATOR_TRAITS
#      define BOOST_NO_STD_ALLOCATOR

       // although sunpro 5.1 supports the syntax for
       // inline initialization it often gets the value
       // wrong, especially where the value is computed
       // from other constants (J Maddock 6th May 2001)
#      define BOOST_NO_INCLASS_MEMBER_INITIALIZATION

       // although sunpro 5.1 supports the syntax for
       // partial specialization, it often seems to
       // bind to the wrong specialization.  Better
       // to disable it until suppport becomes more stable
       // (J Maddock 6th May 2001).
#      define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#    endif
#    if __SUNPRO_CC <= 0x500
#      define BOOST_NO_MEMBER_TEMPLATES
#      define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#    endif

//  Microsoft Visual C++ (excluding Intel/EDG front end)  --------------------
//
//  Must remain the last #elif since some other vendors (Metrowerks, for
//  example) also #define _MSC_VER

# elif defined _MSC_VER
#   define BOOST_MSVC _MSC_VER

    // turn off the warnings before we #include anything
#   pragma warning( disable : 4786 ) // ident trunc to '255' chars in debug info
#   pragma warning( disable : 4503 ) // warning: decorated name length exceeded

#   if _MSC_VER <= 1200  // 1200 == VC++ 6.0
#     define BOOST_NO_INCLASS_MEMBER_INITIALIZATION
#     define BOOST_NO_PRIVATE_IN_AGGREGATE
#     define BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#     define BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS

#     define BOOST_NO_INTEGRAL_INT64_T
#     define BOOST_NO_INTRINSIC_WCHAR_T

//    VC++ 6.0 has member templates but they have numerous problems including
//    cases of silent failure, so for safety we define:
#     define BOOST_NO_MEMBER_TEMPLATES
//    For VC++ experts wishing to attempt workarounds, we define:
#     define BOOST_MSVC6_MEMBER_TEMPLATES

#     define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#     define BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#     define BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#     define BOOST_WEAK_FUNCTION_TEMPLATE_ORDERING
#     include <iterator>  // not sure this is the right way to do this -JGS
#     if __SGI_STL_PORT >= 0x400 || __SGI_STL_PORT >= 0x321 && defined(__STL_USE_NAMESPACES)
        // a perfectly good implementation of std::iterator is supplied
        // A conforming allocator is supplied, but the compiler cannot cope
        // when using "rebind".  (Douglas Gregor)
#       define BOOST_NO_STD_ALLOCATOR
#     elif defined(__SGI_STL_ITERATOR)
#       define BOOST_NO_STD_ITERATOR // No std::iterator in this case
#     elif defined(_CPPLIB_VER) && (_CPPLIB_VER >= 306)
        // full dinkumware 3.06 and above
#       define BOOST_NO_HASH
#       define BOOST_NO_STD_ITERATOR_TRAITS
#       ifndef _GLOBAL_USING    // can be defined in yvals.h
#         define BOOST_NO_STDC_NAMESPACE
#       endif
#       define BOOST_MSVC_STD_ITERATOR
#     else
#       define BOOST_MSVC_STD_ITERATOR
#       define BOOST_NO_SLIST
#       define BOOST_NO_HASH
#       define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#       define BOOST_NO_STD_ALLOCATOR
#       ifndef _CPPLIB_VER
          // Updated Dinkum library defines this, and provides
          // its own min and max definitions.
#         define BOOST_NO_STD_MIN_MAX
#         undef min
#         undef max
#       endif
#       ifndef NOMINMAX
          // avoid spurious NOMINMAX redefinition warning
#         define NOMINMAX
#       endif
#     endif
#     define BOOST_NO_STD_ITERATOR_TRAITS
#     define BOOST_NO_CV_VOID_SPECIALIZATIONS


// Make sure at least one standard library header is included so that library
// implementation detection will work, even if no standard headers have been
// included in front of a boost header. (Ed Brey 5 Jun 00)
#     include <cstddef>

// Determine if the standard library implementation is already pulling names
// into std.  STLport defines the following if so. (Ed Brey 5 Jun 00)
#     if !defined( __STL_IMPORT_VENDOR_CSTD ) || defined( __STL_NO_CSTD_FUNCTION_IMPORTS )
#       define BOOST_NO_STDC_NAMESPACE
#     endif

#   endif

#   if defined BOOST_DECL_EXPORTS
#     if defined BOOST_DECL_IMPORTS
#       error Not valid to define both BOOST_DECL_EXPORTS and BOOST_DECL_IMPORTS
#     endif
#     define BOOST_DECL __declspec(dllexport)
#   elif defined BOOST_DECL_IMPORTS
#     define BOOST_DECL __declspec(dllimport)
#   else
#     define BOOST_DECL
#   endif

# endif // Microsoft (excluding Intel/EDG frontend) 

# ifndef BOOST_DECL
#   define BOOST_DECL  // default for compilers not needing this decoration.
# endif

//  end of compiler specific portion  ----------------------------------------//

#if defined(BOOST_NO_LIMITS) || (defined(_RWSTD_VER) && defined(__BORLANDC__) && _RWSTD_VER < 0x020300) || (defined(__SGI_STL_PORT) && __SGI_STL_PORT <= 0x410 && defined(__STL_STATIC_CONST_INIT_BUG))
// STLPort 4.0 doesn't define the static constants in numeric_limits<> so that they
// can be used at compile time if the compiler bug indicated by
// __STL_STATIC_CONST_INIT_BUG is present.

// Rogue wave STL (C++ Builder) also has broken numeric_limits
// with default template defining members out of line.
// However, Compaq C++ also uses RogueWave (version 0x0203) and it's ok.
#   define BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#endif

#if defined(__hpux)
// HP-UX has a nice stdint.h in a different location, see boost/cstdint.hpp
# define BOOST_SYSTEM_HAS_STDINT_H
#endif

#ifndef BOOST_STD_EXTENSION_NAMESPACE
# define BOOST_STD_EXTENSION_NAMESPACE std
#endif

// Check for old name "BOOST_NMEMBER_TEMPLATES" for compatibility  -----------//
// Don't use BOOST_NMEMBER_TEMPLATES. It is deprecated and will be removed soon.
#if defined( BOOST_NMEMBER_TEMPLATES ) && !defined( BOOST_NO_MEMBER_TEMPLATES )
  #define BOOST_NO_MEMBER_TEMPLATES
#endif

//  BOOST_NO_STDC_NAMESPACE workaround  --------------------------------------//
//
//  Because std::size_t usage is so common, even in boost headers which do not
//  otherwise use the C library, the <cstddef> workaround is included here so
//  that ugly workaround code need not appear in many other boost headers.
//  NOTE WELL: This is a workaround for non-conforming compilers; <cstddef> 
//  must still be #included in the usual places so that <cstddef> inclusion
//  works as expected with standard conforming compilers.  The resulting
//  double inclusion of <cstddef> is harmless.

# ifdef BOOST_NO_STDC_NAMESPACE
#   include <cstddef>
    namespace std { using ::ptrdiff_t; using ::size_t; }
    // using ::wchar_t; removed since wchar_t is a C++ built-in type (Ed Brey)
# endif

#ifdef BOOST_NO_STD_MIN_MAX
namespace std {
  template <class _Tp>
  inline const _Tp& min(const _Tp& __a, const _Tp& __b) {
    return __b < __a ? __b : __a;
  }
  template <class _Tp>
  inline const _Tp& max(const _Tp& __a, const _Tp& __b) {
    return  __a < __b ? __b : __a;
  }
#ifdef BOOST_MSVC
  inline long min(long __a, long __b) {
    return __b < __a ? __b : __a;
  }
  inline long max(long __a, long __b) {
    return  __a < __b ? __b : __a;
  }
#endif
}
#endif

// BOOST_STATIC_CONSTANT workaround --------------------------------------- //
// On compilers which don't allow in-class initialization of static integral
// constant members, we must use enums as a workaround if we want the constants
// to be available at compile-time. This macro gives us a convenient way to
// declare such constants.
#ifdef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
# define BOOST_STATIC_CONSTANT(type, assignment) enum { assignment }
#else
# define BOOST_STATIC_CONSTANT(type, assignment) static const type assignment
#endif

#endif  // BOOST_CONFIG_HPP







