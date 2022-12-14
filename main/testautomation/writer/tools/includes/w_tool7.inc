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
'* short description : Functions mostly used for fields
'*
'*******************************************************************
'*
' #0 fSetLocale
' #0 fSetWestern
' #0 fSetAsian
' #0 fGetType
' #0 fGetFieldContent
' #0 fGetDate
' #0 fGetDate1
'*
'\***********************************************************************

function fSetLocale(sLocaleSetting as String)  as String

    'This function is set Locale in Tools/Options/Language Settings / Languages
    ToolsOptions
    Call hToolsOptions("LANGUAGESETTINGS","LANGUAGES")
    fSetLocale = Gebietsschema.GetSelText
    Gebietsschema.Select  sLocaleSetting
    Kontext "ExtrasOptionenDlg"
    ExtrasOptionenDlg.OK

end function

'----------------------------------------------------

function fSetWestern(sWestern as String)  as String

    'This function is set western language in Tools/Options/Language Settings / Languages
    ToolsOptions
    Call hToolsOptions("LANGUAGESETTINGS","LANGUAGES")
    fSetWestern = Westlich.GetSelText
    if sWestern = "Null" then
        Westlich.Select  1
        goto GoON
    end if
    Westlich.Select  sWestern
    GoON:
    Kontext "ExtrasOptionenDlg"
    ExtrasOptionenDlg.OK

end function

'----------------------------------------------------

function fSetAsian(sAsian as String)  as String

    'This function is set CJK language in Tools/Options/Language Settings / Languages
    ToolsOptions
    Call hToolsOptions("LANGUAGESETTINGS","LANGUAGES")
    fSetAsian = Asiatisch.GetSelText
    if sAsian = "Null" then
        if Asiatisch.IsEnabled then Asiatisch.Select  1
    else
        if Asiatisch.IsEnabled then Asiatisch.Select sAsian
    end if
    Kontext "ExtrasOptionenDlg"
    ExtrasOptionenDlg.OK

end function

'----------------------------------------------------

