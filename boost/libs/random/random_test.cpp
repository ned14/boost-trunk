/* boost random_test.cpp various tests
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * $Id$
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iterator>
#include <boost/random.hpp>
#include <boost/config.hpp>

#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>

#ifdef BOOST_NO_STDC_NAMESPACE
  namespace std { using ::fabs; }
#endif


/*
 * General portability note:
 * MSVC mis-compiles explicit function template instantiations.
 * For example, f<A>() and f<B>() are both compiled to call f<A>().
 * BCC is unable to implicitly convert a "const char *" to a std::string
 * when using explicit function template instantiations.
 *
 * Therefore, avoid explicit function template instantiations.
 */

/*
 * Validate correct implementation
 */

template<class PRNG>
void validate(const std::string & name, const PRNG &)
{
  std::cout << "validating " << name << ": ";
  PRNG rng;
  for(int i = 0; i < 9999; i++)
    rng();
  typename PRNG::result_type val = rng();
  // make sure the validation function is a const member
  bool result = const_cast<const PRNG&>(rng).validation(val);
  
  // allow for a simple eyeball check for MSVC instantiation brokenness
  // (if the numbers for all generators are the same, it's obviously broken)
  std::cout << val << std::endl;
  BOOST_TEST(result);
}

void validate_all()
{
  using namespace boost;
#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
  validate("rand48", rand48());
#endif
  validate("minstd_rand", minstd_rand());
  validate("minstd_rand0", minstd_rand0());
  validate("ecuyer combined", ecuyer1988());
  validate("mt19937", mt19937());
  validate("kreutzer1986", kreutzer1986());
}


/*
 * Check function signatures
 */

template<class Generator>
void instantiate_iterator_interface(Generator & gen)
{
  ++gen;
  gen++;
  typename Generator::result_type res = *gen;
  typename Generator::pointer p = &res;
  (void) &p;
  typename Generator::reference ref = res;
  (void) &ref;
  typename Generator::difference_type diff = 0;
  (void) &diff;
  typedef typename Generator::iterator_category iterator_category;
  std::input_iterator_tag it = iterator_category();
  (void) &it;

  BOOST_TEST(res == *gen++);
  BOOST_TEST(gen == gen);
#if 0
  // Distribution functions may have a cache which is purged on copy.
  // Thus, the copy never compares equal.  Example: normal_distribution.
  Generator gen2 = gen;
  BOOST_TEST(gen == gen2);     // must be equal to a copy
  ++gen2;
  // this is only correct for elementary generators, others have ref members
  BOOST_TEST(gen != gen2);
#endif
}

template<class URNG, class ResultType>
void instantiate_urng(const std::string & s, const URNG &, const ResultType &)
{
  std::cout << "Basic tests for " << s << std::endl;
  URNG urng;
  int a[URNG::has_fixed_range ? 5 : 10];        // compile-time constant
  (void) a;   // avoid "unused" warning
  typename URNG::result_type x1 = urng();
  ResultType x2 = x1;
  (void) &x2;           // avoid "unused" warning

#ifndef BOOST_MSVC   // MSVC brokenness
  URNG urng2 = urng;           // copy constructor
  BOOST_TEST(urng == urng2);   // operator==
  urng();
  urng2 = urng;              // assignment
  BOOST_TEST(urng == urng2);
#endif // BOOST_MSVC

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  // Streamable concept not supported for broken compilers
  {
    std::ofstream file("rng.tmp", std::ofstream::trunc);
    file << urng;
  }
  // move forward
  urng();
  {
    // restore old state
    std::ifstream file("rng.tmp");
    file >> urng;
  }
#ifndef BOOST_MSVC    // MSVC brokenness
  BOOST_TEST(urng == urng2);
#endif // BOOST_MSVC
#endif // BOOST_NO_OPERATORS_IN_NAMESPACE

  // instantiate various distributions with this URNG
  boost::uniform_smallint<URNG> unismall(urng, 0, 11);
  instantiate_iterator_interface(unismall);
  unismall();
  boost::uniform_int<URNG> uni_int(urng, -200, 20000);
  instantiate_iterator_interface(uni_int);
  uni_int();
  boost::uniform_real<URNG> uni_real(urng, 0, 2.1);
  instantiate_iterator_interface(uni_real);
  uni_real();

  boost::bernoulli_distribution<URNG> ber(urng, 0.2);
  instantiate_iterator_interface(ber);
  ber();
  boost::geometric_distribution<URNG> geo(urng, 0.8);
  instantiate_iterator_interface(geo);
  geo();
  boost::triangle_distribution<URNG> tria(urng, 1, 1.5, 7);
  instantiate_iterator_interface(tria);
  tria();
  boost::exponential_distribution<URNG> ex(urng, 5);
  instantiate_iterator_interface(ex);
  ex();
  boost::normal_distribution<URNG> norm(urng);
  instantiate_iterator_interface(norm);
  norm();
  boost::lognormal_distribution<URNG> lnorm(urng, 1, 1);
  instantiate_iterator_interface(lnorm);
  lnorm();
  boost::uniform_on_sphere<URNG> usph(urng, 2);
  instantiate_iterator_interface(usph);
  usph();
}

