// preprocessed part of 'boost/mpl/aux_/iter_fold_if.hpp' header
// see the original for copyright information

namespace boost {
namespace mpl {

namespace aux {
template<typename Iterator, typename State>
struct iter_fold_null_step
{
    typedef State state;

    typedef Iterator iterator;
};

template<bool>
struct iter_fold_step_impl
{
    template
        <
            typename Iterator, typename State, typename StateOp, typename
                IteratorOp
        >
    struct result_
    {
        typedef typename apply2<StateOp, State, Iterator>::type state;

        typedef typename IteratorOp::type iterator;
        typedef false_c is_last;
    };
};

template<>
struct iter_fold_step_impl<false>
{
    template
        <
            typename Iterator, typename State, typename StateOp, typename
                IteratorOp
        >
    struct result_
    {
        typedef State state;

        typedef Iterator iterator;
        typedef true_c is_last;
    };
};

template
    <
        typename Iterator, typename State, typename ForwardOp, typename
            Predicate, typename IsLast = typename apply2
                <
                    Predicate, State, Iterator
                >::type
    >
struct iter_fold_forward_step :
    iter_fold_step_impl<IsLast::value>
        ::template result_<Iterator, State, ForwardOp, next<Iterator> >
{
};

template
    <
        typename Iterator, typename State, typename BackwardOp, typename
            Predicate, typename IsLast = typename apply2
                <
                    Predicate, State, Iterator
                >::type
    >
struct iter_fold_backward_step :
    iter_fold_step_impl<IsLast::value>
        ::template result_<Iterator, State, BackwardOp, identity<Iterator> >
{
};

template
    <
        typename Iterator, typename State, typename ForwardOp, typename
            ForwardPredicate, typename BackwardOp, typename BackwardPredicate
    >
struct iter_fold_if
{
private:
    typedef iter_fold_null_step<Iterator, State> forward_step0;

    typedef iter_fold_forward_step
        <
            typename forward_step0::iterator, typename forward_step0::state, ForwardOp, ForwardPredicate
        > forward_step1;

    typedef iter_fold_forward_step
        <
            typename forward_step1::iterator, typename forward_step1::state, ForwardOp, ForwardPredicate
        > forward_step2;

    typedef iter_fold_forward_step
        <
            typename forward_step2::iterator, typename forward_step2::state, ForwardOp, ForwardPredicate
        > forward_step3;

    typedef iter_fold_forward_step
        <
            typename forward_step3::iterator, typename forward_step3::state, ForwardOp, ForwardPredicate
        > forward_step4;

    typedef typename select_if
        <
            typename forward_step4::is_last, iter_fold_null_step
                <
                    typename forward_step4::iterator, typename forward_step4::state
                > , iter_fold_if
                <
                    typename forward_step4::iterator, typename forward_step4::state, ForwardOp, ForwardPredicate, BackwardOp, BackwardPredicate
                >
        >::type backward_step4;

    typedef iter_fold_backward_step
        <
            typename forward_step3::iterator, typename backward_step4::state, BackwardOp, BackwardPredicate
        > backward_step3;

    typedef iter_fold_backward_step
        <
            typename forward_step2::iterator, typename backward_step3::state, BackwardOp, BackwardPredicate
        > backward_step2;

    typedef iter_fold_backward_step
        <
            typename forward_step1::iterator, typename backward_step2::state, BackwardOp, BackwardPredicate
        > backward_step1;

    typedef iter_fold_backward_step
        <
            typename forward_step0::iterator, typename backward_step1::state, BackwardOp, BackwardPredicate
        > backward_step0;

public:
    typedef typename backward_step0::state state;

    typedef typename backward_step4::iterator iterator;
};
}
}
}
