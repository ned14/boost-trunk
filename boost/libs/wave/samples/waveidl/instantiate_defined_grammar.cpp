/*=============================================================================
    Wave: A Standard compliant C++ preprocessor library

    Sample: IDL oriented preprocessor
            Explicit instantiation of the defined_grammar template

    http://spirit.sourceforge.net/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "idl.hpp"

#if BOOST_WAVE_SEPARATE_GRAMMAR_INSTANTIATION != 0

#include <string>

#include <boost/wave/token_ids.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>

#include "idllexer/idl_lex_iterator.hpp"

#include <boost/wave/grammars/cpp_defined_grammar.hpp>

///////////////////////////////////////////////////////////////////////////////
//  
//  Explicit instantiation of the defined_grammar_gen template 
//  with the correct token type. This instantiates the corresponding parse 
//  function, which in turn instantiates the defined_grammar 
//  object (see wave/grammars/cpp_defined_grammar.hpp)
//
///////////////////////////////////////////////////////////////////////////////

typedef boost::wave::idllexer::lex_iterator<
        boost::wave::cpplexer::lex_token<> >
    lexer_type;
template struct boost::wave::grammars::defined_grammar_gen<lexer_type>;

#endif // #if BOOST_WAVE_SEPARATE_GRAMMAR_INSTANTIATION != 0

