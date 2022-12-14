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
'* short description : Global Routines for Document Handling; Part two
'*
'\***********************************************************************

sub hTabelleEinfuegen
    '/// <b>WRITER only </b>///'
    '///  hTabelleEinfuegen hInsertTable ///'
    '/// insert a dummy table in writer/writerweb/masterdocument ///'
    TableInsertTable

    Kontext "TabelleEinfuegenWriter"
    if ( TabelleEinfuegenWriter.exists( 2 ) ) then

        hCloseDialog( TabelleEinfuegenWriter, "ok" )

        Kontext "TableObjectbar"
        if ( TableObjectbar.exists( 1 ) ) then
            ' We are happy then, do nothing
        else
            Kontext "TextObjectbar"
            TextObjectbar.SetNextToolBox
        end if

        select case ( gApplication )
        Case "WRITER"         : Kontext "DocumentWriter"
        Case "MASTERDOCUMENT" : Kontext "DocumentMasterDoc"
        Case "HTML"           : Kontext "DocumentWriterWeb"
        end select
    else
        warnlog( "hTabelleEinfuegen: Failed to open <TabelleEinfuegenWriter> dialog" )
    endif

end sub
'
'-------------------------------------------------------------------------------
'
sub ZellenMarkieren ( Down%, Right% )
    '/// <b>CALC only</b> ///'
    '/// ZellenMarkieren ( Down%, Right% ) : mark the cells ///'
    Dim Anzahl as Integer

    Kontext "DocumentCalc"
    Anzahl = Right% - 1
    DocumentCalc.TypeKeys "<Shift Right>", Anzahl
    Anzahl = Down% - 1
    DocumentCalc.TypeKeys "<Shift Down>", Anzahl
end sub
'
'-------------------------------------------------------------------------------
'
sub hRechteckErstellen ( BeginX%, BeginY%, EndX%, EndY% )
    '/// <b>IMPRESS/DRAW only</b> ///'
    '/// hRechteckErstellen ( BeginX, BeginY, EndX, EndY ) : create a rectangle ///'
    WL_DRAW_Rechteck
    gMouseMove ( BeginX%, BeginY%, EndX%, EndY% )
end sub
'
'-------------------------------------------------------------------------------
'
sub hTextrahmenErstellen ( TextEingabe$, BeginX%, BeginY%, EndX%, EndY% )
    '/// <b>IMPRESS/DRAW only</b> ///'
    '/// hTextrahmenErstellen ( String, BeginX, BeginY, EndX, EndY ) : create a textbox with a textstring ///'
    WL_SD_TextEinfuegenDraw
    gMouseMove ( BeginX%, BeginY%, EndX%, EndY% )
    hTypeKeys TextEingabe$
end sub
'
'-------------------------------------------------------------------------------
'
sub SchreibenInMathdok ( Eingabe as String )
    '/// <b>MATH only</b> ///'
    '/// SchreibenInMathDok ( String ) : write text in a mathdocument ( with clipboard ) ///'
    if Eingabe <> "Unsinn" then
        SetClipboard Eingabe
    else
        SetClipboard "NROOT <?> <?><over b==<?>"
    endif
    if (GetClipboard() <> Eingabe) then
        warnlog "--No Clipboard available :-(--"
        printlog "---ClipTest--- should: "+Eingabe +", is: "+GetClipboard
    endif
    hUseAsyncSlot( "EditPaste" )
