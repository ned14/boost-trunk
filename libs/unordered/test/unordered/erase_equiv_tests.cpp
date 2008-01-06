
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// The code for erasing elements from containers with equivalent keys is very
// hairy with several tricky edge cases - so explicitly test each one.

#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <list>
#include <set>
#include <iostream>
#include <iterator>
#include <boost/next_prior.hpp>
#include "../objects/test.hpp"

struct write_pair_type
{
    template <class X1, class X2>
    void operator()(std::pair<X1, X2> const& x) const
    {
        std::cout<<"("<<x.first<<","<<x.second<<")";
    }
} write_pair;

template <class Container>
void write_container(Container const& x)
{
    std::for_each(x.begin(), x.end(), write_pair);
    std::cout<<"\n";
}

// Make everything collide - for testing erase in a single bucket.
struct collision_hash
{
    int operator()(int) const { return 0; }
};

// For testing erase in 2 buckets.
struct collision2_hash
{
    int operator()(int x) const { return x & 1; }
};

typedef boost::unordered_multimap<int, int,
    collision_hash, std::equal_to<int>,
    test::allocator<std::pair<int const, int> > > collide_map;
typedef boost::unordered_multimap<int, int,
    collision2_hash, std::equal_to<int>,
    test::allocator<std::pair<int const, int> > > collide_map2;
typedef collide_map::value_type collide_value;
typedef std::list<collide_value> collide_list;


void empty_range_tests()
{
    collide_map x;
    x.erase(x.begin(), x.end());
    x.erase(x.begin(), x.begin());
    x.erase(x.end(), x.end());
}

void single_item_tests()
{
    collide_list init;
    init.push_back(collide_value(1,1));

    collide_map x(init.begin(), init.end());
    x.erase(x.begin(), x.begin());
    BOOST_TEST(x.count(1) == 1 && x.size() == 1);
    x.erase(x.end(), x.end());
    BOOST_TEST(x.count(1) == 1 && x.size() == 1);
    x.erase(x.begin(), x.end());
    BOOST_TEST(x.count(1) == 0 && x.size() == 0);
}

void two_equivalent_item_tests()
{
    collide_list init;
    init.push_back(collide_value(1,1));
    init.push_back(collide_value(1,2));

    {
        collide_map x(init.begin(), init.end());
        x.erase(x.begin(), x.end());
        BOOST_TEST(x.count(1) == 0 && x.size() == 0);
    }

    {
        collide_map x(init.begin(), init.end());
        int value = boost::next(x.begin())->second;
        x.erase(x.begin(), boost::next(x.begin()));
        BOOST_TEST(x.count(1) == 1 && x.size() == 1 &&
            x.begin()->first == 1 && x.begin()->second == value);
    }

    {
        collide_map x(init.begin(), init.end());
        int value = x.begin()->second;
        x.erase(boost::next(x.begin()), x.end());
        BOOST_TEST(x.count(1) == 1 && x.size() == 1 &&
                x.begin()->first == 1 && x.begin()->second == value);
    }
}

// More automated tests...

template<class Range1, class Range2>
bool compare(Range1 const& x, Range2 const& y)
{
    collide_list a;
    collide_list b;
    std::copy(x.begin(), x.end(), std::back_inserter(a));
    std::copy(y.begin(), y.end(), std::back_inserter(b));
    a.sort();
    b.sort();
    return a == b;
}

template <class Container>
bool general_erase_range_test(Container& x, int start, int end)
{
    collide_list l;
    std::copy(x.begin(), x.end(), std::back_inserter(l));
    l.erase(boost::next(l.begin(), start), boost::next(l.begin(), end));
    x.erase(boost::next(x.begin(), start), boost::next(x.begin(), end));
    return compare(l, x);
}

template <class Container>
void erase_subrange_tests(Container const& x)
{
    for(std::size_t length = 0; length < x.size(); ++length) {
        for(std::size_t position = 0; position < x.size() - length; ++position) {
            Container y(x);
            collide_list init;
            std::copy(y.begin(), y.end(), std::back_inserter(init));
            if(!general_erase_range_test(y, position, position + length)) {
                BOOST_ERROR("general_erase_range_test failed.");
                std::cout<<"Erase: ["<<position<<","<<position + length<<")\n";
                write_container(init);
                write_container(y);
            }
        }
    }
}

template <class Container>
void x_by_y_erase_range_tests(Container*, int values, int duplicates)
{
    Container y;

    for(int i = 0; i < values; ++i) {
        for(int j = 0; j < duplicates; ++j) {
            y.insert(collide_value(i, j));
        }
    }

    std::cout<<"Values: "<<values<<", Duplicates: "<<duplicates<<"\n";
    erase_subrange_tests(y);
}

template <class Container>
void exhaustive_erase_tests(Container* x, int num_values,
        int num_duplicated)
{
    for(int i = 0; i < num_values; ++i) {
        for(int j = 0; j < num_duplicated; ++j) {
            x_by_y_erase_range_tests(x, i, j);
        }
    }
}

void exhaustive_collide_tests() 
{
    std::cout<<"exhaustive_collide_tests:\n";
    collide_map m;
    exhaustive_erase_tests((collide_map*) 0, 4, 4);
    std::cout<<"\n";
}

void exhaustive_collide2_tests() 
{
    std::cout<<"exhaustive_collide2_tests:\n";
    exhaustive_erase_tests((collide_map2*) 0, 8, 4);
    std::cout<<"\n";
}

int main()
{
    empty_range_tests();
    single_item_tests();
    two_equivalent_item_tests();
    exhaustive_collide_tests();
    exhaustive_collide2_tests();

    return boost::report_errors();
}
