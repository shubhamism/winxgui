/* This is a part of the Simple Windows Class.
 * Copyright (C) 2005 Francisco Campos G.
 * All rights reserved.
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/


#if !defined(C_DIALOGCONTROLS_H__191265517913803_INCLUDED_)
#define C_DIALOGCONTROLS_H__191265517913803_INCLUDED_


/*
 *
 *   CComboBox
 **/


class CComboBox : public CWin
{
public:

	CComboBox(HWND hWnd = NULL) : CWin(hWnd) { }
	virtual ~CComboBox(){};

	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0),LPVOID lpParam=NULL)
	{
		BOOL rs= CWin::Create(_T("combobox"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}


	void GetDroppedControlRect(LPRECT lprect) 
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( CB_GETDROPPEDCONTROLRECT, 0L, (LPARAM)lprect);
	}
	
	BOOL GetDroppedState() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( CB_GETDROPPEDSTATE, 0L, 0L);
	}
	
	int GetCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_GETCOUNT, 0L, 0L);
	}
	int GetCurSel() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_GETCURSEL, 0L, 0L);
	}
	
	WORD GetLocale() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (WORD)SendMessage( CB_GETLOCALE, 0L, 0L);
	}
	
	int GetLBText(int nIndex, LPTSTR lpszText) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_GETLBTEXT, nIndex, (LPARAM)lpszText);
	}

	int GetLBTextLen(int nIndex) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_GETLBTEXTLEN, nIndex, 0L);
	}

	int GetItemHeight(int nIndex) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_GETITEMHEIGHT, nIndex, 0L);
	}
	
	int GetTopIndex() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_GETTOPINDEX, 0L, 0L);
	}
	int SetTopIndex(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_SETTOPINDEX, nIndex, 0L);
	}
	BOOL GetExtendedUI() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( CB_GETEXTENDEDUI, 0L, 0L);
	}
	int  GetHorizontalExtent() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)SendMessage( CB_GETHORIZONTALEXTENT, 0L, 0L);
	}
	DWORD GetItemData(int nIndex) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)SendMessage( CB_GETITEMDATA, nIndex, 0L);
	}
	DWORD GetEditSel() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)SendMessage( CB_GETEDITSEL, 0L, 0L);
	}
	void SetHorizontalExtent(UINT nExtent)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( CB_SETHORIZONTALEXTENT, nExtent, 0L);
	}
	int GetDroppedWidth() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_GETDROPPEDWIDTH, 0L, 0L);
	}
	int SetDroppedWidth(int nWidth)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_SETDROPPEDWIDTH, nWidth, 0L);
	}


	
	BOOL SetEditSel(int nStart,  int nEnd)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( CB_SETEDITSEL, 0L, MAKELONG(nStart, nEnd));
	}

	int SetCurSel(int nSelect)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_SETCURSEL, nSelect, 0L);
	}
	
	int SetItemData(int nIndex, DWORD dwIdata)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_SETITEMDATA, nIndex, (LPARAM)dwIdata);
	}
	
	WORD SetLocale(WORD wLocale)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (WORD)SendMessage( CB_SETLOCALE, (WPARAM)wLocale, 0L);
	}
	
	int SetItemHeight(int nIndex, UINT cyIheight)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_SETITEMHEIGHT, nIndex, MAKELONG(cyIheight, 0));
	}
	
	int SetExtendedUI(BOOL bExtended = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_SETEXTENDEDUI, bExtended, 0L);
	}
	


	int InitStorage(int nItems, UINT nBytes)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_INITSTORAGE, (WPARAM)nItems, nBytes);
	}
	void ResetContent()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( CB_RESETCONTENT, 0L, 0L);
	}

	BOOL LimitText(int nChars)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( CB_LIMITTEXT, nChars, 0L);
	}

	void ShowDropDown(BOOL bShow = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( CB_SHOWDROPDOWN, bShow, 0L);
	}

	int AddString(LPCTSTR lpszString)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_ADDSTRING, 0L, (LPARAM)lpszString);
	}
	int DeleteString(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_DELETESTRING, nIndex, 0L);
	}
	int InsertString(int nIndex, LPCTSTR lpszString)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_INSERTSTRING, nIndex, (LPARAM)lpszString);
	}
	int Dir(int attr, LPCTSTR lpszWildCard)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_DIR, attr, (LPARAM)lpszWildCard);
	}

	int FindString(int nStartAfter, LPCTSTR lpszString) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_FINDSTRING, nStartAfter, (LPARAM)lpszString);
	}
	int FindStringExact(int nIndexStart, LPCTSTR lpszFind) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_FINDSTRINGEXACT, nIndexStart, (LPARAM)lpszFind);
	}
	int SelectString(int nStartAfter, LPCTSTR lpszString)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( CB_SELECTSTRING, nStartAfter, (LPARAM)lpszString);
	}

	void Clear()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( WM_CLEAR, 0L, 0L);
	}
	void Copy()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( WM_COPY, 0L, 0L);
	}
	void Cut()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( WM_CUT, 0L, 0L);
	}
	void Paste()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( WM_PASTE, 0L, 0L);
	}
};

