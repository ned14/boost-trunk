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
#include "quickbook.hpp"
#include "utils.hpp"
#include "input_path.hpp"
#include "actions_class.hpp"
#include "doc_info_tags.hpp"

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
        while(c.is(tag)) {
            p = c.consume();
            ++count;
        }

        if(count > 1) duplicates->push_back(doc_info_attributes::name(tag));

        return p;
    }

    std::vector<value> consume_multiple(value_consumer& c, value::tag_type tag)
    {
        std::vector<value> values;
        
        while(c.is(tag)) {
            values.push_back(c.consume());
        }
        
        return values;
    }

    void pre(collector& out, quickbook::actions& actions, bool ignore_docinfo)
    {
        // The doc_info in the file has been parsed. Here's what we'll do
        // *before* anything else.

        value_consumer values = actions.values.get();
        std::vector<std::string> duplicates;

        value doc_title;
        if (values.is())
        {
            actions.doc_type = values.consume(doc_info_tags::type).get_quickbook();
            doc_title = values.consume(doc_info_tags::title);
            actions.doc_title_qbk = doc_title.get_quickbook();
        }

        value id = consume_last(values, doc_info_attributes::id, &duplicates);
        value dirname = consume_last(values, doc_info_attributes::dirname, &duplicates);
        value last_revision = consume_last(values, doc_info_attributes::last_revision, &duplicates);
        value purpose = consume_last(values, doc_info_attributes::purpose, &duplicates);
        std::vector<value> categories = consume_multiple(values, doc_info_attributes::category);
        value lang = consume_last(values, doc_info_attributes::lang, &duplicates);
        value version = consume_last(values, doc_info_attributes::version, &duplicates);
        std::vector<value> authors = consume_multiple(values, doc_info_attributes::authors);
        std::vector<value> copyrights = consume_multiple(values, doc_info_attributes::copyright);
        value license = consume_last(values, doc_info_attributes::license, &duplicates);
        std::vector<value> biblioids = consume_multiple(values, doc_info_attributes::biblioid);

        BOOST_ASSERT(!values.is());

        if(!duplicates.empty())
        {
            detail::outwarn(actions.filename,1)
                << (duplicates.size() > 1 ?
                    "Duplicate attributes" : "Duplicate attribute")
                << ":" << detail::utf8(boost::algorithm::join(duplicates, ", "))
                << "\n"
                ;
        }

        if (!id.is_empty())
            actions.doc_id = id.get_quickbook();

        if (actions.doc_id.empty())
            actions.doc_id = detail::make_identifier(
                actions.doc_title_qbk.begin(),actions.doc_title_qbk.end());
        
        if (dirname.is_empty() && actions.doc_type == "library") {
            if (!id.is_empty()) {
                dirname = id;
            }
            else {
                dirname = qbk_bbk_value(actions.doc_id, doc_info_attributes::dirname);
            }
        }


        if (last_revision.is_empty())
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
            last_revision = qbk_bbk_value(strdate, doc_info_attributes::last_revision);
        }

        // if we're ignoring the document info, we're done.
        if (ignore_docinfo)
        {
            return;
        }

        // Quickbook version

        if (qbk_major_version == -1)
        {
            // hard code quickbook version to v1.1
            qbk_major_version = 1;
            qbk_minor_version = 1;
            qbk_version_n = 101;
            detail::outwarn(actions.filename,1)
                << "Warning: Quickbook version undefined. "
                "Version 1.1 is assumed" << std::endl;
        }
        else
        {
            qbk_version_n = ((unsigned) qbk_major_version * 100) +
                (unsigned) qbk_minor_version;
        }
        
        if (qbk_version_n == 106)
        {
            detail::outwarn(actions.filename,1)
                << "Quickbook 1.6 is still under development and is "
                "likely to change in the future." << std::endl;
        }
        else if(qbk_version_n < 100 || qbk_version_n > 106)
        {
            detail::outerr(actions.filename,1)
                << "Unknown version of quickbook: quickbook "
                << qbk_major_version
                << "."
                << qbk_minor_version
                << std::endl;
            ++actions.error_count;
        }

        // Warn about invalid fields

        if (actions.doc_type != "library")
        {
            std::vector<std::string> invalid_attributes;

            if (!purpose.is_empty())
                invalid_attributes.push_back("purpose");

            if (!categories.empty())
                invalid_attributes.push_back("category");

            if (!dirname.is_empty())
                invalid_attributes.push_back("dirname");

            if(!invalid_attributes.empty())
            {
                detail::outwarn(actions.filename,1)
                    << (invalid_attributes.size() > 1 ?
                        "Invalid attributes" : "Invalid attribute")
                    << " for '" << detail::utf8(actions.doc_type) << " document info': "
                    << detail::utf8(boost::algorithm::join(invalid_attributes, ", "))
                    << "\n"
                    ;
            }
        }

        // Write out header

        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            << "<!DOCTYPE "
            << actions.doc_type
            << " PUBLIC \"-//Boost//DTD BoostBook XML V1.0//EN\"\n"
            << "     \"http://www.boost.org/tools/boostbook/dtd/boostbook.dtd\">\n"
            << '<' << actions.doc_type << "\n"
            << "    id=\""
            << actions.doc_id
            << "\"\n";
        
        if(!lang.is_empty())
        {
            out << "    lang=\""
                << doc_info_output(lang, 106)
                << "\"\n";
        }

        if(actions.doc_type == "library")
        {
            out << "    name=\"" << doc_info_output(doc_title, 106) << "\"\n";
        }

        if(!dirname.is_empty())
        {
            out << "    dirname=\""
                << doc_info_output(dirname, 106)
                << "\"\n";
        }

        out << "    last-revision=\""
            << doc_info_output(last_revision, 106)
            << "\" \n"
            << "    xmlns:xi=\"http://www.w3.org/2001/XInclude\">\n";

        std::ostringstream tmp;

        if(!authors.empty())
        {
            tmp << "    <authorgroup>\n";
            BOOST_FOREACH(value_consumer author_values, authors)
            {
                while (author_values.is()) {
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
            tmp << "\n" << "    <copyright>\n";

            while(copyright.is(doc_info_tags::copyright_year))
            {
                tmp << "      <year>" << copyright.consume().get_quickbook() << "</year>\n";
            }
        
            tmp << "      <holder>"
                << doc_info_output(copyright.consume(doc_info_tags::copyright_name), 106)
                << "</holder>\n"
                << "    </copyright>\n"
                << "\n"
            ;
        }

        if (!license.is_empty())
        {
            tmp << "    <legalnotice>\n"
                << "      <para>\n"
                << "        " << doc_info_output(license, 103) << "\n"
                << "      </para>\n"
                << "    </legalnotice>\n"
                << "\n"
            ;
        }

        if (!purpose.is_empty())
        {
            tmp << "    <" << actions.doc_type << "purpose>\n"
                << "      " << doc_info_output(purpose, 103)
                << "    </" << actions.doc_type << "purpose>\n"
                << "\n"
                ;
        }

        BOOST_FOREACH(value const& category, categories) {
            if(!category.is_empty()) {
                tmp << "    <" << actions.doc_type << "category name=\"category:"
                    << doc_info_output(category, 106)
                    << "\"></" << actions.doc_type << "category>\n"
                    << "\n"
                ;
            }
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
    
    void post(collector& out, quickbook::actions& actions, bool ignore_docinfo)
    {
        // if we're ignoring the document info, do nothing.
        if (ignore_docinfo)
        {
            return;
        } 

        // We've finished generating our output. Here's what we'll do
        // *after* everything else.
        out << "\n</" << actions.doc_type << ">\n\n";
    }

    static void write_document_title(collector& out, value const& title, value const& version)
    {
        if (!title.is_empty())
        {
            out << "  <title>"
                << doc_info_output(title, 106);
            if (!version.is_empty()) {
                out << ' ' << doc_info_output(version, 106);
            }
            out<< "</title>\n\n\n";
        }
    }
}
