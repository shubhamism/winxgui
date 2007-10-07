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


#include "stdafx.h"



// CSplitter



CSplitter::CSplitter()
{
	TypeAling=ALINGHORZ;
	m_nSizePix=2;
	mStyleSeparator=STYLE3D;
	bIniciaArrastre=FALSE;
	clrBg=CDrawLayer::GetRGBColorFace();
	mclrLeftTop=CDrawLayer::GetRGBColorBTNHigh();
	mclrBottomRight=CDrawLayer::GetRGBColorShadow();
	m_rectLeft=CRect(0,0,0,0);
	m_rectRight=CRect(0,0,0,0);
}

CSplitter::~CSplitter()
{
}



void CSplitter::SeTypeALing(TYPEALING typeAling)
{
	TypeAling=typeAling;
	m_rcSpplitter=CRect(0,0,0,0);
	Invalidate();
	UpdateWindow();
}


// CSplitter message handlers
void CSplitter::SetColor(COLORREF m_clrface)
{
	clrBg=m_clrface;
}

int CSplitter::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// TODO:  Add your specialized creation code here

	return 0;
}


BOOL CSplitter::Create(CWin* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	LPTSTR lpclassname=RegisterDefaultClass(NULL,WS_CHILD|WS_VISIBLE);
	return CWin::Create(lpclassname,NULL, WS_VISIBLE|WS_CHILD, CRect(0,0,0,0), pParentWnd->GetSafeHwnd(), 0xffff);
}


BOOL CSplitter::OnPaint(HDC hDC)
{
	CPaintDC dc(GetSafeHwnd()); // device context for painting
	CBrush cbr;
	CRect rcClient;
	GetClientRect(&rcClient);
	cbr.CreateSolidBrush(clrBg);
	
	CGDI		MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(dc.m_hDC);
	m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,rcClient.Width(),rcClient.Height());	
	
	CBitmap *m_bitmapOld=new CBitmap(MemDC.SelectObject(&m_BitmapMemDC));
	
	MemDC.FillRect(&rcClient,&cbr);
	DrawSplitter(m_rcSpplitter,m_rectLeft,m_rectRight,&MemDC);
	
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	cbr.DeleteObject();
	dc.DeleteDC();
	m_bitmapOld->DeleteObject();
	delete m_bitmapOld;
	return TRUE;
}

void CSplitter::SetPixelWidht(int nSizePix)
{
	m_nSizePix=nSizePix;
}

void  CSplitter::AddLeftCtrl(CWin* pWnd,long MinSize)
{
	ASSERT(pWnd);
	pWndLeft=pWnd;
}

void  CSplitter::AddRightCtrl(CWin* pWnd,long MinSize)
{
	ASSERT(pWnd);
    pWndRight=pWnd;
	RecalLayout();
}

void CSplitter::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_rcSpplitter.PtInRect(point) && !bIniciaArrastre)
		{
			bIniciaArrastre=TRUE;		
			SetCapture ();
			InvalidateRect(m_rcSpplitter,TRUE);
		}
}

void CSplitter::OnLButtonUp(UINT nFlags, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if (bIniciaArrastre==TRUE)
		{
			bIniciaArrastre=FALSE;
			RecalLayout();
			ReleaseCapture ();	
			Invalidate();
		}
}



void CSplitter::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect m_rectCli;
	GetClientRect(m_rectCli);
    if (bIniciaArrastre==TRUE)
    {
		m_rcSpplitterOld=m_rcSpplitter;
		if (TypeAling==ALINGHORZ)
		{
			if (point.x < m_rectCli.left) 
				m_rcSpplitter.left=m_rectCli.left+m_nSizePix;
			else if (point.x >m_rectCli.right)
				m_rcSpplitter.left=m_rectCli.right-m_nSizePix;
			else 
			{
				m_rcSpplitter.left=	point.x;
				m_rcSpplitter.right=point.x+m_nSizePix;
			}
		}
		else
		{
			if (point.y < m_rectCli.top) 
				m_rcSpplitter.top=m_rectCli.top+m_nSizePix;
			else if (point.y >m_rectCli.bottom)
				m_rcSpplitter.bottom=m_rectCli.top-m_nSizePix;
			else 
			{
				m_rcSpplitter.top=point.y;
				m_rcSpplitter.bottom=point.y+m_nSizePix;
			}	
		}
		CClientDC dc(GetSafeHwnd());
		InvalidateRect(m_rcSpplitterOld);
		RecalLayout();
		dc.DeleteDC();
	}
}

BOOL CSplitter::OnSize(UINT nType, int cx, int cy)
{
	RecalLayout();
	return TRUE;
	// TODO: Add your message handler code here
}