/*
 *
 *   CStatic
 **/


class CStatic : public CWin
{
public:

	CStatic(HWND hWnd = NULL) : CWin(hWnd) { }
	virtual ~CStatic(){};
public:
	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0),LPVOID lpParam=NULL)
	{
		BOOL rs= CWin::Create(_T("static"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}

	HCURSOR GetCursor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HCURSOR)SendMessage( STM_GETIMAGE, IMAGE_CURSOR, 0L);
	}
	
	HICON GetIcon() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HICON)SendMessage( STM_GETICON, 0L, 0L);
	}
	
	HBITMAP GetBitmap() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HBITMAP)SendMessage( STM_GETIMAGE, IMAGE_BITMAP, 0L);
	}
	

	HENHMETAFILE GetEnhMetaFile() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HENHMETAFILE)SendMessage( STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L);
	}
	
	HCURSOR SetCursor(HCURSOR hCursor)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HCURSOR)SendMessage( STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);
	}

	HICON SetIcon(HICON hIcon)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HICON)SendMessage( STM_SETICON, (WPARAM)hIcon, 0L);
	}

	HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HENHMETAFILE)SendMessage( STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);
	}
	HBITMAP SetBitmap(HBITMAP hBitmap)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HBITMAP)SendMessage( STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	}
	
};

/*
 *
 *   CButton
 **/


class CButton : public CWin
{
	public:
		CButton(HWND hWnd=NULL) :CWin(hWnd) {}
		virtual ~CButton(){};
	public:
		
	
	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0),LPVOID lpParam=NULL)
	{
		BOOL rs= CWin::Create(_T("button"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}
	
	int GetCheck() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage(BM_GETCHECK, 0L, 0L);
	}
	
	void SetCheck(int nCheck)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(BM_SETCHECK, nCheck, 0L);
	}
	
	
	int GetState() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage(BM_GETSTATE, 0L, 0L);
	}
	
	void SetState(BOOL bState)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(BM_SETSTATE, bState, 0L);
	}
	
	int GetButtonStyle()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)GetWindowLong(m_hWnd,GWL_STYLE) & 0xff;
	}
	void SetButtonStyle(UINT style, BOOL redraw = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(BM_SETSTYLE, style, (LPARAM)redraw);
	}

	HICON GetIcon() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HICON)SendMessage(BM_GETIMAGE, IMAGE_ICON, 0L);
	}
	HICON SetIcon(HICON hIcon)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HICON)SendMessage(BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
	}
     
	int GetCheckBox() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return ( int ) SendMessage( BM_GETCHECK, 0L, 0L );
	}
	
	void SetCheckBox( UINT nCheck = BST_CHECKED )
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( BM_SETCHECK, nCheck,0L );
	}

	BOOL IsCheckBox()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) GetCheck() == BST_CHECKED;
	}
	
	virtual BOOL OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		return FALSE;
	}
	

	
};

/*
 *
 *   CCheckBox
 **/


