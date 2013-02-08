//  Copyright John Maddock 2013
//  Copyright Christopher Kormanyos 2013.
//  Copyright Paul A. Bristow 2013.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef _MSC_VER
#  pragma warning(disable : 4127) // conditional expression is constant.
#  pragma warning(disable : 4512) // assignment operator could not be generated.
#endif

//#include <pch_light.hpp> // commente dout during testing.

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/airy.hpp>

#include <boost/math/concepts/real_concept.hpp> // for real_concept
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp> // Boost.Test
#include <boost/test/floating_point_comparison.hpp>


#include <typeinfo>


// #include <boost/math/tools/
//
// DESCRIPTION:
// ~~~~~~~~~~~~
//
// This file tests the functions that evaluate zeros (or roots) of Bessel and Airy functions.

// Spot tests which compare our results with selected values computed 
// using the online special function calculator at functions.wolfram.com,
// and values generated with Boost.Multiprecision at about 1000-bit or 100 decimal digits precision.

// We are most grateful for the invaluable
// Weisstein, Eric W. "Bessel Function Zeros." From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/BesselFunctionZeros.html 
// and the newer http://www.wolframalpha.com/

// See also NIST Handbook of Mathetmatical Function http://dlmf.nist.gov/10.21
/*

The algorithms for estimating the roots of both cyl. Bessel
as well as cyl. Neumann have the same cross-over points,
and also use expansions that have the same order of approximation.

Therefore, tests will be equally effective for both functions
in the regions of order.

I have recently changed a critical cross-over in the algorithms
from a value of order of 1.2 to a value of order of 2.2.
In addition, there is a critical cross-over in the rank of the
zero from rank 1 to rank 2 and above. The first zero is
treated differently than the remaining ones.

So I would be most interested in various regions of order,
each one tested with about 20 zeros should suffice:
�   Order 219/100: This checks a region just below a critical cutoff
�   Order 221/100: This checks a region just above a critical cutoff
�   Order 0: Something always tends to go wrong at zero.
�   Order 1/1000: A small order
�   Order 71/19: Merely an intermediate order.
�   Order 7001/19: A medium-large order, small enough to retain moderate efficiency of calculation.
 
If we would like, we could add a few selected high zeros
such as the 1000th zero for a few modest orders such as 71/19, etc.

*/

