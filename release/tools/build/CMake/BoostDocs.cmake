##########################################################################
# Boost Documentation Generation                                         #
##########################################################################
# Copyright (C) 2008 Douglas Gregor <doug.gregor@gmail.com>              #
#                                                                        #
# Distributed under the Boost Software License, Version 1.0.             #
# See accompanying file LICENSE_1_0.txt or copy at                       #
#   http://www.boost.org/LICENSE_1_0.txt                                 #
##########################################################################
# Important developer macros in this file:                               #
#                                                                        #
##########################################################################

# Transforms the source XML file into the target XML file by applying
# the given XSL stylesheet.
#
#   transform_xml(target source stylesheet
#                 [DEPENDS depend1 depend2 ...]
#                 [CATALOG catalog]
#
# 
macro(transform_xml TARGET SOURCE STYLESHEET)
  parse_arguments(THIS_XSL
    "DEPENDS;CATALOG"
    ""
    ${ARGN}
    )
  
  if (THIS_XSL_CATALOG)
    set(THIS_XSL_CATALOG "XML_CATALOG_FILES=${THIS_XSL_CATALOG}")
  endif ()

  # Run the XSLT processor.
  add_custom_command(OUTPUT ${TARGET}
    COMMAND ${THIS_XSL_CATALOG} ${XSLTPROC} --xinclude -o ${TARGET} ${STYLESHEET} ${SOURCE}
    DEPENDS ${SOURCE})

  # set_source_files_properties(${TARGET} PROPERTIES GENERATED TRUE)
endmacro(transform_xml)

macro(boost_add_documentation SOURCE)
  parse_arguments(THIS_DOC
    "DEPENDS"
    ""
    ${ARGN})

  # If SOURCE does not have a 
  get_filename_component(THIS_DOC_SOURCE_PATH ${SOURCE} PATH)
  if(THIS_DOC_SOURCE_PATH STREQUAL "")
    set(THIS_DOC_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}")
  else()
    set(THIS_DOC_SOURCE_PATH ${SOURCE})
  endif()

  # Figure out the source file extension, which will tell us how to
  # build the documentation.
  get_filename_component(THIS_DOC_EXT ${SOURCE} EXT)
  string(TOUPPER ${THIS_DOC_EXT} THIS_DOC_EXT)
  if (THIS_DOC_EXT STREQUAL ".XML")
    # Transform BoostBook XML into DocBook XML
    get_filename_component(SOURCE_FILENAME ${SOURCE} NAME_WE)
    set(DOCBOOK_FILE ${SOURCE_FILENAME}.docbook)
    transform_xml(${DOCBOOK_FILE}
      ${THIS_DOC_SOURCE_PATH} 
      ${BOOSTBOOK_XSL_DIR}/docbook.xsl
      CATALOG ${CMAKE_BINARY_DIR}/catalog.xml
      DEPENDS ${THIS_DOC_DEPENDS})
    add_custom_target(docbook 
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${DOCBOOK_FILE})

    # Transform DocBook into other formats
    boost_add_documentation(${CMAKE_CURRENT_BINARY_DIR}/${DOCBOOK_FILE})
  elseif(THIS_DOC_EXT STREQUAL ".DOCBOOK")
    add_custom_target(html
      COMMAND "XML_CATALOG_FILES=${CMAKE_BINARY_DIR}/catalog.xml"
        ${XSLTPROC} --xinclude -o html/ ${BOOSTBOOK_XSL_DIR}/html.xsl
        ${THIS_DOC_SOURCE_PATH}
      DEPENDS ${THIS_DOC_SOURCE_PATH} ${THIS_DOC_DEPENDS})
  else()
    message(SEND_ERROR "Unknown documentation source kind ${SOURCE}.")
  endif()
endmacro(boost_add_documentation)
            

##########################################################################
# Documentation tools configuration                                      #
##########################################################################

