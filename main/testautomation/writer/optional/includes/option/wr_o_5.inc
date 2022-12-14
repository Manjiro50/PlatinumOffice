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
'* short description : This testcase is for thai issues only
'*
'\***********************************************************************

sub wr_o_5

    Call tLanguageSettingsComplexTextLayout

end sub

testcase tLanguageSettingsComplexTextLayout

    Dim i as integer
    Dim j as integer
    Dim iNumeralsCounter as integer
    Dim iNumeralsCount as integer
    Dim bAsianLanguage as boolean
    Dim bCTLLanguage as boolean
    Dim sCTLLan() as string
    Dim sCurrentDocumentLanguage as string
    Dim sCurrentCTLLanguage as string
    Dim bSequenceChecking as boolean

    '/// Open new writerdocument
    Call hNewDocument
    '/// Activate Asian support
    bAsianLanguage = ActiveDeactivateAsianSupport(True)
    '/// Activate CTL support 
    bCTLLanguage = ActiveDeactivateCTLSupport(True)

	ToolsOptions
        '/// Goto 'Tools->Options->Language settings->Languages
	Call hToolsOptions ("LanguageSettings","Languages")
        sCurrentCTLLanguage = LanguageComplexScript.GetSelText
	Kontext "TabSprachen"
    For i = 1 to LanguageComplexScript.GetItemCount
        '/// Select CTL-Language
        LanguageComplexScript.Select i
        sCurrentDocumentLanguage = LanguageComplexScript.GetSelText
        printlog "- Current selected CTL Language: " & sCurrentDocumentLanguage
        '/// close options dialog with 'ok'
        Kontext "ExtrasOptionenDlg"
        ExtrasOptionenDlg.Ok
        '/// Reopen options and go to Tabpage 'Complex Text Layout'
        ToolsOptions
        Call hToolsOptions ("LanguageSettings","ComplexTextLayout")

        Kontext "TabComplexTextLayout"
            bSequenceChecking = FALSE
            Select Case iSprache
                '/// Checkboxes under 'Sequence checking' should all be checked for CTL languages
                '/// + like "Thai", "Lao", "Khmer", "Vietnamese"
                Case 01
                    sCTLLan = Array("Thai", "Lao", "Khmer", "Burmese", "Vietnamese")
                Case 49
                    sCTLLan = Array("Thai", "Lao", "Khmer", "Birmanisch", "Vietnamesisch")
                Case else
                    QAErrorlog "Please adapt testcase for this language"
                    Kontext "ExtrasOptionenDlg"
                        ExtrasOptionenDlg.Ok
                    goto IfNoSupport
		end select

        for j = 0 to 4
            if sCTLLan(j) = sCurrentDocumentLanguage then
                bSequenceChecking = TRUE
                exit for
            end if
        next j

        Select Case bSequenceChecking
            Case TRUE
                if UseSequenceChecking.IsChecked = False then
                    Warnlog "'Sequence Checking' should be checked for language: " & sCurrentDocumentLanguage
                end if
                if Restricted.IsEnabled = False or Restricted.IsChecked = False then
                    Warnlog "'Restricted' should be enabled and checked for language: " & sCurrentDocumentLanguage
                end if
                if TypeAndReplace.IsEnabled = False or TypeAndReplace.IsChecked = False then
                    Warnlog "'Type And Replace' should be enabled and checked for language: " & sCurrentDocumentLanguage
                end if

            Case FALSE
                if UseSequenceChecking.IsChecked = True then
                    QAErrorlog "'Sequence Checking' should not be checked for language: " & sCurrentDocumentLanguage
                end if
                if Restricted.IsEnabled = True AND Restricted.IsChecked = True then
                    QAErrorlog "'Restricted' should not be checked for language: " & sCurrentDocumentLanguage
                end if
                if TypeAndReplace.IsEnabled = True AND TypeAndReplace.IsChecked = True then
                    QAErrorlog "'Type And Replace' should not checked for language: " & sCurrentDocumentLanguage
                end if
        end select

        'Get the number of Numerals-entries.
        iNumeralsCount = Numerals.GetItemCount

        Kontext "ExtrasOptionenDlg"
            ExtrasOptionenDlg.Ok
        ToolsOptions
        Call hToolsOptions ("LanguageSettings","Languages")
        Kontext "TabSprachen"
    next i

    Kontext "ExtrasOptionenDlg"
        if ExtrasOptionenDlg.Exists then ExtrasOptionenDlg.Ok

    printlog "Check the Numerals-menu."
    ToolsOptions
    Call hToolsOptions ("LanguageSettings","ComplexTextLayout")

    Printlog " Select every entry in the list, then press OK to close the dialogue, then open it again and check if the value got saved."
    for iNumeralsCounter = 1 to iNumeralsCount
        Numerals.Select iNumeralsCounter
        Printlog " Numerals nr: " + iNumeralsCounter + " = " + Numerals.GetSelText

        'Press ok, and open the dialogue again.
        Kontext "ExtrasOptionenDlg"
	    if ExtrasOptionenDlg.Exists then ExtrasOptionenDlg.Ok
        ToolsOptions
        Call hToolsOptions ("LanguageSettings","ComplexTextLayout")

        if Numerals.GetSelIndex <> iNumeralsCounter then Warnlog "The Numeral-Entry number: " + iNumeralsCounter + " didn't get saved when pressing OK in the FormatCharacter-dialogue."
    next iNumeralsCounter

    Kontext "ExtrasOptionenDlg"
    ExtrasOptionenDlg.Ok

    '/// Choose Thai as CTL language
    ToolsOptions
    Call hToolsOptions ("LanguageSettings","Languages")
    Kontext "TabSprachen"
    LanguageComplexScript.Select sCTLLan(0)
    Kontext "ExtrasOptionenDlg"
    ExtrasOptionenDlg.Ok

    '/// Restart office
    Call wOfficeRestart

    '/// Reopen options and go to Tabpage 'Complex Text Layout'
    ToolsOptions
    Call hToolsOptions ("LanguageSettings","ComplexTextLayout")
    '/// Check if all checkboxes under 'Sequence checking' are checked 
    if UseSequenceChecking.IsChecked = False then
        Warnlog "'Sequence Checking' should be checked for language: " & sCTLLan(0)
    end if
    if Restricted.IsEnabled = False or Restricted.IsChecked = False then
        Warnlog "'Restricted' should be enabled and checked for language: " & sCTLLan(0)
    end if
    if TypeAndReplace.IsEnabled = False or TypeAndReplace.IsChecked = False then
        Warnlog "'Type And Replace' should be enabled and checked for language: " & sCTLLan(0)
    end if

    '/// Reset CTL Language
    Kontext "ExtrasOptionenDlg"
    ExtrasOptionenDlg.Ok
    ToolsOptions
    Call hToolsOptions ("LanguageSettings","Languages")
    Kontext "TabSprachen"
    LanguageComplexScript.Select sCurrentCTLLanguage
    Kontext "ExtrasOptionenDlg"
    ExtrasOptionenDlg.Ok

IfNoSupport:
    Call ActiveDeactivateAsianSupport(bAsianLanguage)
    Call ActiveDeactivateCTLSupport(bCTLLanguage)

    Do Until GetDocumentCount = 0
        Call hCloseDocument
    Loop
endcase
