#ifndef BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP

// Boost.Geometry - extensions-gis-projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright (c) 2008-2011 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels (Geodan, Amsterdam)

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
#include <boost/geometry/extensions/gis/projections/impl/proj_mdist.hpp>

namespace boost { namespace geometry { namespace projection
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace rouss{

            struct par_rouss
            {
                double s0;
                double A1, A2, A3, A4, A5, A6;
                double B1, B2, B3, B4, B5, B6, B7, B8;
                double C1, C2, C3, C4, C5, C6, C7, C8;
                double D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11;
                MDIST en;
            };

            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_rouss_ellipsoid : public base_t_fi<base_rouss_ellipsoid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;

                par_rouss m_proj_parm;

                inline base_rouss_ellipsoid(const Parameters& par)
                    : base_t_fi<base_rouss_ellipsoid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    double s, al, cp, sp, al2, s2;

                    cp = cos(lp_lat);
                    sp = sin(lp_lat);
                    s = proj_mdist(lp_lat, sp, cp,  this->m_proj_parm.en) - this->m_proj_parm.s0;
                    s2 = s * s;
                    al = lp_lon * cp / sqrt(1. - this->m_par.es * sp * sp);
                    al2 = al * al;
                    xy_x = this->m_par.k0 * al*(1.+s2*(this->m_proj_parm.A1+s2*this->m_proj_parm.A4)-al2*(this->m_proj_parm.A2+s*this->m_proj_parm.A3+s2*this->m_proj_parm.A5
                                +al2*this->m_proj_parm.A6));
                    xy_y = this->m_par.k0 * (al2*(this->m_proj_parm.B1+al2*this->m_proj_parm.B4)+
                        s*(1.+al2*(this->m_proj_parm.B3-al2*this->m_proj_parm.B6)+s2*(this->m_proj_parm.B2+s2*this->m_proj_parm.B8)+
                        s*al2*(this->m_proj_parm.B5+s*this->m_proj_parm.B7)));
                }

                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                    double s, al, x = xy_x / this->m_par.k0, y = xy_y / this->m_par.k0, x2, y2;;

