#ifndef BOOST_FSM_SIMPLE_STATE_HPP_INCLUDED
#define BOOST_FSM_SIMPLE_STATE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>

#include <boost/fsm/detail/leaf_state.hpp>
#include <boost/fsm/detail/node_state.hpp>
#include <boost/fsm/detail/constructor.hpp>

#include <boost/mpl/apply_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

#include <boost/get_pointer.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <boost/cast.hpp>   // boost::polymorphic_downcast
#include <boost/config.hpp> // BOOST_STATIC_CONSTANT



namespace boost
{
namespace fsm
{
namespace detail
{



typedef mpl::clear< mpl::list<> >::type empty_list;

//////////////////////////////////////////////////////////////////////////////
template< class T >
struct make_list : public mpl::apply_if<
  mpl::is_sequence< T >,
  mpl::identity< T >,
  mpl::identity< mpl::list< T > > > {};

//////////////////////////////////////////////////////////////////////////////
template< class MostDerived, class Context, class InnerInitial >
struct simple_state_base_type
{
  private:
    typedef typename Context::outermost_context_type::allocator_type
      allocator_type;
    typedef typename Context::outermost_context_type::rtti_policy_type
      rtti_policy_type;
    typedef typename detail::make_list< InnerInitial >::type
      inner_initial_list;
    typedef typename mpl::size< inner_initial_list >::type
      inner_initial_list_size;

  public:
    typedef typename mpl::apply_if<
      mpl::empty< inner_initial_list >,
      mpl::identity< typename rtti_policy_type::
        template rtti_derived_type< MostDerived, leaf_state<
          allocator_type,
          rtti_policy_type > > >,
      mpl::identity< typename rtti_policy_type::
        template rtti_derived_type< MostDerived, node_state<
          inner_initial_list_size,
          allocator_type,
          rtti_policy_type > > > >::type type;
};


//////////////////////////////////////////////////////////////////////////////
struct no_transition_function
{
  template< class CommonContext >
  void operator()( CommonContext & ) const {}
};

template< class TransitionContext, class Event >
class transition_function
{
  public:
    transition_function(
      void ( TransitionContext::*pTransitionAction )( const Event & ),
      const Event & evt
    ) :
      pTransitionAction_( pTransitionAction ),
      evt_( evt )
    {
    }

    template< class CommonContext >
    void operator()( CommonContext & commonContext ) const
    {
      ( commonContext.template context< TransitionContext >()
        .*pTransitionAction_ )( evt_ );
    }

