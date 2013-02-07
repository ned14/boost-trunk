/*
    Copyright 2012 Chung-Lin Wen, Davide Anastasia
    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/

/*************************************************************************************************/

#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_XYZ_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_XYZ_HPP

////////////////////////////////////////////////////////////////////////////////////////
/// \file xyz.hpp
/// \brief Support for CIE XYZ color space
/// \author Chung-Lin Wen, Davide Anastasia \n
///
/// \date 2012 \n
///
////////////////////////////////////////////////////////////////////////////////////////

#include <boost/cast.hpp>

namespace boost{ namespace gil {

/// \addtogroup ColorNameModel
/// \{
namespace xyz_color_space
{
/// \brief x Color Component
struct x_t {};    
/// \brief y Color Component
struct y_t {};
/// \brief z Color Component
struct z_t {}; 
}
/// \}

/// \ingroup ColorSpaceModel
typedef mpl::vector3< xyz_color_space::x_t
                    , xyz_color_space::y_t
                    , xyz_color_space::z_t
                    > xyz_t;

/// \ingroup LayoutModel
typedef layout<xyz_t> xyz_layout_t;

GIL_DEFINE_ALL_TYPEDEFS( 32f, xyz );

/// \ingroup ColorConvert
/// \brief RGB to XYZ
/// <a href="http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html">Link</a> 
/// \note rgb_t is assumed to be sRGB D65
template <>
struct default_color_converter_impl< rgb_t, xyz_t >
{
private:
    GIL_FORCEINLINE
    bits32f inverse_companding(bits32f sample) const
    {
        if ( sample > 0.04045f )
        {
            return powf((( sample + 0.055f ) / 1.055f ), 2.4f);
        }
        else
        {
            return ( sample / 12.92f );
        }
    }

public:
    template <typename P1, typename P2>
    void operator()( const P1& src, P2& dst ) const
    {
        using namespace xyz_color_space;

        bits32f red(
                    inverse_companding(
                        channel_convert<bits32f>( get_color( src, red_t() ))
                        )
                    );
        bits32f green(
                    inverse_companding(
                        channel_convert<bits32f>( get_color( src, green_t() ))
                        )
                    );
        bits32f blue(
                    inverse_companding(
                        channel_convert<bits32f>( get_color( src, blue_t() ))
                        )
                    );

        get_color( dst, x_t() ) =
                red * 0.4124564f +
                green * 0.3575761f +
                blue * 0.1804375f;
        get_color( dst, y_t() ) =
                red * 0.2126729f +
                green * 0.7151522f +
                blue * 0.0721750f;
        get_color( dst, z_t() ) =
                red * 0.0193339f +
                green * 0.1191920f +
                blue * 0.9503041f;
    }
};

/// \ingroup ColorConvert
/// \brief XYZ to RGB
template <>
struct default_color_converter_impl<xyz_t,rgb_t>
{
private:
    GIL_FORCEINLINE
    bits32f companding(bits32f sample) const
    {
        if ( sample > 0.0031308f )
        {
            return ( 1.055f * powf( sample, 1.f/2.4f ) - 0.055f );
        }
        else
        {
            return ( 12.92f * sample );
        }
    }

public:
    template <typename P1, typename P2>
    void operator()( const P1& src, P2& dst) const
    {
        using namespace xyz_color_space;

        // Note: ideally channel_convert should be compiled out, because xyz_t
        // is bits32f natively only
        bits32f x( channel_convert<bits32f>( get_color( src, x_t() ) ) );
        bits32f y( channel_convert<bits32f>( get_color( src, y_t() ) ) );
        bits32f z( channel_convert<bits32f>( get_color( src, z_t() ) ) );

        get_color(dst,red_t())  =
                channel_convert<typename color_element_type<P2, red_t>::type>(
                    companding( x *  3.2404542f +
                                y * -1.5371385f +
                                z * -0.4985314f )
                    );
        get_color(dst,green_t()) =
                channel_convert<typename color_element_type<P2, green_t>::type>(
                    companding( x * -0.9692660f +
                                y *  1.8760108f +
                                z *  0.0415560f )
                    );
        get_color(dst,blue_t()) =
                channel_convert<typename color_element_type<P2, blue_t>::type>(
                    companding( x *  0.0556434f +
                                y * -0.2040259f +
                                z *  1.0572252f )
                    );
    }
};

} // namespace gil
} // namespace boost

#endif // BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_XYZ_HPP