template <class RealType>
void test_bessel_zeros(RealType)
{
  // Basic sanity checks for finding zeros of Bessel and Airy function.
  // where template parameter RealType can be float, double, long double,
  // or real_concept, a prototype for user-defined floating-point types.

  // Parameter RealType is only used to communicate the RealType, float, double...
  // and is an arbitrary zero for all tests.
   RealType tolerance = (std::max)(
     static_cast<RealType>(boost::math::tools::epsilon<long double>()),
     boost::math::tools::epsilon<RealType>());
   std::cout << "Tolerance for type " << typeid(RealType).name()  << " is " << tolerance << "." << std::endl;

   // http://www.wolframalpha.com/
   using boost::math::cyl_bessel_j_zero; // (nu, j) 
   using boost::math::isnan;

  if (std::numeric_limits<RealType>::has_quiet_NaN)
  {
    BOOST_CHECK(isnan(cyl_bessel_j_zero(static_cast<RealType>(0), 0U))); // yes - returns NaN - is this right?
  }

  // Abuse with infinity and max.
  if (std::numeric_limits<RealType>::has_infinity)
  {
    //BOOST_CHECK_EQUAL(cyl_bessel_j_zero(static_cast<RealType>(std::numeric_limits<RealType>::infinity()), 1U),
    //  static_cast<RealType>(std::numeric_limits<RealType>::infinity()) );
    // unknown location(0): fatal error in "test_main_caller( argc, argv )": 
    // class boost::exception_detail::clone_impl<struct boost::exception_detail::error_info_injector<class std::domain_error> >:
    // Error in function boost::math::cbrt<long double>(long double): Argument to function must be finite but got 1.#INF.
    //BOOST_CHECK_THROW(cyl_bessel_j_zero(static_cast<RealType>(std::numeric_limits<RealType>::infinity()), 1U),
    // std::domain_error);

  }
  //BOOST_CHECK_THROW(cyl_bessel_j_zero(boost::math::tools::max_value<RealType>(), 1U), std::domain_error);
   //   unknown location(0): fatal error in "test_main_caller( argc, argv )": 
   //class boost::exception_detail::clone_impl<struct boost::exception_detail::error_info_injector<class boost::math::rounding_error> >:
   //  Error in function boost::math::iround<double>(double): Value 3.4028234663852886e+038 can not be represented in the target integer type.

  // http://mathworld.wolfram.com/BesselFunctionZeros.html provides some spot values,
  // evaluation at 50 deciaml digits using WoldramAlpha.

  /* Table[N[BesselJZero[0, n], 50], {n, 1, 5, 1}]
  n | 
  1 | 2.4048255576957727686216318793264546431242449091460
  2 | 5.5200781102863106495966041128130274252218654787829
  3 | 8.6537279129110122169541987126609466855657952312754
  4 | 11.791534439014281613743044911925458922022924699695
  5 | 14.930917708487785947762593997388682207915850115633
  */
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(0), 1U), static_cast<RealType>(2.4048255576957727686216318793264546431242449091460L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(0), 2U), static_cast<RealType>(5.5200781102863106495966041128130274252218654787829L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(0), 3U), static_cast<RealType>(8.6537279129110122169541987126609466855657952312754L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(0), 4U), static_cast<RealType>(11.791534439014281613743044911925458922022924699695L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(0), 5U), static_cast<RealType>(14.930917708487785947762593997388682207915850115633L), tolerance);

  { // Same test using the multiple zeros version.
    std::vector<RealType> zeros;
    cyl_bessel_j_zero(static_cast<RealType>(0.0), 1U, 3, std::back_inserter(zeros) );
    BOOST_CHECK_CLOSE_FRACTION(zeros[0], static_cast<RealType>(2.4048255576957727686216318793264546431242449091460L), tolerance);
    BOOST_CHECK_CLOSE_FRACTION(zeros[1], static_cast<RealType>(5.5200781102863106495966041128130274252218654787829L), tolerance);
    BOOST_CHECK_CLOSE_FRACTION(zeros[2], static_cast<RealType>(8.6537279129110122169541987126609466855657952312754L), tolerance);
  }
  // 1/1000 a small order.
  /* Table[N[BesselJZero[1/1000, n], 50], {n, 1, 4, 1}]
  n | 
1 | 2.4063682720422009275161970278295108254321633626292
2 | 5.5216426858401848664019464270992222126391378706092
3 | 8.6552960859298799453893840513333150237193779482071
4 | 11.793103797689738596231262077785930962647860975357

Table[N[BesselJZero[1/1000, n], 50], {n, 10, 20, 1}]
n | 
10 | 30.636177039613574749066837922778438992469950755736
11 | 33.777390823252864715296422192027816488172667994611
12 | 36.918668992567585467000743488690258054442556198147
13 | 40.059996426251227493370316149043896483196561190610
14 | 43.201362392820317233698309483240359167380135262681
15 | 46.342759065846108737848449985452774243376260538634
16 | 49.484180603489984324820981438067325210499739716337
17 | 52.625622557085775090390071484188995092211215108718
18 | 55.767081479279692992978326069855684800673801918763
19 | 58.908554657366270044071505013449016741804538135905
20 | 62.050039927521244984641179233170843941940575857282

*/

  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(1)/1000, 1U), static_cast<RealType>(2.4063682720422009275161970278295108254321633626292L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(1)/1000, 4U), static_cast<RealType>(11.793103797689738596231262077785930962647860975357L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(1)/1000, 10U), static_cast<RealType>(30.636177039613574749066837922778438992469950755736L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(1)/1000, 20U), static_cast<RealType>(62.050039927521244984641179233170843941940575857282L), tolerance);

    /*
  Table[N[BesselJZero[1, n], 50], {n, 1, 4, 1}]
  n | 
  1 | 3.8317059702075123156144358863081607665645452742878
  2 | 7.0155866698156187535370499814765247432763115029142
  3 | 10.173468135062722077185711776775844069819512500192
  4 | 13.323691936314223032393684126947876751216644731358
  */

  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(1), 1U), static_cast<RealType>(3.8317059702075123156144358863081607665645452742878L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(1), 2U), static_cast<RealType>(7.0155866698156187535370499814765247432763115029142L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(1), 3U), static_cast<RealType>(10.173468135062722077185711776775844069819512500192L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(1), 4U), static_cast<RealType>(13.323691936314223032393684126947876751216644731358L), tolerance);

  /*
  Table[N[BesselJZero[5, n], 50], {n, 1, 5, 1}]
  n | 
  1 | 8.7714838159599540191228671334095605629810770148974
  2 | 12.338604197466943986082097644459004412683491122239
  3 | 15.700174079711671037587715595026422501346662246893
  4 | 18.980133875179921120770736748466932306588828411497
  5 | 22.217799896561267868824764947529187163096116704354
*/

  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(5), 1U), static_cast<RealType>(8.7714838159599540191228671334095605629810770148974L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(5), 2U), static_cast<RealType>(12.338604197466943986082097644459004412683491122239L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(5), 3U), static_cast<RealType>(15.700174079711671037587715595026422501346662246893L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(5), 4U), static_cast<RealType>(18.980133875179921120770736748466932306588828411497L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(5), 5U), static_cast<RealType>(22.217799896561267868824764947529187163096116704354L), tolerance);

  // An intermediate order
  /*
  Table[N[BesselJZero[71/19, n], 50], {n, 1, 20, 1}]

  7.27317519383164895031856942622907655889631967016227,
  10.7248583088831417325361727458514166471107495990849, 
  14.0185045994523881061204595580426602824274719315813, 
  17.2524984591704171821624871665497773491959038386104, 
  20.4566788740445175951802340838942858854605020778141, 
  23.6436308971423452249455142271473195998540517250404, 
  26.8196711402550877454213114709650192615223905192969, 
  29.9883431174236747426791417966614320438788681941419, 
  33.1517968976905208712508624699734452654447919661140, 
  36.3114160002162074157243540350393860813165201842005, 
  39.4681324675052365879451978080833378877659670320292, 
  42.6225978013912364748550348312979540188444334802274, 
  45.7752814645368477533902062078067265814959500124386, 
  48.9265304891735661983677668174785539924717398947994, 
  52.0766070453430027942797460418789248768734780634716, 
  55.2257129449125713935942243278172656890590028901917, 
  58.3740061015388864367751881504390252017351514189321, 
  61.5216118730009652737267426593531362663909441035715, 
  64.6686310537909303683464822148736607945659662871596, 
  67.8151456196962909255567913755559511651114605854579
  */
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(71)/19, 1U), static_cast<RealType>(7.27317519383164895031856942622907655889631967016227L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(71)/19, 4U), static_cast<RealType>(17.2524984591704171821624871665497773491959038386104L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(71)/19, 10U), static_cast<RealType>(36.3114160002162074157243540350393860813165201842005L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(71)/19, 20U), static_cast<RealType>(67.8151456196962909255567913755559511651114605854579L), tolerance);
  /*

  Table[N[BesselJZero[7001/19, n], 50], {n, 1, 2, 1}]

1 | 381.92201523024489386917204470434842699154031135348
2 | 392.17508657648737502651299853099852567001239217724

Table[N[BesselJZero[7001/19, n], 50], {n, 19, 20, 1}]
 
19 | 491.67809669154347398205298745712766193052308172472
20 | 496.39435037938252557535375498577989720272298310802

  */
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(7001)/19, 1U), static_cast<RealType>(381.92201523024489386917204470434842699154031135348L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(7001)/19, 2U), static_cast<RealType>(392.17508657648737502651299853099852567001239217724L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(7001)/19, 20U), static_cast<RealType>(496.39435037938252557535375498577989720272298310802L), tolerance);

  // Some non-integral tests.
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(3.73684210526315789473684210526315789473684210526315789L), 1U), static_cast<RealType>(7.273175193831648950318569426229076558896319670162279791988152000556091140599946365217211157877052381L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(3.73684210526315789473684210526315789473684210526315789L), 20U), static_cast<RealType>(67.81514561969629092555679137555595116511146058545787883557679231060644931096494584364894743334132014L), tolerance);

  // Some non-integral tests in 'tough' regions. 
  // Order 219/100: This checks a region just below a critical cutoff.
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(219)/100, 1U), static_cast<RealType>(5.37568854370623186731066365697341253761466705063679L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(219)/100, 2U), static_cast<RealType>(8.67632060963888122764226633146460596009874991130394L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(219)/100, 20U), static_cast<RealType>(65.4517712237598926858973399895944886397152223643028L), tolerance);
  // Order 221/100: This checks a region just above a critical cutoff.
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(221)/100, 1U), static_cast<RealType>(5.40084731984998184087380740054933778965260387203942L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(221)/100, 2U), static_cast<RealType>(8.70347906513509618445695740167369153761310106851599L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(221)/100, 20U), static_cast<RealType>(65.4825314862621271716158606625527548818843845600782L), tolerance);

  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(7001)/19, 1U), static_cast<RealType>(381.922015230244893869172044704348426991540311353476L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(7001)/19, 2U), static_cast<RealType>(392.175086576487375026512998530998525670012392177242L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_bessel_j_zero(static_cast<RealType>(7001)/19, 20U), static_cast<RealType>(496.394350379382525575353754985779897202722983108025L), tolerance);
  
  //BOOST_CHECK_THROW(boost::math::cyl_bessel_j_zero(static_cast<RealType>(0), -1), std::domain_error);
  //  warning C4245: 'argument' : conversion from 'int' to 'unsigned int', signed/unsigned mismatch

  //BOOST_CHECK_THROW(boost::math::cyl_bessel_j_zero(static_cast<RealType>(std::numeric_limits<RealType>::quiet_NaN()), -1), std::domain_error); // OK if unsigned.
  // doesn't throw :-(

  if (std::numeric_limits<RealType>::has_quiet_NaN)
  {
    BOOST_CHECK_THROW(cyl_bessel_j_zero(static_cast<RealType>(std::numeric_limits<RealType>::quiet_NaN()), 1U), std::domain_error);
  }
 // BOOST_CHECK_THROW(cyl_bessel_j_zero(static_cast<RealType>(std::numeric_limits<RealType>::infinity()), 0U), std::domain_error);
  //BOOST_CHECK_THROW(boost::math::cyl_bessel_j_zero(static_cast<RealType>(std::numeric_limits<RealType>::infinity()), -1), std::domain_error); // OK if unsigned.
  if (std::numeric_limits<RealType>::has_infinity)
  {
     BOOST_CHECK_THROW(cyl_bessel_j_zero(static_cast<RealType>(std::numeric_limits<RealType>::infinity()), 1U), std::domain_error);
  }
  
  // Tests of cyc_neumann zero function (BesselKZero in Wolfram).

  /*
  Table[N[BesselKZero[0, n], 50], {n, 1, 5, 1}]
n | 
1 | 0.89357696627916752158488710205833824122514686193001
2 | 3.9576784193148578683756771869174012814186037655636
3 | 7.0860510603017726976236245968203524689715103811778
4 | 10.222345043496417018992042276342187125994059613181
5 | 13.361097473872763478267694585713786426579135174880

Table[N[BesselKZero[1, n], 50], {n, 1, 5, 1}]
n | 
1 | 2.1971413260310170351490335626989662730530183315003
2 | 5.4296810407941351327720051908525841965837574760291
3 | 8.5960058683311689264296061801639678511029215669749
4 | 11.749154830839881243399421939922350714301165983279
5 | 14.897442128336725378844819156429870879807150630875

Table[N[BesselKZero[2, n], 50], {n, 1, 5, 1}]
n | 
1 | 3.3842417671495934727014260185379031127323883259329
2 | 6.7938075132682675382911671098369487124493222183854
3 | 10.023477979360037978505391792081418280789658279097
4 | 13.209986710206416382780863125329852185107588501072
5 | 16.378966558947456561726714466123708444627678549687

*/
  // Some simple integer values.

  using boost::math::cyl_neumann_zero;

  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(0), 1U), static_cast<RealType>(0.89357696627916752158488710205833824122514686193001L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(1), 2U), static_cast<RealType>(5.4296810407941351327720051908525841965837574760291L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(2), 3U), static_cast<RealType>(10.023477979360037978505391792081418280789658279097L), tolerance);
  
  { // Repeat rest using multiple zeros version.
    std::vector<RealType> zeros;
    cyl_neumann_zero(static_cast<RealType>(0.0), 1, 3, std::back_inserter(zeros) );
    BOOST_CHECK_CLOSE_FRACTION(zeros[0], static_cast<RealType>(0.89357696627916752158488710205833824122514686193001L), tolerance);
    BOOST_CHECK_CLOSE_FRACTION(zeros[1], static_cast<RealType>(3.9576784193148578683756771869174012814186037655636L), tolerance);
    BOOST_CHECK_CLOSE_FRACTION(zeros[2], static_cast<RealType>(7.0860510603017726976236245968203524689715103811778L), tolerance);
  }
  // Order 0: Something always tends to go wrong at zero.

  // TODO ???

  /* Order 219/100: This checks a region just below a critical cutoff.

  Table[N[BesselKZero[219/100, n], 50], {n, 1, 20, 4}]

1 | 3.6039149425338727979151181355741147312162055042157
5 | 16.655399111666833825247894251535326778980614938275
9 | 29.280564448169163756478439692311605757712873534942
13 | 41.870269811145814760551599481942750124112093564643
17 | 54.449180021209532654553613813754733514317929678038
  */
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(219)/100, 1U), static_cast<RealType>(3.6039149425338727979151181355741147312162055042157L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(219)/100, 5U), static_cast<RealType>(16.655399111666833825247894251535326778980614938275L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(219)/100, 17U), static_cast<RealType>(54.449180021209532654553613813754733514317929678038L), tolerance);

  /* Order 221/100: This checks a region just above a critical cutoff.

  Table[N[BesselKZero[220/100, n], 50], {n, 1, 20, 5}]

  1 | 3.6154383428745996706772556069431792744372398748425
  6 | 19.833435100254138641131431268153987585842088078470
  11 | 35.592602956438811360473753622212346081080817891225
  16 | 51.320322762482062633162699745957897178885350674038
  */

  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(220)/100, 1U), static_cast<RealType>(3.6154383428745996706772556069431792744372398748425L), tolerance);
  // cyl_neumann_zero(static_cast<RealType>(220)/100, 1U){3.6154383428746009} 
  //and                             static_cast<RealType>(3.6154383428745996706772556069431792744372398748425L)
  //                                                     {3.6154383428745995}
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(220)/100, 6U), static_cast<RealType>(19.833435100254138641131431268153987585842088078470L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(220)/100, 11U), static_cast<RealType>(35.592602956438811360473753622212346081080817891225L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(220)/100, 16U), static_cast<RealType>(51.320322762482062633162699745957897178885350674038L), tolerance);

  /*  Order 1/1000: A small order.

  Table[N[BesselKZero[1/1000, n], 50], {n, 1, 20, 5}]

  1 | 0.89502371604431360670577815537297733265776195646969
  6 | 16.502492490954716850993456703662137628148182892787
  11 | 32.206774708309182755790609144739319753463907110990
  16 | 47.913467031941494147962476920863688176374357572509
  */

  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(1)/1000, 1U), static_cast<RealType>(0.89502371604431360670577815537297733265776195646969L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(1)/1000, 6U), static_cast<RealType>(16.5024924909547168509934567036621376281481828927870L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(1)/1000, 11U), static_cast<RealType>(32.206774708309182755790609144739319753463907110990L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(1)/1000, 16U), static_cast<RealType>(47.913467031941494147962476920863688176374357572509L), tolerance);

  /* Order 71/19: Merely an intermediate order.

  Table[N[BesselKZero[71/19, n], 50], {n, 1, 20, 5}]

  1 | 5.3527167881149432911848659069476821793319749146616
  6 | 22.051823727778538215953091664153117627848857279151
  11 | 37.890091170552491176745048499809370107665221628364
  16 | 53.651270581421816017744203789836444968181687858095
  */
    BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(71)/19, 1U), static_cast<RealType>(5.3527167881149432911848659069476821793319749146616L), tolerance);
    BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(71)/19, 6U), static_cast<RealType>(22.051823727778538215953091664153117627848857279151L), tolerance);
    BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(71)/19, 11U), static_cast<RealType>(37.890091170552491176745048499809370107665221628364L), tolerance);
    BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(71)/19, 16U), static_cast<RealType>(53.651270581421816017744203789836444968181687858095L), tolerance);


  /* Order 7001/19: A medium-large order, small enough to retain moderate efficiency of calculation.

  Table[N[BesselKZero[7001/19, n], 50], {n, 1}]

   1 | 375.18866334770357669101711932706658671250621098115

  Table[N[BesselKZero[7001/19, n], 50], {n, 2}]
  Standard computation time exceeded :-(
  */
  BOOST_CHECK_CLOSE_FRACTION(cyl_neumann_zero(static_cast<RealType>(7001)/19, 1U), static_cast<RealType>(375.18866334770357669101711932706658671250621098115L), tolerance);

 /* A high zero such as the 1000th zero for a modest order such as 71/19.

   Table[N[BesselKZero[71/19, n], 50], {n, 1000}]
   Standard computation time exceeded :-(
 */

