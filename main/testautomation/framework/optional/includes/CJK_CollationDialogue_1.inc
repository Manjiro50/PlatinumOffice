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
'* short description : CJK Collation Dialogue Design Draft
'*
'\***********************************************************************

testcase tLanguageTest_1

    Dim sLanguageIDEnglishUSA ,sLanguageIDSChinese, sLanguageIDTChinese , sLanguageIDJapanese , sLanguageIDKoren as String
    Dim sKeyTypeEnglishUSA    ,sKeyTypeSChinese   , sKeyTypeTChinese    , sKeyTypeJapanese    , sKeyTypeKoren    as String
    Dim i as Integer

    '/// Check if the default setting for &quot;key type&quot; is right for CJK when alphanumeric is chosen in English

    select case iSprache
    case 01   :' English (USA)
        sKeyTypeEnglishUSA = "Alphanumeric"
        sKeyTypeSChinese   = "Character set"
        sKeyTypeTChinese   = "Numeric"
        sKeyTypeJapanese   = "Character set"
        sKeyTypeKoren      = "Character set"
    case 49   :' German
        sKeyTypeEnglishUSA = "Alphanumerisch"
        sKeyTypeSChinese   = "Numerisch"
        sKeyTypeTChinese   = "Numerisch"
        sKeyTypeJapanese   = "Numerisch"
        sKeyTypeKoren      = "Numerisch"
    case 50   :' Slovenian
        sKeyTypeEnglishUSA = "Alfanumeri??no"
        sKeyTypeSChinese   = "Nabor znakov"
        sKeyTypeTChinese   = "Numeri??no"
        sKeyTypeJapanese   = "Nabor znakov"
        sKeyTypeKoren      = "Nabor znakov"
    case 55   :' Brazilian
        sKeyTypeEnglishUSA = "Alfanum??rico"
        sKeyTypeSChinese   = "Conjunto de caracteres"
        sKeyTypeTChinese   = "num??rico"
        sKeyTypeJapanese   = "Conjunto de caracteres"
        sKeyTypeKoren      = "Conjunto de caracteres"
    case 81   :' Japanese
        sKeyTypeEnglishUSA = "?????????"
        sKeyTypeSChinese   = "????????????(?????????????????????????????????)"
        sKeyTypeTChinese   = "????????????(?????????????????????????????????)"
        sKeyTypeJapanese   = "??????"
        sKeyTypeKoren      = "??????"
        '      case 82   : ' Korean
        '                   sKeyTypeEnglishUSA = 1 'alphanumeric
        '                   sKeyTypeSChinese   = 1 'Character set
        '                   sKeyTypeTChinese   = 3 'Pin yin
        '                   sKeyTypeJapanese   = 2 'Character set
        '                   sKeyTypeKoren      = 3 'Character set
    case 86   :' Chinese (simplified)
        sKeyTypeEnglishUSA = "???????????????"
        sKeyTypeSChinese   = "?????????"
        sKeyTypeTChinese   = "??????"
        sKeyTypeJapanese   = "?????????"
        sKeyTypeKoren      = "??????"
    case 88   :' Chinese (traditional)
        sKeyTypeEnglishUSA = "???????????????"
        sKeyTypeSChinese   = "??????"
        sKeyTypeTChinese   = "??????"
        sKeyTypeJapanese   = "??????"
        sKeyTypeKoren      = "??????"
    case else :' Fallback
        PrintLog "The test does not support the language " + iSprache
        Goto endsub
    end select

    sLanguageIDEnglishUSA = fGetCountryName(01)
    sLanguageIDSChinese   = fGetCountryName(86)
    sLanguageIDTChinese   = fGetCountryName(88)
    sLanguageIDJapanese   = fGetCountryName(81)
    sLanguageIDKoren      = fGetCountryName(82)

    call hNewDocument

    DocumentWriter.TypeKeys "test"
    DocumentWriter.TypeKeys "<Shift Home>"
    Sleep 1

    '/// Open Tools/Sort
    ToolsSort
    Kontext "Sortieren"

    '/// Choose language: English and key type: alphanumeric
    try
        Sprache.Select (sLanguageIDEnglishUSA)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        try
            Sprache.Select ("English (USA)")
        catch
            qaErrorLog "Can't select even tha fallback: 'English (USA)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeEnglishUSA
    catch
        qaErrorLog "Can't select: '" + sKeyTypeEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        for i = 1 to Schluesseltyp1.getItemCount
            printlog "" + i + ": '" + Schluesseltyp1.getItemText(i) + "'"
        next i
    endcatch

    '/// Check to simplified Chinese
    try
        Sprache.Select (sLanguageIDSChinese)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDSChinese + "'"
        ' try fallback to 'Chinese (simplyfied)'
        try
            Sprache.Select ("Chinese (simplyfied)")
        catch
            qaErrorLog "Can't select even tha fallback: 'Chinese (simplyfied)'"
        endcatch
    endcatch
    Sleep 2

    try
        Sprache.Select (sLanguageIDEnglishUSA)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        try
            Sprache.Select ("English (USA)")
        catch
            qaErrorLog "Can't select even tha fallback: 'English (USA)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeEnglishUSA
    catch
        qaErrorLog "Can't select: '" + sKeyTypeEnglishUSA + "'"
    endcatch

    '/// Check to traditional Chinese
    try
        Sprache.Select (sLanguageIDTChinese)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDTChinese + "'"
        ' try fallback to 'Chinese (traditional)'
        try
            Sprache.Select ("Chinese (traditional)")
        catch
            qaErrorLog "Can't select even tha fallback: 'Chinese (traditional)'"
            for i = 1 to Sprache.getItemCount
                printlog "("+i+"/"+ Sprache.getItemCount + "): '"+Sprache.getItemText(i)+"'"
            next i
        endcatch
    endcatch
    Sleep 2

    try
        Sprache.Select (sLanguageIDEnglishUSA)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        try
            Sprache.Select ("English (USA)")
        catch
            qaErrorLog "Can't select even tha fallback: 'English (USA)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeEnglishUSA
    catch
        qaErrorLog "Can't select: '" + sKeyTypeEnglishUSA + "'"
    endcatch

    '/// Check to Japanese
    try
        Sprache.Select (sLanguageIDJapanese)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDJapanese + "'"
        ' try fallback to 'Japanese'
        try
            Sprache.Select ("Japanese")
        catch
            qaErrorLog "Can't select even tha fallback: 'Japanese'"
        endcatch
    endcatch
    Sleep 2
    if Schluesseltyp1.GetSelText <> sKeyTypeJapanese then
        warnlog "The default key type for Japanese should be: '" + sKeyTypeJapanese + "' but is: '" + Schluesseltyp1.GetSelText + "'"
    end if

    try
        Sprache.Select (sLanguageIDEnglishUSA)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        try
            Sprache.Select ("English (USA)")
        catch
            qaErrorLog "Can't select even tha fallback: 'English (USA)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeEnglishUSA
    catch
        qaErrorLog "Can't select: '" + sKeyTypeEnglishUSA + "'"
    endcatch

    '/// Check to Korean
    try
        Sprache.Select (sLanguageIDKoren)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDKoren + "'"
        ' try fallback to 'Korean (RoK)'
        try
            Sprache.Select ("Korean (RoK)")
        catch
            qaErrorLog "Can't select even tha fallback: 'Korean (RoK)'"
            for i = 1 to Sprache.getItemCount
                printlog "("+i+"/"+ Sprache.getItemCount + "): '"+Sprache.getItemText(i)+"'"
            next i
        endcatch
    endcatch
    Sleep 2
    if Schluesseltyp1.GetSelText <> sKeyTypeKoren then
        warnlog "The default key type for Korean should be " +  sKeyTypeKoren + " but get " + Schluesseltyp1.GetSelText
    end if

    Sortieren.Cancel

    Call hCloseDocument

