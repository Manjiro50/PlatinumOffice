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
'* short description : check the internal file dialog ( extended tests )
'*
'\******************************************************************************

testcase tSaveLoadDelFiles()

    
    ' This test checks filenames that resemble Devices and files that contain
    ' the allowed ASCII chars between 32 and 255. The latter is tested by five
    ' random characters
    ' The test should work for all applications and on all languages/locales.
    
    dim cStrangeName as string
    dim iCounter ' iterator
    dim iRandom  ' random number. should end up to be a value between 32 and 255
    dim brc as boolean
    
    dim iCurrentDocType as integer ' increment
    
    for iCurrentDocType = 1 to 1
    
        printlog( "" )
        printlog( "Current Documenttype: " & hNumericDocType( iCurrentDocType ) )
        printlog( "Check if filenames that resemble devicenames are treated ok" )
        printlog( "" )
        
        printlog( "Open a new document" )
        
        brc = hSaveLoadDelSuccess( "COM0"  , true )
        brc = hSaveLoadDelSuccess( "COM10" , true )
        brc = hSaveLoadDelSuccess( "LPT0"  , true )
        brc = hSaveLoadDelSuccess( "LPT10" , true )
        
        ' This test randomizes through a number of characters, a full test of all
        ' possible ascii characters would simply take too long.
        printlog( "" )
        printlog( "Names with allowed ASCII-chars" )
        printlog( "" )
        
        call randomize()
        
        for iCounter = 1 to 3
            
            iRandom = int( 32 + ( 223 * rnd ) )
            printlog( "" )
            printlog( " * Using decimal char: " & iRandom )
            printlog( "" )
            
            
            ' Exclude some special characters that cannot work
            select case iRandom
                
            case  32 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  34 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  35 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  42 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  46 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  47 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  58 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  60 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  62 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  63 : printlog( " - skipping ASCII-Char: " & iRandom )
            case  92 : printlog( " - skipping ASCII-Char: " & iRandom )
            case 124 : printlog( " - skipping ASCII-Char: " & iRandom )
            case 126 : printlog( " - skipping ASCII-Char: " & iRandom )
                
            case else
                
                cStrangeName = hNameGen_append( iRandom )
                brc = hSaveLoadDelSuccess( cStrangeName , TRUE )
                
                cStrangeName = hNameGen_lead( iRandom )
                brc = hSaveLoadDelSuccess( cStrangeName , TRUE )
                
            end select
            
        next iCounter
        
        brc = hDestroyDocument()
        
    next iCurrentDocType

    
endcase


