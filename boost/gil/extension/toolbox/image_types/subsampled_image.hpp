/*
    Copyright 2013 Christian Henning
    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/

/*************************************************************************************************/

#ifndef BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_SUBSAMPLED_IMAGE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_SUBSAMPLED_IMAGE_HPP

////////////////////////////////////////////////////////////////////////////////////////
/// \file subsampled_image.hpp
/// \brief Subsampled Image extension
/// \author Christian Henning \n
///
/// \date 2013 \n
///
////////////////////////////////////////////////////////////////////////////////////////

#include <boost/gil/image.hpp>

namespace boost{ namespace gil {

typedef boost::gil::point2< std::ptrdiff_t > point_t;

////////////////////////////////////////////////////////////////////////////////////////
/// \class subsampled_image_deref_fn
/// \ingroup PixelLocatorModel PixelBasedModel
/// \brief Used for virtual_2D_locator
///
////////////////////////////////////////////////////////////////////////////////////////
template< typename Locator >
struct subsampled_image_deref_fn
{
    typedef gray8_view_t::locator plane_locator_t;

    typedef subsampled_image_deref_fn    const_t;
    typedef typename Locator::value_type value_type;
    typedef value_type                   reference;
    typedef value_type                   const_reference;
    typedef point_t                      argument_type;
    typedef reference                    result_type;

    static const bool is_mutable = false;

    /// default constructor
    subsampled_image_deref_fn() {}

    /// constructor
    subsampled_image_deref_fn( const plane_locator_t&    y_locator
                             , const plane_locator_t&    v_locator
                             , const plane_locator_t&    u_locator
                             , const std::size_t ux_ssfactor
                             , const std::size_t uy_ssfactor
                             , const std::size_t vx_ssfactor
                             , const std::size_t vy_ssfactor
                             )
    : _y_locator  (   y_locator )
    , _v_locator  (   v_locator )
    , _u_locator  (   u_locator )
    , _ux_ssfactor( ux_ssfactor )
    , _uy_ssfactor( uy_ssfactor )
    , _vx_ssfactor( vx_ssfactor )
    , _vy_ssfactor( vy_ssfactor )
    {}

    /// operator()
    typename result_type operator()( const point_t& p ) const
    {
        auto y = *_y_locator.xy_at( p );
        auto v = *_v_locator.xy_at( p.x / _ux_ssfactor, p.y / _uy_ssfactor );
        auto u = *_u_locator.xy_at( p.x / _vx_ssfactor, p.y / _vy_ssfactor );

        return value_type( at_c<0>( y )
                         , at_c<0>( v )
                         , at_c<0>( u )
                         );
    }

    /// 
    const plane_locator_t& y_locator() const { return _y_locator; }
    const plane_locator_t& v_locator() const { return _v_locator; }
    const plane_locator_t& u_locator() const { return _u_locator; }

    const std::size_t ux_ssfactor() const { return ux_ssfactor; }
    const std::size_t uy_ssfactor() const { return uy_ssfactor; }
    const std::size_t vx_ssfactor() const { return vx_ssfactor; }
    const std::size_t vy_ssfactor() const { return vy_ssfactor; }

private:
    
    plane_locator_t _y_locator;
    plane_locator_t _v_locator;
    plane_locator_t _u_locator;

    std::size_t _ux_ssfactor;
    std::size_t _uy_ssfactor;
    std::size_t _vx_ssfactor;
    std::size_t _vy_ssfactor;
};


////////////////////////////////////////////////////////////////////////////////////////
/// \class subsampled_image_locator_type
/// \ingroup PixelLocatorModel PixelBasedModel
/// \brief 
///
////////////////////////////////////////////////////////////////////////////////////////
template< typename Locator >
struct subsampled_image_locator
{
    typedef virtual_2d_locator< subsampled_image_deref_fn< Locator > // Deref
                              , false                                // IsTransposed
                              > type;
};


////////////////////////////////////////////////////////////////////////////////////////
/// \class subsampled_image_view
/// \ingroup ImageViewModel PixelBasedModel
/// \brief A lightweight object that interprets a subsampled image.Models ImageViewConcept,PixelBasedConcept,HasDynamicXStepTypeConcept,HasDynamicYStepTypeConcept,HasTransposedTypeConcept
///
////////////////////////////////////////////////////////////////////////////////////////
template< typename Locator > // subsampled_image_locator< ... >::type
class subsampled_image_view : public image_view< Locator >
{
public:

    typedef typename Locator::deref_fn_t         deref_fn_t;
    typedef typename deref_fn_t::plane_locator_t plane_locator_t;

    typedef subsampled_image_view const_t;

    typedef image_view< plane_locator_t > plane_view_t;

