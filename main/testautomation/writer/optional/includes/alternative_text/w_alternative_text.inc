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
'* short description : Test Alternative Text for objects in writer
'*
'\************************************************************************

sub w_alternative_text

	Call tPictureAlternativeText
	Call tFrameAlternativeText
	Call tOLEAlternativeText	

end sub

'-------------------------------------------------------------------------

testcase tPictureAlternativeText

	printlog "- New writer document"	
	Call hNewDocument
    
	printlog "- Insert a picture"	
	InsertGraphicsFromFile
	Kontext "GrafikEinfuegenDlg"
	Dateiname.Settext ConvertPath(gTesttoolpath + "writer\optional\input\alternative_text\jolink.jpg")
	Sleep 1
	Oeffnen.Click
	Sleep 2

    printlog "- Context menu on the picture, choose 'Description'"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems picture is not selected => Description Object could not be opened"
	endcatch	
	
    printlog "- Type 'TitleText' in the Title field"
	Kontext "DescriptionObject"
	DescriptionTitle.Settext "TitleText"	
	
    printlog "- Type 'This Is A Description'"
	DescriptionText.Settext "This Is A Description"	
	
    printlog "- Close the dialog"
	DescriptionObject.Ok

    printlog "- Context menu on the picture, choose 'Description'"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems picture is not selected => Description Object could not be opened"
	endcatch	

	printlog "Check that the Title and Description fields have been saved correctly"
	Kontext "DescriptionObject"
	if DescriptionTitle.Gettext <> "TitleText" then
		Warnlog "Object title gets lost. Not 'TitleText' but " & DescriptionTitle.Gettext 	
	endif	
	if DescriptionText.Gettext <> "This Is A Description" then
		warnlog "Object description gets lost. Not 'This Is A Description' but " & DescriptionText.Gettext 	
	endif
	DescriptionObject.Cancel	
	
    printlog "- Format - Picture"
	FormatGraphics
	
	printlog "The 'Alternative' field must be filled with the content of the Title field (='TitleText')"
	Kontext
	Active.Setpage TabZusaetze
	Kontext "TabZusaetze"
	if Alternativtext.Gettext <> "TitleText" then
		Warnlog "Alternatice text in pictures options is not set"
	endif
	TabZusaetze.Cancel
	
    printlog "- Save the document"
	Call hFileSaveAsKill ( gOfficePath + "user\work\tPictureAlternativeText.odt" )
	Call hCloseDocument
	
    printlog "- Reload"
	hFileOpen(  gOfficePath + "user\work\tPictureAlternativeText.odt" )		
	' select graphic
	Call wTypeKeys ("<SHIFT F4>")
	
	printlog "Check that the Title and Description fields have been saved correctly"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems picture is not selected => Description Object could not be opened"
	endcatch	

	Kontext "DescriptionObject"
	if DescriptionTitle.Gettext <> "TitleText" then
		Warnlog "Object title gets lost. Not 'TitleText' but " & DescriptionTitle.Gettext 	
	endif	
	if DescriptionText.Gettext <> "This Is A Description" then
		warnlog "Object description gets lost. Not 'This Is A Description' but " & DescriptionText.Gettext 	
	endif
	DescriptionObject.Cancel
	
    printlog "- Format - Picture"
	FormatGraphics
	Kontext
	Active.Setpage TabZusaetze
	Kontext "TabZusaetze"
	if Alternativtext.Gettext <> "TitleText" then
		Warnlog "Alternatice text in pictures options is not set after save and reload"
	endif
	TabZusaetze.Cancel

	printlog "- close document"
 	Call hCloseDocument

endcase

'-------------------------------------------------------------------------