class CCheckBox: public CButton
{
public:
	CCheckBox(HWND hWnd=NULL) :CButton(hWnd) {}
	virtual ~CCheckBox(){};
public:		
	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0L),LPVOID lpParam=NULL)
	{
		dwStyle|=WS_BORDER | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX;
		BOOL rs= CWin::Create(_T("button"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}	
	
		
};


/*
 *
 *   CRadioButton
 **/

class CRadioButton: public CButton
{
public:
	CRadioButton(HWND hWnd=NULL) :CButton(hWnd) {}
	virtual ~CRadioButton(){};
public:		
	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0L),LPVOID lpParam=NULL)
	{
		dwStyle|=WS_BORDER | WS_TABSTOP | WS_VISIBLE | BS_AUTORADIOBUTTON;
		BOOL rs= CWin::Create(_T("button"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}	
	
};

/*
 *
 *   CGroupButton
 **/


class CGroupButton: public CButton
{
public:
	CGroupButton(HWND hWnd=NULL) :CButton(hWnd) {}
	virtual ~CGroupButton(){};
public:		
	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0L),LPVOID lpParam=NULL)
	{
		dwStyle|=WS_BORDER | WS_TABSTOP | WS_VISIBLE | BS_GROUPBOX;
		BOOL rs= CWin::Create(_T("button"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}	
	
};



/*
 *
 *   CEdit
 **/


class CEdit : public CWin
{
public:

	CEdit(HWND hWnd = NULL) : CWin(hWnd) { }
	virtual ~CEdit(){};

public:
	
	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0),LPVOID lpParam=NULL)
	{
		BOOL rs= CWin::Create(_T("edit"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}
	
	
	void Paste()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(WM_PASTE, 0L, 0L);
	}
	
	void Copy()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(WM_COPY, 0L, 0L);
	}

	BOOL Undo()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage(EM_UNDO, 0L, 0L);
	}
	void Clear()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(WM_CLEAR, 0L, 0L);
	}
	
	void Cut()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(WM_CUT, 0L, 0L);
	}
	
	int CanUndo()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) SendMessage(EM_CANUNDO, 0L, 0L);
	}
	
	int GetLineCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage(EM_GETLINECOUNT, 0L, 0L);
	}
	
	int GetModify()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage(EM_GETMODIFY, 0L, 0L);
	}
	
	void SetModify(BOOL bModified = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(EM_SETMODIFY, bModified, 0L);
	}
	
	void GetRect(LPRECT lpRect) 
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_GETRECT, 0L, (LPARAM)lpRect);
	}
	
	DWORD GetSel() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)SendMessage( EM_GETSEL, 0L, 0L);
	}
	void GetSel(DWORD& dwStart, DWORD& dwEnd) 
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
	}
	HLOCAL GetHandle() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HLOCAL)SendMessage( EM_GETHANDLE, 0L, 0L);
	}
	void SetHandle(HLOCAL hBuffer)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETHANDLE, (WPARAM)hBuffer, 0L);
	}
	DWORD GetMargins() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)SendMessage( EM_GETMARGINS, 0L, 0L);
	}
	void SetMargins(UINT nLeft, UINT nRight,UINT nFlag=EC_LEFTMARGIN|EC_RIGHTMARGIN)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETMARGINS, nFlag, MAKELONG(nLeft, nRight));
	}
	UINT GetLimitText() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)SendMessage( EM_GETLIMITTEXT, 0L, 0L);
	}
	void SetLimitText(UINT nLimit)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETLIMITTEXT, nLimit, 0L);
	}
	
	
	int GetLine(int nIndex, LPTSTR lpszBuffer) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}
	int GetLine(int nIndex, LPTSTR lpszBuffer, int nMaxLength) 
	{
		ASSERT(::IsWindow(m_hWnd));
		*(LPWORD)lpszBuffer = (WORD)nMaxLength;
		return (int)SendMessage( EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}

	TCHAR GetPasswordChar() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (TCHAR)SendMessage( EM_GETPASSWORDCHAR, 0L, 0L);
	}
	void SetPasswordChar(TCHAR ch)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETPASSWORDCHAR, ch, 0L);
	}
	
	int GetFirstVisibleLine() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( EM_GETFIRSTVISIBLELINE, 0L, 0L);
	}
	int GetThumb() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( EM_GETTHUMB, 0L, 0L);
	}

	BOOL SetReadOnly(BOOL bReadOnly = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( EM_SETREADONLY, bReadOnly, 0L);
	}


	void EmptyUndoBuffer()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_EMPTYUNDOBUFFER, 0L, 0L);
	}
	BOOL FmtLines(BOOL bAddEOL=TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( EM_FMTLINES, bAddEOL, 0L);
	}
	void GetLimitText(int nChars = 0)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_LIMITTEXT, nChars, 0L);
	}
	int LineFromChar(int nIndex = -1) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( EM_LINEFROMCHAR, nIndex, 0L);
	}
	int LineIndex(int nLine = -1) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( EM_LINEINDEX, nLine, 0L);
	}
	int LineLength(int nLength) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( EM_LINELENGTH, nLength, 0L);
	}
	void LineScroll(int ncxLines, int ncyScroll)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_LINESCROLL, ncxLines, ncyScroll);
	}
	void ReplaceSel(LPCTSTR pszNewText, BOOL bCanUndo = FALSE)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)pszNewText);
	}
	void SetRect(LPCRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETRECT, 0L, (LPARAM)lpRect);
	}
	void SetRectNP(LPCRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETRECTNP, 0L, (LPARAM)lpRect);
	}
	void SetSel(DWORD dwSelection, BOOL bNoScroll = FALSE)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETSEL, LOWORD(dwSelection), HIWORD(dwSelection));
		if(!bNoScroll)
			SendMessage( EM_SCROLLCARET, 0L, 0L);
	}
	void SetSel(DWORD dwStartChar, DWORD dwEndChar)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETSEL, dwStartChar, dwEndChar);
		
	}
	
	BOOL SetTabStops(int nTabStops, LPINT rgTabStops)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( EM_SETTABSTOPS, nTabStops, (LPARAM)rgTabStops);
	}
	BOOL SetTabStops()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( EM_SETTABSTOPS, 0L, 0L);
	}

	BOOL SetTabStops( int cTab, LPDWORD lpTabs)    
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( EM_SETTABSTOPS, cTab, (LPARAM)lpTabs);
	}
	void ScrollCaret()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SCROLLCARET, 0L, 0L);
	}
	int Scroll(int nScroll)
	{
		ASSERT(::IsWindow(m_hWnd));
		return SendMessage( EM_SCROLL, nScroll, 0L);
		
		
	}

	EDITWORDBREAKPROC GetWordBreakProc() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (EDITWORDBREAKPROC)SendMessage( EM_GETWORDBREAKPROC, 0L, 0L);
	}

	void SetWordBreakProc(EDITWORDBREAKPROC edtWProc)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( EM_SETWORDBREAKPROC, 0L, (LPARAM)edtWProc);
	}
		
};


/*
 *
 *   CListBox
 **/

class CListBox : public CWin
{
public:

	
	CListBox(HWND hWnd = NULL) : CWin(hWnd) { }
	virtual ~CListBox(){};
public:
	
	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0),LPVOID lpParam=NULL)
	{
		BOOL rs= CWin::Create(_T("listbox"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}
	
	int GetSelCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETSELCOUNT, 0L, 0L);
	}
	int GetSelItems(int nCount, LPINT pIndex) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETSELITEMS, nCount, (LPARAM)pIndex);
	}
	int GetAnchorIndex() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETANCHORINDEX, 0L, 0L);
	}
	int GetSel(int nIndex)           
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETSEL, nIndex, 0L);
	}
	int GetCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETCOUNT, 0L, 0L);
	}
	int GetCurSel() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETCURSEL, 0L, 0L);
	}
	int GetHorizontalExtent() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETHORIZONTALEXTENT, 0L, 0L);
	}
	int GetTopIndex() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETTOPINDEX, 0L, 0L);
	}
	int GetLocale() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETLOCALE, 0L, 0L);
	}
	DWORD GetItemData(int nIndex) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)SendMessage( LB_GETITEMDATA, nIndex, 0L);
	}
	
	int GetCaretIndex() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETCARETINDEX, 0L, 0);
	}
	int SetCaretIndex(int nIndex, BOOL bScroll = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_SETCARETINDEX, nIndex, MAKELONG(bScroll, 0));
	}

		
	int SetItemData(int nIndex, DWORD dwData)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_SETITEMDATA, nIndex, (LPARAM)dwData);
	}
	
	int GetItemRect(int nIndex, LPRECT lpRect) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETITEMRECT, nIndex, (LPARAM)lpRect);
	}
	int GetText(int nIndex, LPTSTR lpszText) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETTEXT, nIndex, (LPARAM)lpszText);
	}


	int GetTextLen(int nIndex) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETTEXTLEN, nIndex, 0L);
	}
	int GetItemHeight(int nIndex) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_GETITEMHEIGHT, nIndex, 0L);
	}
	int SetItemHeight(int nIndex, int cyIheight)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_SETITEMHEIGHT, nIndex, MAKELONG(cyIheight, 0));
	}

	void SetHorizontalExtent(int nHextent)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( LB_SETHORIZONTALEXTENT, nHextent, 0L);
	}
	
	int SetCount(int nCount)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_SETCOUNT, nCount, 0L);
	}
	int SetTopIndex(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_SETTOPINDEX, nIndex, 0L);
	}
	
	WORD SetLocale(WORD nLocale)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (WORD)SendMessage( LB_SETLOCALE, (WPARAM)nLocale, 0L);
	}

		
	int SetCurSel(int nSelect)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_SETCURSEL, nSelect, 0L);
	}

		
	int SetSel(int nIndex, BOOL bSelect = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_SETSEL, bSelect, nIndex);
	}
	
	void SetAnchorIndex(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( LB_SETANCHORINDEX, nIndex, 0L);
	}
	
	void SetColumnWidth(int nWidth)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( LB_SETCOLUMNWIDTH, nWidth, 0L);
	}
	BOOL SetTabStops(int nTab, LPINT pTab)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( LB_SETTABSTOPS, nTab, (LPARAM)pTab);
	}
	BOOL SetTabStops()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage( LB_SETTABSTOPS, 0L, 0L);
	}
	
	int InitStorage(int nItems, int nBytes)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_INITSTORAGE, (WPARAM)nItems, nBytes);
	}
	void ResetContent()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( LB_RESETCONTENT, 0L, 0L);
	}
	int ItemFromPoint(int nXpos, int nYpos) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return  (DWORD)SendMessage( LB_ITEMFROMPOINT, 0L, MAKELPARAM(nXpos, nYpos));
	}

	int AddString(LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_ADDSTRING, 0L, (LPARAM)lpszItem);
	}
	int DeleteString(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_DELETESTRING, nIndex, 0L);
	}
	int InsertString(int nIndex, LPCTSTR lpszString)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_INSERTSTRING, nIndex, (LPARAM)lpszString);
	}
	int Dir(UINT attr, LPCTSTR lpszFile)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_DIR, attr, (LPARAM)lpszFile);
	}
	int AddFile(LPCTSTR lpstrFileName)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_ADDFILE, 0L, (LPARAM)lpstrFileName);
	}

	int FindString(int nStart, LPCTSTR lpszItem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_FINDSTRING, nStart, (LPARAM)lpszItem);
	}
	int FindStringExact(int nIndex, LPCTSTR lpszFind) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_FINDSTRINGEXACT, nIndex, (LPARAM)lpszFind);
	}
	int SelectString(int nStartAfter, LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage( LB_SELECTSTRING, nStartAfter, (LPARAM)lpszItem);
	}
	int SelItemRange( int nStart, int nEnd,BOOL bSelect=TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return  (int)SendMessage( LB_SELITEMRANGEEX, bSelect, MAKELPARAM( nStart, nEnd )) ;
	}
};

/*
 *
 *   CScrollBar
 **/


class CScrollBar : public CWin
{
public:

	CScrollBar(HWND hWnd = NULL) : CWin(hWnd) { }
	virtual ~CScrollBar(){};
public:
	BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
	   DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0),LPVOID lpParam=NULL)
	{
		BOOL rs= CWin::Create(_T("scrollbar"),lpWindowName,
		   dwStyle,rc,hwndParent,nID,lpParam);
		SubclassWnd(GetSafeHwnd());
		return rs;
	}

	
	void GetRange(int& nMin, int& nMax) 
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( SBM_GETRANGE, ( WPARAM )&nMin, ( LPARAM )&nMax );
	}
	int GetPos() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return ( int )SendMessage( SBM_GETPOS, 0L, 0L );
	}
	int SetPos(int nPos, BOOL bRedraw = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return ( int )SendMessage( SBM_SETPOS, nPos, bRedraw );
	}
	
	void SetRange(int nMin, int nMax, BOOL bRedraw = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( bRedraw ? SBM_SETRANGEREDRAW : SBM_SETRANGE, nMin, nMax );
	}
	
	int SetInfo(LPSCROLLINFO lpScrollInfo)
	{
		ASSERT(::IsWindow(m_hWnd));
		return ( BOOL )SendMessage( SBM_GETSCROLLINFO, 0L, ( LPARAM )lpScrollInfo );
	}
	

	BOOL EnableScrollBar(int nFlags = ESB_ENABLE_BOTH)
	{
		ASSERT(::IsWindow(m_hWnd));
		return ( BOOL )SendMessage( SBM_ENABLE_ARROWS, nFlags,0L );
		
	}

};



/*
 *	CDialog class
 *
 **/

class CDialog : public CWin
{
public:
	CDialog(HWND hWnd=NULL) :CWin(hWnd)
	{bDialog=TRUE;}
	~CDialog()
	{}
protected:
		BOOL LoopMsg;
		int  rsMsg;
public:

