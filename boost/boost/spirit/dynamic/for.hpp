/*=============================================================================
    Spirit V1.5.2
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Martin Wille
    http://spirit.sourceforge.net/

    Permission to copy, use, modify, sell and distribute this software is
    granted provided this copyright notice appears in all copies. This
    software is provided "as is" without express or implied warranty, and
    with no claim as to its suitability for any purpose.
=============================================================================*/
#ifndef BOOST_SPIRIT_FOR_HPP
#define BOOST_SPIRIT_FOR_HPP
////////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SPIRIT_PARSER_HPP)
#include "boost/spirit/core/parser.hpp"
#endif

#if !defined(BOOST_SPIRIT_COMPOSITE_HPP)
#include "boost/spirit/core/composite/composite.hpp"
#endif

#if !defined(BOOST_SPIRIT_CONDITIONS_IPP)
#include "boost/spirit/dynamic/impl/conditions.ipp"
#endif
////////////////////////////////////////////////////////////////////////////////

namespace boost { namespace spirit
{
    namespace impl
    {

        template <typename FuncT>
        struct for_functor : private subject_type<FuncT, nil_t>::type
        {
            typedef typename subject_type<FuncT, nil_t>::type       base_t;
            typedef typename boost::call_traits<FuncT>::param_type  param_t;
            typedef typename base_t::return_t                       return_t;

            for_functor(param_t f) : base_t(f) {}
            for_functor() : base_t() {}
            return_t get() const { return base_t::get(); }
        };

        template <typename InitF>
        struct for_init_functor : for_functor<InitF>
        {
            typedef for_functor<InitF>          base_t;
            typedef typename base_t::param_t    param_t;

            for_init_functor(param_t f) : base_t(f) {}
            for_init_functor() : base_t() {}
            void init() const { return base_t::get()(); }
        };

        template <typename StepF>
        struct for_step_functor : for_functor<StepF>
        {
            typedef for_functor<StepF>          base_t;
            typedef typename base_t::param_t    param_t;

            for_step_functor(param_t f) : base_t(f) {}
            for_step_functor() : base_t() {}
            void step() const { return base_t::get()(); }
        };

        //////////////////////////////////
        // for_parser
        template
        <
            typename InitF, typename CondT, typename StepF,
            typename ParserT
        >
        struct for_parser
            : private for_init_functor<InitF>
            , private for_step_functor<StepF>
            , private condition_evaluator<CondT>
            , public unary
            <
                ParserT,
                parser< for_parser<InitF, CondT, StepF, ParserT> >
            >
        {
            typedef for_parser< InitF, CondT, StepF, ParserT > self_t;
            typedef condition_evaluator<CondT>                 eval_t;
            typedef unary< ParserT, parser< self_t > >         base_t;


            //////////////////////////////
            // constructor, saves init, condition and step functors
            // for later use the parse member function
            for_parser
            (
                InitF const &i, CondT const &c, StepF const &s,
                ParserT const &p
            )
                : for_init_functor<InitF>(i)
                , for_step_functor<StepF>(s)
                , eval_t(c)
                , base_t(p)
            { }

            for_parser()
                : for_init_functor<InitF>()
                , for_step_functor<StepF>()
                , eval_t()
                , base_t()
            {}

            //////////////////////////////
            // parse member function
            template <typename ScannerT>
            typename parser_result<self_t, ScannerT>::type
            parse(ScannerT const &scan) const
            {
                typedef typename parser_result<self_t, ScannerT>::type result_t;
                typedef typename parser_result<ParserT, ScannerT>::type sresult_t;

                typename ScannerT::iterator_t save(scan.first);

                int length = 0;
                int eval_length = 0;

                init();
                while ((eval_length = evaluate(scan))>=0)
                {
                    length += eval_length;
                    sresult_t tmp(this->subject().parse(scan));
                    if (tmp)
                    {
                        length+=tmp.length();
                    }
                    else
                    {
                        return scan.no_match();
                    }
                    step();
                }
                return scan.create_match(length, nil_t(), save, scan.first);
            }
        };

        //////////////////////////////////
        // for_parser_gen generates takes the body parser in brackets
        // and returns the for_parser
        template <typename InitF, typename CondT, typename StepF>
        struct for_parser_gen
        {
            for_parser_gen(InitF const &i, CondT const &c, StepF const &s)
                : init(i)
                , condition(c)
                , step(s)
            {}

            typedef ::boost::spirit::as_parser<CondT> cond_as_parser_t;
            typedef typename cond_as_parser_t::type  cond_p;

            template <typename ParserT>
            for_parser
            <
                InitF, cond_p, StepF,
                typename /*::boost::spirit::*/as_parser<ParserT>::type
            >
            operator[](ParserT const &p) const
            {
                typedef ::boost::spirit::as_parser<ParserT> as_parser_t;
                typedef typename as_parser_t::type parser_t;

                typedef char assert_argument_must_be_a_parser
                     [::boost::spirit::is_parser<parser_t>::value];

                return for_parser<InitF, cond_p, StepF, parser_t>
                (
                    init,
                    cond_as_parser_t::convert(condition),
                    step,
                    as_parser_t::convert(p)
                );
            }

            InitF const &init;
            CondT const &condition;
            StepF const &step;
        };
    } // namespace impl

    //////////////////////////////
    // for_p, returns for-parser generator
    // Usage: spirit::for_p(init-ftor, condition, step-ftor)[body]
    template
    <
        typename InitF, typename ConditionT, typename StepF
    >
    impl::for_parser_gen<InitF, ConditionT, StepF>
    for_p(InitF const &init_f, ConditionT const &condition, StepF const &step_f)
    {
        return impl::for_parser_gen<InitF, ConditionT, StepF>
            (init_f, condition, step_f);
    }

}} // namespace boost::spirit

#endif // BOOST_SPIRIT_FOR_HPP
