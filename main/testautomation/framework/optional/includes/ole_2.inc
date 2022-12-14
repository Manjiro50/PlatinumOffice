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
'* short description : global-level-1-test -> insert all OLE-Objects out of OLE-dialog into all doc-types
'*
'\******************************************************************************

testcase tCheckTheOLEObjectDialog

   qaerrorlog( "#i80670# The OLE retrieval routine is broken beyond repair, redesign required" )
   goto endsub

   Dim lListe (10) as String : Dim lListSoll (10) as String
   Dim i, j as Integer
   Dim iCount, sCount as Integer
   
   call ClosePresentationfloat()
   GetOLEDefaultNames()

   for i=1 to 5
   
      select case i
         case 1 : gApplication = "WRITER"
         case 2 : gApplication = "CALC"
         case 3 : gApplication = "IMPRESS"
         case 4 : gApplication = "DRAW"
         case 5 : gApplication = "MASTERDOCUMENT"
      end select
      
      lListe ( 0 ) = 0 : lListSoll ( 0 ) = 0
      printlog "check OLE-Object-Dialog for " + gApplication
      
      Call hNewDocument
      
      InsertObjectOLEObject

      Kontext "OLEObjektEinfuegen"
      if ( not OLEObjektEinfuegen.exists() ) then
        warnlog( "cannot access the OLE object dialog" )
        goto endsub
      endif
      
      NeuErstellen.Check
      WaitSlot()
      
      for j=1 to ObjektTyp.GetItemCount
         ObjektTyp.Select j
         ListAppend ( lListe(), ObjektTyp.GetSelText )
      next j
      
      ListSort ( lListe() )
      iCount = ListCount ( lListe() )
      
      select case gApplication
         case "WRITER"    : ListAppend ( lListSoll (), gOLECalc )
                            ListAppend ( lListSoll (), gOLEImpress )
                            ListAppend ( lListSoll (), gOLEDraw )
                            ListAppend ( lListSoll (), gOLEChart )
                            ListAppend ( lListSoll (), gOLEMath )
         case "CALC"      : ListAppend ( lListSoll (), gOLEWriter )
                            ListAppend ( lListSoll (), gOLEImpress )
                            ListAppend ( lListSoll (), gOLEDraw )
                            ListAppend ( lListSoll (), gOLEChart )
                            ListAppend ( lListSoll (), gOLEMath )
         case "DRAW"      : ListAppend ( lListSoll (), gOLECalc )
                            ListAppend ( lListSoll (), gOLEImpress )
                            ListAppend ( lListSoll (), gOLEWriter )
                            ListAppend ( lListSoll (), gOLEChart )
                            ListAppend ( lListSoll (), gOLEMath )
         case "IMPRESS"   : ListAppend ( lListSoll (), gOLECalc )
                            ListAppend ( lListSoll (), gOLEDraw )
                            ListAppend ( lListSoll (), gOLEWriter ) 
                            ListAppend ( lListSoll (), gOLEChart )
                            ListAppend ( lListSoll (), gOLEMath )
         case "MASTERDOCUMENT" : ListAppend ( lListSoll (), gOLECalc ) 
                            ListAppend ( lListSoll (), gOLEImpress )
                            ListAppend ( lListSoll (), gOLEDraw ) 
                            ListAppend ( lListSoll (), gOLEChart )
                            ListAppend ( lListSoll (), gOLEMath )
      end select
      
      if ( gPlatgroup = "w95" ) then 
         ListAppend ( lListSoll (), gOLEOthers )
         endif
         
      ListSort ( lListSoll () )
      sCount = ListCount ( lListSoll () )
      
      if iCount <> sCount then
         Warnlog "Expected: " + sCount + "   Found: " + iCount
      else
         for j=1 to sCount
            if lListe (j) <> lListSoll (j) then 
               Warnlog "Expected: '" + lListSoll (j) + "'   Found: '" + lListe (j) +"'"
               endif
         next j
      end if
      
      OLEObjektEinfuegen.Cancel
      hCloseDocument()
   next i
endcase

