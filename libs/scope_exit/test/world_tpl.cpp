
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/scope_exit

#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/vector.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#define BOOST_TEST_MODULE TestWorldTpl
#include <boost/test/unit_test.hpp>
#include <vector>

struct person {};
BOOST_TYPEOF_REGISTER_TYPE(peron)

template<typename Person>
struct world {
    void add_person(Person const& a_person);
    size_t population(void) const { return persons_.size(); }

private:
    std::vector<Person> persons_;
};
BOOST_TYPEOF_REGISTER_TEMPLATE(world, 1)

//[world_tpl
template<typename Person>
void world<Person>::add_person(Person const& a_person) {
    bool commit = false;
    persons_.push_back(a_person);

    BOOST_SCOPE_EXIT_TPL(&commit, this_) { // Use `_TPL` postfix.
        if(!commit) this_->persons_.pop_back();
    } BOOST_SCOPE_EXIT_END

    // ...

    commit = true;
}
//]

BOOST_AUTO_TEST_CASE(test_world_tpl) {
    world<person> w;
    person p;
    w.add_person(p);
    BOOST_CHECK(w.population() == 1);
}

#else

int main(void) { return 0; } // Trivial test.

#endif

