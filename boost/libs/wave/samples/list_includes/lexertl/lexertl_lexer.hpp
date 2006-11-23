/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost 
    Software License, Version 1.0. (See accompanying file 
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_WAVE_LEXERTL_LEXER_HPP_INCLUDED)
#define BOOST_WAVE_LEXERTL_LEXER_HPP_INCLUDED

#include <boost/iterator/iterator_traits.hpp>

#include <boost/wave/wave_config.hpp>
#include <boost/wave/language_support.hpp>
#include <boost/wave/token_ids.hpp>

#include <boost/wave/cpplexer/validate_universal_char.hpp>
#include <boost/wave/cpplexer/convert_trigraphs.hpp>
#include <boost/wave/cpplexer/cpplexer_exceptions.hpp>

#include "../lexertl_iterator.hpp"

#include "lexertl/generator.hpp"
#include "lexertl/rules.hpp"
#include "lexertl/state_machine.hpp"
#include "lexertl/consts.h"

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace wave { namespace cpplexer { namespace lexertl 
{

///////////////////////////////////////////////////////////////////////////////
//  The following numbers are the array sizes of the token regex's which we
//  need to specify to make the CW compiler happy (at least up to V9.5).
#if BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
#define INIT_DATA_SIZE              176
#else
#define INIT_DATA_SIZE              159
#endif
#define INIT_DATA_CPP_SIZE          15
#define INIT_DATA_PP_NUMBER_SIZE    2

///////////////////////////////////////////////////////////////////////////////
namespace lexer
{

///////////////////////////////////////////////////////////////////////////////
//  this is the wrapper for the lexertl lexer library
template <typename Iterator, typename Position>
class lexertl 
{
private:
    typedef BOOST_WAVE_STRINGTYPE string_type;
    typedef typename boost::detail::iterator_traits<Iterator>::value_type 
        char_type;

public:
    lexertl() : has_compiled_dfa(false) {}
    
    wave::token_id next_token(Iterator &first, Iterator const &last,
        string_type& token_value);
    
    void init_dfa(wave::language_support lang);
    
private:
    ::lexertl::rules rules_;
    ::lexertl::state_machine state_machine_;
    bool has_compiled_dfa;
    
// initialization data (regular expressions for the token definitions)
    struct lexer_data {
        token_id tokenid;               // token data
        char_type const *tokenregex;    // associated token to match
    };

    static lexer_data const init_data[INIT_DATA_SIZE];          // common patterns
    static lexer_data const init_data_cpp[INIT_DATA_CPP_SIZE];  // C++ only patterns
    static lexer_data const init_data_pp_number[INIT_DATA_PP_NUMBER_SIZE];  // pp-number only patterns
};

///////////////////////////////////////////////////////////////////////////////
// token regex definitions

#define OR                  "|"
#define Q(c)                "\\" c
#define TRI(c)              Q("?") Q("?") c

// definition of some sub-token regexp's to simplify the regex definitions
#define BLANK               "[ \\t]"
#define CCOMMENT            \
    Q("/") Q("*") "[^*]*" Q("*") "+" "(" "[^/*][^*]*" Q("*") "+" ")*" Q("/")
        
#define PPSPACE             "(" BLANK OR CCOMMENT ")*"

#define OCTALDIGIT          "[0-7]"
#define DIGIT               "[0-9]"
#define HEXDIGIT            "[0-9a-fA-F]"
#define OPTSIGN             "[-+]?"
#define EXPSTART            "[eE]" "[-+]"
#define EXPONENT            "(" "[eE]" OPTSIGN "[0-9]+" ")"
#define NONDIGIT            "[a-zA-Z_]"

#define INTEGER             \
    "(" "(0x|0X)" HEXDIGIT "+" OR "0" OCTALDIGIT "*" OR "[1-9]" DIGIT "*" ")"
            
#define INTEGER_SUFFIX      "(" "[uU][lL]?|[lL][uU]?" ")"
#if BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
#define LONGINTEGER_SUFFIX  "(" "[uU]" "(" "[lL][lL]" ")" OR \
                                "(" "[lL][lL]" ")" "[uU]" "?" OR \
                                "i64" \
                            ")" 
#else
#define LONGINTEGER_SUFFIX  "(" "[uU]" "(" "[lL][lL]" ")" OR \
                            "(" "[lL][lL]" ")" "[uU]" "?" ")"
#endif
#define FLOAT_SUFFIX        "(" "[fF][lL]?|[lL][fF]?" ")"
#define CHAR_SPEC           "L?"

#define BACKSLASH           "(" Q("\\") OR TRI(Q("/")) ")"
#define ESCAPESEQ           BACKSLASH "(" \
                                "[abfnrtv?'\"]" OR \
                                BACKSLASH OR \
                                "x" HEXDIGIT "+" OR \
                                OCTALDIGIT OCTALDIGIT "?" OCTALDIGIT "?" \
                            ")"
#define HEXQUAD             HEXDIGIT HEXDIGIT HEXDIGIT HEXDIGIT 
#define UNIVERSALCHAR       BACKSLASH "(" \
                                "u" HEXQUAD OR \
                                "U" HEXQUAD HEXQUAD \
                            ")" 

#define POUNDDEF            "(" "#" OR TRI("=") OR Q("%:") ")"
#define NEWLINEDEF          "(" "\\n" OR "\\r" OR "\\r\\n" ")"

#if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0
#define INCLUDEDEF          "(include|include_next)"
#else
#define INCLUDEDEF          "include"
#endif

#define PP_NUMBERDEF        Q(".") "?" DIGIT "(" DIGIT OR NONDIGIT OR EXPSTART OR Q(".") ")*"

//  helper for initializing token data
#define TOKEN_DATA(id, regex) { id, regex }

// common C++/C99 token definitions
template <typename Iterator, typename Position>
typename lexertl<Iterator, Position>::lexer_data const 
lexertl<Iterator, Position>::init_data[INIT_DATA_SIZE] = 
{
    TOKEN_DATA(T_AND, "&"),
    TOKEN_DATA(T_ANDAND, "&&"),
    TOKEN_DATA(T_ASSIGN, "="),
    TOKEN_DATA(T_ANDASSIGN, "&="),
    TOKEN_DATA(T_OR, Q("|")),
    TOKEN_DATA(T_OR_TRIGRAPH, TRI("!")),
    TOKEN_DATA(T_ORASSIGN, Q("|=")),
    TOKEN_DATA(T_ORASSIGN_TRIGRAPH, TRI("!=")),
    TOKEN_DATA(T_XOR, Q("^")),
    TOKEN_DATA(T_XOR_TRIGRAPH, TRI("'")),
    TOKEN_DATA(T_XORASSIGN, Q("^=")),
    TOKEN_DATA(T_XORASSIGN_TRIGRAPH, TRI("'=")),
    TOKEN_DATA(T_COMMA, ","),
    TOKEN_DATA(T_COLON, ":"),
    TOKEN_DATA(T_DIVIDEASSIGN, Q("/=")),
    TOKEN_DATA(T_DIVIDE, Q("/")),
    TOKEN_DATA(T_DOT, Q(".")),
    TOKEN_DATA(T_ELLIPSIS, Q(".") Q(".") Q(".")),
    TOKEN_DATA(T_EQUAL, "=="),
    TOKEN_DATA(T_GREATER, ">"),
    TOKEN_DATA(T_GREATEREQUAL, ">="),
    TOKEN_DATA(T_LEFTBRACE, Q("{")),
    TOKEN_DATA(T_LEFTBRACE_ALT, "<" Q("%")),
    TOKEN_DATA(T_LEFTBRACE_TRIGRAPH, TRI("<")),
    TOKEN_DATA(T_LESS, "<"),
    TOKEN_DATA(T_LESSEQUAL, "<="),
    TOKEN_DATA(T_LEFTPAREN, Q("(")),
    TOKEN_DATA(T_LEFTBRACKET, Q("[")),
    TOKEN_DATA(T_LEFTBRACKET_ALT, "<:"),
    TOKEN_DATA(T_LEFTBRACKET_TRIGRAPH, TRI(Q("("))),
    TOKEN_DATA(T_MINUS, Q("-")),
    TOKEN_DATA(T_MINUSASSIGN, Q("-=")),
    TOKEN_DATA(T_MINUSMINUS, Q("-") Q("-")),
    TOKEN_DATA(T_PERCENT, Q("%")),
    TOKEN_DATA(T_PERCENTASSIGN, Q("%=")),
    TOKEN_DATA(T_NOT, "!"),
    TOKEN_DATA(T_NOTEQUAL, "!="),
    TOKEN_DATA(T_OROR, Q("|") Q("|")),
    TOKEN_DATA(T_OROR_TRIGRAPH, TRI("!") Q("|") OR Q("|") TRI("!") OR TRI("!") TRI("!")),
    TOKEN_DATA(T_PLUS, Q("+")),
    TOKEN_DATA(T_PLUSASSIGN, Q("+=")),
    TOKEN_DATA(T_PLUSPLUS, Q("+") Q("+")),
    TOKEN_DATA(T_ARROW, Q("->")),
    TOKEN_DATA(T_QUESTION_MARK, Q("?")),
    TOKEN_DATA(T_RIGHTBRACE, Q("}")),
    TOKEN_DATA(T_RIGHTBRACE_ALT, Q("%>")),
    TOKEN_DATA(T_RIGHTBRACE_TRIGRAPH, TRI(">")),
    TOKEN_DATA(T_RIGHTPAREN, Q(")")),
    TOKEN_DATA(T_RIGHTBRACKET, Q("]")),
    TOKEN_DATA(T_RIGHTBRACKET_ALT, ":>"),
    TOKEN_DATA(T_RIGHTBRACKET_TRIGRAPH, TRI(Q(")"))),
    TOKEN_DATA(T_SEMICOLON, ";"),
    TOKEN_DATA(T_SHIFTLEFT, "<<"),
    TOKEN_DATA(T_SHIFTLEFTASSIGN, "<<="),
    TOKEN_DATA(T_SHIFTRIGHT, ">>"),
    TOKEN_DATA(T_SHIFTRIGHTASSIGN, ">>="),
    TOKEN_DATA(T_STAR, Q("*")),
    TOKEN_DATA(T_COMPL, Q("~")),
    TOKEN_DATA(T_COMPL_TRIGRAPH, TRI("-")),
    TOKEN_DATA(T_STARASSIGN, Q("*=")),
    TOKEN_DATA(T_ASM, "asm"),
    TOKEN_DATA(T_AUTO, "auto"),
    TOKEN_DATA(T_BOOL, "bool"),
    TOKEN_DATA(T_FALSE, "false"),
    TOKEN_DATA(T_TRUE, "true"),
    TOKEN_DATA(T_BREAK, "break"),
    TOKEN_DATA(T_CASE, "case"),
    TOKEN_DATA(T_CATCH, "catch"),
    TOKEN_DATA(T_CHAR, "char"),
    TOKEN_DATA(T_CLASS, "class"),
    TOKEN_DATA(T_CONST, "const"),
    TOKEN_DATA(T_CONSTCAST, "const_cast"),
    TOKEN_DATA(T_CONTINUE, "continue"),
    TOKEN_DATA(T_DEFAULT, "default"),
    TOKEN_DATA(T_DELETE, "delete"),
    TOKEN_DATA(T_DO, "do"),
    TOKEN_DATA(T_DOUBLE, "double"),
    TOKEN_DATA(T_DYNAMICCAST, "dynamic_cast"),
    TOKEN_DATA(T_ELSE, "else"),
    TOKEN_DATA(T_ENUM, "enum"),
    TOKEN_DATA(T_EXPLICIT, "explicit"),
    TOKEN_DATA(T_EXPORT, "export"),
    TOKEN_DATA(T_EXTERN, "extern"),
    TOKEN_DATA(T_FLOAT, "float"),
    TOKEN_DATA(T_FOR, "for"),
    TOKEN_DATA(T_FRIEND, "friend"),
    TOKEN_DATA(T_GOTO, "goto"),
    TOKEN_DATA(T_IF, "if"),
    TOKEN_DATA(T_INLINE, "inline"),
    TOKEN_DATA(T_INT, "int"),
    TOKEN_DATA(T_LONG, "long"),
    TOKEN_DATA(T_MUTABLE, "mutable"),
    TOKEN_DATA(T_NAMESPACE, "namespace"),
    TOKEN_DATA(T_NEW, "new"),
    TOKEN_DATA(T_OPERATOR, "operator"),
    TOKEN_DATA(T_PRIVATE, "private"),
    TOKEN_DATA(T_PROTECTED, "protected"),
    TOKEN_DATA(T_PUBLIC, "public"),
    TOKEN_DATA(T_REGISTER, "register"),
    TOKEN_DATA(T_REINTERPRETCAST, "reinterpret_cast"),
    TOKEN_DATA(T_RETURN, "return"),
    TOKEN_DATA(T_SHORT, "short"),
    TOKEN_DATA(T_SIGNED, "signed"),
    TOKEN_DATA(T_SIZEOF, "sizeof"),
    TOKEN_DATA(T_STATIC, "static"),
    TOKEN_DATA(T_STATICCAST, "static_cast"),
    TOKEN_DATA(T_STRUCT, "struct"),
    TOKEN_DATA(T_SWITCH, "switch"),
    TOKEN_DATA(T_TEMPLATE, "template"),
    TOKEN_DATA(T_THIS, "this"),
    TOKEN_DATA(T_THROW, "throw"),
    TOKEN_DATA(T_TRY, "try"),
    TOKEN_DATA(T_TYPEDEF, "typedef"),
    TOKEN_DATA(T_TYPEID, "typeid"),
    TOKEN_DATA(T_TYPENAME, "typename"),
    TOKEN_DATA(T_UNION, "union"),
    TOKEN_DATA(T_UNSIGNED, "unsigned"),
    TOKEN_DATA(T_USING, "using"),
    TOKEN_DATA(T_VIRTUAL, "virtual"),
    TOKEN_DATA(T_VOID, "void"),
    TOKEN_DATA(T_VOLATILE, "volatile"),
    TOKEN_DATA(T_WCHART, "wchar_t"),
    TOKEN_DATA(T_WHILE, "while"),
    TOKEN_DATA(T_PP_DEFINE, POUNDDEF PPSPACE "define"),
    TOKEN_DATA(T_PP_IF, POUNDDEF PPSPACE "if"),
    TOKEN_DATA(T_PP_IFDEF, POUNDDEF PPSPACE "ifdef"),
    TOKEN_DATA(T_PP_IFNDEF, POUNDDEF PPSPACE "ifndef"),
    TOKEN_DATA(T_PP_ELSE, POUNDDEF PPSPACE "else"),
    TOKEN_DATA(T_PP_ELIF, POUNDDEF PPSPACE "elif"),
    TOKEN_DATA(T_PP_ENDIF, POUNDDEF PPSPACE "endif"),
    TOKEN_DATA(T_PP_ERROR, POUNDDEF PPSPACE "error"),
    TOKEN_DATA(T_PP_QHEADER, POUNDDEF PPSPACE \
        INCLUDEDEF PPSPACE Q("\"") "[^\\n\\r\"]+" Q("\"")),
    TOKEN_DATA(T_PP_HHEADER, POUNDDEF PPSPACE \
        INCLUDEDEF PPSPACE "<" "[^\\n\\r>]+" ">"),
    TOKEN_DATA(T_PP_INCLUDE, POUNDDEF PPSPACE \
        INCLUDEDEF PPSPACE),
    TOKEN_DATA(T_PP_LINE, POUNDDEF PPSPACE "line"),
    TOKEN_DATA(T_PP_PRAGMA, POUNDDEF PPSPACE "pragma"),
    TOKEN_DATA(T_PP_UNDEF, POUNDDEF PPSPACE "undef"),
    TOKEN_DATA(T_PP_WARNING, POUNDDEF PPSPACE "warning"),
#if BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
    TOKEN_DATA(T_MSEXT_INT8, "__int8"),
    TOKEN_DATA(T_MSEXT_INT16, "__int16"),
    TOKEN_DATA(T_MSEXT_INT32, "__int32"),
    TOKEN_DATA(T_MSEXT_INT64, "__int64"),
    TOKEN_DATA(T_MSEXT_BASED, "_?" "_based"),
    TOKEN_DATA(T_MSEXT_DECLSPEC, "_?" "_declspec"),
    TOKEN_DATA(T_MSEXT_CDECL, "_?" "_cdecl"),
    TOKEN_DATA(T_MSEXT_FASTCALL, "_?" "_fastcall"),
    TOKEN_DATA(T_MSEXT_STDCALL, "_?" "_stdcall"),
    TOKEN_DATA(T_MSEXT_TRY , "__try"),
    TOKEN_DATA(T_MSEXT_EXCEPT, "__except"),
    TOKEN_DATA(T_MSEXT_FINALLY, "__finally"),
    TOKEN_DATA(T_MSEXT_LEAVE, "__leave"),
    TOKEN_DATA(T_MSEXT_INLINE, "_?" "_inline"),
    TOKEN_DATA(T_MSEXT_ASM, "_?" "_asm"),
    TOKEN_DATA(T_MSEXT_PP_REGION, POUNDDEF PPSPACE "region"),
    TOKEN_DATA(T_MSEXT_PP_ENDREGION, POUNDDEF PPSPACE "endregion"),
#endif // BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
    TOKEN_DATA(T_LONGINTLIT, INTEGER LONGINTEGER_SUFFIX),
    TOKEN_DATA(T_INTLIT, INTEGER INTEGER_SUFFIX "?"),
    TOKEN_DATA(T_FLOATLIT, 
        "(" DIGIT "*" Q(".") DIGIT "+" OR DIGIT "+" Q(".") ")" 
        EXPONENT "?" FLOAT_SUFFIX "?" OR
        DIGIT "+" EXPONENT FLOAT_SUFFIX "?"),
#if BOOST_WAVE_USE_STRICT_LEXER != 0
    TOKEN_DATA(T_IDENTIFIER, "([a-zA-Z_]" OR UNIVERSALCHAR ")([a-zA-Z0-9_]" OR UNIVERSALCHAR ")*"),
#else
    TOKEN_DATA(T_IDENTIFIER, "([a-zA-Z_$]" OR UNIVERSALCHAR ")([a-zA-Z0-9_$]" OR UNIVERSALCHAR ")*"),
#endif
    TOKEN_DATA(T_CCOMMENT, CCOMMENT),
    TOKEN_DATA(T_CPPCOMMENT, Q("/") Q("/[^\\n\\r]*") NEWLINEDEF ),
    TOKEN_DATA(T_CHARLIT, CHAR_SPEC "'" 
                "(" ESCAPESEQ OR "[^\\n\\r']" OR UNIVERSALCHAR ")+" "'"),
    TOKEN_DATA(T_STRINGLIT, CHAR_SPEC Q("\"") 
                "(" ESCAPESEQ OR "[^\\n\\r\"]" OR UNIVERSALCHAR ")*" Q("\"")),
    TOKEN_DATA(T_SPACE, BLANK "+"),
    TOKEN_DATA(T_SPACE2, "[\\v\\f]+"),
    TOKEN_DATA(T_CONTLINE, Q("\\") "\\n"), 
    TOKEN_DATA(T_NEWLINE, NEWLINEDEF),
    TOKEN_DATA(T_POUND_POUND, "##"),
    TOKEN_DATA(T_POUND_POUND_ALT, Q("%:") Q("%:")),
    TOKEN_DATA(T_POUND_POUND_TRIGRAPH, TRI("=") TRI("=")),
    TOKEN_DATA(T_POUND, "#"),
    TOKEN_DATA(T_POUND_ALT, Q("%:")),
    TOKEN_DATA(T_POUND_TRIGRAPH, TRI("=")),
    TOKEN_DATA(T_ANY_TRIGRAPH, TRI(Q("/"))),
    TOKEN_DATA(T_ANY, "."),     // this should be the last recognized token
    { token_id(0) }       // this should be the last entry
};

// C++ only token definitions
template <typename Iterator, typename Position>
typename lexertl<Iterator, Position>::lexer_data const 
lexertl<Iterator, Position>::init_data_cpp[INIT_DATA_CPP_SIZE] = 
{
    TOKEN_DATA(T_AND_ALT, "bitand"),
    TOKEN_DATA(T_ANDASSIGN_ALT, "and_eq"),
    TOKEN_DATA(T_ANDAND_ALT, "and"),
    TOKEN_DATA(T_OR_ALT, "bitor"),
    TOKEN_DATA(T_ORASSIGN_ALT, "or_eq"),
    TOKEN_DATA(T_OROR_ALT, "or"),
    TOKEN_DATA(T_XORASSIGN_ALT, "xor_eq"),
    TOKEN_DATA(T_XOR_ALT, "xor"),
    TOKEN_DATA(T_NOTEQUAL_ALT, "not_eq"),
    TOKEN_DATA(T_NOT_ALT, "not"),
    TOKEN_DATA(T_COMPL_ALT, "compl"),
#if BOOST_WAVE_SUPPORT_IMPORT_KEYWORD != 0
    TOKEN_DATA(T_IMPORT, "import"),
#endif
    TOKEN_DATA(T_ARROWSTAR, Q("->") Q("*")),
    TOKEN_DATA(T_DOTSTAR, Q(".") Q("*")),
    TOKEN_DATA(T_COLON_COLON, "::"),
    { token_id(0) }       // this should be the last entry
};

// pp-number specific token definitions
template <typename Iterator, typename Position>
typename lexertl<Iterator, Position>::lexer_data const 
lexertl<Iterator, Position>::init_data_pp_number[INIT_DATA_PP_NUMBER_SIZE] = 
{
    TOKEN_DATA(T_PP_NUMBER, PP_NUMBERDEF),
    { token_id(0) }       // this should be the last entry
};

#undef TOKEN_DATA

///////////////////////////////////////////////////////////////////////////////
// initialize lexertl lexer from C++ token regex's
template <typename Iterator, typename Position>
inline void
lexertl<Iterator, Position>::init_dfa(wave::language_support lang)
{
    if (has_compiled_dfa)
        return;
        
// if pp-numbers should be preferred, insert the corresponding rule first
    if (wave::need_prefer_pp_numbers(lang)) {
        for (int j = 0; 0 != init_data_pp_number[j].tokenid; ++j) {
            rules_.add(init_data_pp_number[j].tokenregex, 
                init_data_pp_number[j].tokenid);
        }
    }
        
// if in C99 mode, some of the keywords are not valid    
    if (!wave::need_c99(lang)) {
        for (int j = 0; 0 != init_data_cpp[j].tokenid; ++j) {
            rules_.add(init_data_cpp[j].tokenregex, 
                init_data_cpp[j].tokenid);
        }
    }
    
    for (int i = 0; 0 != init_data[i].tokenid; ++i) {
        rules_.add(init_data[i].tokenregex, init_data[i].tokenid);
    }

// generate minimized DFA
    ::lexertl::generator::build (rules_, state_machine_);
    ::lexertl::generator::minimise_dfa (state_machine_._dfa_alphabet,
	    state_machine_._dfa);

    has_compiled_dfa = true;
}

///////////////////////////////////////////////////////////////////////////////
// return next token from the input stream
template <typename Iterator, typename Position>
inline wave::token_id 
lexertl<Iterator, Position>::next_token(Iterator &first, Iterator const &last,
    string_type& token_value)
{
    size_t const* dfa_start = &state_machine_._dfa.front();
    size_t const* ptr = dfa_start + state_machine_._dfa_alphabet + ::lexertl::dfa_offset;
    Iterator curr = first;
    Iterator end_token = first;
    bool end_state = (*ptr != 0);
    size_t id = *(ptr + 1);

    while (curr != last && ptr != dfa_start) {
        size_t charset = state_machine_._lookup[*curr];
        ++curr;

        ptr = &dfa_start[ptr[charset] * (state_machine_._dfa_alphabet +
            ::lexertl::dfa_offset)];

        if (0 != *ptr) {
            end_state = true;
            id = *(ptr + 1);
            end_token = curr;
        }
    }

    if (end_state) {
	      // return longest match
	      string_type str(first, end_token);
	      token_value.swap(str);
	      first = end_token;
        return wave::token_id(id);
    }
    return T_EOF;
}

}   // namespace lexer

///////////////////////////////////////////////////////////////////////////////
template <typename Iterator, typename Position = wave::util::file_position_type>
class lexertl_functor 
:   public lexertl_input_interface<wave::cpplexer::lex_token<Position> >
{
public:
    typedef wave::util::position_iterator<Iterator, Position> iterator_type;
    typedef typename boost::detail::iterator_traits<Iterator>::value_type 
        char_type;
    typedef BOOST_WAVE_STRINGTYPE string_type;
    typedef wave::cpplexer::lex_token<Position> token_type;

    lexertl_functor(Iterator const &first_, Iterator const &last_, 
            Position const &pos_, wave::language_support language)
    :   first(first_, last_, pos_), language(language), at_eof(false)
    {
        lexer_.init_dfa(language);
    }
    ~lexertl_functor() {}

// get the next token from the input stream
    token_type get()
    {
        token_type token;

        if (!at_eof) {
            do {
            // generate and return the next token
            string_type token_val;
            Position pos = first.get_position();   // begin of token position
            wave::token_id id = lexer_.next_token(first, last, token_val);
            
                if (T_CONTLINE != id) {
                //  The cast should avoid spurious warnings about missing case labels 
                //  for the other token ids's.
                    switch (static_cast<unsigned int>(id)) {   
                    case T_IDENTIFIER:
                    // test identifier characters for validity (throws if 
                    // invalid chars found)
                        if (!(language & support_option_no_character_validation)) {
                            using boost::wave::cpplexer::impl::validate_identifier_name;
                            validate_identifier_name(token_val, 
                                pos.get_line(), pos.get_column(), pos.get_file()); 
                        }
                        break;

                    case T_STRINGLIT:
                    case T_CHARLIT:
                    // test literal characters for validity (throws if invalid 
                    // chars found)
                        if (language & support_option_convert_trigraphs) {
                            using wave::cpplexer::impl::convert_trigraphs;
                            token_val = convert_trigraphs(token_val); 
                        }
                        if (!(language & support_option_no_character_validation)) {
                            using wave::cpplexer::impl::validate_literal;
                            validate_literal(token_val, 
                                pos.get_line(), pos.get_column(), pos.get_file()); 
                        }
                        break;
                        
                    case T_LONGINTLIT:  // supported in C99 and long_long mode
                        if (!wave::need_long_long(language)) {
                        // syntax error: not allowed in C++ mode
                            BOOST_WAVE_LEXER_THROW(
                                boost::wave::cpplexer::lexing_exception, 
                                invalid_long_long_literal, token_val.c_str(), 
                                pos.get_line(), pos.get_column(), 
                                pos.get_file().c_str());
                        }
                        break;

#if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0
                    case T_PP_HHEADER:
                    case T_PP_QHEADER:
                    case T_PP_INCLUDE:
                    // convert to the corresponding ..._next token, if appropriate
                        {
                        // Skip '#' and whitespace and see whether we find an 
                        // 'include_next' here.
                            typename string_type::size_type start = token_val.find("include");
                            if (0 == token_val.compare(start, 12, "include_next", 12))
                                id = token_id(id | AltTokenType);
                            break;
                        }
#endif // BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0

                    case T_EOF:
                    // T_EOF is returned as a valid token, the next call will 
                    // return T_EOI, i.e. the actual end of input
                        at_eof = true;
                        token_val.clear();
                        break;
                        
                    case T_OR_TRIGRAPH:
                    case T_XOR_TRIGRAPH:
                    case T_LEFTBRACE_TRIGRAPH:
                    case T_RIGHTBRACE_TRIGRAPH:
                    case T_LEFTBRACKET_TRIGRAPH:
                    case T_RIGHTBRACKET_TRIGRAPH:
                    case T_COMPL_TRIGRAPH:
                    case T_POUND_TRIGRAPH:
                    case T_ANY_TRIGRAPH:
                        if (language & support_option_convert_trigraphs)
                        {
                            using wave::cpplexer::impl::convert_trigraph;
                            token_val = convert_trigraph(token_val);
                        }
                        break;
                    }
                    return token_type(id, token_val, pos);
                }
            
            // skip the T_CONTLINE token
            } while (true);
        }
        return token;       // return T_EOI
    }
    
    void set_position(Position const &pos) 
    { 
        // set position has to change the file name and line number only
        first.get_position().set_file(pos.get_file()); 
        first.get_position().set_line(pos.get_line()); 
    }

#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
    bool has_include_guards(std::string& guard_name) const { return false; }
#endif    

private:
    iterator_type first;
    iterator_type last;

    wave::language_support language;
    bool at_eof;
    
    static lexer::lexertl<iterator_type, Position> lexer_;
};

template <typename Iterator, typename Position>
lexer::lexertl<
    typename lexertl_functor<Iterator, Position>::iterator_type, Position> 
        lexertl_functor<Iterator, Position>::lexer_;

#undef INIT_DATA_SIZE
#undef INIT_DATA_CPP_SIZE
#undef INIT_DATA_PP_NUMBER_SIZE

///////////////////////////////////////////////////////////////////////////////
//  
//  The new_lexer_gen<>::new_lexer function (declared in lexertl_interface.hpp)
//  should be defined inline, if the lex_functor shouldn't be instantiated 
//  separately from the lex_iterator.
//
//  Separate (explicit) instantiation helps to reduce compilation time.
//
///////////////////////////////////////////////////////////////////////////////

#if BOOST_WAVE_SEPARATE_LEXER_INSTANTIATION != 0
#define BOOST_WAVE_FLEX_NEW_LEXER_INLINE
#else
#define BOOST_WAVE_FLEX_NEW_LEXER_INLINE inline
#endif 

///////////////////////////////////////////////////////////////////////////////
//
//  The 'new_lexer' function allows the opaque generation of a new lexer object.
//  It is coupled to the iterator type to allow to decouple the lexer/iterator 
//  configurations at compile time.
//
//  This function is declared inside the xlex_interface.hpp file, which is 
//  referenced by the source file calling the lexer and the source file, which
//  instantiates the lex_functor. But is is defined here, so it will be 
//  instantiated only while compiling the source file, which instantiates the 
//  lex_functor. While the xlex_interface.hpp file may be included everywhere,
//  this file (xlex_lexer.hpp) should be included only once. This allows
//  to decouple the lexer interface from the lexer implementation and reduces 
//  compilation time.
//
///////////////////////////////////////////////////////////////////////////////

template <typename Iterator, typename Position>
BOOST_WAVE_FLEX_NEW_LEXER_INLINE
wave::cpplexer::lex_input_interface<wave::cpplexer::lex_token<Position> > *
new_lexer_gen<Iterator, Position>::new_lexer(Iterator const &first,
    Iterator const &last, Position const &pos, wave::language_support language)
{
    return new lexertl_functor<Iterator, Position>(first, last, pos, language);
}

#undef BOOST_WAVE_FLEX_NEW_LEXER_INLINE

///////////////////////////////////////////////////////////////////////////////
}}}}   // namespace boost::wave::cpplexer::lexertl

#endif // !defined(BOOST_WAVE_LEXERTL_LEXER_HPP_INCLUDED)

