# Microsoft Developer Studio Project File - Name="nxcon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=nxcon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nxcon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nxcon.mak" CFG="nxcon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nxcon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nxcon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nxcon - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 libnxcl.lib libnetxms.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\libnxcl\Release" /libpath:"..\..\libnetxms\Release"

!ELSEIF  "$(CFG)" == "nxcon - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libnxcl.lib libnetxms.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\libnxcl\Debug" /libpath:"..\..\libnetxms\Debug"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\nxcon.exe ..\..\..\bin
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "nxcon - Win32 Release"
# Name "nxcon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\comm.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\DataCollectionEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\DCIDataView.cpp
# End Source File
# Begin Source File

SOURCE=.\DCIPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DCIThresholdsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\draw.cpp
# End Source File
# Begin Source File

SOURCE=.\EditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\EditEventDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EventBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\EventEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\globals.cpp
# End Source File
# Begin Source File

SOURCE=.\Graph.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MapView.cpp
# End Source File
# Begin Source File

SOURCE=.\NetSummaryFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\NewUserDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NodePropsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeSummary.cpp
# End Source File
# Begin Source File

SOURCE=.\nxcon.cpp
# End Source File
# Begin Source File

SOURCE=.\nxcon.rc
# End Source File
# Begin Source File

SOURCE=.\ObjectBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectInfoBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPropCaps.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPropsGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPropsSecurity.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectSearchBox.cpp
# End Source File
# Begin Source File

SOURCE=.\PasswordChangeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestProcessingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ThresholdDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBox.cpp
# End Source File
# Begin Source File

SOURCE=.\tools.cpp
# End Source File
# Begin Source File

SOURCE=.\UserEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\UserPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserSelectDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ControlPanel.h
# End Source File
# Begin Source File

SOURCE=.\DataCollectionEditor.h
# End Source File
# Begin Source File

SOURCE=.\DCIDataView.h
# End Source File
# Begin Source File

SOURCE=.\DCIPropPage.h
# End Source File
# Begin Source File

SOURCE=.\DCIThresholdsPage.h
# End Source File
# Begin Source File

SOURCE=.\DebugFrame.h
# End Source File
# Begin Source File

SOURCE=.\EditBox.h
# End Source File
# Begin Source File

SOURCE=.\EditEventDlg.h
# End Source File
# Begin Source File

SOURCE=.\EventBrowser.h
# End Source File
# Begin Source File

SOURCE=.\EventEditor.h
# End Source File
# Begin Source File

SOURCE=.\globals.h
# End Source File
# Begin Source File

SOURCE=.\Graph.h
# End Source File
# Begin Source File

SOURCE=.\GraphFrame.h
# End Source File
# Begin Source File

SOURCE=.\GroupPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\LoginDialog.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapFrame.h
# End Source File
# Begin Source File

SOURCE=.\MapView.h
# End Source File
# Begin Source File

SOURCE=.\NetSummaryFrame.h
# End Source File
# Begin Source File

SOURCE=.\NewUserDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\nms_common.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\nms_util.h
# End Source File
# Begin Source File

SOURCE=.\NodePropsGeneral.h
# End Source File
# Begin Source File

SOURCE=.\NodeSummary.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\nxclapi.h
# End Source File
# Begin Source File

SOURCE=.\nxcon.h
# End Source File
# Begin Source File

SOURCE=.\ObjectBrowser.h
# End Source File
# Begin Source File

SOURCE=.\ObjectInfoBox.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPreview.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPropCaps.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPropsGeneral.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\ObjectPropsSecurity.h
# End Source File
# Begin Source File

SOURCE=.\ObjectSearchBox.h
# End Source File
# Begin Source File

SOURCE=.\PasswordChangeDlg.h
# End Source File
# Begin Source File

SOURCE=.\RequestProcessingDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ThresholdDlg.h
# End Source File
# Begin Source File

SOURCE=.\ToolBox.h
# End Source File
# Begin Source File

SOURCE=.\UserEditor.h
# End Source File
# Begin Source File

SOURCE=.\UserPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserSelectDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icons\Alarms.ICO
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\icons\board.ico
# End Source File
# Begin Source File

SOURCE=.\res\down_arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\icons\EARTH.ICO
# End Source File
# Begin Source File

SOURCE=.\icons\event.ico
# End Source File
# Begin Source File

SOURCE=.\icons\graph.ico
# End Source File
# Begin Source File

SOURCE=.\icons\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\login.bmp
# End Source File
# Begin Source File

SOURCE=.\icons\NetMap.ICO
# End Source File
# Begin Source File

SOURCE=.\icons\node.ico
# End Source File
# Begin Source File

SOURCE=.\res\nxcon.ico
# End Source File
# Begin Source File

SOURCE=.\res\nxcon.rc2
# End Source File
# Begin Source File

SOURCE=.\icons\passwd.ico
# End Source File
# Begin Source File

SOURCE=.\icons\RuleManager.ico
# End Source File
# Begin Source File

SOURCE=.\icons\setup.ico
# End Source File
# Begin Source File

SOURCE=.\res\sort_up.bmp
# End Source File
# Begin Source File

SOURCE=.\icons\sort_up.ico
# End Source File
# Begin Source File

SOURCE=.\icons\sortdown.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\icons\tree.ico
# End Source File
# Begin Source File

SOURCE=.\res\up_arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\icons\user.ico
# End Source File
# Begin Source File

SOURCE=.\icons\users.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
