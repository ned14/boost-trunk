/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <numeric>
#include <functional>
#include <algorithm>
#include <boost/filesystem/v3/convenience.hpp>
#include <boost/filesystem/v3/fstream.hpp>
#include <boost/range/algorithm/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/distance.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "quickbook.hpp"
#include "actions.hpp"
#include "utils.hpp"
#include "markups.hpp"
#include "actions_class.hpp"
#include "grammar.hpp"
#include "input_path.hpp"
#include "template_tags.hpp"
#include "table_tags.hpp"

namespace quickbook
{
    char const* quickbook_get_date = "__quickbook_get_date__";
    char const* quickbook_get_time = "__quickbook_get_time__";

    int qbk_major_version = -1;
    int qbk_minor_version = -1;
    unsigned qbk_version_n = 0; // qbk_major_version * 100 + qbk_minor_version

    void assign_qbk_version::operator()(int value) const { v_ = value; }

    namespace {
        std::string fully_qualified_id(std::string const& library_id,
            std::string const& qualified_section_id,
            std::string const& section_id)
        {
            std::string id = library_id;
            if(!id.empty() && !qualified_section_id.empty()) id += '.';
            id += qualified_section_id;
            if(!id.empty() && !section_id.empty()) id += '.';
            id += section_id;
            return id;
        }
    }

    // Handles line-breaks (DEPRECATED!!!)
    void break_action::operator()(iterator first, iterator) const
    {
        if(!actions.output_pre(phrase)) return;

        file_position const pos = first.get_position();
        if(*first == '\\')
        {
            detail::outwarn(actions.filename, pos.line)
                << "in column:" << pos.column << ", "
                << "'\\n' is deprecated, pleases use '[br]' instead" << ".\n";
        }

        if(!actions.warned_about_breaks)
        {
            detail::outwarn(actions.filename, pos.line)
                << "line breaks generate invalid boostbook"
                << "    (will only note first occurrence)."
                << "\n";

            actions.warned_about_breaks = true;
        }
            
        phrase << break_mark;
    }

    void error_message_action::operator()(iterator first, iterator last) const
    {
        file_position const pos = first.get_position();

        std::string value(first, last);
        std::string formatted_message = message;
        boost::replace_all(formatted_message, "%s", value);
        boost::replace_all(formatted_message, "%c",
            boost::lexical_cast<std::string>(pos.column));

        detail::outerr(actions.filename, pos.line)
            << formatted_message << std::endl;
        ++actions.error_count;
    }

    void error_action::operator()(iterator first, iterator /*last*/) const
    {
        file_position const pos = first.get_position();
        detail::outerr(actions.filename, pos.line)
            << "Syntax Error near column " << pos.column << ".\n";
        ++actions.error_count;
    }

    void tagged_action::operator()(iterator, iterator) const
    {
        if(!actions.output_pre(out)) return;

        value_consumer values = actions.values.get();
        out << pre << values.consume().get_boostbook() << post;
    }

    void phrase_action::operator()() const
    {
        if(!actions.output_pre(phrase)) return;

        std::string str;
        phrase.swap(str);
        out << pre << str << post;
    }

    void implicit_paragraph_action::operator()() const
    {
        if(actions.suppress) return;
    
        std::string str;
        phrase.swap(str);

        // TODO: Use spirit to do this?

        std::string::const_iterator
            pos = str.begin(),
            end = str.end();

        while(pos != end && (
            *pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r'))
        {
            ++pos;
        }

        if(pos != end) {
            out << pre << str;
            // TODO: Is this right place?
            actions.output_pre(out);
            out << post;
        }
    }
    
    namespace {
        void write_bridgehead(collector& out, int level,
            std::string const& str, std::string const& id, std::string const& linkend)
        {
            out << "<bridgehead renderas=\"sect" << level << "\"";
            if(!id.empty()) out << " id=\"" << id << "\"";
            out << ">";
            if(!linkend.empty()) out << "<link linkend=\"" << linkend << "\">";
            out << str;
            if(!linkend.empty()) out << "</link>";
            out << "</bridgehead>";
        }
    }

    void header_action::operator()(iterator first, iterator last) const
    {
        if(actions.suppress) return;

        std::string str;
        phrase.swap(str);
        
        value_consumer values = actions.values.get();

        std::string anchor;

        if (qbk_version_n < 103) // version 1.2 and below
        {
            anchor = section_id + '.' +
                detail::make_identifier(str.begin(), str.end());
        }
        else
        {
            std::string id =
                values.is(general_tags::element_id) ? values.consume().get_quickbook() :
                qbk_version_n >= 106 ? detail::make_identifier(first, last) :
                detail::make_identifier(str.begin(), str.end());

            anchor =
                fully_qualified_id(library_id, qualified_section_id, id);
        }

        actions.output_pre(out);
        actions.anchors.swap(actions.saved_anchors);
        actions.anchors.push_back(anchor);
        actions.output_pre(out);
        
        std::string linkend = qbk_version_n < 103 ? std::string() : anchor;
        write_bridgehead(out, level, str, anchor + "-heading", linkend);
    }

    void generic_header_action::operator()(iterator first, iterator last) const
    {
        if(actions.suppress) return;

        int level_ = section_level + 2;     // section_level is zero-based. We need to use a
                                            // one-based heading which is one greater
                                            // than the current. Thus: section_level + 2.
        if (level_ > 6)                     // The max is h6, clip it if it goes
            level_ = 6;                     // further than that
        std::string str;
        phrase.swap(str);

        value_consumer values = actions.values.get();

        std::string id =
            values.is(general_tags::element_id) ? values.consume().get_quickbook() :
            qbk_version_n >= 106 ? detail::make_identifier(first, last) :
            detail::make_identifier(str.begin(), str.end());

        std::string anchor =
            fully_qualified_id(library_id, qualified_section_id, id);

        actions.output_pre(out);
        actions.anchors.swap(actions.saved_anchors);
        actions.anchors.push_back(anchor);
        actions.output_pre(out);

        write_bridgehead(out, level_, str, anchor + "-heading", anchor);
    }

    void simple_phrase_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(out)) return;

        out << pre;
        std::string str(first, last);
        if (std::string const* ptr = find(macro, str.c_str()))
        {
            out << *ptr;
        }
        else
        {
            while (first != last)
                detail::print_char(*first++, out.get());
        }
        out << post;
    }

