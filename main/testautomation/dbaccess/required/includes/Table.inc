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
'* short description : test the Main Table Application Window
'*
'************************************************************************
'*
' #1 tMainMenuBar    
' #1 tSearch            
' #1 tSortAscending
' #1 tSortDescending                              
' #1 tAutoFilter
' #1 tDefaultFilter
' #1 tSortOrder
' #1 tRemoveFilter
' #1 tApplyFilter
' #1 tRefresh
' #1 tEdit
' #1 tCut
' #1 tCopy
' #1 tPaste
' #1 tUndo
' #1 tSave
'*
'\***********************************************************************************
sub Table

    printlog "------------------ Table.inc ---------------------"
    
    printlog "-------------------- main menu -------------------------"
    call tMainMenuBar
    
    printlog "--------------------- toolbar --------------------------"    
    call tSearch 
    call tSortAscending
    call tSortDescending
    call tAutoFilter
    call tDefaultFilter
    call tSortOrder
    call tRemoveFilter
    call tApplyFilter
    call tRefresh
    call tEdit
    call tCut
    call tCopy
    call tPaste
    call tUndo
    call tSave
     
end sub
'-------------------------------------------------------------------------
testcase tSearch

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the search button
    printlog "click on the search button"
    Kontext "Toolbar"
        RecSearch.Click
        sleep(1)
    '/// check if the search dialog appear
    printlog "check if the search dialog appear"
    Kontext "RecordSearch"
        if RecordSearch.Exists(3) then
            '/// close the search dialog
            printlog "close the search dialog"        
            CloseBtn.click
            sleep(2)
        else
            warnlog "The search dialog doesn't appear"            
        end if
        
    
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tSortAscending

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the search button
    printlog "click on the search button"
    Kontext "Toolbar"
        SortAscending.Click
        sleep(1)
        
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tSortDescending

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the search button
    printlog "click on the search button"
    Kontext "Toolbar"
        SortDescending.Click
        sleep(1)
    
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tAutoFilter
    
    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the auto filter button
    printlog "click on the auto filter button"
    Kontext "Toolbar"
        DBAutoFilter.Click
        sleep(1)
        
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tDefaultFilter

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the DefaultFilter button
    printlog "click on the DefaultFilter button"
    Kontext "Toolbar"
        DefaultFilter.Click
        sleep(1)
    '/// check if the default filter dialog appear
    printlog "check if the default filter dialog appear"
    Kontext "FilterDialog"
        if FilterDialog.Exists(2) then
            FilterDialog.Cancel    
        else
            warnlog "The filter dialog doesn't appear"
        end if
        
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tSortOrder

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the sort order button
    printlog "click on the sort order button"
    Kontext "Toolbar"
        SortOrder.Click
        sleep(1)
    '/// check if the sort order dialog appear
    printlog "check if the sort order dialog appear"        
    Kontext "SortOrder"    
        if SortOrder.Exists(2) then
            SortOrder.Cancel    
        else
            warnlog "The sort order dialog doesn't appear"
        end if
        
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tRemoveFilter

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the remove filter button
    printlog "click on the remove filter button"
    Kontext "Toolbar"
        DBAutoFilter.Click
        sleep(1)
        if RemoveFilter.isenabled then
            RemoveFilter.Click
        else
            warnlog "The remove filter icon isn't activ"
        end if
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tApplyFilter

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the applay filter button
    printlog "click on the apply filter button"
    Kontext "Toolbar"
        DBAutoFilter.Click
        sleep(1)
        if ApplyFilter.isenabled then
            ApplyFilter.Click
        else
            warnlog "The apply filter icon isn't activ"
        end if
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tRefresh

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the applay filter button
    printlog "click on the apply filter button"
    Kontext "Toolbar"
        Refresh.Click
        sleep(1)        
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tEdit

    '/// open a new table
    printlog "open a new table"
    initTable
    sleep(1)    
    '/// click on the applay filter button
    printlog "click on the apply filter button"
    Kontext "Toolbar"
        DBEditDoc.Click
        sleep(1)        
    '/// close the table and the database
    printlog "close the table and the database"    
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tSave

    '/// open a new table
    printlog "open a new table"
    initTable    
    sleep(1)
    '/// change a record
    printlog "change a record"
    Kontext "TableView"
        TableView.TypeKeys "hello" , true
    sleep(1)
    '/// check if the save button is active
    '/// but do not click on it
    printlog "check if the save button is active"
    printlog "but do not click on it"
    Kontext "Toolbar"
        if not RecSave.isEnabled then
            warnlog "the save button is not enabled."
        endif
        sleep(1)
    call fCloseTableView
    call fCloseDatabase
    
