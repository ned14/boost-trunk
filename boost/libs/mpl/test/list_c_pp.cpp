/* #line 1	"list_c.hpp"	/* stack depth 1 */
/* #line 1	"use_preprocessed.hpp"	/* stack depth 2 */
/* #line 20	"list_c.hpp"	/* stack depth 1 */
/* #line 1	"impl.hpp"	/* stack depth 2 */
/* #line 1	"list.hpp"	/* stack depth 3 */
/* #line 20	"impl.hpp"	/* stack depth 2 */
/* #line 1	"cat.hpp"	/* stack depth 3 */
/* #line 21	"impl.hpp"	/* stack depth 2 */
/* #line 1	"stringize.hpp"	/* stack depth 3 */
/* #line 22	"impl.hpp"	/* stack depth 2 */
/* #line 1	"list20.hpp"	/* stack depth 3 */
/* #line 1	"use_preprocessed.hpp"	/* stack depth 4 */
/* #line 20	"list20.hpp"	/* stack depth 3 */
/* #line 1	"list10.hpp"	/* stack depth 4 */
/* #line 1	"use_preprocessed.hpp"	/* stack depth 5 */
/* #line 20	"list10.hpp"	/* stack depth 4 */
/* #line 1	"list0.hpp"	/* stack depth 5 */
/* #line 1	"begin_end.hpp"	/* stack depth 6 */
/* #line 1	"begin_end.hpp"	/* stack depth 7 */
/* #line 1	"sequence_tag.hpp"	/* stack depth 8 */
namespace boost {
namespace mpl {
template< typename Sequence >
struct sequence_tag
{
typedef typename Sequence::tag type;
};
}
}
/* #line 20	"begin_end.hpp"	/* stack depth 7 */
/* #line 1	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"placeholder.hpp"	/* stack depth 9 */
/* #line 1	"arity.hpp"	/* stack depth 10 */
/* #line 20	"placeholder.hpp"	/* stack depth 9 */
/* #line 1	"repeat.hpp"	/* stack depth 10 */
/* #line 22	"placeholder.hpp"	/* stack depth 9 */
/* #line 1	"inc.hpp"	/* stack depth 10 */
/* #line 23	"placeholder.hpp"	/* stack depth 9 */
/* #line 1	"cat.hpp"	/* stack depth 10 */
/* #line 24	"placeholder.hpp"	/* stack depth 9 */
namespace boost {
namespace mpl {
template< long N > struct arg;
typedef arg<-1> _;
namespace placeholder {
using boost::mpl::_;
}
typedef arg<1> _1; namespace placeholder { using boost::mpl::_1; } typedef arg<2> _2; namespace placeholder { using boost::mpl::_2; } typedef arg<3> _3; namespace placeholder { using boost::mpl::_3; } typedef arg<4> _4; namespace placeholder { using boost::mpl::_4; } typedef arg<5> _5; namespace placeholder { using boost::mpl::_5; } typedef arg<6> _6; namespace placeholder { using boost::mpl::_6; }
}
}
/* #line 20	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"lambda_fwd.hpp"	/* stack depth 9 */
namespace boost {
namespace mpl {
template< typename T > struct lambda;
}
}
/* #line 21	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"arity.hpp"	/* stack depth 9 */
/* #line 22	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"arity.hpp"	/* stack depth 9 */
/* #line 1	"config.hpp"	/* stack depth 10 */
/* #line 1	"user.hpp"	/* stack depth 11 */
/* #line 26	"config.hpp"	/* stack depth 10 */
/* #line 1	"suffix.hpp"	/* stack depth 11 */
/* #line 1	"limits.h"	/* stack depth 12 */
/* #line 1	"ansi_parms.h"	/* stack depth 13 */
/* #line 1	"msl_c_version.h"	/* stack depth 14 */
/* #line 11	"ansi_parms.h"	/* stack depth 13 */
/* #line 1	"mslGlobals.h"	/* stack depth 14 */
/* #line 1	"ansi_prefix.Win32.h"	/* stack depth 15 */
/* #line 1	"os_enum.h"	/* stack depth 16 */
/* #line 11	"ansi_prefix.Win32.h"	/* stack depth 15 */
/* #line 1	"x86_prefix.h"	/* stack depth 16 */
/* #line 15	"ansi_prefix.Win32.h"	/* stack depth 15 */
/* #line 1	"wchar_t.h"	/* stack depth 16 */
/* #line 1	"ansi_parms.h"	/* stack depth 17 */
/* #line 11	"wchar_t.h"	/* stack depth 16 */
namespace std {
extern "C"{
typedef wchar_t wint_t;
typedef wchar_t wctype_t;
typedef int mbstate_t;
typedef wchar_t Wint_t;
}
}
/* #line 167	"ansi_prefix.Win32.h"	/* stack depth 15 */
/* #line 1	"defaultlibs.win32.h"	/* stack depth 16 */
#pragma comment(lib, "MSL_All_x86.lib")
/* #line 181	"ansi_prefix.Win32.h"	/* stack depth 15 */
/* #line 41	"mslGlobals.h"	/* stack depth 14 */
/* #line 13	"ansi_parms.h"	/* stack depth 13 */
/* #line 11	"limits.h"	/* stack depth 12 */
/* #line 1	"climits"	/* stack depth 13 */
/* #line 1	"ansi_parms.h"	/* stack depth 14 */
/* #line 11	"climits"	/* stack depth 13 */
/* #line 17	"limits.h"	/* stack depth 12 */
/* #line 30	"suffix.hpp"	/* stack depth 11 */
/* #line 57	"config.hpp"	/* stack depth 10 */
/* #line 20	"arity.hpp"	/* stack depth 9 */
namespace boost {
namespace mpl {
namespace aux {
template< typename F, long N >
struct arity
{
static const long value = N ;
};
}
}
}
/* #line 23	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"params.hpp"	/* stack depth 9 */
/* #line 1	"add.hpp"	/* stack depth 10 */
/* #line 1	"dec.hpp"	/* stack depth 11 */
/* #line 16	"add.hpp"	/* stack depth 10 */
/* #line 1	"inc.hpp"	/* stack depth 11 */
/* #line 17	"add.hpp"	/* stack depth 10 */
/* #line 1	"elem.hpp"	/* stack depth 11 */
/* #line 18	"add.hpp"	/* stack depth 10 */
/* #line 1	"while.hpp"	/* stack depth 11 */
/* #line 1	"if.hpp"	/* stack depth 12 */
/* #line 1	"bool.hpp"	/* stack depth 13 */
/* #line 16	"if.hpp"	/* stack depth 12 */
/* #line 1	"elem.hpp"	/* stack depth 13 */
/* #line 17	"if.hpp"	/* stack depth 12 */
/* #line 16	"while.hpp"	/* stack depth 11 */
/* #line 1	"eat.hpp"	/* stack depth 12 */
/* #line 17	"while.hpp"	/* stack depth 11 */
/* #line 19	"add.hpp"	/* stack depth 10 */
/* #line 20	"params.hpp"	/* stack depth 9 */
/* #line 1	"sub.hpp"	/* stack depth 10 */
/* #line 1	"dec.hpp"	/* stack depth 11 */
/* #line 16	"sub.hpp"	/* stack depth 10 */
/* #line 1	"elem.hpp"	/* stack depth 11 */
/* #line 17	"sub.hpp"	/* stack depth 10 */
/* #line 1	"while.hpp"	/* stack depth 11 */
/* #line 18	"sub.hpp"	/* stack depth 10 */
/* #line 21	"params.hpp"	/* stack depth 9 */
/* #line 1	"comma_if.hpp"	/* stack depth 10 */
/* #line 1	"comma.hpp"	/* stack depth 11 */
/* #line 16	"comma_if.hpp"	/* stack depth 10 */
/* #line 1	"empty.hpp"	/* stack depth 11 */
/* #line 17	"comma_if.hpp"	/* stack depth 10 */
/* #line 1	"if.hpp"	/* stack depth 11 */
/* #line 18	"comma_if.hpp"	/* stack depth 10 */
/* #line 22	"params.hpp"	/* stack depth 9 */
/* #line 1	"repeat.hpp"	/* stack depth 10 */
/* #line 23	"params.hpp"	/* stack depth 9 */
/* #line 1	"elem.hpp"	/* stack depth 10 */
/* #line 24	"params.hpp"	/* stack depth 9 */
/* #line 1	"cat.hpp"	/* stack depth 10 */
/* #line 25	"params.hpp"	/* stack depth 9 */
/* #line 24	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"enum.hpp"	/* stack depth 9 */
/* #line 1	"add.hpp"	/* stack depth 10 */
/* #line 20	"enum.hpp"	/* stack depth 9 */
/* #line 1	"sub.hpp"	/* stack depth 10 */
/* #line 21	"enum.hpp"	/* stack depth 9 */
/* #line 1	"comma_if.hpp"	/* stack depth 10 */
/* #line 22	"enum.hpp"	/* stack depth 9 */
/* #line 1	"repeat.hpp"	/* stack depth 10 */
/* #line 23	"enum.hpp"	/* stack depth 9 */
/* #line 1	"elem.hpp"	/* stack depth 10 */
/* #line 24	"enum.hpp"	/* stack depth 9 */
/* #line 1	"cat.hpp"	/* stack depth 10 */
/* #line 25	"enum.hpp"	/* stack depth 9 */
/* #line 25	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"project1st.hpp"	/* stack depth 9 */
/* #line 26	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"def_params_tail.hpp"	/* stack depth 9 */
/* #line 1	"arity.hpp"	/* stack depth 10 */
/* #line 20	"def_params_tail.hpp"	/* stack depth 9 */
/* #line 1	"none.hpp"	/* stack depth 10 */
namespace boost {
namespace mpl {
namespace aux {
struct none;
template< typename > struct reject_if_none {};
template<> struct reject_if_none<none>;
template< typename > struct reject_if_not_none;
template<> struct reject_if_not_none<none> {};
}
}
}
/* #line 21	"def_params_tail.hpp"	/* stack depth 9 */
/* #line 1	"add.hpp"	/* stack depth 10 */
/* #line 23	"def_params_tail.hpp"	/* stack depth 9 */
/* #line 1	"sub.hpp"	/* stack depth 10 */
/* #line 24	"def_params_tail.hpp"	/* stack depth 9 */
/* #line 1	"elem.hpp"	/* stack depth 10 */
/* #line 25	"def_params_tail.hpp"	/* stack depth 9 */
/* #line 1	"repeat.hpp"	/* stack depth 10 */
/* #line 26	"def_params_tail.hpp"	/* stack depth 9 */
/* #line 1	"cat.hpp"	/* stack depth 10 */
/* #line 27	"def_params_tail.hpp"	/* stack depth 9 */
/* #line 27	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"lambda_support.hpp"	/* stack depth 9 */
/* #line 1	"ttp.hpp"	/* stack depth 10 */
/* #line 1	"config.hpp"	/* stack depth 11 */
/* #line 20	"ttp.hpp"	/* stack depth 10 */
/* #line 20	"lambda_support.hpp"	/* stack depth 9 */
/* #line 1	"config.hpp"	/* stack depth 10 */
/* #line 21	"lambda_support.hpp"	/* stack depth 9 */
/* #line 28	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"dtp.hpp"	/* stack depth 9 */
/* #line 29	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 1	"config.hpp"	/* stack depth 9 */
/* #line 30	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 21	"begin_end.hpp"	/* stack depth 7 */
namespace boost {
namespace mpl {
template< typename Tag >
struct begin_algorithm_traits
{
template< typename Sequence > struct algorithm
{
typedef typename Sequence::begin type;
};
};
template< typename Tag >
struct end_algorithm_traits
{
template< typename Sequence > struct algorithm
{
typedef typename Sequence::end type;
};
};
template< typename Sequence >
struct begin
{
private:
typedef typename sequence_tag<Sequence>::type tag_;
public:
typedef typename begin_algorithm_traits<tag_>
::template algorithm< Sequence >::type type;
};
template< typename Sequence >
struct end
{
private:
typedef typename sequence_tag<Sequence>::type tag_;
public:
typedef typename end_algorithm_traits<tag_>
::template algorithm< Sequence >::type type;
};
template<> struct begin< _> { template< typename T0 , typename T1 = aux::none , typename T2 = aux::none , typename T3 = aux::none , typename T4 = aux::none > struct apply : begin< T0> { }; }; namespace aux { template< long N > struct arity< begin< _> , N > { static const long value = 5; }; } template<> struct lambda< begin< _> > { typedef begin< _> type; };
template<> struct end< _> { template< typename T0 , typename T1 = aux::none , typename T2 = aux::none , typename T3 = aux::none , typename T4 = aux::none > struct apply : end< T0> { }; }; namespace aux { template< long N > struct arity< end< _> , N > { static const long value = 5; }; } template<> struct lambda< end< _> > { typedef end< _> type; };
}
}
/* #line 20	"begin_end.hpp"	/* stack depth 6 */
/* #line 1	"iterator.hpp"	/* stack depth 7 */
/* #line 1	"none.hpp"	/* stack depth 8 */
/* #line 20	"iterator.hpp"	/* stack depth 7 */
/* #line 1	"iterator_category.hpp"	/* stack depth 8 */
namespace boost {
namespace mpl {
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;
template< typename Iterator >
struct iterator_category
{
typedef typename Iterator::category type;
};
}
}
/* #line 21	"iterator.hpp"	/* stack depth 7 */
/* #line 1	"lambda_fwd.hpp"	/* stack depth 8 */
/* #line 22	"iterator.hpp"	/* stack depth 7 */
/* #line 1	"lambda_support.hpp"	/* stack depth 8 */
/* #line 23	"iterator.hpp"	/* stack depth 7 */
namespace boost {
namespace mpl {
template< typename Node >
struct list_iterator
{
typedef forward_iterator_tag category;
typedef typename Node::item type;
typedef list_iterator<typename Node::next> next;
};
template<>
struct list_iterator<aux::none>
{
typedef forward_iterator_tag category;
};
template< typename Node >
struct lambda< list_iterator<Node> >
{
typedef list_iterator<Node> type;
};
}
}
/* #line 21	"begin_end.hpp"	/* stack depth 6 */
/* #line 1	"tag.hpp"	/* stack depth 7 */
namespace boost {
namespace mpl {
namespace aux {
struct list_tag;
}
}
}
/* #line 22	"begin_end.hpp"	/* stack depth 6 */
/* #line 1	"node.hpp"	/* stack depth 7 */
/* #line 1	"tag.hpp"	/* stack depth 8 */
/* #line 20	"node.hpp"	/* stack depth 7 */
/* #line 1	"none.hpp"	/* stack depth 8 */
/* #line 21	"node.hpp"	/* stack depth 7 */
/* #line 1	"config.hpp"	/* stack depth 8 */
/* #line 22	"node.hpp"	/* stack depth 7 */
namespace boost {
namespace mpl {
template<
typename T
, typename Next
>
struct list_node
{
typedef aux::list_tag tag;
typedef list_node type;
typedef T item;
typedef Next next;
};
struct null_node
{
typedef aux::list_tag tag;
typedef null_node type;
};
}
}
/* #line 23	"begin_end.hpp"	/* stack depth 6 */
namespace boost {
namespace mpl {
template<>
struct begin_algorithm_traits< aux::list_tag >
{
template< typename List > struct algorithm
{
typedef list_iterator<List> type;
};
};
template<>
struct end_algorithm_traits< aux::list_tag >
{
template< typename > struct algorithm
{
typedef list_iterator<null_node> type;
};
};
}
}
/* #line 20	"list0.hpp"	/* stack depth 5 */
/* #line 1	"push_front.hpp"	/* stack depth 6 */
/* #line 1	"push_front.hpp"	/* stack depth 7 */
/* #line 1	"sequence_tag.hpp"	/* stack depth 8 */
/* #line 20	"push_front.hpp"	/* stack depth 7 */
/* #line 1	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 21	"push_front.hpp"	/* stack depth 7 */
namespace boost {
namespace mpl {
template< typename Tag >
struct push_front_algorithm_traits
{
template< typename Sequence, typename T > struct algorithm;
};
template<
typename Sequence
, typename T
>
struct push_front
{
private:
typedef typename sequence_tag<Sequence>::type tag_;
public:
typedef typename push_front_algorithm_traits<tag_>
::template algorithm< Sequence,T >::type type;
};
template<> struct push_front< _ , _> { template< typename T0 , typename T1 , typename T2 = aux::none , typename T3 = aux::none , typename T4 = aux::none > struct apply : push_front< T0 , T1> { }; }; namespace aux { template< long N > struct arity< push_front< _ , _> , N > { static const long value = 5; }; } template<> struct lambda< push_front< _ , _> > { typedef push_front< _ , _> type; };
}
}
/* #line 20	"push_front.hpp"	/* stack depth 6 */
/* #line 1	"tag.hpp"	/* stack depth 7 */
/* #line 21	"push_front.hpp"	/* stack depth 6 */
/* #line 1	"node.hpp"	/* stack depth 7 */
/* #line 22	"push_front.hpp"	/* stack depth 6 */
namespace boost {
namespace mpl {
template<>
struct push_front_algorithm_traits< aux::list_tag >
{
template< typename List, typename T > struct algorithm
{
typedef list_node<T,List> type;
};
};
}
}
/* #line 21	"list0.hpp"	/* stack depth 5 */
/* #line 1	"pop_front.hpp"	/* stack depth 6 */
/* #line 1	"pop_front.hpp"	/* stack depth 7 */
/* #line 1	"sequence_traits.hpp"	/* stack depth 8 */
namespace boost {
namespace mpl {
template<typename Sequence>
struct sequence_traits
{
typedef typename Sequence::sequence_category sequence_category;
};
}
}
/* #line 20	"pop_front.hpp"	/* stack depth 7 */
namespace boost {
namespace mpl {
template<typename SequenceTag>
struct pop_front_algorithm_traits
{
template<typename Sequence> struct algorithm;
};
template<typename Sequence>
struct pop_front
: pop_front_algorithm_traits<
typename mpl::sequence_traits<Sequence>::sequence_category
>::template algorithm<Sequence>
{
};
}
}
/* #line 20	"pop_front.hpp"	/* stack depth 6 */
/* #line 1	"tag.hpp"	/* stack depth 7 */
/* #line 21	"pop_front.hpp"	/* stack depth 6 */
/* #line 1	"node.hpp"	/* stack depth 7 */
/* #line 22	"pop_front.hpp"	/* stack depth 6 */
namespace boost {
namespace mpl {
template<>
struct pop_front_algorithm_traits< aux::list_tag >
{
template< typename List, typename T > struct algorithm
{
typedef typename List::next type;
};
};
}
}
/* #line 22	"list0.hpp"	/* stack depth 5 */
/* #line 1	"clear.hpp"	/* stack depth 6 */
/* #line 1	"node.hpp"	/* stack depth 7 */
/* #line 20	"clear.hpp"	/* stack depth 6 */
/* #line 1	"tag.hpp"	/* stack depth 7 */
/* #line 21	"clear.hpp"	/* stack depth 6 */
/* #line 1	"clear.hpp"	/* stack depth 7 */
/* #line 1	"sequence_tag.hpp"	/* stack depth 8 */
/* #line 20	"clear.hpp"	/* stack depth 7 */
/* #line 1	"lambda_spec.hpp"	/* stack depth 8 */
/* #line 21	"clear.hpp"	/* stack depth 7 */
namespace boost {
namespace mpl {
template< typename Tag >
struct clear_algorithm_traits
{
template< typename Sequence > struct algorithm;
};
template< typename Sequence >
struct clear
{
private:
typedef typename sequence_tag<Sequence>::type tag_;
public:
typedef typename clear_algorithm_traits<tag_>
::template algorithm< Sequence >::type type;
};
template<> struct clear< _> { template< typename T0 , typename T1 = aux::none , typename T2 = aux::none , typename T3 = aux::none , typename T4 = aux::none > struct apply : clear< T0> { }; }; namespace aux { template< long N > struct arity< clear< _> , N > { static const long value = 5; }; } template<> struct lambda< clear< _> > { typedef clear< _> type; };
}
}
/* #line 22	"clear.hpp"	/* stack depth 6 */
namespace boost {
namespace mpl {
template<>
struct clear_algorithm_traits< aux::list_tag >
{
template< typename List > struct algorithm
{
typedef null_node type;
};
};
}
}
/* #line 23	"list0.hpp"	/* stack depth 5 */
/* #line 1	"node.hpp"	/* stack depth 6 */
/* #line 24	"list0.hpp"	/* stack depth 5 */
namespace boost {
namespace mpl {
typedef null_node list0;
}
}
/* #line 26	"list10.hpp"	/* stack depth 4 */
/* #line 1	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"node.hpp"	/* stack depth 6 */
/* #line 19	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"params.hpp"	/* stack depth 6 */
/* #line 20	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"repeat_2nd.hpp"	/* stack depth 6 */
/* #line 22	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"add.hpp"	/* stack depth 6 */
/* #line 23	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"dec.hpp"	/* stack depth 6 */
/* #line 24	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"if.hpp"	/* stack depth 6 */
/* #line 25	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"identity.hpp"	/* stack depth 6 */
/* #line 1	"empty.hpp"	/* stack depth 7 */
/* #line 16	"identity.hpp"	/* stack depth 6 */
/* #line 26	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"empty.hpp"	/* stack depth 6 */
/* #line 27	"numbered.hpp"	/* stack depth 5 */
/* #line 1	"cat.hpp"	/* stack depth 6 */
/* #line 28	"numbered.hpp"	/* stack depth 5 */
namespace boost {
namespace mpl {
template< typename T0 > struct list1 : list_node< T0 , list0 > { typedef list1 type; }; template< typename T0 , typename T1 > struct list2 : list_node< T0 , list1 < T1 > > { typedef list2 type; }; template< typename T0 , typename T1 , typename T2 > struct list3 : list_node< T0 , list2 < T1 , T2 > > { typedef list3 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 > struct list4 : list_node< T0 , list3 < T1 , T2 , T3 > > { typedef list4 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 > struct list5 : list_node< T0 , list4 < T1 , T2 , T3 , T4 > > { typedef list5 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 > struct list6 : list_node< T0 , list5 < T1 , T2 , T3 , T4 , T5 > > { typedef list6 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 > struct list7 : list_node< T0 , list6 < T1 , T2 , T3 , T4 , T5 , T6 > > { typedef list7 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 > struct list8 : list_node< T0 , list7 < T1 , T2 , T3 , T4 , T5 , T6 , T7 > > { typedef list8 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 > struct list9 : list_node< T0 , list8 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 > > { typedef list9 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 > struct list10 : list_node< T0 , list9 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 > > { typedef list10 type; };
}
}
/* #line 30	"list10.hpp"	/* stack depth 4 */
/* #line 26	"list20.hpp"	/* stack depth 3 */
/* #line 1	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"node.hpp"	/* stack depth 5 */
/* #line 19	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"params.hpp"	/* stack depth 5 */
/* #line 20	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"repeat_2nd.hpp"	/* stack depth 5 */
/* #line 22	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"add.hpp"	/* stack depth 5 */
/* #line 23	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"dec.hpp"	/* stack depth 5 */
/* #line 24	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"if.hpp"	/* stack depth 5 */
/* #line 25	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"identity.hpp"	/* stack depth 5 */
/* #line 26	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"empty.hpp"	/* stack depth 5 */
/* #line 27	"numbered.hpp"	/* stack depth 4 */
/* #line 1	"cat.hpp"	/* stack depth 5 */
/* #line 28	"numbered.hpp"	/* stack depth 4 */
namespace boost {
namespace mpl {
template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 > struct list11 : list_node< T0 , list10 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 > > { typedef list11 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 > struct list12 : list_node< T0 , list11 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 > > { typedef list12 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 > struct list13 : list_node< T0 , list12 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 > > { typedef list13 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 > struct list14 : list_node< T0 , list13 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 > > { typedef list14 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 > struct list15 : list_node< T0 , list14 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 > > { typedef list15 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 > struct list16 : list_node< T0 , list15 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 > > { typedef list16 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 > struct list17 : list_node< T0 , list16 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 > > { typedef list17 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 > struct list18 : list_node< T0 , list17 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 > > { typedef list18 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 > struct list19 : list_node< T0 , list18 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 > > { typedef list19 type; }; template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct list20 : list_node< T0 , list19 < T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 > > { typedef list20 type; };
}
}
/* #line 30	"list20.hpp"	/* stack depth 3 */
/* #line 32	"impl.hpp"	/* stack depth 2 */
/* #line 1	"count_if_not.hpp"	/* stack depth 3 */
/* #line 1	"default_params.hpp"	/* stack depth 4 */
/* #line 1	"add.hpp"	/* stack depth 5 */
/* #line 20	"default_params.hpp"	/* stack depth 4 */
/* #line 1	"sub.hpp"	/* stack depth 5 */
/* #line 21	"default_params.hpp"	/* stack depth 4 */
/* #line 1	"comma_if.hpp"	/* stack depth 5 */
/* #line 22	"default_params.hpp"	/* stack depth 4 */
/* #line 1	"repeat.hpp"	/* stack depth 5 */
/* #line 23	"default_params.hpp"	/* stack depth 4 */
/* #line 1	"elem.hpp"	/* stack depth 5 */
/* #line 24	"default_params.hpp"	/* stack depth 4 */
/* #line 1	"cat.hpp"	/* stack depth 5 */
/* #line 25	"default_params.hpp"	/* stack depth 4 */
/* #line 20	"count_if_not.hpp"	/* stack depth 3 */
/* #line 1	"repeat.hpp"	/* stack depth 4 */
/* #line 22	"count_if_not.hpp"	/* stack depth 3 */
/* #line 1	"expr_if.hpp"	/* stack depth 4 */
/* #line 1	"bool.hpp"	/* stack depth 5 */
/* #line 16	"expr_if.hpp"	/* stack depth 4 */
/* #line 23	"count_if_not.hpp"	/* stack depth 3 */
/* #line 1	"same_traits.hpp"	/* stack depth 4 */
/* #line 1	"ice.hpp"	/* stack depth 5 */
namespace boost{
namespace type_traits{
typedef char yes_type;
typedef double no_type;
template <bool b>
struct ice_not
{ static const bool value = true ; };
template <>
struct ice_not<true>
{ static const bool value = false ; };
template <bool b1, bool b2, bool b3 = false, bool b4 = false, bool b5 = false, bool b6 = false, bool b7 = false>
struct ice_or;
template <bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7>
struct ice_or
{
static const bool value = true ;
};
template <>
struct ice_or<false, false, false, false, false, false, false>
{
static const bool value = false ;
};
template <bool b1, bool b2, bool b3 = true, bool b4 = true, bool b5 = true, bool b6 = true, bool b7 = true>
struct ice_and;
template <bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7>
struct ice_and
{
static const bool value = false ;
};
template <>
struct ice_and<true, true, true, true, true, true, true>
{
static const bool value = true ;
};
template <int b1, int b2>
struct ice_eq
{
static const bool value = (b1 == b2) ;
};
template <int b1, int b2>
struct ice_ne
{
static const bool value = (b1 != b2) ;
};
template <int b1, int b2>
const bool ice_eq<b1,b2>::value;
template <int b1, int b2>
const bool ice_ne<b1,b2>::value;
}
}
/* #line 18	"same_traits.hpp"	/* stack depth 4 */
/* #line 1	"fwd.hpp"	/* stack depth 5 */
/* #line 1	"cstdlib"	/* stack depth 6 */
/* #line 1	"ansi_parms.h"	/* stack depth 7 */
/* #line 11	"cstdlib"	/* stack depth 6 */
/* #line 1	"div_t.h"	/* stack depth 7 */
/* #line 1	"ansi_parms.h"	/* stack depth 8 */
/* #line 11	"div_t.h"	/* stack depth 7 */
#pragma options align=native
namespace std {
extern "C"{
typedef struct {
int quot;
int rem;
} div_t;
typedef struct {
long quot;
long rem;
} ldiv_t;
typedef struct
{
long long quot;
long long rem;
} lldiv_t;
}
}
#pragma options align=reset
/* #line 19	"cstdlib"	/* stack depth 6 */
/* #line 1	"size_t.h"	/* stack depth 7 */
/* #line 1	"ansi_parms.h"	/* stack depth 8 */
/* #line 11	"size_t.h"	/* stack depth 7 */
namespace std {
extern "C"{
typedef __typeof__(sizeof(0)) size_t;
}
}
/* #line 20	"cstdlib"	/* stack depth 6 */
/* #line 1	"null.h"	/* stack depth 7 */
/* #line 1	"ansi_parms.h"	/* stack depth 8 */
/* #line 13	"null.h"	/* stack depth 7 */
/* #line 21	"cstdlib"	/* stack depth 6 */
/* #line 1	"wchar_t.h"	/* stack depth 7 */
/* #line 24	"cstdlib"	/* stack depth 6 */
/* #line 1	"extras.h"	/* stack depth 7 */
/* #line 1	"ansi_parms.h"	/* stack depth 8 */
/* #line 11	"extras.h"	/* stack depth 7 */
/* #line 1	"size_t.h"	/* stack depth 8 */
/* #line 12	"extras.h"	/* stack depth 7 */
/* #line 1	"unistd.h"	/* stack depth 8 */
/* #line 1	"ansi_parms.h"	/* stack depth 9 */
/* #line 11	"unistd.h"	/* stack depth 8 */
/* #line 1	"size_t.h"	/* stack depth 9 */
/* #line 12	"unistd.h"	/* stack depth 8 */
extern "C"{
int __cdecl access(const char*, int);
int __cdecl chdir(const char*);
int __cdecl close(int);
char* __cdecl cuserid(char* );
int __cdecl exec(const char*,...);
char* __cdecl getcwd(char *, int);
char* __cdecl getlogin(void);
int __cdecl isatty(int);
long __cdecl lseek(int, long, int);
int __cdecl read(int , void*, ::std::size_t );
int __cdecl rmdir(const char*);
unsigned int __cdecl sleep(unsigned int);
char* __cdecl ttyname(int );
int __cdecl unlink(const char*);
int __cdecl write(int , const void*, ::std::size_t );
inline int __cdecl getppid(void) {return 8000 ;}
inline int __cdecl getuid(void) {return 200 ;}
inline int __cdecl geteuid(void) {return 200 ;}
inline int __cdecl getgid(void) {return 100 ;}
inline int __cdecl getegid(void) {return 100 ;}
inline int __cdecl getpgrp(void) {return 9000 ;}
}
/* #line 1	"unistd.win32.h"	/* stack depth 9 */
/* #line 1	"ansi_parms.h"	/* stack depth 10 */
/* #line 11	"unistd.win32.h"	/* stack depth 9 */
/* #line 1	"size_t.h"	/* stack depth 10 */
/* #line 12	"unistd.win32.h"	/* stack depth 9 */
extern "C"{
int __cdecl dup(int);
int __cdecl dup2(int,int);
int __cdecl getpid(void);
int __cdecl execl(const char *, ...);
int __cdecl execv(const char *,const char *const*);
int __cdecl execle(const char *,...);
int __cdecl execve(const char *,const char *const*, const char *const*);
int __cdecl execlp(const char *,...);
int __cdecl execvp(const char *,const char *const *);
int __cdecl execlpe(const char *,...);
int __cdecl execvpe(const char *,const char *const *, const char *const*);
int __cdecl spawnl(int,const char *, ...);
int __cdecl spawnv(int,const char *,const char *const*);
int __cdecl spawnle(int,const char *,...);
int __cdecl spawnve(int,const char *,const char *const*, const char *const*);
int __cdecl spawnlp(int,const char *,...);
int __cdecl spawnvp(int,const char *,const char *const *);
int __cdecl spawnlpe(int,const char *,...);
int __cdecl spawnvpe(int,const char *,const char *const *, const char *const*);
int __cdecl cwait(int *,int,int);
int __cdecl _chdir(const char *);
int __cdecl _close(int);
char* __cdecl _cuserid(char *);
int __cdecl _exec(const char *,...);
char* __cdecl _getcwd(char *, int );
char* __cdecl _getlogin(void);
long __cdecl _lseek(int, long , int);
int __cdecl _isatty(int);
int __cdecl _read(int , void* , ::std::size_t );
int __cdecl _rmdir(const char *);
unsigned int __cdecl _sleep(unsigned int);
char* __cdecl _ttyname(int);
int __cdecl _unlink(const char *);
int __cdecl _write(int , const void * , ::std::size_t );
int __cdecl _access(const char *, int );
int __cdecl _getppid(void);
int __cdecl _getuid(void);
int __cdecl _geteuid(void);
int __cdecl _getgid(void);
int __cdecl _getegid(void);
int __cdecl _getpgrp(void);
int __cdecl _getpid(void);
int __cdecl _execl(const char *, ...);
int __cdecl _execv(const char *,const char *const*);
int __cdecl _execle(const char *,...);
int __cdecl _execve(const char *,const char *const*, const char *const*);
int __cdecl _execlp(const char *,...);
int __cdecl _execvp(const char *,const char *const *);
int __cdecl _execlpe(const char *,...);
int __cdecl _execvpe(const char *,const char *const *, const char *const*);
int __cdecl _spawnl(int,const char *, ...);
int __cdecl _spawnv(int,const char *,const char *const*);
int __cdecl _spawnle(int,const char *,...);
int __cdecl _spawnve(int,const char *,const char *const*, const char *const*);
int __cdecl _spawnlp(int,const char *,...);
int __cdecl _spawnvp(int,const char *,const char *const *);
int __cdecl _spawnlpe(int,const char *,...);
int __cdecl _spawnvpe(int,const char *,const char *const *, const char *const*);
int __cdecl _cwait(int *,int,int);
}
/* #line 73	"unistd.h"	/* stack depth 8 */
/* #line 13	"extras.h"	/* stack depth 7 */
/* #line 1	"null.h"	/* stack depth 8 */
/* #line 14	"extras.h"	/* stack depth 7 */
/* #line 1	"stdio.posix.h"	/* stack depth 8 */
/* #line 1	"ansi_parms.h"	/* stack depth 9 */
/* #line 11	"stdio.posix.h"	/* stack depth 8 */
/* #line 1	"size_t.h"	/* stack depth 9 */
/* #line 12	"stdio.posix.h"	/* stack depth 8 */
/* #line 1	"null.h"	/* stack depth 9 */
/* #line 13	"stdio.posix.h"	/* stack depth 8 */
/* #line 1	"eof.h"	/* stack depth 9 */
/* #line 1	"ansi_parms.h"	/* stack depth 10 */
/* #line 14	"eof.h"	/* stack depth 9 */
/* #line 14	"stdio.posix.h"	/* stack depth 8 */
/* #line 1	"va_list.h"	/* stack depth 9 */
/* #line 1	"ansi_parms.h"	/* stack depth 10 */
/* #line 11	"va_list.h"	/* stack depth 9 */
namespace std {
extern "C"{
typedef char * va_list;
}
}
/* #line 15	"stdio.posix.h"	/* stack depth 8 */
/* #line 1	"file_struc.h"	/* stack depth 9 */
/* #line 1	"size_t.h"	/* stack depth 10 */
/* #line 15	"file_struc.h"	/* stack depth 9 */
/* #line 1	"wchar_t.h"	/* stack depth 10 */
/* #line 18	"file_struc.h"	/* stack depth 9 */
#pragma options align=native
namespace std {
extern "C"{
enum __file_kinds
{
__closed_file,
__disk_file,
__console_file,
__unavailable_file
};
enum __open_modes
{
__must_exist,
__create_if_necessary,
__create_or_truncate
};
enum __file_orientation
{
__unoriented,
__char_oriented,
__wide_oriented
};
enum __io_modes
{
__read = 1,
__write = 2,
__read_write = 3,
__append = 4
};
typedef struct
{
unsigned int open_mode : 2;
unsigned int io_mode : 3;
unsigned int buffer_mode : 2;
unsigned int file_kind : 3;
unsigned int file_orientation: 2;
unsigned int binary_io : 1;
} __file_modes;
enum __io_states
{
__neutral,
__writing,
__reading,
__rereading
};
typedef struct
{
unsigned int io_state : 3;
unsigned int free_buffer : 1;
unsigned char eof;
unsigned char error;
} __file_state;
typedef unsigned long __file_handle;
typedef unsigned long fpos_t;
typedef struct _FILE FILE;
enum __io_results
{
__no_io_error,
__io_error,
__io_EOF
};
typedef void (* __idle_proc) (void);
typedef int (* __pos_proc) (__file_handle file, fpos_t * position, int mode, __idle_proc idle_proc);
typedef int (* __io_proc) (__file_handle file, unsigned char * buff, size_t * count, __idle_proc idle_proc);
typedef int (* __close_proc) (__file_handle file);
struct _FILE
{
__file_handle handle;
__file_modes mode;
__file_state state;
unsigned char is_dynamically_allocated;
unsigned char char_buffer;
unsigned char char_buffer_overflow;
unsigned char ungetc_buffer[2 ];
wchar_t ungetwc_buffer[2 ];
unsigned long position;
unsigned char * buffer;
unsigned long buffer_size;
unsigned char * buffer_ptr;
unsigned long buffer_len;
unsigned long buffer_alignment;
unsigned long saved_buffer_len;
unsigned long buffer_pos;
__pos_proc position_proc;
__io_proc read_proc;
__io_proc write_proc;
__close_proc close_proc;
__idle_proc idle_proc;
struct _FILE * next_file_struct;
};
extern FILE __files[];
}
}
#pragma options align=reset
/* #line 16	"stdio.posix.h"	/* stack depth 8 */
/* #line 1	"stdio_api.h"	/* stack depth 9 */
/* #line 1	"ansi_parms.h"	/* stack depth 10 */
/* #line 11	"stdio_api.h"	/* stack depth 9 */
/* #line 1	"size_t.h"	/* stack depth 10 */
/* #line 13	"stdio_api.h"	/* stack depth 9 */
/* #line 1	"null.h"	/* stack depth 10 */
/* #line 14	"stdio_api.h"	/* stack depth 9 */
/* #line 1	"eof.h"	/* stack depth 10 */
/* #line 15	"stdio_api.h"	/* stack depth 9 */
/* #line 1	"va_list.h"	/* stack depth 10 */
/* #line 16	"stdio_api.h"	/* stack depth 9 */
/* #line 1	"wchar_t.h"	/* stack depth 10 */
/* #line 19	"stdio_api.h"	/* stack depth 9 */
/* #line 1	"file_struc.h"	/* stack depth 10 */
/* #line 22	"stdio_api.h"	/* stack depth 9 */
#pragma options align=native
namespace std {
extern "C"{
size_t __cdecl __fread(void *, size_t, size_t, FILE *);
size_t __cdecl __fwrite(const void *, size_t, size_t, FILE *);
fpos_t __cdecl _ftell(FILE *);
int __cdecl _fseek(FILE *, fpos_t, int);
int __cdecl __get_char(FILE * );
int __cdecl __put_char(int c,FILE * );
typedef struct
{
char * CharStr;
size_t MaxCharCount;
size_t CharsWritten;
} __OutStrCtrl;
typedef struct
{
char * NextChar;
int NullCharDetected;
} __InStrCtrl;
void * __cdecl __FileWrite(void *, const char *, size_t);
void * __cdecl __StringWrite(void *, const char *, size_t);
int __cdecl __FileRead(void *, int, int);
int __cdecl __StringRead(void *, int, int);
enum __ReadProcActions
{
__GetAChar,
__UngetAChar,
__TestForError
};
typedef struct
{
wchar_t * wCharStr;
size_t MaxCharCount;
size_t CharsWritten;
} __wOutStrCtrl;
typedef struct
{
wchar_t * wNextChar;
int wNullCharDetected;
} __wInStrCtrl;
void * __cdecl __wFileWrite(void *, const wchar_t *, size_t);
void * __cdecl __wStringWrite(void *, const wchar_t *, size_t);
wint_t __wFileRead(void *, wint_t, int);
wint_t __wStringRead(void *, wint_t, int);
enum __WReadProcActions
{
__GetAwChar,
__UngetAwChar,
__TestForwcsError
};
FILE * __cdecl __handle_open (__file_handle handle, const char * mode);
FILE * __cdecl __handle_reopen(__file_handle handle, const char * mode, FILE * );
void __cdecl __set_idle_proc(FILE * , __idle_proc idle_proc);
}
}
#pragma options align=reset
/* #line 17	"stdio.posix.h"	/* stack depth 8 */
extern "C"{
int __cdecl fileno(::std::FILE *);
::std::FILE * __cdecl fdopen(int , const char *);
int __cdecl _fileno(::std::FILE *);
::std::FILE * __cdecl _fdopen(int, const char *);
}
/* #line 15	"extras.h"	/* stack depth 7 */
/* #line 1	"extras.win32.h"	/* stack depth 8 */
/* #line 1	"ansi_parms.h"	/* stack depth 9 */
/* #line 12	"extras.win32.h"	/* stack depth 8 */
/* #line 1	"unistd.h"	/* stack depth 9 */
/* #line 13	"extras.win32.h"	/* stack depth 8 */
/* #line 1	"dirent.h"	/* stack depth 9 */
/* #line 1	"ansi_parms.h"	/* stack depth 10 */
/* #line 11	"dirent.h"	/* stack depth 9 */
extern "C"{
struct dirent
{
char d_name[260 ];
};
typedef struct
{
struct dirent *_d__dirent;
char *_d__wildcard;
unsigned long *_d__handle;
void *_d__ffd;
} DIR;
DIR *opendir(const char *);
struct dirent *readdir(DIR *);
void rewinddir(DIR *);
int closedir(DIR *);
}
/* #line 14	"extras.win32.h"	/* stack depth 8 */
/* #line 1	"startup.win32.h"	/* stack depth 9 */
/* #line 1	"ansi_parms.h"	/* stack depth 10 */
/* #line 9	"startup.win32.h"	/* stack depth 9 */
extern "C"{
extern int _doserrno;
int __cdecl __set_errno(unsigned long);
unsigned long __cdecl __dup_core(void *handle, void **dup_handle);
int * __cdecl __get_MSL_init_count(void);
}
/* #line 15	"extras.win32.h"	/* stack depth 8 */
/* #line 1	"wchar_t.h"	/* stack depth 9 */
/* #line 18	"extras.win32.h"	/* stack depth 8 */
extern "C"{
void __cdecl makepath(char*, const char*, const char*, const char*, const char *);
void __cdecl splitpath (const char *, char *, char *, char *, char *);
int __cdecl putenv(const char *);
int __cdecl GetHandle();
void __cdecl _makepath(char*, const char*, const char*, const char*, const char *);
void __cdecl _splitpath (const char *, char *, char *, char *, char *);
void __cdecl _searchenv(const char *, const char *, char*);
int __cdecl _chdrive(int );
long __cdecl _get_osfhandle(int );
int __cdecl _open_osfhandle(long , int );
int __cdecl _getdrive();
char * __cdecl _fullpath(char *, const char *, ::std::size_t );
int __cdecl _putenv(const char *);
wchar_t * __cdecl _ltow(unsigned long , wchar_t *, int) ;
wchar_t * __cdecl _ultow(unsigned long, wchar_t *, int) ;
}
/* #line 18	"extras.h"	/* stack depth 7 */
/* #line 1	"wchar_t.h"	/* stack depth 8 */
/* #line 22	"extras.h"	/* stack depth 7 */
extern "C"{
int __cdecl stricmp(const char *, const char *);
int __cdecl strnicmp(const char *, const char *, ::std::size_t );
int __cdecl strcmpi(const char *, const char *);
int __cdecl strncmpi(const char *, const char *, ::std::size_t );
int __cdecl strcasecmp (const char *, const char *);
int __cdecl strncasecmp(const char *, const char *, ::std::size_t );
char * __cdecl strset(char *, int );
char * __cdecl strnset(char *, int , ::std::size_t );
char * __cdecl strrev(char *);
char * __cdecl strupr(char *);
char * __cdecl strspnp(char *, const char *);
char * __cdecl strlwr (char *);
char * __cdecl strdate(char *str);
char * __cdecl strdup(const char *str);
int __cdecl stricoll(const char *, const char *);
int __cdecl strncoll(const char *, const char *, ::std::size_t );
int __cdecl strnicoll(const char *, const char *, ::std::size_t );
int __cdecl heapmin(void);
char * __cdecl itoa(int, char *, int);
int __cdecl filelength(int fileno);
char * __cdecl ultoa(unsigned long, char *, int);
int __cdecl chsize(int,long);
int __cdecl _stricmp(const char *, const char *);
int __cdecl _strnicmp(const char *, const char *, ::std::size_t );
int __cdecl _strcmpi(const char *, const char *);
int __cdecl _strncmpi(const char *, const char *, ::std::size_t );
int __cdecl _strcasecmp (const char *, const char *);
int __cdecl _strncasecmp(const char *, const char *, ::std::size_t );
char * __cdecl _strrev(char *);
char * __cdecl _strupr(char *);
char * __cdecl _strset(char *, int );
char * __cdecl _strnset(char *, int , ::std::size_t );
char * __cdecl _strspnp(char *, const char *);
char * __cdecl _strdate(char *str);
char * __cdecl _strdup(const char *str);
char * __cdecl _strlwr (char *);
int __cdecl _stricoll(const char *, const char *);
int __cdecl _strncoll(const char *, const char *, ::std::size_t );
int __cdecl _strnicoll(const char *, const char *, ::std::size_t );
int __cdecl _heapmin(void);
char * __cdecl _itoa(int, char *, int);
int __cdecl _filelength(int fileno);
char * __cdecl _ultoa(unsigned long, char *, int);
int __cdecl _chsize(int,long);
inline char* __cdecl ltoa(int x, char *y, int z) { return (itoa(x, y, z)); }
inline long __cdecl tell(int fildes) { return (lseek(fildes, 0L, 1 )); }
inline char* __cdecl _ltoa(int x, char *y, int z) { return (itoa(x, y, z)); }
inline long __cdecl _tell(int fildes) { return (lseek(fildes, 0L, 1 )); }
char * __cdecl gcvt(double, int, char *);
char * __cdecl _gcvt(double, int, char *);
wchar_t * __cdecl itow(int, wchar_t *, int);
int __cdecl wtoi(const wchar_t *_a);
int __cdecl wcsicmp(const wchar_t *s1, const wchar_t *s2);
int __cdecl wcsnicmp(const wchar_t *s1, const wchar_t *s2, ::std::size_t n);
wchar_t * __cdecl wstrrev(wchar_t * str);
wchar_t * __cdecl wcsrev(wchar_t *str);
wchar_t * __cdecl wcsupr(wchar_t *str);
wchar_t * __cdecl wcslwr(wchar_t *str);
wchar_t * __cdecl wcsset(wchar_t *str, wchar_t wc);
wchar_t * __cdecl wcsnset(wchar_t *str, wchar_t wc, ::std::size_t n);
wchar_t * __cdecl wcsspnp(const wchar_t *s1, const wchar_t *s2);
wchar_t * __cdecl wcsdup (const wchar_t *str);
int __cdecl wcsicoll(const wchar_t *, const wchar_t *);
int __cdecl wcsncoll(const wchar_t *, const wchar_t *, ::std::size_t );
int __cdecl wcsnicoll(const wchar_t *, const wchar_t *, ::std::size_t );
wchar_t * __cdecl _itow(int, wchar_t *, int);
int __cdecl _wtoi(const wchar_t *_a);
int __cdecl _wcsicmp(const wchar_t *s1, const wchar_t *s2);
int __cdecl _wcsnicmp(const wchar_t *s1, const wchar_t *s2, ::std::size_t n);
wchar_t * __cdecl _wstrrev(wchar_t * str);
wchar_t * __cdecl _wcsrev(wchar_t *str);
wchar_t * __cdecl _wcsupr(wchar_t *str);
wchar_t * __cdecl _wcslwr(wchar_t *str);
wchar_t * __cdecl _wcsset(wchar_t *str, wchar_t wc);
wchar_t * __cdecl _wcsnset(wchar_t *str, wchar_t wc, ::std::size_t n);
wchar_t * __cdecl _wcsspnp(const wchar_t *s1, const wchar_t *s2);
wchar_t * __cdecl _wcsdup (const wchar_t *str);
int __cdecl _wcsicoll(const wchar_t *, const wchar_t *);
int __cdecl _wcsncoll(const wchar_t *, const wchar_t *, ::std::size_t );
int __cdecl _wcsnicoll(const wchar_t *, const wchar_t *, ::std::size_t );
}
/* #line 28	"cstdlib"	/* stack depth 6 */
namespace std {
extern "C"{
double __cdecl atof(const char *);
double __cdecl strtod (const char *, char **);
long double __cdecl strtold(const char *, char **);
int __cdecl atoi(const char *);
long __cdecl atol(const char *);
long __cdecl strtol (const char * , char ** , int);
unsigned long __cdecl strtoul(const char * , char ** , int);
long long __cdecl strtoll (const char * , char ** , int);
unsigned long long __cdecl strtoull(const char * , char ** , int);
int __cdecl rand (void);
void __cdecl srand(unsigned int);
void * __cdecl calloc(size_t , size_t);
void __cdecl free(void *);
void * __cdecl malloc(size_t);
void * __cdecl realloc(void *, size_t);
size_t __cdecl __msize(void *);
void __cdecl abort(void);
int __cdecl atexit(void (__cdecl *func)(void));
void __cdecl exit(int status);
char * __cdecl getenv(const char *);
int __cdecl system(const char *);
typedef int (*_compare_function)(const void*, const void*);
void* __cdecl bsearch(const void*, const void*, size_t, size_t, _compare_function);
void __cdecl qsort(void*, size_t, size_t, _compare_function);
int __cdecl abs (int);
long __cdecl labs(long);
long long __cdecl llabs(long long);
div_t __cdecl div (int,int);
ldiv_t __cdecl ldiv(long,long);
lldiv_t __cdecl lldiv(long long,long long);
}
inline long __cdecl abs(long n)
{return labs(n);}
inline ldiv_t __cdecl div(long numerator, long denominator)
{return ldiv(numerator, denominator);}
inline long long __cdecl abs(long long n)
{return llabs(n);}
inline lldiv_t __cdecl div(long long numerator, long long denominator)
{return lldiv(numerator, denominator);}
extern "C"{
int __cdecl mblen(const char *, size_t);
int __cdecl mbtowc(wchar_t *, const char *, size_t);
int __cdecl wctomb(char *, wchar_t);
size_t __cdecl mbstowcs(wchar_t *, const char * , size_t);
size_t __cdecl wcstombs(char *, const wchar_t *, size_t);
}
}
/* #line 14	"fwd.hpp"	/* stack depth 5 */
/* #line 1	"cstddef"	/* stack depth 6 */
/* #line 1	"ansi_parms.h"	/* stack depth 7 */
/* #line 11	"cstddef"	/* stack depth 6 */
namespace std {
extern "C"{
typedef __typeof__((char*)0-(char*)0) ptrdiff_t;
}
}
/* #line 1	"size_t.h"	/* stack depth 7 */
/* #line 29	"cstddef"	/* stack depth 6 */
/* #line 1	"wchar_t.h"	/* stack depth 7 */
/* #line 30	"cstddef"	/* stack depth 6 */
/* #line 1	"null.h"	/* stack depth 7 */
/* #line 31	"cstddef"	/* stack depth 6 */
/* #line 15	"fwd.hpp"	/* stack depth 5 */
namespace boost{
template <class From, class To>
struct is_convertible;
template <class T>
struct alignment_of;
template <class T>
struct is_void;
template <class T>
struct is_integral;
template <class T>
struct is_float;
template <class T>
struct is_arithmetic;
template <class T>
struct is_fundamental;
template <class T>
struct is_const;
template <class T>
struct is_volatile;
template <class T>
struct remove_const;
template <class T>
struct remove_volatile;
template <class T>
struct remove_cv;
template <class T>
struct add_const;
template <class T>
struct add_volatile;
template <class T>
struct add_cv;
template <class T>
struct is_array;
template <class T>
struct is_pointer;
template <class T>
struct is_reference;
template <class T>
struct is_member_pointer;
template <class T>
struct is_member_function_pointer;
template <class T>
struct is_enum;
template <class T>
struct is_union;
template <class T>
struct is_object;
template <class T>
struct is_scalar;
template <class T>
struct is_class;
template <class T>
struct is_compound;
template <class T>
struct is_POD;
template <class T>
struct has_trivial_constructor;
template <class T>
struct has_trivial_copy;
template <class T>
struct has_trivial_assign;
template <class T>
struct has_trivial_destructor;
template <class T>
struct has_nothrow_constructor;
template <class T>
struct has_nothrow_copy;
template <class T>
struct has_nothrow_assign;
template <class T>
struct is_empty;
template <class Base, class Derived>
struct is_base_and_derived;
template <class T>
struct remove_reference;
template <class T>
struct add_reference;
template <class T>
struct remove_bounds;
template <class T>
struct remove_pointer;
template <class T>
struct add_pointer;
template <class T, class U>
struct is_same;
}
/* #line 21	"same_traits.hpp"	/* stack depth 4 */
namespace boost{
template <typename T, typename U>
struct is_same
{ static const bool value = false ; };
template <typename T>
struct is_same<T, T>
{ static const bool value = true ; };
template <typename T, typename U>
const bool is_same<T, U>::value;
template <typename T>
const bool is_same<T, T>::value;
}
/* #line 24	"count_if_not.hpp"	/* stack depth 3 */
/* #line 35	"impl.hpp"	/* stack depth 2 */
/* #line 1	"none.hpp"	/* stack depth 3 */
/* #line 36	"impl.hpp"	/* stack depth 2 */
/* #line 1	"params.hpp"	/* stack depth 3 */
/* #line 37	"impl.hpp"	/* stack depth 2 */
/* #line 1	"default_params.hpp"	/* stack depth 3 */
/* #line 38	"impl.hpp"	/* stack depth 2 */
/* #line 1	"repeat_2nd.hpp"	/* stack depth 3 */
/* #line 40	"impl.hpp"	/* stack depth 2 */
/* #line 1	"if.hpp"	/* stack depth 3 */
/* #line 41	"impl.hpp"	/* stack depth 2 */
namespace boost {
namespace mpl {
namespace aux {
template< long > struct list_impl_chooser;
}
namespace aux { template<> struct list_impl_chooser<0> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list0 type; }; }; } namespace aux { template<> struct list_impl_chooser<1> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list1< T0 > type; }; }; } namespace aux { template<> struct list_impl_chooser<2> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list2< T0 , T1 > type; }; }; } namespace aux { template<> struct list_impl_chooser<3> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list3< T0 , T1 , T2 > type; }; }; } namespace aux { template<> struct list_impl_chooser<4> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list4< T0 , T1 , T2 , T3 > type; }; }; } namespace aux { template<> struct list_impl_chooser<5> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list5< T0 , T1 , T2 , T3 , T4 > type; }; }; } namespace aux { template<> struct list_impl_chooser<6> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list6< T0 , T1 , T2 , T3 , T4 , T5 > type; }; }; } namespace aux { template<> struct list_impl_chooser<7> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list7< T0 , T1 , T2 , T3 , T4 , T5 , T6 > type; }; }; } namespace aux { template<> struct list_impl_chooser<8> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list8< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 > type; }; }; } namespace aux { template<> struct list_impl_chooser<9> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list9< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 > type; }; }; } namespace aux { template<> struct list_impl_chooser<10> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list10< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 > type; }; }; } namespace aux { template<> struct list_impl_chooser<11> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list11< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 > type; }; }; } namespace aux { template<> struct list_impl_chooser<12> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list12< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 > type; }; }; } namespace aux { template<> struct list_impl_chooser<13> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list13< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 > type; }; }; } namespace aux { template<> struct list_impl_chooser<14> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list14< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 > type; }; }; } namespace aux { template<> struct list_impl_chooser<15> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list15< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 > type; }; }; } namespace aux { template<> struct list_impl_chooser<16> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list16< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 > type; }; }; } namespace aux { template<> struct list_impl_chooser<17> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list17< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 > type; }; }; } namespace aux { template<> struct list_impl_chooser<18> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list18< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 > type; }; }; } namespace aux { template<> struct list_impl_chooser<19> { template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 > struct result_ { typedef list19< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 > type; }; }; }
namespace aux { template< typename T , typename U0 = T , typename U1 = T , typename U2 = T , typename U3 = T , typename U4 = T , typename U5 = T , typename U6 = T , typename U7 = T , typename U8 = T , typename U9 = T , typename U10 = T , typename U11 = T , typename U12 = T , typename U13 = T , typename U14 = T , typename U15 = T , typename U16 = T , typename U17 = T , typename U18 = T , typename U19 = T > struct list_count_if_not { static const long value = !::boost::is_same<T, U0>::value + !::boost::is_same<T, U1>::value + !::boost::is_same<T, U2>::value + !::boost::is_same<T, U3>::value + !::boost::is_same<T, U4>::value + !::boost::is_same<T, U5>::value + !::boost::is_same<T, U6>::value + !::boost::is_same<T, U7>::value + !::boost::is_same<T, U8>::value + !::boost::is_same<T, U9>::value + !::boost::is_same<T, U10>::value + !::boost::is_same<T, U11>::value + !::boost::is_same<T, U12>::value + !::boost::is_same<T, U13>::value + !::boost::is_same<T, U14>::value + !::boost::is_same<T, U15>::value + !::boost::is_same<T, U16>::value + !::boost::is_same<T, U17>::value + !::boost::is_same<T, U18>::value + !::boost::is_same<T, U19>::value; }; }
}
}
/* #line 26	"list_c.hpp"	/* stack depth 1 */
/* #line 1	"list.hpp"	/* stack depth 2 */
/* #line 27	"list_c.hpp"	/* stack depth 1 */
/* #line 1	"params.hpp"	/* stack depth 2 */
/* #line 28	"list_c.hpp"	/* stack depth 1 */
/* #line 1	"default_params.hpp"	/* stack depth 2 */
/* #line 29	"list_c.hpp"	/* stack depth 1 */
/* #line 1	"enum.hpp"	/* stack depth 2 */
/* #line 30	"list_c.hpp"	/* stack depth 1 */
/* #line 1	"elem.hpp"	/* stack depth 2 */
/* #line 31	"list_c.hpp"	/* stack depth 1 */
/* #line 1	"climits"	/* stack depth 2 */
/* #line 32	"list_c.hpp"	/* stack depth 1 */
namespace aux {
template< typename T, unsigned long C0 , unsigned long C1 , unsigned long C2 , unsigned long C3 , unsigned long C4 , unsigned long C5 , unsigned long C6 , unsigned long C7 , unsigned long C8 , unsigned long C9 , unsigned long C10 , unsigned long C11 , unsigned long C12 , unsigned long C13 , unsigned long C14 , unsigned long C15 , unsigned long C16 , unsigned long C17 , unsigned long C18 , unsigned long C19 >
struct list_c_impl
{
typedef aux::list_count_if_not<
integral_c<unsigned long,-1>
, integral_c< unsigned long , C0 > , integral_c< unsigned long , C1 > , integral_c< unsigned long , C2 > , integral_c< unsigned long , C3 > , integral_c< unsigned long , C4 > , integral_c< unsigned long , C5 > , integral_c< unsigned long , C6 > , integral_c< unsigned long , C7 > , integral_c< unsigned long , C8 > , integral_c< unsigned long , C9 > , integral_c< unsigned long , C10 > , integral_c< unsigned long , C11 > , integral_c< unsigned long , C12 > , integral_c< unsigned long , C13 > , integral_c< unsigned long , C14 > , integral_c< unsigned long , C15 > , integral_c< unsigned long , C16 > , integral_c< unsigned long , C17 > , integral_c< unsigned long , C18 > , integral_c< unsigned long , C19 >
> arg_num_;
typedef typename aux::list_impl_chooser< arg_num_::value >
::template result_< integral_c< T , C0 > , integral_c< T , C1 > , integral_c< T , C2 > , integral_c< T , C3 > , integral_c< T , C4 > , integral_c< T , C5 > , integral_c< T , C6 > , integral_c< T , C7 > , integral_c< T , C8 > , integral_c< T , C9 > , integral_c< T , C10 > , integral_c< T , C11 > , integral_c< T , C12 > , integral_c< T , C13 > , integral_c< T , C14 > , integral_c< T , C15 > , integral_c< T , C16 > , integral_c< T , C17 > , integral_c< T , C18 > , integral_c< T , C19 > >::type type;
};
}
template< typename T, unsigned long C0 = 0xffffffffUL , unsigned long C1 = 0xffffffffUL , unsigned long C2 = 0xffffffffUL , unsigned long C3 = 0xffffffffUL , unsigned long C4 = 0xffffffffUL , unsigned long C5 = 0xffffffffUL , unsigned long C6 = 0xffffffffUL , unsigned long C7 = 0xffffffffUL , unsigned long C8 = 0xffffffffUL , unsigned long C9 = 0xffffffffUL , unsigned long C10 = 0xffffffffUL , unsigned long C11 = 0xffffffffUL , unsigned long C12 = 0xffffffffUL , unsigned long C13 = 0xffffffffUL , unsigned long C14 = 0xffffffffUL , unsigned long C15 = 0xffffffffUL , unsigned long C16 = 0xffffffffUL , unsigned long C17 = 0xffffffffUL , unsigned long C18 = 0xffffffffUL , unsigned long C19 = 0xffffffffUL >
struct list_c
: aux::list_c_impl< T, C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7 , C8 , C9 , C10 , C11 , C12 , C13 , C14 , C15 , C16 , C17 , C18 , C19 >::type
{
typedef typename aux::list_c_impl<
T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19
>::type type;
};
}
}
/* #line 17	"list_c.cpp"	/* stack depth 0 */
namespace mpl = boost::mpl;
int main()
{
typedef list_c<bool, true> lt;
typedef list_c<bool, false> lf;
return 0;
}
