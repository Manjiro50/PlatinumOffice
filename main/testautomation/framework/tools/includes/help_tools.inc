'encoding UTF-8  Do not remove or change this line!
'**************************************************************
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
'**************************************************************
'*
'* short description : Replacements for routines in t_lists.inc adds some
'*
'\******************************************************************************

function hOpenHelp() as boolean

    printlog( "Open Help Browser" )

    HelpContents

    kontext "StarOfficeHelp"
    if ( StarOfficeHelp.exists( 5 ) ) then
        hOpenHelp() = TRUE
    else
        warnlog( "Unable to open help browser" )
        hOpenHelp() = FALSE
    endif


end function

'*******************************************************************************

function hCloseHelp() as boolean

    printlog( "Close Help Browser" )

    kontext "StarOfficeHelp"
    StarOfficeHelp.typeKeys( "<MOD1 F4>" )

    if ( StarOfficeHelp.notExists( 3 ) ) then
        hCloseHelp() = TRUE
    else
        warnlog( "Help browser could not be closed" )
        hCloseHelp() = FALSE
    endif

end function

'******************************************************************************

function hSelectHelpTab( cTab as string ) as boolean

    '///<h3>Select a tab on the help dialog by name</h3>
    '///<u>Input</u>:
    '///<ol>
    '///+<li>The tab to open (string)</li>
    '///<ul>
    '///+<li>&quot;content&quot; for the contents tab</li>
    '///+<li>&quot;index&quot; for the index tab</li>
    '///+<li>&quot;find&quot; for the find tab</li>
    '///+<li>&quot;bookmarks&quot; for the bookmarks tab</li>
    '///</ul>
    '///</ol>

    '///<u>Returns</u>:
    '///<ol>
    '///+<li>Errorcondition (boolean)</li>
    '///<ul>
    '///+<li>TRUE if the requested tabpage is open</li>
    '///+<li>FALSE if the requested tabpage did not open</li>
    '///</ul>
    '///</ol>

    '///<u>Description</u>:
    '///<ul>
    const CFN = "hSelectHelpTab::"

    dim brc as boolean     : brc = false
    dim cTabName as string : cTabName = lcase( cTab )

    kontext "StarOfficeHelp"

    printlog( CFN & "Enter" )

    '///+<li>Select the requested Tabpage, verify that it is open</li>
    select case cTabName
    case "content"       : TabControl.setPage( ContentPage )
                           if ( SearchContent.isVisible() ) then
                               call DialogTest( ContentPage )
                               brc = true
                           endif
    case "index"         : TabControl.setPage( IndexPage )
                           if ( SearchIndex.isVisible() ) then
                               call DialogTest( IndexPage )
                               brc = true
                           endif
    case "find"          : TabControl.setPage( FindPage )
                           if ( SearchFind.isVisible() ) then
                               call DialogTest( FindPage )
                               brc = true
                           endif
    case "bookmarks"     : TabControl.setPage( BookmarksPage )
                           if ( Bookmarks.isVisible() ) then
                               call DialogTest( BookmarksPage )
                               brc = true
                           endif
    case else
        printlog( CFN & "Invalid parameter passed to function: " & cTab )
        printlog( CFN & "Valid are: content, index, find, bookmarks" )
        brc = false
    end select

    '///+<li>Print a comment to the log</li>
    if ( brc ) then
        printlog( CFN & "Exit: Selected Tabpage: " & cTab )
    endif

    '///+<li>Return TRUE or FALSE</li>
    hSelectHelpTab() = brc

    '///</ul>
end function

'*******************************************************************************

function hUseBookmarksContextMenu( cAction as string ) as boolean

    '///<h3>handle the bookmarks context menu in Help Browser</h3>
    '///<u>Input</u>:
    '///<ol>
    '///+<li>The context item to execute (string)</li>
    '///<ul>
    '///+<li>&quot;show&quot;</li>
    '///+<li>&quot;rename&quot;</li>
    '///+<li>&quot;delete&quot;</li>
    '///</ul>
    '///</ol>

    '///<u>Returns</u>:
    '///<ol>
    '///+<li>Errorcondition (boolean)</li>
    '///<ul>
    '///+<li>TRUE on success</li>
    '///+<li>FALSE on any other error</li>
    '///</ul>
    '///</ol>

    '///<u>Description</u>:
    '///<ul>
    const CFN = "hUseBookmarksContextMenu::"
    dim cSelection as string
    dim iActionPos as integer

    printlog( CFN & "Enter" )

    '///+<li>Verify that we are on the Bookmarks Page</li>
    Kontext "BookmarksPage"
    if ( not BookmarksPage.exists() ) then
        printlog( CFN & "BookmarksPage is not open" )
        hUseBookmarksContextMenu() = false
        exit function
    endif

    '///+<li>Find the index of the requested entry</li>
    cSelection = lcase( cAction )
    select case cSelection
    case "show"       : iActionPos = 1
    case "rename"     : iActionPos = 2
    case "delete"     : iActionPos = 3
    case else         : iActionPos = 0
    end select

    '///+<li>If action is unsuported, return false and exit the function</li>
    if ( iActionPos = 0 ) then
        printlog( CFN & "Invalid action passed to function" )
        hUseBookmarksContextMenu() = false
        exit function
    endif

    '///+<li>Open the context menu and select the requested index</li>
    kontext "Bookmarks"
    Bookmarks.openContextMenu()
    printlog( CFN & "Exit: Opening item: " & MenuGetItemText( iActionPos ) )
    MenuSelect( iActionPos )

    '///+<li>Return TRUE if all went well so far</li>
    hUseBookmarksContextMenu() = true

    '///</ul>

end function

'*******************************************************************************

function hHelpGetAboutItemCount() as integer

    printlog( "Get the number of applications listed in the help listbox (should be 8)" )
    const ABOUT_ITEMS = 8

    dim itemcount as integer

    hOpenHelp()
    hSelectHelpTab( "index" )

    Kontext "IndexPage"
    itemcount = HelpAbout.getItemCount()

    if ( itemcount <> ABOUT_ITEMS ) then
        warnlog( "Number of applications is incorrect" )
        printlog( "Found...: " & itemcount )
        printlog( "Expected: " & ABOUT_ITEMS
    endif

    hCloseHelp()

    hHelpGetAboutItemCount() = itemcount

end function

