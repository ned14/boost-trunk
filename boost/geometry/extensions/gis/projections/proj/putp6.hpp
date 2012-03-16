#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP6_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP6_HPP

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

#include <boost/concept_check.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/extensions/gis/projections/impl/base_static.hpp>
#include <boost/geometry/extensions/gis/projections/impl/base_dynamic.hpp>
#include <boost/geometry/extensions/gis/projections/impl/projects.hpp>
#include <boost/geometry/extensions/gis/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry { namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace putp6{ 
            static const double EPS = 1e-10;
            static const int NITER = 10;
            static const double CON_POLE = 1.732050807568877;

            struct par_putp6
            {
                double C_x, C_y, A, B, D;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_putp6_spheroid : public base_t_fi<base_putp6_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_putp6 m_proj_parm;

                inline base_putp6_spheroid(const Parameters& par)
                    : base_t_fi<base_putp6_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double p, r, V;
                    int i;
                
                    p = this->m_proj_parm.B * sin(lp_lat);
                    lp_lat *=  1.10265779;
                    for (i = NITER; i ; --i) {
                        r = sqrt(1. + lp_lat * lp_lat);
                        lp_lat -= V = ( (this->m_proj_parm.A - r) * lp_lat - log(lp_lat + r) - p ) /
                            (this->m_proj_parm.A - 2. * r);
                        if (fabs(V) < EPS)
                            break;
                    }
                    if (!i)
                        lp_lat = p < 0. ? -CON_POLE : CON_POLE;
                    xy_x = this->m_proj_parm.C_x * lp_lon * (this->m_proj_parm.D - sqrt(1. + lp_lat * lp_lat));
                    xy_y = this->m_proj_parm.C_y * lp_lat;
                }

                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                    double r;
                
                    lp_lat = xy_y / this->m_proj_parm.C_y;
                    r = sqrt(1. + lp_lat * lp_lat);
                    lp_lon = xy_x / (this->m_proj_parm.C_x * (this->m_proj_parm.D - r));
                    lp_lat = aasin( ( (this->m_proj_parm.A - r) * lp_lat - log(lp_lat + r) ) / this->m_proj_parm.B);
                }
            };

            template <typename Parameters>
            void setup(Parameters& par, par_putp6& proj_parm) 
            {
                boost::ignore_unused_variable_warning(par);
                boost::ignore_unused_variable_warning(proj_parm);
                par.es = 0.;
                // par.inv = s_inverse;
                // par.fwd = s_forward;
            }


            // Putnins P6
            template <typename Parameters>
            void setup_putp6(Parameters& par, par_putp6& proj_parm)
            {
                proj_parm.C_x = 1.01346;
                proj_parm.C_y = 0.91910;
                proj_parm.A   = 4.;
                proj_parm.B   = 2.1471437182129378784;
                proj_parm.D   = 2.;
                setup(par, proj_parm);
            }

            // Putnins P6'
            template <typename Parameters>
            void setup_putp6p(Parameters& par, par_putp6& proj_parm)
            {
                proj_parm.C_x = 0.44329;
                proj_parm.C_y = 0.80404;
                proj_parm.A   = 6.;
                proj_parm.B   = 5.61125;
                proj_parm.D   = 3.;
                setup(par, proj_parm);
            }

        }} // namespace detail::putp6
    #endif // doxygen 

    /*!
        \brief Putnins P6 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp6.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct putp6_spheroid : public detail::putp6::base_putp6_spheroid<Geographic, Cartesian, Parameters>
    {
        inline putp6_spheroid(const Parameters& par) : detail::putp6::base_putp6_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::putp6::setup_putp6(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief Putnins P6' projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp6p.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct putp6p_spheroid : public detail::putp6::base_putp6_spheroid<Geographic, Cartesian, Parameters>
    {
        inline putp6p_spheroid(const Parameters& par) : detail::putp6::base_putp6_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            detail::putp6::setup_putp6p(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class putp6_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<putp6_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        class putp6p_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<putp6p_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void putp6_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("putp6", new putp6_entry<Geographic, Cartesian, Parameters>);
            factory.add_to_factory("putp6p", new putp6p_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail 
    #endif // doxygen

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP6_HPP

