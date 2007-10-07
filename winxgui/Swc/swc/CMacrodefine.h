/*
 * CMacroDefine.h	1.0  23/09/2003
 *
 * Copyright 2005 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms.
 * I´m understand no many people is agree with the macro instruction, however
 * I think that it is include in the languaje for some reason. 
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 *
 *****/


#if !defined(C_MACRODEFINE_H__INCLUDED_)
#define C_MACRODEFINE_H__INCLUDED_


#pragma once
#include <stdio.h>

class CPoint; //we will need it


#ifdef DEBUG
#	define ASSERT (object)	((void)((object) || (AssertDebug(#object,__FILE__,__LINE__),1)))
#else
#	define ASSERT(nothing)	((void)0);
#endif

#define RT_TOOLBAR  MAKEINTRESOURCE(241)

#if defined(_MSC_VER) && _MSC_VER <= 1200
#define sprintf_s	sprintf
#endif

void AssertDebug(LPCSTR msg, LPCSTR file, unsigned line)
{

	char buf[80];
	sprintf_s(buf,"at line %u in file %s: \"%s\"",line,file,msg);
	if (MessageBox(NULL,buf,"ASSERTION FAILURE",
			MB_OKCANCEL|MB_ICONSTOP|MB_TASKMODAL)!=IDOK)
		exit(-1);
}




/*
 *  <class> class CMsg </Class>
 *  <Description> This Class define the NewMsgProc a virtual messages handle   
 *	How to Use->   class Myclass : public CMsg
 *  </Description>
 *  <Author> Francisco Campos </Author>
 *  <Version> 23/09/2003 v 1.0 </Version>
 *  <Modified>  </Modified>
 *****/

class CMsg
{

	/*
	 *  <Function> class CMsg </Function>
	 *  <Description> 
	 *   Al Window's messages will be mapped in this function
	 *   </Description>
	 *  <return> TRUE/FALSE </return>
	 *****/
public:

	virtual BOOL NewMsgProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam,LRESULT lResult)
	{
		return FALSE;
	}
};



 
/*
 *  <Macro> BEGIN_MSG_MAP </Macro>
 *  <Description> 
 *   Esta macro envuelve los mensajes basicos de windows, como puede observarse se emula el sistema mensajes de MFC
 *  </Description>
 *  <return>br/FASLSE </return>
 *****/