endcase

'-------------------------------------------------------------------------

testcase tLanguageTest_2

    Dim sLanguageIDEnglishUSA ,sLanguageIDSChinese, sLanguageIDTChinese , sLanguageIDJapanese , sLanguageIDKoren as String
    Dim sKeyTypeEnglishUSA    ,sKeyTypeSChinese   , sKeyTypeTChinese    , sKeyTypeJapanese    , sKeyTypeKoren    as String
    Dim i                                                                                                        as Integer

    '/// Check if the default setting for &quot;key type&quot; is right for CJK when numeric is chosen in English

    select case iSprache
    case 01   :' English (USA)
        sKeyTypeEnglishUSA = "Numeric"
        sKeyTypeSChinese   = "Numeric"
        sKeyTypeTChinese   = "Numeric"
        sKeyTypeJapanese   = "Numeric"
        sKeyTypeKoren      = "Numeric"
    case 49   :' German
        sKeyTypeEnglishUSA = "Numerisch"
        sKeyTypeSChinese   = "Numerisch"
        sKeyTypeTChinese   = "Numerisch"
        sKeyTypeJapanese   = "Numerisch"
        sKeyTypeKoren      = "Numerisch"
    case 50   :' Slovenian
        sKeyTypeEnglishUSA = "Alfanumeri??no"
        sKeyTypeSChinese   = "Nabor znakov"
        sKeyTypeTChinese   = "Numeri??no"
        sKeyTypeJapanese   = "Nabor znakov"
        sKeyTypeKoren      = "Nabor znakov"
    case 55   :' Brazilian
        sKeyTypeEnglishUSA = "num??rico"
        sKeyTypeSChinese   = "num??rico"
        sKeyTypeTChinese   = "num??rico"
        sKeyTypeJapanese   = "num??rico"
        sKeyTypeKoren      = "num??rico"
    case 81   :' Japanese
        sKeyTypeEnglishUSA = "??????"
        sKeyTypeSChinese   = "??????"
        sKeyTypeTChinese   = "??????"
        sKeyTypeJapanese   = "??????"
        sKeyTypeKoren      = "??????"
        '      case 82    ' Korean
        '                   sKeyTypeEnglishUSA = 2 'numeric
        '                   sKeyTypeSChinese   = 4 'numeric
        '                   sKeyTypeTChinese   = 4 'numeric
        '                   sKeyTypeJapanese   = 4 'numeric
        '                   sKeyTypeKoren      = 4 'numeric
    case 86   :' Chinese (simplified)
        sKeyTypeEnglishUSA = "??????"
        sKeyTypeSChinese   = "??????"
        sKeyTypeTChinese   = "??????"
        sKeyTypeJapanese   = "??????"
        sKeyTypeKoren      = "??????"
    case 88   :' Chinese (traditional)
        sKeyTypeEnglishUSA = "??????"
        sKeyTypeSChinese   = "??????"
        sKeyTypeTChinese   = "??????"
        sKeyTypeJapanese   = "??????"
        sKeyTypeKoren      = "??????"
    case else :' Fallback
        printLog "The test does not support the language " + iSprache
        Goto endsub
    end select

    sLanguageIDEnglishUSA = fGetCountryName(01)
    sLanguageIDSChinese   = fGetCountryName(86)
    sLanguageIDTChinese   = fGetCountryName(88)
    sLanguageIDJapanese   = fGetCountryName(81)
    sLanguageIDKoren      = fGetCountryName(82)

    call hNewDocument

    DocumentWriter.TypeKeys "123"
    DocumentWriter.TypeKeys "<Shift Home>"
    Sleep 1

    '/// Open Tools/Sort
    ToolsSort
    Kontext "Sortieren"

    '/// Choose language: English and key type: Numeric
    try
        Sprache.Select (sLanguageIDEnglishUSA)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        try
            Sprache.Select ("English (USA)")
        catch
            qaErrorLog "Can't select even tha fallback: 'English (USA)'"
            for i = 1 to Sprache.getItemCount
                printlog "" + i + ": '" + Sprache.getItemText(i) + "'"
            next i
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeEnglishUSA
    catch
        qaErrorLog "Can't select: '" + sKeyTypeEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        for i = 1 to Schluesseltyp1.getItemCount
            printlog "" + i + ": '" + Schluesseltyp1.getItemText(i) + "'"
        next i
    endcatch

    '/// Check to simplified Chinese
    try
        Sprache.Select (sLanguageIDSChinese)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDSChinese + "'"
        ' try fallback to 'Chinese (simplyfied)'
        try
            Sprache.Select ("Chinese (simplyfied)")
        catch
            qaErrorLog "Can't select even tha fallback: 'Chinese (simplyfied)'"
        endcatch
    endcatch
    Sleep 2
    if Schluesseltyp1.GetSelText <> sKeyTypeSChinese then
        warnlog "The default key type for Simplified Chinese should be: '" +  sKeyTypeSChinese + "' but is '" + Schluesseltyp1.GetSelText + "'"
    end if

    try
        Sprache.Select (sLanguageIDEnglishUSA)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        try
            Sprache.Select ("English (USA)")
        catch
            qaErrorLog "Can't select even tha fallback: 'English (USA)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeEnglishUSA
    catch
        qaErrorLog "Can't select: '" + sKeyTypeEnglishUSA + "'"
    endcatch

    '/// Check to traditional Chinese
    try
        Sprache.Select (sLanguageIDTChinese)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDTChinese + "'"
        ' try fallback to 'Chinese (traditional)'
        try
            Sprache.Select ("Chinese (traditional)")
        catch
            qaErrorLog "Can't select even tha fallback: 'Chinese (traditional)'"
        endcatch
    endcatch
    Sleep 2
    if Schluesseltyp1.GetSelText <> sKeyTypeTChinese then
        warnlog "The default key type for traditional Chinese should be " +  sKeyTypeTChinese + " but get " +  Schluesseltyp1.GetSelText
    end if

    try
        Sprache.Select (sLanguageIDEnglishUSA)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        try
            Sprache.Select ("English (USA)")
        catch
            qaErrorLog "Can't select even tha fallback: 'English (USA)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeEnglishUSA
    catch
        qaErrorLog "Can't select: '" + sKeyTypeEnglishUSA + "'"
    endcatch

    '/// Check to Japanese
    try
        Sprache.Select (sLanguageIDJapanese)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDJapanese + "'"
        ' try fallback to 'Japanese'
        try
            Sprache.Select ("Japanese")
        catch
            qaErrorLog "Can't select even tha fallback: 'Japanese'"
        endcatch
    endcatch
    Sleep 2
    if Schluesseltyp1.GetSelText <> sKeyTypeJapanese then
        warnlog "The default key type for Japanese should be: '" + sKeyTypeJapanese + "' but is: '" + Schluesseltyp1.GetSelText + "'"
    end if

    try
        Sprache.Select (sLanguageIDEnglishUSA)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDEnglishUSA + "'"
        ' try fallback to 'English (USA)'
        try
            Sprache.Select ("English (USA)")
        catch
            qaErrorLog "Can't select even tha fallback: 'English (USA)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeEnglishUSA
    catch
        qaErrorLog "Can't select: '" + sKeyTypeEnglishUSA + "'"
    endcatch

    '/// Check to Korean
    try
        Sprache.Select (sLanguageIDKoren)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDKoren + "'"
        ' try fallback to 'Korean (RoK)'
        try
            Sprache.Select ("Korean (RoK)")
        catch
            qaErrorLog "Can't select even tha fallback: 'Korean (RoK)'"
        endcatch
    endcatch
    Sleep 2
    if Schluesseltyp1.GetSelText <> sKeyTypeKoren then
        warnlog "The default key type for Korean should be " +  sKeyTypeKoren + " but get " + Schluesseltyp1.GetSelText
    end if

    Sortieren.Cancel

    Call hCloseDocument
