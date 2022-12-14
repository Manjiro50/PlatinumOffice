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
'* short description : Writer Table test
'*
'\***********************************************************************

sub w_204b_
   Call wSplittingTableCellsIntoEqualProportions
end sub


testcase wSplittingTableCellsIntoEqualProportions
   Dim i as integer 
   Dim DaRowHeight as string
   Dim SetRowHeight as boolean
   
   SetRowHeight = True
   printlog "Based on feature ID: 103485"
   printlog " Open a new writer document"
   Call hNewDocument
   printlog "Insert a table with 4 rows and 4 lines"
   Call TBOhTabelleEinfuegen("SplittingTable", 0, 1, 0, 1, "4", "4")
   printlog "Select the table ( Strg + A )"
   Call wTypeKeys ( "<Mod1 A>" )
   printlog "Format / Row / Height"
   Kontext "ZellenHoehe"
   TableAutoFitSetRowHeight
   printlog "In upcoming dialog (Row Height) set height to 1,2cm and check 'Fit to size'"
   if iSystemSprache = 01 or iSystemSprache = 48 or iSystemSprache = 07 then
      Hoehe.Settext "1.20"
   else
      Hoehe.Settext "1,20"
   end if
   Dynamisch.Check
   DaRowHeight = Hoehe.Gettext
   printlog "Close 'Row Height' with 'OK'"
   ZellenHoehe.Ok
   printlog "Point cursor to first cell in first row ( Strg + Home )"
   Call wTypeKeys ( "<Mod1 Home>" )
   For i = 1 to 4
      if wCheckRowHeight( DaRowHeight ) = False then SetRowHeight = False
      Call wTypeKeys ( "<Down>" )
   next i
   if SetRowHeight = True then
      Call wTypeKeys ( "<Up>", 4 )
      printlog "Select 1st and 2nd column"
      Call wTypeKeys ( "<Shift Down>", 3 )
      Call wTypeKeys ( "<Shift Right>" )
      printlog "Format / Cell / Merge to merge all cells"
      TableMergeCells
      printlog "Now split previous merged cell into 4 pieces ( horizontally )"
      printlog "Format / Cell / Split"
      TableSplitCell
      Kontext "ZellenTeilen"
      printlog "In 'Split Cells' Dialog set 'Split cell into' to 4"
      Anzahl.Settext "4"
      printlog "Check 'Horizontally' and 'Into equal proportions'"
      Horizontal.Check
      GleichmaessigTeilen.Check
      printlog "Close dialog with 'OK'"
      ZellenTeilen.Ok
      printlog "Now the cell has to be splitted into 4 rows of height 1,2cm"
      For i = 1 to 4
         if wCheckRowHeight( DaRowHeight ) = False then SetRowHeight = False
         Call wTypeKeys ( "<Down>" )
      next i
   else
      Warnlog "Error setting the row height !"
   end if

   Call hCloseDocument

endcase
