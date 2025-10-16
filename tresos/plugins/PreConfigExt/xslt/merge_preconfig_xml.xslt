<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:fnc="http://fnc"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:xslt="http://xml.apache.org/xslt">

   <xsl:import href="default_copy_all.xslt"/>

   <xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>
   <xsl:strip-space elements="*"/>

   <xsl:param name="inputFiles" as="xs:string"/>

   <xsl:variable name="gCopyAllGroups">
      <preconfig xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="preconfig.xsd" schema-version="1">
         <xsl:copy-of select="collection($inputFiles)//group"/>
      </preconfig>
   </xsl:variable>

   <xsl:variable name="gMergeGroups">
      <xsl:apply-templates select="$gCopyAllGroups" mode="mergeGroups"/>
   </xsl:variable>

   <xsl:template match="/">
      <xsl:copy-of select="$gMergeGroups"/>
   </xsl:template>


   <!--
      first group of a name remains, content of groups of same name is merged into this one
   -->
   <xsl:template mode="mergeGroups" match="group[not(name = preceding-sibling::group/name)]/configuration-checks">
      <xsl:variable name="vGroupName" select="../name" as="element()"/>
      <xsl:variable name="vEnabledCondition" select="../enabled-condition" as="element()"/>
 
      <xsl:if test="../following-sibling::group[name = $vGroupName and not(enabled-condition = $vEnabledCondition)]">
         <xsl:message terminate="yes">[ERROR] enabled condition mismatch for groups of name '<xsl:value-of select="$vGroupName"/>'</xsl:message>
      </xsl:if>

      <xsl:copy>
         <xsl:apply-templates mode="#current"/>
         <xsl:copy-of select="../following-sibling::group[name = $vGroupName]/configuration-checks/configuration-check"/>
      </xsl:copy>
   </xsl:template>

   <!-- following groups of a name are deleted -->
   <xsl:template mode="mergeGroups" match="group[name = preceding-sibling::group/name]"/>

</xsl:stylesheet>