    /// default constructor
    subsampled_image_view()
    : image_view< Locator >()
    {}

    /// constructor
    subsampled_image_view( const point_t& y_dimensions
                         , const point_t& v_dimensions
                         , const point_t& u_dimensions
                         , const Locator& locator
                         )
    : image_view< Locator >( y_dimensions, locator )
    , _y_dimensions( y_dimensions )
    , _v_dimensions( v_dimensions )
    , _u_dimensions( u_dimensions )
    {}
    
    /// copy constructor
    template< typename Subsampled_View >
    subsampled_image_view( const Subsampled_View& v )
    : image_view< locator_t >( v )
    {}

    const point_t& v_ssfactors() const { return point_t( get_deref_fn().vx_ssfactor(), get_deref_fn().vx_ssfactor() ); }
    const point_t& u_ssfactors() const { return point_t( get_deref_fn().ux_ssfactor(), get_deref_fn().ux_ssfactor() ); }

    const point_t& y_dimension() const { return _y_dimensions; }
    const point_t& v_dimension() const { return _v_dimensions; }
    const point_t& u_dimension() const { return _u_dimensions; }

    const plane_locator_t& y_plane() const { return get_deref_fn().y_locator(); }
    const plane_locator_t& v_plane() const { return get_deref_fn().v_locator(); }
    const plane_locator_t& u_plane() const { return get_deref_fn().u_locator(); }

    const plane_view_t y_plane_view() const { return plane_view_t( _y_dimensions, y_plane() ); }
    const plane_view_t v_plane_view() const { return plane_view_t( _v_dimensions, v_plane() ); }
    const plane_view_t u_plane_view() const { return plane_view_t( _u_dimensions, u_plane() ); }


private:

    const deref_fn_t& get_deref_fn() const { return this->pixels().deref_fn(); }

private:

    template< typename Locator > friend class subsampled_image_view;

    point_t _y_dimensions;
    point_t _v_dimensions;
    point_t _u_dimensions;
};


////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup ImageModel PixelBasedModel
/// \brief container interface over image view. Models ImageConcept, PixelBasedConcept
///
/// A subsampled image holds a bunch of planes which don't need to have the same resolution.
///
////////////////////////////////////////////////////////////////////////////////////////
template< typename Pixel
        , typename Allocator = std::allocator< unsigned char >
        >
class subsampled_image
{
public:
    
    typedef typename channel_type< Pixel >::type channel_t;
    typedef pixel< channel_t, gray_layout_t> pixel_t;

    typedef image< pixel_t, false, Allocator > plane_image_t;

    typedef typename plane_image_t::view_t plane_view_t;
    typedef typename plane_image_t::const_view_t plane_const_view_t;
    typedef typename plane_view_t::locator plane_locator_t;

    typedef typename view_type_from_pixel< Pixel >::type pixel_view_t;
    typedef typename subsampled_image_locator< typename pixel_view_t::locator >::type locator_t;

    typedef typename plane_image_t::coord_t x_coord_t;
    typedef typename plane_image_t::coord_t y_coord_t;

    typedef subsampled_image_view< locator_t > view_t;
    typedef typename view_t::const_t           const_view_t;


    /// constructor
    subsampled_image( const x_coord_t   y_width
                    , const y_coord_t   y_height
                    , const std::size_t vx_ssfactor = 2
                    , const std::size_t vy_ssfactor = 2
                    , const std::size_t ux_ssfactor = 2
                    , const std::size_t uy_ssfactor = 2
                    )
    : _y_plane(               y_width,               y_height, 0, Allocator() )
    , _v_plane( y_width / vx_ssfactor, y_height / vy_ssfactor, 0, Allocator() )
    , _u_plane( y_width / ux_ssfactor, y_height / uy_ssfactor, 0, Allocator() )
    {
        init( point_t( y_width, y_height )
            , vx_ssfactor
            , vy_ssfactor
            , ux_ssfactor
            , uy_ssfactor
            );
    }

public:

    view_t _view;

private:

    void init( const point_t&    y_dimensions
             , const std::size_t vx_ssfactor
             , const std::size_t vy_ssfactor
             , const std::size_t ux_ssfactor
             , const std::size_t uy_ssfactor
             )
    {
        typedef subsampled_image_deref_fn< locator_t > defer_fn_t;

        defer_fn_t deref_fn( view( _y_plane ).xy_at( 0, 0 )
                           , view( _v_plane ).xy_at( 0, 0 )
                           , view( _u_plane ).xy_at( 0, 0 )
                           , vx_ssfactor
                           , vy_ssfactor
                           , ux_ssfactor
                           , uy_ssfactor
                           );

        // init a virtual_2d_locator
        locator_t locator( point_t( 0, 0 ) // p
                         , point_t( 1, 1 ) // step
                         , deref_fn
                         );

        _view = view_t( _y_plane.dimensions()
                      , _v_plane.dimensions()
                      , _u_plane.dimensions()
                      , locator
                      );
    }
    

private:

