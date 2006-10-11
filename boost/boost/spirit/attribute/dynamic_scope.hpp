/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef SPIRIT_ATTRIBUTE_DYNAMIC_SCOPE_HPP
#define SPIRIT_ATTRIBUTE_DYNAMIC_SCOPE_HPP

#include <boost/spirit/core/parser.hpp>
#include <boost/spirit/core/composite/composite.hpp>
#include <boost/spirit/core/non_terminal/parser_context.hpp>
#include <boost/spirit/attribute/parametric.hpp>
#include <boost/spirit/attribute/dynamic_scope_fwd.hpp>
#include <boost/spirit/phoenix/scope/dynamic.hpp>
#include <boost/spirit/phoenix/core.hpp>
#include <boost/static_assert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/algorithm/transformation/join.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/mpl.hpp>
#include <boost/fusion/sequence/intrinsic/mpl.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>

#if !defined(BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT)
# define BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT PHOENIX_DYNAMIC_LIMIT
#endif

namespace boost { namespace spirit
{
    template<typename DynamicScope>
    struct dynamic_scope_context_linker : DynamicScope
    {
        template <typename Parser>
        dynamic_scope_context_linker(Parser const& p)
            : DynamicScope(p) {}
    
        template <typename Parser, typename Scanner>
        void pre_parse(Parser const& p, Scanner const& scan)
        {
            DynamicScope::pre_parse(p, scan); 
        }
    
        template <typename ResultT, typename Parser, typename Scanner>
        ResultT& post_parse(ResultT& hit, Parser const& p, Scanner const& scan)
        {
            return DynamicScope::post_parse(hit, p, scan);
        }
    };

    template <typename DynamicScope>
    struct dynamic_scope_context : parser_context_base
    {
        typedef typename 
            fusion::result_of::value_at_c<
                typename DynamicScope::tuple_type, 0>::type 
        attr_t;
        
        typedef DynamicScope base_t;

        typedef 
            dynamic_scope_context_linker<dynamic_scope_context<DynamicScope> >
        context_linker_t;

        dynamic_scope_context(DynamicScope const& scope)
            : frame(scope) {}

        ~dynamic_scope_context() {}

        template <typename Parser, typename Scanner>
        void pre_parse(Parser const&, Scanner const&) {}

        template <typename ResultT, typename Parser, typename Scanner>
        ResultT& post_parse(ResultT& hit, Parser const&, Scanner const&)
        { 
            hit.value(fusion::at_c<0>(frame.data())); 
            return hit;
        }

    private:

        phoenix::dynamic_frame<typename DynamicScope::phoenix_dynamic_t> frame;
    };

    struct get_actor_result
    {
        template <typename Actor>
        struct result : ::boost::result_of<Actor()> {};
    
        template <typename Actor>
        typename result<Actor>::type 
        operator()(Actor const& actor) const
        {
            return actor();
        }
    };

    template <typename TupleResult, typename ActorTuple>
    TupleResult convert_actors(ActorTuple const& actor_tuple)
    {
        static int const tuple_size = fusion::result_of::size<TupleResult>::value;
        static int const actor_tuple_size = fusion::result_of::size<ActorTuple>::value;
        BOOST_STATIC_ASSERT(actor_tuple_size <= tuple_size);

        typedef typename fusion::result_of::begin<TupleResult>::type result_begin;
        typedef typename fusion::result_of::end<TupleResult>::type result_end;
        typedef typename fusion::result_of::advance_c<result_begin, actor_tuple_size>::type result_advance;
        typedef mpl::fusion_iterator<result_advance> mpl_result_advance;
        typedef mpl::fusion_iterator<result_end> mpl_result_end;
        typedef mpl::iterator_range<mpl_result_advance, mpl_result_end> append_type;
        
        return TupleResult(fusion::join(fusion::transform(actor_tuple, get_actor_result()), append_type()));
    }

    template <typename DynamicScope>
    struct init_dynamic_scope_context : public parser_context_base
    {
        typedef typename DynamicScope::tuple_type tuple_type;
        typedef typename DynamicScope::dynamic_scope_t dynamic_scope_t;

        init_dynamic_scope_context(DynamicScope const& scope)
            : frame(scope.subject(), convert_actors<tuple_type>(scope.init)) {}

        ~init_dynamic_scope_context() {}

