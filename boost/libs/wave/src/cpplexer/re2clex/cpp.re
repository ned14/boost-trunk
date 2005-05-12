/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library

    Copyright (c) 2001 Daniel C. Nuffer
    Copyright (c) 2001-2005 Hartmut Kaiser. 
    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    TODO: 
        It also may be necessary to add $ to identifiers, for asm. 
        handle errors better.
        have some easier way to parse strings instead of files (done) 
=============================================================================*/

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <boost/config.hpp>

#if defined(BOOST_HAS_UNISTD_H)
#include <unistd.h>
#else
#include <io.h>
#endif 

#include <boost/assert.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/wave/token_ids.hpp>
#include <boost/wave/cpplexer/re2clex/aq.hpp>
#include <boost/wave/cpplexer/re2clex/scanner.hpp>
#include <boost/wave/cpplexer/re2clex/cpp_re.hpp>

///////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_MSVC)
#pragma warning (disable: 4101)     // 'foo' : unreferenced local variable
#pragma warning (disable: 4102)     // 'foo' : unreferenced label
#endif

///////////////////////////////////////////////////////////////////////////////
#define BSIZE     196608

#define YYCTYPE   uchar
#define YYCURSOR  cursor
#define YYLIMIT   limit
#define YYMARKER  marker
#define YYFILL(n) {cursor = uchar_wrapper(fill(s, cursor), cursor.column);}