end sub
'
'-------------------------------------------------------------------------------
'
function fSelectFirstOLE() as integer
    'Select first visible OLE object using Navigator
    'Returns error-code:
    '+ 0 := Sucess
    '- 1 := unknown application

    const RETVAL_SUCCESS = 0
    const RETVAL_UNKNOWN_APPLICATION = -1

    const MAX_WAIT_FOR_NAVIGATOR = 10

    dim bNavigatorWasVisible as boolean : bNavigatorWasVisible = FALSE
    dim iIndex as integer

    fSelectFirstOLE() = RETVAL_UNKNOWN_APPLICATION

    select case ( gApplication )
    case "CALC"                     :   Kontext "NavigatorCalc"
        'First check if Navigator is visible and remember result
        if NavigatorCalc.exists ( MAX_WAIT_FOR_NAVIGATOR ) then
            bNavigatorWasVisible = TRUE
        else
            try
                'Invoke Navigator if not visible
                ViewNavigator
            catch
                'If inside chart or elsewhere the call
                'will fail. Again trying the slot after
                'switching to the document.
                Kontext "DocumentCalc"
                DocumentCalc.TypeKeys "<Escape>"
                ViewNavigator
            endcatch
        end if
        Kontext "NavigatorCalc"
        if NavigatorCalc.exists ( MAX_WAIT_FOR_NAVIGATOR ) then
            'Select first OLE in list
            Liste.TypeKeys "<HOME>"
            for iIndex = 1 to 8
                Liste.TypeKeys "-"
                wait 500
                Liste.TypeKeys "<DOWN>"
                wait 500
            next iIndex
            Liste.select(6)
            Liste.TypeKeys "+"
            Liste.TypeKeys "<DOWN><RETURN>"
            fSelectFirstOLE() = RETVAL_SUCCESS
        else
            QAErrorLog "Navigator couldn't be opened!"
        end if
    case "DRAW" , "IMPRESS"         :   Kontext "NavigatorDraw"
        if NavigatorDraw.Exists( MAX_WAIT_FOR_NAVIGATOR ) then
            bNavigatorWasVisible = TRUE
        else
            try
                'Invoke Navigator if not visible
                ViewNavigator
            catch
                'If inside chart or elsewhere the call
                'will fail. Again trying the slot after
                'switching to the document.
                Kontext "DocumentDraw"
                DocumentDraw.TypeKeys "<Escape>"
                ViewNavigator
            endcatch
            Kontext "NavigatorDraw"
            if NavigatorDraw.exists( MAX_WAIT_FOR_NAVIGATOR ) then
                'Select first OLE in list
                Liste.TypeKeys "<HOME>"
                Liste.select(1)
                Liste.TypeKeys "+<DOWN><RETURN>"
                fSelectFirstOLE() = RETVAL_SUCCESS
            else
                QAErrorLog "Navigator did not open!"
            end if
        end if

    case "WRITER" , "HTML" , "MASTERDOCUMENT" :
        select case ( gApplication )
        case "MASTERDOCUMENT"    :   Kontext "NavigatorGlobalDoc"
            if NavigatorGlobalDoc.Exists( MAX_WAIT_FOR_NAVIGATOR ) then
                bNavigatorWasVisible = TRUE
            else
                ViewNavigator
            end if
            wait 500
            Kontext "NavigatorGlobalDoc"
            if Liste.IsVisible then
                Kontext "GlobaldokumentToolbox"
                Umschalten.Click
            endif
        case else           :   Kontext "NavigatorWriter"
            'First check if Navigator is visible and remember result
            if NavigatorWriter.Exists ( MAX_WAIT_FOR_NAVIGATOR ) then
                bNavigatorWasVisible = TRUE
            else
                try
                    'Invoke Navigator if not visible
                    ViewNavigator
                catch
                    'If inside chart or elsewhere the call
                    'will fail. Again trying the slot after
                    'switching to the document.
                    Kontext "DocumentWriter"
                    call gMouseclick (99,99)
                    call gMouseclick (50,50)
                    ViewNavigator
                endcatch
            end if
        end select
        Kontext "NavigatorWriter"
        if NavigatorWriter.Exists( MAX_WAIT_FOR_NAVIGATOR ) then
			' Check if all content is visible
			if Auswahlliste.GetItemCount < 2 then
				Inhaltsansicht.Click
			end if
            'Select first OLE in list
            Auswahlliste.TypeKeys "<HOME>"
            for iIndex = 1 to 13
                Auswahlliste.TypeKeys "-<DOWN>"
            next iIndex
            Auswahlliste.select(5)
            Auswahlliste.TypeKeys "+<DOWN><RETURN>"
            fSelectFirstOLE() = RETVAL_SUCCESS
        else
            QAErrorLog "Navigator did not occoured!"
        end if
    case else                       :   QAErrorLog "Application not supported"
    end select

    'Close navigator if it was invisible by entering the routine
    if bNavigatorWasVisible = TRUE then
        printlog "Leaving navigator open as initially found"
    else
        if ( fSelectFirstOLE = RETVAL_SUCCESS ) then
            ViewNavigator
            printlog "Closing navigator as initially found"
        else
            printlog "Closing navigator not needed. It was not possible to open it."
        end if
    end if
end function