void  CSplitter::RecalLayout()
{
	CRect m_rectCli;
	CRect m_rctemp;
	GetClientRect(m_rectCli);
	if (m_rectCli.IsRectEmpty()) return;

	if ((pWndLeft== NULL || pWndRight==NULL) || 
		(pWndLeft->IsWindowVisible()==FALSE || pWndRight->IsWindowVisible()==FALSE)){
		if (pWndLeft== NULL || pWndRight==NULL)
		{
			if (pWndLeft== NULL && pWndRight==NULL)
				return;
			else if (pWndLeft==NULL)
			{
				if (pWndLeft->IsWindowVisible())
					pWndLeft->MoveWindow(m_rectCli);
			}
			else
			{
				if (pWndRight->IsWindowVisible())
					pWndRight->MoveWindow(m_rectCli);
			}
		}
		else if (pWndLeft->IsWindowVisible()==FALSE || pWndRight->IsWindowVisible()==FALSE)
		{
			if (pWndLeft->IsWindowVisible()==FALSE && pWndRight->IsWindowVisible()==FALSE)
				return;
			else if (pWndLeft->IsWindowVisible())
			{
				if (pWndLeft!=NULL)
					pWndLeft->MoveWindow(m_rectCli);
			}
			else
			{
				if (pWndRight!=NULL)
					pWndRight->MoveWindow(m_rectCli);
			}
		}
		::SendMessage(GetParent(),WM_SIZE,0,0);
		return ;
	}
		
	if (m_rcSpplitter.left < m_rectCli.left ) m_rcSpplitter.left=m_rectCli.left+1;
	if (m_rcSpplitter.right > m_rectCli.right) m_rcSpplitter.right=m_rectCli.right-1;
	if (m_rcSpplitter.bottom > m_rectCli.bottom) m_rcSpplitter.bottom=m_rectCli.bottom-1;
	if (m_rcSpplitter.top < m_rectCli.top) m_rcSpplitter.top=m_rectCli.top+1;
	if (m_rcSpplitter.IsRectEmpty() || m_rcSpplitter.bottom >=5000 )
	{
		m_rcSpplitter=m_rectCli;
		if (TypeAling==ALINGHORZ)	
		{
			m_rcSpplitter.right=m_rectCli.Width()/2;
			m_rcSpplitter.left=m_rcSpplitter.right-m_nSizePix;	
		}
		else
		{
			m_rcSpplitter.bottom=m_rectCli.Height()/2;
			m_rcSpplitter.top=m_rcSpplitter.bottom-m_nSizePix;	
		}
	}
	
	if (TypeAling==ALINGHORZ)
	{
		m_rcSpplitter.right=m_rcSpplitter.left+m_nSizePix;
		m_rcSpplitter.bottom=m_rectCli.bottom;
	}
	else
	{
		m_rcSpplitter.bottom=m_rcSpplitter.top+m_nSizePix;	
		m_rcSpplitter.right=m_rectCli.right;
	}

	m_rctemp=m_rectCli;
	if (TypeAling==ALINGHORZ)
		m_rctemp.right=m_rcSpplitter.left-1;
	else
		m_rctemp.bottom=m_rcSpplitter.top-1;
	m_rectLeft=m_rctemp;
	m_rctemp.DeflateRect(1,1);
	pWndLeft->MoveWindow(m_rctemp);
	pWndLeft->Invalidate();
	pWndLeft->UpdateWindow();
	m_rctemp=m_rectCli;
	if (TypeAling==ALINGHORZ)
		m_rctemp.left=m_rcSpplitter.right+1;
	else
		m_rctemp.top=m_rcSpplitter.bottom+1;
	m_rectRight=m_rctemp;
	m_rctemp.DeflateRect(1,1);
	pWndRight->MoveWindow(m_rctemp);
	pWndRight->Invalidate();
	pWndRight->UpdateWindow();
	

}

BOOL CSplitter::OnSysColorChange()
{
	// TODO: Add your message handler code here
	return TRUE;
}

BOOL CSplitter::OnSetCursor(HWND hWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptCurPos;
	GetCursorPos (&ptCurPos);
	ScreenToClient (&ptCurPos);

	if (m_rcSpplitter.PtInRect (ptCurPos))
	{
		if(TypeAling==ALINGHORZ)
			SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZEWE)));
		else if(TypeAling==ALINGVERT)
			SetCursor(LoadCursor (NULL,MAKEINTRESOURCE(IDC_SIZENS)));
		return TRUE;
	}
	SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW)));
	return TRUE;
}

void CSplitter::SetStyleSeparator(STYLESEPARATOR StyleSeparator,COLORREF clrLeftTop,COLORREF clrBottomRight)
	
{
	mStyleSeparator=StyleSeparator;
	mclrLeftTop=clrLeftTop;
	mclrBottomRight=clrBottomRight;
}

void CSplitter::DrawSplitter(CRect rcSeparator,CRect rcLeft,CRect rcRight,CGDI* pDC)
{
	if (mStyleSeparator == STYLE3D)
	{
		pDC->Draw3dRect(rcLeft,mclrLeftTop,mclrBottomRight);
		pDC->Draw3dRect(rcRight,mclrLeftTop,mclrBottomRight);
	}
	else
	{
		pDC->Draw3dRect(rcLeft,CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
		pDC->Draw3dRect(rcRight,CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
	}
	

}
