/*=============================================================================
    Spirit v1.6.2
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at 
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <boost/spirit/iterator/fixed_size_queue.hpp>
#include <cassert>

int main(int, char**)
{

    boost::spirit::fixed_size_queue<int, 5> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.push_back(4);
    assert(q.front() == 1);
    q.pop_front();
    assert(q.front() == 2);
    q.pop_front();
    assert(q.front() == 3);
    q.pop_front();
    assert(q.front() == 4);
    q.pop_front();
    q.push_back(5);
    q.push_back(6);
    q.push_back(7);
    q.push_back(8);
    assert(q.front() == 5);
    q.pop_front();
    assert(q.front() == 6);
    q.pop_front();
    assert(q.front() == 7);
    q.pop_front();
    assert(q.front() == 8);
    q.pop_front();

    q.push_front(5);
    q.push_front(4);
    q.push_front(3);
    q.push_front(2);
    q.push_front(1);
    typedef boost::spirit::fixed_size_queue<int, 5>::iterator iter_t;

    iter_t b = q.begin();
    assert(*b++ == 1);
    assert(*b++ == 2);
    assert(*b++ == 3);
    assert(*b++ == 4);
    assert(*b++ == 5);
    assert(b == q.end());
    return 0;
}

