// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2011 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2011 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2011 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIDE_HPP


#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace side
{

namespace services
{

/*!
\brief Traits class binding a side determination strategy to a coordinate system
\ingroup util
\tparam Tag tag of coordinate system of point-type
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CalculationType = void>
struct default_strategy
{
    typedef strategy::not_implemented type;
};


} // namespace services


}} // namespace strategy::side


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIDE_HPP
