<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
   version="1.0"
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
   xmlns="http://www.tresos.de/_projects/DataModel2/16/root.xsd" 
   xmlns:a="http://www.tresos.de/_projects/DataModel2/16/attribute.xsd" 
   xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd" 
   xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd"
   xmlns:ad="http://www.tresos.de/_projects/DataModel2/08/admindata.xsd" 
   xmlns:cd="http://www.tresos.de/_projects/DataModel2/08/customdata.xsd" 
   xmlns:f="http://www.tresos.de/_projects/DataModel2/14/formulaexpr.xsd" 
   xmlns:icc="http://www.tresos.de/_projects/DataModel2/08/implconfigclass.xsd" 
   xmlns:mt="http://www.tresos.de/_projects/DataModel2/11/multitest.xsd"  
   xmlns:variant="http://www.tresos.de/_projects/DataModel2/11/variant.xsd"
   >

   <!--
      By default, we copy all elements to the output
   -->

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


   <!--
      The actual rules for removing elements
   -->

   <!-- configuration ID of splitImport wizard, used as importer name in importer info -->
   <xsl:param name="splitImportConfig"/>

   <!-- remove importer info for splitImEx importer config -->
   <xsl:template match="a:a[@name='IMPORTER_INFO'][@value=$splitImportConfig]"/>

   <!-- remove split tag -->
   <xsl:template match="a:a[@name='CUSTOMDATA'][@type='CUSTOMDATA'][*[local-name() = 'v'][@id='splittag']]"/>

</xsl:stylesheet>