#define BEGIN_MSG_MAP() \
public: \
	virtual BOOL NewMsgProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam,LRESULT& lResult) \
	{ \
		
#define ON_MESSAGE(Msg, vfunc) \
	if(uID == Msg) \
	{ \
		vfunc(uID, wParam, lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_MESSAGE_RANGE(MsgF, MsgL, vfunc) \
	if(uID >= MsgF && uID <= MsgL) \
	{ \
		lResult=vfunc(uID, wParam, lParam); \
		return TRUE; \
	}

#define ON_COMMAND_CONTROL(iControl, iEvent, vfunc) \
	if(uID == WM_COMMAND && iControl == LOWORD(wParam) && iEvent == HIWORD(wParam)) \
	{ \
		vfunc(HIWORD(wParam), LOWORD(wParam), (HWND)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_COMMAND( iEvent, vfunc) \
	if(uID == WM_COMMAND && iEvent == LOWORD(wParam)) \
	{ \
		vfunc(HIWORD(wParam), LOWORD(wParam), (HWND)lParam); \
		lResult=0;\
		return TRUE; \
	}
#define ON_REFLECTED_NOTIFY(iEvent, func) \
	if (uID == WM_NOTIFY && iEvent == ((LPNMHDR)lParam)->code) \
	{ \
		lResult = func((LPNMHDR)lParam); \
		return lResult; \
	}
#define ON_NOTIFY(iControl, iEvent, vfunc) \
	if(uID == WM_NOTIFY && iControl == ((LPNMHDR)lParam)->iControlFrom && iEvent == ((LPNMHDR)lParam)->code) \
	{ \
		lResult = vfunc((int)wParam, (LPNMHDR)lParam); \
		return TRUE; \
	}

#define ON_NOTIFY_ID(iControl, vfunc) \
	if(uID == WM_NOTIFY && iControl == ((LPNMHDR)lParam)->iControlFrom) \
	{ \
		lResult = vfunc((int)wParam, (LPNMHDR)lParam); \
		return TRUE; \
	}

#define ON_NOTIFY_CODE(iEvent, vfunc) \
	if(uID == WM_NOTIFY && iEvent == ((LPNMHDR)lParam)->code) \
	{ \
		lResult = vfunc((int)wParam, (LPNMHDR)lParam); \
		return TRUE; \
	}

#define ON_NOTIFY_RANGE(iControlFirst, iControlLast, vfunc) \
	if(uID == WM_NOTIFY && ((LPNMHDR)lParam)->iControlFrom >= iControlFirst && ((LPNMHDR)lParam)->iControlFrom <= iControlLast) \
	{ \
		lResult = vfunc((int)wParam, (LPNMHDR)lParam); \
		return TRUE; \
	}

#define ON_WM_CREATE(vfunc)\
	if (uID == WM_CREATE) \
	{ \
		lResult =  vfunc((LPCREATESTRUCT)lParam); \
		return TRUE;\
	}

#define ON_WM_DESTROY(vfunc)\
	if (uID == WM_DESTROY) \
	{ \
		vfunc(); \
		lResult =0;\
		return TRUE;\
	}

#define ON_WM_CLOSE(vfunc)\
	if (uID == WM_CLOSE) \
	{ \
		lResult =vfunc(); \
		return lResult; \
	}

#define ON_WM_MOVE(vfunc)\
	if (uID == WM_MOVE) \
	{ \
		vfunc(CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult=0;\
		return TRUE; \
	}

#define ON_WM_SIZE(vfunc)\
	if (uID == WM_SIZE) \
	{ \
		vfunc((UINT)wParam,LOWORD(lParam),HIWORD(lParam)); \
		lResult=0;\
		return TRUE; \
	}

#define ON_WM_ACTIVATE(vfunc)\
	if (uID == WM_ACTIVATE) \
	{ \
		vfunc(LOWORD(wParam),HIWORD(wParam),(HWND) lParam); \
		lResult=0;\
		return TRUE; \
	}

#define ON_WM_SETFOCUS(vfunc)\
	if (uID == WM_SETFOCUS) \
	{ \
		vfunc((HWND)wParam); \
		lResult = 0; \
		return TRUE; \
	}


#define ON_WM_KILLFOCUS(vfunc)\
	if (uID == WM_KILLFOCUS) \
	{ \
		vfunc((HWND)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_ENABLE(vfunc)\
	if (uID == WM_ENABLE) \
	{ \
		vfunc((HWND)wParam); \
		lResult = 0; \
		return  br; \
	}

#define ON_WM_SETREDRAW(vfunc)\
	if (uID == WM_SETREDRAW) \
	{ \
		vfunc((HWND)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SETTEXT(vfunc)\
	if (uID == WM_SETTEXT) \
	{ \
		lResult = vfunc((LPARAM)(LPCTSTR)lparam); \
		return TRUE; \
	}

#define ON_WM_GETTEXT(vfunc)\
	if (uID == WM_GETTEXT) \
	{ \
		lResult = vfunc((WPARAM)wParam, (LPARAM) lParam); \
		return TRUE; \
	}

#define ON_WM_GETTEXTLENGTH(vfunc)\
	if (uID == WM_GETTEXTLENGTH) \
	{ \
		lResult = vfunc(); \
		return TRUE; \
	}

#define ON_WM_PAINT(vfunc)\
	if (uID == WM_PAINT) \
	{ \
		vfunc((HDC) wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_QUERYENDSESSION(vfunc)\
	if (uID == WM_QUERYENDSESSION) \
	{ \
		lResult = vfunc((UINT) wParam,lParam); \
		return TRUE; \
	}

#define ON_WM_QUIT(vfunc)\
	if (uID == WM_QUIT) \
	{ \
		vfunc((int) wParam); \
		lResult=0;\
		return TRUE; \
	}

#define ON_WM_QUERYOPEN(vfunc)\
	if (uID == WM_QUERYOPEN) \
	{ \
		lResult = vfunc(); \
		return TRUE; \
	}

#define ON_WM_ERASEBKGND(vfunc)\
	if (uID == WM_ERASEBKGND) \
	{ \
		lResult = vfunc((HDC) wParam); \
		return TRUE; \
	}

#define ON_WM_SYSCOLORCHANGE(vfunc)\
	if (uID == WM_SYSCOLORCHANGE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}


#define ON_WM_ENDSESSION(vfunc)\
	if (uID == WM_ENDSESSION) \
	{ \
		vfunc((BOOL) wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SHOWWINDOW(vfunc)\
	if (uID == WM_SHOWWINDOW) \
	{ \
		vfunc((BOOL) wParam,(int)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SETTINGCHANGE(vfunc)\
	if (uID == WM_SETTINGCHANGE) \
	{ \
		vfunc(wParam,(LPARAM) (LPCTSTR) Param); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_DEVMODECHANGE(vfunc)\
	if (uID == WM_DEVMODECHANGE) \
	{ \
		vfunc((LPCTSTR) lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_ACTIVATEAPP(vfunc)\
	if (uID == WM_ACTIVATEAPP) \
	{ \
		vfunc((BOOL) wParam,(DWORD) lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_FONTCHANGE(vfunc)\
	if (uID == WM_FONTCHANGE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_TIMECHANGE(vfunc)\
	if (uID == WM_TIMECHANGE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_CANCELMODE(vfunc)\
	if (uID == WM_CANCELMODE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SETCURSOR(vfunc)\
	if (uID == WM_SETCURSOR) \
	{ \
		lResult =vfunc((HWND) wParam,LOWORD(lParam),HIWORD(lParam)); \
		return TRUE; \
	}

#define ON_WM_MOUSEACTIVATE(vfunc)\
	if (uID == WM_MOUSEACTIVATE) \
	{ \
		lResult =vfunc((HWND) wParam,CPoint(LOWORD(lParam),HIWORD(lParam))); \
		return TRUE; \
	}

#define ON_WM_CHILDACTIVATE(vfunc)\
	if (uID == WM_CHILDACTIVATE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_QUEUESYNC(vfunc)\
	if (uID == WM_QUEUESYNC) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_GETMINMAXINFO(vfunc)\
	if (uID == WM_GETMINMAXINFO) \
	{ \
		vfunc((LPMINMAXINFO)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_PAINTICON(vfunc)\
	if (uID == WM_PAINTICON) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_ICONERASEBKGND(vfunc)\
	if (uID == WM_ICONERASEBKGND) \
	{ \
		vfunc((HDC)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NEXTDLGCTL(vfunc)\
	if (uID == WM_NEXTDLGCTL) \
	{ \
		vfunc(wParam,(BOOL)LOWORD(lParam)); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SPOOLERSTATUS(vfunc)\
	if (uID == WM_SPOOLERSTATUS) \
	{ \
		vfunc(wParam,LOWORD(lParam)); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_DRAWITEM(vfunc)\
	if (uID == WM_DRAWITEM) \
	{ \
		vfunc((LPDRAWITEMSTRUCT)lParam); \
		lResult = 1; \
		return TRUE; \
	}

#define ON_WM_MEASUREITEM(vfunc)\
	if (uID == WM_MEASUREITEM) \
	{ \
		vfunc((LPMEASUREITEMSTRUCT)lParam); \
		lResult = 1; \
		return TRUE; \
	}

#define ON_WM_DELETEITEM(vfunc)\
	if (uID == WM_DELETEITEM) \
	{ \
		vfunc(wParam,(LPDELETEITEMSTRUCT)lParam); \
		lResult = 1; \
		return TRUE; \
	}

#define ON_WM_VKEYTOITEM(vfunc)\
	if (uID == WM_VKEYTOITEM) \
	{ \
		lResult =vfunc(LOWORD(wParam),HIWORD(wParam),lParam); \
		return TRUE; \
	}

#define ON_WM_CHARTOITEM(vfunc)\
	if (uID == WM_CHARTOITEM) \
	{ \
		lResult = vfunc(LOWORD(wParam),HIWORD(wParam),(HWND)lParam); \
		return TRUE; \
	}

#define ON_WM_SETFONT(vfunc)\
	if (uID == WM_SETFONT) \
	{ \
		vfunc(wParam,MAKELPARAM(lParam,0)); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_GETFONT(vfunc)\
	if (uID == WM_GETFONT) \
	{ \
		lResult = vfunc(); \
		return TRUE; \
	}

#define ON_WM_GETHOTKEY(vfunc)\
	if (uID == WM_GETHOTKEY) \
	{ \
		lResult = vfunc(); \
		return TRUE; \
	}

#define ON_WM_QUERYDRAGICON(vfunc)\
	if (uID == WM_QUERYDRAGICON) \
	{ \
		lResult =vfunc(); \
		return TRUE; \
	}

#define ON_WM_COMPAREITEM(vfunc)\
	if (uID == WM_COMPAREITEM) \
	{ \
		lResult =vfunc((LPCOMPAREITEMSTRUCT)lParam); \
		return TRUE; \
	}

#define ON_WM_COMPACTING(vfunc)\
	if (uID == WM_COMPACTING) \
	{ \
		vfunc((UINT)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_WINDOWPOSCHANGING(vfunc)\
	if (uID == WM_WINDOWPOSCHANGING) \
	{ \
		vfunc((LPWINDOWPOS)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_WINDOWPOSCHANGED(vfunc)\
	if (uID == WM_WINDOWPOSCHANGED) \
	{ \
		vfunc((LPWINDOWPOS)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_POWER(vfunc)\
	if (uID == WM_POWER) \
	{ \
		lResult = vfunc(wParam); \
		return TRUE; \
	}

#define ON_WM_COPYDATA(vfunc)\
	if (uID == WM_COPYDATA) \
	{ \
		lResult =vfunc((HWND)wParam,(PCOPYDATASTRUCT) lParam); \
		return TRUE; \
	}

#define ON_WM_CANCELJOURNAL(vfunc)\
	if (uID == WM_CANCELJOURNAL) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_INPUTLANGCHANGEREQUEST(vfunc)\
	if (uID == WM_INPUTLANGCHANGEREQUEST) \
	{ \
		vfunc((BOOL)wparam,(HKL) lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_INPUTLANGCHANGE(vfunc)\
	if (uID == WM_INPUTLANGCHANGE) \
	{ \
		vfunc(wParam,(HKL) lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_TCARD(vfunc)\
	if (uID == WM_TCARD) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_CONTEXTMENU(vfunc)\
	if (uID == WM_CONTEXTMENU) \
	{ \
		vfunc((HWND)wParam,CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_STYLECHANGING(vfunc)\
	if (uID == WM_STYLECHANGING) \
	{ \
		vfunc(wParam,(LPSTYLESTRUCT)lParam); \
		Result = 0; \
		return TRUE; \
	}

#define ON_WM_STYLECHANGED(vfunc)\
	if (uID == WM_STYLECHANGED) \
	{ \
		vfunc(wParam,(LPSTYLESTRUCT)lParam); \
		Result = 0; \
		return TRUE; \
	}

#define ON_WM_DISPLAYCHANGE(vfunc)\
	if (uID == WM_DISPLAYCHANGE) \
	{ \
		vfunc(wParam,CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_GETICON(vfunc)\
	if (uID == WM_GETICON) \
	{ \
		lResult = vfunc(wParam); \
		return TRUE; \
	}

#define ON_WM_SETICON(vfunc)\
	if (uID == WM_SETICON) \
	{ \
		lResult = vfunc(wParam,(LPARAM)(HICON)lParam); \
		return TRUE; \
	}


#define ON_WM_NCCREATE(vfunc)\
	if (uID == WM_NCCREATE) \
	{ \
		lResult =vfunc((LPCREATESTRUCT)lParam); \
		return TRUE; \
	}

#define ON_WM_NCDESTROY(vfunc)\
	if (uID == WM_NCDESTROY) \
	{ \
		vfunc((LPCREATESTRUCT)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCCALCSIZE(vfunc)\
	if (uID == WM_NCCALCSIZE) \
	{ \
		lResult = vfunc((BOOL) wParam,(LPNCCALCSIZE_PARAMS)lParam); \
		return TRUE; \
	}

#define ON_WM_NCHITTEST(vfunc)\
	if (uID == WM_NCHITTEST) \
	{ \
		lResult =vfunc(CPoint(LOWORD(lParam),HIWORD(lParam))); \
		return TRUE; \
	}

#define ON_WM_NCPAINT(vfunc)\
	if (uID == WM_NCPAINT) \
	{ \
		vfunc((HRGN) wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCACTIVATE(vfunc)\
	if (uID == WM_NCACTIVATE) \
	{ \
		lResult = vfunc((BOOL) wParam); \
		return TRUE; \
	}

#define ON_WM_GETDLGCODE(vfunc)\
	if (uID == WM_GETDLGCODE) \
	{ \
		lResult =vfunc((BOOL) wParam); \
		return TRUE; \
	}

#define ON_WM_SYNCPAINT(vfunc)\
	if (uID == WM_SYNCPAINT) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCMOUSEMOVE(vfunc)\
	if (uID == WM_NCMOUSEMOVE) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCLBUTTONDOWN(vfunc)\
	if (uID == WM_NCLBUTTONDOWN) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCLBUTTONUP(vfunc)\
	if (uID == WM_NCLBUTTONUP) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCLBUTTONDBLCLK(vfunc)\
	if (uID == WM_NCLBUTTONDBLCLK) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCRBUTTONDOWN(vfunc)\
	if (uID == WM_NCRBUTTONDOWN) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCRBUTTONUP(vfunc)\
	if (uID == WM_NCRBUTTONUP) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}


#define ON_WM_NCRBUTTONDBLCLK(vfunc)\
	if (uID == WM_NCRBUTTONDBLCLK) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCMBUTTONDOWN(vfunc)\
	if (uID == WM_NCMBUTTONDOWN) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCMBUTTONUP(vfunc)\
	if (uID == WM_NCMBUTTONUP) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NCMBUTTONDBLCLK(vfunc)\
	if (uID == WM_NCMBUTTONDBLCLK) \
	{ \
		vfunc((INT)wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_KEYDOWN(vfunc)\
	if (uID == WM_KEYDOWN) \
	{ \
		vfunc((int)wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_KEYUP(vfunc)\
	if (uID == WM_KEYUP) \
	{ \
		vfunc((int)wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_CHAR(vfunc)\
	if (uID == WM_CHAR) \
	{ \
		vfunc((TCHAR)wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_DEADCHAR(vfunc)\
	if (uID == WM_DEADCHAR) \
	{ \
		vfunc((TCHAR)wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SYSKEYDOWN(vfunc)\
	if (uID == WM_SYSKEYDOWN) \
	{ \
		vfunc((int)wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SYSKEYUP(vfunc)\
	if (uID == WM_SYSKEYUP) \
	{ \
		vfunc((int)wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SYSCHAR(vfunc)\
	if (uID == WM_SYSCHAR) \
	{ \
		vfunc((TCHAR)wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SYSDEADCHAR(vfunc)\
	if (uID == WM_SYSDEADCHAR) \
	{ \
		vfunc((TCHAR)wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_INITDIALOG(vfunc)\
	if (uID == WM_INITDIALOG) \
	{ \
		lResult =vfunc((HWND)wParam,lParam); \
		return TRUE; \
	}

#define ON_WM_SYSCOMMAND(vfunc)\
	if (uID == WM_SYSCOMMAND) \
	{ \
		vfunc(wParam,CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_TIMER(vfunc)\
	if (uID == WM_TIMER) \
	{ \
		vfunc((UINT)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_HSCROLL(vfunc)\
	if (uID == WM_HSCROLL) \
	{ \
		vfunc((int)LOWORD(wParam),(short int)HIWORD(wParam),(HWND)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_VSCROLL(vfunc)\
	if (uID == WM_VSCROLL) \
	{ \
		vfunc((int)LOWORD(wParam),(short int)HIWORD(wParam),(HWND)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_INITMENU(vfunc)\
	if (uID == WM_INITMENU) \
	{ \
		vfunc((HMENU)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_INITMENUPOPUP(vfunc)\
	if (uID == WM_INITMENUPOPUP) \
	{ \
		vfunc((HMENU)wParam,(UINT)LOWORD(lParam), (BOOL) HIWORD(lParam)); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MENUSELECT(vfunc)\
	if (uID == WM_MENUSELECT) \
	{ \
		vfunc((UINT)LOWORD(wParam),(UINT)HIWORD(lParam), (HMENU)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MENUCHAR(vfunc)\
	if (uID == WM_MENUCHAR) \
	{ \
		lResult = vfunc((TCHAR)LOWORD(wParam),(UINT)HIWORD(lParam), (HMENU)lParam); \
		return TRUE; \
	}

#define ON_WM_ENTERIDLE(vfunc)\
	if (uID == WM_ENTERIDLE) \
	{ \
		vfunc(wParam, (HMENU)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_CTLCOLOREDIT(vfunc)\
	if (uID == WM_CTLCOLOREDIT) \
	{ \
		lResult =vfunc((HDC)wParam, (HWND)lParam); \
		return TRUE; \
	}

#define ON_WM_CTLCOLORLISTBOX(vfunc)\
	if (uID == WM_CTLCOLORLISTBOX) \
	{ \
		lResult =vfunc((HDC)wParam, (HWND)lParam); \
		return TRUE; \
	}

#define ON_WM_CTLCOLORBTN(vfunc)\
	if (uID == WM_CTLCOLORBTN) \
	{ \
		lResult =vfunc((HDC)wParam, (HWND)lParam); \
		return TRUE; \
	}

#define ON_WM_CTLCOLORDLG(vfunc)\
	if (uID == WM_CTLCOLORDLG) \
	{ \
		lResult =vfunc((HDC)wParam, (HWND)lParam); \
		return TRUE; \
	}

#define ON_WM_CTLCOLORSCROLLBAR(vfunc)\
	if (uID == WM_CTLCOLORSCROLLBAR) \
	{ \
		lResult =vfunc((HDC)wParam, (HWND)lParam); \
		return TRUE; \
	}

#define ON_WM_CTLCOLORSTATIC(vfunc)\
	if (uID == WM_CTLCOLORSTATIC) \
	{ \
		lResult =vfunc((HDC)wParam, (HWND)lParam); \
		return TRUE; \
	}

#define ON_WM_MOUSEMOVE(vfunc)\
	if (uID == WM_MOUSEMOVE) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}


#define ON_WM_LBUTTONDOWN(vfunc)\
	if (uID == WM_LBUTTONDOWN) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}


#define ON_WM_LBUTTONUP(vfunc)\
	if (uID == WM_LBUTTONUP) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_LBUTTONDBLCLK(vfunc)\
	if (uID == WM_LBUTTONDBLCLK) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_RBUTTONDOWN(vfunc)\
	if (uID == WM_RBUTTONDOWN) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_RBUTTONUP(vfunc)\
	if (uID == WM_RBUTTONUP) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_RBUTTONDBLCLK(vfunc)\
	if (uID == WM_RBUTTONDBLCLK) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MBUTTONDOWN(vfunc)\
	if (uID == WM_MBUTTONDOWN) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MBUTTONUP(vfunc)\
	if (uID == WM_MBUTTONUP) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MBUTTONDBLCLK(vfunc)\
	if (uID == WM_MBUTTONDBLCLK) \
	{ \
		vfunc(wParam, CPoint(LOWORD(lParam),HIWORD(lParam))); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_PARENTNOTIFY(vfunc)\
	if (uID == WM_PARENTNOTIFY) \
	{ \
		vfunc(LOWORD(wParam), HIWORD(wParam), lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_ENTERMENULOOP(vfunc)\
	if (uID == WM_ENTERMENULOOP) \
	{ \
		vfunc((BOOL)wParam); \
		lResult = 0; \
		return TRUE; \
	}


#define ON_WM_EXITMENULOOP(vfunc)\
	if (uID == WM_EXITMENULOOP) \
	{ \
		vfunc((BOOL)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_NEXTMENU(vfunc)\
	if (uID == WM_NEXTMENU) \
	{ \
		vfunc((int)wParam,(LPMDINEXTMENU)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SIZING(vfunc)\
	if (uID == WM_SIZING) \
	{ \
		vfunc(wParam,(LPRECT)lParam); \
		lResult = 1; \
		return TRUE; \
	}

#define ON_WM_CAPTURECHANGED(vfunc)\
	if (uID == WM_CAPTURECHANGED) \
	{ \
		vfunc((HWND)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MOVING(vfunc)\
	if (uID == WM_MOVING) \
	{ \
		vfunc(wParam,(LPRECT)lParam); \
		lResult = 1; \
		return TRUE; \
	}

#define ON_WM_POWERBROADCAST(vfunc)\
	if (uID == WM_POWERBROADCAST) \
	{ \
		lResult = vfunc(wParam,(DWORD)lParam); \
		return TRUE; \
	}

#define ON_WM_DEVICECHANGE(vfunc)\
	if (uID == WM_DEVICECHANGE) \
	{ \
		lResult = vfunc((UINT)wParam,(DWORD)lParam); \
		return TRUE; \
	}

#define ON_WM_MDICREATE(vfunc)\
	if (uID == WM_MDICREATE) \
	{ \
		lResult =vfunc((LPARAM)(LPMDICREATESTRUCT)lParam); \
		return TRUE; \
	}

#define ON_WM_MDIDESTROY(vfunc)\
	if (uID == WM_MDIDESTROY) \
	{ \
		vfunc((WPARAM)(HWND)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MDIACTIVATE(vfunc)\
	if (uID == WM_MDIACTIVATE) \
	{ \
		vfunc((HWND) wParam,lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MDIRESTORE(vfunc)\
	if (uID == WM_MDIRESTORE) \
	{ \
		vfunc((HWND)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MDINEXT(vfunc)\
	if (uID == WM_MDINEXT) \
	{ \
		vfunc((WPARAM)(HWND)wParam,(LPARAM)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MDIMAXIMIZE(vfunc)\
	if (uID == WM_MDIMAXIMIZE) \
	{ \
		vfunc((HWND)wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MDITILE(vfunc)\
	if (uID == WM_MDITILE) \
	{ \
		lResult = vfunc((WPARAM)(UINT)wParam); \
		return TRUE; \
	}

#define ON_WM_MDICASCADE(vfunc)\
	if (uID == WM_MDICASCADE) \
	{ \
		lResult = vfunc((WPARAM)(UINT)wParam); \
		return TRUE; \
	}

#define ON_WM_MDIICONARRANGE(vfunc)\
	if (uID == WM_MDIICONARRANGE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MDIGETACTIVE(vfunc)\
	if (uID == WM_MDIGETACTIVE) \
	{ \
		lResult =vfunc((LPBOOL)lParam); \
		return TRUE; \
	}

#define ON_WM_MDISETMENU(vfunc)\
	if (uID == WM_MDISETMENU) \
	{ \
		lResult =vfunc((WPARAM)(HMENU)wParam,(LPARAM)(HMENU)lParam); \
		return TRUE; \
	}

#define ON_WM_ENTERSIZEMOVE(vfunc)\
	if (uID == WM_ENTERSIZEMOVE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_EXITSIZEMOVE(vfunc)\
	if (uID == WM_EXITSIZEMOVE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_MDIREFRESHMENU(vfunc)\
	if (uID == WM_MDIREFRESHMENU) \
	{ \
		lResult =vfunc(); \
		return TRUE; \
	}

#define ON_WM_CUT(vfunc)\
	if (uID == WM_CUT) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_COPY(vfunc)\
	if (uID == WM_COPY) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_PASTE(vfunc)\
	if (uID == WM_PASTE) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_CLEAR(vfunc)\
	if (uID == WM_CLEAR) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_UNDO(vfunc)\
	if (uID == WM_UNDO) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_RENDERFORMAT(vfunc)\
	if (uID == WM_RENDERFORMAT) \
	{ \
		vfunc((UINT) wParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_RENDERALLFORMATS(vfunc)\
	if (uID == WM_RENDERALLFORMATS) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_DESTROYCLIPBOARD(vfunc)\
	if (uID == WM_DESTROYCLIPBOARD) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_DRAWCLIPBOARD(vfunc)\
	if (uID == WM_DRAWCLIPBOARD) \
	{ \
		vfunc(); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_PAINTCLIPBOARD(vfunc)\
	if (uID == WM_PAINTCLIPBOARD) \
	{ \
		vfunc((HWND)param,(HGLOBAL)lParam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_VSCROLLCLIPBOARD(vfunc)\
	if (uID == WM_VSCROLLCLIPBOARD) \
	{ \
		vfunc((HWND)param,(int)LOWORD(lParam), (int)HIWORD(lParam)); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_SIZECLIPBOARD(vfunc)\
	if (uID == WM_SIZECLIPBOARD) \
	{ \
		vfunc((HWND)param,(HGLOBAL)lParam ); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_ASKCBFORMATNAME(vfunc)\
	if (uID == WM_ASKCBFORMATNAME) \
	{ \
		vfunc((DWORD)param,(LPTSTR)lParam ); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_CHANGECBCHAIN(vfunc)\
	if (uID == WM_CHANGECBCHAIN) \
	{ \
		vfunc((HWND)param,(HWND)lParam ); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_HSCROLLCLIPBOARD(vfunc)\
	if (uID == WM_HSCROLLCLIPBOARD) \
	{ \
		vfunc((HWND)param,(int)LOWORD(lParam),(int)HIWORD(lParam) ); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_QUERYNEWPALETTE(vfunc)\
	if (uID == WM_QUERYNEWPALETTE) \
	{ \
		lResult = vfunc(); \
		return TRUE; \
	}

#define ON_WM_PALETTEISCHANGING(vfunc)\
	if (uID == WM_PALETTEISCHANGING) \
	{ \
		vfunc((HWND)wparam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_PALETTECHANGED(vfunc)\
	if (uID == WM_PALETTECHANGED) \
	{ \
		vfunc((HWND)wparam); \
		lResult = 0; \
		return TRUE; \
	}

#define ON_WM_HOTKEY(vfunc)\
	if (uID == WM_HOTKEY) \
	{ \
		vfunc((int)wparam,(UINT)LOWORD(lParam),(UINT)HIWORD(lParam)); \
		lResult = 0; \
		return TRUE; \
	}

#define END_MSG_MAP_DEFAULT() \
		return FALSE; \
	} \

#define END_MSG_MAP(theBaseClass) \
		theBaseClass::NewMsgProc(hWnd,uID,wParam,lParam,lResult);\
		return FALSE; \
	} \

#endif // !defined(C_MACRODEFINE_H__INCLUDED_)