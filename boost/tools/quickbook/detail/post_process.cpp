/*=============================================================================
    Copyright (c) 2005 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "./post_process.hpp"
#include <boost/spirit/core.hpp>
#include <boost/bind.hpp>
#include <set>
#include <stack>
#include <cctype>

namespace quickbook
{
    using namespace boost::spirit;
    using boost::bind;
    typedef std::string::const_iterator iter_type;
    
    struct printer
    {
        printer(std::string& out, int& current_indent, int linewidth)
            : prev(0), out(out), current_indent(current_indent) , column(0)
            , in_string(false), linewidth(linewidth) {}
                
        void indent()
        {
            assert(current_indent >= 0); // this should not happen!
            for (int i = 0; i < current_indent; ++i)
                out += ' ';
            column = current_indent;
        }

        void cr()
        {
            out.erase(out.find_last_not_of(' ')+1); // trim trailing spaces
            out += '\n';
            indent();
        }
        
        bool line_is_empty() const
        {
            for (iter_type i = out.end()-(column-current_indent); i != out.end(); ++i)
            {
                if (*i != ' ')
                    return false;
            }
            return true;
        }
        
        void align_indent()
        {
            // make sure we are at the proper indent position
            if (column != current_indent)
            {
                if (column > current_indent)
                {
                    if (line_is_empty())
                    {
                        // trim just enough trailing spaces down to current_indent position
                        out.erase(out.end()-(column-current_indent), out.end());
                        column = current_indent;
                    }
                    else
                    {
                        // nope, line is not empty. do a hard CR
                        cr();
                    }
                }
                else
                {
                    // will this happen? (i.e. column <= current_indent)
                    while (column != current_indent) 
                    {
                        out += ' ';
                        ++column;
                    }
                }
            }
        }

        bool break_after(char prev)
        {
            switch (prev)
            {
                case '>':
                case '=':
                case ';':
                case ',':
                    // no '.' and '?'. the space algorithm below 
                    // already does the right thing.
                    return true;
                default:
                    return false;
            }
        }

        bool break_before(char ch)
        {
            switch (ch)
            {
                case '<':
                case '(':
                case '[':
                case '{':
                case '&':
                    return true;
                default:
                    return false;
            }
        }

        void print(char ch)
        {
            // what's the proper way to not break strings?
            if (ch == '"' && prev != '\\')
                in_string = !in_string; // don't break strings!

            if (!in_string && std::isspace(ch))
            {
                // we can break spaces if they are not inside strings
                if (!std::isspace(prev))
                {
                    if (column >= linewidth)
                    {
                        cr();
                        if (column == 0 && ch == ' ')
                        {
                            ++column;
                            out += ' ';
                        }
                    }
                    else
                    {
                        ++column;
                        out += ' ';
                    }
                }
            }
            else
            {
                // we can break tag boundaries and stuff after 
                // delimiters if they are not inside strings
                if (!in_string 
                    && column >= linewidth 
                    && (break_before(ch) || break_after(prev)))
                    cr();
                out += ch;
                ++column;
            }


            prev = ch;
        }

        void         
        print(iter_type f, iter_type l)
        {
            for (iter_type i = f; i != l; ++i)
                print(*i);
        }

        void         
        print_tag(iter_type f, iter_type l, bool is_flow_tag)
        {
            if (is_flow_tag)
            {
                print(f, l);
            }
            else
            {
                // This is not a flow tag, so, we're going to do a 
                // carriage return anyway. Let us remove extra right
                // spaces.
                std::string str(f, l);
                assert(f != l); // this should not happen
                iter_type i = str.end();
                while (i != str.begin() && std::isspace(*(i-1)))
                    --i;
                print(str.begin(), i);
            }            
        }

        char prev;
        std::string& out;
        int& current_indent;
        int column;
        bool in_string;
        int linewidth;
    };    
    
    struct tidy_compiler
    {
        tidy_compiler(std::string& out, int linewidth)
            : out(out), current_indent(0), printer_(out, current_indent, linewidth)
        {
            flow_tags.insert("anchor");
            flow_tags.insert("phrase");
            flow_tags.insert("literal");
            flow_tags.insert("entry");
            flow_tags.insert("emphasis");
            flow_tags.insert("ulink");
            flow_tags.insert("link");
            flow_tags.insert("varlistentry");
            flow_tags.insert("term");
            flow_tags.insert("functionname");
            flow_tags.insert("classname");
            flow_tags.insert("methodname");
            flow_tags.insert("enumname");
            flow_tags.insert("headername");
            flow_tags.insert("inlinemediaobject");
            flow_tags.insert("imageobject");
            flow_tags.insert("imagedata");
            flow_tags.insert("title");
            flow_tags.insert("xi");
            flow_tags.insert("firstname");
            flow_tags.insert("surname");
            flow_tags.insert("year");
            flow_tags.insert("holder");
            flow_tags.insert("sbr");
            flow_tags.insert("quote");
        }
        
        bool is_flow_tag(std::string const& tag)
        {
            return flow_tags.find(tag) != flow_tags.end();
        }

        std::set<std::string> flow_tags;
        std::stack<std::string> tags;
        std::string& out;
        int current_indent;
        printer printer_;
        std::string current_tag;
    };    
    
    struct tidy_grammar : grammar<tidy_grammar>
    {
        tidy_grammar(tidy_compiler& state, int indent)
            : state(state), indent(indent) {}

        template <typename Scanner>
        struct definition
        {
            definition(tidy_grammar const& self)
            {
                tag = (lexeme_d[+alnum_p])  [bind(&tidy_grammar::do_tag, &self, _1, _2)];

                code =
                        "<programlisting>"
                    >>  *(anychar_p - "</programlisting>")
                    >>  "</programlisting>"
                    ;

                // What's the business of lexeme_d['>' >> *ch_p(' ')]; ?
                // It is there to preserve the space after the tag that is
                // otherwise consumed by the space_p skipper.
                
                start_tag = '<' >> tag >> *(anychar_p - '>') >> lexeme_d['>' >> *ch_p(' ')];
                start_end_tag = 
                        '<' >> tag >> *(anychar_p - ('/' | ch_p('>'))) >> lexeme_d["/>" >> *ch_p(' ')]
                    |   "<?" >> tag >> *(anychar_p - '?') >> lexeme_d["?>" >> *ch_p(' ')]
                    |   "<!" >> tag >> *(anychar_p - '>') >> lexeme_d['>' >> *ch_p(' ')]
                    ;
                content = lexeme_d[ +(anychar_p - '<') ];
                end_tag = "</" >> +(anychar_p - '>') >> lexeme_d['>' >> *ch_p(' ')];

                markup = 
                        code            [bind(&tidy_grammar::do_code, &self, _1, _2)]
                    |   start_end_tag   [bind(&tidy_grammar::do_start_end_tag, &self, _1, _2)]
                    |   start_tag       [bind(&tidy_grammar::do_start_tag, &self, _1, _2)]
                    |   end_tag         [bind(&tidy_grammar::do_end_tag, &self, _1, _2)]
                    |   content         [bind(&tidy_grammar::do_content, &self, _1, _2)]
                    ;

                tidy = +markup;
            }

            rule<Scanner> const&
            start() { return tidy; }

            rule<Scanner>   tidy, tag, start_tag, start_end_tag,
                            content, end_tag, markup, code;
        };

        void do_code(iter_type f, iter_type l) const
        {
            state.out += '\n';
            state.out += std::string(f, l);
            state.out += '\n';
            state.printer_.indent();
        }

        void do_tag(iter_type f, iter_type l) const
        {
            state.current_tag = std::string(f, l);
        }

        void do_start_end_tag(iter_type f, iter_type l) const
        {
            bool is_flow_tag = state.is_flow_tag(state.current_tag);
            if (!is_flow_tag)
                state.printer_.align_indent();
            state.printer_.print_tag(f, l, is_flow_tag);
            if (!is_flow_tag)
                state.printer_.cr();
        }

        void do_start_tag(iter_type f, iter_type l) const
        {
            state.tags.push(state.current_tag);                     
            bool is_flow_tag = state.is_flow_tag(state.current_tag);
            if (!is_flow_tag)
                state.printer_.align_indent();
            state.printer_.print_tag(f, l, is_flow_tag);
            if (!is_flow_tag)
            {
                state.current_indent += indent;
                state.printer_.cr();
            }
        }

        void do_content(iter_type f, iter_type l) const
        {
            state.printer_.print(f, l);
        }

        void do_end_tag(iter_type f, iter_type l) const
        {
            bool is_flow_tag = state.is_flow_tag(state.tags.top());
            if (!is_flow_tag)
            {
                state.current_indent -= indent;
                state.printer_.align_indent();
            }
            state.printer_.print_tag(f, l, is_flow_tag);
            state.tags.pop();                     
        }
        
        tidy_compiler& state;
        int indent;
    };

    void post_process(
        std::string const& in
      , std::ostream& out
      , int indent
      , int linewidth)
    {
        if (indent == -1)
            indent = 2;         // set default to 2
        if (linewidth == -1)
            linewidth = 80;     // set default to 80

        std::string tidy;
        tidy_compiler state(tidy, linewidth);
        tidy_grammar g(state, indent);
        parse_info<iter_type> r = parse(in.begin(), in.end(), g, space_p);
        assert(r.full); // this should not happen!
        out << tidy;
    }
}

