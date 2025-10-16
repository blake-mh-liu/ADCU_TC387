<?xml version="1.0" encoding="utf-8"?>
<!--
   General note: We use an Excel export as input file. Excel's export to XML feature does not
   write XML elements for empty cells. Therefore, we may need to check whether an elements exists
   before we use it in locations where an empty element is not allowed.
-->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:fnc="http://fnc"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:xslt="http://xml.apache.org/xslt"
    xmlns:a="http://www.tresos.de/_projects/DataModel2/08/attribute.xsd"
    xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd"
    xmlns:cd="http://www.tresos.de/_projects/DataModel2/08/customdata.xsd"
    xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd">

   <xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>

   <xsl:strip-space elements="*"/>


   <xsl:variable name="vGeneralDescriptionText"> &lt;p&gt;&lt;b&gt;Notes:&lt;/b&gt;&lt;/p&gt;&lt;p&gt;The project
    configuration is automatically checked for conformance to the requirements related to the
    corresponding configuration parameter. Non-conformance is indicated as follows:&lt;/p&gt;
    &lt;ol&gt;
        &lt;li&gt;category &lt;i&gt;required&lt;/i&gt;
            &lt;ul&gt;
                &lt;li&gt;error message if the check is enabled&lt;/li&gt;
                &lt;li&gt;warning message if the check is disabled but no rationale for this is provided in the comment field&lt;/li&gt;
                &lt;li&gt;no indication if the check is disabled and a rationale for this is provided in the comment field&lt;/li&gt;
            &lt;/ul&gt;
        &lt;li&gt;category &lt;i&gt;recommended&lt;/i&gt;
            &lt;ul&gt;
                &lt;li&gt;error message if the check is enabled&lt;/li&gt;
                &lt;li&gt;no indication if the check is disabled&lt;/li&gt;
            &lt;/ul&gt;
    &lt;/ol&gt;
    &lt;p&gt;You can use the autoconfiguration wizard in order to
    bulk-change non-conformant configuration parameters (see M4_MODULE()
    documentation).&lt;/p&gt;&lt;p&gt;&lt;b&gt;Warning:&lt;/b&gt; Before running the autoconfiguration
    wizard, please analyse whether the recommended parameter settings are suitable for your
    project and make sure to enable only such suitable parameters in
    M4_MODULE().&lt;/p&gt;</xsl:variable>


   <!--
      Write the configuration schema XDM file
   -->
   <xsl:template match="/">

      <!-- first perform some global input validation -->

      <xsl:variable name="vSchemaVersion" select="/preconfig/@schema-version" as="attribute()"/>
      <xsl:variable name="vExpectedSchemaVersion">1</xsl:variable>
      <xsl:if test="not($vSchemaVersion = $vExpectedSchemaVersion)">
         <xsl:message terminate="yes">[ERROR] input file schema version is <xsl:value-of select="$vSchemaVersion"/>, but expected schema version is <xsl:value-of select="$vExpectedSchemaVersion"/></xsl:message>
      </xsl:if>

      <xsl:variable name="vDuplicateGroupNames" select="//group/name[. = ../following-sibling::group/name]"/>
      <xsl:if test="$vDuplicateGroupNames">
         <xsl:message terminate="yes">[ERROR] duplicate group name(s): <xsl:value-of select="string-join($vDuplicateGroupNames, ',')"/></xsl:message>
      </xsl:if>

      <xsl:variable name="vDuplicateConfigCheckIds" select="//configuration-check/id[. = ../following-sibling::configuration-check/id]"/>
      <xsl:if test="$vDuplicateConfigCheckIds">
         <xsl:message terminate="yes">[ERROR] The following configuration check identifiers are not unique inside their group: <xsl:value-of select="string-join($vDuplicateConfigCheckIds, ',')"/></xsl:message>
      </xsl:if>

      <datamodel version="3.0"
         xmlns="http://www.tresos.de/_projects/DataModel2/08/root.xsd"
         xmlns:a="http://www.tresos.de/_projects/DataModel2/08/attribute.xsd"
         xmlns:v="http://www.tresos.de/_projects/DataModel2/06/schema.xsd"
         xmlns:d="http://www.tresos.de/_projects/DataModel2/06/data.xsd">

         <d:ctr type="AUTOSAR" factory="autosar"
            xmlns:ad="http://www.tresos.de/_projects/DataModel2/08/admindata.xsd"
            xmlns:icc="http://www.tresos.de/_projects/DataModel2/08/implconfigclass.xsd"
            xmlns:mt="http://www.tresos.de/_projects/DataModel2/11/multitest.xsd" >
            <d:lst type="TOP-LEVEL-PACKAGES">
               <d:ctr name="M4_MODULE_VARIANT" type="AR-PACKAGE">
                  <d:lst type="ELEMENTS">
                     <d:chc name="M4_MODULE_NAME" type="AR-ELEMENT" value="MODULE-DEF">
                        <v:ctr type="MODULE-DEF">
                           <a:a name="LOWER-MULTIPLICITY" value="1"/>
                           <a:a name="UPPER-MULTIPLICITY" value="1"/>
                           <a:a name="RELEASE" value="asc:4.0"/>

                           <v:ctr name="ConfigValidation" type="IDENTIFIABLE">
                              <a:a name="LABEL" value="Configuration parameter validation"/>

                              <v:var name="ImporterHasPriority" type="BOOLEAN">
                                 <a:a name="LABEL" value="Importer has priority over requirement"/>
                                 <a:da name="DEFAULT" value="true"/>
                                 <a:a name="DESC">
                                    <a:v>&lt;html&gt;&lt;p&gt;If this parameter is set to 'true',
                                       configuration values that have been imported have priority
                                       over OEM requirements. This means that even if a
                                       configuration parameter's value differs from that
                                       one demanded by a requirement, no violation of this requirement
                                       is reported.&lt;/p&gt;&lt;/html&gt;</a:v>
                                 </a:a>
                              </v:var>

                              <xsl:apply-templates/>

                           </v:ctr>

                        </v:ctr>
                     </d:chc>
                  </d:lst>
               </d:ctr>
            </d:lst>
         </d:ctr>

      </datamodel>
   </xsl:template>


   <!--
      Creates the containers for the modules, containing elements for required and recommended
      settings. We use a named template in order to prevent errors caused by code duplication.
   -->
   <xsl:template match="group">
      <xsl:variable name="vGroup" select="." as="element()"/>
      <xsl:variable name="vGroupName" select="$vGroup/name" as="element()"/>
      <xsl:variable name="vGroupEnabledCondition" select="$vGroup/enabled-condition" as="element()"/>

      <v:ctr name="{$vGroupName}" type="IDENTIFIABLE">
         <a:a name="TAB" value="{$vGroupName}"/>
         <a:a name="DESC">
            <a:v>&lt;html&gt; &lt;p&gt;Configuration parameter validation settings of category <xsl:value-of select="$vGroupName"/>.&lt;/p&gt;
               <xsl:value-of select="$vGeneralDescriptionText"/>
               &lt;/html&gt;</a:v>
         </a:a>
         <!-- If the corresponding module does not exist at all, the verification for it shall not be enabled. -->
         <a:da name="ENABLE" type="XPath" expr="{$vGroupEnabledCondition}"/>

         <v:ctr name="Required" type="IDENTIFIABLE">
            <a:a name="DESC">
               <a:v>&lt;html&gt; &lt;p&gt;Required configuration parameter settings.&lt;/p&gt;
                  <xsl:value-of select="$vGeneralDescriptionText"/>
                  &lt;/html&gt;
               </a:v>
            </a:a>
            <a:a name="OPTIONAL" value="true"/>
            <a:da name="ENABLE" value="true"/>

            <xsl:apply-templates select=".//configuration-check[required-or-recommended = 'required']"/>

         </v:ctr>


         <v:ctr name="Recommended" type="IDENTIFIABLE">
            <a:a name="DESC">
               <a:v>&lt;html&gt; &lt;p&gt;Recommended configuration parameter settings.&lt;/p&gt;
                  <xsl:value-of select="$vGeneralDescriptionText"/>
                  &lt;/html&gt;
               </a:v>
            </a:a>
            <a:a name="OPTIONAL" value="true"/>
            <a:da name="ENABLE" value="true"/>

            <xsl:apply-templates select=".//configuration-check[required-or-recommended = 'recommended']"/>

         </v:ctr>


      </v:ctr>
   </xsl:template>


   <xsl:template match="configuration-check">
      <xsl:variable name="vGroupName"             select="ancestor::group/name"    as="element()"/>
      <xsl:variable name="vId"                    select="id"                      as="element()"/>
      <xsl:variable name="vRequirementId"         select="requirement-id"          as="element()"/>
      <xsl:variable name="vRequirementText"       select="requirement-text"        as="element()"/>
      <xsl:variable name="vRequiredOrRecommended" select="required-or-recommended" as="element()"/>
      <xsl:variable name="vCheckParameters"       select="check-parameters"        as="element()"/>
      <xsl:variable name="vCheckValue"            select="check-value"             as="element()"/>
      <xsl:variable name="vSetParameters"         select="set-parameters"          as="element()"/>
      <xsl:variable name="vSetValue"              select="set-to-value"            as="element()"/>
      <xsl:variable name="vOptions"               select="options"                 as="element()"/>

      <v:var name="{$vId}" type="BOOLEAN">
         <a:a name="DESC">
            <xsl:variable name="vDescriptionWithHtmlNewlines" select="replace($vRequirementText, '\n', '&lt;/p&gt;&lt;p&gt;')"/>
            <a:v>&lt;html&gt;
               &lt;p&gt;The following requirement needs to be fulfilled (<xsl:value-of select="$vId"/>):&lt;/p&gt;
               &lt;p&gt;&lt;strong&gt;Requirement ID <xsl:value-of select="$vRequirementId"/>&lt;/strong&gt;: <xsl:value-of select="$vDescriptionWithHtmlNewlines"/>&lt;/p&gt;
               <xsl:value-of select="$vGeneralDescriptionText"/>
               &lt;p&gt;Tags: <xsl:value-of select="$vOptions"/>&lt;/p&gt;
               &lt;/html&gt;
            </a:v>
         </a:a>

         <!-- all values shall be checked by default -->
         <a:da name="DEFAULT" value="true"/>

         <!--
            FIXME: This needs a refactoring. As we now have a proper
            input XML format and only a single file as database, this
            allows us to get rid of that ugly, user-visible hack that
            provided the requirement check data to the XPath function
            checks by misusing the tooltip. The input XML file can
            simply be copied into the Java plug-in; a look-up by the
            unique validation check identifier in a hash table can be
            used. 
         -->
         <!-- we misuse the TOOLTIP attribute as carrier for the validation criterion information from XDM to Java code -->
         <a:da name="TOOLTIP" value="{string-join(($vRequiredOrRecommended, $vId, $vCheckParameters, $vCheckValue, $vSetParameters, $vSetValue, $vOptions), '#;#')}"/>

         <!--
            Add automatic validation. For recommended values that shall be checked, we
            raise an error if the verification criterion is not fulfilled. For required values
            however, we raise an error if the criterion shall be checked and is not fulfilled and raise a
            warning if it shall not be checked and is not fulfilled.
         -->
         <a:da name="INVALID" type="XPath">
            <!-- An error is shown if this XPath evaluates to true -->
            <a:tst expr="PreConfig:isConfigValidationError(.)"
                   true="Requirement {$vRequirementId} is not fulfilled. If the check is disabled, a rationale needs to be provided in the comment field (not mandatory for recommended setting checks). Please see description of parameter {$vId} in M4_MODULE_NAME module for details.  Requirement description: '{$vRequirementText}'"/>
         </a:da>
         <a:da name="WARNING" type="XPath">
            <!-- A warning is shown if this XPath evaluates to true -->
            <a:tst expr="PreConfig:isConfigValidationWarning(.)"
                   true="Requirement {$vRequirementId} not met. Please see description of parameter {$vId} in M4_MODULE_NAME module for details.  Requirement description: '{$vRequirementText}'"/>
         </a:da>

      </v:var>

   </xsl:template>


</xsl:stylesheet>