//#define RET(i)    {s->cur = cursor; return (i);}
#define RET(i)                                                                \
    {                                                                         \
        s->line += count_backslash_newlines(s, cursor);                       \
        s->curr_column = cursor.column;                                       \
        s->cur = cursor;                                                      \
        s->lim = limit;                                                       \
        s->ptr = marker;                                                      \
        return (i);                                                           \
    }                                                                         \
    /**/

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave {
namespace cpplexer {
namespace re2clex {

#define RE2C_ASSERT BOOST_ASSERT

int get_one_char(Scanner *s)
{
    if (s->fd != -1) {
    uchar val;
    
        if (read(s->fd, &val, sizeof(val)))
            return val;
    }
    else if (0 != s->act) {
        RE2C_ASSERT(s->first != 0 && s->last != 0);
        RE2C_ASSERT(s->first <= s->act && s->act <= s->last);
        if (s->act < s->last) 
            return *(s->act)++;
    }
    return -1;
}

std::ptrdiff_t rewind_stream (Scanner *s, int cnt)
{
    if (s->fd != -1) {
        return lseek(s->fd, cnt, SEEK_CUR);
    }
    else if (0 != s->act) {
        RE2C_ASSERT(s->first != 0 && s->last != 0);
        s->act += cnt;
        RE2C_ASSERT(s->first <= s->act && s->act <= s->last);
        return s->act - s->first;
    }
    return 0;
}

std::size_t get_first_eol_offset(Scanner* s)
{
    if (!AQ_EMPTY(s->eol_offsets))
    {
        return s->eol_offsets->queue[s->eol_offsets->head];
    }
    else
    {
        return (unsigned int)-1;
    }
}

void adjust_eol_offsets(Scanner* s, std::size_t adjustment)
{
    aq_queue q;
    std::size_t i;
    
    if (!s->eol_offsets)
        s->eol_offsets = aq_create();

    q = s->eol_offsets;

    if (AQ_EMPTY(q))
        return;

    i = q->head;
    while (i != q->tail)
    {
        if (adjustment > q->queue[i])
            q->queue[i] = 0;
        else
            q->queue[i] -= adjustment;
        ++i;
        if (i == q->max_size)
            i = 0;
    }
    if (adjustment > q->queue[i])
        q->queue[i] = 0;
    else
        q->queue[i] -= adjustment;
}

int count_backslash_newlines(Scanner *s, uchar *cursor)
{
    std::size_t diff, offset;
    int skipped = 0;
    
    /* figure out how many backslash-newlines skipped over unknowingly. */
    diff = cursor - s->bot;
    offset = get_first_eol_offset(s);
    while (offset <= diff && offset != (unsigned int)-1)
    {
        skipped++;
        aq_pop(s->eol_offsets);
        offset = get_first_eol_offset(s);
    }
    return skipped;
}

bool is_backslash(uchar *p, uchar *end, int &len)
{
    if (*p == '\\') {
        len = 1;
        return true;
    }
    else if (*p == '?' && *(p+1) == '?' && (p+2 < end && *(p+2) == '/')) {
        len = 3;
        return true;
    }
    return false;
}

uchar *fill(Scanner *s, uchar *cursor)
{
    using namespace std;    // some systems have memcpy etc. in namespace std
    if(!s->eof)
    {
        uchar* p;
        std::ptrdiff_t cnt = s->tok - s->bot;
        if(cnt)
        {
            memcpy(s->bot, s->tok, s->lim - s->tok);
            s->tok = s->bot;
            s->ptr -= cnt;
            cursor -= cnt;
            s->lim -= cnt;
            adjust_eol_offsets(s, cnt);
        }

        if((s->top - s->lim) < BSIZE)
        {
            uchar *buf = (uchar*) malloc(((s->lim - s->bot) + BSIZE)*sizeof(uchar));
            if (buf == 0)
            {
                using namespace std;      // some systems have printf in std
                if (0 != s->error_proc)
                    (*s->error_proc)(s, "Out of memory!");
                else 
                    printf("Out of memory!\n");
                    
                /* get the scanner to stop */
                *cursor = 0;
                return cursor;
            }

            memcpy(buf, s->tok, s->lim - s->tok);
            s->tok = buf;
            s->ptr = &buf[s->ptr - s->bot];
            cursor = &buf[cursor - s->bot];
            s->lim = &buf[s->lim - s->bot];
            s->top = &s->lim[BSIZE];
            free(s->bot);
            s->bot = buf;
        }

        if (s->fd != -1) {
            if((cnt = read(s->fd, (char*) s->lim, BSIZE)) != BSIZE)
            {
                s->eof = &s->lim[cnt]; *(s->eof)++ = '\0';
            }
        }
        else if (s->act != 0) {
            cnt = s->last - s->act;
            if (cnt > BSIZE)
                cnt = BSIZE;
            memcpy(s->lim, s->act, cnt);
            s->act += cnt;
            if (cnt != BSIZE) 
            {
                s->eof = &s->lim[cnt]; *(s->eof)++ = '\0';
            }
        }
        
        /* backslash-newline erasing time */

        /* first scan for backslash-newline and erase them */
        for (p = s->lim; p < s->lim + cnt - 2; ++p)
        {
            int len = 0;
            if (is_backslash(p, s->lim + cnt, len))
            {
                if (*(p+len) == '\n')
                {
                    int offset = len + 1;
                    memmove(p, p + offset, s->lim + cnt - p - offset);
                    cnt -= offset;
                    --p;
                    aq_enqueue(s->eol_offsets, p - s->bot + 1);    
                }
                else if (*(p+len) == '\r')
                {
                    if (*(p+len+1) == '\n')
                    {
                        int offset = len + 2;
                        memmove(p, p + offset, s->lim + cnt - p - offset);
                        cnt -= offset;
                        --p;
                    }
                    else
                    {
                        int offset = len + 1;
                        memmove(p, p + offset, s->lim + cnt - p - offset);
                        cnt -= offset;
                        --p;
                    }
                    aq_enqueue(s->eol_offsets, p - s->bot + 1);    
                }
            }
        }

        /* FIXME: the following code should be fixed to recognize correctly the 
                  trigraph backslash token */
                  
        /* check to see if what we just read ends in a backslash */
        if (cnt >= 2)
        {
            uchar last = s->lim[cnt-1];
            uchar last2 = s->lim[cnt-2];
            /* check \ EOB */
            if (last == '\\')
            {
                int next = get_one_char(s);
                /* check for \ \n or \ \r or \ \r \n straddling the border */
                if (next == '\n')
                {
                    --cnt; /* chop the final \, we've already read the \n. */
                    aq_enqueue(s->eol_offsets, cnt + (s->lim - s->bot));    
                }
                else if (next == '\r')
                {
                    int next2 = get_one_char(s);
                    if (next2 == '\n')
                    {
                        --cnt; /* skip the backslash */
                    }
                    else
                    {
                        /* rewind one, and skip one char */
                        rewind_stream(s, -1);
                        --cnt;
                    }
                    aq_enqueue(s->eol_offsets, cnt + (s->lim - s->bot));    
                }
                else if (next != -1) /* -1 means end of file */
                {
                    /* next was something else, so rewind the stream */
                    rewind_stream(s, -1);
                }
            }
            /* check \ \r EOB */
            else if (last == '\r' && last2 == '\\')
            {
                int next = get_one_char(s);
                if (next == '\n')
                {
                    cnt -= 2; /* skip the \ \r */
                }
                else
                {
                    /* rewind one, and skip two chars */
                    rewind_stream(s, -1);
                    cnt -= 2;
                }
                aq_enqueue(s->eol_offsets, cnt + (s->lim - s->bot));    
            }
            /* check \ \n EOB */
            else if (last == '\n' && last2 == '\\')
            {
                cnt -= 2;
                aq_enqueue(s->eol_offsets, cnt + (s->lim - s->bot));    
            }
        }
        
        s->lim += cnt;
        if (s->eof) /* eof needs adjusting if we erased backslash-newlines */
        {
            s->eof = s->lim;
            *(s->eof)++ = '\0';
        }
    }
    return cursor;
}

///////////////////////////////////////////////////////////////////////////////
//  Special wrapper class holding the current cursor position 
struct uchar_wrapper
{
    uchar_wrapper (uchar *base_cursor, unsigned int column = 1)
    :   base_cursor(base_cursor), column(column)
    {}
    
    uchar_wrapper& operator++() 
    {
        ++base_cursor;
        ++column;
        return *this;
    }
    
    uchar_wrapper& operator--() 
    {
        --base_cursor;
        --column;
        return *this;
    }
    
    uchar operator* () const
    {
        return *base_cursor;
    }
    
    operator uchar *() const
    {
        return base_cursor;
    }
    
    uchar *base_cursor;
    unsigned int column;
};

///////////////////////////////////////////////////////////////////////////////
boost::wave::token_id scan(Scanner *s)
{
    uchar_wrapper cursor (s->tok = s->cur, s->column = s->curr_column);
    uchar_wrapper marker (s->ptr);
    uchar_wrapper limit (s->lim);
        
/*!re2c
any                = [\t\v\f\r\n\040-\377];
OctalDigit         = [0-7];
Digit              = [0-9];
HexDigit           = [a-fA-F0-9];
Integer            = (("0" [xX] HexDigit+) | ("0" OctalDigit*) | ([1-9] Digit*));
ExponentPart       = [Ee] [+-]? Digit+;
FractionalConstant = (Digit* "." Digit+) | (Digit+ ".");
FloatingSuffix     = [fF] [lL]? | [lL] [fF]?;
IntegerSuffix      = [uU] [lL]? | [lL] [uU]?;
LongIntegerSuffix  = [uU] ("ll" | "LL") | ("ll" | "LL") [uU]?;
Backslash          = [\\] | "??/";
EscapeSequence     = Backslash ([abfnrtv?'"] | Backslash | "x" HexDigit+ | OctalDigit OctalDigit? OctalDigit?);
HexQuad            = HexDigit HexDigit HexDigit HexDigit;
UniversalChar      = Backslash ("u" HexQuad | "U" HexQuad HexQuad);
Newline            = "\r\n" | "\n" | "\r";
PPSpace            = ([ \t]|("/*"(any\[*]|Newline|("*"+(any\[*/]|Newline)))*"*"+"/"))*;
Pound              = "#" | "??=" | "%:";
*/

