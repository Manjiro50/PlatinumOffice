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
'*  short description : Tools->Options Load/Save: General
'*
'\******************************************************************************

testcase tLoadSaveGeneral
    Dim lbSave(15) as Boolean
    Dim lsSave(20) as String
    Dim AppCount as Integer
    dim i as Integer


    ToolsOptions
    hToolsOptions("LoadSave","General")
    printlog " - save old settings"
    lbSave(13) = BenutzerspezifischeEinstellungen.IsChecked
    lbSave(1)  = DokumenteigenschaftenBearbeiten.IsChecked
    lbSave(2)  = Sicherungskopie.IsChecked
    lbSave(3)  = AutomatischSpeichern.IsChecked

    if AutomatischSpeichern.IsChecked then
        lsSave(1) = Minuten.GetText
    endif

    lbSave(10) = NoPrettyPrinting.IsChecked
    lbSave(11) = URLimDateisystem.IsChecked
    lbSave(12) = URLimInternet.IsChecked

    printlog("Listed Documenttypes are: ")
    AppCount = Dokumenttyp.GetItemCount
    if (AppCount > 7) then
        Warnlog( "Seven applications should be listed, there are " & AppCount )
        for i = 1 to AppCount
            DokumentTyp.select(i)
            printlog( "    -  " & DokumentTyp.getSelText)
        next i
    endif
    
    for i=1 to AppCount
        Dokumenttyp.Select(i)
        lsSave(2+i)          = Dokumenttyp.GetSelText
        lsSave(2+AppCount+i) = Filter.GetSelText
    next i

    printlog " - invert/change settings"
    if lbSave(13) then
        BenutzerspezifischeEinstellungen.UnCheck
    else
        BenutzerspezifischeEinstellungen.Check
    endif

    if lbSave(1) then
        DokumenteigenschaftenBearbeiten.Uncheck
    else
        DokumenteigenschaftenBearbeiten.Check
    endif

    if lbSave(2) then
        Sicherungskopie.Uncheck
    else
        Sicherungskopie.Check
    endif

    if lbSave(3) then
        AutomatischSpeichern.Uncheck
    else
        AutomatischSpeichern.Check
    endif

    if AutomatischSpeichern.IsChecked then
        lsSave(1) = Minuten.GetText
        Minuten.SetText "23"
    endif

    if lbSave(10) then
        NoPrettyPrinting.Uncheck
    else
        NoPrettyPrinting.Check
    endif

    if lbSave(11) then
        URLimDateisystem.Uncheck
    else
        URLimDateisystem.Check
    endif

    if lbSave(12) then
        URLimInternet.Uncheck
    else
        URLimInternet.Check
    endif

    printlog( "Setting filters for documenttypes: Select third item from every list" )

    for i=1 to AppCount
        Dokumenttyp.Select(i)
        Filter.Select(3)
        printlog( "Doctype: " & Dokumenttyp.getSelText() & " has filter: " & Filter.getSelText() )
    next i

    printlog " - close options-dlg with OK"
    kontext "ExtrasOptionenDlg"
    hCloseDialog( ExtrasOptionenDlg, "ok" )

    printlog " - exit/restart StarOffice"
    ExitRestartTheOffice

    printlog " - check inverting/changes"
    ToolsOptions
    hToolsOptions ( "LoadSave", "General" )

    if BenutzerspezifischeEinstellungen.IsChecked = lbSave ( 13 ) then
        Warnlog "'Load user setting with document' => changes not saved"
    endif

    if DokumenteigenschaftenBearbeiten.IsChecked = lbSave ( 1 ) then
        Warnlog "'Edit document properties before saving' => changes not saved"
    endif

    if Sicherungskopie.IsChecked = lbSave ( 2 ) then
        Warnlog "'Create backup copy' => changes not saved"
    endif

    if AutomatischSpeichern.IsChecked = lbSave ( 3 ) then
        printlog "AutoSave => changes not saved"
    endif

    if AutomatischSpeichern.IsChecked then
        if Minuten.GetText <> "23" then
            Warnlog "Minutes for AutoSave => changes not saved"
        endif
    endif
    if NoPrettyPrinting.IsChecked = lbSave ( 10 ) then
        Warnlog "no pretty printing => changes not saved"
    endif

    if URLimDateisystem.IsChecked = lbSave ( 11 ) then
        Warnlog "URL: File system => changes not saved"
    endif

    if URLimInternet.IsChecked = lbSave ( 12 ) then
        Warnlog "URL: Internet => changes not saved"
    endif

    printlog( "Verifying filters for documenttypes: Select third item from every list" )
    for i=1 to AppCount
        Dokumenttyp.Select(i)
        printlog( "Doctype: " & Dokumenttyp.getSelText() & " has filter: " & Filter.getSelText() )

        if Filter.GetSelIndex <> 3 then
            '#i79150# 
            warnlog( "Some options in Tools/Options->Load/Save->General are not saved" )
        endif
    next i

    printlog " - make other changes"
    BenutzerspezifischeEinstellungen.Uncheck
    DokumenteigenschaftenBearbeiten.Check
    Sicherungskopie.Uncheck
    AutomatischSpeichern.Check
    Minuten.SetText "01"
    NoPrettyPrinting.Uncheck
    URLimDateisystem.Uncheck
    URLimInternet.Uncheck

    for i=1 to AppCount
        Dokumenttyp.Select(i)
        Filter.Select(4)
    next i

    printlog " - close options-dlg with OK"

    kontext "extrasoptionendlg"
    hCloseDialog( ExtrasOptionenDlg, "ok" )

    printlog "    - react on messageboxes for loosing settings after changing default-filters"
    kontext "FilterWarning"
    for i=1 to AppCount
        if FilterWarning.Exists(5) then
            FilterWarning.OK
        else
            i = AppCount + 1
        endif
    next i
    WaitSlot()

    printlog " - check second changes"
    ToolsOptions
    hToolsOptions ( "LoadSave", "General" )

    if BenutzerspezifischeEinstellungen.IsChecked <> FALSE then
        Warnlog "'Load user setting with document' => changes not saved"
    endif

    if DokumenteigenschaftenBearbeiten.IsChecked <> TRUE then
        Warnlog "'Edit document properties before saving' => changes not saved"
    endif

    if Sicherungskopie.IsChecked <> FALSE then
        Warnlog "'Create backup copy' => changes not saved"
    endif

    if AutomatischSpeichern.IsChecked <> TRUE then
        Warnlog "AutoSave => changes not saved"
    endif

    if Minuten.GetText <> "1" then
        Warnlog "Minutes for AutoSave => changes not saved"
    endif

    if NoPrettyPrinting.IsChecked <> FALSE then
        Warnlog "no pretty printing => changes not saved"
    endif

    if URLimDateisystem.IsChecked <> FALSE then
        Warnlog "URL: File system => changes not saved"
    endif

    if URLimInternet.IsChecked <> FALSE  then
        Warnlog "URL: Internet => changes not saved"
    endif

    for i=1 to AppCount
        Dokumenttyp.Select(i)
        if Filter.GetSelIndex <> 4 then
            Warnlog "Document '" + Dokumenttyp.GetSelText + "': changes not saved"
        endif
    next i

    printlog " - reset to saved settings"
    if lbSave ( 13 ) = FALSE then
        BenutzerspezifischeEinstellungen.UnCheck else BenutzerspezifischeEinstellungen.Check
    endif

    if lbSave ( 1  ) = FALSE then
        DokumenteigenschaftenBearbeiten.UnCheck else DokumenteigenschaftenBearbeiten.Check
    endif
    if lbSave ( 2  ) = FALSE then
        Sicherungskopie.Uncheck else Sicherungskopie.Check
    endif

    AutomatischSpeichern.Check
    Minuten.SetText lsSave ( 1 )

    if lbSave ( 3  ) = FALSE then
        AutomatischSpeichern.Uncheck else AutomatischSpeichern.Check
    endif

    if lbSave ( 10 ) = FALSE then
        NoPrettyPrinting.Uncheck else NoPrettyPrinting.Check
    endif

    if lbSave ( 11 ) = FALSE then
        URLimDateisystem.UnCheck else URLimDateisystem.Check
    endif

    if lbSave ( 12 ) = FALSE then
        URLimInternet.UnCheck else URLimInternet.Check
    endif

    for i=1 to AppCount
        Dokumenttyp.Select(i)
        if Dokumenttyp.GetSelText <> lsSave ( 2 + i ) then
            Warnlog "The sorting of the document-listbox has been changed!"
        endif
        Filter.Select(lsSave(2+AppCount+i))
    next i

    kontext "ExtrasOptionenDlg"
    hCloseDialog( ExtrasOptionenDlg, "ok" )


    printlog " - check settings"
    ToolsOptions
    hToolsOptions ( "LoadSave", "General" )

    if BenutzerspezifischeEinstellungen.IsChecked <> lbSave ( 13 ) then
        Warnlog "'Load user setting with document' => changes not saved"
    endif

    if DokumenteigenschaftenBearbeiten.IsChecked <> lbSave ( 1 ) then
        Warnlog "'Edit document properties before saving' => changes not saved"
    endif

    if Sicherungskopie.IsChecked <> lbSave ( 2 ) then
        Warnlog "'Create backup copy' => changes not saved"
    endif

    if AutomatischSpeichern.IsChecked <> lbSave ( 3 ) then
        Warnlog "AutoSave => changes not saved"
    endif

    if AutomatischSpeichern.IsChecked then
        if Minuten.GetText <> lsSave( 1 ) then
            Warnlog "Minutes for AutoSave => changes not saved"
        endif
    endif

    if NoPrettyPrinting.IsChecked <> lbSave ( 10 ) then
        Warnlog "no pretty printing => changes not saved"
    endif

    if URLimDateisystem.IsChecked <> lbSave ( 11 ) then
        Warnlog "URL: File system => changes not saved"
    endif

    if URLimInternet.IsChecked <> lbSave ( 12 ) then
        Warnlog "URL: Internet => changes not saved"
    endif

    for i=1 to AppCount
        Dokumenttyp.Select(i)
        if Dokumenttyp.GetSelText <> lsSave ( 2 + i ) then
            Warnlog "The sorting of the document-listbox has been changed!"
        endif
        if Filter.GetSelText <> lsSave ( 2 + AppCount + i ) then
            Warnlog "Document '" + Dokumenttyp.GetSelText + "': changes not saved"
        endif
    next i

    kontext "extrasoptionendlg"
    hCloseDialog( ExtrasOptionenDlg, "ok" )

endcase
