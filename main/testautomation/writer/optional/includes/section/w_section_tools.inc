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
'* short description :  tools/functions for the Section-testing
'*
'************************************************************************
'*
' #1 fInsertSection
' #1 fInsertBookmark
' #1 fInsertFootnote
' #1 fInsertEndnote
' #1 fInsertTable
' #1 fCloseNavigator
' #1 fCheckDirectCursor
' #1 fMultiSelection
'*
'\***********************************************************************

'******************************************************
'* insert a section with name SectionName            **
'******************************************************
function fInsertSection(SectionName as string)
   InsertSection
   wait 500
   Kontext
   Active.Setpage TabBereiche
   Kontext "TabBereiche"
   Bereichsliste.Settext SectionName
   TabBereiche.OK
   wait 500
end function

'******************************************************
'* insert a bookmark with name                       **
'******************************************************
function fInsertBookmark(BookmarkName as string)

    InsertBookmark
    Kontext
    Kontext "TextmarkeEinfuegen"
    Textmarken.SetText BookmarkName
    TextmarkeEinfuegen.OK

end function


'******************************************************
'*    insert a footnote                              **
'******************************************************
function fInsertFootnote(Numbering as string , ConTentInCharater as String)

   InsertFootnote
   Kontext "FussnoteEinfuegen"

   ' check footnote
   Fussnote.Check

   Select Case Numbering
    Case "automatic" : Automatisch.Check
    Case "character" : Zeichen.Check
                       ZeichenText.SetText ConTentInCharater
    Case else : Warnlog "Maybe new options! :-)"
                Automatisch.Check
   end select

   FussnoteEinfuegen.OK

end function


'******************************************************
'* insert a endnote                                  **
'******************************************************
function fInsertEndnote(Numbering as string , ConTentInCharater as String)

   InsertFootnote
   Kontext "FussnoteEinfuegen"

   ' check endnote
   Endnote.Check

   Select Case Numbering
    Case "automatic" : Automatisch.Check
    Case "character" : Zeichen.Check
                       ZeichenText.SetText ConTentInCharater
    Case else : Warnlog "Maybe new options! :-)"
                Automatisch.Check
   end select

   FussnoteEinfuegen.OK

end function


'******************************************************
'* insert a table with name TableName                **
'* Column is table's column's number                 **
'* Row    is table's row   's number                 **
'******************************************************
function fInsertTable(TableName as string, ColumnNumber as string, RowNumber as string)

   InsertTableWriter
   Sleep 1
   Kontext "TabelleEinfuegenWriter"
   TabellenName.SetText TableName

   Spalten.SetText ColumnNumber
   Zeilen.SetText  RowNumber

   TabelleEinfuegenWriter.OK

end function

'*******************************************************
'* Close Navigator                                    **
'*******************************************************
function fCloseNavigator

   Kontext
   Kontext "Navigator"
   try
    Navigator.Close
   catch
    Warnlog "Could not close Navigator!"
   endcatch

end function

'*******************************************************
'*  Open options and check 'Direct-Cursor' in options **
'*******************************************************
function fCheckDirectCursor

    ToolsOptions
    Call hToolsOptions("WRITER","FormattingAids")
    Zonen_Cursor.Check
    Kontext "ExtrasOptionenDlg"
    ExtrasOptionenDlg.OK

end function


'*********************************************************
'*  This function is evaluated multisection             **
'*  selectString is the selected string in the text     **
'*  There must be more than 2 selectStrings in the text **
'*********************************************************
function fMultiSelection(selectedString as String)

   Kontext
   EditSearchAndReplace
   Kontext "FindAndReplace"

   SearchFor.SetText selectedString
   SearchAll.Click
   Sleep 1

   FindAndReplace.Close

end function
