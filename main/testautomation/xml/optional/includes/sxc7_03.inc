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
'* short description : XML Calc Include File
'*
'\***********************************************************************************
   Dim Isliste(250) as string
   Dim OutputPath as string
   Dim iSecurityBefore as integer

sub sxc7_03
    printlog "------------------- sxc_03.inc ---------------------"

    call tchart_export
    call tconditional_formatting
        iSecurityBefore = ""
        iSecurityBefore = hSetMacroSecurity(1)
    call tcontrols01
        call hSetMacroSecurity(iSecurityBefore)        
    call tdatabase_ranges
    call tfilter_and_subtotals1
    call tfilter_and_subtotals4
    call tmatrixformula_and_notes
    call tpassword3
end sub

'-------------------------------------------------------------------------

testcase tchart_export
    printlog "+- chart_export.sdc"
    if bDebugVersion = TRUE then
        warnlog "#i41970# Assertion in DEBUG version breaks automated testing. This testcase will be ignored."
        goto endsub
    end if
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\calc\so_binary\chart_export.sdc"))
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\calc\level1\chart_export.sxc") , "StarOffice XML (Calc)") = TRUE then
        '/// Closing the document also if there is a verification dialog.
        call hCloseDocument()
        sleep(3)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\calc\level1\chart_export.sxc") , gOfficePath & ConvertPath("user\work\xml\calc\level1\chart_export") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\chart_export\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\chart_export\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\chart_export\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\calc\level1\chart_export.sxc"))
            sleep(2)
            call hCloseDocument
            sleep(2)
        end if
    else
        warnlog "It was not possible to save the document as XML!"
    end if
endcase

'-------------------------------------------------------------------------

testcase tconditional_formatting
  printlog "+- conditional_formatting.sdc"

  call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\calc\so_binary\conditional_formatting.sdc"))
  if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\calc\level1\conditional_formatting.sxc") , "StarOffice XML (Calc)") = TRUE then
    '/// Closing the document also if there is a verification dialog.
    call hCloseDocument()
    sleep(3)
    UnpackStorage( gOfficePath & ConvertPath("user\work\xml\calc\level1\conditional_formatting.sxc") , gOfficePath & ConvertPath("user\work\xml\calc\level1\conditional_formatting") )
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\conditional_formatting\styles.xml")) = FALSE then
      warnlog "XML-file 'styles.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\conditional_formatting\meta.xml")) = FALSE then
      warnlog "XML-file 'meta.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\conditional_formatting\content.xml")) = FALSE then
      warnlog "XML-file 'content.xml' not well formed!"
     else
      call hFileOpen (gOfficePath & ConvertPath("user\work\xml\calc\level1\conditional_formatting.sxc"))
      sleep(2)
      call hCloseDocument
      sleep(2)
    end if
   else
    warnlog "It was not possible to save the document as XML!"
  end if
endcase

'-------------------------------------------------------------------------

testcase tcontrols01
    Dim cWhereCalled as string    
    
    printlog "+- controls01.sdc"

    cWhereCalled = "xml::level1::inc::sxc7_03.inc::tcontrols01: "
    
    '/// Open Tools/Options -> OpenOffice.org/Security
    '/// Click on the macro security button
    '/// Set the <b>medium</b> security level
    try
        if iSecurityBefore = "" then
            QAErrorLog cWhereCalled & "Macro security level needs to be set before to 1 (medium)!"
            goto endsub
        end if
    catch
        'if variable iSecurityBefore is not initialized and causes into an error
        QAErrorLog cWhereCalled & "Macro security level needs to be set before to 1 (medium)!"
        goto endsub        
    endcatch
    
    call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\calc\so_binary\controls01.sdc"))
   
    Kontext "SecurityWarning"
    if SecurityWarning.Exists(1) then
        SecurityWarning.OK
    else
        warnlog "#i80769# Macros not being loaded. Exiting test case."
        'warnlog "No Macro Security Warning occoured while loading 'controls01.sdc'."
        call hCloseDocument
        goto endsub
    end if
    sleep(2)  
    if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\calc\level1\controls01.sxc") , "StarOffice XML (Calc)") = TRUE then
        '/// Closing the document also if there is a verification dialog.
        call hCloseDocument()
        sleep(3)
        UnpackStorage( gOfficePath & ConvertPath("user\work\xml\calc\level1\controls01.sxc") , gOfficePath & ConvertPath("user\work\xml\calc\level1\controls01") )
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\controls01\styles.xml")) = FALSE then
            warnlog "XML-file 'styles.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\controls01\meta.xml")) = FALSE then
            warnlog "XML-file 'meta.xml' not well formed!"
        end if
        if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\controls01\content.xml")) = FALSE then
            warnlog "XML-file 'content.xml' not well formed!"
        else
            call hFileOpen (gOfficePath & ConvertPath("user\work\xml\calc\level1\controls01.sxc"))
            '/// Accept the security warning and enable executing the macros.
            Kontext "SecurityWarning"
            if SecurityWarning.Exists(1) then
                SecurityWarning.OK
            else
                warnlog "Macro will not be loaded due to bug #i80769#"
                'warnlog "No Macro Security Warning occoured while loading 'controls01.sxc'."
            end if
            sleep(2)
            call hCloseDocument
            sleep(2)
        end if
    else
        warnlog "It was not possible to save the document as XML!"
    end if        
endcase

'-------------------------------------------------------------------------