	LRESULT Run()
	{
		MSG msg;
		BOOL bPeekMsg=TRUE;
		LoopMsg=TRUE;
		while ( LoopMsg && ::GetMessage(&msg, NULL, 0, 0) ) 
		{
			if ( msg.hwnd == NULL ) continue;
			if ( msg.message == WM_QUIT )
			{
				LoopMsg=FALSE;
				::PostQuitMessage(( int )msg.wParam );
				
				break;
			}
			//bresult=(!TranslateAccelerator (msg.hwnd, theApp->GetAccelTable(), &msg));
			CWin* pActive= reinterpret_cast<CWin*>(::GetWindowLong(msg.hwnd,GWL_USERDATA)); 
			BOOL bPre=TRUE;
			if (pActive)
				bPre=pActive->PreTranslateMessage(&msg);
			if (bPre) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		return  rsMsg;
	}



	int DoModal( CWin* pParent, LPCTSTR pszDialogName )
	{
		HWND hFocus = ::GetFocus();
		if ( !Create( pParent==NULL?NULL:pParent, pszDialogName ))
			 return FALSE;
		ShowWindow();
		UpdateWindow();
		if ( pParent && pParent->IsWindowEnabled())
		{
			pParent->EnableWindow( FALSE );
		}
		int resp=Run();
		if ( pParent )
		{
		   pParent->EnableWindow( TRUE );
		   pParent->SetForegroundWindow();
		}

		int nResult=0;
		::DestroyWindow(GetSafeHwnd());
		if ( hFocus ) 
			::SetFocus( hFocus );
		return resp;
	}

	LRESULT DefWindowProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam)
	{
		return 0;  //sin uso
	}


	int DoModal( LPCTSTR pszDialogName )
	{
		return DoModal(NULL,pszDialogName);
	}


	BOOL Create( CWin* pParent,LPCTSTR pszDialogName )
	{
		if ( !::CreateDialogParam( GetModuleHandle(NULL), pszDialogName, pParent->GetSafeHwnd(),
			   (DLGPROC)WndProc, ( LPARAM )this))
			return FALSE;
		return TRUE;
	}
		

		
	BOOL EndDialog( int nResult )
	{
		LoopMsg=FALSE;
		rsMsg=nResult;
		return TRUE;
	}

		// Overidables.
	virtual BOOL OnOK()
	{
		EndDialog(IDOK);
		return TRUE;
	}

	virtual BOOL OnCancel()
	{
		EndDialog(IDCANCEL);
		return TRUE;
	}

	virtual BOOL OnInitDialog(HWND wParam,LPARAM lParam)
	{
		return TRUE;
	}

	
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return TRUE;
	}
	
	void MapDialogRect(LPRECT lpRect) 
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		::MapDialogRect(m_hWnd, lpRect); 
	}

	void CDialog::NextDlgCtrl() 
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		::SendMessage(m_hWnd, WM_NEXTDLGCTL, 0, 0); 
	}

	void CDialog::PrevDlgCtrl() 
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		::SendMessage(m_hWnd, WM_NEXTDLGCTL, 1, 0); 
	}

	void CDialog::GotoDlgCtrl(CWin* pWndCtrl)
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		::SendMessage(m_hWnd, WM_NEXTDLGCTL, (WPARAM)pWndCtrl->GetSafeHwnd(), 1L); 
	}

	void CDialog::SetDefID(UINT nID)
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		::SendMessage(m_hWnd, DM_SETDEFID, nID, 0); 
	}

	DWORD CDialog::GetDefID() 
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		return ::SendMessage(m_hWnd, DM_GETDEFID, 0, 0); 
	}
	
BEGIN_MSG_MAP()
	ON_WM_INITDIALOG(OnInitDialog)
END_MSG_MAP(CWin)
};



/*
 * simple wrapper of common dialog tools, they are not include HOOK procedures
 *
 *   CFileOpen
 **/

class CFileOpen : public CDialog 
{
protected:
	OPENFILENAME ofn;
public:
	CFileOpen(CWin *pWin, LPCTSTR lpszDefExt = NULL,
			LPCTSTR lpszFileName = NULL,LPCSTR title=NULL,LPCSTR lpFilter=NULL,LPCSTR lpInitialDir=NULL,
			DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT)
	{
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = pWin->GetSafeHwnd();
		ofn.lpstrFilter = (LPSTR)lpFilter;
		ofn.lpstrFile = (LPSTR)lpszFileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = lpszDefExt;
		ofn.lpstrInitialDir=(LPSTR)lpInitialDir;
		ofn.Flags |= dwFlags | OFN_EXPLORER | OFN_ENABLEHOOK | OFN_ENABLESIZING;
		ofn.nMaxFileTitle = _MAX_FNAME;
	}
	
