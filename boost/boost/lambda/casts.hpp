// - casts.hpp -- BLambda Library -------------
//
// Copyright (C) 2000 Gary Powell (gary.powell@sierra.com)
// Copyright (C) 1999, 2000 Jaakko J�rvi (jaakko.jarvi@cs.utu.fi)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.
//
// For more information, see http://www.boost.org

// -----------------------------------------------

#if !defined(BOOST_LAMBDA_CASTS_HPP)
#define BOOST_LAMBDA_CASTS_HPP

#include <typeinfo>

namespace boost { 
namespace lambda {

template<class T> class cast_action;

template<class T> class static_cast_action;
template<class T> class dynamic_cast_action;
template<class T> class const_cast_action;
template<class T> class reinterpret_cast_action;

class typeid_action;

// Cast actions
template<class T> class cast_action<static_cast_action<T> > 
{
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return static_cast<RET>(a1);
  }
};

template<class T> class cast_action<dynamic_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return dynamic_cast<RET>(a1);
  }
};

template<class T> class cast_action<const_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return const_cast<RET>(a1);
  }
};

template<class T> class cast_action<reinterpret_cast_action<T> > {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return reinterpret_cast<RET>(a1);
  }
};

class typeid_action {
public:
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return typeid(a1);
  }
};


// return types of casting lambda_functors (all "T" type.)

template<template <class T> class cast_type, class T, class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, cast_action< cast_type<T> > >, Args, Code>,
 Open>
{ 
  typedef T const type;
};

// return type of typeid_action

template<class Args, int Code, class Open>
struct return_type<lambda_functor_args<action<1, typeid_action >, Args, Code>,
 Open>
{ 
	typedef std::type_info const & type;
};










// the four cast & typeid overloads.

// static_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_args<
    action<1, 
      cast_action<static_cast_action<T> >
    >, 
    tuple<typename const_copy_argument <const Arg1>::type>, 
    dig_arity<Arg1>::value
  > 
>
ll_static_cast(const Arg1& a1) { 
  return lambda_functor< lambda_functor_args<
			action<1, 
			cast_action<static_cast_action<T> > 
		>, 
	  tuple<typename const_copy_argument <const Arg1>::type>, 
	  dig_arity<Arg1>::value> >
    ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// dynamic_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_args<
    action<1, 
      cast_action<dynamic_cast_action<T> >
    >, 
    tuple<typename const_copy_argument <const Arg1>::type>, 
    dig_arity<Arg1>::value
  > 
>
ll_dynamic_cast(const Arg1& a1) { 
  return lambda_functor< lambda_functor_args<
			action<1, 
			cast_action<dynamic_cast_action<T> > 
		>, 
	  tuple<typename const_copy_argument <const Arg1>::type>, 
	  dig_arity<Arg1>::value> >
    ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// const_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_args<
    action<1, 
      cast_action<const_cast_action<T> >
    >, 
    tuple<typename const_copy_argument <const Arg1>::type>, 
    dig_arity<Arg1>::value
  > 
>
ll_const_cast(const Arg1& a1) { 
  return lambda_functor< lambda_functor_args<
			action<1, 
			cast_action<const_cast_action<T> > 
		>, 
	  tuple<typename const_copy_argument <const Arg1>::type>, 
	  dig_arity<Arg1>::value> >
    ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// reinterpret_cast
template <class T, class Arg1>
inline const lambda_functor<
  lambda_functor_args<
    action<1, 
      cast_action<reinterpret_cast_action<T> >
    >, 
    tuple<typename const_copy_argument <const Arg1>::type>, 
    dig_arity<Arg1>::value
  > 
>
ll_reinterpret_cast(const Arg1& a1) { 
  return lambda_functor< lambda_functor_args<
			action<1, 
			cast_action<reinterpret_cast_action<T> > 
		>, 
	  tuple<typename const_copy_argument <const Arg1>::type>, 
	  dig_arity<Arg1>::value> >
    ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}

// typeid
template <class Arg1>
inline const lambda_functor<
  lambda_functor_args<
    action<1, 
      typeid_action
    >, 
    tuple<typename const_copy_argument <const Arg1>::type>, 
    dig_arity<Arg1>::value
  > 
>
ll_typeid(const Arg1& a1) { 
  return lambda_functor< lambda_functor_args<
			action<1, 
			typeid_action
		>, 
	  tuple<typename const_copy_argument <const Arg1>::type>, 
	  dig_arity<Arg1>::value> >
    ( tuple<typename const_copy_argument <const Arg1>::type>(a1));
}


} // namespace lambda 
} // namespace boost

#endif