  private:
    void ( TransitionContext::*pTransitionAction_ )( const Event & );
    const Event & evt_;
};


template< bool contextHasInheritedDeepHistory, bool contextHasDeepHistory >
struct deep_history_storer
{
  template< class HistorizedState, class LeafState, class Context >
  static void store_deep_history( Context & ) {}
};

template<>
struct deep_history_storer< true, false >
{
  template< class HistorizedState, class LeafState, class Context >
  static void store_deep_history( Context & ctx )
  {
    ctx.template store_deep_history_impl< LeafState >();
  }
};

template<>
struct deep_history_storer< true, true >
{
  template< class HistorizedState, class LeafState, class Context >
  static void store_deep_history( Context & ctx )
  {
    ctx.outermost_context().template store_deep_history<
      HistorizedState, LeafState >();
    ctx.template store_deep_history_impl< LeafState >();
  }
};



} // namespace detail



//////////////////////////////////////////////////////////////////////////////
typedef detail::empty_list no_reactions;

//////////////////////////////////////////////////////////////////////////////
enum history_mode
{
  has_no_history,
  has_shallow_history,
  has_deep_history,
  has_full_history // shallow & deep
};



//////////////////////////////////////////////////////////////////////////////
template< class MostDerived,
          class Context,
          class Reactions = no_reactions,
          class InnerInitial = detail::empty_list,
          history_mode historyMode = has_no_history >
class simple_state : public detail::simple_state_base_type< MostDerived,
  typename Context::inner_context_type, InnerInitial >::type
{
  typedef typename detail::simple_state_base_type<
    MostDerived, typename Context::inner_context_type,
    InnerInitial >::type base_type;

  public:
    //////////////////////////////////////////////////////////////////////////
    typedef typename Context::inner_context_type context_type;

    template< detail::orthogonal_position_type innerOrthogonalPosition >
    struct orthogonal
    {
      typedef mpl::integral_c<
        detail::orthogonal_position_type,
        innerOrthogonalPosition > inner_orthogonal_position;
      typedef MostDerived inner_context_type;
    };

    typedef typename context_type::outermost_context_type
      outermost_context_type;

    outermost_context_type & outermost_context()
    {
      BOOST_ASSERT( get_pointer( pContext_ ) != 0 );
      return pContext_->outermost_context();
    }

    const outermost_context_type & outermost_context() const
    {
      BOOST_ASSERT( get_pointer( pContext_ ) != 0 );
      return pContext_->outermost_context();
    }

    template< class OtherContext >
    OtherContext & context()
    {
      typedef typename mpl::if_<
        is_same< OtherContext, MostDerived >,
        context_impl_this_context,
        context_impl_other_context
      >::type impl;
      return impl::template context_impl< OtherContext >( *this );
    }

    template< class OtherContext >
    const OtherContext & context() const
    {
      typedef typename mpl::if_<
        is_same< OtherContext, MostDerived >,
        context_impl_this_context,
        context_impl_other_context
      >::type impl;
      return impl::template context_impl< OtherContext >( *this );
    }

    template< class Target >
    Target state_cast() const
    {
      return outermost_context().template state_cast< Target >();
    }

    template< class Target >
    Target state_downcast() const
    {
      return outermost_context().template state_downcast< Target >();
    }

    typedef typename context_type::state_base_type state_base_type;
    typedef typename context_type::state_iterator state_iterator;

    state_iterator state_begin() const
    {
      return outermost_context().state_begin();
    }

    state_iterator state_end() const
    {
      return outermost_context().state_end();
    }


    typedef typename context_type::event_base_ptr_type event_base_ptr_type;

    void post_event( const event_base_ptr_type & pEvent )
    {
      outermost_context().post_event( pEvent );
    }

    result discard_event()
    {
      state_base_type::reaction_initiated();
      return do_discard_event;
    }

    result forward_event()
    {
      state_base_type::reaction_initiated();
      return do_forward_event;
    }

    result defer_event()
    {
      state_base_type::reaction_initiated();
      state_base_type::defer_event();
      return do_defer_event;
    }

    template< class DestinationState >
    result transit()
    {
      return transit_impl< DestinationState >(
        detail::no_transition_function() );
    }

    template< class DestinationState, class TransitionContext, class Event >
    result transit(
      void ( TransitionContext::*pTransitionAction )( const Event & ),
      const Event & evt )
    {
      return transit_impl< DestinationState >(
        detail::transition_function< TransitionContext, Event >(
          pTransitionAction, evt ) );
    }

    result terminate()
    {
      state_base_type::reaction_initiated();
      outermost_context().terminate( *this );
      return do_discard_event;
    }

    template<
      class HistoryContext,
      detail::orthogonal_position_type orthogonalPosition >
    void clear_shallow_history()
    {
      outermost_context().clear_shallow_history<
        HistoryContext, orthogonalPosition >();
    }

    template<
      class HistoryContext,
      detail::orthogonal_position_type orthogonalPosition >
    void clear_deep_history()
    {
      outermost_context().clear_deep_history<
        HistoryContext, orthogonalPosition >();
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    simple_state() : pContext_( 0 ) {}

    virtual ~simple_state()
    {
      // As a result of a throwing derived class constructor, this destructor
      // can be called before the context is set.
      if ( get_pointer( pContext_ ) != 0 )
      {
        if ( state_base_type::deferred_events() )
        {
          outermost_context().release_events( this );
        }

        check_store_shallow_history< stores_shallow_history >();
        check_store_deep_history< stores_deep_history >();

        pContext_->remove_inner_state( orthogonal_position::value );
      }
    }

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    typedef typename Context::inner_orthogonal_position orthogonal_position;

    // If you receive a
    // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or similar
    // compiler error here then this state resides in a non-existent
    // orthogonal region of the outer state.
    BOOST_STATIC_ASSERT( ( mpl::less<
      orthogonal_position,
      typename context_type::no_of_orthogonal_regions >::value ) );

    typedef MostDerived inner_context_type;
    typedef mpl::integral_c< detail::orthogonal_position_type, 0 >
      inner_orthogonal_position;

    typedef typename context_type::state_base_type state_base_type;
    typedef typename context_type::event_base_type event_base_type;
    typedef typename context_type::rtti_policy_type rtti_policy_type;

    typedef typename context_type::outermost_context_type
      outermost_context_type;
    typedef typename context_type::inner_context_ptr_type context_ptr_type;
    typedef typename context_type::state_list_type state_list_type;
    typedef intrusive_ptr< inner_context_type > inner_context_ptr_type;
    typedef typename detail::make_list< InnerInitial >::type
      inner_initial_list;
    typedef typename mpl::size< inner_initial_list >::type
      inner_initial_list_size;
    typedef mpl::integral_c<
      detail::orthogonal_position_type,
      inner_initial_list_size::value > no_of_orthogonal_regions;
    typedef typename mpl::push_front<
      typename context_type::context_type_list,
      context_type >::type context_type_list;

    // If you receive a
    // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or similar
    // compiler error here then the direct or indirect context of this state
    // has deep history _and_ this state has two or more orthogonal regions.
    // boost::fsm does not currently support deep history in a state whose
    // direct or indirect inner states have two or more orthogonal regions.
    // Please consult the documentation on how to work around this limitation.
    BOOST_STATIC_ASSERT(
      ( no_of_orthogonal_regions::value <= 1 ) ||
      ( !context_type::inherited_deep_history ) );

    BOOST_STATIC_CONSTANT( bool, shallow_history =
      ( historyMode & has_shallow_history ) != 0 );
    BOOST_STATIC_CONSTANT( bool, stores_shallow_history =
      context_type::shallow_history );
    BOOST_STATIC_CONSTANT( bool, deep_history =
      ( historyMode & has_deep_history ) != 0 );
    BOOST_STATIC_CONSTANT( bool, inherited_deep_history =
      ( deep_history || context_type::inherited_deep_history ) );
    BOOST_STATIC_CONSTANT( bool, stores_deep_history =
      inherited_deep_history && mpl::empty< inner_initial_list >::value );

    typedef mpl::bool_< false > history_destination;

    virtual result react_impl(
      const event_base_type & evt,
      typename rtti_policy_type::id_type eventType )
    {
      state_base_type::enable_reaction();
      typedef typename detail::make_list< Reactions >::type reaction_list;
      result reactionResult = local_react< reaction_list >( evt, eventType );

      if ( reactionResult == do_forward_event )
      {
        // we can only safely access pContext_ if the handler did not
        // return do_discard_event!
        // TODO: The following call to react_impl of our outer state should
        // be made with a context_type:: prefix to call directly instead of
        // virtually. For some reason the compiler complains...
        reactionResult = pContext_->react_impl( evt, eventType );
      }

      return reactionResult;
    }

    virtual const state_base_type * outer_state_ptr() const
    {
      typedef typename mpl::if_<
        is_same< outermost_context_type, context_type >,
        outer_state_ptr_impl_outermost,
        outer_state_ptr_impl_non_outermost
      >::type impl;
      return impl::outer_state_ptr_impl( *this );
    }

    template< class OtherContext >
    const typename OtherContext::inner_context_ptr_type & context_ptr() const
    {
      typedef typename mpl::if_<
        is_same< OtherContext, context_type >,
        context_ptr_impl_my_context,
        context_ptr_impl_other_context
      >::type impl;

      return impl::template context_ptr_impl< OtherContext >( *this );
    }

    static void initial_deep_construct(
      outermost_context_type & outermostContext )
    {
      deep_construct( &outermostContext, outermostContext );
    }

    static void deep_construct(
      const context_ptr_type & pContext,
      outermost_context_type & outermostContext )
    {
      outermostContext.add( pContext );
      const inner_context_ptr_type pInnerContext(
        shallow_construct( pContext ) );
      deep_construct_inner< inner_initial_list >(
        pInnerContext, outermostContext );
    }

    static inner_context_ptr_type shallow_construct(
      const context_ptr_type & pContext )
    {
      const inner_context_ptr_type pInnerContext( new MostDerived );
      pInnerContext->set_context( pContext );
      return pInnerContext;
    }

    void set_context( const context_ptr_type & pContext )
    {
      BOOST_ASSERT( get_pointer( pContext ) != 0 );
      pContext_ = pContext;
      base_type::set_context(
        orthogonal_position::value, get_pointer( pContext ) );
    }

    template< class InnerList >
    static void deep_construct_inner(
      const inner_context_ptr_type & pInnerContext,
      outermost_context_type & outermostContext )
    {
      typedef typename mpl::if_<
        mpl::empty< InnerList >,
        deep_construct_inner_impl_leaf_state,
        deep_construct_inner_impl_node_state
      >::type impl;
      impl::template deep_construct_inner_impl< InnerList >(
        pInnerContext, outermostContext );
    }

    static void reserve_history_slot(
      outermost_context_type & outermostContext )
    {
      reserve_shallow_history_slot< context_type::shallow_history >(
        outermostContext );
      reserve_deep_history_slot< context_type::deep_history >(
        outermostContext );
    }

    template< class LeafState >
    void store_deep_history_impl()
    {
      if ( !state_base_type::termination_state() )
      {
        detail::deep_history_storer<
          context_type::inherited_deep_history,
          context_type::deep_history
        >::template store_deep_history< MostDerived, LeafState >(
          *pContext_ );
      }
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    struct deep_construct_inner_impl_node_state
    {
      template< class InnerList >
      static void deep_construct_inner_impl(
        const inner_context_ptr_type & pInnerContext,
        outermost_context_type & outermostContext )
      {
        node_state_deep_construct_inner< InnerList >(
          pInnerContext, outermostContext );
      }
    };

    struct deep_construct_inner_impl_leaf_state
    {
      template< class InnerList >
      static void deep_construct_inner_impl(
        const inner_context_ptr_type & pInnerContext,
        outermost_context_type & outermostContext )
      {
        outermostContext.add( pInnerContext );
      }
    };

    struct context_ptr_impl_other_context
    {
      template< class OtherContext, class State >
      static const typename OtherContext::inner_context_ptr_type &
      context_ptr_impl( const State & stt )
      {
        BOOST_ASSERT( get_pointer( stt.pContext_ ) != 0 );
        return stt.pContext_->template context_ptr< OtherContext >();
      }
    };
    friend struct context_ptr_impl_other_context;

    struct context_ptr_impl_my_context
    {
      template< class OtherContext, class State >
      static const typename OtherContext::inner_context_ptr_type &
      context_ptr_impl( const State & stt )
      {
        BOOST_ASSERT( get_pointer( stt.pContext_ ) != 0 );
        return stt.pContext_;
      }
    };
    friend struct context_ptr_impl_my_context;

    struct context_impl_other_context
    {
      template< class OtherContext, class State >
      static OtherContext & context_impl( State & stt )
      {
        BOOST_ASSERT( get_pointer( stt.pContext_ ) != 0 );
        return stt.pContext_->template context< OtherContext >();
      }
    };
    friend struct context_impl_other_context;

    struct context_impl_this_context
    {
      template< class OtherContext, class State >
      static OtherContext & context_impl( State & stt )
      {
        return *polymorphic_downcast< MostDerived * >( &stt );
      }
    };
    friend struct context_impl_this_context;

    template< class DestinationState, class TransitionAction >
    result transit_impl( const TransitionAction & transitionAction )
    {
      base_type::reaction_initiated();

      typedef typename mpl::find_if<
        context_type_list,
        mpl::contains<
          typename DestinationState::context_type_list,
          mpl::placeholders::_ > >::type common_context_iter;
      typedef typename mpl::deref< common_context_iter >::type
        common_context_type;
      typedef typename mpl::at<
        typename mpl::push_front< context_type_list, MostDerived >::type,
        typename mpl::distance<
          typename mpl::begin< context_type_list >::type,
          common_context_iter >::type >::type termination_state_type;

      // If you receive a
      // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or
      // similar compiler error here then you tried to make a transition to
      // history from a state residing on the same level as the history
      // connector (or from a direct or indirect inner state). Since the
      // outer state has never been left no history has ever been saved.
      BOOST_STATIC_ASSERT( (
        mpl::or_<
          mpl::not_< typename DestinationState::history_destination >,
          mpl::not_< is_same<
            typename DestinationState::context_type,
            common_context_type > > >::value ) );

      termination_state_type & terminationState(
        context< termination_state_type >() );
      const typename
        common_context_type::inner_context_ptr_type pCommonContext(
          terminationState.context_ptr< common_context_type >() );
      outermost_context_type & outermostContext(
        pCommonContext->outermost_context() );

      outermostContext.terminate( terminationState );
      outermostContext.add( pCommonContext );
      transitionAction( *pCommonContext );

      typedef typename detail::make_context_list<
        common_context_type, DestinationState >::type context_list_type;

      // If you receive a
      // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or
      // similar compiler error here then you tried to make an invalid
      // transition between different orthogonal regions.
      BOOST_STATIC_ASSERT( ( mpl::equal_to<
        typename termination_state_type::orthogonal_position,
        typename mpl::front< context_list_type >::type::orthogonal_position
      >::value ) );

      detail::constructor<
        context_list_type, outermost_context_type >::construct(
          pCommonContext, outermostContext );

      return do_discard_event;
    }

    struct local_react_impl_nonempty
    {
      template< class ReactionList, class State >
      static result local_react_impl(
        State & stt,
        const event_base_type & evt,
        typename rtti_policy_type::id_type eventType )
      {
        result reactionResult = mpl::front< ReactionList >::type::react(
          *polymorphic_downcast< MostDerived * >( &stt ), evt, eventType );

        if ( reactionResult == no_reaction )
        {
          reactionResult = stt.template local_react<
            typename mpl::pop_front< ReactionList >::type >( evt, eventType );
        }

        return reactionResult;
      }
    };
    friend struct local_react_impl_nonempty;

    struct local_react_impl_empty
    {
      template< class ReactionList, class State >
      static result local_react_impl(
        State &, const event_base_type &, typename rtti_policy_type::id_type )
      {
        return do_forward_event;
      }
    };

    template< class ReactionList >
    result local_react(
      const event_base_type & evt,
      typename rtti_policy_type::id_type eventType )
    {
      typedef typename mpl::if_<
        mpl::empty< ReactionList >,
        local_react_impl_empty,
        local_react_impl_nonempty
      >::type impl;
      return impl::template local_react_impl< ReactionList >(
        *this, evt, eventType );
    }

    struct outer_state_ptr_impl_non_outermost
    {
      template< class State >
      static const state_base_type * outer_state_ptr_impl( const State & stt )
      {
        return get_pointer( stt.pContext_ );
      }
    };
    friend struct outer_state_ptr_impl_non_outermost;

    struct outer_state_ptr_impl_outermost
    {
      template< class State >
      static const state_base_type * outer_state_ptr_impl( const State & )
      {
        return 0;
      }
    };

    struct node_state_deep_construct_inner_impl_non_empty_list
    {
      template< class InnerList >
      static void node_state_deep_construct_inner_impl(
        const inner_context_ptr_type & pInnerContext,
        outermost_context_type & outermostContext )
      {
        typedef typename mpl::front< InnerList >::type current_inner;

        // If you receive a
        // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or
        // similar compiler error here then there is a mismatch between the
        // orthogonal position of a state and its position in the inner initial
        // list of its outer state.
        BOOST_STATIC_ASSERT( ( is_same<
          current_inner,
          typename mpl::at<
            typename current_inner::context_type::inner_initial_list,
            typename current_inner::orthogonal_position >::type >::value ) );

        current_inner::reserve_history_slot( outermostContext );
        current_inner::deep_construct( pInnerContext, outermostContext );

        typedef typename mpl::pop_front< InnerList >::type recurse_list;
        node_state_deep_construct_inner_impl_holder< recurse_list >::
          template node_state_deep_construct_inner_impl< recurse_list >(
            pInnerContext, outermostContext );
      }
    };

    struct node_state_deep_construct_inner_impl_empty_list
    {
      template< class InnerList >
      static void node_state_deep_construct_inner_impl(
        const inner_context_ptr_type &, outermost_context_type & ) {}
    };

    template< class InnerList >
    struct node_state_deep_construct_inner_impl_holder : mpl::if_<
      mpl::empty< InnerList >,
      node_state_deep_construct_inner_impl_empty_list,
      node_state_deep_construct_inner_impl_non_empty_list >::type {};

    template< class InnerList >
    static void node_state_deep_construct_inner(
      const inner_context_ptr_type & pInnerContext,
      outermost_context_type & outermostContext )
    {
      node_state_deep_construct_inner_impl_holder< InnerList >::
        template node_state_deep_construct_inner_impl< InnerList >(
          pInnerContext, outermostContext );
    }

    struct reserve_shallow_history_slot_impl_no
    {
      static void reserve_shallow_history_slot_impl(
        outermost_context_type & ) {}
    };

    struct reserve_shallow_history_slot_impl_yes
    {
      static void reserve_shallow_history_slot_impl(
        outermost_context_type & outermostContext )
      {
        outermostContext.template reserve_shallow_history_slot<
          MostDerived >();
      }
    };

    template< bool reserveShallowHistorySlot >
    static void reserve_shallow_history_slot(
      outermost_context_type & outermostContext )
    {
      typedef typename mpl::if_<
        mpl::bool_< reserveShallowHistorySlot >,
        reserve_shallow_history_slot_impl_yes,
        reserve_shallow_history_slot_impl_no
      >::type impl;

      impl::reserve_shallow_history_slot_impl( outermostContext );
    }

    struct check_store_shallow_history_impl_no
    {
      template< class State >
      static void check_store_shallow_history_impl( State & ) {}
    };

    struct check_store_shallow_history_impl_yes
    {
      template< class State >
      static void check_store_shallow_history_impl( State & stt )
      {
        // If we are not the termination state then it can only be one of our
        // direct or indirect outer states
        if ( !stt.state_base_type::termination_state() )
        {
          stt.outermost_context().template store_shallow_history<
            MostDerived >();
        }
      }
    };
    friend struct check_store_shallow_history_impl_yes;

    template< bool storeShallowHistory >
    void check_store_shallow_history()
    {
      typedef typename mpl::if_<
        mpl::bool_< storeShallowHistory >,
        check_store_shallow_history_impl_yes,
        check_store_shallow_history_impl_no
      >::type impl;
      impl::check_store_shallow_history_impl( *this );
    }

    struct reserve_deep_history_slot_impl_no
    {
      static void reserve_deep_history_slot_impl(
        outermost_context_type & ) {}
    };

    struct reserve_deep_history_slot_impl_yes
    {
      static void reserve_deep_history_slot_impl(
        outermost_context_type & outermostContext )
      {
        outermostContext.template reserve_deep_history_slot<
          MostDerived >();
      }
    };

    template< bool reserveDeepHistorySlot >
    static void reserve_deep_history_slot(
      outermost_context_type & outermostContext )
    {
      typedef typename mpl::if_<
        mpl::bool_< reserveDeepHistorySlot >,
        reserve_deep_history_slot_impl_yes,
        reserve_deep_history_slot_impl_no
      >::type impl;

      impl::reserve_deep_history_slot_impl( outermostContext );
    }

    struct check_store_deep_history_impl_no
    {
      template< class State >
      static void check_store_deep_history_impl( State & ) {}
    };

    struct check_store_deep_history_impl_yes {
      template< class State >
      static void check_store_deep_history_impl( State & stt )
      {
        stt.store_deep_history_impl< MostDerived >();
        // If we are not the termination state then it can only be one of our
        // direct or indirect outer states
      }
    };
    friend struct check_store_deep_history_impl_yes;

    template< bool storeDeepHistory >
    void check_store_deep_history()
    {
      typedef typename mpl::if_<
        mpl::bool_< storeDeepHistory >,
        check_store_deep_history_impl_yes,
        check_store_deep_history_impl_no
      >::type impl;
      impl::check_store_deep_history_impl( *this );
    }


    context_ptr_type pContext_;
};



} // namespace fsm
} // namespace boost



#endif
