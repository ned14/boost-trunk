/*=============================================================================
    Spirit V1.5.2
    Copyright (c) 2001-2003 Hartmut Kaiser
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

    Permission to copy, use, modify, sell and distribute this software is
    granted provided this copyright notice appears in all copies. This
    software is provided "as is" without express or implied warranty, and
    with no claim as to its suitability for any purpose.
=============================================================================*/

#if !defined(PARSE_TREE_XML_HPP)
#define PARSE_TREE_XML_HPP

///////////////////////////////////////////////////////////////////////////////
#include "boost/spirit/spirit_tree_fwd.hpp"

namespace boost { namespace spirit {

///////////////////////////////////////////////////////////////////////////////
//
//  Dump a parse tree as a xml stream
//
//      The functions 'tree_to_xml' can be used to output a parse tree as a xml
//      stream into the given ostream. The parameters have the following
//      meaning:
//
//  mandatory parameters:
//      ostrm       The output stream used for streaming the parse tree.
//      tree        The parse tree to output.
//
//  optional parameters:
//      input_line  The input line from which the parse tree was
//                  generated (if given, it is used to output a comment
//                  containing this line).
//      id_to_name  A map, which is used for converting the rule id's contained
//                  in the parse tree to readable strings. Here a auxiliary
//                  associative container can be used, which maps a rule_id to
//                  a std::string (i.e. a std::map<rule_id, std::string>).
//      get_token_id
//                  A function or functor, which takes an instance of a token
//                  and which should return a token id (i.e. something like
//                  'int f(char const c)').
//      get_token_value
//                  A function or functor, which takes an instance of a token
//                  and which should return a readable representation of this
//                  token (i.e. something like 'std::string f(char const c)').
//
//  The structure of the generated xml stream conforms to the DTD given in the
//  file 'parsetree.dtd'. This file is located in the spirit/tree directory.
//
///////////////////////////////////////////////////////////////////////////////

    template <
        typename TreeNodeT, typename AssocContainerT,
        typename GetIdT, typename GetValueT
    >
    void tree_to_xml (std::ostream &ostrm, TreeNodeT const &tree,
        std::string const &input_line, AssocContainerT const& id_to_name,
        GetIdT const &get_token_id, GetValueT const &get_token_value);

    template <typename TreeNodeT, typename AssocContainerT>
    void tree_to_xml (std::ostream &ostrm, TreeNodeT const &tree,
        std::string const &input_line, AssocContainerT const& id_to_name);

    template <typename TreeNodeT>
    void tree_to_xml (std::ostream &ostrm, TreeNodeT const &tree,
        std::string const &input_line = "");

}} // namespace boost::spirit

#include "boost/spirit/tree/impl/parse_tree_xml.ipp"

#endif // !defined(PARSE_TREE_XML_HPP)
