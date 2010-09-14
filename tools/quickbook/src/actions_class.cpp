/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "actions_class.hpp"
#include "markups.hpp"
#include "quickbook.hpp"

#if (defined(BOOST_MSVC) && (BOOST_MSVC <= 1310))
#pragma warning(disable:4355)
#endif

namespace quickbook
{
    actions::actions(char const* filein_, fs::path const& outdir_, string_stream& out_)
    // header info
        : doc_type()
        , doc_title()
        , doc_version()
        , doc_id()
        , doc_dirname()
        , doc_copyrights()
        , doc_purpose()
        , doc_categories()
        , doc_authors()
        , doc_license()
        , doc_last_revision()
        , include_doc_id()

    // main output stream
        , out(out_)

    // auxilliary streams
        , phrase()
        , list_buffer()

    // state
        , filename(fs::complete(fs::path(filein_)))
        , outdir(outdir_)
        , macro_change_depth(0)
        , macro()
        , section_level(0)
        , min_section_level(0)
        , section_id()
        , qualified_section_id()
        , source_mode("c++")

    // temporary or global state
        , element_id()
        , table_title()
        , table_span(0)
        , table_header()
        , macro_id()
        , list_marks()
        , list_indent(-1)
        , template_identifier()
        , template_info()
        , template_depth(0)
        , template_escape(false)
        , templates()
        , error_count(0)
        , image_fileref()
        , attribute_name()
        , attributes()

    // actions
        , error(error_count)
        , extract_doc_title(doc_title, phrase)
        , extract_doc_license(doc_license, phrase)
        , extract_doc_purpose(doc_purpose, phrase)
        , extract_doc_version(doc_version, phrase)
        , extract_doc_id(doc_id_tmp, phrase)
        , extract_doc_dirname(doc_dirname, phrase)
        , extract_copyright_second(copyright.second, phrase)
        , extract_name_second(name.second, phrase)
        , extract_name_first(name.first, phrase)
        , extract_doc_last_revision(doc_last_revision, phrase)
        , extract_doc_category(doc_category, phrase)
        , extract_doc_biblioid(doc_biblioid.second, phrase)
        , code(out, phrase, *this)
        , code_block(phrase, phrase, *this)
        , inline_code(phrase, *this)
        , inside_paragraph(out, phrase, paragraph_pre, paragraph_post)
        , h(out, phrase, element_id, doc_id, section_id, qualified_section_id, section_level)
        , h1(out, phrase, element_id, doc_id, section_id, qualified_section_id, h1_pre, h1_post)
        , h2(out, phrase, element_id, doc_id, section_id, qualified_section_id, h2_pre, h2_post)
        , h3(out, phrase, element_id, doc_id, section_id, qualified_section_id, h3_pre, h3_post)
        , h4(out, phrase, element_id, doc_id, section_id, qualified_section_id, h4_pre, h4_post)
        , h5(out, phrase, element_id, doc_id, section_id, qualified_section_id, h5_pre, h5_post)
        , h6(out, phrase, element_id, doc_id, section_id, qualified_section_id, h6_pre, h6_post)
        , hr(out, hr_)
        , blurb(out, blurb_pre, blurb_post)
        , blockquote(out, blockquote_pre, blockquote_post)
        , preformatted(out, phrase, preformatted_pre, preformatted_post)
        , warning(out, warning_pre, warning_post)
        , caution(out, caution_pre, caution_post)
        , important(out, important_pre, important_post)
        , note(out, note_pre, note_post)
        , tip(out, tip_pre, tip_post)
        , plain_char(phrase)
        , raw_char(phrase)
        , escape_unicode(phrase)
        , attribute(attributes, attribute_name, error_count)
        , image(phrase, attributes, image_fileref)
        , cond_phrase_pre(phrase, conditions, macro)
        , cond_phrase_post(phrase, conditions, macro)

        , list(out, list_buffer, list_indent, list_marks)
        , list_format(list_buffer, list_indent, list_marks, error_count)
        , list_item(list_buffer, phrase, list_item_pre, list_item_post)

        , funcref_pre(phrase, funcref_pre_)
        , funcref_post(phrase, funcref_post_)
        , classref_pre(phrase, classref_pre_)
        , classref_post(phrase, classref_post_)
        , memberref_pre(phrase, memberref_pre_)
        , memberref_post(phrase, memberref_post_)
        , enumref_pre(phrase, enumref_pre_)
        , enumref_post(phrase, enumref_post_)
        , macroref_pre(phrase, macroref_pre_)
        , macroref_post(phrase, macroref_post_)
        , headerref_pre(phrase, headerref_pre_)
        , headerref_post(phrase, headerref_post_)
        , conceptref_pre(phrase, conceptref_pre_)
        , conceptref_post(phrase, conceptref_post_)
        , globalref_pre(phrase, globalref_pre_)
        , globalref_post(phrase, globalref_post_)

