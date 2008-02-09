# Microsoft Developer Studio Project File - Name="kscomm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=kscomm - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "kscomm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "kscomm.mak" CFG="kscomm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "kscomm - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "kscomm - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/DevSrc/Tools/kscomm", DAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "kscomm - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../../Include/_backward/kscomm" /I "../../../Include" /I "." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/win32/kscomm.lib"

!ELSEIF  "$(CFG)" == "kscomm - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../../Include/_backward/kscomm" /I "../../../Include/" /I "." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/win32d/kscommd.lib"

!ENDIF 

# Begin Target

# Name "kscomm - Win32 Release"
# Name "kscomm - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h"
# Begin Group "FilePath"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\fileext.c
# End Source File
# Begin Source File

SOURCE=.\gendeffile.c
# End Source File
# Begin Source File

SOURCE=.\makepath.c
# End Source File
# Begin Source File

SOURCE=.\makepath2.c
# End Source File
# Begin Source File

SOURCE=.\mergepath.c
# End Source File
# Begin Source File

SOURCE=.\rmpathsep.c
# End Source File
# Begin Source File

SOURCE=.\searchpath.c
# End Source File
# Begin Source File

SOURCE=.\splitpat.c
# End Source File
# Begin Source File

SOURCE=.\splitpat2.c
# End Source File
# Begin Source File

SOURCE=.\stdpath.c
# End Source File
# End Group
# Begin Group "String"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\stratom.cpp
# End Source File
# Begin Source File

SOURCE=.\stricmp.c
# End Source File
# Begin Source File

SOURCE=.\string.c
# End Source File
# End Group
# Begin Group "Dir"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\linux\linux_finddir.c
# End Source File
# Begin Source File

SOURCE=.\scandir.c
# End Source File
# Begin Source File

SOURCE=.\win32\win32_finddir.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\baseimp.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\switch.c
# End Source File
# End Group
# End Target
# End Project
