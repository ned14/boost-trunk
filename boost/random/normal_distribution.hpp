/* boost random/normal_distribution.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Copyright Steven Watanabe 2010-2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_NORMAL_DISTRIBUTION_HPP
#define BOOST_RANDOM_NORMAL_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <istream>
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/integer.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/integer_log2.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>

namespace boost {
namespace random {

namespace detail {

// tables for the ziggurat algorithm
template<class RealType>
struct normal_table {
    static const RealType table_x[129];
    static const RealType table_y[129];
};

template<class RealType>
const RealType normal_table<RealType>::table_x[129] = {
    RealType(3.7130862467403632609),  RealType(3.4426198558966521214),  RealType(3.2230849845786185446),  RealType(3.0832288582142137009),
    RealType(2.9786962526450169606),  RealType(2.8943440070186706210),  RealType(2.8231253505459664379),  RealType(2.7611693723841538514),
    RealType(2.7061135731187223371),  RealType(2.6564064112581924999),  RealType(2.6109722484286132035),  RealType(2.5690336259216391328),
    RealType(2.5300096723854666170),  RealType(2.4934545220919507609),  RealType(2.4590181774083500943),  RealType(2.4264206455302115930),
    RealType(2.3954342780074673425),  RealType(2.3658713701139875435),  RealType(2.3375752413355307354),  RealType(2.3104136836950021558),
    RealType(2.2842740596736568056),  RealType(2.2590595738653295251),  RealType(2.2346863955870569803),  RealType(2.2110814088747278106),
    RealType(2.1881804320720206093),  RealType(2.1659267937448407377),  RealType(2.1442701823562613518),  RealType(2.1231657086697899595),
    RealType(2.1025731351849988838),  RealType(2.0824562379877246441),  RealType(2.0627822745039633575),  RealType(2.0435215366506694976),
    RealType(2.0246469733729338782),  RealType(2.0061338699589668403),  RealType(1.9879595741230607243),  RealType(1.9701032608497132242),
    RealType(1.9525457295488889058),  RealType(1.9352692282919002011),  RealType(1.9182573008597320303),  RealType(1.9014946531003176140),
    RealType(1.8849670357028692380),  RealType(1.8686611409895420085),  RealType(1.8525645117230870617),  RealType(1.8366654602533840447),
    RealType(1.8209529965910050740),  RealType(1.8054167642140487420),  RealType(1.7900469825946189862),  RealType(1.7748343955807692457),
    RealType(1.7597702248942318749),  RealType(1.7448461281083765085),  RealType(1.7300541605582435350),  RealType(1.7153867407081165482),
    RealType(1.7008366185643009437),  RealType(1.6863968467734863258),  RealType(1.6720607540918522072),  RealType(1.6578219209482075462),
    RealType(1.6436741568569826489),  RealType(1.6296114794646783962),  RealType(1.6156280950371329644),  RealType(1.6017183802152770587),
    RealType(1.5878768648844007019),  RealType(1.5740982160167497219),  RealType(1.5603772223598406870),  RealType(1.5467087798535034608),
    RealType(1.5330878776675560787),  RealType(1.5195095847593707806),  RealType(1.5059690368565502602),  RealType(1.4924614237746154081),
    RealType(1.4789819769830978546),  RealType(1.4655259573357946276),  RealType(1.4520886428822164926),  RealType(1.4386653166774613138),
    RealType(1.4252512545068615734),  RealType(1.4118417124397602509),  RealType(1.3984319141236063517),  RealType(1.3850170377251486449),
    RealType(1.3715922024197322698),  RealType(1.3581524543224228739),  RealType(1.3446927517457130432),  RealType(1.3312079496576765017),
    RealType(1.3176927832013429910),  RealType(1.3041418501204215390),  RealType(1.2905495919178731508),  RealType(1.2769102735516997175),
    RealType(1.2632179614460282310),  RealType(1.2494664995643337480),  RealType(1.2356494832544811749),  RealType(1.2217602305309625678),
    RealType(1.2077917504067576028),  RealType(1.1937367078237721994),  RealType(1.1795873846544607035),  RealType(1.1653356361550469083),
    RealType(1.1509728421389760651),  RealType(1.1364898520030755352),  RealType(1.1218769225722540661),  RealType(1.1071236475235353980),
    RealType(1.0922188768965537614),  RealType(1.0771506248819376573),  RealType(1.0619059636836193998),  RealType(1.0464709007525802629),
    RealType(1.0308302360564555907),  RealType(1.0149673952392994716),  RealType(0.99886423348064351303), RealType(0.98250080350276038481),
    RealType(0.96585507938813059489), RealType(0.94890262549791195381), RealType(0.93161619660135381056), RealType(0.91396525100880177644),
    RealType(0.89591535256623852894), RealType(0.87742742909771569142), RealType(0.85845684317805086354), RealType(0.83895221428120745572),
    RealType(0.81885390668331772331), RealType(0.79809206062627480454), RealType(0.77658398787614838598), RealType(0.75423066443451007146),
    RealType(0.73091191062188128150), RealType(0.70647961131360803456), RealType(0.68074791864590421664), RealType(0.65347863871504238702),
    RealType(0.62435859730908822111), RealType(0.59296294244197797913), RealType(0.55869217837551797140), RealType(0.52065603872514491759),
    RealType(0.47743783725378787681), RealType(0.42654798630330512490), RealType(0.36287143102841830424), RealType(0.27232086470466385065),
    RealType(0)
};

template<class RealType>
const RealType normal_table<RealType>::table_y[129] = {
    RealType(0),                       RealType(0.0026696290839025035092), RealType(0.0055489952208164705392), RealType(0.0086244844129304709682),
    RealType(0.011839478657982313715), RealType(0.015167298010672042468),  RealType(0.018592102737165812650),  RealType(0.022103304616111592615),
    RealType(0.025693291936149616572), RealType(0.029356317440253829618),  RealType(0.033087886146505155566),  RealType(0.036884388786968774128),
    RealType(0.040742868074790604632), RealType(0.044660862200872429800),  RealType(0.048636295860284051878),  RealType(0.052667401903503169793),
    RealType(0.056752663481538584188), RealType(0.060890770348566375972),  RealType(0.065080585213631873753),  RealType(0.069321117394180252601),
    RealType(0.073611501884754893389), RealType(0.077950982514654714188),  RealType(0.082338898242957408243),  RealType(0.086774671895542968998),
    RealType(0.091257800827634710201), RealType(0.09578784912257815216),   RealType(0.10036444102954554013),   RealType(0.10498725541035453978),
    RealType(0.10965602101581776100),  RealType(0.11437051244988827452),   RealType(0.11913054670871858767),   RealType(0.12393598020398174246),
    RealType(0.12878670619710396109),  RealType(0.13368265258464764118),   RealType(0.13862377998585103702),   RealType(0.14361008009193299469),
    RealType(0.14864157424369696566),  RealType(0.15371831220958657066),   RealType(0.15884037114093507813),   RealType(0.16400785468492774791),
    RealType(0.16922089223892475176),  RealType(0.17447963833240232295),   RealType(0.17978427212496211424),   RealType(0.18513499701071343216),
    RealType(0.19053204032091372112),  RealType(0.19597565311811041399),   RealType(0.20146611007620324118),   RealType(0.20700370944187380064),
    RealType(0.21258877307373610060),  RealType(0.21822164655637059599),   RealType(0.22390269938713388747),   RealType(0.22963232523430270355),
    RealType(0.23541094226572765600),  RealType(0.24123899354775131610),   RealType(0.24711694751469673582),   RealType(0.25304529850976585934),
    RealType(0.25902456739871074263),  RealType(0.26505530225816194029),   RealType(0.27113807914102527343),   RealType(0.27727350292189771153),
    RealType(0.28346220822601251779),  RealType(0.28970486044581049771),   RealType(0.29600215684985583659),   RealType(0.30235482778947976274),
    RealType(0.30876363800925192282),  RealType(0.31522938806815752222),   RealType(0.32175291587920862031),   RealType(0.32833509837615239609),
    RealType(0.33497685331697116147),  RealType(0.34167914123501368412),   RealType(0.34844296754987246935),   RealType(0.35526938485154714435),
    RealType(0.36215949537303321162),  RealType(0.36911445366827513952),   RealType(0.37613546951445442947),   RealType(0.38322381105988364587),
    RealType(0.39038080824138948916),  RealType(0.39760785649804255208),   RealType(0.40490642081148835099),   RealType(0.41227804010702462062),
    RealType(0.41972433205403823467),  RealType(0.42724699830956239880),   RealType(0.43484783025466189638),   RealType(0.44252871528024661483),
    RealType(0.45029164368692696086),  RealType(0.45813871627287196483),   RealType(0.46607215269457097924),   RealType(0.47409430069824960453),
    RealType(0.48220764633483869062),  RealType(0.49041482528932163741),   RealType(0.49871863547658432422),   RealType(0.50712205108130458951),
    RealType(0.51562823824987205196),  RealType(0.52424057267899279809),   RealType(0.53296265938998758838),   RealType(0.54179835503172412311),
    RealType(0.55075179312105527738),  RealType(0.55982741271069481791),   RealType(0.56902999107472161225),   RealType(0.57836468112670231279),
    RealType(0.58783705444182052571),  RealType(0.59745315095181228217),   RealType(0.60721953663260488551),   RealType(0.61714337082656248870),
    RealType(0.62723248525781456578),  RealType(0.63749547734314487428),   RealType(0.64794182111855080873),   RealType(0.65858200005865368016),
    RealType(0.66942766735770616891),  RealType(0.68049184100641433355),   RealType(0.69178914344603585279),   RealType(0.70333609902581741633),
    RealType(0.71515150742047704368),  RealType(0.72725691835450587793),   RealType(0.73967724368333814856),   RealType(0.75244155918570380145),
    RealType(0.76558417390923599480),  RealType(0.77914608594170316563),   RealType(0.79317701178385921053),   RealType(0.80773829469612111340),
    RealType(0.82290721139526200050),  RealType(0.83878360531064722379),   RealType(0.85550060788506428418),   RealType(0.87324304892685358879),
    RealType(0.89228165080230272301),  RealType(0.91304364799203805999),   RealType(0.93628268170837107547),   RealType(0.96359969315576759960),
    RealType(1)
};

template<class Engine>
inline typename boost::make_unsigned<typename Engine::result_type>::type
generate_one_digit(Engine& eng, std::size_t bits)
{
    typedef typename Engine::result_type base_result;
    typedef typename boost::make_unsigned<base_result>::type base_unsigned;

    base_unsigned range =
        detail::subtract<base_result>()((eng.max)(), (eng.min)());
    base_unsigned y0_mask = (base_unsigned(2) << (bits - 1)) - 1;
    base_unsigned y0 = (range + 1) & ~y0_mask;
    base_unsigned u;
    do {
        u = detail::subtract<base_result>()(eng(), (eng.min)());
    } while(y0 != 0 && u > base_unsigned(y0 - 1));
    return u & y0_mask;
}

template<class RealType, std::size_t w, class Engine>
std::pair<RealType, int> generate_int_float_pair(Engine& eng, boost::mpl::true_)
{
    typedef typename Engine::result_type base_result;
    typedef typename boost::make_unsigned<base_result>::type base_unsigned;

    base_unsigned range =
        detail::subtract<base_result>()((eng.max)(), (eng.min)());

    std::size_t m =
        (range == (std::numeric_limits<base_unsigned>::max)()) ?
            std::numeric_limits<base_unsigned>::digits :
            detail::integer_log2(range + 1);

    int bucket = 0;
    // process as many full digits as possible into the int part
    for(std::size_t i = 0; i < w/m; ++i) {
        base_unsigned u = generate_one_digit(eng, m);
        bucket = (bucket << m) | u;
    }
    RealType r;

    const std::size_t digits = std::numeric_limits<RealType>::digits;
    {
        base_unsigned u = generate_one_digit(eng, m);
        base_unsigned mask = (base_unsigned(1) << (w%m)) - 1;
        bucket = (bucket << (w%m)) | (mask & u);
        const RealType mult = RealType(1)/RealType(base_unsigned(1) << (m - w%m));
        // zero out unused bits
        if (m - w%m > digits) {
            u &= ~(base_unsigned(1) << (m - digits));
        }
        r = RealType(u >> (w%m)) * mult;
    }
    for(std::size_t i = m - w%m; i + m < digits; ++i) {
        base_unsigned u = generate_one_digit(eng, m);
        r += u;
        r *= RealType(0.5)/RealType(base_unsigned(1) << (m - 1));
    }
    if (m - w%m < digits)
    {
        const std::size_t remaining = (digits - m + w%m) % m;
        base_unsigned u = generate_one_digit(eng, m);
        r += u & ((base_unsigned(2) << (remaining - 1)) - 1);
        const RealType mult = RealType(0.5)/RealType(base_unsigned(1) << (remaining - 1));
        r *= mult;
    }
    return std::make_pair(r, bucket);
}

template<class RealType, std::size_t w, class Engine>
inline std::pair<RealType, int> generate_int_float_pair(Engine& eng, boost::mpl::false_)
{
    int bucket = uniform_int_distribution<>(0, (1 << w) - 1)(eng);
    RealType r = uniform_01<RealType>()(eng);
    return std::make_pair(r, bucket);
}

template<class RealType, std::size_t w, class Engine>
inline std::pair<RealType, int> generate_int_float_pair(Engine& eng)
{
    typedef typename Engine::result_type base_result;
    return generate_int_float_pair<RealType, w>(eng,
        boost::is_integral<base_result>());
}

template<class RealType = double>
struct unit_normal_distribution
{
    template<class Engine>
    RealType operator()(Engine& eng) {
        const double * const table_x = normal_table<double>::table_x;
        const double * const table_y = normal_table<double>::table_y;
        for(;;) {
            std::pair<RealType, int> vals = generate_int_float_pair<RealType, 8>(eng);
            int i = vals.second;
            int sign = (i & 1) * 2 - 1;
            i = i >> 1;
            RealType x = vals.first * RealType(table_x[i]);
            if(x < table_x[i + 1]) return x * sign;
            if(i == 0) return generate_tail(eng) * sign;
            RealType y = RealType(table_y[i]) + uniform_01<RealType>()(eng) * RealType(table_y[i + 1] - table_y[i]);
            if (y < f(x)) return x * sign;
        }
    }
    static RealType f(RealType x) {
        using std::exp;
        return exp(-x*x/2);
    }
    template<class Engine>
    RealType generate_tail(Engine& eng) {
        boost::random::exponential_distribution<RealType> exponential;
        const RealType tail_start(normal_table<RealType>::table_x[1]);
        for(;;) {
            RealType x = exponential(eng)/tail_start;
            RealType y = exponential(eng);
            if(2*y > x*x) return x + tail_start;
        }
    }
};

}

// deterministic Box-Muller method, uses trigonometric functions

/**
 * Instantiations of class template normal_distribution model a
 * \random_distribution. Such a distribution produces random numbers
 * @c x distributed with probability density function
 * \f$\displaystyle p(x) =
 *   \frac{1}{\sqrt{2\pi\sigma}} e^{-\frac{(x-\mu)^2}{2\sigma^2}}
 * \f$,
 * where mean and sigma are the parameters of the distribution.
 */