                    x2 = x * x;
                    y2 = y * y;
                    al = x*(1.-this->m_proj_parm.C1*y2+x2*(this->m_proj_parm.C2+this->m_proj_parm.C3*y-this->m_proj_parm.C4*x2+this->m_proj_parm.C5*y2-this->m_proj_parm.C7*x2*y)
                        +y2*(this->m_proj_parm.C6*y2-this->m_proj_parm.C8*x2*y));
                    s = this->m_proj_parm.s0 + y*(1.+y2*(-this->m_proj_parm.D2+this->m_proj_parm.D8*y2))+
                        x2*(-this->m_proj_parm.D1+y*(-this->m_proj_parm.D3+y*(-this->m_proj_parm.D5+y*(-this->m_proj_parm.D7+y*this->m_proj_parm.D11)))+
                        x2*(this->m_proj_parm.D4+y*(this->m_proj_parm.D6+y*this->m_proj_parm.D10)-x2*this->m_proj_parm.D9));
                    lp_lat=proj_inv_mdist(s, this->m_proj_parm.en);
                    s = sin(lp_lat);
                    lp_lon=al * sqrt(1. - this->m_par.es * s * s)/cos(lp_lat);
                }
            };

            // Roussilhe Stereographic
            template <typename Parameters>
            void setup_rouss(Parameters& par, par_rouss& proj_parm)
            {
                double N0, es2, t, t2, R_R0_2, R_R0_4;
                proj_mdist_ini(par.es, proj_parm.en);

                es2 = sin(par.phi0);
                proj_parm.s0 = proj_mdist(par.phi0, es2, cos(par.phi0), proj_parm.en);
                t = 1. - (es2 = par.es * es2 * es2);
                N0 = 1./sqrt(t);
                R_R0_2 = t * t / par.one_es;
                R_R0_4 = R_R0_2 * R_R0_2;
                t = tan(par.phi0);
                t2 = t * t;
                proj_parm.C1 = proj_parm.A1 = R_R0_2 / 4.;
                proj_parm.C2 = proj_parm.A2 = R_R0_2 * (2 * t2 - 1. - 2. * es2) / 12.;
                proj_parm.A3 = R_R0_2 * t * (1. + 4. * t2)/ ( 12. * N0);
                proj_parm.A4 = R_R0_4 / 24.;
                proj_parm.A5 = R_R0_4 * ( -1. + t2 * (11. + 12. * t2))/24.;
                proj_parm.A6 = R_R0_4 * ( -2. + t2 * (11. - 2. * t2))/240.;
                proj_parm.B1 = t / (2. * N0);
                proj_parm.B2 = R_R0_2 / 12.;
                proj_parm.B3 = R_R0_2 * (1. + 2. * t2 - 2. * es2)/4.;
                proj_parm.B4 = R_R0_2 * t * (2. - t2)/(24. * N0);
                proj_parm.B5 = R_R0_2 * t * (5. + 4.* t2)/(8. * N0);
                proj_parm.B6 = R_R0_4 * (-2. + t2 * (-5. + 6. * t2))/48.;
                proj_parm.B7 = R_R0_4 * (5. + t2 * (19. + 12. * t2))/24.;
                proj_parm.B8 = R_R0_4 / 120.;
                proj_parm.C3 = R_R0_2 * t * (1. + t2)/(3. * N0);
                proj_parm.C4 = R_R0_4 * (-3. + t2 * (34. + 22. * t2))/240.;
                proj_parm.C5 = R_R0_4 * (4. + t2 * (13. + 12. * t2))/24.;
                proj_parm.C6 = R_R0_4 / 16.;
                proj_parm.C7 = R_R0_4 * t * (11. + t2 * (33. + t2 * 16.))/(48. * N0);
                proj_parm.C8 = R_R0_4 * t * (1. + t2 * 4.)/(36. * N0);
                proj_parm.D1 = t / (2. * N0);
                proj_parm.D2 = R_R0_2 / 12.;
                proj_parm.D3 = R_R0_2 * (2 * t2 + 1. - 2. * es2) / 4.;
                proj_parm.D4 = R_R0_2 * t * (1. + t2)/(8. * N0);
                proj_parm.D5 = R_R0_2 * t * (1. + t2 * 2.)/(4. * N0);
                proj_parm.D6 = R_R0_4 * (1. + t2 * (6. + t2 * 6.))/16.;
                proj_parm.D7 = R_R0_4 * t2 * (3. + t2 * 4.)/8.;
                proj_parm.D8 = R_R0_4 / 80.;
                proj_parm.D9 = R_R0_4 * t * (-21. + t2 * (178. - t2 * 26.))/720.;
                proj_parm.D10 = R_R0_4 * t * (29. + t2 * (86. + t2 * 48.))/(96. * N0);
                proj_parm.D11 = R_R0_4 * t * (37. + t2 * 44.)/(96. * N0);
                // par.fwd = e_forward;
                // par.inv = e_inverse;
            }

        }} // namespace detail::rouss
    #endif // doxygen

    /*!
        \brief Roussilhe Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Ellps
        \par Example
        \image html ex_rouss.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct rouss_ellipsoid : public detail::rouss::base_rouss_ellipsoid<Geographic, Cartesian, Parameters>
    {
        inline rouss_ellipsoid(const Parameters& par) : detail::rouss::base_rouss_ellipsoid<Geographic, Cartesian, Parameters>(par)
        {
            detail::rouss::setup_rouss(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class rouss_entry : public detail::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<rouss_ellipsoid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void rouss_init(detail::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("rouss", new rouss_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

}}} // namespace boost::geometry::projection

#endif // BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP

