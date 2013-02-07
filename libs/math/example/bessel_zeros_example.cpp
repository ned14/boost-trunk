// Copyright Christopher Kormanyos 2013.
// Copyright Paul A. Bristow 2013.
// Copyright John Maddock 2013.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifdef _MSC_VER
#  pragma warning (disable : 4512) // assignment operator could not be generated.
#  pragma warning (disable : 4996) // assignment operator could not be generated.
#endif

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>

// Weisstein, Eric W. "Bessel Function Zeros." From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/BesselFunctionZeros.html 
// Test values can be calculated using [@wolframalpha.com WolframAplha]
// See also http://dlmf.nist.gov/10.21

//[bessel_zero_example_1

/*`This example demonstrates calculating zeros of the Bessel, Neumann and Airy functions.
It shows how Boost.Math and Boost.Multiprecision can be combined to provide
a many decimal digit precision. For 50 decimal digit precision we need to include
*/

  #include <boost/multiprecision/cpp_dec_float.hpp>

/*`and a typedef may be convenient
(allowing a quick switch to recalculate at built-in `double` or other precision)
*/
  typedef boost::multiprecision::cpp_dec_float_50 float_type;

//`To use the functions for finding zeros of the functions we need

  #include <boost/math/special_functions/bessel.hpp>

//`This file has the forward declaration signatures for the zero-finding functions:

  #include <boost/math/special_functions/math_fwd.hpp>

/*`but more details are in the full documentation, for example at
[@http://www.boost.org/doc/libs/1_53_0/libs/math/doc/sf_and_dist/html/math_toolkit/special/bessel/bessel_over.html Boost.Math Bessel functions]
*/

/*`This example shows obtaining both a single zero of the Bessel function,
and then placing multiple zeros into a container like `std::vector` by providing an iterator.
The signature of the single value function is:

  template <class T>
  inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type 
    cyl_bessel_j_zero(T v,  // Floating-point value for Jv.
    unsigned m); // start index.

The result type is controlled by the floating-point type of parameter `v`
(but subject to the usual __precision_policy and __promotion_policy).

The signature of multiple zeros function is:

  template <class T, class OutputIterator>
  inline OutputIterator cyl_bessel_j_zero(T v, // Floating-point value for Jv.
                                unsigned start_index, // 1-based start index.
                                unsigned number_of_zeros,
                                OutputIterator out_it); // iterator into container for zeros. 

There is also a version which allows control of the __policy_section for error handling and precision.

  template <class T, class OutputIterator, class Policy>
  inline OutputIterator cyl_bessel_j_zero(T v, // Floating-point value for Jv.
                                unsigned start_index, // 1-based start index.
                                unsigned number_of_zeros,
                                OutputIterator out_it,
                                const Policy& pol); // iterator into container for zeros. 

*/
//]  [/bessel_zero_example_1]

//[bessel_zero_example_iterator_1]
/*`We use the `cyl_bessel_j_zero` output iterator parameter `out_it` to create a sum of `1/zeros[super 2]`
by defining a custom output iterator:
*/

template <class T>
struct output_summation_iterator
{
   output_summation_iterator(T* p) : p_sum(p)
   {}
   output_summation_iterator& operator*()
   { return *this; }
    output_summation_iterator& operator++()
   { return *this; }
   output_summation_iterator& operator++(int)
   { return *this; }
   output_summation_iterator& operator = (T const& val)
   {
     *p_sum += 1./ (val * val); // Summing 1/zero^2.
     return *this;
   }
private:
   T* p_sum;
};

//] [/bessel_zero_example_iterator_1]