endcase

'-------------------------------------------------------------------------

testcase tStrokeSort

    Dim testFile              as String
    Dim sLanguageIDSChinese   as String
    Dim sKeyTypeSChinese      as String
    Dim aCorrectSequence()    as String

    Dim i , j                 as Integer

    testFile         = gTesttoolPath & "framework\optional\input\CJK\sortTest.sxw"
    testFile         = convertpath( testFile )
    aCorrectSequence = Array( "1" , "2" , "3" , "4" ,"5" )

    j = UBound(aCorrectSequence)

    select case iSprache
    case 01   :  ' English (USA)
        sKeyTypeSChinese      =  "Stroke"
    case 49   :  ' German
        sKeyTypeSChinese      =  "Stroke"
    case 50   :  ' Slovenian
        sKeyTypeSChinese      =  "Poteza"
    case 55   :  ' Brazilian
        sKeyTypeSChinese      =  "Tra??o"
    case 81   :  ' Japanese
        sKeyTypeSChinese      =  "?????????"
    case 86   :  ' Chinese (simplified)
        sKeyTypeSChinese      =  "??????"
    case 88   :  ' Chinese (simplified)
        sKeyTypeSChinese      =  "??????"
    case else :  ' Fallback
        printLog "Now, the test does not support for the language " +iSprache
        Goto endsub
    end select

    sLanguageIDSChinese =  fGetCountryName(86)

    '/// Check Stroke sort for Simplified Chinese

    Call hNewDocument
    '/// Open a test file and check <i>No Grid</i> checkbox
    hFileOpenLocally( testfile )
    hUseAsyncSlot( "EditSelectAll" )

    '/// Open <i>Tools/Sort</i>
    ToolsSort
    Kontext "Sortieren"

    '/// Choose language: Simplified Chinese and key type <i>Stroke</i>
    try
        Sprache.Select (sLanguageIDSChinese)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDSChinese + "'"
        ' try fallback to 'Chinese (simplyfied)'
        try
            Sprache.Select ("Chinese (simplyfied)")
        catch
            qaErrorLog "Can't select even tha fallback: 'Chinese (simplyfied)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeSChinese
    catch
        qaErrorLog "Can't select: '" + sKeyTypeSChinese + "'"
        for i = 1 to Schluesseltyp1.getItemCount
            printlog "" + i + ": '" + Schluesseltyp1.getItemText(i) + "'"
        next i
    endcatch

    Sortieren.OK

    Kontext "DocumentWriter"
    DocumentWriter.TypeKeys "<MOD1 Home>"

    For i = 0 to j
        DocumentWriter.TypeKeys "<End>"
        DocumentWriter.TypeKeys "<Shift Left>"

        EditCopy
        if GetClipboardText <> aCorrectSequence(i) then Warnlog "The Stroke sort is wrong , should be " +  aCorrectSequence(i) + " ,but get " +GetClipboardText

        DocumentWriter.TypeKeys "<Down>"
    next i

    Call hCloseDocument
    hFileDelete( gLastWorkFile )

