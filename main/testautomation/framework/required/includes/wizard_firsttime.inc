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
'*  short description : Updatetest for the first time wizard
'*
'\******************************************************************************

testcase tUpdtWizardFirsttime

    printlog( "Resource test for the first start wizard" )
    
    dim iClick as integer
    dim cFirstName as string
    dim cLastName as string
    dim cInitials as string
    
    cFirstName = "Tom"
    cLastName = "Cat"
    cInitials = "TC"
    
    dim cQuickstarterPath as string
        cQuickStarterPath = gNetzOfficePath & "program\quickstart.exe"
    
    
    hInitSingleDoc()
    
    printlog( "Open the Wizard" )
    FirstTimeWizard
    
    ' give the wizard a maximum of 2 seconds to open, it's a serve-url and
    ' should open almost instantly
    kontext "WelcomeDialog"
    if ( WelcomeDialog.exists( 2 ) ) then
        printlog( "The Wizard is open" )
        call dialogtest( WelcomeDialog )
        
        printlog( "click 'next'")
        NextBtn.click()
    endif
    
    printlog( "Check the license page" )
    kontext "TabFirstStartLicense"
    if ( TabFirstStartLicense.exists( 2 ) ) then
        printlog( "License page is visible" )
        call dialogtest( TabFirstStartLicense )

    
        printlog( "scroll down (button!) the licensetext to enable the >>-button" )
        for iClick = 1 to 50
    
            kontext "TabFirstStartLicense"
            if ( ScrollDown.isEnabled( 1 ) ) then
                ScrollDown.click()
            else
                kontext "WelcomeDialog"
                if ( NextBtn.isEnabled() ) then
                    printlog( "Needed " & iClick & " clicks on 'scroll down' " )
                    exit for
                else
                    warnlog( "Both Scroll-button and Next-button are disabled" )
                    goto endsub
                endif
            endif
        next iClick
    
        sleep( 1 )
    
        kontext "WelcomeDialog"
        if ( WelcomeDialog.exists( 2 ) ) then
            NextBtn.click()
        else
            warnlog( "Cannot access welcome dialog" )
        endif
    endif
    
    
    
    printlog( "Handle Data-Migration page" )
    kontext "TabPersonalDataMigration"
    if ( TabPersonalDataMigration.exists( 2 ) ) then
        call dialogtest( TabPersonalDataMigration )
        printlog( "The data migration page is visible" )
        TransferPersonalData.uncheck()
        kontext "WelcomeDialog"
        NextBtn.click()
    endif
    
    
    
    printlog( "The personal data page should show up" )
    Kontext "TabFirstStartUser"
    if ( TabFirstStartUser.exists( 2 ) ) then
    
        call dialogtest( TabFirstStartUser )
        
        Kontext "TabFirstStartUser"
        printlog( "Enter lastname, name and initials" )
        FirstName.setText( cFirstname )
        LastName.setText( cLastName )
        Initials.setText( cInitials )
        
        kontext "WelcomeDialog"
        NextBtn.click()
    else
        warnlog( "Could not access TabFirstStartUser" )
    endif
    
    if (gAutoUpdate) then
        kontext "TabFirstStartOnlineUpdate"
        if ( TabFirstStartOnlineUpdate.exists( 2 ) ) then
            call dialogtest( TabFirstStartOnlineUpdate )
            CheckForUpdates.unCheck()
            kontext "WelcomeDialog"
            NextBtn.click()
        else
            warnlog( "Online Update Page is missing" )
        endif
    else
            qaErrorlog( "Online Update Page is missing" )
    endif
        
    
    Kontext "TabFirstStartRegistration"
    if ( TabFirstStartRegistration.exists( 3 ) ) then
        printlog( "Registration page visible." )
    else
	    qaerrorlog( "An additional page appears on rerun of wizard" )
        kontext "WelcomeDialog"
        NextBtn.click()
    endif
 
    printlog( "Registration page: " )
    Kontext "TabFirstStartRegistration"
    if ( TabFirstStartRegistration.exists( 2 ) ) then
        printlog( "Page is present." )
        call dialogtest( TabFirstStartRegistration )
        printlog( "Choose not to register" )
        DoNotWantRegister.check()
        
        printlog( "close the wizard" )
    	kontext "WelcomeDialog"
     	WelcomeDialog.ok()
    endif
    
    printlog( "Verify that the userdata made it to tools/options" )
    ToolsOptions
    hToolsOptions( "StarOffice" , "UserData" )

    if ( Vorname.getText() <> cFirstname ) then
        warnlog( "First name is not transferred to Tools/options/userdata" )
    endif
   
    if ( ZuName.getText() <> cLastName ) then
        warnlog( "Last name is not transferred to Tools/options/userdata" )
    endif
    
    if ( Kuerzel.getText() <> cInitials ) then
        warnlog( "Initials are not transferred to Tools/options/userdata" )
    endif
    
    hToolsOptions( "StarOffice", "Memory" )
    
    if ( LoadQuickstarter.exists() ) then
        if ( LoadQuickstarter.isEnabled() ) then
            printlog( "Quickstarter checkbox is enabled" )
            if ( LoadQuickstarter.isChecked() ) then
                printlog( "Quickstart is activated, turning it off." )
                LoadQuickstarter.unCheck()
                printlog( "Closing Tools/Options" )
                Kontext "OptionenDlg"
                hCloseDialog( OptionenDlg, "cancel" )
                printlog( "Restarting program" )
                call ExitRestartTheOffice()
            else
                printlog( "Quickstarter is not turned on." )
            endif
        else
            printlog( "Quickstarter checkbox is not enabled for this system" )
        endif
    else
        if ( gPlatGroup <> "unx" ) then
            if ( dir( cQuickStarterPath ) <> "" ) then
                warnlog( "Quickstarter checkbox is missing on options page" )
            else
                printlog( "Quickstarter is not installed/no checkbox present" )
            endif
        endif
    endif
        
    Kontext "OptionenDlg"
    hCloseDialog( OptionenDlg, "cancel, optional" )
    
    ' due to issue i105248 the Quickstart disabler needs to get called again, because the First Start Wizard resets the veto
    call hDisableQuickstarterAPI()

    hFileCloseAll()
   
endcase

