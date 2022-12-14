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
'* short description : Chart2 functional tests
'*
'\************************************************************************

sub ch2_lvl1a

    Call tPlotOptions
    Call tChartShapes

end sub


testcase tPlotOptions

    Dim sOutputFile as string
    sOutputFile = convertpath(gOfficepath & "user\work\hiddenCells.ods")

    gApplication = "CALC"

    printlog "Load simple chart document"
    if fLoadVerySimpleChartAndSaveLocal() > 0 then
        warnlog "Loading test document seems to have failed -> Check this out!"
        goto endsub
    endif
    printlog "Select chart using navigator"
    if fSelectFirstOLE = -1 then
        warnlog "It was not possible to select the chart object!"
        Call hCloseDocument
        goto endsub
    endif

    printlog "Edit / Object / Edit"
    EditObjectEdit
      waitslot()
      printlog "Select DataSeries A by toolbar selectorbox"
    Kontext "DocumentChart"
    call fChartSelectElement (8)

    printlog "Invoke Format::ObjectProperties"
    Kontext "Toolbar"
    FormatSelection.Click

    printlog "Select tab page Options"
    Kontext
    Active.SetPage TabDataSeriesOptions
    Kontext "TabDataSeriesOptions"
    printlog "activate checkbox 'Include values from hidden cells'"
    try
        IncludeHiddenCells.Check
    catch
        Warnlog "checkbox hidden or disabled"
        Call hCloseDocument
        goto endsub
    endcatch

    printlog "Close and reopen data series dialog - checkbox should be still activated"
    TabDataSeriesOptions.Ok
    sleep (1)
    Kontext "DocumentChart"
    FormatSelection
    printlog "Select tab page Options"
    Kontext
    Active.SetPage TabDataSeriesOptions
    Kontext "TabDataSeriesOptions"
    if Not IncludeHiddenCells.IsChecked then
        Warnlog "After closing and reopening of Data-Series dialog the checkbox isn't checked anymore"
        TabDataSeriesOptions.Cancel
        Kontext "DocumentCalc"
        DocumentCalc.TypeKeys "<Escape>"
        call hCloseDocument
        goto endsub
    endif

    TabDataSeriesOptions.Ok

    printlog "save and reopen file - checkbox still must be checked"
    if NOT hFileSaveAsKill (sOutputFile) then
        warnlog "Saving test document failed -> Aborting"
        Kontext "DocumentCalc"
        DocumentCalc.TypeKeys "<Escape>"
        call hCloseDocument
        goto endsub
    endif
    Call hCloseDocument

    Call hFileOpen(sOutputFile)
    if fSelectFirstOLE = -1 then
        warnlog "It was not possible to select the chart object!"
        Call hCloseDocument
        goto endsub
    endif

    EditObjectEdit
        waitslot()
        printlog "Select DataSeries A by toolbar selectorbox"
    call fChartSelectElement (8)

    printlog "Invoke Format::ObjectProperties"
    Kontext "Toolbar"
    FormatSelection.Click
    Kontext
    Active.SetPage TabDataSeriesOptions
    Kontext "TabDataSeriesOptions"
    if Not IncludeHiddenCells.IsChecked then
        Warnlog "After closing and reopening of Data-Series dialog the checkbox isn't checked anymore"
        TabDataSeriesOptions.Cancel
        Kontext "DocumentCalc"
        DocumentCalc.TypeKeys "<Escape>"
        call hCloseDocument
        goto endsub
    endif

    '/// Close dialog with Cancel-button
    TabDataSeriesOptions.Cancel
    '/// Close document
    Kontext "DocumentCalc"
    DocumentCalc.TypeKeys "<Escape>"

    Call hCloseDocument
endcase

'
'-------------------------------------------------------------------------
'
testcase tChartShapes

    Dim sLocalFile as string
    Dim sLocalFileXLS as string
    Dim sFormatXLS as string
    sLocalFile = convertpath(gOfficepath & "user\work\chartshapes.ods")
    sLocalFileXLS = convertpath(gOfficepath & "user\work\chartshapes.xls")
    sFormatXLS = "MS Excel 97"

    gApplication = "CALC"

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

    printlog " Insert a shape to the chart by <STRG-RETURN>"
    Kontext "DocumentChart"
    DocumentChart.TypeKeys "<F6>",4
    Kontext "DrawBar"
    sleep (1)
    DrawBar.typekeys "<TAB>",TRUE
    DrawBar.typekeys "<TAB>",TRUE
    DrawBar.typekeys "<TAB>",TRUE
    DrawBar.typekeys "<TAB>",TRUE
    DrawBar.typekeys "<MOD1 RETURN>",TRUE
    printlog " Rename inserted shape"
    Kontext "DocumentChart"
    sleep (1)
    DocumentChart.OpenContextMenu
    sleep (1)
    hMenuSelectNr (6)
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
    DocumentChart.typekeys "<SHIFT TAB>"
    Sleep (1)
    Kontext "Toolbar"
    if ChartElementSelector.GetSelText <> "ChartShape1" then
        warnlog "Something is wrong with the shape"
    endif
    printlog " Leave Chart"
    Kontext "DocumentCalc"
    DocumentCalc.TypeKeys "<Escape>"
    printlog " Save document with the default calc filter"
    call hFileSaveAsKill ( sLocalFile )
    printlog " Save document to xls"
    if NOT hFileSaveAsWithFilterKill ( sLocalFileXLS , sFormatXLS ) then
        warnlog "Saving test document localy failed -> Aborting"
        call hCloseDocument
        goto endsub
    end if
    printlog " Close document"
    call hCloseDocument
    printlog " Open document"
    call hFileOpen ( sLocalFile )
    printlog "Select chart using navigator"
    call fSelectFirstOLE
    printlog "Invoke Edit::Object::Edit to enter Inplace Mode"
    EditObjectEdit
    printlog " Check if shape is still there"
    Kontext "DocumentChart"
    DocumentChart.typekeys "<SHIFT TAB>"
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
    call hFileOpen ( sLocalFileXLS )
    printlog "Select chart using navigator"
    call fSelectFirstOLE
    printlog "Invoke Edit::Object::Edit to enter Inplace Mode"
    EditObjectEdit
    printlog " Check if shape is still there"
    Kontext "DocumentChart"
    DocumentChart.typekeys "<SHIFT TAB>"
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
