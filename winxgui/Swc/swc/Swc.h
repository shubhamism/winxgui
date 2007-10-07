/*
 * swc.h	1.0		23/09/2004
 *
 * Copyright 2005 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms.
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 *  you should include all new headers class in thi header
 *
 *****/


#ifndef __SWC_H
#define __SWC_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <shellapi.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commctrl.h>
#include <commdlg.h>
#include <Time.h>
#include <resource.h>

#define BASE_STATUS_BAR  		0x999111
#define BASE_TOOLTIPS_CLASS 	0x9112
#define BASE_TOOLBAR_CLASS  	0x9113
#define ID_MDI_FIRSTCHILD   	0x5000
#define IDC_HSPLITBAR           30980       // splitter
#define IDC_VSPLITBAR           30981       // splitter
#define RT_TOOLBAR				MAKEINTRESOURCE(241)
#define DOCK_VERT				0x999922
#define DOCK_HORZ				0x999923
#define DOCK_LEFT				0x999924
#define DOCK_RIGHT				0x999925
#define DOCK_TOP				0x999926
#define DOCK_BOTTOM				0x999927

#define BS_FLOATING			0x00234
#define BS_DOCKING			0x00235
#define BS_DOCKINGTAB		0x00236
#define BS_DOCKINGLEFT		0x00237
#define BS_DOCKINGRIGHT		0x00238
#define BS_DOCKINGBOTTOM	0x00239


#define WINNT     0x01
#define WIN2000   0x02
#define WINXP     0x03


class CApp;
_declspec(selectany) CApp* theApp=0;
#include "CMacrodefine.h"
#include "CGdi.h"
#include "NewBConfig.h"
#include "NewBValArray.h"
#include "CWin.h"
#include "CApp.h"
#include "resource1.h"
#include "CDialogControls.h"
#include "CCommonCtrl.h"
#include "CComboboxExt.h"
#include "CMenuSpawn.h"
#include "CSplitter.h"
#include "CToolButton.h"
#include "CFrame.h"
#include "CContainer.h"
#include "CWorkTab.h"
#include "CTabbed.h"
#include "CHeaderCtrl.h"
//#include "CDockManager.h"
#include "CFolder.h"
#include "CMMedia.h"
#include "COutLook.h"
#include "CMainFrame.h"

#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED           0x00080000
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#endif // ndef WS_EX_LAYERED


#pragma comment(lib, "comctl32.lib")

#endif