    void cond_phrase_action_pre::operator()(iterator first, iterator last) const
    {
        std::string str(first, last);
        condition = find(macro, str.c_str());
    }

    cond_phrase_push::cond_phrase_push(quickbook::actions& actions)
        : actions(actions)
        , saved_suppress(actions.suppress)
    {
        actions.suppress = actions.suppress || !actions.condition;
    }
    
    cond_phrase_push::~cond_phrase_push()
    {
        actions.suppress = saved_suppress;
    }

    void list_action::operator()(iterator first, iterator last) const
    {
        if(actions.suppress) return;
    
        BOOST_ASSERT(!list_marks.empty()); // there must be at least one item in the stack
        out << list_buffer.str();
        list_buffer.clear();

        while (!list_marks.empty())
        {
            char mark = list_marks.top().first;
            list_marks.pop();
            out << std::string((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
            if (list_marks.size() >= 1)
                out << "</listitem>";
        }

        list_indent = -1; // reset
    }

    void list_format_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(out)) return;
    
        int new_indent = 0;
        while (first != last && (*first == ' ' || *first == '\t'))
        {
            char mark = *first++;
            if (mark == ' ')
            {
                ++new_indent;
            }
            else // must be a tab
            {
                BOOST_ASSERT(mark == '\t');
                // hardcoded tab to 4 for now
                new_indent = ((new_indent + 4) / 4) * 4;
            }
        }

        char mark = *first;
        BOOST_ASSERT(mark == '#' || mark == '*'); // expecting a mark

        if (list_indent == -1) // the very start
        {
            BOOST_ASSERT(new_indent == 0);
        }

        if (new_indent > list_indent)
        {
            list_indent = new_indent;
            list_marks.push(mark_type(mark, list_indent));
            if (list_marks.size() > 1)
            {
                // Make this new list a child of the previous list.
                // The previous listelem has already ended so we erase
                // "</listitem>" to accomodate this sub-list. We'll close
                // the listelem later.

                std::string str;
                out.swap(str);
                std::string::size_type pos = str.rfind("</listitem>");
                BOOST_ASSERT(pos <= str.size());
                str.erase(str.begin()+pos, str.end());
                out << str;
            }
            out << std::string((mark == '#') ? "<orderedlist>\n" : "<itemizedlist>\n");
        }

        else if (new_indent < list_indent)
        {
            BOOST_ASSERT(!list_marks.empty());
            list_indent = new_indent;

            while (!list_marks.empty() && (list_indent < list_marks.top().second))
            {
                char mark = list_marks.top().first;
                list_marks.pop();
                out << std::string((mark == '#') ? "\n</orderedlist>" : "\n</itemizedlist>");
                if (list_marks.size() >= 1)
                    out << "</listitem>";
            }
        }

        if (mark != list_marks.top().first) // new_indent == list_indent
        {
            file_position const pos = first.get_position();
            detail::outerr(actions.filename, pos.line)
                << "Illegal change of list style near column " << pos.column << ".\n";
            detail::outwarn(actions.filename, pos.line)
                << "Ignoring change of list style" << std::endl;
            ++error_count;
        }
    }

    // TODO: No need to check suppress since this is only used in the syntax
    //       highlighter. I should moved this or something.
    void span::operator()(iterator first, iterator last) const
    {
        out << "<phrase role=\"" << name << "\">";
        while (first != last)
            detail::print_char(*first++, out.get());
        out << "</phrase>";
    }

    void unexpected_char::operator()(iterator first, iterator last) const
    {
        file_position const pos = first.get_position();

        detail::outwarn(actions.filename, pos.line)
            << "in column:" << pos.column
            << ", unexpected character: " << detail::utf8(first, last)
            << "\n";

        // print out an unexpected character
        out << "<phrase role=\"error\">";
        while (first != last)
            detail::print_char(*first++, out.get());
        out << "</phrase>";
    }

    void anchor_action::operator()(iterator first, iterator last) const
    {
        if(!actions.suppress)
            actions.anchors.push_back(std::string(first, last));
    }

    void do_macro_action::operator()(std::string const& str) const
    {
        if(!actions.output_pre(phrase)) return;

        if (str == quickbook_get_date)
        {
            char strdate[64];
            strftime(strdate, sizeof(strdate), "%Y-%b-%d", current_time);
            phrase << strdate;
        }
        else if (str == quickbook_get_time)
        {
            char strdate[64];
            strftime(strdate, sizeof(strdate), "%I:%M:%S %p", current_time);
            phrase << strdate;
        }
        else
        {
            phrase << str;
        }
    }

    void space::operator()(char ch) const
    {
        detail::print_space(ch, out.get());
    }

    void space::operator()(iterator first, iterator last) const
    {
        while (first != last)
            detail::print_space(*first++, out.get());
    }