// Tests of Airy zeros.


/*  The algorithms use tabulated values for the first 10 zeros,
whereby algorithms are used for rank 11 and higher.
So testing the zeros of Ai and Bi from 1 through 20 handles
this cross-over nicely.

In addition, the algorithms for the estimates of the zeros
become increasingly accurate for larger, negative argument.

On the other hand, the zeros become increasingly close
for large, negative argument. So another nice test
involves testing pairs of zeros for different orders of
magnitude of the zeros, to insure that the program
properly resolves very closely spaced zeros.
*/

  // Test Data for airy_ai
   using boost::math::airy_ai_zero; // 

   using boost::math::isnan;

  if (std::numeric_limits<RealType>::has_quiet_NaN)
  {
    BOOST_CHECK(isnan(airy_ai_zero<RealType>(0)) );
  }

  // Can't abuse with infinity because won't compile - no conversion.
  //if (std::numeric_limits<RealType>::has_infinity)
  //{
  //  BOOST_CHECK(isnan(airy_bi_zero<RealType>(std::numeric_limits<RealType>::infinity)) );
  //}


  // WolframAlpha  Table[N[AiryAiZero[n], 51], {n, 1, 20, 1}]

  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(1U), static_cast<RealType>(-2.33810741045976703848919725244673544063854014567239L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(2U), static_cast<RealType>(-4.08794944413097061663698870145739106022476469910853L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(3U), static_cast<RealType>(-5.52055982809555105912985551293129357379721428061753L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(4U), static_cast<RealType>(-6.78670809007175899878024638449617696605388247739349L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(5U), static_cast<RealType>(-7.94413358712085312313828055579826853214067439697221L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(6U), static_cast<RealType>(-9.02265085334098038015819083988008925652467753515608L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(7U), static_cast<RealType>(-10.0401743415580859305945567373625180940429025691058L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(8U), static_cast<RealType>(-11.0085243037332628932354396495901510167308253815040L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(9U), static_cast<RealType>(-11.9360155632362625170063649029305843155778862321198L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(10U), static_cast<RealType>(-12.8287767528657572004067294072418244773864155995734L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(11U), static_cast<RealType>(-13.6914890352107179282956967794669205416653698092008L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(12U), static_cast<RealType>(-14.5278299517753349820739814429958933787141648698348L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(13U), static_cast<RealType>(-15.3407551359779968571462085134814867051175833202480L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(14U), static_cast<RealType>(-16.1326851569457714393459804472025217905182723970763L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(15U), static_cast<RealType>(-16.9056339974299426270352387706114765990900510950317L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(16U), static_cast<RealType>(-17.6613001056970575092536503040180559521532186681200L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(17U), static_cast<RealType>(-18.4011325992071154158613979295043367545938146060201L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(18U), static_cast<RealType>(-19.1263804742469521441241486897324946890754583847531L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(19U), static_cast<RealType>(-19.8381298917214997009475636160114041983356824945389L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(20U), static_cast<RealType>(-20.5373329076775663599826814113081017453042180147375L), tolerance);

  // Table[N[AiryAiZero[n], 51], {n, 1000, 1001, 1}]

  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(1000U), static_cast<RealType>(-281.031519612521552835336363963709689055717463965420L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(1001U), static_cast<RealType>(-281.218889579130068414512015874511112547569713693446L), tolerance);

  // Table[N[AiryAiZero[n], 51], {n, 1000000, 1000001, 1}]
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(1000000U), static_cast<RealType>(-28107.8319793795834876064419863203282898723750036048L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(1000001U), static_cast<RealType>(-28107.8507179357979542838020057465277368471496446555L), tolerance);


  // Table[N[AiryAiZero[n], 51], {n, 1000000000, 1000000001, 1}]
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(1000000000U), static_cast<RealType>(-2.81078366593344513918947921096193426320298300481145E+6L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_ai_zero<RealType>(1000000001U), static_cast<RealType>(-2.81078366780730091663459728526906320267920607427246E+6L), tolerance);

  // Test Data for airy_bi
  using boost::math::airy_bi_zero;

  if (std::numeric_limits<RealType>::has_quiet_NaN)
  {
    BOOST_CHECK(isnan(airy_bi_zero<RealType>(0)) );
  }

  // Can't abuse with infinity because won't compile - no conversion.
  //if (std::numeric_limits<RealType>::has_infinity)
  //{
  //  BOOST_CHECK(isnan(airy_bi_zero<RealType>(std::numeric_limits<RealType>::infinity)) );
  //}

  // Table[N[AiryBiZero[n], 51], {n, 1, 20, 1}]
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(1U), static_cast<RealType>(-1.17371322270912792491997996247390210454364638917570L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(2U), static_cast<RealType>(-3.27109330283635271568022824016641380630093596910028L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(3U), static_cast<RealType>(-4.83073784166201593266770933990517817696614261732301L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(4U), static_cast<RealType>(-6.16985212831025125983336452055593667996554943427563L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(5U), static_cast<RealType>(-7.37676207936776371359995933044254122209152229939710L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(6U), static_cast<RealType>(-8.49194884650938801344803949280977672860508755505546L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(7U), static_cast<RealType>(-9.53819437934623888663298854515601962083907207638247L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(8U), static_cast<RealType>(-10.5299135067053579244005555984531479995295775946214L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(9U), static_cast<RealType>(-11.4769535512787794379234649247328196719482538148877L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(10U), static_cast<RealType>(-12.3864171385827387455619015028632809482597983846856L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(11U), static_cast<RealType>(-13.2636395229418055541107433243954907752411519609813L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(12U), static_cast<RealType>(-14.1127568090686577915873097822240184716840428285509L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(13U),  static_cast<RealType>(-14.9370574121541640402032143104909046396121763517782L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(14U), static_cast<RealType>(-15.7392103511904827708949784797481833807180162767841L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(15U), static_cast<RealType>(-16.5214195506343790539179499652105457167110310370581L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(16U), static_cast<RealType>(-17.2855316245812425329342366922535392425279753602710L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(17U), static_cast<RealType>(-18.0331132872250015721711125433391920008087291416406L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(18U), static_cast<RealType>(-18.7655082844800810413429789236105128440267189551421L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(19U), static_cast<RealType>(-19.4838801329892340136659986592413575122062977793610L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(20U), static_cast<RealType>(-20.1892447853962024202253232258275360764649783583934L), tolerance);


 // Table[N[AiryBiZero[n], 51], {n, 1000, 1001, 1}]
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(1000U), static_cast<RealType>(-280.937811203415240157883427412260300146245056425646L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(1001U), static_cast<RealType>(-281.125212400956392021977771104562061554648675044114L), tolerance);

  // Table[N[AiryBiZero[n], 51], {n, 1000000, 1000001, 1}]
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(1000000U), static_cast<RealType>(-28107.8226100991339342855024130953986989636667226163L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(1000001U), static_cast<RealType>(-28107.8413486584714939255315213519230566014624895515L), tolerance);

  //Table[N[AiryBiZero[n], 51], {n, 1000000000, 1000000001, 1}]
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(1000000000U), static_cast<RealType>(-2.81078366499651725023268820158218492845371527054171E+6L), tolerance);
  BOOST_CHECK_CLOSE_FRACTION(airy_bi_zero<RealType>(1000000001U), static_cast<RealType>(-2.81078366687037302799011557215619265502627118526716E+6L), tolerance);
  
} // template <class RealType> void test_spots(RealType)

BOOST_AUTO_TEST_CASE(test_main)
{
   test_bessel_zeros(0.1F);
   test_bessel_zeros(0.1);
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
   test_bessel_zeros(0.1L);
#ifndef BOOST_MATH_NO_REAL_CONCEPT_TESTS
   test_bessel_zeros(boost::math::concepts::real_concept(0.1));
#endif
#else
   std::cout << "<note>The long double tests have been disabled on this platform "
      "either because the long double overloads of the usual math functions are "
      "not available at all, or because they are too inaccurate for these tests "
      "to pass.</note>" << std::cout;
#endif
} 




