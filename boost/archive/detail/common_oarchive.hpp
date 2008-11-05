#ifndef BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// common_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/archive/detail/basic_oarchive.hpp>
#include <boost/archive/detail/interface_oarchive.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost {
namespace archive {
namespace detail {

// note: referred to as Curiously Recurring Template Patter (CRTP)
template<class Archive, bool HelperSupport = true>
class common_oarchive : 
    public basic_oarchive,
    public interface_oarchive<Archive, HelperSupport>
{
    friend class interface_oarchive<Archive, HelperSupport>;
private:
    virtual void vsave(const version_type t){
        * this->This() << t;
    }
    virtual void vsave(const object_id_type t){
        * this->This() << t;
    }
    virtual void vsave(const object_reference_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_reference_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_optional_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_name_type & t){
        * this->This() << t;
    }
    virtual void vsave(const tracking_type t){
        * this->This() << t;
    }
protected:
    // default processing - invoke serialization library
    template<class T>
    void save_override(T & t, BOOST_PFTO int){
        archive::save(* this->This(), t);
    }
    void save_start(const char * /*name*/){}
    void save_end(const char * /*name*/){}
    common_oarchive(unsigned int flags = 0) : 
        basic_oarchive(flags),
        interface_oarchive<Archive, HelperSupport>()
    {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP
