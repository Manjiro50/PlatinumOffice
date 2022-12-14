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
'* short description : Chart resource test - section toolbars
'*
'************************************************************************
'*
' #1 tDrawBar
'*
'\************************************************************************

testcase tDrawBar

    printlog " Load simple chart document"
    if fLoadVerySimpleChartAndSaveLocal() > 0 then
        warnlog "Loading test document seems to have failed -> Check this out!"
        goto endsub
    endif
    printlog " Select chart using navigator"
    call fSelectFirstOLE
    printlog " Invoke Edit::Object::Edit to enter Inplace Mode"
    EditObjectEdit
    printlog " Verify that the drawbar is visible"
    Kontext "DrawBar"
   
    if Not DrawBar.Exists then 
        warnlog "Drawbar is not enabled"
        Kontext "DocumentCalc"
        DocumentCalc.TypeKeys "<Escape>"
        printlog " Close document"
        Call hCloseDocument
        goto endsub
'    	Call hToolbarSelect("Drawing", true)
    endif

    printlog " Check if all items on drawbar are available"
    if DrawBar.GetItemCount <> 16 then
    	warnlog "There are " & DrawBar.GetItemCount & " instead of 16 items on drawbar"
    endif
    printlog " Click on every button on the Drawingbar"
    Auswahl.click
    Linie.click
    LineArrowEnd.click
    Rechteck.click
    Ellipse.click
    Freihand.click
    Textobjekt.click
    Legende.click
    BasicShapes.click
    SymbolShapes.click
    BlockArrows.click
    Flowcharts.click
    Callouts.click
    Stars.click
    printlog " Open menubutton BasicShapes"
    BasicShapes.TearOff
    Kontext "BasicShapes"
    printlog " Check that there are 25 BasicShapes"
    if BasicShapes.GetItemCount <> 25 then
    	warnlog "There are " & BasicShapes.GetItemCount & " instead of 25 BasicShapes"
    endif
    BasicShapes.close
    Kontext "DrawBar"
    printlog " Open menubutton SymbolShapes"
    SymbolShapes.TearOff
    Kontext "SymbolShapes"
    printlog " Check that there are 20 SymbolShapes"
    if SymbolShapes.GetItemCount <> 20 then
    	warnlog "There are " & SymbolShapes.GetItemCount & " instead of 25 SymbolShapes"
    endif
    SymbolShapes.close
    Kontext "DrawBar"
    printlog " Open menubutton BlockArrows"
    BlockArrows.TearOff
    Kontext "ArrowShapes"
    printlog " Check that there are 30 ArrowShapes"
    if ArrowShapes.GetItemCount <> 30 then
    	warnlog "There are " & ArrowShapes.GetItemCount & " instead of 25 ArrowShapes"
    endif
    ArrowShapes.close
    Kontext "DrawBar"
    printlog " Open menubutton Flowcharts"
    Flowcharts.TearOff
    Kontext "Flowchart"
    printlog " Check that there are 32 FlowChartShapes"
    if Flowchart.GetItemCount <> 32 then
    	warnlog "There are " & Flowchart.GetItemCount & " instead of 32 Flowchartshapes"
    endif
    Flowchart.close
    Kontext "DrawBar"
    printlog " Open menubutton Callouts"
    Callouts.TearOff
    Kontext "Callouts"
    printlog " Check that there are 7 Callouts"
    if Callouts.GetItemCount <> 7 then
    	warnlog "There are " & Callouts.GetItemCount & " instead of 7 Callouts"
    endif
    Callouts.close
    Kontext "DrawBar"
    printlog " Open menubutton Stars"
    Stars.TearOff
    Kontext "Starshapes"
    printlog " Check that there are 13 StarShapes"
    if Starshapes.GetItemCount <> 13 then
    	warnlog "There are " & Starshapes.GetItemCount & " instead of 13 StarShapes"
    endif
    Starshapes.close
    printlog " Insert a shape to the chart by <STRG-RETURN>"
    Kontext "DrawBar"
    sleep (1)
    DrawBar.typekeys "<TAB>",TRUE
    DrawBar.typekeys "<TAB>",TRUE
    DrawBar.typekeys "<TAB>",TRUE
    DrawBar.typekeys "<TAB>",TRUE
    DrawBar.typekeys "<MOD1 RETURN>",TRUE
    printlog " Rename inserted shape"
    Kontext "DocumentChart"
    DocumentChart.OpenContextMenu
    sleep (1)
    hMenuSelectNr (6)
    sleep (1)
    Kontext "NameDlgObject"
    NameField.SetText "ChartShape1"
    NameDlgObject.OK
    printlog " Leave Chart"
    Kontext "DocumentCalc"
    DocumentCalc.TypeKeys "<Escape>"
    printlog "Select chart using navigator"
    call fSelectFirstOLE   
    printlog "Invoke Edit::Object::Edit to enter Inplace Mode"
    EditObjectEdit
    printlog " Check if shape is still there"
    Kontext "DocumentChart"
    DocumentChart.typekeys "<SHIFT TAB>",TRUE
    Sleep (1)
    Kontext "Toolbar"
    if ChartElementSelector.GetSelText <> "ChartShape1" then
    	warnlog "Something is wrong with the shape"
    endif
    printlog " Leave Chart"
    Kontext "DocumentCalc"
    DocumentCalc.TypeKeys "<Escape>"
    printlog " Close document"
    Call hCloseDocument
    
endcase