function fGetType(sType as String)  as String

    'This function will RETURN TYPE
    select case sType
    case "Author"
        select case iSprache
        case 1:   	fGetType = "Author"
        case 7:		fGetType = "??????????"
        case 31:  	fGetType = "Gebruiker"
        case 33:  	fGetType = "Utilisateur"
        case 34:  	fGetType = "Autor"
        case 36:  	fGetType = "Szerz??"
        case 39:  	fGetType = "Autore"
        case 46:  	fGetType = "Anv??ndare"
        case 49:  	fGetType = "Benutzer"
        case 55:  	fGetType = "Autor"
        case 81:  	fGetType = "????????????"
        case 82:  	fGetType = "??????????"
        case 86:  	fGetType = "?????????"
        case 88:  	fGetType = "?????????"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case "Chapter"
        select case iSprache
        case 1:      	fGetType = "Chapter"
        case 7:		fGetType = "??????????"
        case 31:     	fGetType = "Hoofdstuk"
        case 33:     	fGetType = "Chapitre"
        case 34:     	fGetType = "Cap??tulo"
        case 36:     	fGetType = "Fejezet"
        case 39:     	fGetType = "Capitolo"
        case 46:     	fGetType = "Kapitel"
        case 49:     	fGetType = "Kapitel"
        case 55:     	fGetType = "Cap??tulo"
        case 81:     	fGetType = "???"
        case 82:     	fGetType = "???"
        case 86:     	fGetType = "???"
        case 88:     	fGetType = "???"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case "Date"
        select case iSprache
        case 1:      	fGetType = "Date"
        case 7:		fGetTYpe = "????????"
        case 31:     	fGetType = "Datum"
        case 33:     	fGetType = "Date"
        case 34:     	fGetType = "Fecha"
        case 36:     	fGetType = "D??tum"
        case 39:     	fGetType = "Data"
        case 46:     	fGetType = "Datum"
        case 49:     	fGetType = "Datum"
        case 55:     	fGetType = "Data"
        case 81:     	fGetType = "??????"
        case 82:     	fGetType = "??????"
        case 86:     	fGetType = "??????"
        case 88:     	fGetType = "??????"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case "File name"
        select case iSprache
        case 1:      	fGetType = "File name"
        case 7:		fGetType = "?????? ??????????"
        case 31:     	fGetType = "Bestandsnaam"
        case 33:     	fGetType = "Nom de fichier"
        case 34:     	fGetType = "Nombre del archivo"
        case 36:     	fGetType = "F??jln??v"
        case 39:     	fGetType = "Nome file"
        case 46:     	fGetType = "Filnamn"
        case 49:     	fGetType = "Dateiname"
        case 55:     	fGetType = "Nome do arquivo"
        case 81:     	fGetType = "?????????????????"
        case 82:     	fGetType = "?????????? ??????????"
        case 86:     	fGetType = "???????????"
        case 88:     	fGetType = "???????????"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case "Page"
        select case iSprache
        case 1:      	fGetType = "Page"
        case 7:		fGetType = "????????????????"
        case 31:     	fGetType = "Pagina"
        case 33:     	fGetType = "Page"
        case 34:     	fGetType = "P??gina"
        case 36:     	fGetType = "Oldal"
        case 39:     	fGetType = "Pagina"
        case 46:     	fGetType = "Sida"
        case 49:     	fGetType = "Seite"
        case 55:     	fGetType = "P??gina"
        case 81:     	fGetType = "?????????"
        case 82:     	fGetType = "?????????????"
        case 86:     	fGetType = "???"
        case 88:     	fGetType = "????"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case "Sender"
        select case iSprache
        case 1:      	fGetType = "Sender"
        case 7:		fGetType = "??????????????????????"
        case 31:     	fGetType = "Afzender"
        case 33:     	fGetType = "Exp??diteur"
        case 34:     	fGetType = "Remitente"
        case 36:     	fGetType = "Felad??"
        case 39:     	fGetType = "Mittente"
        case 46:     	fGetType = "Avs??ndare"
        case 49:     	fGetType = "Absender"
        case 55:     	fGetType = "Remetente"
        case 81:     	fGetType = "?????????"
        case 82:     	fGetType = "?????? ??????"
        case 86:     	fGetType = "?????????????"
        case 88:     	fGetType = "?????????"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case "Statistics"
        select case iSprache
        case 1:      fGetType = "Statistics"
        case 7:		fGetType = "????????????????????"
        case 31:     fGetType = "Statistiek"
        case 33:     fGetType = "Statistiques"
        case 34:     fGetType = "Estad??stica"
        case 36:     fGetType = "Statisztika"
        case 39:     fGetType = "Statistiche"
        case 46:     fGetType = "Statistik"
        case 49:     fGetType = "Statistik"
        case 55:     fGetType = "Estat??sticas"
        case 81:     fGetType = "??????"
        case 82:     fGetType = "??????"
        case 86:     fGetType = "??????"
        case 88:     fGetType = "??????"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case "Templates"
        select case iSprache
        case 1:      	fGetType = "Templates"
        case 7:      	fGetType = "??????????????"
        case 31:     	fGetType = "Sjablonen"
        case 33:     	fGetType = "Mod??le de document"
        case 34:     	fGetType = "Plantillas"
        case 36:     	fGetType = "Sablonok"
        case 39:     	fGetType = "Modello"
        case 46:     	fGetType = "Dokumentmall"
        case 49:     	fGetType = "Dokumentvorlage"
        case 55:     	fGetType = "Modelos"
        case 81:     	fGetType = "????????????????????????????????????"
        case 82:     	fGetType = "??????? ??????????"
        case 86:     	fGetType = "?????????????"
        case 88:     	fGetType = "?????????????"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case "Time"
        select case iSprache
        case 1:      	fGetType = "Time"
        case 7:		fGetTYpe = "??????????"
        case 31:     	fGetType = "Tijd"
        case 33:     	fGetType = "Heure"
        case 34:     	fGetType = "Hora"
        case 36:     	fGetTYpe = "Id??"
        case 39:     	fGetType = "Orario"
        case 46:     	fGetType = "Klockslag"
        case 49:     	fGetType = "Uhrzeit"
        case 55:     	fGetType = "Hora"
        case 81:     	fGetType = "??????"
        case 82:     	fGetType = "??????"
        case 86:     	fGetType = "??????"
        case 88:     	fGetType = "??????"
        case else :
            QAErrorLog "Now, the test does not support for the language " +iSprache
            fGetType = ""
        end select
    case else :        ' Fallback
        QAErrorLog "Now, the test does not support for the type -- " &sType
        fGetType = ""
    end select

end function

'----------------------------------------------------

function fGetFieldContent( ) as String

    Call fFormatCharacter("TabHyperlinkZeichen")
    fGetFieldContent = Hinweis.GetText
    TabHyperlinkZeichen.Cancel

end function

'----------------------------------------------------

function fSetToBigSize( )

    Call fFormatCharacter("TabFont")
    try
        SizeWest.Select SizeWest.GetItemCount
    catch
        Size.Select Size.GetItemCount
    endcatch
    TabFont.OK

end function


'----------------------------------------------------

