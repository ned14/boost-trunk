<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:rev="http://www.cs.rpi.edu/~gregod/boost/tools/doc/revision"
                version="1.0">

  <!-- Import the HTML chunking stylesheet -->
  <xsl:import 
    href="http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl"/>

  <xsl:param name="html.stylesheet" select="'reference.css'"/>
  <xsl:param name="navig.graphics" select="1"/>
  <xsl:param name="navig.graphics.extension" select="'.png'"/>
  <xsl:param name="chapter.autolabel" select="0"/>
  <xsl:param name="use.id.as.filename" select="1"/>
  <xsl:param name="refentry.generate.name" select="0"/>
  <xsl:param name="refentry.generate.title" select="1"/>
  <xsl:param name="html.extra.head.links" select="1"/>
  <xsl:param name="make.year.ranges" select="1"/>
  <xsl:param name="generate.manifest" select="1"/>
  <xsl:param name="generate.section.toc.level" select="3"/>

  <xsl:template name="header.navigation">
    <table border="1" cellpadding="2" bgcolor="#007F7F">
      <tr>
        <td bgcolor="#FFFFFF">
          <img src="../../c++boost.gif"
            alt="c++boost.gif (8819 bytes)" width="277" height="86"/>
        </td>
        <td>
          <a href="../../index.htm">
            <font color="#FFFFFF" size="4" face="Arial">Home</font>
          </a>
        </td>
        <td>
          <a href="libraries.html">
            <font color="#FFFFFF" size="4" face="Arial">Libraries</font>
          </a>
        </td>
        <td>
          <a href="../../people/people.htm">
            <font color="#FFFFFF" size="4" face="Arial">People</font>
          </a>
        </td>
        <td>
          <a href="../../more/faq.htm">
            <font color="#FFFFFF" size="4" face="Arial">FAQ</font>
          </a>
        </td>
        <td>
          <a href="../../more/index.htm">
            <font color="#FFFFFF" size="4" face="Arial">More</font>
          </a>
        </td>
      </tr>
    </table>
  </xsl:template>

  <xsl:template name="format.cvs.revision">
    <xsl:param name="text"/>

    <!-- Remove the "$Date: " -->
    <xsl:variable name="text.noprefix" 
      select="substring-after($text, '$Date: ')"/>

    <!-- Grab the year -->
    <xsl:variable name="year" select="substring-before($text.noprefix, '/')"/>
    <xsl:variable name="text.noyear" 
      select="substring-after($text.noprefix, '/')"/>

    <!-- Grab the month -->
    <xsl:variable name="month" select="substring-before($text.noyear, '/')"/>
    <xsl:variable name="text.nomonth" 
      select="substring-after($text.noyear, '/')"/>

    <!-- Grab the year -->
    <xsl:variable name="day" select="substring-before($text.nomonth, ' ')"/>
    <xsl:variable name="text.noday" 
      select="substring-after($text.nomonth, ' ')"/>

    <!-- Get the time -->
    <xsl:variable name="time" select="substring-before($text.noday, ' ')"/>

    <xsl:variable name="month.name">
      <xsl:choose>
        <xsl:when test="$month=1">January</xsl:when>
        <xsl:when test="$month=2">February</xsl:when>
        <xsl:when test="$month=3">March</xsl:when>
        <xsl:when test="$month=4">April</xsl:when>
        <xsl:when test="$month=5">May</xsl:when>
        <xsl:when test="$month=6">June</xsl:when>
        <xsl:when test="$month=7">July</xsl:when>
        <xsl:when test="$month=8">August</xsl:when>
        <xsl:when test="$month=9">September</xsl:when>
        <xsl:when test="$month=10">October</xsl:when>
        <xsl:when test="$month=11">November</xsl:when>
        <xsl:when test="$month=12">December</xsl:when>
      </xsl:choose>
    </xsl:variable>

    <xsl:value-of select="concat($month.name, ' ', $day, ', ', $year, ' at ',
                                 $time, ' GMT')"/>
  </xsl:template>

  <xsl:template match="copyright" mode="boost.footer">
    <xsl:if test="position() &gt; 1">
      <br/>
    </xsl:if>
    <xsl:call-template name="gentext">
      <xsl:with-param name="key" select="'Copyright'"/>
    </xsl:call-template>
    <xsl:call-template name="gentext.space"/>
    <xsl:call-template name="dingbat">
      <xsl:with-param name="dingbat">copyright</xsl:with-param>
    </xsl:call-template>
    <xsl:call-template name="gentext.space"/>
    <xsl:call-template name="copyright.years">
      <xsl:with-param name="years" select="year"/>
      <xsl:with-param name="print.ranges" select="$make.year.ranges"/>
      <xsl:with-param name="single.year.ranges"
        select="$make.single.year.ranges"/>
    </xsl:call-template>
    <xsl:call-template name="gentext.space"/>
    <xsl:apply-templates select="holder" mode="titlepage.mode"/>
  </xsl:template>

  <xsl:template name="user.footer.content">
    <table width="100%">
      <tr>
        <td align="left">
          <small>
            <xsl:variable name="revision-nodes" 
              select="ancestor-or-self::*
                        [not (attribute::rev:last-revision='')]"/>
            <xsl:if test="count($revision-nodes)">
              <xsl:variable name="revision-node"
                select="$revision-nodes[last()]"/>
              <xsl:text>Last revised: </xsl:text>
              <xsl:call-template name="format.cvs.revision">
                <xsl:with-param name="text"
                  select="string($revision-node/attribute::rev:last-revision)"/>
              </xsl:call-template>
            </xsl:if>
          </small>
        </td>
        <td align="right">
          <small>
            <xsl:apply-templates select="ancestor::*/*/copyright" 
              mode="boost.footer"/>
          </small>
        </td>
      </tr>
    </table>
  </xsl:template>

  <xsl:template match="variablelist">
    <xsl:choose>
      <xsl:when test="@spacing='boost'">
        <p><xsl:apply-templates mode="boost.variablelist"/></p>
      </xsl:when>
      <xsl:otherwise>
        <xsl:apply-imports />
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="varlistentry" mode="boost.variablelist">
    <xsl:if test="position() &gt; 1">
      <br/>
    </xsl:if>
    <b><xsl:apply-templates select="term"/></b>:

    <xsl:choose>
      <xsl:when test="local-name(listitem/*[1])='simpara' or
                      local-name(listitem/*[1])='para'">
        <xsl:apply-templates 
          select="listitem/*[1]/*|listitem/*[1]/text()"/>
        <xsl:apply-templates select="(listitem/*|listitem/text())[position() &gt; 1]"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:apply-templates select="listitem/*|listitem/text()"/>        
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
  
  <!-- We don't want refentry's to show up in the TOC because they
       will merely be redundant with the synopsis. -->
  <xsl:template match="refentry" mode="toc"/>
 </xsl:stylesheet>