    void pre_escape_back::operator()(iterator first, iterator last) const
    {
        escape_actions.phrase.push(); // save the stream
    }

    void post_escape_back::operator()(iterator first, iterator last) const
    {
        escape_actions.output_pre(escape_actions.phrase);
        out << escape_actions.phrase.str();
        escape_actions.phrase.pop(); // restore the stream
    }

    void code_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(out)) return;

        // preprocess the code section to remove the initial indentation
        std::string program(first, last);
        detail::unindent(program);
        if (program.size() == 0)
            return; // Nothing left to do here. The program is empty.

        iterator first_(program.begin(), first.get_position());
        iterator last_(program.end());

        // TODO: Shouldn't phrase be empty here? Why would it be output
        // after the code block?
        std::string save;
        phrase.swap(save);

        // print the code with syntax coloring
        std::string str = syntax_highlight(first_, last_, actions, actions.source_mode);

        phrase.swap(save);

        //
        // We must not place a \n after the <programlisting> tag
        // otherwise PDF output starts code blocks with a blank line:
        //
        out << "<programlisting>";
        out << str;
        out << "</programlisting>\n";
    }

    void inline_code_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(out)) return;

        std::string save;
        out.swap(save);

        // print the code with syntax coloring
        std::string str = syntax_highlight(first, last, actions, actions.source_mode);

        out.swap(save);

        out << "<code>";
        out << str;
        out << "</code>";
    }

    void raw_char_action::operator()(char ch) const
    {
        if(!actions.output_pre(phrase)) return;
        phrase << ch;
    }

    void raw_char_action::operator()(iterator first, iterator /*last*/) const
    {
        if(!actions.output_pre(phrase)) return;
        phrase << *first;
    }

    void plain_char_action::operator()(char ch) const
    {
        if(!actions.output_pre(phrase)) return;
        detail::print_char(ch, phrase.get());
    }

    void plain_char_action::operator()(iterator first, iterator /*last*/) const
    {
        if(!actions.output_pre(phrase)) return;
        detail::print_char(*first, phrase.get());
    }

    void escape_unicode_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(phrase)) return;

        while(first != last && *first == '0') ++first;

        // Just ignore \u0000
        // Maybe I should issue a warning?
        if(first == last) return;
        
        std::string hex_digits(first, last);
        
        if(hex_digits.size() == 2 && *first > '0' && *first <= '7') {
            using namespace std;
            detail::print_char(strtol(hex_digits.c_str(), 0, 16), phrase.get());
        }
        else {
            phrase << "&#x" << hex_digits << ";";
        }
    }

    void image_action::operator()(iterator, iterator) const
    {
        if(!actions.output_pre(phrase)) return;

        typedef std::map<std::string, value> attribute_map;
        attribute_map attributes;

        value_consumer values = actions.values.get();
        attributes["fileref"] = values.consume();

        BOOST_FOREACH(value pair_, values)
        {
            value_consumer pair = pair_;
            value name = pair.consume();
            value value = pair.consume();
            assert(!pair.is());
            if(!attributes.insert(std::make_pair(name.get_quickbook(), value)).second)
            {
                detail::outwarn(actions.filename, name.get_position().line)
                    << "Duplicate image attribute: " << name.get_quickbook() << std::endl;
            }
        }

        // Find the file basename and extension.
        //
        // Not using Boost.Filesystem because I want to stay in UTF-8.
        // Need to think about uri encoding.
        
        std::string fileref = attributes["fileref"].get_quickbook();

        // Check for windows paths, then convert.
        // A bit crude, but there you go.

        if(fileref.find('\\') != std::string::npos)
        {
            detail::outwarn(actions.filename, attributes["fileref"].get_position().line)
                << "Image path isn't portable: '"
                << detail::utf8(fileref)
                << "'"
                << std::endl;
        }

        boost::replace(fileref, '\\', '/');

        // Find the file basename and extension.
        //
        // Not using Boost.Filesystem because I want to stay in UTF-8.
        // Need to think about uri encoding.

        std::string::size_type pos;
        std::string stem,extension;

        pos = fileref.rfind('/');
        stem = pos == std::string::npos ?
            fileref :
            fileref.substr(pos + 1);

        pos = stem.rfind('.');
        if (pos != std::string::npos)
        {
            extension = stem.substr(pos + 1);
            stem = stem.substr(0, pos);
        }

        // Extract the alt tag, to use as a text description.
        // Or if there isn't one, use the stem of the file name.
        // TODO: IMO if there isn't an alt tag, then the description should
        //       be empty or missing.

        attribute_map::iterator alt_pos = attributes.find("alt");
        std::string alt_text = alt_pos != attributes.end() ?
            alt_pos->second.get_quickbook() : stem;
        attributes.erase("alt");

        if(extension == ".svg")
        {
           //
           // SVG's need special handling:
           //
           // 1) We must set the "format" attribute, otherwise
           //    HTML generation produces code that will not display
           //    the image at all.
           // 2) We need to set the "contentwidth" and "contentdepth"
           //    attributes, otherwise the image will be displayed inside
           //    a tiny box with scrollbars (Firefox), or else cropped to
           //    fit in a tiny box (IE7).
           //

           attributes.insert(attribute_map::value_type("format", qbk_value("SVG")));

           //
           // Image paths are relative to the html subdirectory:
           //
           // TODO: This seems wrong to me.
           //
           fs::path img = detail::generic_to_path(fileref);
           if(img.root_path().empty())
              img = "html" / img;  // relative path

           //
           // Now load the SVG file:
           //
           std::string svg_text;
           fs::ifstream fs(img);
           char c;
           while(fs.get(c) && fs.good())
              svg_text.push_back(c);
           //
           // Extract the svg header from the file:
           //
           std::string::size_type a, b;
           a = svg_text.find("<svg");
           b = svg_text.find('>', a);
           svg_text = (a == std::string::npos) ? "" : svg_text.substr(a, b - a);
           //
           // Now locate the "width" and "height" attributes
           // and borrow their values:
           //
           a = svg_text.find("width");
           a = svg_text.find('=', a);
           a = svg_text.find('\"', a);
           b = svg_text.find('\"', a + 1);
           if(a != std::string::npos)
           {
              attributes.insert(std::make_pair(
                "contentwidth", qbk_value(std::string(
                    svg_text.begin() + a + 1, svg_text.begin() + b))
                ));
           }
           a = svg_text.find("height");
           a = svg_text.find('=', a);
           a = svg_text.find('\"', a);
           b = svg_text.find('\"', a + 1);
           if(a != std::string::npos)
           {
              attributes.insert(std::make_pair(
                "contentdepth", qbk_value(std::string(
                    svg_text.begin() + a + 1, svg_text.begin() + b))
                ));
           }
        }

        phrase << "<inlinemediaobject>";

        phrase << "<imageobject><imagedata";
        
        BOOST_FOREACH(attribute_map::value_type const& attr, attributes)
        {
            phrase << " " << attr.first << "=\"";

            std::string value = attr.second.get_quickbook();
            for(std::string::const_iterator
                first = value.begin(), last  = value.end();
                first != last; ++first)
            {
                if (*first == '\\' && ++first == last) break;
                detail::print_char(*first, phrase.get());
            }

            phrase << "\"";
        }

        phrase << "></imagedata></imageobject>";

        // Add a textobject containing the alt tag from earlier.
        // This will be used for the alt tag in html.
        phrase << "<textobject><phrase>";
        detail::print_string(alt_text, phrase.get());
        phrase << "</phrase></textobject>";

        phrase << "</inlinemediaobject>";
    }

    void macro_identifier_action::operator()(iterator first, iterator last) const
    {
        if(actions.suppress) return;
        actions.macro_id.assign(first, last);
        actions.phrase.push(); // save the phrase
    }

    void macro_definition_action::operator()(iterator first, iterator last) const
    {
        if(actions.suppress) return;
        actions.copy_macros_for_write();
        actions.macro.add(
            actions.macro_id.begin()
          , actions.macro_id.end()
          , actions.phrase.str());
        actions.phrase.pop(); // restore the phrase
    }

    void template_body_action::operator()(iterator, iterator) const
    {
        if(actions.suppress) return;

        value_consumer values = actions.values.get();
        std::string identifier = values.consume().get_quickbook();

        std::vector<std::string> template_values;
        BOOST_FOREACH(value const& p, values.consume()) {
            template_values.push_back(p.get_quickbook());
        }

        BOOST_ASSERT(values.is(template_tags::block) || values.is(template_tags::phrase));
        value body = values.consume();
        BOOST_ASSERT(!values.is());
    
        if (!actions.templates.add(
            template_symbol(
                identifier,
                template_values,
                body.get_quickbook(),
                actions.filename,
                body.get_position(),
                body.get_tag() == template_tags::block,
                &actions.templates.top_scope())))
        {
            file_position const pos = body.get_position();
            detail::outerr(actions.filename, pos.line)
                << "Template Redefinition: " << detail::utf8(identifier) << std::endl;
            ++actions.error_count;
        }
    }

    namespace
    {
        iterator find_bracket_end(iterator begin, iterator const& end)
        {
            unsigned int depth = 1;

            while(depth > 0) {
                char const* search_chars = "[]\\";
                begin = std::find_first_of(begin, end, search_chars, search_chars + 3);
                if(begin == end) return begin;

                if(*begin == '\\')
                {
                    if(++begin == end) return begin;
                    ++begin;
                }
                else
                {
                    depth += (*begin == '[') ? 1 : -1;
                    ++begin;
                }
            }

            return begin;
        }

        iterator find_first_seperator(iterator const& begin, iterator const& end)
        {
            if(qbk_version_n < 105) {
                char const* whitespace = " \t\r\n";
                return std::find_first_of(begin, end, whitespace, whitespace + 4);
            }
            else {
                iterator pos = begin;

                while(true)
                {
                    char const* search_chars = " \t\r\n\\[";
                    pos = std::find_first_of(pos, end, search_chars, search_chars + 6);
                    if(pos == end) return pos;

                    switch(*pos)
                    {
                    case '[':
                        pos = find_bracket_end(++pos, end);
                        break;
                    case '\\':
                        if(++pos == end) return pos;
                        ++pos;
                        break;
                    default:
                        return pos;
                    }
                }
            }
        }
    
        bool break_arguments(
            std::vector<template_body>& args
          , std::vector<std::string> const& params
          , fs::path const& filename
          , file_position const& pos
        )
        {
            // Quickbook 1.4-: If there aren't enough parameters seperated by
            //                 '..' then seperate the last parameter using
            //                 whitespace.
            // Quickbook 1.5+: If '..' isn't used to seperate the parameters
            //                 then use whitespace to separate them
            //                 (2 = template name + argument).

            if (qbk_version_n < 105 || args.size() == 1)
            {
           
                while (args.size() < params.size())
                {
                    // Try to break the last argument at the first space found
                    // and push it into the back of args. Do this
                    // recursively until we have all the expected number of
                    // arguments, or if there are no more spaces left.

                    template_body& body = args.back();
                    iterator begin(body.content.begin(), body.position);
                    iterator end(body.content.end());
                    
                    iterator l_pos = find_first_seperator(begin, end);
                    if (l_pos == end)
                        break;
                    char const* whitespace = " \t\r\n";
                    char const* whitespace_end = whitespace + 4;
                    iterator r_pos = l_pos;
                    while(r_pos != end && std::find(whitespace, whitespace_end, *r_pos) != whitespace_end) ++r_pos;
                    if (r_pos == end)
                        break;
                    template_body second(std::string(r_pos, end), body.filename, r_pos.get_position(), false);
                    body.content = std::string(begin, l_pos);
                    args.push_back(second);
                }
            }

            if (args.size() != params.size())
            {
                detail::outerr(filename, pos.line)
                    << "Invalid number of arguments passed. Expecting: "
                    << params.size()
                    << " argument(s), got: "
                    << args.size()
                    << " argument(s) instead."
                    << std::endl;
                return false;
            }
            return true;
        }

        std::pair<bool, std::vector<std::string>::const_iterator>
        get_arguments(
            std::vector<template_body>& args
          , std::vector<std::string> const& params
          , template_scope const& scope
          , file_position const& pos
          , quickbook::actions& actions
        )
        {
            std::vector<template_body>::const_iterator arg = args.begin();
            std::vector<std::string>::const_iterator tpl = params.begin();
            std::vector<std::string> empty_params;


            // Store each of the argument passed in as local templates:
            while (arg != args.end())
            {
                if (!actions.templates.add(
                        template_symbol(*tpl, empty_params, arg->content,
                            arg->filename, arg->position, arg->is_block, &scope)))
                {
                    detail::outerr(actions.filename, pos.line)
                        << "Duplicate Symbol Found" << std::endl;
                    ++actions.error_count;
                    return std::make_pair(false, tpl);
                }
                ++arg; ++tpl;
            }
            return std::make_pair(true, tpl);
        }
        
        bool parse_template(
            template_body const& body
          , bool escape
          , quickbook::actions& actions
        )
        {
            // How do we know if we are to parse the template as a block or
            // a phrase? We apply a simple heuristic: if the body starts with
            // a newline, then we regard it as a block, otherwise, we parse
            // it as a phrase.
            //
            // Note: this is now done in the grammar.

            if (escape)
            {
                //  escape the body of the template
                //  we just copy out the literal body
                (body.is_block ? actions.out : actions.phrase) << body.content;
                return true;
            }
            else
            {
                if (!body.is_block)
                {
                    //  do a phrase level parse
                    actions.filename = body.filename;
                    iterator first(body.content.begin(), body.position);
                    iterator last(body.content.end());
                    
                    return cl::parse(first, last, actions.grammar().simple_phrase).full;
                }
                else
                {
                    //  do a block level parse
                    //  ensure that we have enough trailing newlines to eliminate
                    //  the need to check for end of file in the grammar.
                    
                    actions.filename = body.filename;
                    std::string content = body.content + "\n\n";
                    iterator first(content.begin(), body.position);
                    iterator last(content.end());

                    return cl::parse(first, last, actions.grammar().block).full;
                }
            }
        }
    }

    namespace detail
    {
        int callout_id = 0;
    }

    void do_template_action::operator()(iterator first, iterator) const
    {
        if(actions.suppress) return;

        file_position const pos = first.get_position();
        
        // Get the arguments
        value_consumer values = actions.values.get();

        bool template_escape = values.is(template_tags::escape);
        if(template_escape) values.consume();

        std::string identifier = values.consume(template_tags::identifier).get_quickbook();

        std::vector<template_body> args;

        BOOST_FOREACH(value arg, values)
        {
            BOOST_ASSERT(
                arg.get_tag() == template_tags::block ||
                arg.get_tag() == template_tags::phrase);

            args.push_back(
                template_body(
                    arg.get_quickbook(),
                    actions.filename,
                    arg.get_position(),
                    arg.get_tag() == template_tags::block
                ));
        }

        ++actions.template_depth;
        if (actions.template_depth > actions.max_template_depth)
        {
            detail::outerr(actions.filename, pos.line)
                << "Infinite loop detected" << std::endl;
            --actions.template_depth;
            ++actions.error_count;
            return;
        }

        // The template arguments should have the scope that the template was
        // called from, not the template's own scope.
        //
        // Note that for quickbook 1.4- this value is just ignored when the
        // arguments are expanded.
        template_scope const& call_scope = actions.templates.top_scope();

        template_symbol const* symbol = actions.templates.find(identifier);
        BOOST_ASSERT(symbol);

        std::string block;
        std::string phrase;

        actions.push(); // scope the actions' states
        {
            // Store the current section level so that we can ensure that
            // [section] and [endsect] tags in the template are balanced.
            actions.min_section_level = actions.section_level;

            // Quickbook 1.4-: When expanding the tempalte continue to use the
            //                 current scope (the dynamic scope).
            // Quickbook 1.5+: Use the scope the template was defined in
            //                 (the static scope).
            if (qbk_version_n >= 105)
                actions.templates.set_parent_scope(*symbol->parent);

            ///////////////////////////////////
            // Initialise the arguments
            
            if (!symbol->callout)
            {
                // Break the arguments for a template
            
                if (!break_arguments(args, symbol->params, actions.filename, pos))
                {
                    actions.pop(); // restore the actions' states
                    --actions.template_depth;
                    ++actions.error_count;
                    return;
                }
            }
            else
            {
                if (!args.empty())
                {
                    detail::outerr(actions.filename, pos.line)
                        << "Arguments for code snippet."
                        <<std::endl;
                    ++actions.error_count;

                    args.clear();
                }

                unsigned int size = symbol->params.size();

                for(unsigned int i = 0; i < size; ++i)
                {
                    std::string callout_id = actions.doc_id +
                        boost::lexical_cast<std::string>(detail::callout_id + i);

                    std::string code;
                    code += "'''";
                    code += "<co id=\"" + callout_id + "co\" ";
                    code += "linkends=\"" + callout_id + "\" />";
                    code += "'''";

                    args.push_back(template_body(code, actions.filename, pos, false));
                }
            }

            ///////////////////////////////////
            // Prepare the arguments as local templates
            bool get_arg_result;
            std::vector<std::string>::const_iterator tpl;
            boost::tie(get_arg_result, tpl) =
                get_arguments(args, symbol->params,
                    call_scope, pos, actions);

            if (!get_arg_result)
            {
                actions.pop(); // restore the actions' states
                --actions.template_depth;
                return;
            }

            ///////////////////////////////////
            // parse the template body:

            if (!parse_template(symbol->body, template_escape, actions))
            {
                file_position const pos = first.get_position();
                detail::outerr(actions.filename, pos.line)
                    << "Expanding "
                    << (symbol->body.is_block ? "block" : "phrase")
                    << " template: " << detail::utf8(symbol->identifier) << std::endl
                    << std::endl
                    << "------------------begin------------------" << std::endl
                    << detail::utf8(symbol->body.content)
                    << "------------------end--------------------" << std::endl
                    << std::endl;
                actions.pop(); // restore the actions' states
                --actions.template_depth;
                ++actions.error_count;
                return;
            }

            if (actions.section_level != actions.min_section_level)
            {
                file_position const pos = first.get_position();
                detail::outerr(actions.filename, pos.line)
                    << "Mismatched sections in template " << detail::utf8(identifier) << std::endl;
                actions.pop(); // restore the actions' states
                --actions.template_depth;
                ++actions.error_count;
                return;
            }
        }

        actions.out.swap(block);
        actions.phrase.swap(phrase);
        actions.pop(); // restore the actions' states

        if(symbol->callout && symbol->callouts.size() > 0)
        {
            BOOST_ASSERT(phrase.empty());
            block += "<calloutlist>";
            BOOST_FOREACH(template_body const& c, symbol->callouts)
            {
                std::string callout_id = actions.doc_id +
                    boost::lexical_cast<std::string>(detail::callout_id++);

                std::string callout_value;
                actions.push();
                bool r = parse_template(c, false, actions);
                actions.out.swap(callout_value);
                actions.pop();

                if(!r)
                {
                    detail::outerr(c.filename, c.position.line)
                        << "Expanding callout." << std::endl
                        << "------------------begin------------------" << std::endl
                        << detail::utf8(c.content)
                        << std::endl
                        << "------------------end--------------------" << std::endl
                        ;
                    ++actions.error_count;
                    return;
                }
                
                block += "<callout arearefs=\"" + callout_id + "co\" ";
                block += "id=\"" + callout_id + "\">";
                block += callout_value;
                block += "</callout>";
            }
            block += "</calloutlist>";
        }

        if(symbol->body.is_block || !block.empty()) {
            actions.inside_paragraph();
            actions.out << block;
            actions.phrase << phrase;
        }
        else {
            actions.phrase << phrase;
        }
        --actions.template_depth;
    }

    void link_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(phrase)) return;

        iterator save = first;
        phrase << tag;
        while (first != last)
            detail::print_char(*first++, phrase.get());
        phrase << "\">";

        // Yes, it is safe to dereference last here. When we
        // reach here, *last is certainly valid. We test if
        // *last == ']'. In which case, the url is the text.
        // Example: [@http://spirit.sourceforge.net/]

        if (*last == ']')
        {
            first = save;
            while (first != last)
                detail::print_char(*first++, phrase.get());
        }
    }

    void variablelist_action::operator()(iterator, iterator) const
    {
        if(actions.suppress) return;

        value_consumer values = actions.values.get();
        std::string title = values.consume(table_tags::title).get_quickbook();

        actions.out << "<variablelist>\n";

        actions.out << "<title>";
        detail::print_string(title, actions.out.get());
        actions.out << "</title>\n";

        BOOST_FOREACH(value_consumer entry, values) {
            actions.out << start_varlistentry_;
            
            if(entry.is()) {
                actions.out << start_varlistterm_;
                actions.out << entry.consume().get_boostbook();
                actions.out << end_varlistterm_;
            }
            
            if(entry.is()) {
                actions.out << start_varlistitem_;
                BOOST_FOREACH(value phrase, entry) actions.out << phrase.get_boostbook();
                actions.out << end_varlistitem_;
            }

            actions.out << end_varlistentry_;
        }

        actions.out << "</variablelist>\n";
    }

    void table_action::operator()(iterator, iterator) const
    {
        if(actions.suppress) return;

        value_consumer values = actions.values.get();

        std::string element_id;
        if(values.is(general_tags::element_id))
            element_id = values.consume().get_quickbook();

        std::string title = values.consume(table_tags::title).get_quickbook();
        bool has_title = !title.empty();
        
        std::string table_id;
        if(qbk_version_n >= 105) {
            if(!element_id.empty()) {
                table_id = fully_qualified_id(actions.doc_id,
                    actions.qualified_section_id, element_id);
            }
            else if(has_title) {
                table_id = fully_qualified_id(actions.doc_id,
                    actions.qualified_section_id,
                    detail::make_identifier(title.begin(), title.end()));
            }
        }

        // Emulating the old behaviour which used the width of the final
        // row for span_count.
        int row_count = 0;
        int span_count = 0;

        BOOST_FOREACH(value row, values) {
            ++row_count;
            span_count = boost::distance(row);
        }

        if (has_title)
        {
            actions.out << "<table frame=\"all\"";
            if(!table_id.empty())
                actions.out << " id=\"" << table_id << "\"";
            actions.out << ">\n";
            actions.out << "<title>";
            detail::print_string(title, actions.out.get());
            actions.out << "</title>";
        }
        else
        {
            actions.out << "<informaltable frame=\"all\"";
            if(!table_id.empty())
                actions.out << " id=\"" << table_id << "\"";
            actions.out << ">\n";
        }

        actions.out << "<tgroup cols=\"" << span_count << "\">\n";

        if (row_count > 1)
        {
            actions.out << "<thead>" << start_row_;
            BOOST_FOREACH(value cell, values.consume()) {
                actions.out << start_cell_ << cell.get_boostbook() << end_cell_;
            }
            actions.out << end_row_ << "</thead>\n";
        }

        actions.out << "<tbody>\n";

        BOOST_FOREACH(value row, values) {
            actions.out << start_row_;
            BOOST_FOREACH(value cell, row) {
                actions.out << start_cell_ << cell.get_boostbook() << end_cell_;
            }
            actions.out << end_row_;
        }

        actions.out << "</tbody>\n"
                     << "</tgroup>\n";

        if (has_title)
        {
            actions.out << "</table>\n";
        }
        else
        {
            actions.out << "</informaltable>\n";
        }
    }

    void begin_section_action::operator()(iterator first, iterator last) const
    {    
        if(actions.suppress) return;

        value_consumer values = actions.values.get();

        section_id = values.is(general_tags::element_id) ?
            values.consume().get_quickbook() :
            detail::make_identifier(first, last);

        if (section_level != 0)
            qualified_section_id += '.';
        else
            BOOST_ASSERT(qualified_section_id.empty());
        qualified_section_id += section_id;
        ++section_level;

        actions.output_pre(out);

        if (qbk_version_n < 103) // version 1.2 and below
        {
            out << "\n<section id=\""
                << library_id << "." << section_id << "\">\n";
        }
        else // version 1.3 and above
        {
            out << "\n<section id=\"" << library_id
                << "." << qualified_section_id << "\">\n";
        }
        std::string str;
        phrase.swap(str);

        out << "<title>";

        actions.anchors.swap(actions.saved_anchors);
        actions.output_pre(out);

        if (qbk_version_n < 103) // version 1.2 and below
        {
            out << str;
        }
        else // version 1.3 and above
        {
            out << "<link linkend=\"" << library_id
                    << "." << qualified_section_id << "\">"
                << str
                << "</link>"
                ;
        }
        
        out << "</title>\n";
    }

    void end_section_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(out)) return;

        if (section_level <= min_section_level)
        {
            file_position const pos = first.get_position();
            detail::outerr(actions.filename, pos.line)
                << "Mismatched [endsect] near column " << pos.column << ".\n";
            ++error_count;
            
            return;
        }

        --section_level;
        out << "</section>";

        if (section_level == 0)
        {
            qualified_section_id.clear();
        }
        else
        {
            std::string::size_type const n =
                qualified_section_id.find_last_of('.');
            qualified_section_id.erase(n, std::string::npos);
        }
    }
    
    void element_id_warning_action::operator()(iterator first, iterator) const
    {
        file_position const pos = first.get_position();
        detail::outwarn(actions.filename, pos.line) << "Empty id.\n";        
    }

    fs::path path_difference(fs::path const& outdir, fs::path const& path)
    {
        fs::path outtmp, temp;
        fs::path::iterator out = outdir.begin(), file = path.begin();
        for(; out != outdir.end() && file != path.end(); ++out, ++file)
        {
            if(!fs::equivalent(outtmp /= *out, temp /= *file))
                break;
        }
        out = (out == outdir.begin()) ? outdir.end() : out;

        fs::path result = fs::path();
        for(; out != outdir.end(); ++out)
            if(*out != ".") result /= "..";
        std::divides<fs::path> concat;
        return std::accumulate(file, path.end(), result, concat);
    }

    std::string check_path(iterator first, iterator last,
        quickbook::actions& actions)
    {
        std::string path_text(first, last);

        if(path_text.find('\\') != std::string::npos)
        {
            detail::outwarn(actions.filename, first.get_position().line)
                << "Path isn't portable: "
                << detail::utf8(path_text)
                << std::endl;
        }
        
        boost::replace(path_text, '\\', '/');
        
        return path_text;
    }

    fs::path calculate_relative_path(std::string const& name, quickbook::actions& actions)
    {
        // Given a source file and the current filename, calculate the
        // path to the source file relative to the output directory.

        fs::path path = detail::generic_to_path(name);
        if (!path.has_root_directory() && !path.has_root_name())
        {
            fs::path infile = fs::absolute(actions.filename).normalize();
            path = (infile.parent_path() / path).normalize();
            fs::path outdir = fs::absolute(actions.outdir).normalize();
            path = path_difference(outdir, path);
        }
        return path;
    }

    void xinclude_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(out)) return;

        fs::path path = calculate_relative_path(check_path(first, last, actions), actions);
        out << "\n<xi:include href=\"";
        detail::print_string(detail::escape_uri(path.generic_string()), out.get());
        out << "\" />\n";
    }

    namespace
    {
        fs::path include_search(fs::path const & current, std::string const & name)
        {
            fs::path path(name);

            // If the path is relative, try and resolve it.
            if (!path.has_root_directory() && !path.has_root_name())
            {
                // See if it can be found locally first.
                if (fs::exists(current / path))
                {
                    return current / path;
                }

                // Search in each of the include path locations.
                BOOST_FOREACH(fs::path full, include_path)
                {
                    full /= path;
                    if (fs::exists(full))
                    {
                        return full;
                    }
                }
            }

            return path;
        }
    }

    void import_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(actions.out)) return;

        fs::path path = include_search(actions.filename.parent_path(),
            check_path(first, last, actions));
        std::string ext = path.extension().generic_string();
        std::vector<template_symbol> storage;
        actions.error_count +=
            load_snippets(path.string(), storage, ext, actions.doc_id);

        BOOST_FOREACH(template_symbol& ts, storage)
        {
            std::string tname = ts.identifier;
            ts.parent = &actions.templates.top_scope();
            if (!actions.templates.add(ts))
            {
                detail::outerr(ts.body.filename, ts.body.position.line)
                    << "Template Redefinition: " << detail::utf8(tname) << std::endl;
                ++actions.error_count;
            }
        }
    }

    void include_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(actions.out)) return;

        fs::path filein = include_search(actions.filename.parent_path(),
            check_path(first, last, actions));
        std::string doc_type, doc_id;

        // swap the filenames
        std::swap(actions.filename, filein);

        // save the doc info strings and source mode
        if(qbk_version_n >= 106) {
            doc_type = actions.doc_type;
            doc_id = actions.doc_id;
        }
        else {
            actions.doc_type.swap(doc_type);
            actions.doc_id.swap(doc_id);
        }
        
        // save the source mode and version info (only restored for 1.6+)
        std::string source_mode = actions.source_mode;
        unsigned qbk_major_version_store = qbk_major_version;
        unsigned qbk_minor_version_store = qbk_minor_version;
        unsigned qbk_version_n_store = qbk_version_n;

        // scope the macros
        string_symbols macro = actions.macro;
        std::size_t macro_change_depth = actions.macro_change_depth;
        // scope the templates
        //~ template_symbols templates = actions.templates; $$$ fixme $$$

        // if an id is specified in this include (as in [include:id foo.qbk])
        // then use it as the doc_id.
        if (!actions.include_doc_id.empty())
        {
            actions.doc_id = actions.include_doc_id;
            actions.include_doc_id.clear();
        }

        // update the __FILENAME__ macro
        *boost::spirit::classic::find(actions.macro, "__FILENAME__")
            = detail::path_to_generic(actions.filename);

        // parse the file
        quickbook::parse_file(actions.filename.string().c_str(), actions, true);

        // restore the values
        std::swap(actions.filename, filein);

        actions.doc_type.swap(doc_type);
        actions.doc_id.swap(doc_id);
        
        if(qbk_version_n >= 106 || qbk_version_n_store >= 106)
        {
            actions.source_mode = source_mode;

            qbk_major_version = qbk_major_version_store;
            qbk_minor_version = qbk_minor_version_store;
            qbk_version_n = qbk_version_n_store;
        }

        // restore the macros
        actions.macro = macro;
        actions.macro_change_depth = macro_change_depth;
        // restore the templates
        //~ actions.templates = templates; $$$ fixme $$$
    }

    void phrase_to_string_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(phrase)) return;

        out.clear();
        phrase.swap(out);
    }

    void phrase_to_docinfo_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(actions.phrase)) return;

        std::string encoded;
        actions.phrase.swap(encoded);
        actions.values.builder.insert(
            qbk_bbk_value(first, last, encoded, actions.values.builder.release_tag()));
    }
    
    void phrase_to_value_action::operator()(iterator first, iterator last) const
    {
        if(!actions.output_pre(actions.phrase)) return;

        std::string value;
        actions.phrase.swap(value);
        actions.values.builder.insert(
            bbk_value(value, actions.values.builder.release_tag()));
    }
    
    void inner_phrase_action_pre::operator()(iterator, iterator) const
    {
        // TODO: Really?
        if(actions.suppress) return;

        actions.saved_anchors.clear();
        actions.saved_anchors.swap(actions.anchors);
    }

    void inner_phrase_action_post::operator()(iterator, iterator) const
    {
        if(actions.suppress) return;

        actions.output_pre(actions.phrase);
    }

    bool pre_output_action::operator()(collector& tgt) const
    {
        if(actions.suppress) return false;

        for(quickbook::actions::string_list::iterator
            it = actions.anchors.begin(),
            end = actions.anchors.end();
            it != end; ++it)
        {
            tgt << "<anchor id=\"";
            detail::print_string(*it, tgt.get());
            tgt << "\"/>\n";
        }
        
        actions.anchors.clear();

        return true;
    }
    
    bool pre_output_action::operator()(iterator, iterator) const
    {
        return (*this)(actions.out);
    }

    scoped_block_push::scoped_block_push(quickbook::actions& actions)
        : actions(actions)
    {
        actions.out.push();
        actions.phrase.push();
    }
    
    scoped_block_push::~scoped_block_push()
    {
        actions.phrase.pop();
        actions.out.pop();
    }

    void scoped_block_push::success_impl()
    {
        actions.inside_paragraph();
        actions.values.builder.insert(
            bbk_value(actions.out.str(), actions.values.builder.release_tag()));
    }

    set_no_eols_scoped::set_no_eols_scoped(quickbook::actions& actions)
        : actions(actions), saved_no_eols(actions.no_eols)
    {
        actions.no_eols = false;
    }

    set_no_eols_scoped::~set_no_eols_scoped()
    {
        actions.no_eols = saved_no_eols;
    }
}
