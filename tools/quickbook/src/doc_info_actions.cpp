/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    Copyright (c) 2005 Thomas Guest
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <sstream>
#include <boost/bind.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/foreach.hpp>
#include "quickbook.hpp"
#include "utils.hpp"
#include "files.hpp"
#include "input_path.hpp"
#include "actions_class.hpp"
#include "doc_info_tags.hpp"
#include "id_manager.hpp"

namespace quickbook
{
    static void write_document_title(collector& out, value const& title, value const& version);
    
    static std::string doc_info_output(value const& p, unsigned version)
    {
        return (qbk_version_n < version) ? p.get_quickbook() : p.get_boostbook();
    }

    value consume_last(value_consumer& c, value::tag_type tag,
            std::vector<std::string>* duplicates)
    {
        value p;

        int count = 0;
        while(c.check(tag)) {
            p = c.consume();
            ++count;
        }

        if(count > 1) duplicates->push_back(doc_info_attributes::name(tag));

        return p;
    }

    value consume_last_single(value_consumer& c, value::tag_type tag,
            std::vector<std::string>* duplicates)
    {
        value l = consume_last(c, tag, duplicates);
        if(l.empty()) return l;

        assert(l.is_list());
        value_consumer c2 = l;
        value p = c2.consume();
        c2.finish();

        return p;
    }

    std::vector<value> consume_multiple(value_consumer& c, value::tag_type tag)
    {
        std::vector<value> values;
        
        while(c.check(tag)) {
            values.push_back(c.consume());
        }
        
        return values;
    }