template<class RealType = double>
class normal_distribution
{
public:
    typedef RealType input_type;
    typedef RealType result_type;

    class param_type {
    public:
        typedef normal_distribution distribution_type;

        /**
         * Constructs a @c param_type with a given mean and
         * standard deviation.
         *
         * Requires: sigma >= 0
         */
        explicit param_type(RealType mean_arg = RealType(0.0),
                            RealType sigma_arg = RealType(1.0))
          : _mean(mean_arg),
            _sigma(sigma_arg)
        {}

        /** Returns the mean of the distribution. */
        RealType mean() const { return _mean; }

        /** Returns the standand deviation of the distribution. */
        RealType sigma() const { return _sigma; }

        /** Writes a @c param_type to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._mean << " " << parm._sigma ; return os; }

        /** Reads a @c param_type from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._mean >> std::ws >> parm._sigma; return is; }

        /** Returns true if the two sets of parameters are the same. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._mean == rhs._mean && lhs._sigma == rhs._sigma; }

        /** Returns true if the two sets of parameters are the different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        RealType _mean;
        RealType _sigma;
    };

    /**
     * Constructs a @c normal_distribution object. @c mean and @c sigma are
     * the parameters for the distribution.
     *
     * Requires: sigma >= 0
     */
    explicit normal_distribution(const RealType& mean_arg = RealType(0.0),
                                 const RealType& sigma_arg = RealType(1.0))
      : _mean(mean_arg), _sigma(sigma_arg)
    {
        BOOST_ASSERT(_sigma >= RealType(0));
    }

