<?xml version="1.0" encoding="utf-8"?>
<!--

Copyright MetaCommunications, Inc. 2003-2004.

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)

-->

<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:exsl="http://exslt.org/common"
    xmlns:func="http://exslt.org/functions"
    xmlns:set="http://exslt.org/sets"
    xmlns:meta="http://www.meta-comm.com"
    extension-element-prefixes="func exsl"
    exclude-result-prefixes="exsl set meta"
    version="1.0">

    <xsl:import href="common.xsl"/>

    <xsl:output method="html" 
        doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN" 
        encoding="utf-8" 
        indent="yes"
        />

    <xsl:param name="links_file"/>
    <xsl:param name="mode"/>
    <xsl:param name="source"/>
    <xsl:param name="run_date"/>
    <xsl:param name="comment_file"/>
    <xsl:param name="expected_results_file"/>
    <xsl:param name="explicit_markup_file"/>
    <xsl:param name="release"/>

    <!-- the author-specified expected test results -->
    <xsl:variable name="explicit_markup" select="document( $explicit_markup_file )"/>
    <xsl:variable name="expected_results" select="document( $expected_results_file )" />
     
    <!-- necessary indexes -->
    <xsl:key 
        name="test_name_key" 
        match="test-log" 
        use="concat( @library, '&gt;@&lt;', @test-name )"/>
    <xsl:key name="toolset_key" match="test-log" use="@toolset"/>

    <!-- runs / toolsets -->
    <xsl:variable name="run_toolsets" select="meta:test_structure( /, $release )"/>

    <!-- libraries -->

    <xsl:variable name="test_case_logs" select="//test-log[ meta:is_test_log_a_test_case(.) ]"/>
    <xsl:variable name="libraries" select="set:distinct( $test_case_logs/@library )"/>


    <!-- modes -->

    <xsl:variable name="alternate_mode">
        <xsl:choose>
        <xsl:when test="$mode='user'">developer</xsl:when>
        <xsl:otherwise>user</xsl:otherwise>
        </xsl:choose>
    </xsl:variable>

    <xsl:variable name="release_postfix">
        <xsl:if test="$release='yes'">_release</xsl:if>
    </xsl:variable>


    <xsl:template name="test_type_col">
        <td class="test-type">
        <a href="http://www.boost.org/status/compiler_status.html#Understanding" class="legend-link" target="_top">
            <xsl:variable name="test_type" select="./@test-type"/>
            <xsl:choose>
            <xsl:when test="$test_type='run_pyd'">      <xsl:text>r</xsl:text>  </xsl:when>
            <xsl:when test="$test_type='run'">          <xsl:text>r</xsl:text>  </xsl:when>
            <xsl:when test="$test_type='run_fail'">     <xsl:text>rf</xsl:text> </xsl:when>
            <xsl:when test="$test_type='compile'">      <xsl:text>c</xsl:text>  </xsl:when>
            <xsl:when test="$test_type='compile_fail'"> <xsl:text>cf</xsl:text> </xsl:when>
            <xsl:otherwise>
                <xsl:message terminate="yes">Incorrect test type "<xsl:value-of select="$test_type"/>"</xsl:message>
            </xsl:otherwise>
            </xsl:choose>
        </a>
        </td>
    </xsl:template>


    <xsl:template match="/">

        <exsl:document href="debug.xml" 
          method="xml" 
          encoding="utf-8"
          indent="yes">

            <debug>
                <runs>
                    <xsl:for-each select="$run_toolsets">
                        <xsl:copy-of select="."/>
                    </xsl:for-each>
                </runs>
            </debug>

        </exsl:document>

        <xsl:variable name="index_path" select="concat( 'index_', $release_postfix, '.html' )"/>
        
        <!-- Index page -->
        <head>
            <link rel="stylesheet" type="text/css" href="../master.css" title="master" />
            <title>Boost regression: <xsl:value-of select="$source"/></title>
        </head>
        <frameset cols="190px,*" frameborder="0" framespacing="0" border="0">
            <frame name="tocframe" src="toc{$release_postfix}.html" scrolling="auto"/>
            <frame name="docframe" src="{$index_path}" scrolling="auto"/>
        </frameset>

        <!-- Index content -->
        <xsl:message>Writing document <xsl:value-of select="$index_path"/></xsl:message>

        <exsl:document href="{$index_path}" 
            method="html" 
            doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
            encoding="utf-8"
            indent="yes">

            <html>
            <head>
                <link rel="stylesheet" type="text/css" href="../master.css" title="master" />
            </head>
            <body>

                <img border="0" src="http://www.boost.org/boost.png" width="277" height="86" align="right" alt="Boost logo"></img>

                <h1 class="page-title">
                    <xsl:value-of select="$mode"/>
                    <xsl:text> report: </xsl:text>
                    <a class="hover-link" href="summary.html" target="_top"><xsl:value-of select="$source"/></a>
                </h1>                            

                <div class="report-info">
                    <div>
                        <b>Report Time: </b> <xsl:value-of select="$run_date"/>
                    </div>
                      
                    <div>
                        <b>Purpose: </b>
                        <xsl:choose>
                            <xsl:when test="$mode='user'">
                                The purpose of this report is to help a user to find out whether a particular library 
                                works on the particular compiler(s). For CVS "health report", see 
                                <a href="../{$alternate_mode}/index.html" target="_top">developer summary</a>.
                            </xsl:when>
                            <xsl:when test="$mode='developer'">
                                Provides Boost developers with visual indication of the CVS "health". For user-level 
                                report, see <a href="../{$alternate_mode}/index.html" target="_top">user summary</a>.
                            </xsl:when>
                        </xsl:choose>
                    </div>
                </div>
                              
                <div class="comment">
                    <xsl:if test="$comment_file != ''">
                        <xsl:copy-of select="document( $comment_file )"/>
                    </xsl:if>
                </div>

            </body>
            </html>
        </exsl:document>  

              
        <xsl:variable name="multiple.libraries" select="count( $libraries ) > 1"/>

        <!-- TOC -->
        <xsl:if test="$multiple.libraries">
            
            <xsl:variable name="toc_path" select="concat( 'toc', $release_postfix, '.html' )"/>
            <xsl:message>Writing document <xsl:value-of select="$toc_path"/></xsl:message>

            <exsl:document href="{$toc_path}" 
                method="html" 
                doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
                encoding="utf-8"
                indent="yes">

            <html>
            <head>
                <link rel="stylesheet" type="text/css" href="../master.css" title="master" />
            </head>
            <body class="{$mode}-toc">
                <div class="toc-header-entry">
                    <a href="index{$release_postfix}.html" class="toc-entry" target="_top">Report info</a>
                </div>
                <div class="toc-header-entry">
                    <a href="summary{$release_postfix}.html" class="toc-entry" target="_top">Summary</a>
                </div>
                
                <xsl:if test="$mode='developer'">
                    <div class="toc-header-entry">
                        <a href="issues.html" class="toc-entry" target="_top">Unresolved issues</a>
                    </div>
                </xsl:if>
                
                <div class="toc-header-entry">
                    <xsl:call-template name="insert_view_link">
                        <xsl:with-param name="page" select="'index'"/>
                        <xsl:with-param name="class" select="'toc-entry'"/>
                        <xsl:with-param name="release" select="$release"/>
                    </xsl:call-template>
                </div>

                <hr/>
                                  
                <xsl:for-each select="$libraries">
                    <xsl:sort select="." order="ascending" />
                    <xsl:variable name="library_page" select="meta:encode_path(.)" />
                    <div class="toc-entry">
                        <a href="{$library_page}{$release_postfix}.html" class="toc-entry" target="_top">
                            <xsl:value-of select="."/>
                        </a>
                    </div>
                </xsl:for-each>
            </body>
            </html>
            
            </exsl:document>  
        </xsl:if> 
         
        <!-- Libraries -->
        <xsl:for-each select="$libraries[ meta:show_library( ., $release )]">
            <xsl:sort select="." order="ascending" />
            <xsl:variable name="library" select="." />
            
            <xsl:variable name="library_results" select="concat( meta:encode_path( $library ), $release_postfix, '_.html' )"/>
            <xsl:variable name="library_page" select="concat( meta:encode_path( $library ), $release_postfix, '.html' )"/>

            <!-- Library page -->
            <xsl:message>Writing document <xsl:value-of select="$library_page"/></xsl:message>
            
            <exsl:document href="{$library_page}"
                method="html" 
                doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
                encoding="utf-8"
                indent="yes">

                <html>
                <head>
                    <link rel="stylesheet" type="text/css" href="../master.css" title="master" />
                    <title>Boost regression: <xsl:value-of select="$library"/>/<xsl:value-of select="$source"/></title>
                </head>
                <frameset cols="190px,*" frameborder="0" framespacing="0" border="0">
                <frame name="tocframe" src="toc{$release_postfix}.html" scrolling="auto"/>
                <frame name="docframe" src="{$library_results}" scrolling="auto"/>
                </frameset>
                </html>
            </exsl:document>  

            <!-- Library results frame -->
            <xsl:message>Writing document <xsl:value-of select="$library_results"/></xsl:message>
            
            <exsl:document href="{$library_results}"
                method="html" 
                doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
                encoding="utf-8"
                indent="yes">

                <html>
                <head>
                    <link rel="stylesheet" type="text/css" href="../master.css" title="master" />
                </head>
                  
                <body>

                <xsl:call-template name="insert_page_links">
                    <xsl:with-param name="page" select="meta:encode_path( $library )"/>
                    <xsl:with-param name="release" select="$release"/>
                </xsl:call-template>

                <h1 class="page-title">
                    <a class="hover-link" name="{$library}" href="http://www.boost.org/libs/{$library}" target="_top">
                        <xsl:value-of select="$library" />
                    </a>
                    <xsl:text>/</xsl:text>
                    <a class="hover-link" href="summary.html" target="_top"><xsl:value-of select="$source"/></a>
                </h1>

                <div class="report-info">
                    <b>Report Time: </b> <xsl:value-of select="$run_date"/>
                </div>

                <!-- library marks = library-unusable markup for toolsets in the report  -->
                <xsl:variable name="library_marks" select="$explicit_markup//library[ @name = $library ]/mark-unusable/toolset[  meta:re_match( @name, $run_toolsets//toolset/@name ) ]/.."/>
                <lmarks>
                    <xsl:copy-of select="$library_marks"/>
                </lmarks>

                <table border="0" cellspacing="0" cellpadding="0" class="library-table" width="1%" summary="Library results">

                    <thead>
                      <xsl:call-template name="insert_runners_rows">
                        <xsl:with-param name="mode" select="'details'"/>
                        <xsl:with-param name="top_or_bottom" select="'top'"/>
                        <xsl:with-param name="run_toolsets" select="$run_toolsets"/>
                      </xsl:call-template>
                      
                      <xsl:call-template name="insert_toolsets_row">
                        <xsl:with-param name="mode" select="'details'"/>
                        <xsl:with-param name="library_marks" select="$library_marks"/>
                        <xsl:with-param name="library" select="$library"/>
                      </xsl:call-template>
                    </thead>
                    <tfoot>
                      <xsl:call-template name="insert_toolsets_row">
                        <xsl:with-param name="mode" select="'details'"/>
                        <xsl:with-param name="library_marks" select="$library_marks"/>
                        <xsl:with-param name="library" select="$library"/>
                      </xsl:call-template>

                      <xsl:call-template name="insert_runners_rows">
                          <xsl:with-param name="mode" select="'details'"/>
                          <xsl:with-param name="top_or_bottom" select="'bottom'"/>
                      </xsl:call-template>
                    </tfoot>

                    <tbody>
                        <!-- lib_tests = test_log* -->
                        <xsl:variable name="lib_tests" select="$test_case_logs[@library = $library]" /> 

                        <!-- lib_unique_test_names = test_log* -->
                        <xsl:variable name="lib_unique_test_names" 
                            select="$lib_tests[ generate-id(.) = generate-id( key('test_name_key', concat( @library, '&gt;@&lt;', @test-name ) ) ) ]" />

                        <xsl:variable name="lib_corner_case_tests_markup" select="$explicit_markup//library[ @name = $library ]/test[ @corner-case='yes' ]"/>
                        
                        <xsl:variable name="lib_general_tests" 
                            select="meta:order_tests_by_name( $lib_unique_test_names[ not( @test-name = $lib_corner_case_tests_markup/@name ) ]  )"/>


                        <xsl:variable name="lib_corner_case_tests" select="meta:order_tests_by_name( $lib_unique_test_names[ @test-name = $lib_corner_case_tests_markup/@name ] ) " />


                        <!-- general tests section -->

                        <xsl:call-template name="insert_test_section">
                            <xsl:with-param name="library" select="$library"/>
                            <xsl:with-param name="section_test_names" select="$lib_general_tests"/>
                            <xsl:with-param name="lib_tests" select="$lib_tests"/>
                        </xsl:call-template>

                        <!-- corner-case tests section -->

                        <xsl:if test="count( $lib_corner_case_tests ) > 0">
                            <tr>
                                <!--<td colspan="2">&#160;</td>                  -->
                                <td class="library-corner-case-header" colspan="{count($run_toolsets/platforms/platform/runs/run/toolset) + 3 }" align="center">Corner-case tests</td>
                                <!--<td>&#160;</td>-->
                            </tr>

                        <xsl:call-template name="insert_test_section">
                            <xsl:with-param name="library" select="$library"/>
                            <xsl:with-param name="section_test_names" select="$lib_corner_case_tests"/>
                            <xsl:with-param name="lib_tests" select="$lib_tests"/>
                        </xsl:call-template>
                        
                    </xsl:if>

                    </tbody>
                </table>
                <xsl:if test="count( $library_marks/note ) > 0 ">
                    <table border="0" cellpadding="0" cellspacing="0" class="library-library-notes" summary="library notes">
                    <xsl:for-each select="$library_marks/note">
                        <tr class="library-library-note">
                        <td valign="top" width="3em">
                            <a name="{$library}-note-{position()}">
                            <span class="super"><xsl:value-of select="position()"/></span>
                            </a>
                        </td>
                        <td>
                            <xsl:variable name="refid" select="@refid"/>
                            <xsl:call-template name="show_note">
                                <xsl:with-param name="note" select="." />
                                <xsl:with-param name="references" select="$refid"/>
                            </xsl:call-template>
                        </td>
                        </tr>
                    </xsl:for-each>
                    </table>
                </xsl:if>
                    
                <xsl:copy-of select="document( concat( 'html/library_', $mode, '_legend.html' ) )"/>

                <xsl:call-template name="insert_page_links">
                    <xsl:with-param name="page" select="meta:encode_path( $library )"/>
                    <xsl:with-param name="release" select="$release"/>
                </xsl:call-template>

                </body>
                </html>
            
            </exsl:document>  

            </xsl:for-each>

    </xsl:template>
      

    <!-- insert test result with log file link -->

    <xsl:template name="insert_test_result">
        <xsl:param name="result"/>
        <xsl:param name="log_link"/>

        <xsl:choose>
            <xsl:when test="$log_link != ''">
                <xsl:text>&#160;&#160;</xsl:text>
                <a href="{$log_link}" class="log-link" target="_top">
                    <xsl:copy-of select="$result"/>
                </a>
                <xsl:text>&#160;&#160;</xsl:text>
            </xsl:when>
            <xsl:otherwise>
                <xsl:text>&#160;&#160;</xsl:text>
                <xsl:copy-of select="$result"/>
                <xsl:text>&#160;&#160;</xsl:text>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <!-- report developer status -->
    <xsl:template name="insert_cell_developer">
        <xsl:param name="library"/>
        <xsl:param name="toolset"/>
        <xsl:param name="test_log"/>
        
        <xsl:variable name="class" select="concat( 'library-', meta:result_cell_class( $library, $toolset, $test_log ) )"/>

        <xsl:variable name="cell_link">
            <xsl:choose>
                <xsl:when test="count( $test_log ) &gt; 1">
                    <xsl:variable name="variants_file_path" select="concat( meta:encode_path( concat( $test_log/../@runner, '-', $test_log/@library, '-', $test_log/@toolset, '-', $test_log/@test-name, '-variants' ) ), '.html' )"/>
                    <xsl:variable name="variants__file_path" select="concat( meta:encode_path( concat( $test_log/../@runner, '-', $test_log/@library, '-', $test_log/@toolset, '-', $test_log/@test-name, '-variants_' ) ), '.html' )"/>
                    <xsl:message>Writing variants file <xsl:value-of select="$variants_file_path"/></xsl:message>
                    
                    <exsl:document href="{$variants_file_path}"
                        method="html" 
                        doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
                        encoding="utf-8"
                        indent="yes">
                        <html>
                            <head>
                                <link rel="stylesheet" type="text/css" href="../master.css" title="master" />
                                <title>Boost regression: <xsl:value-of select="$library"/>/<xsl:value-of select="$source"/></title>
                            </head>
                            <frameset cols="190px,*" frameborder="0" framespacing="0" border="0">
                                <frame name="tocframe" src="toc{$release_postfix}.html" scrolling="auto"/>
                                <frame name="docframe" src="{$variants__file_path}" scrolling="auto"/>
                            </frameset>
                        </html>
                    </exsl:document>  

                    <exsl:document href="{$variants__file_path}"
                        method="html" 
                        doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
                        encoding="utf-8"
                        indent="yes">

                        <html>
                            <body>
                                <table>
                                    <xsl:for-each select="$test_log">
                                        <tr>
                                            <td>
                                                <!--<debug>
                                                    <xsl:copy-of select="."/>

                                                    <xsl:value-of select="meta:show_output( $explicit_markup, . )"/>
                                                    <xsl:value-of select="meta:log_file_path(.)"/>
                                                </debug>-->
                                                <xsl:choose>
                                                    <xsl:when test="meta:log_file_path(.) != ''">
                                                        <a href="{meta:log_file_path(.)}" target="_top" >
                                                            <xsl:value-of select="@target-directory"/>
                                                        </a>
                                                    </xsl:when>
                                                    <xsl:otherwise>
                                                        <xsl:value-of select="@target-directory"/>
                                                    </xsl:otherwise>
                                                </xsl:choose>
                                            </td>
                                        </tr>
                                    </xsl:for-each>
                                </table>
                            </body>
                        </html>
                    </exsl:document>           
                    <xsl:value-of select="$variants_file_path"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="meta:log_file_path($test_log)"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:variable>

        <td class="{$class}" title="{$test_log/@test-name}/{$toolset}">
        <xsl:choose>
             <xsl:when test="meta:is_unusable( $explicit_markup, $library, $toolset )">
                <xsl:call-template name="insert_test_result">
                    <xsl:with-param name="result" select="'n/a'"/>
                    <xsl:with-param name="log_link" select="$cell_link"/>
                </xsl:call-template>
            </xsl:when> 

            <xsl:when test="count( $test_log ) &lt; 1">
                <xsl:text>&#160;&#160;&#160;&#160;</xsl:text>
            </xsl:when> 
 
            <xsl:when test="$test_log/@result != 'success' and $test_log/@status = 'expected'">
                <xsl:call-template name="insert_test_result">
                    <xsl:with-param name="result">
                        <xsl:choose>
                            <xsl:when test="$test_log/@expected-reason != ''">
                                <xsl:text>fail?</xsl:text>
                            </xsl:when> 
                            <xsl:otherwise>
                                <xsl:text>fail*</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:with-param>
                    <xsl:with-param name="log_link" select="$cell_link"/>
                </xsl:call-template>
            </xsl:when>

            <xsl:when test="$test_log/@result != 'success' and $test_log/@status = 'unexpected'">
                <xsl:call-template name="insert_test_result">
                    <xsl:with-param name="result" select="'fail'"/>
                    <xsl:with-param name="log_link" select="$cell_link"/>
                </xsl:call-template>
            </xsl:when>

            <xsl:when test="$test_log/@result = 'success' and $test_log/@status = 'unexpected'">
                <xsl:call-template name="insert_test_result">
                    <xsl:with-param name="result" select="'pass'"/>
                    <xsl:with-param name="log_link" select="$cell_link"/>
                </xsl:call-template>
            </xsl:when>

            <xsl:otherwise>
                <xsl:call-template name="insert_test_result">
                    <xsl:with-param name="result" select="'pass'"/>
                    <xsl:with-param name="log_link" select="$cell_link"/>
                </xsl:call-template>
            </xsl:otherwise>
        </xsl:choose>  
        </td>
    </xsl:template>

    <!-- report user status -->
    <xsl:template name="insert_cell_user">
        <xsl:param name="library"/>
        <xsl:param name="toolset"/>
        <xsl:param name="test_log"/>
        <xsl:param name="log_link"/>
        
        <xsl:variable name="class">
        <xsl:choose>
            <xsl:when test="meta:is_unusable( $explicit_markup, $library, $toolset )">
            <xsl:text>library-unusable</xsl:text>
            </xsl:when>
            <xsl:when test="not( $test_log )">
            <xsl:text>library-missing</xsl:text>
            </xsl:when>
            <xsl:when test="$test_log[@result='fail' and @status='unexpected']">
            <xsl:text>library-user-fail-unexpected</xsl:text>
            </xsl:when>
            <xsl:when test="$test_log[ @result='fail' and @status='expected' ]">
            <xsl:text>library-user-fail-expected</xsl:text>
        </xsl:when>
        <xsl:when test="$test_log[ @result='success']">
            <xsl:text>library-user-success</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:message terminate="yes">
            Unknown status
            </xsl:message>
        </xsl:otherwise>
        </xsl:choose>

    </xsl:variable>

        <td class="{$class}" title="{$test_log/@test-name}/{$toolset}">
        <xsl:choose>
            <xsl:when test="not( $test_log )">
            missing
            </xsl:when>
            <xsl:when test="$test_log/@result != 'success' and $test_log/@status = 'expected'">
            <a href="{$log_link}" class="log-link" target="_top">
                fail
            </a>
            </xsl:when>
            <xsl:when test="$test_log/@result != 'success'">
            <a href="{$log_link}" class="log-link" target="_top">
                unexp.
            </a>
            </xsl:when>
            <xsl:otherwise>
            <xsl:text>pass</xsl:text>
            </xsl:otherwise>
        </xsl:choose>  

        <!--<xsl:if test="count( $test_log ) > 1" > 
            <div class="conf-problem">conf.&#160;problem</div>
        </xsl:if>-->
        </td>
    </xsl:template>

    <xsl:template name="insert_test_line">
        <xsl:param name="library"/>    
        <xsl:param name="test_name"/>
        <xsl:param name="test_results"/>
        <xsl:param name="toolsets"/>
        <xsl:param name="line_mod"/>

        <xsl:variable name="test_program">
        <xsl:value-of select="$test_results[1]/@test-program"/>
        </xsl:variable>

        <xsl:variable name="test_header">
        <td class="test-name">
            <a href="http://cvs.sourceforge.net/viewcvs.py/*checkout*/boost/boost/{$test_program}" class="test-link" target="_top">
                <xsl:value-of select="$test_name"/>
            </a>
        </td>
        </xsl:variable>

        <tr class="library-row{$line_mod}">
        <xsl:copy-of select="$test_header"/>
        <xsl:call-template name="test_type_col"/>
          
        <xsl:for-each select="$run_toolsets/platforms/platform/runs/run/toolset">
            <xsl:variable name="toolset" select="@name" />
            <xsl:variable name="runner" select="../@runner" />

            <!-- Write log file -->
            <xsl:variable name="test_result_for_toolset" select="$test_results[ @toolset = $toolset and ../@runner=$runner ]"/>


            <xsl:for-each select="$test_result_for_toolset">
                <xsl:variable name="log_file" select="meta:log_file_path(.)"/>

                <xsl:if test="$release != 'yes' and count( $test_result_for_toolset ) > 0 and $log_file != '' ">
                    <xsl:message>Writing log file document  <xsl:value-of select="$log_file"/></xsl:message>
                        <exsl:document href="{$log_file}"
                            method="html" 
                            doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" 
                            encoding="utf-8"
                            indent="yes">
                            
                            <html>
                                <head>
                                    <link rel="stylesheet" type="text/css" href="../master.css" title="master" />
                                    <!--<title>Boost regression unresolved issues: <xsl:value-of select="$source"/></title>-->
                                </head>
                                <frameset cols="190px,*" frameborder="0" framespacing="0" border="0">
                                    <frame name="tocframe" src="../toc.html" scrolling="auto"/>
                                    <frame name="docframe" src="../../{$log_file}" scrolling="auto"/>
                                </frameset>
                            </html>
                        </exsl:document>
                    </xsl:if>
                
            </xsl:for-each>


            <!-- Insert cell -->
            <xsl:choose>
            <xsl:when test="$mode='user'">
                <xsl:call-template name="insert_cell_user">
                <xsl:with-param name="library" select="$library"/>
                <xsl:with-param name="toolset" select="$toolset"/>
                <xsl:with-param name="test_log" select="$test_result_for_toolset"/>
                <xsl:with-param name="log_link" select="$log_file"/>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test="$mode='developer'">
                <xsl:call-template name="insert_cell_developer">
                <xsl:with-param name="library" select="$library"/>
                <xsl:with-param name="toolset" select="$toolset"/>
                <xsl:with-param name="test_log" select="$test_result_for_toolset"/>
                </xsl:call-template>
            </xsl:when>
            </xsl:choose>
            
        </xsl:for-each>
        <xsl:copy-of select="$test_header"/>
        </tr>
    </xsl:template>

    <xsl:template name="insert_test_section">
        <xsl:param name="library"/>      
        <xsl:param name="section_test_nanes"/>
        <xsl:param name="lib_tests"/>
        <xsl:param name="toolsets"/>

        <xsl:for-each select="$section_test_names">
            <xsl:variable name="test_name" select="@test-name"/>
            <xsl:variable name="line_mod">
                <xsl:choose>
                    <xsl:when test="1 = last()">
                        <xsl:text>-single</xsl:text>
                    </xsl:when>
                    <xsl:when test="generate-id( . ) = generate-id( $section_test_names[1] )">
                        <xsl:text>-first</xsl:text>
                    </xsl:when>
                    <xsl:when test="generate-id( . ) = generate-id( $section_test_names[last()] )">
                        <xsl:text>-last</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text></xsl:text>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:variable>
              
            <xsl:call-template name="insert_test_line">
                <xsl:with-param name="library" select="$library"/>
                <xsl:with-param name="test_results" select="$lib_tests[ @test-name = $test_name ]"/>
                <xsl:with-param name="toolsets" select="$toolsets"/>
                <xsl:with-param name="test_name" select="$test_name"/>
                <xsl:with-param name="line_mod" select="$line_mod"/>
            </xsl:call-template>
        </xsl:for-each>
          
    </xsl:template>

    <func:function name="meta:order_tests_by_name">
        <xsl:param name="tests"/>

        <xsl:variable name="a">                  
            <xsl:for-each select="$tests">
                <xsl:sort select="@test-name" order="ascending"/>
                <xsl:copy-of select="."/>
            </xsl:for-each>
        </xsl:variable>
        <func:result select="exsl:node-set( $a )/*"/>
    </func:function>

</xsl:stylesheet>
