#ifndef BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP

// Boost.Geometry - extensions-gis-projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Original copyright notice:
 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry { namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace vandg2{ 
            static const double TOL = 1e-10;
            static const double TWORPI = 0.63661977236758134308;

            struct par_vandg2
            {
                int    vdg3;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_vandg2_spheroid : public base_t_f<base_vandg2_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_vandg2 m_proj_parm;

                inline base_vandg2_spheroid(const Parameters& par)
                    : base_t_f<base_vandg2_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double x1, at, bt, ct;
                
                    bt = fabs(TWORPI * lp_lat);
                    if ((ct = 1. - bt * bt) < 0.)
                        ct = 0.;
                    else
                        ct = sqrt(ct);
                    if (fabs(lp_lon) < TOL) {
                        xy_x = 0.;
                        xy_y = PI * (lp_lat < 0. ? -bt : bt) / (1. + ct);
                    } else {
                        at = 0.5 * fabs(PI / lp_lon - lp_lon / PI);
                        if (this->m_proj_parm.vdg3) {
                            x1 = bt / (1. + ct);
                            xy_x = PI * (sqrt(at * at + 1. - x1 * x1) - at);
                            xy_y = PI * x1;
                        } else {
                            x1 = (ct * sqrt(1. + at * at) - at * ct * ct) /
                                (1. + at * at * bt * bt);
                            xy_x = PI * x1;
                            xy_y = PI * sqrt(1. - x1 * (x1 + 2. * at) + TOL);
                        }
                        if ( lp_lon < 0.) xy_x = -xy_x;
                        if ( lp_lat < 0.) xy_y = -xy_y;
                    }
                }
            };

            // van der Grinten II
            template <typename Parameters>
            void setup_vandg2(Parameters& par, par_vandg2& proj_parm)
            {
                proj_parm.vdg3 = 0;
                // par.inv = 0;
                // par.fwd = s_forward;
            }

            // van der Grinten III
            template <typename Parameters>
            void setup_vandg3(Parameters& par, par_vandg2& proj_parm)
            {
                proj_parm.vdg3 = 1;
                par.es = 0.;
                // par.fwd = s_forward;
            }

        }} // namespace detail::vandg2
    #endif // doxygen 

    /*!
        \brief van der Grinten II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_vandg2.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct vandg2_spheroid : public detail::vandg2::base_vandg2_spheroid<Geographic, Cartesian, Parameters>
    {
        inline vandg2_spheroid(const Parameters& par) : detail::vandg2::base_vandg2_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::vandg2::setup_vandg2(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief van der Grinten III projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_vandg3.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct vandg3_spheroid : public detail::vandg2::base_vandg2_spheroid<Geographic, Cartesian, Parameters>
    {
        inline vandg3_spheroid(const Parameters& par) : detail::vandg2::base_vandg2_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::vandg2::setup_vandg3(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class vandg2_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_f<vandg2_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class vandg3_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_f<vandg3_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void vandg2_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("vandg2", new vandg2_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("vandg3", new vandg3_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail 
    #endif // doxygen

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP

