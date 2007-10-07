/*
 * 
 *
 * Copyright 2007 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/


#pragma once


// CSplitter

class  CSplitter : public CWin
{
public:
	enum TYPEALING {ALINGHORZ=0,ALINGVERT=1};
	enum STYLESEPARATOR{STYLE3D=0,STYLEFLAT=1};
	void SetColor(COLORREF m_clrface);
	void AddLeftCtrl(CWin* pWnd,long MinSize);
	void AddRightCtrl(CWin* pWnd,long MinSize);
	CWin* GetLeft()
	{
		if (HIWORD(pWndLeft))
			return pWndLeft;
		return NULL;
	}
	CWin* GetRight()
	{
		if (HIWORD(pWndRight))
			return pWndRight;
		return NULL;
	}
	void SeTypeALing(TYPEALING typeAling);
	void SetPixelWidht(int nSizePix);
	void RecalLayout();
	virtual void DrawSplitter(CRect rcSeparator,CRect rcLeft,CRect rcRight,CGDI* pDC);
	void SetStyleSeparator(STYLESEPARATOR StyleSeparator=STYLEFLAT,COLORREF clrLeftTop=CDrawLayer::GetRGBColorShadow(),
							COLORREF clrBottomRight=CDrawLayer::GetRGBColorShadow());

public:
	
	//-----------------------
	 BOOL Create(CWin* pParentWnd);
	 int OnCreate(LPCREATESTRUCT lpCreateStruct);
	 BOOL OnPaint(HDC hDC);
	 void OnLButtonDown(UINT nFlags, CPoint pt);
	 void OnLButtonUp(UINT nFlags, CPoint pt);
	 void OnMouseMove(UINT nFlags, CPoint pt);
	 BOOL OnSize(UINT nType, int cx, int cy);
	 BOOL OnSysColorChange();
	 BOOL OnSetCursor(HWND hWnd, UINT nHitTest, UINT message);
	//-----------------------
public:
	CSplitter();
	virtual ~CSplitter();
protected:
	COLORREF	clrBg;
	CWin*		pWndLeft;
	CWin*		pWndRight;
	TYPEALING	TypeAling;
	CRect		m_rcSpplitter;
	int			m_nSizePix;
	CRect		m_rcSpplitterOld;
	BOOL		bIniciaArrastre;
	STYLESEPARATOR mStyleSeparator;
	COLORREF	mclrLeftTop;
	COLORREF	mclrBottomRight;
	CRect		m_rectLeft;
	CRect		m_rectRight;

protected:
	BEGIN_MSG_MAP()
	ON_WM_CREATE(OnCreate)
	ON_WM_PAINT(OnPaint)
	ON_WM_LBUTTONDOWN(OnLButtonDown)
	ON_WM_MOUSEMOVE(OnMouseMove)
	ON_WM_LBUTTONUP(OnLButtonUp)
	ON_WM_SIZE(OnSize)
	ON_WM_SYSCOLORCHANGE(OnSysColorChange)
	ON_WM_SETCURSOR(OnSetCursor)
	END_MSG_MAP(CWin)
	
};