endcase

'-------------------------------------------------------------------------

testcase tPinyinSort

    Dim testFile              as String
    Dim sLanguageIDSChinese   as String
    Dim sKeyTypeSChinese      as String
    Dim aCorrectSequence()    as String

    Dim i , j                 as Integer

    testFile         = gTesttoolPath & "framework\optional\input\CJK\sortTest.sxw"
    testFile         = convertpath( testFile )

    aCorrectSequence = Array( "2" , "3" , "4" , "1" , "5"  )

    j = UBound(aCorrectSequence)

    select case iSprache
    case 01   :  ' English (USA)
        sKeyTypeSChinese      =  "Pinyin"
    case 49   :  ' German
        sKeyTypeSChinese      =  "Pinyin"
    case 50   :  ' Slovenian
        sKeyTypeSChinese      =  "Pinjin"
    case 55   :  ' Brazilian
        sKeyTypeSChinese      =  "Pinyin"
    case 81   :  ' Japanese
        sKeyTypeSChinese      =  "????????????(?????????????????????????????????)"
    case 86   :  ' Chinese (simplified)
        sKeyTypeSChinese      =  "??????"
    case 88   :  ' Chinese (simplified)
        sKeyTypeSChinese      =  "??????"
    case else :  ' Fallback
        printLog "Now, the test does not support for the language " +iSprache
        Goto endsub
    end select

    sLanguageIDSChinese =  fGetCountryName(86)

    '/// Check <i>Pinyin</i> sort for Simplified Chinese

    Call hNewDocument
    '/// Open a test file and check <i>No Grid</i> checkbox
    hFileOpenLocally( testfile )
    hUseAsyncSlot( "EditSelectAll" )

    '/// Open <i>Tools/Sort</i>
    ToolsSort
    Kontext "Sortieren"

    '/// Choose language: Simplified Chinese and key type <i>Pin yin</i>
    try
        Sprache.Select (sLanguageIDSChinese)
    catch
        qaErrorLog "Can't select: '" + sLanguageIDSChinese + "'"
        ' try fallback to 'Chinese (simplyfied)'
        try
            Sprache.Select ("Chinese (simplyfied)")
        catch
            qaErrorLog "Can't select even tha fallback: 'Chinese (simplyfied)'"
        endcatch
    endcatch
    try
        Schluesseltyp1.Select sKeyTypeSChinese
    catch
        qaErrorLog "Can't select: '" + sKeyTypeSChinese + "'"
        for i = 1 to Schluesseltyp1.getItemCount
            printlog "" + i + ": '" + Schluesseltyp1.getItemText(i) + "'"
        next i
    endcatch

    Sortieren.OK

    Kontext "DocumentWriter"
    DocumentWriter.TypeKeys "<MOD1 Home>"

    For i = 0 to j
        DocumentWriter.TypeKeys "<End>"
        DocumentWriter.TypeKeys "<Shift Left>"

        EditCopy
        if GetClipboardText <> aCorrectSequence(i) then
            Warnlog "The Pin yin sort is wrong, should be: '" +  aCorrectSequence(i) + "' ,but is: '" +GetClipboardText + "'"
        endif

        DocumentWriter.TypeKeys "<Down>"
    next i

    Call hCloseDocument
    hFileDelete( gLastWorkFile )