        , bold_pre(phrase, bold_pre_)
        , bold_post(phrase, bold_post_)
        , italic_pre(phrase, italic_pre_)
        , italic_post(phrase, italic_post_)
        , underline_pre(phrase, underline_pre_)
        , underline_post(phrase, underline_post_)
        , teletype_pre(phrase, teletype_pre_)
        , teletype_post(phrase, teletype_post_)
        , strikethrough_pre(phrase, strikethrough_pre_)
        , strikethrough_post(phrase, strikethrough_post_)
        , quote_pre(phrase, quote_pre_)
        , quote_post(phrase, quote_post_)
        , replaceable_pre(phrase, replaceable_pre_)
        , replaceable_post(phrase, replaceable_post_)
        , footnote_pre(phrase, footnote_pre_)
        , footnote_post(phrase, footnote_post_)

        , simple_bold(phrase, bold_pre_, bold_post_, macro)
        , simple_italic(phrase, italic_pre_, italic_post_, macro)
        , simple_underline(phrase, underline_pre_, underline_post_, macro)
        , simple_teletype(phrase, teletype_pre_, teletype_post_, macro)
        , simple_strikethrough(phrase, strikethrough_pre_, strikethrough_post_, macro)

        , variablelist(*this)
        , start_varlistentry(phrase, start_varlistentry_)
        , end_varlistentry(phrase, end_varlistentry_)
        , start_varlistterm(phrase, start_varlistterm_)
        , end_varlistterm(phrase, end_varlistterm_)
        , varlistitem(phrase, start_varlistitem_, end_varlistitem_)

        , break_(phrase)
        , macro_identifier(*this)
        , macro_definition(*this)
        , do_macro(phrase)
        , template_body(*this)
        , template_arg(*this)
        , do_template(*this)
        , url_pre(phrase, url_pre_)
        , url_post(phrase, url_post_)
        , link_pre(phrase, link_pre_)
        , link_post(phrase, link_post_)
        , table(*this)
        , start_row(phrase, table_span, table_header)
        , end_row(phrase, end_row_)
        , cell(phrase, table_span)
        , anchor(out)

        , begin_section(out, phrase, doc_id, section_id, section_level, qualified_section_id, element_id)
        , end_section(out, section_level, min_section_level, qualified_section_id, error_count)
        , xinclude(out, *this)
        , include(*this)
        , import(out, *this)

        , escape_pre(phrase, escape_pre_)
        , escape_post(phrase, escape_post_)
    {
        // turn off __FILENAME__ macro on debug mode = true
        std::string filename_str = debug_mode ?
            std::string("NO_FILENAME_MACRO_GENERATED_IN_DEBUG_MODE") :
            filename.file_string();

        // add the predefined macros
        macro.add
            ("__DATE__", std::string(quickbook_get_date))
            ("__TIME__", std::string(quickbook_get_time))
            ("__FILENAME__", filename_str)
        ;
    }

    void actions::push()
    {
        state_stack.push(
            boost::make_tuple(
                filename
              , outdir
              , macro_change_depth
              , section_level
              , min_section_level
              , section_id
              , qualified_section_id
              , source_mode
            )
        );

        out.push();
        phrase.push();
        list_buffer.push();
        templates.push();        
    }
    
    // Pushing and popping the macro symbol table is pretty expensive, so
    // instead implement a sort of 'stack on write'. Call this whenever a
    // change is made to the macro table, and it'll stack the current macros
    // if necessary. Would probably be better to implement macros in a less
    // expensive manner.
    void actions::copy_macros_for_write()
    {
        if(macro_change_depth != state_stack.size())
        {
            macro_stack.push(macro);
            macro_change_depth = state_stack.size();
        }
    }

    void actions::pop()
    {
        if(macro_change_depth == state_stack.size())
        {
            macro = macro_stack.top();
            macro_stack.pop();
        }
    
        boost::tie(
            filename
          , outdir
          , macro_change_depth
          , section_level
          , min_section_level
          , section_id
          , qualified_section_id
          , source_mode
        ) = state_stack.top();
        state_stack.pop();

        out.pop();
        phrase.pop();
        list_buffer.pop();
        templates.pop();
    }
}
