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
    xmlns:str="http://exslt.org/strings"
    xmlns:set="http://exslt.org/sets"
    xmlns:meta="http://www.meta-comm.com"
    extension-element-prefixes="func"
    exclude-result-prefixes="exsl func str set meta"
    version="1.0">

    <xsl:variable name="output_directory" select="'output'"/>

    <!-- structural -->

    <func:function name="meta:test_structure">
        <xsl:param name="document"/>
        <xsl:param name="release"/>
        <xsl:variable name="required_toolsets" select="$explicit_markup//mark-toolset[ @status='required' ]"/>

        <xsl:variable name="runs" select="$document//test-run"/>
        <xsl:variable name="platforms" select="set:distinct( $document//test-run/@platform )"/>
        
        
        <xsl:variable name="run_toolsets_f">
            <platforms>
                <xsl:for-each select="$platforms">
                    <xsl:variable name="platform" select="."/>
                    <platform name="{$platform}">
                        <runs>
                            <xsl:for-each select="$runs[ @platform = $platform ]">
                                <xsl:sort select="."/>
                                <run 
                                    runner="{@runner}" 
                                    timestamp="{@timestamp}" 
                                    platform="{@platform}"
                                    run-type="{@run-type}"
                                    source="{@source}">
                            
                                    <comment><xsl:value-of select="comment"/></comment>
                                    <xsl:variable name="not_ordered_toolsets" select="set:distinct( .//test-log[ meta:is_test_log_a_test_case(.) and meta:show_toolset( @toolset, $release ) ]/@toolset ) "/>
                                    
                                    <xsl:variable name="not_ordered_toolsets_with_info_f">
                                        <xsl:for-each select="$not_ordered_toolsets">
                                            <xsl:sort select="." order="ascending"/>
                                            <xsl:variable name="toolset" select="."/>
                                            <xsl:variable name="required">
                                                <xsl:choose>
                                                    <xsl:when test="count( $required_toolsets[ @name = $toolset ] ) > 0">yes</xsl:when>
                                                        <xsl:otherwise>no</xsl:otherwise>
                                                    </xsl:choose>
                                                </xsl:variable>
                                                <xsl:variable name="required_sort_hint">
                                                    <xsl:choose>
                                                        <xsl:when test="$required = 'yes'">sort hint A</xsl:when>
                                                        <xsl:otherwise>sort hint B</xsl:otherwise>
                                                    </xsl:choose>
                                                </xsl:variable>
                                                <toolset name="{$toolset}" required="{$required}" required_sort_hint="{$required_sort_hint}"/>
                                            </xsl:for-each>
                                        </xsl:variable>
                                        
                                        <xsl:variable name="not_ordered_toolsets_with_info" select="exsl:node-set( $not_ordered_toolsets_with_info_f )"/>
                                        
                                        <xsl:for-each select="$not_ordered_toolsets_with_info/toolset">
                                            <xsl:sort select="concat( @required_sort_hint, '-', @name )" order="ascending"/>
                                            <xsl:copy-of select="."/>
                                        </xsl:for-each>
                                    </run>
                                </xsl:for-each>
                            </runs>
                        </platform>
                    </xsl:for-each>
                </platforms>
            </xsl:variable>
        <func:result select="exsl:node-set( $run_toolsets_f )"/>
    </func:function>


    <func:function name="meta:test_case_status">
        <xsl:param name="test_log"/>
        <xsl:param name="$explicit_markup"/>

        <xsl:variable name="status">
            <xsl:choose> 
                 <xsl:when test="meta:is_unusable( $explicit_markup, $test_log/@library, $test_log/@toolset )">
                     <xsl:text>unusable</xsl:text>
                 </xsl:when>
                 <xsl:when test="$test_log/@result='fail' and  $test_log/@status='unexpected' and $test_log/@is-new='no'">
                     <xsl:text>fail-unexpected</xsl:text>
                 </xsl:when>
                 <xsl:when test="$test_log/@result='fail' and  $test_log/@status='unexpected' and $test_log/@is-new='yes'">
                     <xsl:text>fail-unexpected-new</xsl:text>
                 </xsl:when>
                 <xsl:when test="$test_log/@result='success' and  $test_log/@status='unexpected'">
                     <xsl:text>success-unexpected</xsl:text>
                 </xsl:when>
                 <xsl:when test="$test_log/@status='expected'">
                     <xsl:text>expected</xsl:text>
                 </xsl:when>
                 <xsl:otherwise>
                     <xsl:text>other</xsl:text>
                 </xsl:otherwise>
             </xsl:choose>
         </xsl:variable>
         <func:result select="$status"/>
     </func:function>

    <func:function name="meta:is_toolset_required">
        <xsl:param name="toolset"/>
        <func:result select="count( $explicit_markup/explicit-failures-markup/mark-toolset[ @name = $toolset and @status='required' ] ) > 0"/>
    </func:function>

    <func:function name="meta:is_library_beta">
        <xsl:param name="library"/>
        <func:result select="count( $explicit_markup/explicit-failures-markup/library[ @name = $library and @status='beta' ] ) > 0"/>
    </func:function>

    <func:function name="meta:is_test_log_a_test_case">
        <xsl:param name="test_log"/>      
        <func:result select="$test_log/@test-type='compile' or $test_log/@test-type='compile_fail' or $test_log/@test-type='run' or $test_log/@test-type='run_pyd'"/>
    </func:function>

    <func:function name="meta:is_unusable">
        <xsl:param name="explicit_markup"/>
        <xsl:param name="library"/>
        <xsl:param name="toolset"/>
          
        <func:result select="count( $explicit_markup//library[ @name = $library ]/mark-unusable/toolset[ meta:re_match( @name, $toolset ) ] ) > 0"/>
    </func:function>

    <func:function name="meta:re_match">
        <xsl:param name="pattern"/>
        <xsl:param name="text"/>
        
        <xsl:choose>
            <xsl:when test="not( contains( $pattern, '*' ) )">
                <func:result select="$text = $pattern"/>
            </xsl:when>
            <xsl:when test="$pattern = '*'">
                <func:result select="1 = 1"/>
            </xsl:when>
            <xsl:when test="substring( $pattern, 1, 1 ) = '*' and substring( $pattern, string-length($pattern), 1 ) = '*' ">
                <func:result select="contains( $text, substring( $pattern, 2, string-length($pattern) - 2 ) ) "/>
            </xsl:when>
            <xsl:when test="substring( $pattern, 1, 1 ) = '*'">
                <xsl:variable name="pattern_tail" select="substring( $pattern, 2, string-length($pattern) - 1 )"/>
                <func:result select="substring( $text, string-length($text) - string-length($pattern_tail) + 1, string-length($pattern_tail) ) = $pattern_tail"/>
            </xsl:when>
            <xsl:when test="substring( $pattern, string-length($pattern), 1 ) = '*' ">
                <xsl:variable name="pattern_head" select="substring( $pattern, 1, string-length($pattern) - 2 )"/>
                <func:result select="substring( $text, 1, string-length($pattern_head) ) = $pattern_head "/>
            </xsl:when>
        </xsl:choose>
    </func:function>

    <!-- path -->

    <func:function name="meta:encode_path">
        <xsl:param name="path"/>
        <func:result select="translate( translate( $path, '/', '-' ), './', '-' )"/>
    </func:function>

    <func:function name="meta:output_file_path">
        <xsl:param name="path"/>
        <func:result select="concat( $output_directory, '/', meta:encode_path( $path ), '.html' )"/>
    </func:function>

    <func:function name="meta:log_file_path">
        <xsl:param name="test_log"/>
        <func:result>
            <xsl:choose>
                <xsl:when test="meta:show_output( $explicit_markup, $test_log )">
                    <xsl:value-of select="meta:output_file_path( concat( $test_log/../@runner, '-', $test_log/@target-directory ) )"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text></xsl:text>
                </xsl:otherwise>
            </xsl:choose>
        </func:result>
    </func:function>

    <!-- presentation -->

    <func:function name="meta:show_library">
        <xsl:param name="library"/>
        <xsl:param name="release" select="'no'"/>
        <func:result select="$release != 'yes' or not( meta:is_library_beta( $library ) )"/>
    </func:function>

    <func:function name="meta:show_output">
        <xsl:param name="explicit_markup"/>
        <xsl:param name="test_log"/>
        <func:result select="( $test_log/@result != 'success' or $test_log/@show-run-output = 'true' or
                                $test_log/@result = 'success'  and $test_log/@status = 'unexpected' )
                            and not( meta:is_unusable( $explicit_markup, $test_log/@library, $test_log/@toolset ) )
                            "/>
    </func:function>

    <func:function name="meta:show_toolset">
        <xsl:param name="toolset"/>
        <xsl:param name="release" select="'no'"/>
        <func:result select="$release != 'yes' or meta:is_toolset_required( $toolset )"/>
    </func:function>

    <func:function name="meta:result_cell_class">
        <xsl:param name="library"/>
        <xsl:param name="toolset"/>
        <xsl:param name="test_logs"/>

        <func:result>
            <xsl:choose>
                <xsl:when test="meta:is_unusable( $explicit_markup, $library, $toolset )">
                    <xsl:text>unusable</xsl:text>
                </xsl:when>
                
                <xsl:when test="count( $test_logs ) &lt; 1">
                    <xsl:text>missing</xsl:text>
                </xsl:when>
                
                <xsl:when test="count( $test_logs[@result='fail' and  @status='unexpected' and @is-new='no'] )">
                    <xsl:text>fail-unexpected</xsl:text>
                </xsl:when>
                
                <xsl:when test="count( $test_logs[@result='fail' and  @status='unexpected' and @is-new='yes'] )">
                    <xsl:text>fail-unexpected-new</xsl:text>
                </xsl:when>


                <xsl:when test="count( $test_logs[@result='fail' and @expected-reason != '' ] )">
                    <xsl:text>fail-expected-unresearched</xsl:text>
                </xsl:when>

                <xsl:when test="count( $test_logs[@result='fail'] )">
                    <xsl:text>fail-expected</xsl:text>
                </xsl:when>
                
                
                <xsl:when test="count( $test_logs[@result='success' and  @status='unexpected'] )">
                    <xsl:text>success-unexpected</xsl:text>
                </xsl:when>
                
                <xsl:when test="count( $test_logs[@status='expected'] )">
                    <xsl:text>success-expected</xsl:text>
                </xsl:when>
                
                <xsl:otherwise>
                    <xsl:text>unknown</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
        </func:result>
    </func:function>


    <xsl:template name="insert_view_link">
        <xsl:param name="page"/>
        <xsl:param name="release"/>
        <xsl:param name="class"/>

        <xsl:choose>
        <xsl:when test="$release='yes'">
            <a href="{$page}.html" class="{$class}" target="_top">
                <xsl:text>Full View</xsl:text>
            </a>
        </xsl:when>
        <xsl:otherwise>
            <a href="{$page}_release.html" class="{$class}" target="_top">
                <xsl:text>Release View</xsl:text>
            </a>
        </xsl:otherwise>
        </xsl:choose>

    </xsl:template>


    <xsl:template name="insert_page_links">
        <xsl:param name="page"/>
        <xsl:param name="release"/>

        <div class="links">
            <xsl:copy-of select="document( 'html/make_tinyurl.html' )"/>
            <xsl:text>&#160;|&#160;</xsl:text>
            <xsl:call-template name="insert_view_link">
                <xsl:with-param name="page" select="$page"/>
                <xsl:with-param name="class" select="''"/>
                <xsl:with-param name="release" select="$release"/>
            </xsl:call-template>
        </div>

    </xsl:template>


    <xsl:template name="insert_runners_rows">
        <xsl:param name="mode"/>
        <xsl:param name="top_or_bottom"/>

        <xsl:variable name="colspan">
            <xsl:choose>
                <xsl:when test="$mode = 'summary'">1</xsl:when>
                <xsl:when test="$mode = 'details'">2</xsl:when>
            </xsl:choose>
        </xsl:variable>


        <xsl:if test="$top_or_bottom = 'top'">
            <tr>
                <td colspan="{$colspan}">&#160;</td>
                <xsl:for-each select="$run_toolsets/platforms/platform">
                    <xsl:if test="count(./runs/run/toolset) &gt; 0">
                        <td colspan="{count(./runs/run/toolset)}" class="runner">
                            <xsl:value-of select="@name"/>
                        </td>
                    </xsl:if>
                </xsl:for-each>
                <td colspan="{$colspan}">&#160;</td>
            </tr>
        </xsl:if>

        <tr>
            <td colspan="{$colspan}">&#160;</td>
            <xsl:for-each select="$run_toolsets//runs/run[ count(toolset) > 0 ]">
                <td colspan="{count(toolset)}" class="runner">
                    <a href="../{@runner}.html">
                        <xsl:value-of select="@runner"/>
                    </a>
                </td>
            </xsl:for-each>
            <td colspan="{$colspan}">&#160;</td>
        </tr>

        <tr>
            <td colspan="{$colspan}">&#160;</td>
            <xsl:for-each select="$run_toolsets//runs/run[ count(toolset) > 0 ]">
                <td colspan="{count(toolset)}" class="timestamp"><xsl:value-of select="@timestamp"/></td>
            </xsl:for-each>
            <td colspan="{$colspan}">&#160;</td>
        </tr>

        <xsl:if test="$top_or_bottom = 'bottom'">
            <tr>
                <td colspan="{$colspan}">&#160;</td>
                <xsl:for-each select="$run_toolsets/platforms/platform">
                    <xsl:if test="count(./runs/run/toolset) &gt; 0">
                        <td colspan="{count(./runs/run/toolset)}" class="runner">
                            <xsl:value-of select="@name"/>
                        </td>
                    </xsl:if>
                </xsl:for-each>
                <td colspan="{$colspan}">&#160;</td>
            </tr>
        </xsl:if>

    </xsl:template>

    <xsl:template name="insert_toolsets_row">
        <xsl:param name="mode"/>
        <xsl:param name="library"/>
        <xsl:param name="library_marks"/>

        <tr valign="middle">
            <xsl:variable name="colspan">
                <xsl:choose>
                    <xsl:when test="$mode = 'summary'">1</xsl:when>
                    <xsl:when test="$mode = 'details'">2</xsl:when>
                </xsl:choose>
            </xsl:variable>

            <xsl:variable name="title">
                <xsl:choose>
                    <xsl:when test="$mode = 'summary'">&#160;library&#160;/&#160;toolset&#160;</xsl:when>
                    <xsl:when test="$mode = 'details'">&#160;test&#160;/&#160;toolset&#160;</xsl:when>
                </xsl:choose>
            </xsl:variable>
              
            <td class="head" colspan="{$colspan}" width="1%"><xsl:value-of select="$title"/></td>
              

            <xsl:for-each select="$run_toolsets//runs/run/toolset">
                <xsl:variable name="toolset" select="@name"/>
                  
                <xsl:variable name="class">
                    <xsl:choose>
                        <xsl:when test="@required='yes'">
                            <xsl:text>required-toolset-name</xsl:text>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>toolset-name</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:variable>

                <td class="{$class}">

                    <!-- break toolset names into words -->
                    <xsl:for-each select="str:tokenize($toolset, '-')">
                        <xsl:value-of select="." />
                        <xsl:if test="position()!=last()">
                            <xsl:text>- </xsl:text>
                        </xsl:if>
                    </xsl:for-each>
                    
                    <xsl:if test="$mode = 'details'">
                        <!-- prepare toolset notes -->
                        <xsl:variable name="toolset_notes_fragment">
                            <xsl:for-each select="$library_marks/note">
                                <xsl:if test="count( ../toolset[meta:re_match( @name, $toolset )] ) > 0">
                                    <note index="{position()}"/>
                                </xsl:if>
                            </xsl:for-each>
                        </xsl:variable>
                        
                        <xsl:variable name="toolset_notes" select="exsl:node-set( $toolset_notes_fragment )/*"/>
                        <xsl:if test="count( $toolset_notes ) > 0">
                            <span class="super">
                            <xsl:for-each select="$toolset_notes">
                                <xsl:variable name="note_index" select="@index"/>
                                <xsl:if test="generate-id( . ) != generate-id( $toolset_notes[1] )">, </xsl:if>
                                <a href="#{$library}-note-{$note_index}" title="Note {$note_index}">
                                    <xsl:value-of select="$note_index"/>
                                </a>
                            </xsl:for-each>
                            </span>
                        </xsl:if>
                    </xsl:if>
                </td>
            </xsl:for-each>
              
        <td class="head" width="1%"><xsl:value-of select="$title"/></td>
    </tr>
    </xsl:template>

    <xsl:template name="show_notes">
        <xsl:param name="explicit_markup"/>
        <xsl:param name="notes"/>
            <div class="notes">
            <xsl:for-each select="$notes">
                <div>
                    <xsl:variable name="ref_id" select="@refid"/>
                    <xsl:call-template name="show_note">
                        <xsl:with-param name="note" select="."/>
                        <xsl:with-param name="references" select="$ref_id"/>
                    </xsl:call-template>
                </div>
            </xsl:for-each>
            </div>
    </xsl:template>

    <xsl:template name="show_note">
        <xsl:param name="note"/>
        <xsl:param name="references"/>

        <div class="note">
            <xsl:variable name="author">
                <xsl:choose>
                    <xsl:when test="$note/@author">
                        <xsl:value-of select="$note/@author"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:variable>

            <xsl:variable name="date">
                <xsl:choose>
                    <xsl:when test="$note/@date">
                        <xsl:value-of select="$note/@date"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:variable>

        <span class="note-header">
            <xsl:choose>
                <xsl:when test="$author != '' and $date != ''">
                    [&#160;<xsl:value-of select="$author"/>&#160;<xsl:value-of select="$date"/>&#160;]
                </xsl:when>
                <xsl:when test="$author != ''">
                    [&#160;<xsl:value-of select="$author"/>&#160;]                        
                </xsl:when>
                <xsl:when test="$date != ''">
                    [&#160;<xsl:value-of select="$date"/>&#160;]                        
                </xsl:when>
            </xsl:choose>
        </span>

        <xsl:if test="$references">
            <!-- lookup references (refid="17,18") -->
            <xsl:for-each select="str:tokenize($references, ',')">
                <xsl:variable name="ref_id" select="."/>
                <xsl:variable name="referenced_note" select="$explicit_markup//note[ $ref_id = @id ]"/>

                <xsl:choose>
                    <xsl:when test="$referenced_note">
                        <xsl:copy-of select="$referenced_note/node()"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="$ref_id"/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:for-each>
        </xsl:if>

        <xsl:copy-of select="$note/node()"/>      

        </div>
    </xsl:template>

</xsl:stylesheet>
