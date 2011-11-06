/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_xmloff.hxx"


#include "XMLIndexTOCSourceContext.hxx"
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XIndexReplace.hpp>
#include "XMLIndexTemplateContext.hxx"
#include "XMLIndexTitleTemplateContext.hxx"
#include "XMLIndexTOCStylesContext.hxx"
#include <xmloff/xmlictxt.hxx>
#include <xmloff/xmlimp.hxx>
#include <xmloff/txtimp.hxx>
#include "xmloff/xmlnmspe.hxx"
#include <xmloff/nmspmap.hxx>
#include <xmloff/xmltoken.hxx>
#include <xmloff/xmluconv.hxx>
#include <tools/debug.hxx>
#include <rtl/ustring.hxx>



using namespace ::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;

const sal_Char sAPI_CreateFromChapter[] = "CreateFromChapter";
const sal_Char sAPI_CreateFromOutline[] = "CreateFromOutline";
const sal_Char sAPI_CreateFromMarks[] = "CreateFromMarks";
const sal_Char sAPI_Level[] = "Level";
const sal_Char sAPI_CreateFromLevelParagraphStyles[] = "CreateFromLevelParagraphStyles";


TYPEINIT1( XMLIndexTOCSourceContext, XMLIndexSourceBaseContext );

XMLIndexTOCSourceContext::XMLIndexTOCSourceContext(
	SvXMLImport& rImport, 
	sal_uInt16 nPrfx,
	const OUString& rLocalName,
	Reference<XPropertySet> & rPropSet)
:	XMLIndexSourceBaseContext(rImport, nPrfx, rLocalName, rPropSet, sal_True)
,	sCreateFromMarks(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromMarks))
,	sLevel(RTL_CONSTASCII_USTRINGPARAM(sAPI_Level))
,	sCreateFromOutline(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromOutline))
,	sCreateFromLevelParagraphStyles(RTL_CONSTASCII_USTRINGPARAM(sAPI_CreateFromLevelParagraphStyles))
	// use all chapters by default
,	nOutlineLevel(rImport.GetTextImport()->GetChapterNumbering()->getCount())
,	bUseOutline(sal_True)
,	bUseMarks(sal_True)
,	bUseParagraphStyles(sal_False)
{
}

XMLIndexTOCSourceContext::~XMLIndexTOCSourceContext()
{
}

void XMLIndexTOCSourceContext::ProcessAttribute(
	enum IndexSourceParamEnum eParam, 
	const OUString& rValue)
{
	switch (eParam)
	{
		case XML_TOK_INDEXSOURCE_OUTLINE_LEVEL:
			if ( IsXMLToken( rValue, XML_NONE ) )
			{
                // #104651# use OUTLINE_LEVEL and USE_OUTLINE_LEVEL instead of
                // OUTLINE_LEVEL with values none|1..10. For backwards
                // compatibility, 'none' must still be read.
				bUseOutline = sal_False;
			}
			else
			{
				sal_Int32 nTmp;
				if (SvXMLUnitConverter::convertNumber(
					nTmp, rValue, 1, GetImport().GetTextImport()->
					GetChapterNumbering()->getCount()))
				{
					bUseOutline = sal_True;
					nOutlineLevel = nTmp;
				}
			}
			break;
			
		case XML_TOK_INDEXSOURCE_USE_OUTLINE_LEVEL:
        {
			sal_Bool bTmp;
			if (SvXMLUnitConverter::convertBool(bTmp, rValue))
			{
				bUseOutline = bTmp;
			}
			break;
		}


		case XML_TOK_INDEXSOURCE_USE_INDEX_MARKS:
		{
			sal_Bool bTmp;
			if (SvXMLUnitConverter::convertBool(bTmp, rValue))
			{
				bUseMarks = bTmp;
			}
			break;
		}

		case XML_TOK_INDEXSOURCE_USE_INDEX_SOURCE_STYLES:
		{
			sal_Bool bTmp;
			if (SvXMLUnitConverter::convertBool(bTmp, rValue))
			{
				bUseParagraphStyles = bTmp;
			}
			break;
		}

		default:
			// default: ask superclass
			XMLIndexSourceBaseContext::ProcessAttribute(eParam, rValue);
			break;
	}
}

void XMLIndexTOCSourceContext::EndElement()
{
	Any aAny;

	aAny.setValue(&bUseMarks, ::getBooleanCppuType());
	rIndexPropertySet->setPropertyValue(sCreateFromMarks, aAny);

	aAny.setValue(&bUseOutline, ::getBooleanCppuType());
	rIndexPropertySet->setPropertyValue(sCreateFromOutline, aAny);

	aAny.setValue(&bUseParagraphStyles, ::getBooleanCppuType());
	rIndexPropertySet->setPropertyValue(sCreateFromLevelParagraphStyles, aAny);

	aAny <<= (sal_Int16)nOutlineLevel;
	rIndexPropertySet->setPropertyValue(sLevel, aAny);

	// process common attributes
	XMLIndexSourceBaseContext::EndElement();
}


SvXMLImportContext* XMLIndexTOCSourceContext::CreateChildContext( 
	sal_uInt16 nPrefix,
	const OUString& rLocalName,
	const Reference<XAttributeList> & xAttrList )
{
	if ( (XML_NAMESPACE_TEXT == nPrefix) &&
		 IsXMLToken(rLocalName, XML_TABLE_OF_CONTENT_ENTRY_TEMPLATE) )
	{
		return new XMLIndexTemplateContext(GetImport(), rIndexPropertySet, 
										   nPrefix, rLocalName,
										   aLevelNameTOCMap,
										   XML_OUTLINE_LEVEL,
										   aLevelStylePropNameTOCMap,
										   aAllowedTokenTypesTOC, sal_True );
	}
	else 
	{
		return XMLIndexSourceBaseContext::CreateChildContext(nPrefix, 
															 rLocalName,
															 xAttrList);
	}
}
