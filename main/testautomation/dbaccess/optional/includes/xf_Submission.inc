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
'* short description : XForms submission Test
'*
'\***********************************************************************************

sub xf_Submission

   printlog "------------------ xf_Submission.inc ---------------------"
      
   call tDataNavigatorSubmission
   
end sub
'-------------------------------------------------------------------------
testcase tDataNavigatorSubmission    
    
    Dim sSubmitPath as string

    '/// open new XML Form
    printlog "open new XML Form"
    
    FileOpen "FileName", "private:factory/swriter?slot=21053" , "FrameName", "_default", "SynchronMode" ,True
        
    sleep(5)        
	
    call hToolbarSelect("FormDesignTools",true)

    sleep(1)
    
    '/// open the datanavigator
    printlog "open the datanavigator"
    Kontext "XFormsDataNavigator"
        if ( not XFormsDataNavigator.exists(2) ) then
            Kontext "FormDesignTools"
            XFormsDataNavigator.Click
        endif    
    
	sleep(1)
    
    '/// select the instance tabpage
    printlog "select the instance tabpage"
    
    Kontext "XFormsDataNavigator"        
        while ( XFormsDataNavigatorTabControl.getPageID() <> 12 )
            XFormsDataNavigatorTabControl.TypeKeys("<RIGHT>")
        wend
       
    ItemList.select 1
    
    '/// click the add element icon    
    printlog "click the add element icon"
    
    Kontext "XFormToolbar"
        AddElement.Click
    
    '/// insert element1 as name and click OK
    printlog "insert element1 as name and click OK"
    Kontext "XFormAddItemDLG"
        ElementName.setText "element1"
        XFormAddItemDLG.OK

    '/// select the submisson tabpage
    printlog "select the submisson tabpage"

    Kontext "XFormsDataNavigator"        
        while ( XFormsDataNavigatorTabControl.getPageID() <> 10 )
            XFormsDataNavigatorTabControl.TypeKeys("<RIGHT>")
        wend        
        
    '/// click the add submission icon
    printlog "click the add submission icon"
    
    Kontext "XFormToolbar"
        AddSubmission.Click

    '/// add a submission
    Kontext "XFormAddSubmission"
        SubmitName.setText("submission1")
        sSubmitPath = "file:///" + gOfficePath + "user/work/test.xml"
        SubmitAction.setText( hStringReplaceChar( sSubmitPath, "\", "/" ) )
        SubmitMethod.select 2            
            
    '/// close the add submission dialog
    printlog "close the add submission dialog"    
    Kontext "XFormAddSubmission"        
        XFormAddSubmission.OK
    
    '/// close the xform data navigator
    printlog "close the xform data navigator"
    
    Kontext "XFormsDataNavigator"
        XFormsDataNavigator.Close    
    
    '/// open the FormControl toolbar
    call hToolbarSelect("FormControls",true)

    '/// insert a control    
    Kontext "FormControls"
	    Pushbutton.Click
        
    call hDrawingWithSelection(50,20,60,30)

    sleep(1)

    '/// open the FormControl Properties Dialog
    printlog "open the FormControl Properties Dialog"
    Kontext "FormControls"
	    ControlProperties.Click
    
    '/// select the first submission
    printlog "select the first submission"
    Kontext "TabGeneralControl"
        ButtonType.select 2
        Submission.select 1
        TabGeneralControl.TypeKeys("<RETURN>", true)
        
    sleep(3)
    '/// save the document
    printlog "save the document"    
    call hFileSaveAsKill(gOfficePath + "user/work/test.odt")
    
    '/// close the document
    printlog "close the document"
    call hCloseDocument
    
    sleep(1)
    '/// open the document
    printlog "open the document"
    call hFileOpen(gOfficePath + "user/work/test.odt")

    '/// click on the button in the document
    printlog "click on the button in the document"
    Kontext "DocumentWriter"
        DocumentWriter.TypeKeys "<MOD1 F5>" , true
        DocumentWriter.TypeKeys "<RETURN>" , true
        
    '/// close the document
    printlog "close the document"
    call hCloseDocument
    
    sleep(1)

    Open gOfficePath + "user/work/test.xml" For Input As 1
    
    dim sLine as String
    
    Line Input #1, sLine
    if sLine <> "<?xml version=""1.0"" encoding=""UTF-8""?>" then
        warnlog "the first line in the xml document should <?xml version=""1.0"" encoding=""UTF-8""?> but it is " + sLine
    endif
    Line Input #1, sLine
    if sLine <> "<instanceData><element1/></instanceData>" then
        warnlog "the second line in the xml document should <instanceData><element1/></instanceData> but it is " + sLine
    endif
    
endcase
'-------------------------------------------------------------------------

