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
'* short description : Global resource tests for the menu: File
'*
'*************************************************************************
'*
' #1 tFileExportAsPDF
' #1 tExportAsPDFButton
'*
'\************************************************************************

testcase tFileExportAsPDF
    dim sPDF as string
    dim sTemp as string

    sPDF = "PDF - Portable Document Format (.pdf)"

    '/// open application ///'
    Call hNewDocument

    '/// choose File->Export As PDF ... ///'
    FileExportAsPDF
    ' The file dialog has to come up
    Kontext "SpeichernDlg"
    if SpeichernDlg.exists(5) then
        '/// the selected file type should be: 'PDF - Portable Document Format (.pdf)' ///'
        sTemp = Dateityp.GetSelText
        if (sTemp <> sPDF) then
            Warnlog "filter for PDF export is missing :-( should: '" + sPDF + "'; is: '" + sTemp + "'"
        endif
        '///+ - set Textbox 'File name' to "abc" ///'
        Dateiname.SetText "abc"
        speichern.click
        kontext
        if active.exists(5) then
            ' catch active about already existing file name
            if active.getrt = 304 then
                active.yes
            endif
        endif
    else
        ' changed with SRC680m210 - first options, then file dialog...
        ' kept for testcase backwards compatibility
        'warnlog "Export dialog didn't come up."
    endif
    kontext
    '/// dialog 'PDF Options' comes up ///'
    if active.exists(5) then
        '/// select the tab page 'General' ///'
        active.setPage PDFOptions
        kontext "PDFOptions"
        if PDFOptions.exists(5) then
            dialogTest(PDFOptions)
        else
            warnlog "Tab page 'PDF Options - General' isn't available."
        endif
    else
        warnlog "Dialog 'PDF Options' didn't come up"
    endif
    kontext
    if active.exists(5) then
        '/// select the tab page 'Initial View' ///'
        active.setPage PDFOptionsInitialView
        kontext "PDFOptionsInitialView"
        if PDFOptionsInitialView.exists(5) then
            dialogTest(PDFOptionsInitialView)
        else
            warnlog "Tab page 'PDF Options - Initial View' isn't available."
        endif
    endif
    kontext
    if active.exists(5) then
        '/// select the tab page 'User Interface' ///'
        active.setPage PDFOptionsUserInterface
        kontext "PDFOptionsUserInterface"
        if PDFOptionsUserInterface.exists(5) then
            dialogTest(PDFOptionsUserInterface)
        else
            warnlog "Tab page 'PDF Options - User Interface' isn't available."
        endif
    endif
    kontext
    if active.exists(5) then
        '/// select the tab page 'General' ///'
        active.setPage PDFOptions
        kontext "PDFOptions"
        '/// close the dialog with 'Cancel' ///'
        if PDFOptions.exists(5) then
            PDFOptions.cancel
        else
            warnlog "Tab page 'PDF Options - General' isn't available."
        endif
    endif
    '/// close application ///'
    Call hCloseDocument
endcase
'
'-------------------------------------------------------------------------------
'
testcase tExportAsPDFButton
    Dim sTemp as string
    '/// Create new document
    Call hNewDocument
    '/// Click the button 'Export Directly as PDF' on the standard toolbar.
    Kontext "Standardbar"
    ExportAsPDF.click
    '///  The 'Export as PDF' dialog has to come up, with the only 'File type' 'PDF - Portable Document Format'
    Kontext "SpeichernDlg"
    if SpeichernDlg.exists(1) then
        sTemp = Dateityp.GetSelText
        if InStr(sTemp, "PDF") = 0 then
            warnlog "Filter for PDF export seems to be wrong or is missing in selection."
        endif
        '/// Leave dialog with CANCEL button
        SpeichernDlg.Cancel
    else
        warnlog "SaveAsPDF dialog did not come up."
    endif
    '/// Close spreadsheet document.
    Call hCloseDocument
endcase