function fGetDirLanguage( ) as String

    'This function will RETURN language name for
    'install directory ,
    'eg . $SO_path/share/template/?? <- What you need to know
    Select case iSprache
    case 01   : fGetDirLanguage = "en-US"    '(English USA)
    case 31   : fGetDirLanguage = "nl"    ' Dutch
    case 33   : fGetDirLanguage = "fr-FR"    '(French)
    case 34   : fGetDirLanguage = "es-ES"    '(Spanish)
    case 39   : fGetDirLanguage = "it-IT"    '(Italian)
    case 46   : fGetDirLanguage = "sv-SE"    '(Swedish)
    case 49   : fGetDirLanguage = "de-DE"    '(German)
    case 55   : fGetDirLanguage = "pt-BR"    '(Portuguese)
    case 81   : fGetDirLanguage = "ja-JP"    '(Japanese)
    case 82   : fGetDirLanguage = "ko-KR"    '(Korean)
    case 86   : fGetDirLanguage = "zh-CN"    '(Simplified Chinese)
    case 88   : fGetDirLanguage = "zh-TW"    '(Traditional Chinese)
    case else : QAErrorLog "The test does not support the language " + iSprache
        fGetDirLanguage = "en-US"
    end select

end function

'----------------------------------------------------

function fGetCategory( ) as String

    'This function will RETURN Category when inserting from template
    Select case iSprache
    case 01   : fGetCategory = "Education"
    case 31   : fGetCategory = "Opleiding"
    case 33   : fGetCategory = "??ducation"
    case 34   : fGetCategory = "Educaci??n"
    case 39   : fGetCategory = "Formazione"
    case 46   : fGetCategory = "Utbildning"
    case 49   : fGetCategory = "Bildung"
    case 55   : fGetCategory = "Forma????o"
    case 81   : fGetCategory = "??????"
    case 82   : fGetCategory = "??????? ?????? ??????"
    case 86   : fGetCategory = "??????"
    case 88   : fGetCategory = "??????"
    case else : QAErrorLog "The test does not support the language " + iSprache
    end select

end function

'----------------------------------------------------

function fGetStyle( ) as String

    'This function will RETURN Style when inserting from template
    Select case iSprache
    case 01   : fGetStyle = "Master's Thesis"
    case 33   : fGetStyle = "M??moire"
    case 34   : fGetStyle = "Trabajo de licenciatura"
    case 39   : fGetStyle = "Tesi di laurea"
    case 46   : fGetStyle = "Examensarbete"
    case 49   : fGetStyle = "Diplomarbeit"
    case 55   : fGetStyle = "Disserta????o de Mestrado"
    case 81   : fGetStyle = "????????????????"
    case 82   : fGetStyle = "???????"
    case 86   : fGetStyle = "????????????"
    case 88   : fGetStyle = "????????????"
    case else : QAErrorLog "The test does not support the language " + iSprache
    end select

end function

'----------------------------------------------------

function fGetDate(sDate as String) as String

    Dim sMonth , sDay , sYear as String

    'This function will RETURN Style when inserting from template

    select case iSystemSprache
    case 01   :
        sMonth = Left (sDate , 2)
        sDay   = Mid  (sDate , 4 , 2)
        sYear  = Right(sDate , 2)
    case 49   :
        sMonth = Mid  (sDate , 4 , 2)
        sDay   = Left (sDate , 2)
        sYear  = Right(sDate , 2)
    case 86   :
        sMonth = Mid  (sDate , 6 , 2)
        sDay   = Right(sDate , 2)
        sYear  = Mid  (sDate , 3 , 2)
    case else:

    end select
    fGetDate = sMonth & "/" & sDay & "/" & sYear

end function

'----------------------------------------------------

function fGetDate1(sDate as String) as String

    Dim sMonth , sDay , sYear as String

    'This function will RETURN Style when inserting from template

    select case iSystemSprache
    case 01   :
        sMonth = Left (sDate , 2)
        sDay   = Mid  (sDate , 4 , 2)
        sYear  = Right(sDate , 4)
    case 49   :
        sMonth = Mid  (sDate , 4 , 2)
        sDay   = Left (sDate , 2)
        sYear  = Right(sDate , 4)
    case 86   :
        sMonth = Mid  (sDate , 6 , 2)
        sDay   = Right(sDate , 2)
        sYear  = Left (sDate , 4)
    case else:

    end select
    fGetDate1 = sMonth & "/" & sDay & "/" & sYear

end function

'-------------------------------------------------------------------------------------------

function fConvertBacklashToSlash (sTest) as String
    '/// convert all \ to / , return the string with /
    '///+ eg, \tmp\test\optional\includes\ ==> /tmp/test/optional/includes/

    Dim i    as Integer
    Dim s1$ : Dim s2$ : Dim s3$

    s1$ = sTest

    'convert all \ to /
    do
        i = InStr( s1$, "\" )
        if i = 0 then exit do
        s2$ = Left( s1$ , i-1 )
        s1$ = Mid( s1$ , i+1 )
        s3$ = s3$ + s2$ + "/"
    loop until s1$=""
    fConvertBacklashToSlash = s3$ + s1$

end function