endcase

'-------------------------------------------------------------------------

testcase tSortOptionTest_1

    Dim  i  , j  as Integer
    Dim asList() as String

    select case iSprache
    case 81   :' Japanese
        if iSystemSprache <> 81 then goto NOTest
        asList = Array( "Sun,Mon,Tue,Wed,Thu,Fri,Sat"     , "Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday"    , "Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec"    , "January,February,March,April,May,June,July,August,September,October,November,December"    , "???,???,???,???,???,???,???"    , "?????????,?????????,?????????,?????????,?????????,?????????,?????????"    , )
    case 82   :' Korean
        if iSystemSprache <> 82 then goto NOTest
        asList = Array( "???,???,???,???,???,???,???" ,"?????????,?????????,?????????,?????????,?????????,?????????,?????????"  ,"1,2,3,4,5,6,7,8,9,10,11,12"    , "???,???,???,???,???,???,???"    , "?????????,?????????,?????????,?????????,?????????,?????????,?????????"    , )
    case 86   :' Chinese (simplified)
        if iSystemSprache <> 86 then goto NOTest
        asList = Array( "???,???,???,???,???,???,???"     , "?????????,?????????,?????????,?????????,?????????,?????????,?????????"    , "???,???,???,???,???,???,???,???,???,???,??????,??????"    , "??????,??????,??????,??????,??????,??????,??????,??????,??????,??????,?????????,?????????"    , )
    case 88   :' Chinese (traditional)
        if iSystemSprache <> 88 then goto NOTest
        asList = Array( "???,???,???,???,???,???,???"     , "?????????,?????????,?????????,?????????,?????????,?????????,?????????"    , "???,???,???,???,???,???,???,???,???,???,??????,??????"    , "??????,??????,??????,??????,??????,??????,??????,??????,??????,??????,?????????,?????????"    , )
    case else :' Fallback
        NOTest:
        printLog "The test does not support for the language " +iSprache + " System language " + iSystemSprache
        Goto endsub
    end select

    '/// Check if the entries in custom sort order is right in CJK version

    call hNewDocument

    '/// Open <i>Data/Sort</i> -&gt; tabpage <i>option</i>

    DataSort

    Kontext
    active.SetPage TabSortierenOptionen
    Kontext "TabSortierenOptionen"

    BenutzerdefinierteSortierreihenfolge.Check

    For i = 1 to SortierreihenfolgeListe.GetItemCount
        if  SortierreihenfolgeListe.GetItemText(i) <> asList(i-1) then
            warnlog "Should get " +asList(i) + " but get " +SortierreihenfolgeListe.GetItemText(i)
        end if
    next i

    TabSortierenOptionen.Cancel

    Call hCloseDocument

endcase

'----------------------------------------------------------------