testcase tdatabase_ranges
  printlog "+- database_ranges.sdc"

  call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\calc\so_binary\database_ranges.sdc"))
  if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\calc\level1\database_ranges.sxc") , "StarOffice XML (Calc)") = TRUE then
    '/// Closing the document also if there is a verification dialog.
    call hCloseDocument()
    sleep(3)
    UnpackStorage( gOfficePath & ConvertPath("user\work\xml\calc\level1\database_ranges.sxc") , gOfficePath & ConvertPath("user\work\xml\calc\level1\database_ranges") )
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\database_ranges\styles.xml")) = FALSE then
      warnlog "XML-file 'styles.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\database_ranges\meta.xml")) = FALSE then
      warnlog "XML-file 'meta.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\database_ranges\content.xml")) = FALSE then
      warnlog "XML-file 'content.xml' not well formed!"
     else
      call hFileOpen (gOfficePath & ConvertPath("user\work\xml\calc\level1\database_ranges.sxc"))
      sleep(2)
      call hCloseDocument
      sleep(2)
    end if
   else
    warnlog "It was not possible to save the document as XML!"
  end if
endcase

'-------------------------------------------------------------------------

testcase tfilter_and_subtotals1
  printlog "+- filter_and_subtotals1"

  call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\calc\so_binary\filter_and_subtotals1.sdc"))
  if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals1.sxc") , "StarOffice XML (Calc)") = TRUE then
    '/// Closing the document also if there is a verification dialog.
    call hCloseDocument()
    sleep(3)
    UnpackStorage( gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals1.sxc") , gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals1") )
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals1\styles.xml")) = FALSE then
      warnlog "XML-file 'styles.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals1\meta.xml")) = FALSE then
      warnlog "XML-file 'meta.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals1\content.xml")) = FALSE then
      warnlog "XML-file 'content.xml' not well formed!"
     else
      call hFileOpen (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals1.sxc"))
      sleep(2)
      call hCloseDocument
      sleep(2)
    end if
   else
    warnlog "It was not possible to save the document as XML!"
  end if
endcase

'-------------------------------------------------------------------------

testcase tfilter_and_subtotals4
  printlog "+- filter_and_subtotals4.sdc"

  call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\calc\so_binary\filter_and_subtotals4.sdc"))
  if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals4.sxc") , "StarOffice XML (Calc)") = TRUE then
    '/// Closing the document also if there is a verification dialog.
    call hCloseDocument()
    sleep(3)
    UnpackStorage( gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals4.sxc") , gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals4") )
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals4\styles.xml")) = FALSE then
      warnlog "XML-file 'styles.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals4\meta.xml")) = FALSE then
      warnlog "XML-file 'meta.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals4\content.xml")) = FALSE then
      warnlog "XML-file 'content.xml' not well formed!"
     else
      call hFileOpen (gOfficePath & ConvertPath("user\work\xml\calc\level1\filter_and_subtotals4.sxc"))
      sleep(2)
      call hCloseDocument
      sleep(2)
    end if
   else
    warnlog "It was not possible to save the document as XML!"
  end if
endcase

'-------------------------------------------------------------------------

testcase tmatrixformula_and_notes
  printlog "+- matrixformula_and_notes.sdc"

  call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\calc\so_binary\matrixformula_and_notes.sdc"))
  if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\calc\level1\matrixformula_and_notes.sxc") , "StarOffice XML (Calc)") = TRUE then
    '/// Closing the document also if there is a verification dialog.
    call hCloseDocument()
    sleep(3)     
    UnpackStorage( gOfficePath & ConvertPath("user\work\xml\calc\level1\matrixformula_and_notes.sxc") , gOfficePath & ConvertPath("user\work\xml\calc\level1\matrixformula_and_notes") )
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\matrixformula_and_notes\styles.xml")) = FALSE then
      warnlog "XML-file 'styles.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\matrixformula_and_notes\meta.xml")) = FALSE then
      warnlog "XML-file 'meta.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\matrixformula_and_notes\content.xml")) = FALSE then
      warnlog "XML-file 'content.xml' not well formed!"
     else
      call hFileOpen (gOfficePath & ConvertPath("user\work\xml\calc\level1\matrixformula_and_notes.sxc"))
      sleep(2)
      call hCloseDocument
      sleep(2)
    end if
   else
    warnlog "It was not possible to save the document as XML!"
  end if
endcase

'-------------------------------------------------------------------------

testcase tpassword3
  printlog "+- password3.sdc"

  call hFileOpen (gTesttoolPath & ConvertPath("xml\optional\input\calc\so_binary\password3.sdc"))
  if hFileSaveAsWithFilterKill (gOfficePath & ConvertPath("user\work\xml\calc\level1\password3.sxc") , "StarOffice XML (Calc)") = TRUE then
    '/// Closing the document also if there is a verification dialog.
    call hCloseDocument()
    sleep(3)
    UnpackStorage( gOfficePath & ConvertPath("user\work\xml\calc\level1\password3.sxc") , gOfficePath & ConvertPath("user\work\xml\calc\level1\password3") )
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\password3\styles.xml")) = FALSE then
      warnlog "XML-file 'styles.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\password3\meta.xml")) = FALSE then
      warnlog "XML-file 'meta.xml' not well formed!"
    end if
    if XMLWellformed (gOfficePath & ConvertPath("user\work\xml\calc\level1\password3\content.xml")) = FALSE then
      warnlog "XML-file 'content.xml' not well formed!"
     else
      call hFileOpen (gOfficePath & ConvertPath("user\work\xml\calc\level1\password3.sxc"))
      sleep(2)
      call hCloseDocument
      sleep(2)
    end if
   else
    warnlog "It was not possible to save the document as XML!"
  end if
endcase

