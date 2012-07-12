//  (C) Copyright 2009-2011 Frederic Bron.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_integral_constant.hpp"

#include <boost/type_traits/has_operator.hpp>
#include "has_binary_classes.hpp"

TT_TEST_BEGIN(BOOST_TT_TRAIT_NAME)
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const, C014, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const, C014 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const, C014 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const, C014 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const, C014 const &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const, C014 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014 const &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 &, C014 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 const, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 const &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C014 const &, C014 const &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015, C015, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015, C015, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015, C015 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015, C015 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015, C015 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const, C015, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const, C015, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const, C015 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const, C015 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const, C015 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const, C015 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const, C015 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 &, C015, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 &, C015, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 &, C015 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 &, C015 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 &, C015 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const &, C015, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const &, C015 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const &, C015 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const &, C015 const &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C015 const &, C015 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036, C036, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036, C036 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036, C036 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036, C036 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036, C036 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036, C036 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036, C036 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const, C036, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const, C036, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const, C036 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const, C036 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const, C036 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const, C036 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 &, C036, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 &, C036, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 &, C036 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 &, C036 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 &, C036 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 &, C036 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 &, C036 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 &, C036 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036 &, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036 &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C036 const &, C036 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037, C037 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const, C037 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 &, C037, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 &, C037, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 &, C037, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 &, C037, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 &, C037 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 &, C037 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 &, C037 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 &, C037 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const &, C037, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const &, C037, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const &, C037 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const &, C037 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const &, C037 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C037 const &, C037 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038, C038 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const, C038 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 &, C038, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 &, C038, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 &, C038 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 &, C038 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 &, C038 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 &, C038 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 &, C038 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const &, C038, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const &, C038, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const &, C038, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C038 const &, C038 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041, C041, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041, C041 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041, C041 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041, C041 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041, C041 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041, C041 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041, C041 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const, C041, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const, C041 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const, C041 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const, C041 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const, C041 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const, C041 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const, C041 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 &, C041 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 &, C041 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 &, C041 &, ret & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 &, C041 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 &, C041 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C041 const &, C041 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042 &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042, C042 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const, C042, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const, C042, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const, C042, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const, C042 const, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const, C042 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const, C042 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const, C042 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 &, C042, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 &, C042 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 &, C042 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 &, C042 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 &, C042 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 &, C042 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042 &, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042 const &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C042 const &, C042 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045, C045 &, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045, C045 &, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045, C045 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045 &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045 &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045 const &, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const, C045 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 &, C045, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 &, C045, ret >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 &, C045, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 &, C045, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 &, C045 const, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 &, C045 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 &, C045 &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 &, C045 const &, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const &, C045 const, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const &, C045 const, ret const >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const &, C045 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const &, C045 const, ret const & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C045 const &, C045 const &, void >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046, C046 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046, C046 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046, C046 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const, C046, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const, C046 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const, C046 const, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const, C046 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const, C046 &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const, C046 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const, C046 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 &, C046 const, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 &, C046 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 &, C046 const &, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 &, C046 const &, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 &, C046 const &, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const &, C046, void >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const &, C046, ret const >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const &, C046 const, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const &, C046 const, ret & >::value), 0);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const &, C046 const, ret const & >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const &, C046 &, ret >::value), 1);
   BOOST_CHECK_INTEGRAL_CONSTANT((::boost::has_plus< C046 const &, C046 &, ret const >::value), 1);
TT_TEST_END