void instantiate_all()
{
  using namespace boost;

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
  instantiate_urng("rand48", rand48(), 0);
  rand48 rnd(boost::int32_t(5));
  rand48 rnd2(boost::uint64_t(0x80000000) * 42);
  rnd.seed(boost::int32_t(17));
  rnd2.seed(boost::uint64_t(0x80000000) * 49);
#endif

  instantiate_urng("minstd_rand0", minstd_rand0(), 0);
  instantiate_urng("minstd_rand", minstd_rand(), 0);
  minstd_rand mstd(42);
  mstd.seed(17);

  instantiate_urng("ecuyer1988", ecuyer1988(), 0);
  instantiate_urng("kreutzer1986", kreutzer1986(), 0);
  instantiate_urng("hellekalek1995", hellekalek1995(), 0);
  
  instantiate_urng("mt11213b", mt11213b(), 0u);
  instantiate_urng("mt19937", mt19937(), 0u);
  mt19937 mt(boost::uint32_t(17));  // needs to be an exact type match for MSVC
  int i = 42;
  mt.seed(boost::uint32_t(i));
  mt19937 mt2(mstd);
  mt2.seed(mstd);


  random_number_generator<mt19937> std_rng(mt2);
  (void) std_rng(10);
}

/*
 * A few equidistribution tests
 */

// yet to come...

template<class Generator>
void check_uniform_int(Generator & gen, int iter)
{
  std::cout << "testing uniform_int(" << gen.min() << "," << gen.max() 
	    << ")" << std::endl;
  int range = gen.max()-gen.min()+1;
  std::vector<int> bucket(range);
  for(int j = 0; j < iter; j++) {
    int result = gen();
    if(result < gen.min() || result > gen.max())
      std::cerr << "   ... delivers " << result << std::endl;
    else
      bucket[result-gen.min()]++;
  }
  int sum = 0;
  // use a different variable name "k", because MSVC has broken "for" scoping
  for(int k = 0; k < range; k++)
    sum += bucket[k];
  double avg = static_cast<double>(sum)/range;
  double threshold = 2*avg/std::sqrt(static_cast<double>(iter));
  for(int i = 0; i < range; i++) {
    if(std::fabs(bucket[i] - avg) > threshold) {
      // 95% confidence interval
      std::cout << "   ... has bucket[" << i << "] = " << bucket[i] 
		<< "  (distance " << (bucket[i] - avg) << ")" 
		<< std::endl;
    }
  }
}

template<class Generator>
void test_uniform_int(Generator & gen)
{
  typedef boost::uniform_int<Generator, int>  int_gen;

  // large range => small range (modulo case)
  int_gen uint12(gen,1,2);
  BOOST_TEST(uint12.min() == 1);
  BOOST_TEST(uint12.max() == 2);
  check_uniform_int(uint12, 100000);
  int_gen uint16(gen,1,6);
  check_uniform_int(uint16, 100000);

  // test chaining to get all cases in operator()
  typedef boost::uniform_int<int_gen, int> intint_gen;

  // identity map
  intint_gen uint01(uint12, 0, 1);
  check_uniform_int(uint01, 100000);

  // small range => larger range
  intint_gen uint05(uint12, -3, 2);
  check_uniform_int(uint05, 100000);

  typedef boost::uniform_int<intint_gen, int> intintint_gen;

#if 0
  // This takes a lot of time to run and is of questionable net effect:
  // avoid for now.

  // small => larger range, not power of two
  // (for unknown reasons, this has noticeably uneven distribution)
  intintint_gen uint1_49(uint05, 1, 49);
  check_uniform_int(uint1_49, 500000);
#endif

  // larger => small range, rejection case
  intintint_gen uint1_4(uint05, 1, 4);
  check_uniform_int(uint1_4, 100000);
}

#if defined(BOOST_MSVC) && _MSC_VER <= 1200

// These explicit instantiations are necessary, otherwise MSVC does
// find the <boost/operators.hpp> inline friends.
// We ease the typing with a suitable preprocessor macro.
#define INSTANT(x) \
template class boost::uniform_smallint<x>; \
template class boost::uniform_int<x>; \
template class boost::uniform_real<x>; \
template class boost::bernoulli_distribution<x>; \
template class boost::geometric_distribution<x>; \
template class boost::triangle_distribution<x>; \
template class boost::exponential_distribution<x>; \
template class boost::normal_distribution<x>; \
template class boost::uniform_on_sphere<x>; \
template class boost::lognormal_distribution<x>;

INSTANT(boost::minstd_rand0)
INSTANT(boost::minstd_rand)
INSTANT(boost::ecuyer1988)
INSTANT(boost::kreutzer1986)
INSTANT(boost::hellekalek1995)
INSTANT(boost::mt19937)
INSTANT(boost::mt11213b)

#endif

int test_main(int, char*[])
{
  instantiate_all();
  validate_all();
  boost::mt19937 mt;
  test_uniform_int(mt);
  // Some compilers don't pay attention to std:3.6.1/5 and issue a
  // warning here if "return 0;" is omitted.
  return 0;
}