# Downloads the DocBook DTD into a place where DOCBOOK_DTD_DIR can
# find it.
macro(download_docbook_dtd)
  if (NOT DOCBOOK_DTD_DIR)
    set(DOCBOOK_DTD_FILENAME "docbook-xml-${WANT_DOCBOOK_DTD_VERSION}.zip")
    set(DOCBOOK_DTD_URL 
      "http://www.oasis-open.org/docbook/xml/${WANT_DOCBOOK_DTD_VERSION}/${DOCBOOK_DTD_FILENAME}")
    message(STATUS "Downloading DocBook DTD from ${DOCBOOK_DTD_URL}...")
    file(DOWNLOAD 
      "${DOCBOOK_DTD_URL}"
      "${CMAKE_BINARY_DIR}/${DOCBOOK_DTD_FILENAME}"
      TIMEOUT 60 STATUS DOCBOOK_DTD_STATUS)
    list(GET DOCBOOK_DTD_STATUS 0 DOCBOOK_DTD_ERROR)
    if (DOCBOOK_DTD_ERROR EQUAL 0)
      # Download successful! Extract the DTD ZIP file.
      message(STATUS "Extracting DocBook DTD...")
      execute_process(
        COMMAND ${UNZIP} -d docbook-dtd-${WANT_DOCBOOK_DTD_VERSION} -q "${CMAKE_BINARY_DIR}/${DOCBOOK_DTD_FILENAME}"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE UNZIP_DTD_RESULT)
      if (UNZIP_DTD_RESULT EQUAL 0)
        # Extraction successful. Cleanup the downloaded file.
        file(REMOVE ${CMAKE_BINARY_DIR}/${DOCBOOK_DTD_FILENAME})
        set(DOCBOOK_DTD_DIR 
          ${CMAKE_BINARY_DIR}/docbook-dtd-${WANT_DOCBOOK_DTD_VERSION}
          CACHE PATH "Path to the DocBook DTD" FORCE)
      else()
        # We failed: report the error to the user
        message(SEND_ERROR "Extraction of DocBook DTD archive ${DOCBOOK_DTD_FILENAME} failed with error \"${UNZIP_DTD_RESULT}\". DocBook DTD and XSL autoconfiguration cannot continue.")
      endif ()
    else()
    list(GET DOCBOOK_DTD_STATUS 1 DOCBOOK_DTD_ERRORMSG)
      message(SEND_ERROR "Unable to download DocBook DTD from ${DOCBOOK_DTD_URL}. Error was: \"${DOCBOOK_DTD_ERRORMSG}\"")
    endif()
  endif()
endmacro(download_docbook_dtd)

# Downloads the DocBook XSL into a place where DOCBOOK_XSL_DIR can
# find it.
macro(download_docbook_xsl)
  if (NOT DOCBOOK_XSL_DIR)
    set(DOCBOOK_XSL_FILENAME "docbook-xsl-${WANT_DOCBOOK_XSL_VERSION}.zip")
    set(DOCBOOK_XSL_URL 
      "${SOURCEFORGE_MIRROR}/sourceforge/docbook/${DOCBOOK_XSL_FILENAME}")
    message(STATUS "Downloading DocBook XSL from ${DOCBOOK_XSL_URL}...")
    file(DOWNLOAD 
      "${DOCBOOK_XSL_URL}"
      "${CMAKE_BINARY_DIR}/${DOCBOOK_XSL_FILENAME}"
      TIMEOUT 60 STATUS DOCBOOK_XSL_STATUS)
    list(GET DOCBOOK_XSL_STATUS 0 DOCBOOK_XSL_ERROR)
    if (DOCBOOK_XSL_ERROR EQUAL 0)
      # Download successful! Extract the XSL ZIP file.
      message(STATUS "Extracting DocBook XSL stylesheets...")
      execute_process(
        COMMAND ${UNZIP} -q "${CMAKE_BINARY_DIR}/${DOCBOOK_XSL_FILENAME}"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE UNZIP_XSL_RESULT)
      if (UNZIP_XSL_RESULT EQUAL 0)
        # Extraction successful. Clean up the downloaded file.
        file(REMOVE ${CMAKE_BINARY_DIR}/${DOCBOOK_XSL_FILENAME})
        set(DOCBOOK_XSL_DIR 
          ${CMAKE_BINARY_DIR}/docbook-xsl-${WANT_DOCBOOK_XSL_VERSION}
          CACHE PATH "Path to the DocBook XSL stylesheets" FORCE)       
      else()
        # We failed: report the error to the user
        message(SEND_ERROR "Extraction of DocBook XSL archive ${DOCBOOK_XSL_FILENAME} failed with error \"${UNZIP_XSL_RESULT}\". DocBook XSL and XSL autoconfiguration cannot continue.")
      endif ()
    else()
    list(GET DOCBOOK_XSL_STATUS 1 DOCBOOK_XSL_ERRORMSG)
      message(SEND_ERROR "Unable to download DocBook XSL from ${DOCBOOK_XSL_URL}. Error was: \"${DOCBOOK_XSL_ERRORMSG}\". You might want to try another SourceForge mirror site by changing the advanced configuration variable SOURCEFORGE_MIRROR.")
    endif()
  endif()