        template <typename ParserT, typename ScannerT>
        void pre_parse(ParserT const& /*p*/, ScannerT const&) {}

        template <typename ResultT, typename ParserT, typename ScannerT>
        ResultT& post_parse(ResultT& hit, ParserT const&, ScannerT const&)
        { 
            hit.value(fusion::at_c<0>(frame.data())); 
            return hit; 
        }

    private:

        phoenix::dynamic_frame<dynamic_scope_t> frame;
    };

    template <typename Parser, typename ActorTuple>
    struct init_dynamic_scope_parser
        : unary<Parser, parser<init_dynamic_scope_parser<Parser, ActorTuple> > >
    {
        typedef init_dynamic_scope_parser<Parser, ActorTuple> self_t;
        typedef unary<Parser, parser<self_t> > base_t;
        typedef typename Parser::phoenix_dynamic_t dynamic_scope_t;
        typedef typename Parser::tuple_type tuple_type;
        typedef typename fusion::result_of::value_at_c<tuple_type, 0>::type attr_t;

        template <typename Scanner>
        struct result
        {
            typedef typename match_result<Scanner, attr_t>::type type;
        };

        init_dynamic_scope_parser(Parser const& p, ActorTuple const& init)
            : base_t(p), init(init) {}

        template <typename Scanner>
        typename parser_result<self_t, Scanner>::type
        parse_main(Scanner const& scan) const
        {
            return this->subject().parse_main(scan);
        }

        template <typename Scanner>
        typename parser_result<self_t, Scanner>::type
        parse(Scanner const& scan) const
        {
            typedef init_dynamic_scope_context<self_t> init_scope_context_t;
            typedef parser_scanner_linker<Scanner> scanner_t;
            typedef dynamic_scope_context_linker<init_scope_context_t> context_t;
            typedef typename parser_result<self_t, Scanner>::type result_t;
            BOOST_SPIRIT_CONTEXT_PARSE(
                scan, *this, scanner_t, context_t, result_t);
        }

        ActorTuple init;
    };

    template <
        typename Derived
      , BOOST_PP_ENUM_PARAMS(BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT, typename T)
    >
    struct dynamic_scope :
        phoenix::dynamic<BOOST_PP_ENUM_PARAMS(BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT, T)>
    {
        typedef 
            phoenix::dynamic<BOOST_PP_ENUM_PARAMS(BOOST_SPIRIT_DYNAMIC_SCOPE_LIMIT, T)>
        phoenix_dynamic_t;

        typedef dynamic_scope_context<Derived> context_t;

        dynamic_scope() {}
        ~dynamic_scope() {}
        
        template <typename Derived2>
        struct aux
        {
            Derived2& aux_derived()
            {
                return *static_cast<Derived2*>(this); 
            }

            Derived2 const& aux_derived() const
            {
                return *static_cast<Derived2 const*>(this);
            }
            
            #include <boost/spirit/attribute/impl/dynamic_scope_aux_gen.hpp>
        };
    };
}}

/*
    SPIRIT_DYNAMIC_SCOPE macro(name, type-name sequence)
    Example:

    SPIRIT_DYNAMIC_SCOPE(
        my_dynamic,
            (int, num)
            (std::string, message)
            (double, real)
    );

    which expands to:

    struct my_dynamic : ::boost::spirit::dynamic_scope<my_dynamic, int, std::string, double>
    {
        my_dynamic() : num(*this), message(*this), real(*this) {}
    
        member1 num;
        member2 message;
        member3 real;
    };    
*/

#define SPIRIT_DYNAMIC_SCOPE(name, bseq)                                        \
    SPIRIT_DYNAMIC_SCOPE_A(                                                     \
        name, BOOST_PP_CAT(PHOENIX_DYNAMIC_X bseq, 0))                          \

#define SPIRIT_DYNAMIC_SCOPE_A(name, seq)                                       \
    struct name :                                                               \
        ::boost::spirit::dynamic_scope<name,                                    \
            BOOST_PP_SEQ_FOR_EACH_I(PHOENIX_DYNAMIC_A, ~, seq)> {               \
        name() : BOOST_PP_SEQ_FOR_EACH_I(PHOENIX_DYNAMIC_B, ~, seq) {}          \
        BOOST_PP_SEQ_FOR_EACH_I(PHOENIX_DYNAMIC_C, ~, seq)                      \
    }                                                                           \

#endif
