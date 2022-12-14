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
'* short description :
'*
'*********************************************************************
' #1 tViewZoom
'\********************************************************************

testcase tViewZoom
 dim Zaehler as integer
 dim Position1 as integer
 dim Position2 as integer
 Dim Datei$
   Printlog "- view Zoom"

    if (gApplication = "IMPRESS") then 
        ExtensionString = "odp"
    else
        ExtensionString = "odg"
    end if

    Datei$ = ConvertPath (gOfficePath + "user\work\test." & ExtensionString)

    Printlog "- View-Zoom testing"
    printlog "to avoid the anoying overwrite warnlog :-)"
  if dir(Datei$) <> "" then app.Kill(Datei$)
  printlog "new document"
Call hNewDocument            
  ViewZoom
  Kontext "Massstab"
  Vergroesserung100.Check       
  Massstab.OK
  printlog "create a number of rectangles with different color properties"
   Kontext "SD_Farbleiste"
   sleep 1
    if SD_Farbleiste.Exists then
       Printlog "- Color toolbar will be disabled now"
       ViewToolbarsColorBar
    end if
   printlog "All rectangles are created with same dimensions but using different zoom settings"
   For Zaehler = 1 to 9
      Position1 = 5 * Zaehler - 3
      Position2 = 105 - 5 * Zaehler
      Call hRechteckErstellen (Position1, Position1, Position2, Position2)
      FormatArea
      kontext
      Active.SetPage TabFarben
      Kontext "TabFarben"
      Farbe.Select 5*Zaehler
      TabFarben.OK
       sleep 1
       gMouseClick 50,0
   Next Zaehler
   sleep 2
    printlog "save document"
    hFileSaveAs (Datei$)
  sleep 3
  printlog "changing zoom settings and checking functionality with controlling the color of the selected rectangle"
   for Zaehler = 1 to 6	          
      ViewZoom
      Kontext "Massstab"
      VergroesserungStufenlos.check
      Stufenlos.Settext "45"
      Massstab.OK
       sleep 2
       gMouseClick 50,1
      ViewZoom
      Kontext "Massstab"
      Select Case Zaehler
         Case 1: VergroesserungStufenlos.check
                 Stufenlos.Settext "40"
         Case 2: VergroesserungStufenlos.check
                 Stufenlos.Settext "50"
         Case 3: VergroesserungStufenlos.check
                 Stufenlos.Settext "75"
         Case 4: VergroesserungStufenlos.check
                 Stufenlos.Settext "100"
         Case 5: VergroesserungStufenlos.check
                 Stufenlos.Settext "150"
         Case 6: VergroesserungStufenlos.check
                 Stufenlos.Settext "200"
                 
      End Select
      Massstab.OK
       sleep 1
      Kontext "DocumentImpress"
      printlog "Mouseclick should hit a rectangle. Color tells us then if it was zoomed correctly."
       gMouseClick 15,15        
                                    
      FormatArea                    
       sleep 1
      Kontext
      Active.SetPage TabFarben
      Kontext "TabFarben"
      printlog "Color index ", Farbe.GetSelIndex
      TabFarben.Cancel
      sleep 1
   next Zaehler

  'GanzeSeite.push
  'Optimal.push
  'Seitenbreite.push
  sleep 2
  printlog "close document"
 Call hCloseDocument         
endcase
