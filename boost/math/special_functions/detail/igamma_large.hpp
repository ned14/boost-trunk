//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This file implements the asymptotic expansions of the incomplete
// gamma functions P(a, x) and Q(a, x), used when a is large and
// x ~ a.
//
// The primary reference is:
//
// "The Asymptotic Expansion of the Incomplete Gamma Functions"
// N. M. Temme.
// Siam J. Math Anal. Vol 10 No 4, July 1979, p757.
//
// A different way of evaluating these expansions,
// plus a lot of very useful background information is in:
// 
// "A Set of Algorithms For the Incomplete Gamma Functions."
// N. M. Temme.
// Probability in the Engineering and Informational Sciences,
// 8, 1994, 291.
//
// An alternative implementation is in:
//
// "Computation of the Incomplete Gamma Function Ratios and their Inverse."
// A. R. Didonato and A. H. Morris.
// ACM TOMS, Vol 12, No 4, Dec 1986, p377.
//
// There are various versions of the same code below, each accurate
// to a different precision.  To understand the code, refer to Didonato
// and Morris, from Eq 17 and 18 onwards.
//
// The coefficients used here are not taken from Didonato and Morris:
// the domain over which these expansions are used is slightly different
// to theirs, and their constants are not quite accurate enough for
// 128-bit long double's.  Instead the coefficients were calculated
// using the methods described by Temme p762 from Eq 3.8 onwards.
// The values obtained agree with those obtained by Didonato and Morris
// (at least to the first 30 digits that they provide).
// At double precision the degrees of polynomial required for full
// machine precision are close to those recomended to Didonato and Morris,
// but of course many more terms are needed for larger types.
//
#ifndef BOOST_MATH_DETAIL_IGAMMA_LARGE
#define BOOST_MATH_DETAIL_IGAMMA_LARGE

#ifdef _MSC_VER
#pragma once
#endif

