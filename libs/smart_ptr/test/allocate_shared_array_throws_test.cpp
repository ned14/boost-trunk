/*
 * Copyright (c) 2012 Glen Joseph Fernandes 
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License, 
 * Version 1.0. (See accompanying file LICENSE_1_0.txt 
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#include <boost/detail/lightweight_test.hpp>
#include <boost/smart_ptr/allocate_shared_array.hpp>

class type {
public:
    static unsigned int instances;
    explicit type() {
        if (instances == 5) {
            throw true;
        }
        instances++;
    }
    ~type() {
        instances--;
    }
private:
    type(const type&);
    type& operator=(const type&);
};

unsigned int type::instances = 0;

int main() {
    BOOST_TEST(type::instances == 0);
    try {
        boost::allocate_shared<type[]>(std::allocator<type>(), 6);
        BOOST_ERROR("allocate_shared did not throw");
    } catch (...) {
        BOOST_TEST(type::instances == 0);
    }
    BOOST_TEST(type::instances == 0);
    try {
        boost::allocate_shared<type[][2]>(std::allocator<type>(), 3);
        BOOST_ERROR("allocate_shared did not throw");
    } catch (...) {
        BOOST_TEST(type::instances == 0);
    }
#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
    BOOST_TEST(type::instances == 0);
    try {
        boost::allocate_shared<type[6]>(std::allocator<type>());
        BOOST_ERROR("allocate_shared did not throw");
    } catch (...) {
        BOOST_TEST(type::instances == 0);
    }
    BOOST_TEST(type::instances == 0);
    try {
        boost::allocate_shared<type[3][2]>(std::allocator<type>());
        BOOST_ERROR("allocate_shared did not throw");
    } catch (...) {
        BOOST_TEST(type::instances == 0);
    }
#endif
    return boost::report_errors();
}
