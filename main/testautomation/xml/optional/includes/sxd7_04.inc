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
'* short description : XML Draw Include File
'*
'\***********************************************************************************
   Dim Isliste(250) as string
   Dim OutputPath as string

sub sxd7_04

   printlog "------------------- sxd_04.inc ---------------------"

   Call ExitRestartTheOffice
   call t18139_18145
   call t18244
   call t18245
   call t18246_18250
   call t18464_18467
   call t18520_18524
   call t18526_18531
   call t18537_18544
   call t18629_18632
   call t18633

end sub

'-------------------------------------------------------------------------

testcase t18139_18145
    printlog "+- Draw: 18139-18145.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18139-18145.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18139-18145.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18139-18145.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18139-18145\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18139-18145\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18139-18145\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18139-18145\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18139-18145.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18244
    printlog "+- Draw: 18244.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18244.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18244.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18244.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18244\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18244\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18244\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18244\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18244.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18245
    printlog "+- Draw: 18245.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18245.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18245.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18245.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18245\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18245\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18245\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18245\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18245.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18246_18250
    printlog "+- Draw: 18246-18250.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18246-18250.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18246-18250.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18246-18250.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18246-18250\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18246-18250\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18246-18250\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18246-18250\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18246-18250.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18464_18467
    printlog "+- Draw: 18464-18467.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18464-18467.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18464-18467.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18464-18467.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18464-18467\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18464-18467\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18464-18467\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18464-18467\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18464-18467.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18520_18524
    printlog "+- Draw: 18520-18524.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18520-18524.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18520-18524.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18520-18524.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18520-18524\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18520-18524\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18520-18524\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18520-18524\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18520-18524.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18526_18531
    printlog "+- Draw: 18526-18531.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18526-18531.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18526-18531.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18526-18531.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18526-18531\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18526-18531\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18526-18531\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18526-18531\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18526-18531.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18537_18544
    printlog "+- Draw: 18537-18544.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18537-18544.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18537-18544.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18537-18544.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18537-18544\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18537-18544\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18537-18544\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18537-18544\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18537-18544.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18629_18632
    printlog "+- Draw: 18629-18632.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18629-18632.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18629-18632.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18629-18632.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18629-18632\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18629-18632\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18629-18632\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18629-18632\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18629-18632.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

testcase t18633
    printlog "+- Draw: 18633.sda"
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\graphics\so_bin\18633.sda"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\draw\level1\18633.sxd") , "StarOffice XML (Draw)") then
        call hCloseDocument
        sleep(2)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\draw\level1\18633.sxd") , gOfficePath & ConvertPath("user\work\xml\draw\level1\18633\") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18633\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18633\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\draw\level1\18633\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
         else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\draw\level1\18633.sxd")
            call hCloseDocument
        end if
    else
        call hCloseDocument
    end if
endcase

'-------------------------------------------------------------------------