/*!re2c
    "/*"            { goto ccomment; }
    "//"            { goto cppcomment; }
    
    "asm"           { RET(T_ASM); }
    "auto"          { RET(T_AUTO); }
    "bool"          { RET(T_BOOL); }
    "break"         { RET(T_BREAK); }
    "case"          { RET(T_CASE); }
    "catch"         { RET(T_CATCH); }
    "char"          { RET(T_CHAR); }
    "class"         { RET(T_CLASS); }
    "const"         { RET(T_CONST); }
    "const_cast"    { RET(T_CONSTCAST); }
    "continue"      { RET(T_CONTINUE); }
    "default"       { RET(T_DEFAULT); }
    "delete"        { RET(T_DELETE); }
    "do"            { RET(T_DO); }
    "double"        { RET(T_DOUBLE); }
    "dynamic_cast"  { RET(T_DYNAMICCAST); }
    "else"          { RET(T_ELSE); }
    "enum"          { RET(T_ENUM); }
    "explicit"      { RET(T_EXPLICIT); }
    "export"        { RET(T_EXPORT); }
    "extern"        { RET(T_EXTERN); }
    "false"         { RET(T_FALSE); }
    "float"         { RET(T_FLOAT); }
    "for"           { RET(T_FOR); }
    "friend"        { RET(T_FRIEND); }
    "goto"          { RET(T_GOTO); }
    "if"            { RET(T_IF); }
    "inline"        { RET(T_INLINE); }
    "int"           { RET(T_INT); }
    "long"          { RET(T_LONG); }
    "mutable"       { RET(T_MUTABLE); }
    "namespace"     { RET(T_NAMESPACE); }
    "new"           { RET(T_NEW); }
    "operator"      { RET(T_OPERATOR); }
    "private"       { RET(T_PRIVATE); }
    "protected"     { RET(T_PROTECTED); }
    "public"        { RET(T_PUBLIC); }
    "register"      { RET(T_REGISTER); }
    "reinterpret_cast" { RET(T_REINTERPRETCAST); }
    "return"        { RET(T_RETURN); }
    "short"         { RET(T_SHORT); }
    "signed"        { RET(T_SIGNED); }
    "sizeof"        { RET(T_SIZEOF); }
    "static"        { RET(T_STATIC); }
    "static_cast"   { RET(T_STATICCAST); }
    "struct"        { RET(T_STRUCT); }
    "switch"        { RET(T_SWITCH); }
    "template"      { RET(T_TEMPLATE); }
    "this"          { RET(T_THIS); }
    "throw"         { RET(T_THROW); }
    "true"          { RET(T_TRUE); }
    "try"           { RET(T_TRY); }
    "typedef"       { RET(T_TYPEDEF); }
    "typeid"        { RET(T_TYPEID); }
    "typename"      { RET(T_TYPENAME); }
    "union"         { RET(T_UNION); }
    "unsigned"      { RET(T_UNSIGNED); }
    "using"         { RET(T_USING); }
    "virtual"       { RET(T_VIRTUAL); }
    "void"          { RET(T_VOID); }
    "volatile"      { RET(T_VOLATILE); }
    "wchar_t"       { RET(T_WCHART); }
    "while"         { RET(T_WHILE); }

    "__int8"        { RET(s->enable_ms_extensions ? T_MSEXT_INT8 : T_IDENTIFIER); }
    "__int16"       { RET(s->enable_ms_extensions ? T_MSEXT_INT16 : T_IDENTIFIER); }
    "__int32"       { RET(s->enable_ms_extensions ? T_MSEXT_INT32 : T_IDENTIFIER); }
    "__int64"       { RET(s->enable_ms_extensions ? T_MSEXT_INT64 : T_IDENTIFIER); }
    "_"? "_based"   { RET(s->enable_ms_extensions ? T_MSEXT_BASED : T_IDENTIFIER); }
    "_"? "_declspec" { RET(s->enable_ms_extensions ? T_MSEXT_DECLSPEC : T_IDENTIFIER); }
    "_"? "_cdecl"   { RET(s->enable_ms_extensions ? T_MSEXT_CDECL : T_IDENTIFIER); }
    "_"? "_fastcall" { RET(s->enable_ms_extensions ? T_MSEXT_FASTCALL : T_IDENTIFIER); }
    "_"? "_stdcall" { RET(s->enable_ms_extensions ? T_MSEXT_STDCALL : T_IDENTIFIER); }
    "__try"         { RET(s->enable_ms_extensions ? T_MSEXT_TRY : T_IDENTIFIER); }
    "__except"      { RET(s->enable_ms_extensions ? T_MSEXT_EXCEPT : T_IDENTIFIER); }
    "__finally"     { RET(s->enable_ms_extensions ? T_MSEXT_FINALLY : T_IDENTIFIER); }
    "__leave"       { RET(s->enable_ms_extensions ? T_MSEXT_LEAVE : T_IDENTIFIER); }
    "_"? "_inline"  { RET(s->enable_ms_extensions ? T_MSEXT_INLINE : T_IDENTIFIER); }
    "_"? "_asm"     { RET(s->enable_ms_extensions ? T_MSEXT_ASM : T_IDENTIFIER); }

    "{"             { RET(T_LEFTBRACE); }
    "??<"           { RET(T_LEFTBRACE_TRIGRAPH); }
    "<%"            { RET(T_LEFTBRACE_ALT); }
    "}"             { RET(T_RIGHTBRACE); }
    "??>"           { RET(T_RIGHTBRACE_TRIGRAPH); }
    "%>"            { RET(T_RIGHTBRACE_ALT); }
    "["             { RET(T_LEFTBRACKET); }
    "??("           { RET(T_LEFTBRACKET_TRIGRAPH); }
    "<:"            { RET(T_LEFTBRACKET_ALT); }
    "]"             { RET(T_RIGHTBRACKET); }
    "??)"           { RET(T_RIGHTBRACKET_TRIGRAPH); }
    ":>"            { RET(T_RIGHTBRACKET_ALT); }
    "#"             { RET(T_POUND); }
    "%:"            { RET(T_POUND_ALT); }
    "??="           { RET(T_POUND_TRIGRAPH); }
    "##"            { RET(T_POUND_POUND); }
    "#??="          { RET(T_POUND_POUND_TRIGRAPH); }
    "??=#"          { RET(T_POUND_POUND_TRIGRAPH); }
    "??=??="        { RET(T_POUND_POUND_TRIGRAPH); }
    "%:%:"          { RET(T_POUND_POUND_ALT); }
    "("             { RET(T_LEFTPAREN); }
    ")"             { RET(T_RIGHTPAREN); }
    ";"             { RET(T_SEMICOLON); }
    ":"             { RET(T_COLON); }
    "..."           { RET(T_ELLIPSIS); }
    "?"             { RET(T_QUESTION_MARK); }
    "::"            
        { 
            if (s->act_in_c99_mode) {
                --YYCURSOR;
                RET(T_COLON);
            }
            else {
                RET(T_COLON_COLON); 
            }
        }
    "."             { RET(T_DOT); }
    ".*" 
        { 
            if (s->act_in_c99_mode) {
                --YYCURSOR;
                RET(T_DOT);
            }
            else {
                RET(T_DOTSTAR); 
            }
        }
    "+"             { RET(T_PLUS); }
    "-"             { RET(T_MINUS); }
    "*"             { RET(T_STAR); }
    "/"             { RET(T_DIVIDE); }
    "%"             { RET(T_PERCENT); }
    "^"             { RET(T_XOR); }
    "??'"           { RET(T_XOR_TRIGRAPH); }
    "xor"           { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_XOR_ALT); }
    "&"             { RET(T_AND); }
    "bitand"        { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_AND_ALT); }
    "|"             { RET(T_OR); }
    "bitor"         { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_OR_ALT); }
    "??!"           { RET(T_OR_TRIGRAPH); }
    "~"             { RET(T_COMPL); }
    "??-"           { RET(T_COMPL_TRIGRAPH); }
    "compl"         { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_COMPL_ALT); }
    "!"             { RET(T_NOT); }
    "not"           { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_NOT_ALT); }
    "="             { RET(T_ASSIGN); }
    "<"             { RET(T_LESS); }
    ">"             { RET(T_GREATER); }
    "+="            { RET(T_PLUSASSIGN); }
    "-="            { RET(T_MINUSASSIGN); }
    "*="            { RET(T_STARASSIGN); }
    "/="            { RET(T_DIVIDEASSIGN); }
    "%="            { RET(T_PERCENTASSIGN); }
    "^="            { RET(T_XORASSIGN); }
    "xor_eq"        { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_XORASSIGN_ALT); }
    "??'="          { RET(T_XORASSIGN_TRIGRAPH); }
    "&="            { RET(T_ANDASSIGN); }
    "and_eq"        { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_ANDASSIGN_ALT); }
    "|="            { RET(T_ORASSIGN); }
    "or_eq"         { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_ORASSIGN_ALT); }
    "??!="          { RET(T_ORASSIGN_TRIGRAPH); }
    "<<"            { RET(T_SHIFTLEFT); }
    ">>"            { RET(T_SHIFTRIGHT); }
    ">>="           { RET(T_SHIFTRIGHTASSIGN); }
    "<<="           { RET(T_SHIFTLEFTASSIGN); }
    "=="            { RET(T_EQUAL); }
    "!="            { RET(T_NOTEQUAL); }
    "not_eq"        { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_NOTEQUAL_ALT); }
    "<="            { RET(T_LESSEQUAL); }
    ">="            { RET(T_GREATEREQUAL); }
    "&&"            { RET(T_ANDAND); }
    "and"           { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_ANDAND_ALT); }
    "||"            { RET(T_OROR); }
    "??!|"          { RET(T_OROR_TRIGRAPH); }
    "|??!"          { RET(T_OROR_TRIGRAPH); }
    "or"            { RET(s->act_in_c99_mode ? T_IDENTIFIER : T_OROR_ALT); }
    "??!??!"        { RET(T_OROR_TRIGRAPH); }
    "++"            { RET(T_PLUSPLUS); }
    "--"            { RET(T_MINUSMINUS); }
    ","             { RET(T_COMMA); }
    "->*"           
        { 
            if (s->act_in_c99_mode) {
                --YYCURSOR;
                RET(T_ARROW);
            }
            else {
                RET(T_ARROWSTAR); 
            }
        }
    "->"            { RET(T_ARROW); }
    "??/"           { RET(T_ANY_TRIGRAPH); }
    
    ([a-zA-Z_] | UniversalChar) ([a-zA-Z_0-9] | UniversalChar)*        
        { RET(T_IDENTIFIER); }
    
    Integer LongIntegerSuffix
        { RET(T_LONGINTLIT); }

    Integer IntegerSuffix?
        { RET(T_INTLIT); }

    ((FractionalConstant ExponentPart?) | (Digit+ ExponentPart)) FloatingSuffix?
        { RET(T_FLOATLIT); }
    
    "L"? (['] (EscapeSequence|any\[\n\r\\']|UniversalChar)+ ['])
        { RET(T_CHARLIT); }
    
    "L"? (["] (EscapeSequence|any\[\n\r\\"]|UniversalChar)* ["])
        { RET(T_STRINGLIT); }
    

    Pound PPSpace ( "include" | "include_next") PPSpace "<" (any\[\n\r>])+ ">" 
        { RET(T_PP_HHEADER); }

    Pound PPSpace ( "include" | "include_next") PPSpace "\"" (any\[\n\r"])+ "\"" 
        { RET(T_PP_QHEADER); } 

    Pound PPSpace ( "include" | "include_next") PPSpace
        { RET(T_PP_INCLUDE); } 

    Pound PPSpace "if"        { RET(T_PP_IF); }
    Pound PPSpace "ifdef"     { RET(T_PP_IFDEF); }
    Pound PPSpace "ifndef"    { RET(T_PP_IFNDEF); }
    Pound PPSpace "else"      { RET(T_PP_ELSE); }
    Pound PPSpace "elif"      { RET(T_PP_ELIF); }
    Pound PPSpace "endif"     { RET(T_PP_ENDIF); }
    Pound PPSpace "define"    { RET(T_PP_DEFINE); }
    Pound PPSpace "undef"     { RET(T_PP_UNDEF); }
    Pound PPSpace "line"      { RET(T_PP_LINE); }
    Pound PPSpace "error"     { RET(T_PP_ERROR); }
    Pound PPSpace "pragma"    { RET(T_PP_PRAGMA); }

    Pound PPSpace "warning"   { RET(T_PP_WARNING); }

    Pound PPSpace "region"    { RET(T_MSEXT_PP_REGION); }
    Pound PPSpace "endregion" { RET(T_MSEXT_PP_ENDREGION); }

    [ \t\v\f]+
        { RET(T_SPACE); }

    Newline
    {
        s->line++;
        cursor.column = 1;
        RET(T_NEWLINE);
    }

    "\000"
    {
        if(cursor != s->eof) 
        {
            using namespace std;      // some systems have printf in std
            if (0 != s->error_proc)
                (*s->error_proc)(s, "'\\000' in input stream");
            else
                printf("Error: 0 in file\n");
        }
        RET(T_EOF);
    }

    any
    {
        /* if (0 != s->error_proc)
            (*s->error_proc)(s, "Unexpected character: '%c'", *s->tok);
        else
            printf("unexpected character: '%c'\n", *s->tok);
        */
        RET(TOKEN_FROM_ID(*s->tok, UnknownTokenType));
    }
