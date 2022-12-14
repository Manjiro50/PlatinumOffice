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
'*  short description : Hit update button for an extension
'*
'\******************************************************************************

testcase tExtensionUpdate

    'warnlog( "#i81543# Office crashes when Testtool executes .exists() method on some objects" )
    'goto endsub

    '///<h3>Hit update button for an extension</h3>
    '///<ul>
    
    const EXTENSION_NAME = "ShortLicense.oxt"
    
    dim cSampleExtension as string
        cSampleExtension = gTesttoolPath & "extensions\optional\input\simpleLicense\" 
        cSampleExtension = cSampleExtension & EXTENSION_NAME
        cSampleExtension = convertpath( cSampleExtension )
        
    dim iDocumentsBefore as integer
    dim iDocumentsAfter as integer
    
    printlog( "" )
    
    if ( dir( cSampleExtension ) <> "" ) then
        printlog( "Using extension: " & cSampleExtension )
    else
        warnlog( "Fatal: Sample extension could not be found: " & cSampleExtension )
        goto endsub
    endif
    printlog( "" )
    
    
    '///+<li>Create a new writer document</li>
    hNewDocument()
    
    '///+<li>get the number of open documents (should be 2)</li>
    iDocumentsBefore = getDocumentCount()
    
    '///+<li>Add sample extension &quot;ShortLicense&quot;</li>
    hExtensionAddGUI( cSampleExtension , "InstallForUser,AcceptLicense,Verbose" )
    
    '///+<li>Reopen the Extension Manager</li>
    printlog( "Reopen Extension Manager" )
    ToolsPackageManager
    
    '///+<li>Click the &quot;Update&quot;-button</li>
    printlog( "Click the update-button" )
    kontext "PackageManager"
    updates.click()
    
    '///+<li>verif y that the update-Dialog is present</li>
    kontext "ExtensionUpdate"
    if ( ExtensionUpdate.exists() ) then
        printlog( "Close update-dialog. Good." )
        ExtensionUpdate.close()
    else
        warnlog( "Extension update dialog is missing" )
    endif
    
    '///+<li>Close the Extension Manager"
    kontext "PackageManager"
    if ( PackageManager.exists() ) then
        printlog( "Close Extension Manager" )
        PackageManager.close()
    endif

    '///+<li>verify that we still have the correct number of documents open</li>
    iDocumentsAfter = getDocumentCount()
    if ( iDocumentsAfter <> iDocumentsBefore ) then
        warnlog( "Incorrect number of documents open. Please verify" )
    else
        printlog( "Correct number of documents are open. Good" )
    endif
    
    '///+<li>Close the second document</li>
    hCloseDocument()
    
    '///+<li>Remove the extension</li>
    hExtensionRemoveGUI( EXTENSION_NAME )
    
    '///</ul>

endcase

