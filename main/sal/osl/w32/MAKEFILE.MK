#**************************************************************
#  
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#  
#    http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing,
#  software distributed under the License is distributed on an
#  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
#  specific language governing permissions and limitations
#  under the License.
#  
#**************************************************************



PRJ=..$/..

PRJNAME=sal
TARGET=cpposl
USE_LDUMP2=TRUE

PROJECTPCH4DLL=TRUE
PROJECTPCH=cont_pch
PROJECTPCHSOURCE=cont_pch

MULTITHREAD_OBJ=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# Uncomment the following line if you want to compile with -Wall
# it disables lots of unnecessary warnings comming from the Win32
# header files (disabling warnings via command line only works with
# MSVC >= 7.x)
#
# CFLAGS+=/wd4668 /wd4711 /wd4201 /wd4710 /wd4619 /wd4514 /wd4820

# --- Files --------------------------------------------------------
.IF "$(CCNUMVER)" >= "001400000000"
CDEFS+=-D_CRT_NON_CONFORMING_SWPRINTFS
.ENDIF

.IF "$(header)" == ""

SLOFILES=   $(SLO)$/conditn.obj  \
            $(SLO)$/diagnose.obj \
            $(SLO)$/dllentry.obj \
            $(SLO)$/semaphor.obj \
            $(SLO)$/socket.obj   \
            $(SLO)$/interlck.obj \
            $(SLO)$/nlsupport.obj\
            $(SLO)$/mutex.obj    \
            $(SLO)$/thread.obj   \
            $(SLO)$/module.obj   \
            $(SLO)$/process.obj  \
            $(SLO)$/security.obj \
            $(SLO)$/profile.obj  \
            $(SLO)$/time.obj     \
            $(SLO)$/signal.obj   \
            $(SLO)$/pipeimpl.obj \
            $(SLO)$/pipe.obj     \
            $(SLO)$/util.obj     \
            $(SLO)$/file.obj\
            $(SLO)$/file_dirvol.obj\
            $(SLO)$/file_error.obj\
            $(SLO)$/file_url.obj\
            $(SLO)$/tempfile.obj\
            $(SLO)$/path_helper.obj\
            $(SLO)$/procimpl.obj \
			$(SLO)$/salinit.obj

OBJFILES=   $(OBJ)$/conditn.obj  \
            $(OBJ)$/diagnose.obj \
            $(OBJ)$/libutil.obj  \
            $(OBJ)$/semaphor.obj \
            $(OBJ)$/socket.obj   \
            $(OBJ)$/interlck.obj \
            $(OBJ)$/nlsupport.obj\
            $(OBJ)$/mutex.obj    \
            $(OBJ)$/thread.obj   \
            $(OBJ)$/module.obj   \
            $(OBJ)$/process.obj  \
            $(OBJ)$/security.obj \
            $(OBJ)$/profile.obj  \
            $(OBJ)$/time.obj     \
            $(OBJ)$/signal.obj   \
            $(OBJ)$/pipeimpl.obj \
            $(OBJ)$/pipe.obj     \
            $(OBJ)$/util.obj     \
            $(OBJ)$/file.obj\
            $(OBJ)$/file_dirvol.obj\
            $(OBJ)$/file_error.obj\
            $(OBJ)$/file_url.obj\
            $(OBJ)$/tempfile.obj\
            $(OBJ)$/path_helper.obj\
            $(OBJ)$/procimpl.obj \
			$(OBJ)$/salinit.obj

.ENDIF

# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk


