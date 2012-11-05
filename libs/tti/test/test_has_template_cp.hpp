
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_HAS_TEMPLATE_CHECK_PARAMS_HPP)
#define TEST_HAS_TEMPLATE_CHECK_PARAMS_HPP

#include "test_structs.hpp"

#if defined(BOOST_TTI_VERSION_1_6)

#include <boost/tti/has_template.hpp>

BOOST_TTI_HAS_TEMPLATE(ATPMemberTemplate,(1,(class)))
BOOST_TTI_TRAIT_HAS_TEMPLATE(HaveCL,CLMemberTemplate,(2,(class,class)))
BOOST_TTI_HAS_TEMPLATE(AMemberTemplate,(1,(int)))
BOOST_TTI_TRAIT_HAS_TEMPLATE(HaveAnotherMT,AnotherMemberTemplate,(2,(int,int)))
BOOST_TTI_HAS_TEMPLATE(SomeMemberTemplate,(6,(class,class,class,class,class,class)))
BOOST_TTI_TRAIT_HAS_TEMPLATE(ATemplateWithParms,ManyParameters,(7,(class,class,int,class,template <class> class,class,long)))
BOOST_TTI_HAS_TEMPLATE(SimpleTMP,(4,(class,class,class,class)))
BOOST_TTI_HAS_TEMPLATE(TemplateNotExist,(3,(int,class,template <class> class ATemplate)))
BOOST_TTI_TRAIT_HAS_TEMPLATE(WrongParametersForMP,ManyParameters,(8,(class,class,int,class,template <class,class> class InnerTemplate,class,long)))
BOOST_TTI_TRAIT_HAS_TEMPLATE(WrongParameters2ForMP,ManyParameters,(7,(class,long,int,class,template <class> class InnerTemplate,class,long)))

#else // !BOOST_TTI_VERSION_1_6

#include <boost/tti/has_template_check_params.hpp>

BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(ATPMemberTemplate,(class))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(HaveCL,CLMemberTemplate,(class)(class))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(AMemberTemplate,(int))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(HaveAnotherMT,AnotherMemberTemplate,(int)(int))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(SomeMemberTemplate,(class)(class)(class)(class)(class)(class))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(ATemplateWithParms,ManyParameters,(class)(class)(int)(class)(template <class> class)(class)(long))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(SimpleTMP,(class)(class)(class)(class))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(TemplateNotExist,(int)(class)(template <class> class ATemplate))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(WrongParametersForMP,ManyParameters,(class)(class)(int)(class)(template <class)(class> class InnerTemplate)(class)(long))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(WrongParameters2ForMP,ManyParameters,(class)(long)(int)(class)(template <class> class InnerTemplate)(class)(long))

#endif // BOOST_TTI_VERSION_1_6

#endif // TEST_HAS_TEMPLATE_CHECK_PARAMS_HPP
