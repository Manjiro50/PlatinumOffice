'encoding UTF-8  Do not remove or change this line!
'*************************************************************************
'
'  Licensed to the Apache Software Foundation (ASF) under one
'  or more contributor license agreements.  See the NOTICE file
'  distributed with this work for additional information
'  regarding copyright ownership.  The ASF licenses this file
'  to you under the Apache License, Version 2.0 (the
'  "License"); you may not use this file except in compliance
'  with the License.  You may obtain a copy of the License at
'  
'    http://www.apache.org/licenses/LICENSE-2.0
'  
'  Unless required by applicable law or agreed to in writing,
'  software distributed under the License is distributed on an
'  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
'  KIND, either express or implied.  See the License for the
'  specific language governing permissions and limitations
'  under the License.
'
'*************************************************************************
'*
'*  short description : Test VBA compatibility switches
'*
'\******************************************************************************

testcase tBasicVBACompatImportNothing()

    printlog( "Test VBA compatibility switch / executable Microsoft(R) Excel(R) Macros" )
    printlog( "Test case 1: Do not import macros at all" )
    
    ' This test case is based on the use cases provided in issue #i88690
    ' Spec: http://specs.openoffice.org/appwide/options_settings/Option_Dialog.odt
' Depending on the mode of macro import we have differtent basic libraries listed
    const NODE_COUNT = 72 ' Do not import Microsoft(R) Excel(R) macros at all
    const MACRO_LIST = 0  ' The document library should have no scripts listed
    const DOCUMENT_POSITION_OFFSET = -1

    const IMPORT_EXCEL_MACROS = FALSE
    const EXEC_EXCEL_MACROS   = FALSE

    const DOCUMENT_NAME = "vba-test.xls"
    const MATCH_NONE    = 0
    const MATCH_EXACT   = 1
    const MATCH_PARTLY  = 2

    dim cTestFile as string
        cTestFile = gTesttoolPath & "framework/optional/input/vba-compat/" & DOCUMENT_NAME
        
    dim cNodeCount as integer
     
    printlog( "Set macro security to low" )
    hSetMacroSecurityAPI( GC_MACRO_SECURITY_LEVEL_LOW )
    
    printlog( "Open Tools/Options" )

    hSetExcelBasicImportMode( IMPORT_EXCEL_MACROS, EXEC_EXCEL_MACROS )
    
    printlog( "Load the test file" )
    hFileOpen( cTestFile )
    
    printlog( "Open the Basic organizer" )
    ToolsMacro_uno
    
    printlog( "Expand all nodes" )
    kontext "Makro"
    cNodeCount = hExpandAllNodes( MakroAus )
    
    printlog( "Verify that we have the correct node count for the current mode" )
    if ( gOOo ) then
        if ( cNodeCount <> NODE_COUNT_OOO ) then warnlog( "The number of nodes is incorrect: " & cNodeCount )
    else
        if ( cNodeCount <> NODE_COUNT ) then warnlog( "The number of nodes is incorrect: " & cNodeCount )
    endif
    
    printlog( "Verify position of the document node" )
    MakroAus.select( cNodeCount + DOCUMENT_POSITION_OFFSET )
    select case( hCompareSubStrings( MakroAus.getSelText(), DOCUMENT_NAME  ) )
    case MATCH_NONE   : warnlog ( "The document is not listed at the expected position" )
    case MATCH_EXACT  : printlog( "The document is at the expected position and writable" )
    case MATCH_PARTLY : printlog( "The document is at the expected position and write protected" )
    end select
    
    printlog( "Select the last node, this should be the standard Library for the document" )
    MakroAus.select( cNodeCount ) 
    
    printlog( "Verify that the Standard library for the document has no scripts" )
    if ( MakroListe.getItemCount <> MACRO_LIST ) then
        warnlog( "There should be no macros listed for the current library"
    endif
    
    printlog( "Close Macro Organizer" )
    Kontext "Makro"
    Makro.close()
    WaitSlot()
            
    hCloseDocument()
    hSetExcelImportModeDefault()    
    hSetMacroSecurityAPI( GC_MACRO_SECURITY_LEVEL_DEFAULT )

endcase


