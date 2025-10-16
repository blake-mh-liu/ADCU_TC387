<?xml version="1.0" encoding="utf-8"?>
<!--
  These template overwrite the default copy behaviour: By default, all elements
  that are not matched by a template are skipped. The templates here will write
  all those elements to the output.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xslt="http://xml.apache.org/xslt">

  <!-- Subfunction to copy all -->
  <xsl:template name="COPY">
    <xsl:copy>
      <xsl:apply-templates select="@*|comment()|processing-instruction()|text()|*" mode="#current"/>
    </xsl:copy>
  </xsl:template>
  
  <!-- default copy subtemplate to copy comments -->
  <xsl:template match="@*|comment()|processing-instruction()|text()" mode="#all">
    <xsl:copy/>
  </xsl:template>
  
  <!-- default copy -->
  <xsl:template match="*" mode="#all">
    <xsl:call-template name="COPY"/>
  </xsl:template>

</xsl:stylesheet>