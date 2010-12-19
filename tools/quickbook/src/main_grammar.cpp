/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "grammar_impl.hpp"
#include "actions_class.hpp"
#include "utils.hpp"
#include "scoped_block.hpp"
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_clear_actor.hpp>
#include <boost/spirit/include/classic_if.hpp>
#include <boost/spirit/include/classic_loops.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;

    template <typename Rule, typename Action>
    inline void
    simple_markup(
        Rule& simple
      , char mark
      , Action const& action
      , Rule const& close
    )
    {
        simple =
            mark >>
            (
                (
                    cl::graph_p                 // A single char. e.g. *c*
                    >> cl::eps_p(mark
                        >> (cl::space_p | cl::punct_p | cl::end_p))
                                                // space_p, punct_p or end_p
                )                               // must follow mark
            |
                (   cl::graph_p >>              // graph_p must follow mark
                    *(cl::anychar_p -
                        (   (cl::graph_p >> mark) // Make sure that we don't go
                        |   close                 // past a single block
                        )
                    ) >> cl::graph_p            // graph_p must precede mark
                    >> cl::eps_p(mark
                        >> (cl::space_p | cl::punct_p | cl::end_p))
                                                // space_p, punct_p or end_p
                )                               // must follow mark
            )                                   [action]
            >> mark
            ;
    }

    struct main_grammar_local
    {
        cl::rule<scanner>
                        top_level, blocks, paragraph_separator,
                        block_markup, block_markup_start,
                        code, code_line, blank_line,
                        space, blank, comment, dummy_block, hr,
                        list, ordered_list, list_item, hard_space, eol,
                        phrase_markup,
                        simple_phrase_end, phrase_end,
                        escape,
                        inline_code, simple_format,
                        simple_bold, simple_italic, simple_underline,
                        simple_teletype, template_,
                        code_block, macro,
                        template_args,
                        template_args_1_4, template_arg_1_4,
                        template_inner_arg_1_4, brackets_1_4,
                        template_args_1_5, template_arg_1_5,
                        template_inner_arg_1_5, brackets_1_5,
                        command_line_macro_identifier, command_line_phrase
                        ;

        cl::rule<scanner> block_keyword_rule;
        cl::rule<scanner> phrase_keyword_rule;
    };

    void quickbook_grammar::impl::init_main()
    {
        using detail::var;

        main_grammar_local& local = store_.create();

        block_skip_initial_spaces =
            *(cl::blank_p | local.comment) >> block_start
            ;

        block_start =
            local.top_level >> local.blank
            ;

        local.top_level
            =   local.blocks
            >>  *(
                    local.block_markup >> local.blocks
                |   local.paragraph_separator >> local.blocks
                |   common
                |   cl::space_p                 [actions.space_char]
                |   cl::anychar_p               [actions.plain_char]
                );

        local.blocks =
           *(   local.code
            |   local.list                      [actions.list]
            |   local.hr                        [actions.hr]
            |   +local.eol
            )
            ;

        local.paragraph_separator
            =   cl::eol_p
            >> *cl::blank_p
            >>  cl::eol_p                       [actions.inside_paragraph]
            ;

        local.space =
            *(cl::space_p | local.comment)
            ;

        local.blank =
            *(cl::blank_p | local.comment)
            ;

        local.eol = local.blank >> cl::eol_p
            ;

        // Follows after an alphanumeric identifier - ensures that it doesn't
        // match an empty space in the middle of the identifier.
        local.hard_space =
            (cl::eps_p - (cl::alnum_p | '_')) >> local.space
            ;

        local.comment =
            "[/" >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        local.dummy_block =
            '[' >> *(local.dummy_block | (cl::anychar_p - ']')) >> ']'
            ;

        local.hr =
            cl::str_p("----")
            >> *(cl::anychar_p - local.eol)
            >> +local.eol
            ;

        local.block_markup
            =   local.block_markup_start        [actions.inside_paragraph]
            >>  (   local.block_keyword_rule
                >>  (   (local.space >> ']' >> +local.eol)
                    |   cl::eps_p               [actions.error]
                    )
                |   cl::eps_p                   [actions.error]
                )
            ;

        local.block_markup_start
            =   '[' >> local.space
            >>  (   block_keyword_rules         [detail::assign_rule(local.block_keyword_rule)]
                >>  (cl::eps_p - (cl::alnum_p | '_'))
                |   block_symbol_rules          [detail::assign_rule(local.block_keyword_rule)]
                )
            ;
        
        local.code =
            (
                local.code_line
                >> *(*local.blank_line >> local.code_line)
            )                                   [actions.code]
            >> *local.eol
            ;

        local.code_line =
            cl::blank_p >> *(cl::anychar_p - cl::eol_p) >> cl::eol_p
            ;

        local.blank_line =
            *cl::blank_p >> cl::eol_p
            ;

        local.list =
            cl::eps_p(cl::ch_p('*') | '#') >>
           +(
                (*cl::blank_p
                >> (cl::ch_p('*') | '#'))       [actions.list_format]
                >> *cl::blank_p
                >> local.list_item
            )                                   [actions.list_item]
            ;

        local.list_item =
           *(   common
            |   (cl::anychar_p -
                    (   cl::eol_p >> *cl::blank_p
                    >>  (cl::ch_p('*') | '#' | cl::eol_p)
                    )
                )                               [actions.plain_char]
            )
            >> +local.eol
            ;

        local.phrase_end =
            ']' |
            cl::if_p(var(no_eols))
            [
                cl::eol_p >> *cl::blank_p >> cl::eol_p
                                                // Make sure that we don't go
            ]                                   // past a single block, except
            ;                                   // when preformatted.

        common =
                local.macro
            |   local.phrase_markup
            |   local.code_block
            |   local.inline_code
            |   local.simple_format
            |   local.escape
            |   local.comment
            ;

        local.macro =
            // must not be followed by alpha or underscore
            cl::eps_p(actions.macro
                >> (cl::eps_p - (cl::alpha_p | '_')))
            >> actions.macro                    [actions.do_macro]
            ;

        static const bool true_ = true;
        static const bool false_ = false;

        local.template_ =
            (
                cl::ch_p('`')                   [cl::assign_a(actions.template_escape,true_)]
                |
                cl::eps_p                       [cl::assign_a(actions.template_escape,false_)]
            )
            >>
            ( (
                (cl::eps_p(cl::punct_p)
                    >> actions.templates.scope
                )                               [cl::assign_a(actions.template_identifier)]
                                                [cl::clear_a(actions.template_args)]
                >> !local.template_args
            ) | (
                (actions.templates.scope
                    >> cl::eps_p(local.hard_space)
                )                               [cl::assign_a(actions.template_identifier)]
                                                [cl::clear_a(actions.template_args)]
                >> local.space
                >> !local.template_args
            ) )
            >> cl::eps_p(']')
            ;

        local.template_args =
            cl::if_p(qbk_since(105u)) [
                local.template_args_1_5
            ].else_p [
                local.template_args_1_4
            ]
            ;

        local.template_args_1_4 = local.template_arg_1_4 >> *(".." >> local.template_arg_1_4);

        local.template_arg_1_4 =
                (   cl::eps_p(*cl::blank_p >> cl::eol_p)
                                                [cl::assign_a(actions.template_block, true_)]
                |   cl::eps_p                   [cl::assign_a(actions.template_block, false_)]
                )
            >>  local.template_inner_arg_1_4    [actions.template_arg]
            ;

        local.template_inner_arg_1_4 =
            +(local.brackets_1_4 | (cl::anychar_p - (cl::str_p("..") | ']')))
            ;

        local.brackets_1_4 =
            '[' >> local.template_inner_arg_1_4 >> ']'
            ;

        local.template_args_1_5 = local.template_arg_1_5 >> *(".." >> local.template_arg_1_5);

        local.template_arg_1_5 =
                (   cl::eps_p(*cl::blank_p >> cl::eol_p)
                                                [cl::assign_a(actions.template_block, true_)]
                |   cl::eps_p                   [cl::assign_a(actions.template_block, false_)]
                )
            >>  (+(local.brackets_1_5 | ('\\' >> cl::anychar_p) | (cl::anychar_p - (cl::str_p("..") | '[' | ']'))))
                                                [actions.template_arg]
            ;

        local.template_inner_arg_1_5 =
            +(local.brackets_1_5 | ('\\' >> cl::anychar_p) | (cl::anychar_p - (cl::str_p('[') | ']')))
            ;

        local.brackets_1_5 =
            '[' >> local.template_inner_arg_1_5 >> ']'
            ;

        local.inline_code =
            '`' >>
            (
               *(cl::anychar_p -
                    (   '`'
                    |   (cl::eol_p >> *cl::blank_p >> cl::eol_p)
                                                // Make sure that we don't go
                    )                           // past a single block
                ) >> cl::eps_p('`')
            )                                   [actions.inline_code]
            >>  '`'
            ;

        local.code_block =
                (
                    "```" >>
                    (
                       *(cl::anychar_p - "```")
                            >> cl::eps_p("```")
                    )                           [actions.code_block]
                    >>  "```"
                )
            |   (
                    "``" >>
                    (
                       *(cl::anychar_p - "``")
                            >> cl::eps_p("``")
                    )                           [actions.code_block]
                    >>  "``"
                )
            ;

        local.simple_format =
                local.simple_bold
            |   local.simple_italic
            |   local.simple_underline
            |   local.simple_teletype
            ;

        local.simple_phrase_end = '[' | local.phrase_end;

        simple_markup(local.simple_bold,
            '*', actions.simple_bold, local.simple_phrase_end);
        simple_markup(local.simple_italic,
            '/', actions.simple_italic, local.simple_phrase_end);
        simple_markup(local.simple_underline,
            '_', actions.simple_underline, local.simple_phrase_end);
        simple_markup(local.simple_teletype,
            '=', actions.simple_teletype, local.simple_phrase_end);

        phrase =
           *(   common
            |   local.comment
            |   (cl::anychar_p - local.phrase_end)    [actions.plain_char]
            )
            ;

        local.phrase_markup
            =   '['
            >>  (   phrase_keyword_rules        [detail::assign_rule(local.phrase_keyword_rule)]
                >>  (cl::eps_p - (cl::alnum_p | '_'))
                >>  local.phrase_keyword_rule
                |   phrase_symbol_rules         [detail::assign_rule(local.phrase_keyword_rule)]
                >>  local.phrase_keyword_rule
                |   local.template_             [actions.do_template]
                |   cl::str_p("br")             [actions.break_]
                )
            >>  ']'
            ;

        local.escape =
                cl::str_p("\\n")                [actions.break_]
            |   cl::str_p("\\ ")                // ignore an escaped space
            |   '\\' >> cl::punct_p             [actions.raw_char]
            |   "\\u" >> cl::repeat_p(4) [cl::chset<>("0-9a-fA-F")]
                                                [actions.escape_unicode]
            |   "\\U" >> cl::repeat_p(8) [cl::chset<>("0-9a-fA-F")]
                                                [actions.escape_unicode]
            |   (
                    ("'''" >> !local.eol)       [actions.escape_pre]
                >>  *(cl::anychar_p - "'''")    [actions.raw_char]
                >>  cl::str_p("'''")            [actions.escape_post]
                )
            ;

        //
        // Simple phrase grammar
        //

        simple_phrase =
           *(   common
            |   local.comment
            |   (cl::anychar_p - ']')       [actions.plain_char]
            )
            ;

        //
        // Command line
        //

        command_line =
                *cl::space_p
            >>  local.command_line_macro_identifier
                                            [actions.macro_identifier]
            >>  *cl::space_p
            >>  (   '='
                >>  *cl::space_p
                >>  local.command_line_phrase
                                            [actions.macro_definition]
                >>  *cl::space_p
                )
            |   cl::eps_p                   [actions.macro_definition]
            ;

        local.command_line_macro_identifier =
            +(cl::anychar_p - (cl::space_p | ']' | '='))
            ;


        local.command_line_phrase =
           *(   common
            |   (cl::anychar_p - ']')       [actions.plain_char]
            )
            ;
    }
}