testcase tFrameAlternativeText

	printlog "- New writer document"	
	Call hNewDocument
    
	printlog "- Insert a frame"	
	Call wInsertFrame
	
    printlog "- Context menu on the frame, choose 'Description'"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems Frame is not selected => Description Object could not be opened"
	endcatch	
	
    printlog "- Type 'TitleText' in the Title field"
	Kontext "DescriptionObject"
	DescriptionTitle.Settext "TitleText"	
	
    printlog "- Type 'This Is A Description'"
	DescriptionText.Settext "This Is A Description"	
	
    printlog "- Close the dialog"
	DescriptionObject.Ok

    printlog "- Context menu on the frame, choose 'Description'"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems frame is not selected => Description Object could not be opened"
	endcatch	

	printlog "Check that the Title and Description fields have been saved correctly"
	Kontext "DescriptionObject"
	if DescriptionTitle.Gettext <> "TitleText" then
		Warnlog "Object title gets lost. Not 'TitleText' but " & DescriptionTitle.Gettext 	
	endif	
	if DescriptionText.Gettext <> "This Is A Description" then
		warnlog "Object description gets lost. Not 'This Is A Description' but " & DescriptionText.Gettext 	
	endif
	DescriptionObject.Cancel		
	
    printlog "- Save the document"
	Call hFileSaveAsKill ( gOfficePath + "user\work\tFrameAlternativeText.odt" )
	Call hCloseDocument
	
    printlog "- Reload"
	hFileOpen(  gOfficePath + "user\work\tFrameAlternativeText.odt" )		
	' select frame
	Call wTypeKeys ("<SHIFT F4>")
	
	printlog "Check that the Title and Description fields have been saved correctly"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems frame is not selected => Description Object could not be opened"
	endcatch	

	Kontext "DescriptionObject"
	if DescriptionTitle.Gettext <> "TitleText" then
		Warnlog "Object title gets lost. Not 'TitleText' but " & DescriptionTitle.Gettext 	
	endif	
	if DescriptionText.Gettext <> "This Is A Description" then
		warnlog "Object description gets lost. Not 'This Is A Description' but " & DescriptionText.Gettext 	
	endif
	DescriptionObject.Cancel
	
	printlog "- close document"
 	Call hCloseDocument


endcase

'-------------------------------------------------------------------------

testcase tOLEAlternativeText

	printlog "- New writer document"	
	Call hNewDocument
    
	printlog "- Insert a OLE"	
    InsertObjectOLEObject
    Kontext "OLEObjektEinfuegen"
    NeuErstellen.Check
    OLEObjektEinfuegen.Ok
	Sleep 2	
	Call gMouseClick (10,10)	
	Call wTypeKeys "<SHIFT F4>"
	
    printlog "- Context menu on the OLE, choose 'Description'"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems OLE is not selected => Description Object could not be opened"
	endcatch	
	
    printlog "- Type 'TitleText' in the Title field"
	Kontext "DescriptionObject"
	DescriptionTitle.Settext "TitleText"	
	
    printlog "- Type 'This Is A Description'"
	DescriptionText.Settext "This Is A Description"	
	
    printlog "- Close the dialog"
	DescriptionObject.Ok

    printlog "- Context menu on the OLE, choose 'Description'"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems OLE is not selected => Description Object could not be opened"
	endcatch	

	printlog "Check that the Title and Description fields have been saved correctly"
	Kontext "DescriptionObject"
	if DescriptionTitle.Gettext <> "TitleText" then
		Warnlog "Object title gets lost. Not 'TitleText' but " & DescriptionTitle.Gettext 	
	endif	
	if DescriptionText.Gettext <> "This Is A Description" then
		warnlog "Object description gets lost. Not 'This Is A Description' but " & DescriptionText.Gettext 	
	endif
	DescriptionObject.Cancel		
	
    printlog "- Save the document"
	Call hFileSaveAsKill ( gOfficePath + "user\work\tOLEAlternativeText.odt" )
	Call hCloseDocument
	
    printlog "- Reload"
	hFileOpen(  gOfficePath + "user\work\tOLEAlternativeText.odt" )		
	' select OLE
	Call wTypeKeys ("<SHIFT F4>")
	
	printlog "Check that the Title and Description fields have been saved correctly"
	try
		ContextDescriptionObject
	catch
		Warnlog "Seems OLE is not selected => Description Object could not be opened"
	endcatch	

	Kontext "DescriptionObject"
	if DescriptionTitle.Gettext <> "TitleText" then
		Warnlog "Object title gets lost. Not 'TitleText' but " & DescriptionTitle.Gettext 	
	endif	
	if DescriptionText.Gettext <> "This Is A Description" then
		warnlog "Object description gets lost. Not 'This Is A Description' but " & DescriptionText.Gettext 	
	endif
	DescriptionObject.Cancel
	
	printlog "- close document"
 	Call hCloseDocument

endcase