    plane_image_t _y_plane;
    plane_image_t _v_plane;
    plane_image_t _u_plane;
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \name view, const_view
/// \brief Get an image view from an subsampled_image
/// \ingroup ImageModel
/// \brief Returns the non-constant-pixel view of an image
/////////////////////////////////////////////////////////////////////////////////////////
template< typename Pixel >
inline
const typename subsampled_image< Pixel >::view_t& view( subsampled_image< Pixel >& img )
{
    return img._view;
}

template< typename Pixel >
inline
const typename subsampled_image< Pixel >::const_view_t const_view( subsampled_image< Pixel >& img )
{
    return static_cast< const typename subsampled_image< Pixel >::const_view_t>( img._view );
}

/////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup ImageViewSTLAlgorithmsFillPixels
/// \brief std::fill for subsampled_image views
/////////////////////////////////////////////////////////////////////////////////////////
template< typename Locator
        , typename Pixel
        >
void fill_pixels( const subsampled_image_view< Locator >& view
                , const Pixel&                            value
                )
{
    typedef typename subsampled_image<Pixel>::plane_view_t::value_type channel_t;

    fill_pixels( view.y_plane_view(), channel_t( at_c<0>( value )));
    fill_pixels( view.v_plane_view(), channel_t( at_c<1>( value )));
    fill_pixels( view.u_plane_view(), channel_t( at_c<2>( value )));
}

/////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup ImageViewConstructors
/// \brief Creates a subsampled view from a raw memory
/////////////////////////////////////////////////////////////////////////////////////////
//template< typename Pixel >
//typename subsampled_image< Pixel >::view_t subsampled_view( std::size_t    y_width
//                                                          , std::size_t    y_height
//                                                          , unsigned char* y_base
//                                                          , std::size_t    vx_ssfactor = 2
//                                                          , std::size_t    vy_ssfactor = 2
//                                                          , std::size_t    ux_ssfactor = 2
//                                                          , std::size_t    uy_ssfactor = 2
//                                                          )
//{
//    std::size_t y_channel_size = 1;
//    std::size_t u_channel_size = 1;
//
//    unsigned char* u_base = y_base + ( y_width  * y_height * y_channel_size );
//    unsigned char* v_base = u_base + ( y_width / ux_ssfactor ) * ( y_height / uy_ssfactor ) * u_channel_size;
//
//    typedef subsampled_image< Pixel >::plane_view_t plane_view_t;
//
//    plane_view_t y_plane = interleaved_view( y_width
//                                           , y_height
//                                           , (plane_view_t::value_type*) y_base // pixels
//                                           , y_width                            // rowsize_in_bytes
//                                           );
//
//    plane_view_t v_plane = interleaved_view( y_width  / vx_ssfactor 
//                                           , y_height / vy_ssfactor
//                                           , (plane_view_t::value_type*) v_base // pixels
//                                           , y_width                            // rowsize_in_bytes
//                                           );
//
//    plane_view_t u_plane = interleaved_view( y_width  / ux_ssfactor
//                                           , y_height / uy_ssfactor
//                                           , (plane_view_t::value_type*) u_base // pixels
//                                           , y_width                            // rowsize_in_bytes
//                                           );
//
//    typedef subsampled_image_deref_fn< subsampled_image< Pixel >::locator_t > defer_fn_t;
//    defer_fn_t deref_fn( y_plane.xy_at( 0, 0 )
//                       , v_plane.xy_at( 0, 0 )
//                       , u_plane.xy_at( 0, 0 )
//                       , vx_ssfactor
//                       , vy_ssfactor
//                       , ux_ssfactor
//                       , uy_ssfactor
//                       );
//    
//
//    typedef subsampled_image< Pixel >::locator_t locator_t;
//    locator_t locator( point_t( 0, 0 ) // p
//                     , point_t( 1, 1 ) // step
//                     , deref_fn
//                     );
//
//    typedef subsampled_image< Pixel >::view_t view_t;
//    return view_t( point_t(               y_width,               y_height )
//                 , point_t( y_width / vx_ssfactor, y_height / vy_ssfactor )
//                 , point_t( y_width / ux_ssfactor, y_height / uy_ssfactor )
//                 , locator
//                 );
//}


} // namespace gil
} // namespace boost

#endif // BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_SUBSAMPLED_IMAGE_HPP