int main()
{
  try
  { 
//[bessel_zero_example_2]

/*`[tip It is always wise to place code using Boost.Math inside try'n'catch blocks;
this will ensure that helpful error messages are shown when exceptional conditions arise.]
*/

/*`First, evaluate a single Bessel zero.

The precision is controlled by the float-point type of template parameter `T` of `v`
so this example has `double` precision, at least 15 but up to 17 decimal digits.
*/
    double root = boost::math::cyl_bessel_j_zero(0.0, 1U);
    // Displaying with default precision of 6 decimal digits:
    std::cout << "boost::math::cyl_bessel_j_zero(0.0, 1U) " << root << std::endl; // 2.40483
    // And with all the guaranteed (15) digits:
    std::cout.precision(std::numeric_limits<double>::digits10);
    std::cout << "boost::math::cyl_bessel_j_zero(0.0, 1U) " << root << std::endl; // 2.40482555769577
/*`But note that because the parameter `v` controls the precision of the result,
it [*must be a floating-point type].
So if you provide an integer type, say 0, rather than 0.0, then it will fail to compile thus:
``
    root = boost::math::cyl_bessel_j_zero(0, 1U);
``
with this error message
``
  error C2338: Order must be a floating-point type.
``
*/
/*`Another version of `cyl_bessel_j_zero`  allows calculation of multiple zeros with one call,
placing the results in a container, often `std::vector`.
For example, generate five `double` roots of J[sub v] for integral order 2.

As column J[sub 2](x) in table 1 of
[@ http://mathworld.wolfram.com/BesselFunctionZeros.html Wolfram Bessel Function Zeros].

*/
    unsigned int n_roots = 5U;
    std::vector<double> roots;
    boost::math::cyl_bessel_j_zero(2.0, 1U, n_roots, std::back_inserter(roots));
    std::copy(roots.begin(),
              roots.end(),
              std::ostream_iterator<double>(std::cout, "\n"));

/*`Or generate 50 decimal digit roots of J[sub v] for non-integral order `v=71/19`.

We set the precision of the output stream and show trailing zeros to display a fixed 50 decimal digits.
*/  
    std::cout.precision(std::numeric_limits<float_type>::digits10); // 50 decimal digits.
    std::cout << std::showpoint << std::endl; // Show trailing zeros.

    float_type x = float_type(71) / 19;
    float_type r = boost::math::cyl_bessel_j_zero(x, 1U); // 1st root.
    std::cout << "x = " << x << ", r = " << r << std::endl;

    r = boost::math::cyl_bessel_j_zero(x, 20U); // 20th root.
    std::cout << "x = " << x << ", r = " << r << std::endl;

    std::vector<float_type> zeros(3); // Space for 10 roots.
    boost::math::cyl_bessel_j_zero(float_type(71) / 19, 1U, unsigned(zeros.size()), zeros.begin());

    // Print the roots to the output stream.
    std::copy(zeros.begin(), zeros.end(),
              std::ostream_iterator<float_type>(std::cout, "\n"));

/*`The Neumann functions zeros are evaluated very similarly:
*/
    using boost::math::cyl_neumann_zero;
    std::cout << "cyl_neumann_zero(2., 1U) = " << cyl_neumann_zero(2., 1U) << std::endl;

    std::vector<float> nzeros(3); // Space for 3 zeros.
    cyl_neumann_zero(2.F, 1U, unsigned(nzeros.size()), nzeros.begin());

    // Print the zeros to the output stream.
    std::copy(nzeros.begin(), nzeros.end(),
              std::ostream_iterator<float>(std::cout, "\n"));

/*`Finally we show how the output interator can be used to compute a sum of zeros.

See [@http://dx.doi.org/10.1017/S2040618500034067 Ian N. Sneddon, Infinite Sums of Bessel Zeros],
page 150 equation 40.
*/  
//] [/bessel_zero_example_2]

    {
//[bessel_zero_example_iterator_2]
/*`The sum is calculated for many values, converging on the analytical value of `1/8`.
*/
    using boost::math::cyl_bessel_j_zero;
    double nu = 1.;
    double sum = 0;
    output_summation_iterator<double> it(&sum);  // sum of 1/zeros^2
    cyl_bessel_j_zero(nu, 1u, 10000U, it);

    std::cout << std::setprecision(6) << "nu = " << nu << ", sum = " << sum << std::endl; 
    // nu = 1.0, sum = 0.124998986795763

    double s = 1/(4 * (nu + 1)); // 0.125 = 1/8 is exact analytical solution.
//] [/bessel_zero_example_iterator_2]
    }
  }
  catch (std::exception ex)
  {
    std::cout << "Throw exception " << ex.what() << std::endl;
  }

 } // int main()

/*
Mathematica: Table[N[BesselJZero[71/19, n], 50], {n, 1, 20, 1}]

7.2731751938316489503185694262290765588963196701623
10.724858308883141732536172745851416647110749599085
14.018504599452388106120459558042660282427471931581
17.25249845917041718216248716654977734919590383861
20.456678874044517595180234083894285885460502077814
23.64363089714234522494551422714731959985405172504
26.819671140255087745421311470965019261522390519297
29.988343117423674742679141796661432043878868194142
33.151796897690520871250862469973445265444791966114
36.3114160002162074157243540350393860813165201842
39.468132467505236587945197808083337887765967032029
42.622597801391236474855034831297954018844433480227
45.775281464536847753390206207806726581495950012439
48.926530489173566198367766817478553992471739894799
52.076607045343002794279746041878924876873478063472
55.225712944912571393594224327817265689059002890192
58.374006101538886436775188150439025201735151418932
61.521611873000965273726742659353136266390944103571
64.66863105379093036834648221487366079456596628716
67.815145619696290925556791375555951165111460585458

Mathematica: Table[N[BesselKZero[2, n], 50], {n, 1, 5, 1}]
n | 
1 | 3.3842417671495934727014260185379031127323883259329
2 | 6.7938075132682675382911671098369487124493222183854
3 | 10.023477979360037978505391792081418280789658279097


*/

 /*
[bessel_zero_output]
  boost::math::cyl_bessel_j_zero(0.0, 1U) 2.40483
  boost::math::cyl_bessel_j_zero(0.0, 1U) 2.40482555769577
  5.13562230184068
  8.41724414039986
  11.6198411721491
  14.7959517823513
  17.9598194949878
  
  x = 3.7368421052631578947368421052631578947368421052632, r = 7.2731751938316489503185694262290765588963196701623
  x = 3.7368421052631578947368421052631578947368421052632, r = 67.815145619696290925556791375555951165111460585458
  7.2731751938316489503185694262290765588963196701623
  10.724858308883141732536172745851416647110749599085
  14.018504599452388106120459558042660282427471931581
  cyl_neumann_zero(2., 1U) = 3.3842417671495935000000000000000000000000000000000
  3.3842418193817139000000000000000000000000000000000
  6.7938075065612793000000000000000000000000000000000
  10.023477554321289000000000000000000000000000000000
  nu = 1.00000, sum = 0.124990

] [/bessel_zero_output]
*/

