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

testcase tBasicVBACompatThisWorkBook()

    printlog( "Functionality of .thisWorkbook" )
    ' Based on issue #i110672

    const IMPORT_EXCEL_MACROS  = TRUE
    const EXEC_EXCEL_MACROS    = TRUE
    const DOCUMENT_NAME        = "vba-thisworkbook.xls"
    const LIBRARY_NAME         = "Standard"
    const MODULE_NAME          = "Module1"
    const EXPECTED_MACRO_COUNT = 2
    const MAX_REPEAT_COUNT     = 2
    const MAX_WAIT             = 2

    dim macro_identifier( EXPECTED_MACRO_COUNT )
        macro_identifier( 1 ) = "Test 1 passed."
        macro_identifier( 2 ) = "Test 2 passed."

    dim cTestFile as string
        cTestFile = gTesttoolPath & "framework/optional/input/vba-compat/" & DOCUMENT_NAME

    dim iMacroPosition as integer
    dim iCurrentMacro as integer
    dim iRepeat as integer

    printlog( "Set macro security to low" )
    hSetMacroSecurityAPI( GC_MACRO_SECURITY_LEVEL_LOW )
    
    printlog( "Open Tools/Options" )
    hSetExcelBasicImportMode( IMPORT_EXCEL_MACROS, EXEC_EXCEL_MACROS )
    
    printlog( "Load the test file" )
    hFileOpen( cTestFile )

    printlog( "Execute the procedure twice to trigger issue 111553" )
    for iRepeat = 1 to MAX_REPEAT_COUNT

        ToolsMacro_uno

        kontext "Makro"
        if ( Makro.exists( MAX_WAIT ) ) then

            iMacroPosition = hSelectNodeByName( MakroAus, DOCUMENT_NAME )
            hExpandNode( MakroAus, iMacroPosition )

            printlog( "Move to node <" & LIBRARY_NAME & ">" )
            iMacroPosition = hSelectNextNode( MakroAus )
            if ( not hVerifyNodeName( MakroAus, LIBRARY_NAME ) ) then
                warnlog( "This is not the expected library" )
            endif

            printlog( "Move to node <" & MODULE_NAME & ">" )
            hSelectNextNode( MakroAus )
            if ( not hVerifyNodeName( MakroAus, MODULE_NAME ) ) then
                warnlog( "This is not the expected module" )
            endif

            printlog( "Click <Ausfuehren> to execute the macro" )
            iMacroPosition = hClickButton( Ausfuehren )

            printlog( "Check for two expected messageboxes" )
            for iCurrentMacro = 1 to EXPECTED_MACRO_COUNT

                kontext "Active"
                printlog( "Check for messagebox: " & macro_identifier( iCurrentMacro ) )
                if ( Active.exists( MAX_WAIT ) ) then

                    if ( Active.getText() = macro_identifier( iCurrentMacro ) ) then
                        printlog( "Correct macro executed" )
                    else
                        printlog( "Macro execution error, trying to identify..." )
                        if ( instr( Active.getText(), "BASIC runtime error." ) > 0 ) then
                            if ( iRepeat = MAX_REPEAT_COUNT ) then
                                warnlog( "#i111533 - Cannot execute ThisWorkbook macro twice" )
                                Active.ok()
                                hFileCloseAll()
                                goto endsub
                            else
                                warnlog( "Executing macro failed" )
                                goto endsub
                            endif
                        else
                            warnlog( "Unknown messagebox. Aborting test" )
                            goto endsub
                        endif
                    endif

                    Active.ok()

                else
                    warnlog( "Expected messagebox not displayed within reasonable timeframe" )
                    goto endsub
                endif

            next iCurrentMacro
        else
            warnlog( "A macro with the name <" & MODULE_NAME & "> could not be found" )
            goto endsub
        endif

    next iRepeat

    printlog( "Cleanup" )
    hCloseDocument()
    hSetExcelImportModeDefault()    
    hSetMacroSecurityAPI( GC_MACRO_SECURITY_LEVEL_DEFAULT )

endcase


