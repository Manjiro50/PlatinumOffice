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
'* short description : Read menubar and first level drop down lists and compare to reference
'*
'\*****************************************************************

sub t_getMenuText
    dim k,c as integer
    dim sApplication() as string

    sApplication = array("WRITER","MASTERDOCUMENT","HTML","CALC","IMPRESS","DRAW","MATH","BASIC","DATABASE")

    ' for every application
    c = uBound(sApplication())
    for k = 0 to c
        gApplication = sApplication(k)
        printlog "********** " + gApplication
        call s_getMenuText
    next k
    gApplication = "WRITER"
end sub

testcase s_getMenuText
    dim i,j,l,m,a,b,d,e as integer
    dim sReference(400) as string
    dim sCurrent(400) as string
    dim sFileName as string
    dim sTemp as string
    dim bError as boolean
    dim iTopLevelCount as integer
    dim iOffset as integer
    
        for i=0 to uBound(sReference())
            sReference(i) = 0
            sCurrent(i) = 0
        next i
        bError = FALSE
        hNewDocument
        hUseMenu
        ' for every item in main menu bar
        a = MenuGetItemCount
        iTopLevelCount = a
        MenuSelect (0)
        for i = 1 to a
            hUseMenu
            stemp = MenuGetItemText(MenuGetItemID(i))
            'printlog sTemp
            listAppend(sCurrent(),"********** "+sTemp)
            MenuSelect(MenuGetItemID(i))
            b = MenuGetItemCount
            for j = 1 to b
                sTemp = MenuGetItemText(MenuGetItemID(j))
                'printlog "    " + sTemp
                listAppend(sCurrent(),sTemp)
            next j
            MenuSelect (0)
        next i
        hCloseDocument
        sFileName = convertPath(gTestToolPath+"framework\optional\input/menu/"+lCase(gISOLang+"_"+gApplication+".txt"))
        printlog( "Using reference file: " & sFileName )
        ' gProductName should not make a big difference.
        if fileExists(sFileName) then
            ' load to compare
            listRead(sReference(), sFileName, "utf8")
            d = listCount(sCurrent())
            m = d
            e = listCount(sReference())
            if (d <> e) then
                warnlog "The count of Menuentries differs from reference "+gApplication+". should: '" + e + "'; delta is: '" + (d - e) + "'"
                bError = TRUE
                ' always take the shorter list count
                if cBool(d - e) then
                    d = e
                endif
                e = m - e
            else
                printlog "Count of Menuentries is ok"
                e = 0
            endif
            ' compare all entries
            iOffset = 0
            m = 0
            for l=1 to d 
                ' count main menu bar items
                if inStr(sReference(l), "********** ") > 0 then
                    m = m + 1
                    ' bug in inc m :-(
                    printlog mid(sReference(l),12)
                endif
                ' complain non existing accelerator
                if (sReference(l) <> "") AND (inStr(sReference(l),"~") < 1) then
                    qaErrorLog "No accelerator (~) in item: '" + sReference(l) + "'"
                endif
                ' compare the menu entries
                if (sReference(l) <> sCurrent(l+iOffset))then
                    ' try to syncronize different count of entries
                    if (e <> 0) then
                        iOffset = iOffset + sgn(e)
                        'qaerrorlog "io: " + ioffset
                        e = e - sgn(e)
                        'qaerrorlog "e: " + e
                    endif
                    '
                    if (m = (iTopLevelCount-1)) then
                        ' tolerate the window menu
                        printlog "String differs: " + chr(13) + "current  : '"+sCurrent(l) + "'" + chr(13) + "reference: '" + sReference(l) + "'"
                    else
                        bError = TRUE
                        warnlog "String differs: " + chr(13) + "current  : '"+sCurrent(l) + "'" + chr(13) + "reference: '" + sReference(l) + "'"
                    endif
                endif
            next l
          '  for l=d-5 to d+5
          '  printlog "------"
          '  printlog sreference(l)
          '  printlog scurrent(l)
          '  next l
            ' if there is still is a difference in count
            if (e <> 0) then
                if sgn(e) then
                    warnlog "Not all reference entries are there, e.g.: '" + sReference(l+1) + "'"
                else
                    warnlog "There are too much entries, e.g.: '" + sCurrent(l+1) + "'"
                endif
            endif
            if bError then
                sFileName = convertPath(gOfficePath+"user/work/menu/"+lCase(gISOLang+"_"+gApplication+".txt"))
                listWrite(sCurrent(), sFileName, "utf8")
                printlog "Written strings from this build to: " + chr(13) + sFileName
            else
                ' OK
            endif
        else
            ' write to checkin
            warnlog "No reference found; please copy:"+lCase(gISOLang+"_"+gApplication+".txt")
            sFileName = convertPath(gOfficePath+"user/work/menu/"+lCase(gISOLang+"_"+gApplication+".txt"))
            listWrite(sCurrent(), sFileName, "utf8")
            printlog sFileName + chr(13) + "to"
            sFileName = convertPath(gTestToolPath+"framework/level1/input/menu/"+lCase(gISOLang+"_"+gApplication+".txt"))
            printlog sFilename
            'listWrite(sCurrent(), sFileName, "utf8")
        endif
    'speichern: (vendor?) sprache gISOLang applikation
endcase

