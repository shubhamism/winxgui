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


#if !defined(SWC_BCHEADER_H_INCLUDED_)
#define SWC_BCHEADER_H_INCLUDED_


/////////////////////////////////////////////////////////////////////////////
// CGuiHeaderCtrl window

class CHeaderView : public CHeaderCtrl
{
// Construction
public:
	//*******************************************************
	CHeaderView();
	virtual ~CHeaderView();
	//*******************************************************
protected:
	CWin		m_pParentWnd;
	COLORREF	m_clrFace;
	COLORREF	m_clrShadow;
	COLORREF	m_clrLight;
	CSize		m_sizeImag;
	CImageCtrl  m_img;
	int			m_nNumbottomSelect;
	BOOL		m_bSentido;
	BOOL		m_bMouserOver;
	int			m_selected;
	CFont		m_cfontNormal;
	CFont		m_cfontBold;
public:
	//***********************************************************************
	void SetImageCol(int icol,int img);
	void ReDraw(); 
	void BiselaBoton(CRect rcWin,CGDI* pDC);
	void SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void ClearImages();
	void DelImageCol(int icol);
	void DrawTextExt(LPCSTR Cad,CGDI* pDC,CRect* rc);
	void DrawArrow(CGDI* pDC,CRect rc,BOOL bUp);
	void SetSortColumn(int nCol,BOOL sentido);
	int  GetSortColumn(BOOL* bSortCol );
	virtual void PreSubClassWnd();
	void OnTimer(UINT nIDEvent);
	BOOL OnSetCursor(HWND hWnd, UINT nHitTest, UINT message);
	

	//***********************************************************************	
public:


	virtual BOOL DrawItem(HDITEM hdi,CGDI* pDC);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnPaint(HDC hDC);
	void OnWindowPosChanged(LPWINDOWPOS lParam);
	BOOL OnEraseBkgnd(HDC pDC);
	BOOL OnLButtonDown(UINT nFlags, CPoint pt);

	
protected:
	BEGIN_MSG_MAP()
	ON_WM_CREATE(OnCreate)
	ON_WM_PAINT(OnPaint)
	ON_WM_ERASEBKGND(OnEraseBkgnd)
	ON_WM_WINDOWPOSCHANGED(OnWindowPosChanged)
	ON_WM_DRAWITEM(OnDrawItem)
	ON_WM_SETCURSOR(OnSetCursor)
	ON_WM_TIMER(OnTimer)
	ON_WM_LBUTTONDOWN(OnLButtonDown) 
	END_MSG_MAP(CHeaderCtrl)
};

/////////////////////////////////////////////////////////////////////////////


#endif 