	int	DoModal(BOOL bOpenFile=TRUE)
	{ 	
		BOOL bRet;
		
		if(bOpenFile)
			bRet = ::GetOpenFileName(&ofn);
		else
			bRet = ::GetSaveFileName(&ofn);

		m_hWnd = NULL;
		
		if (bRet) return IDOK;
		
		return  IDCANCEL;
	
	}

	
	int GetFilePath(LPTSTR lpstrFilePath, int nLength) 
	{
		return (int)SendMessage(CDM_GETFILEPATH, nLength, (LPARAM)lpstrFilePath);
	}

	int GetFolderIDList(LPVOID lpBuff, int nLength) 
	{
		return (int)SendMessage(CDM_GETFOLDERIDLIST, nLength, (LPARAM)lpBuff);
	}

	int GetFolderPath(LPTSTR lpstrFolderPath, int nLength) 
	{
		return (int)SendMessage(CDM_GETFOLDERPATH, nLength, (LPARAM)lpstrFolderPath);
	}

	int GetSpec(LPTSTR lpstrSpec, int nLength)
	{
		return (int)SendMessage(CDM_GETSPEC, nLength, (LPARAM)lpstrSpec);
	}

	void SetControlText(int nCtrlID, LPCTSTR lpstrText)
	{
		SendMessage(CDM_SETCONTROLTEXT, nCtrlID, (LPARAM)lpstrText);
	}

	void SetDefExt(LPCTSTR lpstrExt)
	{
		SendMessage(CDM_SETDEFEXT, 0, (LPARAM)lpstrExt);
	}

	BOOL GetReadOnlyPref() 	
	{
		return (ofn.Flags & OFN_READONLY) ? TRUE : FALSE;
	}

	/*void HideControl(int nCtrlID)
	{
		SendMessage(CDM_HIDECONTROL, nCtrlID);
	}*/
	void setFilter(LPCSTR lpFilter)
	{
		if (lpFilter) 
			ofn.lpstrFilter=(LPSTR)lpFilter; 
	}
	
	void setDir(LPCSTR lpdir)
	{
		ofn.lpstrInitialDir=(LPSTR)lpdir; 
	}
		
	
};


/*
 *
 *   CColorDialog
 **/


class  CColorDialog 
{
  CHOOSECOLOR m_cc;

public:
	CColorDialog(COLORREF clrInit = 0, DWORD dwFlags = 0, HWND hWndParent = NULL)
	{
		memset(&m_cc, 0, sizeof(m_cc));

		m_cc.lStructSize = sizeof(m_cc);
		m_cc.hwndOwner = hWndParent;
		m_cc.Flags = dwFlags | CC_ENABLEHOOK;
		if(clrInit != 0)
		{
			m_cc.rgbResult = clrInit;
			m_cc.Flags |= CC_RGBINIT;
		}
	}

	~CColorDialog(){};
public:
	
	int DoModal(CWin* pWin)
	{

		if(m_cc.hwndOwner == NULL)	
			m_cc.hwndOwner = pWin->GetSafeHwnd();
		BOOL bRet = ::ChooseColor(&m_cc);
		if (bRet)
			return IDOK;
		return  IDCANCEL;
	}

	COLORREF GetColor() 
	{
		return m_cc.rgbResult;
	}

};


/*
 *
 *   CPrintDialog
 **/


class  CPrintDialog 
{
public:
	PRINTDLG m_pd;

public:
	CPrintDialog(CWin* pParent = NULL,BOOL bSetup = FALSE,
			DWORD dwFlags = PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_NOSELECTION	)
	{
		memset(&m_pd, 0, sizeof(PRINTDLG));
		m_pd.lStructSize = sizeof(PRINTDLG);
		m_pd.hwndOwner = pParent->GetSafeHwnd();
		m_pd.Flags = dwFlags ;
		if(bSetup)
			m_pd.Flags |= PD_PRINTSETUP;
		else
			m_pd.Flags |= PD_RETURNDC;

		m_pd.Flags &= ~PD_RETURNIC; 
	}
	
	~CPrintDialog(){ DeleteDC(m_pd.hDC);}

public:
	
	int  DoModal(CWin* pParent)
	{
		
		if(m_pd.hwndOwner == NULL)		
			m_pd.hwndOwner = pParent->GetSafeHwnd();

		BOOL bRet = ::PrintDlg(&m_pd);
		if(bRet)
			return IDOK;
		return  IDCANCEL;
	}

	BOOL GetDefaults()
	{
		m_pd.Flags |= PD_RETURNDEFAULT;
		ASSERT(m_pd.hDevMode == NULL && m_pd.hDevNames == NULL)
		return ::PrintDlg(&m_pd);
	}

