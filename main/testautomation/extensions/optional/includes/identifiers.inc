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
'*  short description : Use unique identifiers instead of filenames for extensions
'*
'\******************************************************************************

testcase tExtensionIdentifiers()

    printlog( "Extension identifiers / reinstallation of extensions" )
    
    if ( gBuild <= 9183 ) then
        printlog( "Build does not support extension identifiers" )
        goto endsub
    endif
    
        
    dim cExtensionPath( 2 ) as string
    dim cCommonPath as string
    dim cExtensionCount( 3 ) as integer
    const EXTENSION_NAME = "identifier.oxt"
    dim cExtensionFlags as string
    
    
    ' paths to the extensions - the have identical names but different identifiers
    cCommonPath = gTesttoolPath & "extensions\optional\input\identifier\"
    cExtensionPath( 1 ) = convertpath( cCommonPath & "legacy\"   & EXTENSION_NAME )
    cExtensionPath( 2 ) = convertpath( cCommonPath & "explicit\" & EXTENSION_NAME )
    cExtensionCount( 0 ) = hGetExtensionCount()
    
    ' Install first extension
    cExtensionFlags = "InstallForUser"
    cExtensionCount( 1 ) = hExtensionAddGUI( cExtensionPath( 1 ), cExtensionFlags )
    if ( cExtensionCount( 1 ) = cExtensionCount( 0 ) + 1 ) then
        printlog( "Extension 1 was installed" )
    else
        warnlog( "Incorrect extension count: " & cExtensionCount( 1 ) )
    endif

    ' Install second extension
    cExtensionFlags = "InstallForUser"
    cExtensionCount( 2 ) = hExtensionAddGUI( cExtensionPath( 2 ), cExtensionFlags )
    if ( cExtensionCount( 2 ) = cExtensionCount( 1 ) + 1 ) then
        printlog( "Extension 2 was installed" )
    else
        warnlog( "Incorrect extension count: " & cExtensionCount( 2 ) )
    endif
    
    ' Install first extension again
    cExtensionFlags = "InstallForUser,AllowUpdate"
    cExtensionCount( 3 ) = hExtensionAddGUI( cExtensionPath( 1 ), cExtensionFlags )
    if ( cExtensionCount( 3 ) = cExtensionCount( 2 ) ) then
        printlog( "Extension 1 was installed, overwriting existing" )
    endif


    ' Install second extension again
    cExtensionFlags = "InstallForUser,AllowUpdate"
    cExtensionCount( 3 ) = hExtensionAddGUI( cExtensionPath( 2 ), cExtensionFlags )
    if ( cExtensionCount( 3 ) = cExtensionCount( 2 ) ) then
        printlog( "Extension 2 was installed, overwriting existing" )
    endif
    
    hExtensionRemoveGUI( EXTENSION_NAME )
    hExtensionRemoveGUI( EXTENSION_NAME )
    
    ' Install first extension
    cExtensionFlags = "InstallForUser"
    cExtensionCount( 1 ) = hExtensionAddGUI( cExtensionPath( 1 ), cExtensionFlags )
    if ( cExtensionCount( 1 ) = cExtensionCount( 0 ) + 1 ) then
        printlog( "Extension 1 was installed again" )
    else
        warnlog( "Extension 1 was not installed" )
    endif

    ' Install second extension
    cExtensionFlags = "InstallForUser"
    cExtensionCount( 2 ) = hExtensionAddGUI( cExtensionPath( 2 ), cExtensionFlags )
    if ( cExtensionCount( 2 ) = cExtensionCount( 1 ) + 1 ) then
        printlog( "Extension 2 was installed again" )
    else
        warnlog( "Extension 2 was not installed" )
    endif
    
    hExtensionRemoveGUI( EXTENSION_NAME )
    hExtensionRemoveGUI( EXTENSION_NAME )
    
    if ( hGetExtensionCount() <> cExtensionCount( 0 ) ) then
        warnlog( "For some reason we have an unexpected number of extensions listed" )
    else
        printlog( "Extensions were handled correctly" )
    endif
    
endcase
