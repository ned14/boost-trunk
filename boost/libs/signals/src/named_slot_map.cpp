// Boost.Signals library

// Copyright Doug Gregor 2001-2004. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_SIGNALS_SOURCE

#include <boost/signals/detail/named_slot_map.hpp>
#include <cassert>
#include <map>
#include <list>
#include <typeinfo>

namespace boost { namespace BOOST_SIGNALS_NAMESPACE { namespace detail {

class named_slot_map::impl
{
public:
  typedef std::list<connection_slot_pair> group_list;
  typedef group_list::iterator slot_pair_iterator;
  typedef std::map<any, group_list, compare_type> slot_container_type;
  typedef slot_container_type::iterator group_iterator;

  impl(const compare_type& compare) : groups(compare)
  {
    clear();
  }

  void clear()
  {
    groups.clear();
    groups[front_type()];
    groups[back_type()];
    back = groups.end();
    --back;
  }

  slot_container_type groups;
  group_iterator back;

  bool empty(group_iterator group) const
  {
    return (group->second.empty() && group != groups.begin() && group != back);
  }
};

class named_slot_map::iterator::impl
{
public:
  typedef named_slot_map::impl::slot_pair_iterator slot_pair_iterator;
  typedef named_slot_map::impl::group_iterator group_iterator;

  impl() {}

  impl(group_iterator group, group_iterator last_group)
    : group(group), last_group(last_group)
  { init_next_group(); }

  impl(group_iterator group, group_iterator last_group,
       slot_pair_iterator slot_)
    : group(group), last_group(last_group), slot_(slot_) { }

  void init_next_group()
  {
    while (group != last_group && group->second.empty()) ++group;
    if (group != last_group) slot_ = group->second.begin();
  }

  named_slot_map::impl::group_iterator group;
  named_slot_map::impl::group_iterator last_group;
  named_slot_map::impl::slot_pair_iterator slot_;
};

named_slot_map::iterator::iterator() {}

named_slot_map::iterator::iterator(std::auto_ptr<impl> impl_)
  : impl_(impl_) {}

named_slot_map::iterator::iterator(const iterator& other)
{
  impl_.reset(new impl(other.impl_->group, other.impl_->last_group,
                       other.impl_->slot_));
}

named_slot_map::iterator::~iterator() {}

named_slot_map::iterator&
named_slot_map::iterator::operator=(const iterator& other)
{
  if (impl_) {
    impl_->group = other.impl_->group;
    impl_->last_group = other.impl_->last_group;
    impl_->slot_ = other.impl_->slot_;
  } else {
    impl_.reset(new impl(other.impl_->group, other.impl_->last_group,
                         other.impl_->slot_));
  }
  return *this;
}

connection_slot_pair& named_slot_map::iterator::dereference() const
{ return *impl_->slot_; }

void named_slot_map::iterator::increment()
{
  ++impl_->slot_;
  if (impl_->slot_ == impl_->group->second.end()) {
    ++impl_->group;
    impl_->init_next_group();
  }
}

bool named_slot_map::iterator::equal(const iterator& other) const
{
  return (impl_->group == other.impl_->group
          && (impl_->group == impl_->last_group
              || impl_->slot_ == other.impl_->slot_));
}

#if BOOST_WORKAROUND(BOOST_MSVC, <= 0x1701)
void named_slot_map::iterator::decrement() { assert(false); }
void named_slot_map::iterator::advance(difference_type) { assert(false); }
#endif

named_slot_map::named_slot_map(const compare_type& compare)
{
  impl_.reset(new impl(compare));
}

named_slot_map::~named_slot_map() {}

void named_slot_map::clear() { impl_->clear(); }

named_slot_map::iterator named_slot_map::begin()
{
  std::auto_ptr<iterator::impl> it;
  it.reset(new iterator::impl(impl_->groups.begin(),
                              impl_->groups.end()));
  return iterator(it);
}

named_slot_map::iterator named_slot_map::end()
{
  std::auto_ptr<iterator::impl> it;
  it.reset(new iterator::impl(impl_->groups.end(),
                              impl_->groups.end()));
  return iterator(it);
}

named_slot_map::iterator
named_slot_map::insert(const any& name, const connection& con, const any& slot,
                       connect_position at)
{
  impl::group_iterator group;
  if (name.empty()) {
    switch (at) {
    case at_front: group = impl_->groups.begin(); break;
    case at_back: group = impl_->back; break;
    }
  } else {
    group = impl_->groups.find(name);
    if (group == impl_->groups.end()) {
      impl::slot_container_type::value_type v(name, impl::group_list());
      group = impl_->groups.insert(v).first;
    }
  }
  std::auto_ptr<iterator::impl> it(new iterator::impl);
  it->group = group;
  it->last_group = impl_->groups.end();

  switch (at) {
  case at_back:
    group->second.push_back(connection_slot_pair(con, slot));
    it->slot_ = group->second.end();
    --(it->slot_);
    break;

  case at_front:
    group->second.push_front(connection_slot_pair(con, slot));
    it->slot_ = group->second.begin();
    break;
  }
  return iterator(it);
}

void named_slot_map::disconnect(const any& name)
{
  impl::group_iterator group = impl_->groups.find(name);
  if (group != impl_->groups.end()) {
    impl::slot_pair_iterator i = group->second.begin();
    while (i != group->second.end()) {
      impl::slot_pair_iterator next = i;
      ++next;
      i->first.disconnect();
      i = next;
    }
    impl_->groups.erase(group);
  }
}

void named_slot_map::erase(iterator pos)
{
  // Erase the slot
  pos.impl_->group->second.erase(pos.impl_->slot_);
}

void named_slot_map::remove_disconnected_slots()
{
  // Remove any disconnected slots
  impl::group_iterator g = impl_->groups.begin();
  while (g != impl_->groups.end()) {
    impl::slot_pair_iterator s = g->second.begin();
    while (s != g->second.end()) {
      if (s->first.connected()) ++s;
      else g->second.erase(s++);
    }

    // Clear out empty groups
    if (impl_->empty(g)) impl_->groups.erase(g++);
    else ++g;
  }
}


} } }
