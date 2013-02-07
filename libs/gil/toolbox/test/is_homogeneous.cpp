#include <boost/test/unit_test.hpp>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/toolbox/metafunctions/is_homogeneous.hpp>

using namespace boost;
using namespace gil;

BOOST_AUTO_TEST_SUITE( is_homogeneous_test )

BOOST_AUTO_TEST_CASE( is_homogeneous_test )
{
    BOOST_STATIC_ASSERT(( is_homogeneous< rgb8_pixel_t >::value ));

    BOOST_STATIC_ASSERT(( is_homogeneous< cmyk16c_planar_ref_t >::value ));

    typedef bit_aligned_image1_type< 4, gray_layout_t>::type image_t;
    BOOST_STATIC_ASSERT(( is_homogeneous< image_t::view_t::reference >::value ));
}

BOOST_AUTO_TEST_SUITE_END()