endmacro(download_docbook_xsl)

# Preferred versions of DocBook stylesheets and utilities. We don't
# require these, but we know that they work.
set(WANT_DOCBOOK_DTD_VERSION 4.2)
set(WANT_DOCBOOK_XSL_VERSION 1.73.2)

# Find xsltproc to transform XML documents via XSLT
find_program(XSLTPROC xsltproc DOC "xsltproc transforms XML via XSLT")

# Find the DocBook DTD (version 4.2)
find_path(DOCBOOK_DTD_DIR docbookx.dtd
  PATHS "${CMAKE_BINARY_DIR}/docbook-dtd-${WANT_DOCBOOK_DTD_VERSION}"
  DOC "Path to the DocBook DTD")

# Find the DocBook XSL stylesheets
find_path(DOCBOOK_XSL_DIR html/html.xsl
  PATHS "${CMAKE_BINARY_DIR}/docbook-xsl-${WANT_DOCBOOK_XSL_VERSION}"
  DOC "Path to the DocBook XSL stylesheets")

# Find the BoostBook DTD (it should be in the distribution!)
find_path(BOOSTBOOK_DTD_DIR boostbook.dtd
  PATHS ${CMAKE_SOURCE_DIR}/tools/boostbook/dtd
  DOC "Path to the BoostBook DTD")
mark_as_advanced(BOOSTBOOK_DTD_DIR)

# Find the BoostBook XSL stylesheets (they should be in the distribution!)
find_path(BOOSTBOOK_XSL_DIR docbook.xsl
  PATHS ${CMAKE_SOURCE_DIR}/tools/boostbook/xsl
  DOC "Path to the BoostBook XSL stylesheets")
mark_as_advanced(BOOSTBOOK_XSL_DIR)

if (XSLTPROC)
  if (DOCBOOK_DTD_DIR AND DOCBOOK_XSL_DIR)
    # We have all we need for documentation generation.
    option(BUILD_DOCUMENTATION "Whether to build library documentation" ON)

    # Generate an XML catalog file.
    configure_file(${CMAKE_SOURCE_DIR}/tools/build/CMake/catalog.xml.in
      ${CMAKE_BINARY_DIR}/catalog.xml 
      @ONLY)
  else()
    # Look for "unzip", because we'll need to to permit downloading
    # the DocBook DTD and XSL stylesheets.
    find_program(UNZIP unzip DOC "Used to extract ZIP archives")

    if (UNZIP)
      option(DOCBOOK_AUTOCONFIG 
        "Automatically download and configure DocBook DTD and XSL" OFF)
      set(SOURCEFORGE_MIRROR "http://dl.sourceforge.net"
        CACHE STRING "SourceForge mirror used to download DocBook XSL during autoconfiguration")
      mark_as_advanced(SOURCEFORGE_MIRROR)
      if (DOCBOOK_AUTOCONFIG)
        message(STATUS "Initiating DocBook DTD and XSL autoconfiguration...")
        download_docbook_dtd()
        download_docbook_xsl()
      endif (DOCBOOK_AUTOCONFIG)
    endif()
  endif()
endif()