    /**
     * Constructs a @c normal_distribution object from its parameters.
     */
    explicit normal_distribution(const param_type& parm)
      : _mean(parm.mean()), _sigma(parm.sigma())
    {}

    /**  Returns the mean of the distribution. */
    RealType mean() const { return _mean; }
    /** Returns the standard deviation of the distribution. */
    RealType sigma() const { return _sigma; }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return -std::numeric_limits<RealType>::infinity(); }
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return std::numeric_limits<RealType>::infinity(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_mean, _sigma); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        _mean = parm.mean();
        _sigma = parm.sigma();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /**  Returns a normal variate. */
    template<class Engine>
    result_type operator()(Engine& eng)
    {
        detail::unit_normal_distribution<RealType> impl;
        return impl(eng) * _sigma + _mean;
    }

    /** Returns a normal variate with parameters specified by @c param. */
    template<class URNG>
    result_type operator()(URNG& urng, const param_type& parm)
    {
        return normal_distribution(parm)(urng);
    }

    /** Writes a @c normal_distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, normal_distribution, nd)
    {
        os << nd._mean << " " << nd._sigma;
        return os;
    }

    /** Reads a @c normal_distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, normal_distribution, nd)
    {
        is >> std::ws >> nd._mean >> std::ws >> nd._sigma;
        return is;
    }

    /**
     * Returns true if the two instances of @c normal_distribution will
     * return identical sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(normal_distribution, lhs, rhs)
    {
        return lhs._mean == rhs._mean && lhs._sigma == rhs._sigma;
    }

    /**
     * Returns true if the two instances of @c normal_distribution will
     * return different sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(normal_distribution)

private:
    RealType _mean, _sigma;

};

} // namespace random

using random::normal_distribution;

} // namespace boost

#endif // BOOST_RANDOM_NORMAL_DISTRIBUTION_HPP
