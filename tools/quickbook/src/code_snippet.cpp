/*=============================================================================
    Copyright (c) 2006 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "block_tags.hpp"
#include "template_stack.hpp"
#include "actions.hpp"
#include "values.hpp"
#include "files.hpp"

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    struct code_snippet_actions
    {
        code_snippet_actions(std::vector<template_symbol>& storage,
                                file_ptr source_file,
                                char const* source_type)
            : last_code_pos(source_file->source.begin())
            , in_code(false)
            , callout_id(0)
            , snippet_stack()
            , storage(storage)
            , source_file(source_file)
            , source_type(source_type)
        {
            content.start(source_file);
        }

        void mark(string_iterator first, string_iterator last);
        void pass_thru(string_iterator first, string_iterator last);
        void escaped_comment(string_iterator first, string_iterator last);
        void start_snippet(string_iterator first, string_iterator last);
        void start_snippet_impl(std::string const&, string_iterator);
        void end_snippet(string_iterator first, string_iterator last);
        void end_snippet_impl(string_iterator);
        void callout(string_iterator first, string_iterator last);
        
        void append_code(string_iterator first, string_iterator last);
        void close_code();

        struct snippet_data
        {
            snippet_data(std::string const& id, int callout_base_id)
                : id(id)
                , callout_base_id(callout_base_id)
                , start_code(false)
            {}
            
            std::string id;
            int callout_base_id;
            bool start_code;
            std::string::const_iterator source_pos;
            mapped_file_builder::pos start_pos;
            value_builder callouts;
            boost::shared_ptr<snippet_data> next;
        };
        
        void push_snippet_data(std::string const& id, int callout_base_id,
                std::string::const_iterator pos)
        {
            boost::shared_ptr<snippet_data> new_snippet(
                new snippet_data(id, callout_base_id));
            new_snippet->next = snippet_stack;
            snippet_stack = new_snippet;
            snippet_stack->start_code = in_code;
            snippet_stack->source_pos = pos;
            snippet_stack->start_pos = content.get_pos();
        }

        boost::shared_ptr<snippet_data> pop_snippet_data()
        {
            boost::shared_ptr<snippet_data> snippet(snippet_stack);
            snippet_stack = snippet->next;
            snippet->next.reset();
            return snippet;
        }

        mapped_file_builder content;
        std::string::const_iterator mark_begin, mark_end;
        std::string::const_iterator last_code_pos;
        bool in_code;
        int callout_id;
        boost::shared_ptr<snippet_data> snippet_stack;
        std::vector<template_symbol>& storage;
        file_ptr source_file;
        char const* const source_type;
    };

    struct python_code_snippet_grammar
        : cl::grammar<python_code_snippet_grammar>
    {
        typedef code_snippet_actions actions_type;
  
        python_code_snippet_grammar(actions_type & actions)
            : actions(actions)
        {}

        template <typename Scanner>
        struct definition
        {
            typedef code_snippet_actions actions_type;
            
            definition(python_code_snippet_grammar const& self)
            {

                actions_type& actions = self.actions;
            
                start_ = *code_elements;

                identifier =
                    (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
                    ;

                code_elements =
                        start_snippet               [boost::bind(&actions_type::start_snippet, &actions, _1, _2)]
                    |   end_snippet                 [boost::bind(&actions_type::end_snippet, &actions, _1, _2)]
                    |   escaped_comment             [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)]
                    |   pass_thru_comment           [boost::bind(&actions_type::pass_thru, &actions, _1, _2)]
                    |   ignore                      [boost::bind(&actions_type::append_code, &actions, _1, _2)]
                    |   cl::anychar_p
                    ;

                start_snippet =
                        *cl::blank_p
                    >>  !(cl::eol_p >> *cl::blank_p)
                    >>  "#["
                    >>  *cl::blank_p
                    >>  identifier                  [boost::bind(&actions_type::mark, &actions, _1, _2)]
                    >>  *(cl::anychar_p - cl::eol_p)
                    ;

                end_snippet =
                        *cl::blank_p
                    >>  !(cl::eol_p >> *cl::blank_p)
                    >>  "#]"
                    >>  *(cl::anychar_p - cl::eol_p)
                    ;

                ignore
                    =   cl::confix_p(
                            *cl::blank_p >> "#<-",
                            *cl::anychar_p,
                            "#->" >> *cl::blank_p >> (cl::eol_p | cl::end_p)
                        )
                    |   cl::confix_p(
                            "\"\"\"<-\"\"\"",
                            *cl::anychar_p,
                            "\"\"\"->\"\"\""
                        )
                    |   cl::confix_p(
                            "\"\"\"<-",
                            *cl::anychar_p,
                            "->\"\"\""
                        )
                    ;

                escaped_comment =
                        cl::confix_p(
                            *cl::space_p >> "#`",
                            (*cl::anychar_p)        [boost::bind(&actions_type::mark, &actions, _1, _2)],
                            (cl::eol_p | cl::end_p)
                        )
                    |   cl::confix_p(
                            *cl::space_p >> "\"\"\"`",
                            (*cl::anychar_p)        [boost::bind(&actions_type::mark, &actions, _1, _2)],
                            "\"\"\""
                        )
                    ;

                // Note: Unlike escaped_comment and ignore, this doesn't
                // swallow preceeding whitespace.
                pass_thru_comment
                    =   "#=" >> (cl::eps_p - '=')
                    >>  (   *(cl::anychar_p - cl::eol_p)
                        >>  (cl::eol_p | cl::end_p)
                        )                           [boost::bind(&actions_type::mark, &actions, _1, _2)]
                    |   cl::confix_p(
                            "\"\"\"=" >> (cl::eps_p - '='),
                            (*cl::anychar_p)        [boost::bind(&actions_type::mark, &actions, _1, _2)],
                            "\"\"\""
                        )
                    ;
            }

            cl::rule<Scanner>
                start_, identifier, code_elements, start_snippet, end_snippet,
                escaped_comment, pass_thru_comment, ignore;

            cl::rule<Scanner> const&
            start() const { return start_; }
        };

        actions_type& actions;
    };  

    struct cpp_code_snippet_grammar
        : cl::grammar<cpp_code_snippet_grammar>
    {
        typedef code_snippet_actions actions_type;
  
        cpp_code_snippet_grammar(actions_type & actions)
            : actions(actions)
        {}

        template <typename Scanner>
        struct definition
        {
            definition(cpp_code_snippet_grammar const& self)
            {
                actions_type& actions = self.actions;
            
                start_ = *code_elements;

                identifier =
                    (cl::alpha_p | '_') >> *(cl::alnum_p | '_')
                    ;

                code_elements =
                        start_snippet               [boost::bind(&actions_type::start_snippet, &actions, _1, _2)]
                    |   end_snippet                 [boost::bind(&actions_type::end_snippet, &actions, _1, _2)]
                    |   escaped_comment             [boost::bind(&actions_type::escaped_comment, &actions, _1, _2)]
                    |   ignore                      [boost::bind(&actions_type::append_code, &actions, _1, _2)]
                    |   pass_thru_comment           [boost::bind(&actions_type::pass_thru, &actions, _1, _2)]
                    |   line_callout                [boost::bind(&actions_type::callout, &actions, _1, _2)]
                    |   inline_callout              [boost::bind(&actions_type::callout, &actions, _1, _2)]
                    |   cl::anychar_p
                    ;

                start_snippet =
                            *cl::blank_p
                        >>  !(cl::eol_p >> *cl::blank_p)
                        >>  "//["
                        >>  *cl::blank_p
                        >>  identifier              [boost::bind(&actions_type::mark, &actions, _1, _2)]
                        >>  *(cl::anychar_p - cl::eol_p)
                    |
                            *cl::blank_p
                        >>  cl::eol_p
                        >>  *cl::blank_p
                        >>  "/*["
                        >>  *cl::space_p
                        >>  identifier              [boost::bind(&actions_type::mark, &actions, _1, _2)]
                        >>  *cl::space_p
                        >>  "*/"
                        >>  *cl::blank_p
                        >>  cl::eps_p(cl::eol_p)
                    |
                            "/*["
                        >>  *cl::space_p
                        >>  identifier              [boost::bind(&actions_type::mark, &actions, _1, _2)]
                        >>  *cl::space_p
                        >>  "*/"
                    ;

                end_snippet =
                            *cl::blank_p
                        >>  !(cl::eol_p >> *cl::blank_p)
                        >>  "//]"
                        >>  *(cl::anychar_p - cl::eol_p)
                    |
                            *cl::blank_p
                        >>  cl::eol_p
                        >>  *cl::blank_p
                        >>  "/*]*/"
                        >>  *cl::blank_p
                        >>  cl::eps_p(cl::eol_p)
                    |
                            "/*[*/"
                    ;

                inline_callout
                    =   cl::confix_p(
                            "/*<" >> *cl::space_p,
                            (*cl::anychar_p)        [boost::bind(&actions_type::mark, &actions, _1, _2)],
                            ">*/"
                        )
                        ;

                line_callout
                    =   cl::confix_p(
                            "/*<<" >> *cl::space_p,
                            (*cl::anychar_p)        [boost::bind(&actions_type::mark, &actions, _1, _2)],
                            ">>*/"
                        )
                    >>  *cl::space_p
                    ;

                ignore
                    =   cl::confix_p(
                            *cl::blank_p >> "//<-",
                            *cl::anychar_p,
                            "//->"
                        )
                    >>  *cl::blank_p
                    >>  cl::eol_p
                    |   cl::confix_p(
                            "/*<-*/",
                            *cl::anychar_p,
                            "/*->*/"
                        )
                    |   cl::confix_p(
                            "/*<-",
                            *cl::anychar_p,
                            "->*/"
                        )
                    ;

                escaped_comment
                    =   cl::confix_p(
                            *cl::space_p >> "//`",
                            (*cl::anychar_p)        [boost::bind(&actions_type::mark, &actions, _1, _2)],
                            (cl::eol_p | cl::end_p)
                        )
                    |   cl::confix_p(
                            *cl::space_p >> "/*`",
                            (*cl::anychar_p)        [boost::bind(&actions_type::mark, &actions, _1, _2)],
                            "*/"
                        )
                    ;

                // Note: Unlike escaped_comment and ignore, this doesn't
                // swallow preceeding whitespace.
                pass_thru_comment
                    =   "//=" >> (cl::eps_p - '=')
                    >>  (   *(cl::anychar_p - cl::eol_p)
                        >>  (cl::eol_p | cl::end_p)
                        )                           [boost::bind(&actions_type::mark, &actions, _1, _2)]
                    |   cl::confix_p(
                            "/*=" >> (cl::eps_p - '='),
                            (*cl::anychar_p)        [boost::bind(&actions_type::mark, &actions, _1, _2)],
                            "*/"
                        )
                    ;
            }

            cl::rule<Scanner>
            start_, identifier, code_elements, start_snippet, end_snippet,
                escaped_comment, pass_thru_comment, inline_callout, line_callout, ignore;

            cl::rule<Scanner> const&
            start() const { return start_; }
        };

        actions_type& actions;
    };

    int load_snippets(
        fs::path const& filename
      , std::vector<template_symbol>& storage   // snippets are stored in a
                                                // vector of template_symbols
      , std::string const& extension
      , value::tag_type load_type)
    {
        assert(load_type == block_tags::include ||
            load_type == block_tags::import);

        bool is_python = extension == ".py";
        code_snippet_actions a(storage, load(filename, qbk_version_n), is_python ? "[python]" : "[c++]");

        string_iterator first(a.source_file->source.begin());
        string_iterator last(a.source_file->source.end());

        cl::parse_info<string_iterator> info;

        if(is_python) {
            info = boost::spirit::classic::parse(first, last, python_code_snippet_grammar(a));
        }
        else {
            info = boost::spirit::classic::parse(first, last, cpp_code_snippet_grammar(a));
        }

        assert(info.full);

        return 0;
    }

    void code_snippet_actions::append_code(string_iterator first, string_iterator last)
    {
        assert(last_code_pos <= first);

        if(snippet_stack) {
            if (last_code_pos != first) {
                if (!in_code)
                {
                    content.add("\n\n", last_code_pos);
                    content.add(source_type, last_code_pos);
                    content.add("```\n", last_code_pos);

                    in_code = true;
                }

                content.add(last_code_pos, first);
            }
        }
        
        last_code_pos = last;
    }

    void code_snippet_actions::close_code()
    {
        if (!snippet_stack) return;
    
        if (in_code)
        {
            content.add("\n```\n\n", last_code_pos);
            in_code = false;
        }
    }

    void code_snippet_actions::mark(string_iterator first, string_iterator last)
    {
        mark_begin = first;
        mark_end = last;
    }

    void code_snippet_actions::pass_thru(string_iterator first, string_iterator last)
    {
        if(!snippet_stack) return;
        append_code(first, last);

        if (!in_code)
        {
            content.add("\n\n", first);
            content.add(source_type, first);
            content.add("```\n", first);
            in_code = true;
        }

        content.add(mark_begin, mark_end);
    }

    void code_snippet_actions::callout(string_iterator first, string_iterator last)
    {
        if(!snippet_stack) return;
        append_code(first, last);

        if (!in_code)
        {
            content.add("\n\n", first);
            content.add(source_type, first);
            content.add("```\n", first);
            in_code = true;
        }

        content.add(
            "``[[callout" + boost::lexical_cast<std::string>(callout_id) + "]]``",
            first);
    
        snippet_stack->callouts.insert(qbk_value(source_file, mark_begin, mark_end, template_tags::block));
        ++callout_id;
    }

    void code_snippet_actions::escaped_comment(string_iterator first, string_iterator last)
    {
        append_code(first, last);
        close_code();

        if (mark_begin != mark_end)
        {
            if (!snippet_stack)
            {
                start_snippet_impl("!", first);
            }
    
            snippet_data& snippet = *snippet_stack;

            content.add("\n", mark_begin);
            content.unindent_and_add(mark_begin, mark_end);

            if (snippet.id == "!")
            {
                end_snippet_impl(last);
            }
        }
    }

    void code_snippet_actions::start_snippet(string_iterator first, string_iterator last)
    {
        append_code(first, last);
        start_snippet_impl(std::string(mark_begin, mark_end), first);
    }

    void code_snippet_actions::end_snippet(string_iterator first, string_iterator last)
    {
        // TODO: Error?
        if(!snippet_stack) return;
        append_code(first, last);
        end_snippet_impl(first);
    }

    void code_snippet_actions::start_snippet_impl(std::string const& id,
            string_iterator position)
    {
        push_snippet_data(id, callout_id, position);
    }

    void code_snippet_actions::end_snippet_impl(string_iterator position)
    {
        boost::shared_ptr<snippet_data> snippet = pop_snippet_data();
        value callouts = snippet->callouts.release();

        mapped_file_builder f;
        f.start(source_file);
        if (snippet->start_code) {
            f.add("\n\n", snippet->source_pos);
            f.add(source_type, snippet->source_pos);
            f.add("```\n", snippet->source_pos);
        }
        f.add(content, snippet->start_pos, content.get_pos());
        if (in_code) {
            f.add("\n```\n\n", position);
        }

        std::vector<std::string> params;
        int i = 0;
        for(value::iterator it = callouts.begin(); it != callouts.end(); ++it)
        {
            params.push_back("[callout" + boost::lexical_cast<std::string>(snippet->callout_base_id + i) + "]");
            ++i;
        }

        file_ptr body = f.release();

        value_builder builder;
        builder.set_tag(template_tags::snippet);
        builder.insert(qbk_value(body, body->source.begin(), body->source.end(),
            template_tags::block));
        builder.insert(callouts);

        template_symbol symbol(snippet->id, params, builder.release());
        storage.push_back(symbol);

        // Copy the snippet's callouts to its parent

        if(snippet_stack)
        {
            snippet_stack->callouts.extend(callouts);
        }
    }
}
