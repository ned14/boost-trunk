/*=============================================================================
    Copyright (c) 2009 Daniel James
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_SPIRIT_QUICKBOOK_QUICKBOOK_HPP)
#define BOOST_SPIRIT_QUICKBOOK_QUICKBOOK_HPP

namespace quickbook
{
    extern unsigned qbk_major_version;
    extern unsigned qbk_minor_version;
    extern unsigned qbk_version_n; // qbk_major_version * 100 + qbk_minor_version

    struct quickbook_range {
        template <typename Arg>
        struct result
        {
            typedef bool type;
        };
        
        quickbook_range(unsigned min, unsigned max)
            : min(min), max(max) {}
        
        bool operator()() const {
            return qbk_version_n >= min && qbk_version_n < max;
        }

        unsigned min, max;
    };
    
    inline quickbook_range qbk_since(unsigned min) {
        return quickbook_range(min, 999);
    }
    
    inline quickbook_range qbk_before(unsigned max) {
        return quickbook_range(0, max);
    }
}

#endif