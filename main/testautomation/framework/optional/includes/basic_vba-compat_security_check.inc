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

testcase tBasicVBACompatSecurityCheck()

    printlog( "Test VBA Security feature" )
    printlog( "VBA macros may not ignore global macro security setting" )
    
    ' This test case is based on the use cases provided in issue #i109699
    
    const IMPORT_EXCEL_MACROS = TRUE
    const EXEC_EXCEL_MACROS   = TRUE

    const MACRO_IDENTIFICATION_MESSAGE = "Clicked"
    const MACRO_NAME = "CommandButton1_Click"

    const WORK_FILE = "framework/optional/input/vba-compat/Book1.xls"

    dim cTestFile as string : cTestFile = gTesttoolPath & WORK_FILE
    dim iSecurityLevel as integer


    printlog( "Set VBA macro handling to import and execute" )
    hSetExcelBasicImportMode( IMPORT_EXCEL_MACROS, EXEC_EXCEL_MACROS )

    for iSecurityLevel = GC_MACRO_SECURITY_LEVEL_MEDIUM to GC_MACRO_SECURITY_LEVEL_VERYHIGH

        printlog( "Adjust security level" )
        hSetMacroSecurityAPI( iSecurityLevel )

        printlog( "Load the test file" )
        hFileOpen( cTestFile )

        printlog( "Deny macro execution or close macros blocked message" )
        if ( iSecurityLevel = GC_MACRO_SECURITY_LEVEL_MEDIUM ) then
            hDenyMacroExecution()
        else
            kontext "Active"
            Active.ok()
        endif

        printlog( "Try to execute macro via macro organizer" )
        hMacroOrganizerRunMacro( MACRO_NAME )

        printlog( "Probe for warning message (or macro)" )
        kontext "Active"
        if ( Active.exists( 2 ) ) then
            if ( Active.getText() = MACRO_IDENTIFICATION_MESSAGE ) then
                warnlog( "Macro was executed though macro execution has been denied" )
                Active.ok()
            else
                printlog( "Macro execution blocked - warning is displayed." )
                Active.ok()
            endif
        else
            warnlog( "No warning message for blocked macro execution" )
        endif

        ' recover silently, the warnings above should say it all.
        kontext "Makro"
        if ( Makro.exists() ) then Makro.cancel()

        printlog( "Close file" )
        hDestroyDocument()

    next iSecurityLevel

    printlog( "Reset VBA import options to default" )
    hSetExcelImportModeDefault()

    printlog( "Reset macro security level to default" )
    hSetMacroSecurityAPI( GC_MACRO_SECURITY_LEVEL_DEFAULT )

endcase

