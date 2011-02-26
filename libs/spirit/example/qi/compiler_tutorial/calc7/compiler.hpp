/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CALC7_COMPILER_HPP)
#define BOOST_SPIRIT_CALC7_COMPILER_HPP

#include "ast.hpp"
#include <vector>

namespace client
{
    ///////////////////////////////////////////////////////////////////////////
    //  The Compiler
    ///////////////////////////////////////////////////////////////////////////
    struct compiler
    {
        typedef void result_type;

        std::vector<int>& code;
        compiler(std::vector<int>& code)
          : code(code) {}

        void op(int opcode) const { code.push_back(opcode); }

        void operator()(ast::nil) const { BOOST_ASSERT(0); }
        void operator()(ast::unsigned_ const& x) const;
        void operator()(ast::operation const& x) const;
        void operator()(ast::signed_ const& x) const;
        void operator()(ast::program const& x) const;
    };
}

#endif