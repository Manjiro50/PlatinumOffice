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
'*  short description : Access document properties
'*
'\******************************************************************************

testcase tFiledlgDocumentProperties()


    dim cFileName as string
        cFileName = "DigitalSignature" & hGetSuffix( "current" )
        
    dim cFilePath as string
        cFilePath = gTesttoolPath & "framework\optional\input\security"
        cFilePath = convertpath( cFilePath )
        
    dim cFileURL as string : cFileURL = cFilePath & gPathSigne & cFileName
        
    dim iFileSize as long
    dim cFileSize as string
    dim iFileSizeInfo as long
    dim cSignatureCreator as string
    
    dim cTestExpression as string
    
    dim cSelectAll as string
    dim cCopy as string

    dim brc as boolean
        
    printlog( "Using filename: " & cFileName )
    printlog( "Using filepath: " & cFilePath )
    
    if ( FileExists( cFileURL ) ) then
    	iFileSize = FileLen( cFileURL )
        printlog( "Testfile size is: " & iFileSize & " Bytes" )
    else
    	warnlog( "The workfile does not exist. aborting test" )
    	goto endsub
    endif
    
    hFileOpen( cFileURL )
    
    FileProperties
    
    brc = hDocumentInfoSelectTab( "General" )
    if ( not brc ) then
        warnlog( "Unable to switch to the requested tabpage, trying to recover" )
        kontext "TabDokument"
        TabDokument.cancel()
        hDestroyDocument()
    endif
        
    cTestExpression = hGetStringFromStaticTextField( FileLocationInfo )
    if ( cTestExpression = cFilePath ) then
    	printlog( "Path is correct" )
    else
        warnlog( "The path string is incorrect: " & cTestExpression )
    endif

    kontext "TabDokument"
    cFileSize = hGetStringFromStaticTextField( FileSizeInfo )
    iFileSizeInfo =  hConvertStringToLong( cFileSize )
    if ( iFileSize <> iFileSizeInfo ) then	
        warnlog( "Filesize does not match, please check" )
        printlog( "Found...: " & iFileSizeInfo )
        printlog( "Expected: " & iFileSize    )
    else
        printlog( "Filesize is correct" )
    endif
    
    kontext "TabDokument"
    TabDokument.cancel()
    
    hDestroyDocument()
    

endcase

'*******************************************************************************

function hDocumentInfoSelectTab( cTabPage as string ) as boolean


    '///<h3>Switch between the tabpages in the document info dialog</h3>
    '///<i>The declaration of the document info dialog is not complete which
    '///+ enforces special treatment</i><br><br>

    '///<u>Parameter(s):</u><br>
    '///<ol>

    '///+<li>The name of the tabpage to be activated (String)</li>
    '///<ul>
    '///+<li>&quot;General&quot;</li>
    '///+<li>&quot;Description&quot;</li>
    '///+<li>&quot;User&quot;</li>
    '///+<li>&quot;Internet&quot;</li>
    '///+<li>&quot;Statistics&quot;</li>
    '///+<li>The string is case insensitive</li>

    '///</ul>

    '///</ol>


    '///<u>Returns:</u><br>
    '///<ol>
    '///+<li>Errorcondition (Boolean)</li>
    '///<ul>
    '///+<li>TRUE if tabpage is known and switching worked</li>
    '///+<li>FALSE on icorrect input parameter</li>
    '///+<li>FALSE on any other error</li>
    '///</ul>
    '///</ol>

    const CFN = "hDocumentInfoSelectTab::"
    printlog( CFN & "Enter with option (tabpage): " & cTabPage )
    dim brc as boolean 'a multi purpose boolean returnvalue
        brc = true

    '///<u>Description:</u>
    '///<ul>
    '///+<li>Kontext to the dialog</li>
    Kontext

    '///+<li>Select the page to switch to, context to the new page</li>
    select case ( ucase( cTabPage ) )
    case "GENERAL"     : active.setPage TabDokument     : kontext "TabDokument"
    case "DESCRIPTION" : active.setPage TabBeschreibung : kontext "TabBeschreibung"
    case "USER"        : warnlog( "#i95523# - Cannot access controls on Custom page" )
                         brc = false
                        'active.setPage TabBenutzer     : kontext "TabBenutzer"
    case "INTERNET"    : active.setPage TabInternet     : kontext "TabInternet"
    case "STATISTICS"  : active.setPage TabStatistik    : kontext "TabStatistik"
    case default       : brc = false
    end select

    '///</ul>

    printlog( CFN & "Exit with result: " & brc )
    hDocumentInfoSelectTab() = brc

end function