endcase
'-------------------------------------------------------------------------
testcase tCut

    '/// open a table
    printlog "open a table"
    initTable
    sleep(1)
    
    '/// click on the cut button
    printlog "click on the cut button"
    Kontext "Toolbar"
        Cut.Click
        sleep(1)
        
    '/// check if the text is in the clipboard
    printlog "check if the text is in the clipboard"                
    if getClipboard <> "GUR00" then
        warnlog "The Cut button doesn't work"
    end if        

    '/// check if the cut icon is disabled
    Kontext "Toolbar"
        if Cut.isEnabled then
            warnlog "The CUT icon is enabled, but I have nothing selected"
        endif
        sleep(1)
        
    '/// close the table and the database
    printlog "close the table and the database"
    call fCloseTableView
    call fCloseDatabase   
        
endcase
'-------------------------------------------------------------------------
testcase tCopy
    
    '/// open a table
    printlog "open a table"
    initTable
    sleep(1)
    
    '/// click on the copy button
    printlog "click on the copy button"
    Kontext "Toolbar"
        Copy.Click
        sleep(1)
        
    '/// check if the text is in the clipboard
    printlog "check if the text is in the clipboard"                
    if getClipboard <> "GUR00" then
        warnlog "The Cut button doesn't work"
    end if        
    
    '/// close the table and the database
    printlog "close the table and the database"
    call fCloseTableView
    call fCloseDatabase   
       
        
endcase
'-------------------------------------------------------------------------
testcase tPaste

    '/// opene new table
    printlog "opene new table"    
    initTable

    '/// set a string to the clipboard
    printlog "set a string to the clipboard"
    setClipboard "word"
    
    '/// press the cursor left key
    printlog "press the cursor left key"
    Kontext "TableView"
        TableView.TypeKeys "<LEFT>" , true
        sleep(1)
    '/// paste the text from the clipbaord
    printlog "paste the text from the clipbaord"
    Kontext "Toolbar"
        Paste.Click
        sleep(1)
    '/// check if the text is pasted to the fieldname
    printlog "check if the text is pasted to the fieldname"    
    Kontext "TableView"
        TableView.TypeKeys "<HOME>" , true
        sleep(1)
        TableView.TypeKeys "<SHIFT END>" , true
        sleep(1)
    '/// click the copy icon
    printlog "click the copy icon"
    Kontext "Toolbar"
        Copy.Click
        sleep(1)        
        if getClipboard <> "wordGUR00" then
            warnlog "the paste button doesn't work"
        end if
    '/// close the table design and the database
    printlog "close the table design and the database"    
    call fCloseTableView
    call fCloseDatabase     
    
endcase
'-------------------------------------------------------------------------
testcase tUndo

    '/// open a table
    printlog "open a table"
    initTable
    
    '/// set a string to the clipboard
    printlog "set a string to the clipboard"
    setClipboard "word"
          
    '/// press the cursor left key
    printlog "press the cursor left key"
    Kontext "TableView"
        TableView.TypeKeys "<LEFT>" , true
        sleep(1)
    '/// paste the text from the clipbaord
    printlog "paste the text from the clipbaord"
    Kontext "Toolbar"
        Paste.Click
        sleep(1)
    '/// check if the text is pasted to the fieldname
    printlog "check if the text is pasted to the fieldname"    
    Kontext "TableView"
        TableView.TypeKeys "<HOME>" , true
        sleep(1)
        TableView.TypeKeys "<SHIFT END>" , true
        sleep(1)
    '/// click the copy icon
    printlog "click the copy icon"
    Kontext "Toolbar"
        Copy.Click
        sleep(1)        
        if getClipboard <> "wordGUR00" then
            warnlog "the paste button doesn't work"
        end if
    
    
    '/// click the undo icon
    printlog "click the undo icon"
    Kontext "Toolbar"
        RecUndo.Click
        sleep(1)
    
    '/// click the copy icon
    Kontext "Toolbar"
        Copy.Click
        sleep(1)        
        if getClipboard <> "GUR00" then
            warnlog "the undo button doesn't work"
        end if
    
    '/// close the table design and the database
    printlog "close the table design and the database"    
    call fCloseTableView
    call fCloseDatabase   
    
