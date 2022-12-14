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
'*  short description : Copy a control with i18n data
'*
'\******************************************************************************

testcase tBasicDialogI18nCopyControl


    const COMMAND_BUTTON = 1            ' id of the command button (formcontrols.inc)
    const DIALOG_NAME = "DialogExport"  ' Name of the first module
    const LANGUAGES_TO_COPY = 5         ' Only copy n languages
    const TARGET_DIALOG = "Target"      ' The name of the dialog the control is pasted to
    const DEFAULT_TIMEOUT = 2
    
    dim cLanguageList( LANGUAGES_TO_COPY ) as string ' Note: Index 0 is used
    dim iCurrentLanguage as integer
    
    ' These are the strings used to simulate localized text
    dim cIDStrings( 5 ) as string
        cIDStrings( 0 ) = "language_a"
        cIDStrings( 1 ) = "language_b"
        cIDStrings( 2 ) = "language_c"
        cIDStrings( 3 ) = "language_d"
        cIDStrings( 4 ) = "language_e"
        cIDStrings( 5 ) = "language_f"
        
    dim cTempString as string
        
    ' These are the IDE internal coordinates of the control, used to restore
    ' identical coordinates in the source and target dialogs
    dim iOriginalCoordinates( 4 ) as integer
    
    hCreateDocument()

    printlog( "Test init: Setting up environment" )
    if ( hInitFormControls( DIALOG_NAME ) ) then

        printlog( "Draw a commandbutton on the dialog" )
        hDrawControlOnDialog( COMMAND_BUTTON )

        printlog( "Open the property browser" )
        hOpenPropertyBrowser()
        kontext "TabGeneralControl"
        printlog( "Get internal coordinates for the control" )
        iOriginalCoordinates( 1 ) = height.getText()
        iOriginalCoordinates( 2 ) = width.getText()
        iOriginalCoordinates( 3 ) = PosX.getText()
        iOriginalCoordinates( 4 ) = PosY.getText()
        printlog( "Height: " & iOriginalCoordinates( 1 ) )
        printlog( "Width.: " & iOriginalCoordinates( 2 ) )
        printlog( "Pos X.: " & iOriginalCoordinates( 3 ) )
        printlog( "Pos Y.: " & iOriginalCoordinates( 4 ) )
        hClosePropertyBrowser()

        qaerrorlog( "#i80456# properties button not enabled when a formcontrol is inserted via keyboard" )

        kontext "ToolsCollectionBar"
        printlog( "Click <Manage Languages>" )
        ManageLanguage.click()

        kontext "ManageUILanguages"
        if ( ManageUILanguages.exists( DEFAULT_TIMEOUT ) ) then

            printlog( "Click <Add>" )
            hClickButton( Add )

            kontext "SetDefaultLanguage"
            if ( SetDefaultLanguage.exists( DEFAULT_TIMEOUT ) ) then
                hCloseDialog( SetDefaultLanguage, "ok" )
            else
                warnlog( "Set Default Language dialog is missing" )
            endif
        else
            warnlog( "Unable to open Manage UI Languages dialog" )
        endif

        kontext "ManageUILanguages"
        if ( ManageUILanguages.exists( DEFAULT_TIMEOUT ) ) then

            printlog( "Click <Add>" )
            hClickButton( Add )

            kontext "AddUserInterface"
            if ( AddUserInterface.exists( DEFAULT_TIMEOUT ) ) then
                for iCurrentLanguage = 1 to LANGUAGES_TO_COPY
                    AddNewControl.select( iCurrentLanguage )
                    AddNewControl.check()
                next iCurrentLanguage
                hCloseDialog( AddUserInterface, "ok" )
            else
                warnlog( "Add User Interface Language dialog is missing" )
            endif
        else
            warnlog( "Unable to open Manage UI Languages dialog" )
        endif

        kontext "ManageUILanguages"
        for iCurrentLanguage = 0 to LANGUAGES_TO_COPY
            PresentLanguages.select( iCurrentLanguage + 1 )
            cLanguageList( iCurrentLanguage ) = PresentLanguages.getSelText()
            printlog( iCurrentLanguage & ": " & cLanguageList( iCurrentLanguage ) )
        next iCurrentLanguage

        kontext "ManageUILanguages"
        hCloseDialog( ManageUILanguages, "close" )

        printlog( "Localizing control" )
        for iCurrentLanguage = 0 to LANGUAGES_TO_COPY
            kontext "TranslationBar"
            CurrentLanguage.select( iCurrentLanguage + 1 )
            kontext "BasicIde"
            hSelectControl( COMMAND_BUTTON )
            hOpenPropertyBrowser()
            printlog( "Setting string: " & cIDStrings( iCurrentLanguage ) )
            kontext "TabGeneralControl"
            NameText.typeKeys( cIDStrings( iCurrentLanguage ) & "<RETURN>" )
            hClosePropertyBrowser()
        next iCurrentLanguage

        printlog( "Copy control" )
        hUseAsyncSlot( "EditCopy" )

        printlog( "New dialog" )
        hNewDialog()

        printlog( "Paste control" )
        hUseAsyncSlot( "EditPaste" )

        hOpenPropertyBrowser()
        kontext "TabGeneralControl"
        printlog( "Set coordinates to be identical with those from the source control" )
        PosX.typeKeys  (  )
        PosX.typeKeys  ( "<HOME><SHIFT END>" & iOriginalCoordinates( 3 ) & "<RETURN>" )
        PosY.typeKeys  ( "<HOME><SHIFT END>" & iOriginalCoordinates( 4 ) & "<RETURN>" )
        Height.typeKeys( "<HOME><SHIFT END>" & iOriginalCoordinates( 1 ) & "<RETURN>" )
        Width.typeKeys ( "<HOME><SHIFT END>" & iOriginalCoordinates( 2 ) & "<RETURN>" )
        hClosePropertyBrowser


        hOpenPropertyBrowser()
        kontext "TabGeneralControl"
        printlog( "Get internal coordinates for the control" )
        iOriginalCoordinates( 1 ) = height.getText()
        iOriginalCoordinates( 2 ) = width.getText()
        iOriginalCoordinates( 3 ) = PosX.getText()
        iOriginalCoordinates( 4 ) = PosY.getText()
        printlog( "Height: " & iOriginalCoordinates( 1 ) )
        printlog( "Width.: " & iOriginalCoordinates( 2 ) )
        printlog( "Pos X.: " & iOriginalCoordinates( 3 ) )
        printlog( "Pos Y.: " & iOriginalCoordinates( 4 ) )
        hClosePropertyBrowser()


        kontext "TranslationBar"
        for iCurrentLanguage = 0 to LANGUAGES_TO_COPY
            CurrentLanguage.select( iCurrentLanguage + 1 )
            cTempString = CurrentLanguage.getSelText()
            if ( cTempString = cLanguageList( iCurrentLanguage ) ) then
                printlog( "Language <" & cTempString & "> was successfully copied" )
            else
                warnlog( "Either a language was lost or the sort order changed" )
                printlog( "Expected: " & cLanguageList( iCurrentLanguage ) )
                printlog( "Found...: " & cTempString )
            endif
        next iCurrentLanguage

        hCloseBasicIDE()
    else
        warnlog( "Failed to initialize dialog" )
    endif
    hDestroyDocument()
    
endcase