namespace boost{ namespace math{ namespace detail{

// This version will never be called (at runtime), it's a stub used
// when T is unsuitable to be passed to these routines:
//
template <class T, class Policy>
inline T igamma_temme_large(T, T, const Policy& /* pol */, mpl::int_<0> const *)
{
   // stub function, should never actually be called
   BOOST_ASSERT(0);
   return 0;
}
//
// This version is accurate for up to 64-bit mantissa's, 
// (80-bit long double, or 10^-20).
//
template <class T, class Policy>
T igamma_temme_large(T a, T x, const Policy& pol, mpl::int_<64> const *)
{
   BOOST_MATH_STD_USING // ADL of std functions
   T sigma = (x - a) / a;
   T phi = -boost::math::log1pmx(sigma, pol);
   T y = a * phi;
   T z = sqrt(2 * phi);
   if(x < a)
      z = -z;

   T workspace[13];

   static const T C0[] = {
      -0.333333333333333333333L,
      0.0833333333333333333333L,
      -0.0148148148148148148148L,
      0.00115740740740740740741L,
      0.000352733686067019400353L,
      -0.0001787551440329218107L,
      0.39192631785224377817e-4L,
      -0.218544851067999216147e-5L,
      -0.18540622107151599607e-5L,
      0.829671134095308600502e-6L,
      -0.176659527368260793044e-6L,
      0.670785354340149858037e-8L,
      0.102618097842403080426e-7L,
      -0.438203601845335318655e-8L,
      0.914769958223679023418e-9L,
      -0.255141939949462497669e-10L,
      -0.583077213255042506746e-10L,
      0.243619480206674162437e-10L,
      -0.502766928011417558909e-11L,
   };
   workspace[0] = tools::evaluate_polynomial(C0, z);

   static const T C1[] = {
      -0.00185185185185185185185L,
      -0.00347222222222222222222L,
      0.00264550264550264550265L,
      -0.000990226337448559670782L,
      0.000205761316872427983539L,
      -0.40187757201646090535e-6L,
      -0.18098550334489977837e-4L,
      0.764916091608111008464e-5L,
      -0.161209008945634460038e-5L,
      0.464712780280743434226e-8L,
      0.137863344691572095931e-6L,
      -0.575254560351770496402e-7L,
      0.119516285997781473243e-7L,
      -0.175432417197476476238e-10L,
      -0.100915437106004126275e-8L,
      0.416279299184258263623e-9L,
      -0.856390702649298063807e-10L,
   };
   workspace[1] = tools::evaluate_polynomial(C1, z);

   static const T C2[] = {
      0.00413359788359788359788L,
      -0.00268132716049382716049L,
      0.000771604938271604938272L,
      0.200938786008230452675e-5L,
      -0.000107366532263651605215L,
      0.529234488291201254164e-4L,
      -0.127606351886187277134e-4L,
      0.342357873409613807419e-7L,
      0.137219573090629332056e-5L,
      -0.629899213838005502291e-6L,
      0.142806142060642417916e-6L,
      -0.204770984219908660149e-9L,
      -0.140925299108675210533e-7L,
      0.622897408492202203356e-8L,
      -0.136704883966171134993e-8L,
   };
   workspace[2] = tools::evaluate_polynomial(C2, z);

   static const T C3[] = {
      0.000649434156378600823045L,
      0.000229472093621399176955L,
      -0.000469189494395255712128L,
      0.000267720632062838852962L,
      -0.756180167188397641073e-4L,
      -0.239650511386729665193e-6L,
      0.110826541153473023615e-4L,
      -0.56749528269915965675e-5L,
      0.142309007324358839146e-5L,
      -0.278610802915281422406e-10L,
      -0.169584040919302772899e-6L,
      0.809946490538808236335e-7L,
      -0.191111684859736540607e-7L,
   };
   workspace[3] = tools::evaluate_polynomial(C3, z);

   static const T C4[] = {
      -0.000861888290916711698605L,
      0.000784039221720066627474L,
      -0.000299072480303190179733L,
      -0.146384525788434181781e-5L,
      0.664149821546512218666e-4L,
      -0.396836504717943466443e-4L,
      0.113757269706784190981e-4L,
      0.250749722623753280165e-9L,
      -0.169541495365583060147e-5L,
      0.890750753220530968883e-6L,
      -0.229293483400080487057e-6L,
   };
   workspace[4] = tools::evaluate_polynomial(C4, z);

   static const T C5[] = {
      -0.000336798553366358150309L,
      -0.697281375836585777429e-4L,
      0.000277275324495939207873L,
      -0.000199325705161888477003L,
      0.679778047793720783882e-4L,
      0.141906292064396701483e-6L,
      -0.135940481897686932785e-4L,
      0.801847025633420153972e-5L,
      -0.229148117650809517038e-5L,
   };
   workspace[5] = tools::evaluate_polynomial(C5, z);

   static const T C6[] = {
      0.000531307936463992223166L,
      -0.000592166437353693882865L,
      0.000270878209671804482771L,
      0.790235323266032787212e-6L,
      -0.815396936756196875093e-4L,
      0.561168275310624965004e-4L,
      -0.183291165828433755673e-4L,
      -0.307961345060330478256e-8L,
      0.346515536880360908674e-5L,
      -0.20291327396058603727e-5L,
      0.57887928631490037089e-6L,
   };
   workspace[6] = tools::evaluate_polynomial(C6, z);

   static const T C7[] = {
      0.000344367606892377671254L,
      0.517179090826059219337e-4L,
      -0.000334931610811422363117L,
      0.000281269515476323702274L,
      -0.000109765822446847310235L,
      -0.127410090954844853795e-6L,
      0.277444515115636441571e-4L,
      -0.182634888057113326614e-4L,
      0.578769494973505239894e-5L,
   };
   workspace[7] = tools::evaluate_polynomial(C7, z);

   static const T C8[] = {
      -0.000652623918595309418922L,
      0.000839498720672087279993L,
      -0.000438297098541721005061L,
      -0.696909145842055197137e-6L,
      0.000166448466420675478374L,
      -0.000127835176797692185853L,
      0.462995326369130429061e-4L,
   };
   workspace[8] = tools::evaluate_polynomial(C8, z);

   static const T C9[] = {
      -0.000596761290192746250124L,
      -0.720489541602001055909e-4L,
      0.000678230883766732836162L,
      -0.0006401475260262758451L,
      0.000277501076343287044992L,
   };
   workspace[9] = tools::evaluate_polynomial(C9, z);

   static const T C10[] = {
      0.00133244544948006563713L,
      -0.0019144384985654775265L,
      0.00110893691345966373396L,
   };
   workspace[10] = tools::evaluate_polynomial(C10, z);

   static const T C11[] = {
      0.00157972766073083495909L,
      0.000162516262783915816899L,
      -0.00206334210355432762645L,
      0.00213896861856890981541L,
      -0.00101085593912630031708L,
   };
   workspace[11] = tools::evaluate_polynomial(C11, z);

   static const T C12[] = {
      -0.00407251211951401664727L,
      0.00640336283380806979482L,
      -0.00404101610816766177474L,
   };
   workspace[12] = tools::evaluate_polynomial(C12, z);

   T result = tools::evaluate_polynomial<13, T, T>(workspace, 1/a);
   result *= exp(-y) / sqrt(2 * constants::pi<T>() * a);
   if(x < a)
      result = -result;

   result += boost::math::erfc(sqrt(y), pol) / 2;

   return result;
}
//
// This one is accurate for 53-bit mantissa's
// (IEEE double precision or 10^-17).
//
template <class T, class Policy>
T igamma_temme_large(T a, T x, const Policy& pol, mpl::int_<53> const *)
{
   BOOST_MATH_STD_USING // ADL of std functions
   T sigma = (x - a) / a;
   T phi = -boost::math::log1pmx(sigma, pol);
   T y = a * phi;
   T z = sqrt(2 * phi);
   if(x < a)
      z = -z;

   T workspace[10];

   static const T C0[] = {
      static_cast<T>(-0.33333333333333333L),
      static_cast<T>(0.083333333333333333L),
      static_cast<T>(-0.014814814814814815L),
      static_cast<T>(0.0011574074074074074L),
      static_cast<T>(0.0003527336860670194L),
      static_cast<T>(-0.00017875514403292181L),
      static_cast<T>(0.39192631785224378e-4L),
      static_cast<T>(-0.21854485106799922e-5L),
      static_cast<T>(-0.185406221071516e-5L),
      static_cast<T>(0.8296711340953086e-6L),
      static_cast<T>(-0.17665952736826079e-6L),
      static_cast<T>(0.67078535434014986e-8L),
      static_cast<T>(0.10261809784240308e-7L),
      static_cast<T>(-0.43820360184533532e-8L),
      static_cast<T>(0.91476995822367902e-9L),
   };
   workspace[0] = tools::evaluate_polynomial(C0, z);

   static const T C1[] = {
      static_cast<T>(-0.0018518518518518519L),
      static_cast<T>(-0.0034722222222222222L),
      static_cast<T>(0.0026455026455026455L),
      static_cast<T>(-0.00099022633744855967L),
      static_cast<T>(0.00020576131687242798L),
      static_cast<T>(-0.40187757201646091e-6L),
      static_cast<T>(-0.18098550334489978e-4L),
      static_cast<T>(0.76491609160811101e-5L),
      static_cast<T>(-0.16120900894563446e-5L),
      static_cast<T>(0.46471278028074343e-8L),
      static_cast<T>(0.1378633446915721e-6L),
      static_cast<T>(-0.5752545603517705e-7L),
      static_cast<T>(0.11951628599778147e-7L),
   };
   workspace[1] = tools::evaluate_polynomial(C1, z);

   static const T C2[] = {
      static_cast<T>(0.0041335978835978836L),
      static_cast<T>(-0.0026813271604938272L),
      static_cast<T>(0.00077160493827160494L),
      static_cast<T>(0.20093878600823045e-5L),
      static_cast<T>(-0.00010736653226365161L),
      static_cast<T>(0.52923448829120125e-4L),
      static_cast<T>(-0.12760635188618728e-4L),
      static_cast<T>(0.34235787340961381e-7L),
      static_cast<T>(0.13721957309062933e-5L),
      static_cast<T>(-0.6298992138380055e-6L),
      static_cast<T>(0.14280614206064242e-6L),
   };
   workspace[2] = tools::evaluate_polynomial(C2, z);

   static const T C3[] = {
      static_cast<T>(0.00064943415637860082L),
      static_cast<T>(0.00022947209362139918L),
      static_cast<T>(-0.00046918949439525571L),
      static_cast<T>(0.00026772063206283885L),
      static_cast<T>(-0.75618016718839764e-4L),
      static_cast<T>(-0.23965051138672967e-6L),
      static_cast<T>(0.11082654115347302e-4L),
      static_cast<T>(-0.56749528269915966e-5L),
      static_cast<T>(0.14230900732435884e-5L),
   };
   workspace[3] = tools::evaluate_polynomial(C3, z);

   static const T C4[] = {
      static_cast<T>(-0.0008618882909167117L),
      static_cast<T>(0.00078403922172006663L),
      static_cast<T>(-0.00029907248030319018L),
      static_cast<T>(-0.14638452578843418e-5L),
      static_cast<T>(0.66414982154651222e-4L),
      static_cast<T>(-0.39683650471794347e-4L),
      static_cast<T>(0.11375726970678419e-4L),
   };
   workspace[4] = tools::evaluate_polynomial(C4, z);

   static const T C5[] = {
      static_cast<T>(-0.00033679855336635815L),
      static_cast<T>(-0.69728137583658578e-4L),
      static_cast<T>(0.00027727532449593921L),
      static_cast<T>(-0.00019932570516188848L),
      static_cast<T>(0.67977804779372078e-4L),
      static_cast<T>(0.1419062920643967e-6L),
      static_cast<T>(-0.13594048189768693e-4L),
      static_cast<T>(0.80184702563342015e-5L),
      static_cast<T>(-0.22914811765080952e-5L),
   };
   workspace[5] = tools::evaluate_polynomial(C5, z);

   static const T C6[] = {
      static_cast<T>(0.00053130793646399222L),
      static_cast<T>(-0.00059216643735369388L),
      static_cast<T>(0.00027087820967180448L),
      static_cast<T>(0.79023532326603279e-6L),
      static_cast<T>(-0.81539693675619688e-4L),
      static_cast<T>(0.56116827531062497e-4L),
      static_cast<T>(-0.18329116582843376e-4L),
   };
   workspace[6] = tools::evaluate_polynomial(C6, z);

   static const T C7[] = {
      static_cast<T>(0.00034436760689237767L),
      static_cast<T>(0.51717909082605922e-4L),
      static_cast<T>(-0.00033493161081142236L),
      static_cast<T>(0.0002812695154763237L),
      static_cast<T>(-0.00010976582244684731L),
   };
   workspace[7] = tools::evaluate_polynomial(C7, z);

   static const T C8[] = {
      static_cast<T>(-0.00065262391859530942L),
      static_cast<T>(0.00083949872067208728L),
      static_cast<T>(-0.00043829709854172101L),
   };
   workspace[8] = tools::evaluate_polynomial(C8, z);
   workspace[9] = static_cast<T>(-0.00059676129019274625L);

   T result = tools::evaluate_polynomial<10, T, T>(workspace, 1/a);
   result *= exp(-y) / sqrt(2 * constants::pi<T>() * a);
   if(x < a)
      result = -result;

   result += boost::math::erfc(sqrt(y), pol) / 2;

   return result;
}
//
// This one is accurate for 24-bit mantissa's
// (IEEE float precision, or 10^-8)
//
template <class T, class Policy>
T igamma_temme_large(T a, T x, const Policy& pol, mpl::int_<24> const *)
{
   BOOST_MATH_STD_USING // ADL of std functions
   T sigma = (x - a) / a;
   T phi = -boost::math::log1pmx(sigma, pol);
   T y = a * phi;
   T z = sqrt(2 * phi);
   if(x < a)
      z = -z;

   T workspace[3];

   static const T C0[] = {
      static_cast<T>(-0.333333333L),
      static_cast<T>(0.0833333333L),
      static_cast<T>(-0.0148148148L),
      static_cast<T>(0.00115740741L),
      static_cast<T>(0.000352733686L),
      static_cast<T>(-0.000178755144L),
      static_cast<T>(0.391926318e-4L),
   };
   workspace[0] = tools::evaluate_polynomial(C0, z);

   static const T C1[] = {
      static_cast<T>(-0.00185185185L),
      static_cast<T>(-0.00347222222L),
      static_cast<T>(0.00264550265L),
      static_cast<T>(-0.000990226337L),
      static_cast<T>(0.000205761317L),
   };
   workspace[1] = tools::evaluate_polynomial(C1, z);

   static const T C2[] = {
      static_cast<T>(0.00413359788L),
      static_cast<T>(-0.00268132716L),
      static_cast<T>(0.000771604938L),
   };
   workspace[2] = tools::evaluate_polynomial(C2, z);

   T result = tools::evaluate_polynomial(workspace, 1/a);
   result *= exp(-y) / sqrt(2 * constants::pi<T>() * a);
   if(x < a)
      result = -result;

   result += boost::math::erfc(sqrt(y), pol) / 2;

   return result;
}
//
// And finally, a version for 113-bit mantissa's
// (128-bit long doubles, or 10^-34).
// Note this one has been optimised for a > 200
// It's use for a < 200 is not recomended, that would
// require many more terms in the polynomials.
//
template <class T, class Policy>
T igamma_temme_large(T a, T x, const Policy& pol, mpl::int_<113> const *)
{
   BOOST_MATH_STD_USING // ADL of std functions
   T sigma = (x - a) / a;
   T phi = -boost::math::log1pmx(sigma, pol);
   T y = a * phi;
   T z = sqrt(2 * phi);
   if(x < a)
      z = -z;

   T workspace[14];

   static const T C0[] = {
      -0.333333333333333333333333333333333333L,
      0.0833333333333333333333333333333333333L,
      -0.0148148148148148148148148148148148148L,
      0.00115740740740740740740740740740740741L,
      0.0003527336860670194003527336860670194L,
      -0.000178755144032921810699588477366255144L,
      0.391926317852243778169704095630021556e-4L,
      -0.218544851067999216147364295512443661e-5L,
      -0.185406221071515996070179883622956325e-5L,
      0.829671134095308600501624213166443227e-6L,
      -0.17665952736826079304360054245742403e-6L,
      0.670785354340149858036939710029613572e-8L,
      0.102618097842403080425739573227252951e-7L,
      -0.438203601845335318655297462244719123e-8L,
      0.914769958223679023418248817633113681e-9L,
      -0.255141939949462497668779537993887013e-10L,
      -0.583077213255042506746408945040035798e-10L,
      0.243619480206674162436940696707789943e-10L,
      -0.502766928011417558909054985925744366e-11L,
      0.110043920319561347708374174497293411e-12L,
      0.337176326240098537882769884169200185e-12L,
      -0.13923887224181620659193661848957998e-12L,
      0.285348938070474432039669099052828299e-13L,
      -0.513911183424257261899064580300494205e-15L,
      -0.197522882943494428353962401580710912e-14L,
      0.809952115670456133407115668702575255e-15L,
      -0.165225312163981618191514820265351162e-15L,
      0.253054300974788842327061090060267385e-17L,
      0.116869397385595765888230876507793475e-16L,
      -0.477003704982048475822167804084816597e-17L,
      0.969912605905623712420709685898585354e-18L,
   };
   workspace[0] = tools::evaluate_polynomial(C0, z);

   static const T C1[] = {
      -0.00185185185185185185185185185185185185L,
      -0.00347222222222222222222222222222222222L,
      0.0026455026455026455026455026455026455L,
      -0.000990226337448559670781893004115226337L,
      0.000205761316872427983539094650205761317L,
      -0.401877572016460905349794238683127572e-6L,
      -0.180985503344899778370285914867533523e-4L,
      0.76491609160811100846374214980916921e-5L,
      -0.16120900894563446003775221882217767e-5L,
      0.464712780280743434226135033938722401e-8L,
      0.137863344691572095931187533077488877e-6L,
      -0.575254560351770496402194531835048307e-7L,
      0.119516285997781473243076536699698169e-7L,
      -0.175432417197476476237547551202312502e-10L,
      -0.100915437106004126274577504686681675e-8L,
      0.416279299184258263623372347219858628e-9L,
      -0.856390702649298063807431562579670208e-10L,
      0.606721510160475861512701762169919581e-13L,
      0.716249896481148539007961017165545733e-11L,
      -0.293318664377143711740636683615595403e-11L,
      0.599669636568368872330374527568788909e-12L,
      -0.216717865273233141017100472779701734e-15L,
      -0.497833997236926164052815522048108548e-13L,
      0.202916288237134247736694804325894226e-13L,
      -0.413125571381061004935108332558187111e-14L,
      0.828651623988309644380188591057589316e-18L,
      0.341003088693333279336339355910600992e-15L,
      -0.138541953028939715357034547426313703e-15L,
      0.281234665322887466568860332727259483e-16L,
   };
   workspace[1] = tools::evaluate_polynomial(C1, z);

   static const T C2[] = {
      0.0041335978835978835978835978835978836L,
      -0.00268132716049382716049382716049382716L,
      0.000771604938271604938271604938271604938L,
      0.200938786008230452674897119341563786e-5L,
      -0.000107366532263651605215391223621676297L,
      0.529234488291201254164217127180090143e-4L,
      -0.127606351886187277133779191392360117e-4L,
      0.34235787340961380741902003904747389e-7L,
      0.137219573090629332055943852926020279e-5L,
      -0.629899213838005502290672234278391876e-6L,
      0.142806142060642417915846008822771748e-6L,
      -0.204770984219908660149195854409200226e-9L,
      -0.140925299108675210532930244154315272e-7L,
      0.622897408492202203356394293530327112e-8L,
      -0.136704883966171134992724380284402402e-8L,
      0.942835615901467819547711211663208075e-12L,
      0.128722524000893180595479368872770442e-9L,
      -0.556459561343633211465414765894951439e-10L,
      0.119759355463669810035898150310311343e-10L,
      -0.416897822518386350403836626692480096e-14L,
      -0.109406404278845944099299008640802908e-11L,
      0.4662239946390135746326204922464679e-12L,
      -0.990510576390690597844122258212382301e-13L,
      0.189318767683735145056885183170630169e-16L,
      0.885922187259112726176031067028740667e-14L,
      -0.373782039804640545306560251777191937e-14L,
      0.786883363903515525774088394065960751e-15L,
   };
   workspace[2] = tools::evaluate_polynomial(C2, z);

   static const T C3[] = {
      0.000649434156378600823045267489711934156L,
      0.000229472093621399176954732510288065844L,
      -0.000469189494395255712128140111679206329L,
      0.000267720632062838852962309752433209223L,
      -0.756180167188397641072538191879755666e-4L,
      -0.239650511386729665193314027333231723e-6L,
      0.110826541153473023614770299726861227e-4L,
      -0.567495282699159656749963105701560205e-5L,
      0.14230900732435883914551894470580433e-5L,
      -0.278610802915281422405802158211174452e-10L,
      -0.16958404091930277289864168795820267e-6L,
      0.809946490538808236335278504852724081e-7L,
      -0.191111684859736540606728140872727635e-7L,
      0.239286204398081179686413514022282056e-11L,
      0.206201318154887984369925818486654549e-8L,
      -0.946049666185513217375417988510192814e-9L,
      0.215410497757749078380130268468744512e-9L,
      -0.138882333681390304603424682490735291e-13L,
      -0.218947616819639394064123400466489455e-10L,
      0.979099895117168512568262802255883368e-11L,
      -0.217821918801809621153859472011393244e-11L,
      0.62088195734079014258166361684972205e-16L,
      0.212697836327973697696702537114614471e-12L,
      -0.934468879151743333127396765626749473e-13L,
      0.204536712267828493249215913063207436e-13L,
   };
   workspace[3] = tools::evaluate_polynomial(C3, z);

   static const T C4[] = {
      -0.000861888290916711698604702719929057378L,
      0.00078403922172006662747403488144228885L,
      -0.000299072480303190179733389609932819809L,
      -0.146384525788434181781232535690697556e-5L,
      0.664149821546512218665853782451862013e-4L,
      -0.396836504717943466443123507595386882e-4L,
      0.113757269706784190980552042885831759e-4L,
      0.250749722623753280165221942390057007e-9L,
      -0.169541495365583060147164356781525752e-5L,
      0.890750753220530968882898422505515924e-6L,
      -0.229293483400080487057216364891158518e-6L,
      0.295679413754404904696572852500004588e-10L,
      0.288658297427087836297341274604184504e-7L,
      -0.141897394378032193894774303903982717e-7L,
      0.344635804994648970659527720474194356e-8L,
      -0.230245171745280671320192735850147087e-12L,
      -0.394092330280464052750697640085291799e-9L,
      0.186023389685045019134258533045185639e-9L,
      -0.435632300505661804380678327446262424e-10L,
      0.127860010162962312660550463349930726e-14L,
      0.467927502665791946200382739991760062e-11L,
      -0.214924647061348285410535341910721086e-11L,
      0.490881561480965216323649688463984082e-12L,
   };
   workspace[4] = tools::evaluate_polynomial(C4, z);

   static const T C5[] = {
      -0.000336798553366358150308767592718210002L,
      -0.697281375836585777429398828575783308e-4L,
      0.00027727532449593920787336425196507501L,
      -0.000199325705161888477003360405280844238L,
      0.679778047793720783881640176604435742e-4L,
      0.141906292064396701483392727105575757e-6L,
      -0.135940481897686932784583938837504469e-4L,
      0.80184702563342015397192571980419684e-5L,
      -0.229148117650809517038048790128781806e-5L,
      -0.325247355129845395166230137750005047e-9L,
      0.346528464910852649559195496827579815e-6L,
      -0.184471871911713432765322367374920978e-6L,
      0.482409670378941807563762631738989002e-7L,
      -0.179894667217435153025754291716644314e-13L,
      -0.630619450001352343517516981425944698e-8L,
      0.316241762877456793773762181540969623e-8L,
      -0.784092425369742929000839303523267545e-9L,
   };
   workspace[5] = tools::evaluate_polynomial(C5, z);

   static const T C6[] = {
      0.00053130793646399222316574854297762391L,
      -0.000592166437353693882864836225604401187L,
      0.000270878209671804482771279183488328692L,
      0.790235323266032787212032944390816666e-6L,
      -0.815396936756196875092890088464682624e-4L,
      0.561168275310624965003775619041471695e-4L,
      -0.183291165828433755673259749374098313e-4L,
      -0.307961345060330478256414192546677006e-8L,
      0.346515536880360908673728529745376913e-5L,
      -0.202913273960586037269527254582695285e-5L,
      0.578879286314900370889997586203187687e-6L,
      0.233863067382665698933480579231637609e-12L,
      -0.88286007463304835250508524317926246e-7L,
      0.474359588804081278032150770595852426e-7L,
      -0.125454150207103824457130611214783073e-7L,
   };
   workspace[6] = tools::evaluate_polynomial(C6, z);

   static const T C7[] = {
      0.000344367606892377671254279625108523655L,
      0.517179090826059219337057843002058823e-4L,
      -0.000334931610811422363116635090580012327L,
      0.000281269515476323702273722110707777978L,
      -0.000109765822446847310235396824500789005L,
      -0.127410090954844853794579954588107623e-6L,
      0.277444515115636441570715073933712622e-4L,
      -0.182634888057113326614324442681892723e-4L,
      0.578769494973505239894178121070843383e-5L,
      0.493875893393627039981813418398565502e-9L,
      -0.105953670140260427338098566209633945e-5L,
      0.616671437611040747858836254004890765e-6L,
      -0.175629733590604619378669693914265388e-6L,
   };
   workspace[7] = tools::evaluate_polynomial(C7, z);

   static const T C8[] = {
      -0.000652623918595309418922034919726622692L,
      0.000839498720672087279993357516764983445L,
      -0.000438297098541721005061087953050560377L,
      -0.696909145842055197136911097362072702e-6L,
      0.00016644846642067547837384572662326101L,
      -0.000127835176797692185853344001461664247L,
      0.462995326369130429061361032704489636e-4L,
      0.455790986792270771162749294232219616e-8L,
      -0.105952711258051954718238500312872328e-4L,
      0.678334290486516662273073740749269432e-5L,
      -0.210754766662588042469972680229376445e-5L,
   };
   workspace[8] = tools::evaluate_polynomial(C8, z);

   static const T C9[] = {
      -0.000596761290192746250124390067179459605L,
      -0.720489541602001055908571930225015052e-4L,
      0.000678230883766732836161951166000673426L,
      -0.000640147526026275845100045652582354779L,
      0.000277501076343287044992374518205845463L,
      0.181970083804651510461686554030325202e-6L,
      -0.847950711706850318239732559632810086e-4L,
      0.610519208250153101764709122740859458e-4L,
      -0.210739201834048624082975255893773306e-4L,
   };
   workspace[9] = tools::evaluate_polynomial(C9, z);

   static const T C10[] = {
      0.00133244544948006563712694993432717968L,
      -0.00191443849856547752650089885832852254L,
      0.0011089369134596637339607446329267522L,
      0.993240412264229896742295262075817566e-6L,
      -0.000508745012930931989848393025305956774L,
      0.00042735056665392884328432271160040444L,
      -0.000168588537679107988033552814662382059L,
   };
   workspace[10] = tools::evaluate_polynomial(C10, z);

   static const T C11[] = {
      0.00157972766073083495908785631307733022L,
      0.000162516262783915816898635123980270998L,
      -0.00206334210355432762645284467690276817L,
      0.00213896861856890981541061922797693947L,
      -0.00101085593912630031708085801712479376L,
   };
   workspace[11] = tools::evaluate_polynomial(C11, z);

   static const T C12[] = {
      -0.00407251211951401664727281097914544601L,
      0.00640336283380806979482363809026579583L,
      -0.00404101610816766177473974858518094879L,
   };
   workspace[12] = tools::evaluate_polynomial(C12, z);
   workspace[13] = -0.0059475779383993002845382844736066323L;

   T result = tools::evaluate_polynomial(workspace, T(1/a));
   result *= exp(-y) / sqrt(2 * constants::pi<T>() * a);
   if(x < a)
      result = -result;

   result += boost::math::erfc(sqrt(y), pol) / 2;

   return result;
}


}  // namespace detail
}  // namespace math
}  // namespace math


#endif // BOOST_MATH_DETAIL_IGAMMA_LARGE