endcase
'-------------------------------------------------------------------------
'-------------------------------------------------------------------------
testcase tMainMenuBar

    dim iCount as integer ' the numbers of the items in the menu.    
    
    call initTable
    
    Kontext "TableView"
        TableView.UseMenu
           
        '/// check if there are between 8 and 12 items in the file menu.
        printlog "check if there are between 8 and 12 items in the file menu."
        '/// + there different count related to the file pick list.                
        printlog "+ there different count related to the file pick list."        
        hMenuSelectNr(1) ' the file menu        
        iCount = getMenuItemCount()        
        if ( lcase( gPlatform ) = "osx" ) then
            if ( iCount <> 7 ) then
                warnlog( "File menu: 8 items expected, found " & iCount ) 
            endif
        else
            if (iCount <> 8 ) then
               warnlog "There should between 8 and 12 items in the file menu but there are " + iCount + " items."
            end if
        endif
        
        '/// check if there are 12 items in the FILE/NEW menu.
        printlog "check if there are 12 items in the FILE/NEW menu."
        printlog "check the FILE/NEW"
        hMenuSelectNr(1) ' FILE/NEW menu        
        iCount = hMenuItemGetCount()        
        if (iCount <> 12) then
            warnlog "There should 12 items in the FILE/NEW menu but there are " + iCount + " items."
        end if        
        call hMenuClose() ' close the FILE menu
        
        '/// check the FILE/AUTOPILOTS
        printlog "check the FILE/AUTOPILOTS"
        TableView.UseMenu        
        hMenuSelectNr(1) ' the file menu
        hMenuSelectNr(3) ' the autopilots menu        
        iCount = hMenuItemGetCount()
        if (iCount <> 8) then
            warnlog "There should 8 items in the FILE/AUTOPILOTS menu but there are " + iCount + " items."
        endif
        call hMenuClose()
        
        '/// check if there are 8 items in the edit menu.
        printlog "check if there are 8 items in the edit menu."
        TableView.UseMenu 
        hMenuSelectNr(2)        
        iCount = hMenuItemGetCount()
        if (iCount <> 8) then
            warnlog "There should 8 items in the edit menu but there are " + iCount + " items."
        end if
        call hMenuClose()
        
        '/// check if there are 2 items in the view menu.
        printlog "check if there are 2 items in the view menu."
        TableView.UseMenu 
        hMenuSelectNr(3)        
        iCount = hMenuItemGetCount()
        if (iCount <> 2) then
            warnlog "There should 2 items in the view menu but there are " + iCount + " items."
        end if
        call hMenuClose()

        '/// check if there are 4 items in the tools menu.
        printlog "check if there are 4 items in the tools menu."        
        TableView.UseMenu 
        hMenuSelectNr(5)        
        iCount = hMenuItemGetCount()
        if ( lcase( gPlatform ) = "osx" ) then
            if ( iCount <> 3 ) then
                warnlog( "Tools menu: 3 items expected, found " & iCount )
            endif
        else
            if (iCount <> 4) then
                warnlog "There should 4 items in the tools menu but there are " + iCount + " items."
            end if
        endif
        call hMenuClose()
        
        '/// check if there are 4 items in the TOOLS/MACRO menu.
        printlog "check if there are 4 items in the TOOLS/MACRO menu."        
        TableView.UseMenu 
        hMenuSelectNr(5)
        hMenuSelectNr(1)        
        iCount = hMenuItemGetCount()
        if (iCount <> 4) then
            warnlog "There should 4 items in the TOOLS/MACRO menu but there are " + iCount + " items."
        end if
        call hMenuClose()
        
        call fCloseTableView
        
        call fCloseDatabase
        
endcase
'-------------------------------------------------------------------------
'-------------------------------------------------------------------------
'-------------------------------------------------------------------------
function getMenuItemCount as Integer
'use this function becasue this doesn't count the pick list
    Dim i as Integer
    Dim j as Integer
    Dim Ende as Integer
    Dim nID as Integer
    Sleep 2
    j=0
    for i=1 to MenuGetItemCount
        if NOT MenuIsSeperator ( i ) then            
            dim s as String 
            s = Mid(MenuGetItemText( MenuGetItemID(i)),3,1)
            'printlog "s = " + s
            'printlog "MenuGetItemText( MenuGetItemID(i)) = " + MenuGetItemText( MenuGetItemID(i))
            if s <> ":" then             
                j=j+1
            endif
        endif
    next i
    getMenuItemCount = j
end function
'-------------------------------------------------------------------------
sub initTable

    
    hFileOpen( gOfficePath & "user/database/biblio.odb" )    
    
    Kontext "DATABASE"
    
    Database.MouseDown(50,50)
    Database.MouseUp(50,50)
    
    sleep(1)
    
    ViewTables
    
    Kontext "ContainerView"
    TableTree.select 1
    
    OpenTable
    
    sleep(2)
    
end sub    