	int GetCopies()
	{
		return m_pd.nCopies;
	}
	BOOL PrintCollate() 
	{
		return (m_pd.Flags & PD_COLLATE) ? TRUE : FALSE;
	}
	BOOL PrintSelection() 
	{
		return (m_pd.Flags & PD_SELECTION) ? TRUE : FALSE;
	}
	
	BOOL PrintRange() 
	{
		return (m_pd.Flags & PD_PAGENUMS) ? TRUE : FALSE;
	}
	int GetFromPage() 
	{
		return m_pd.nFromPage ;
	}
	int GetToPage() 
	{
		return m_pd.nToPage ;
	}
	LPDEVMODE GetDevMode()
	{
		if(m_pd.hDevMode == NULL)
			return NULL;

		return (LPDEVMODE)::GlobalLock(m_pd.hDevMode);
	}
	LPCTSTR GetDriverName() 
	{
		if(m_pd.hDevNames == NULL)
			return NULL;

		LPDEVNAMES lpDev = (LPDEVNAMES)::GlobalLock(m_pd.hDevNames);
		if(lpDev == NULL)
			return NULL;

		return (LPCTSTR)lpDev + lpDev->wDriverOffset;
	}
	LPCTSTR GetDeviceName()
	{
		if(m_pd.hDevNames == NULL)
			return NULL;

		LPDEVNAMES lpDev = (LPDEVNAMES)::GlobalLock(m_pd.hDevNames);
		if(lpDev == NULL)
			return NULL;

		return (LPCTSTR)lpDev + lpDev->wDeviceOffset;
	}
	LPCTSTR GetPortName() 
	{
		if(m_pd.hDevNames == NULL)
			return NULL;

		LPDEVNAMES lpDev = (LPDEVNAMES)::GlobalLock(m_pd.hDevNames);
		if(lpDev == NULL)
			return NULL;

		return (LPCTSTR)lpDev + lpDev->wOutputOffset;
	}
	HDC GetPrinterDC() 
	{
		ASSERT(m_pd.Flags & PD_RETURNDC);
		return m_pd.hDC;
	}

};


/*
 *
 *   CFontDialog
 **/



class  CFontDialog 
{
	CHOOSEFONT m_choosefont;
	TCHAR m_szStyle[64];	

public:
	

	CFontDialog(CWin* pWin=NULL, COLORREF clrColor=RGB(0,0,0),DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS)
	{
		memset(&m_choosefont, 0, sizeof(m_choosefont));
		memset(&m_szStyle, 0, sizeof(m_szStyle));
		m_choosefont.lStructSize = sizeof(m_choosefont);
		m_choosefont.hwndOwner = pWin->GetSafeHwnd();
		m_choosefont.rgbColors =clrColor;
		m_choosefont.Flags = dwFlags ;
		m_choosefont.lpszStyle = (LPTSTR)&m_szStyle;
		
	}

public:
	int  DoModal(CWin* pParent)
	{
		if(m_choosefont.hwndOwner == NULL)		
		m_choosefont.hwndOwner = pParent->GetSafeHwnd();
		BOOL bRet = ::ChooseFont(&m_choosefont);
		if (bRet) return IDOK;
		return IDCANCEL;
	}

	void GetCurrentFont(LPLOGFONT lpfont) 
	{
		if(lpfont != NULL)
		::SendMessage(m_choosefont.hwndOwner, WM_CHOOSEFONT_GETLOGFONT, 0, (LPARAM)lpfont);
	}
	
	LPCTSTR GetFaceName() 
	{
		return (LPCTSTR)m_choosefont.lpLogFont->lfFaceName;
	}
	LPCTSTR GetStyleName() 
	{
		return m_choosefont.lpszStyle;
	}
	int GetPointSize() 
	{
		return m_choosefont.iPointSize;
	}
	COLORREF GetColors() 
	{
		return m_choosefont.rgbColors;
	}
	int GetWeight() 
	{
		return (int)m_choosefont.lpLogFont->lfWeight;
	}
	BOOL IsStrikeOut() 
	{
		return (m_choosefont.lpLogFont->lfStrikeOut) ? TRUE : FALSE;
	}
	BOOL IsUnderline() 
	{
		return (m_choosefont.lpLogFont->lfUnderline) ? TRUE : FALSE;
	}
	BOOL IsBold() 
	{
		return (m_choosefont.lpLogFont->lfWeight == FW_BOLD) ? TRUE : FALSE;
	}
	BOOL IsItalic() 
	{
		return m_choosefont.lpLogFont->lfItalic ? TRUE : FALSE;
	}
};





#endif // !defined(C_DIALOGCONTROLS_H__191265517913803_INCLUDED_)