    void pre(collector& out, quickbook::actions& actions,
            value include_doc_id, docinfo_types docinfo_type)
    {
        // The doc_info in the file has been parsed. Here's what we'll do
        // *before* anything else.
        //
        // If there isn't a doc info block, then values will be empty, so most
        // of the following code won't actually do anything.

        value_consumer values = actions.values.release();

        // Skip over invalid attributes

        while (values.check(value::default_tag)) values.consume();
        
        value qbk_version = values.optional_consume(doc_info_tags::qbk_version);
        
        value doc_title;
        if (values.check())
        {
            actions.doc_type = values.consume(doc_info_tags::type).get_quickbook();
            doc_title = values.consume(doc_info_tags::title);
            actions.doc_title_qbk = doc_title.get_quickbook();
        }
        else
        {
            actions.doc_type.clear();
        }

        std::vector<std::string> duplicates;

        value id = consume_last_single(values, doc_info_attributes::id, &duplicates);
        value dirname = consume_last_single(values, doc_info_attributes::dirname, &duplicates);
        value last_revision = consume_last_single(values, doc_info_attributes::last_revision, &duplicates);
        value purpose = consume_last_single(values, doc_info_attributes::purpose, &duplicates);
        std::vector<value> categories = consume_multiple(values, doc_info_attributes::category);
        value lang = consume_last_single(values, doc_info_attributes::lang, &duplicates);
        value version = consume_last_single(values, doc_info_attributes::version, &duplicates);
        std::vector<value> authors = consume_multiple(values, doc_info_attributes::authors);
        std::vector<value> copyrights = consume_multiple(values, doc_info_attributes::copyright);
        value license = consume_last_single(values, doc_info_attributes::license, &duplicates);
        std::vector<value> biblioids = consume_multiple(values, doc_info_attributes::biblioid);
        value compatibility_mode = consume_last(values, doc_info_attributes::compatibility_mode, &duplicates);
        
        // Skip over source-mode tags (already dealt with)

        while (values.check(doc_info_attributes::source_mode)) values.consume();

        values.finish();

        if(!duplicates.empty())
        {
            detail::outwarn(actions.current_file->path,1)
                << (duplicates.size() > 1 ?
                    "Duplicate attributes" : "Duplicate attribute")
                << ":" << detail::utf8(boost::algorithm::join(duplicates, ", "))
                << "\n"
                ;
        }

        std::string include_doc_id_, id_;

        if (!include_doc_id.empty())
            include_doc_id_.assign(
                include_doc_id.get_quickbook().begin(),
                include_doc_id.get_quickbook().end());

        if (!id.empty())
            id_.assign(
                id.get_quickbook().begin(),
                id.get_quickbook().end());

        // if we're ignoring the document info, just start the file
        // and we're done.

        if (!docinfo_type)
        {
            actions.current_file_tmp->version(qbk_version_n);
            actions.ids.start_file(include_doc_id_, id_, actions.doc_title_qbk);

            return;
        }

        // Quickbook version

        int qbk_major_version, qbk_minor_version;
        unsigned compatibility_version;

        if (qbk_version.empty())
        {
            // hard code quickbook version to v1.1
            qbk_major_version = 1;
            qbk_minor_version = 1;
            qbk_version_n = 101;
            detail::outwarn(actions.current_file->path,1)
                << "Quickbook version undefined. "
                "Version 1.1 is assumed" << std::endl;
        }
        else
        {
            value_consumer qbk_version_values(qbk_version);
            qbk_major_version = qbk_version_values.consume().get_int();
            qbk_minor_version = qbk_version_values.consume().get_int();
            qbk_version_values.finish();

            qbk_version_n = ((unsigned) qbk_major_version * 100) +
                (unsigned) qbk_minor_version;
        }
        
        if (qbk_version_n == 106)
        {
            detail::outwarn(actions.current_file->path,1)
                << "Quickbook 1.6 is still under development and is "
                "likely to change in the future." << std::endl;
        }
        else if(qbk_version_n < 100 || qbk_version_n > 106)
        {
            detail::outerr(actions.current_file->path,1)
                << "Unknown version of quickbook: quickbook "
                << qbk_major_version
                << "."
                << qbk_minor_version
                << std::endl;
            ++actions.error_count;
        }
        
        if (compatibility_mode.empty())
        {
            compatibility_version = qbk_version_n;
        }
        else
        {
            value_consumer values(compatibility_mode);
            int compatibility_major_version = values.consume().get_int();
            int compatibility_minor_version = values.consume().get_int();
            values.finish();

            compatibility_version = ((unsigned) compatibility_major_version * 100) +
                (unsigned) compatibility_minor_version;

            if (compatibility_version < 100 || compatibility_version > 106)
            {
                detail::outerr(actions.current_file->path,1)
                    << "Unknown compatibility version of quickbook: "
                    << qbk_major_version
                    << "."
                    << qbk_minor_version
                    << std::endl;
                ++actions.error_count;
            }
        }

        actions.current_file_tmp->version(qbk_version_n);

        id_manager::start_file_info start_file_info =
            actions.ids.start_file_with_docinfo(
                compatibility_version, include_doc_id_, id_,
                actions.doc_title_qbk);

        // if we're ignoring the document info, we're done.

        if (!docinfo_type)
        {
            return;
        }

        // Make sure we really did have a document info block.

        assert(doc_title.check() && !actions.doc_type.empty() &&
            !start_file_info.doc_id.empty());

        // Warn about invalid fields

        if (actions.doc_type != "library")
        {
            std::vector<std::string> invalid_attributes;

            if (!purpose.empty())
                invalid_attributes.push_back("purpose");

            if (!categories.empty())
                invalid_attributes.push_back("category");

            if (!dirname.empty())
                invalid_attributes.push_back("dirname");

            if(!invalid_attributes.empty())
            {
                detail::outwarn(actions.current_file->path,1)
                    << (invalid_attributes.size() > 1 ?
                        "Invalid attributes" : "Invalid attribute")
                    << " for '" << detail::utf8(actions.doc_type) << " document info': "
                    << detail::utf8(boost::algorithm::join(invalid_attributes, ", "))
                    << "\n"
                    ;
            }
        }

        // Write out header

        if (docinfo_type == docinfo_main)
        {
            out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                << "<!DOCTYPE "
                << actions.doc_type
                << " PUBLIC \"-//Boost//DTD BoostBook XML V1.0//EN\"\n"
                << "     \"http://www.boost.org/tools/boostbook/dtd/boostbook.dtd\">\n"
                ;
        }

        out << '<' << actions.doc_type << "\n"
            << "    id=\""
            << start_file_info.placeholder
            << "\"\n";

        if(!lang.empty())
        {
            out << "    lang=\""
                << doc_info_output(lang, 106)
                << "\"\n";
        }

        if(actions.doc_type == "library")
        {
            out << "    name=\"" << doc_info_output(doc_title, 106) << "\"\n";
        }

        // Set defaults for dirname + last_revision

        if(!dirname.empty() || actions.doc_type == "library")
        {
            out << "    dirname=\"";
            if (!dirname.empty())
                out << doc_info_output(dirname, 106);
            else
                out << start_file_info.doc_id;
            out << "\"\n";
        }

        out << "    last-revision=\"";
        if (!last_revision.empty())
        {
            out << doc_info_output(last_revision, 106);
        }
        else
        {
            // default value for last-revision is now

            char strdate[64];
            strftime(
                strdate, sizeof(strdate),
                (debug_mode ?
                    "DEBUG MODE Date: %Y/%m/%d %H:%M:%S $" :
                    "$" /* prevent CVS substitution */ "Date: %Y/%m/%d %H:%M:%S $"),
                current_gm_time
            );

            out << strdate;
        }

        out << "\" \n"
            << "    xmlns:xi=\"http://www.w3.org/2001/XInclude\">\n";

        std::ostringstream tmp;

        if(!authors.empty())
        {
            tmp << "    <authorgroup>\n";
            BOOST_FOREACH(value_consumer author_values, authors)
            {
                while (author_values.check()) {
                    value surname = author_values.consume(doc_info_tags::author_surname);
                    value first = author_values.consume(doc_info_tags::author_first);
    
                    tmp << "      <author>\n"
                        << "        <firstname>"
                        << doc_info_output(first, 106)
                        << "</firstname>\n"
                        << "        <surname>"
                        << doc_info_output(surname, 106)
                        << "</surname>\n"
                        << "      </author>\n";
                }
            }
            tmp << "    </authorgroup>\n";
        }

        BOOST_FOREACH(value_consumer copyright, copyrights)
        {
            while(copyright.check())
            {
                tmp << "\n" << "    <copyright>\n";
    
                while(copyright.check(doc_info_tags::copyright_year))
                {
                    value year_start_value = copyright.consume();
                    int year_start = year_start_value.get_int();
                    int year_end =
                        copyright.check(doc_info_tags::copyright_year_end) ?
                        copyright.consume().get_int() :
                        year_start;
    
                    if (year_end < year_start) {
                        ++actions.error_count;
    
                        detail::outerr(actions.current_file, copyright.begin()->get_position())
                            << "Invalid year range: "
                            << year_start
                            << "-"
                            << year_end
                            << "."
                            << std::endl;
                    }
    
                    for(; year_start <= year_end; ++year_start)
                        tmp << "      <year>" << year_start << "</year>\n";
                }
            
                tmp << "      <holder>"
                    << doc_info_output(copyright.consume(doc_info_tags::copyright_name), 106)
                    << "</holder>\n"
                    << "    </copyright>\n"
                    << "\n"
                ;
            }
        }

        if (!license.empty())
        {
            tmp << "    <legalnotice id=\""
                << actions.ids.add_id("legal", id_category::generated)
                << "\">\n"
                << "      <para>\n"
                << "        " << doc_info_output(license, 103) << "\n"
                << "      </para>\n"
                << "    </legalnotice>\n"
                << "\n"
            ;
        }

        if (!purpose.empty())
        {
            tmp << "    <" << actions.doc_type << "purpose>\n"
                << "      " << doc_info_output(purpose, 103)
                << "    </" << actions.doc_type << "purpose>\n"
                << "\n"
                ;
        }

        BOOST_FOREACH(value_consumer values, categories) {
            value category = values.optional_consume();
            if(!category.empty()) {
                tmp << "    <" << actions.doc_type << "category name=\"category:"
                    << doc_info_output(category, 106)
                    << "\"></" << actions.doc_type << "category>\n"
                    << "\n"
                ;
            }
            values.finish();
        }

        BOOST_FOREACH(value_consumer biblioid, biblioids)
        {
            value class_ = biblioid.consume(doc_info_tags::biblioid_class);
            value value_ = biblioid.consume(doc_info_tags::biblioid_value);
            
            tmp << "    <biblioid class=\""
                << class_.get_quickbook()
                << "\">"
                << doc_info_output(value_, 106)
                << "</biblioid>"
                << "\n"
                ;
            biblioid.finish();
        }

        if(actions.doc_type != "library") {
            write_document_title(out, doc_title, version);
        }

        std::string docinfo = tmp.str();
        if(!docinfo.empty())
        {
            out << "  <" << actions.doc_type << "info>\n"
                << docinfo
                << "  </" << actions.doc_type << "info>\n"
                << "\n"
            ;
        }

        if(actions.doc_type == "library") {
            write_document_title(out, doc_title, version);
        }
    }
    
    void post(collector& out, quickbook::actions& actions, docinfo_types docinfo_type)
    {
        // We've finished generating our output. Here's what we'll do
        // *after* everything else.

        // Close any open sections.
        if (docinfo_type && actions.ids.section_level() > 1) {
            detail::outwarn(actions.current_file->path)
                << "Missing [endsect] detected at end of file."
                << std::endl;

            while(actions.ids.section_level() > 1) {
                out << "</section>";
                actions.ids.end_section();
            }
        }

        actions.ids.end_file();
        if (docinfo_type) out << "\n</" << actions.doc_type << ">\n\n";
    }

    static void write_document_title(collector& out, value const& title, value const& version)
    {
        if (!title.empty())
        {
            out << "  <title>"
                << doc_info_output(title, 106);
            if (!version.empty()) {
                out << ' ' << doc_info_output(version, 106);
            }
            out<< "</title>\n\n\n";
        }
    }
}
