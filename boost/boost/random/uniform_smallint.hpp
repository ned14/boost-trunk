/* boost random/uniform_smallint.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-04-08  added min<max assertion (N. Becker)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_UNIFORM_SMALLINT_HPP
#define BOOST_RANDOM_UNIFORM_SMALLINT_HPP

#include <cassert>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/random/uniform_01.hpp>

namespace boost {

// uniform integer distribution on a small range [min, max]
template<class UniformRandomNumberGenerator, class IntType = int,
         bool is_integer = std::numeric_limits<typename UniformRandomNumberGenerator::result_type>::is_integer>
class uniform_smallint;


template<class UniformRandomNumberGenerator, class IntType>
class uniform_smallint<UniformRandomNumberGenerator, IntType, true>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef IntType result_type;
  BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);

  BOOST_STATIC_ASSERT(std::numeric_limits<IntType>::is_integer);

  uniform_smallint(base_type & rng, IntType min, IntType max);

  result_type min() const { return _min; }
  result_type max() const { return _max; }
  base_type& base() const { return _rng; }
  void reset() { }

  result_type operator()()
  {
    // we must not use the low bits here, because LCGs get very bad then
    return ((_rng() - _rng.min()) / _factor) % _range + _min;
  }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const uniform_smallint& x, const uniform_smallint& y)
  { return x._min == y._min && x._max == y._max && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const uniform_smallint& rhs) const
  { return _min == rhs._min && _max == rhs._max && _rng == rhs._rng;  }
#endif
private:
  typedef typename base_type::result_type base_result;
  base_type & _rng;
  IntType _min, _max;
  base_result _range;
  int _factor;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class UniformRandomNumberGenerator, class IntType>
const bool uniform_smallint<UniformRandomNumberGenerator, IntType, true>::has_fixed_range;
#endif

template<class UniformRandomNumberGenerator, class IntType>
uniform_smallint<UniformRandomNumberGenerator, IntType, true>::
uniform_smallint(base_type & rng, IntType min, IntType max) 
  : _rng(rng), _min(min), _max(max),
    _range(static_cast<base_result>(_max-_min)+1), _factor(1)
{
  assert(min < max);
  
  // LCGs get bad when only taking the low bits.
  // (probably put this logic into a partial template specialization)
  // Check how many low bits we can ignore before we get too much
  // quantization error.
  base_result r_base = _rng.max() - _rng.min();
  if(r_base == std::numeric_limits<base_result>::max()) {
    _factor = 2;
    r_base /= 2;
  }
  r_base += 1;
  if(r_base % _range == 0) {
    // No quantization effects, good
    _factor = r_base / _range;
  } else {
    // carefully avoid overflow; pessimizing heree
    for( ; r_base/_range/32 >= _range; _factor *= 2)
      r_base /= 2;
  }
}


// Implementation for floating-point generator base
template<class UniformRandomNumberGenerator, class IntType>
class uniform_smallint<UniformRandomNumberGenerator, IntType, false>
{
public:
  typedef UniformRandomNumberGenerator base_type;
  typedef IntType result_type;
  BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);

  BOOST_STATIC_ASSERT(std::numeric_limits<IntType>::is_integer);

  uniform_smallint(base_type & rng, IntType min, IntType max);

  result_type min() const { return _min; }
  result_type max() const { return _max; }
  base_type& base() const { return _rng.base(); }
  void reset() { }

  result_type operator()()
  {
    return static_cast<IntType>(_rng() * _range) + _min;
  }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const uniform_smallint& x, const uniform_smallint& y)
  { return x._min == y._min && x._max == y._max && x._rng == y._rng; }
#else
  // Use a member function
  bool operator==(const uniform_smallint& rhs) const
  { return _min == rhs._min && _max == rhs._max && _rng == rhs._rng;  }
#endif
private:
  typedef typename base_type::result_type base_result;
  uniform_01<base_type> _rng;
  IntType _min, _max;
  base_result _range;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class UniformRandomNumberGenerator, class IntType>
const bool uniform_smallint<UniformRandomNumberGenerator, IntType, false>::has_fixed_range;
#endif

template<class UniformRandomNumberGenerator, class IntType>
uniform_smallint<UniformRandomNumberGenerator, IntType, false>::
uniform_smallint(base_type & rng, IntType min, IntType max) 
  : _rng(rng), _min(min), _max(max),
    _range(static_cast<base_result>(_max-_min)+1)
{
  assert(min < max);
}

} // namespace boost

#endif // BOOST_RANDOM_UNIFORM_SMALLINT_HPP