*/

ccomment:
/*!re2c
    "*/"            { RET(T_CCOMMENT); }
    
    Newline
    {
        /*if(cursor == s->eof) RET(T_EOF);*/
        /*s->tok = cursor; */
        s->line += count_backslash_newlines(s, cursor) +1;
        cursor.column = 1;
        goto ccomment;
    }

    any            { goto ccomment; }

    "\000"
    {
        using namespace std;      // some systems have printf in std
        if(cursor == s->eof) 
        {
            if (s->error_proc)
                (*s->error_proc)(s, "Unterminated comment");
            else
                printf("Error: Unterminated comment\n");
        }
        else
        {
            if (s->error_proc)
                (*s->error_proc)(s, "'\\000' in input stream");
            else
                printf("Error: 0 in file");
        }
        /* adjust cursor such next call returns T_EOF */
        --YYCURSOR;
        /* the comment is unterminated, but nevertheless its a comment */
        RET(T_CCOMMENT);
    }

*/

cppcomment:
/*!re2c
    Newline
    {
        /*if(cursor == s->eof) RET(T_EOF); */
        /*s->tok = cursor; */
        s->line++;
        cursor.column = 1;
        RET(T_CPPCOMMENT);
    }

    any            { goto cppcomment; }

    "\000"
    {
        using namespace std;      // some systems have printf in std
        if(cursor != s->eof) 
        {
            if (s->error_proc)
                (*s->error_proc)(s, "'\\000' in input stream");
            else
                printf("Error: 0 in file");
        }
        /* adjust cursor such next call returns T_EOF */
        --YYCURSOR;
        /* the comment is unterminated, but nevertheless its a comment */
        RET(T_CPPCOMMENT);
    }
*/

} /* end of scan */

///////////////////////////////////////////////////////////////////////////////
}   // namespace re2clex
}   // namespace cpplexer
}   // namespace wave
}   // namespace boost

#undef RET
#undef BSIZE 
#undef YYCTYPE
#undef YYCURSOR
#undef YYLIMIT
#undef YYMARKER
#undef YYFILL

