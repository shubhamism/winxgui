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
/////////////////////////////////////////////////////////////////////////////
// COutLook

COutLook::COutLook()
{
	m_ArrayButtons.RemoveAll();
	m_sizeImage=CSize(20,20);
	m_ActualButtonPres=-1;
	m_cbkg=::GetSysColor(COLOR_3DSHADOW);
	m_NumBottoms=0;
	m_mouseMove=-1;
	m_ultimoBotonResal=-1;
	m_Avance=0;    //avance del scroll
	m_iDrawFrameUp=FALSE;		//dibujar o no los botones arriba 
	m_iDrawFrameDown=FALSE;	    //y abajo
	m_bIsXp=FALSE;
	m_TypeOutLook=TRUE;
}

CItems::CItems(COutLook* pParent,HICON hIcon,UINT Cmd,LPCSTR szMessage,LPCSTR szToolTip,BOOL m_TypeLook)
{

	m_bt.Create(pParent->GetSafeHwnd(),Cmd, _T(""), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
		CRect(0,0,0,0));
	
	if (!m_TypeLook)
		m_bt.SetCaption(szMessage);
	m_bt.SethIcon(hIcon);
	m_bt.SetToolTip(szToolTip);
	m_szMessage=(LPSTR)szMessage;
	m_btipo=TRUE;
}

COutLook::~COutLook()
{

}


/////////////////////////////////////////////////////////////////////////////
// COutLook message handlers

BOOL COutLook::Create(DWORD dwStyle,  CRect& rect, CWin* pParentWnd, UINT nID) 
{
	mnID=nID;
	LPCTSTR lpclassname=RegisterDefaultClass(NULL,WS_CHILD|WS_VISIBLE|CS_HREDRAW|CS_VREDRAW);
	return CWin::Create(lpclassname,NULL, dwStyle|WS_VISIBLE|WS_CHILD, CRect(0,0,0,0), pParentWnd->GetSafeHwnd(), nID);
}

BOOL COutLook::PreTranslateMessage(MSG* pMsg) 
{
	return TRUE;
}



BOOL COutLook::OnEraseBkgnd(HDC hDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
}

BOOL COutLook::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int m_iNumBotton= m_ArrayButtons.GetSize();
	CClientDC  dc(this);
	m_bPressU=FALSE;
	m_bPressD=FALSE;
	
	if (m_iDrawFrameUp==TRUE)
	{
		if (m_rectArrowUp.PtInRect(point))
		{
			dc.DrawFrameControl(m_rectArrowUp,DFC_SCROLL,DFCS_SCROLLUP|DFCS_PUSHED);
			m_bPressU=TRUE;
			SetTimer(1,100,NULL);
			m_bPressU=FALSE;
		}
	}
	if (m_iDrawFrameDown==TRUE)
	{
		if (m_rectArrowDown.PtInRect(point))
		{
			dc.DrawFrameControl(m_rectArrowDown,DFC_SCROLL,DFCS_SCROLLDOWN|DFCS_PUSHED);
			m_bPressD=TRUE;
			SetTimer(1,100,NULL);
			m_bPressD=FALSE;
		}
	}
	return TRUE;
}

void COutLook::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		CPoint pt(GetMessagePos());
		CRect m_rc;
		ScreenToClient(&pt);
		GetClientRect(m_rc);
		if (!m_rc.PtInRect(pt))
		{
			KillTimer(1);
			CClientDC dc(this);
			if (m_bPressU==TRUE)
				dc.DrawFrameControl(m_rectArrowUp,DFC_SCROLL,DFCS_SCROLLUP);
			if (m_bPressD==TRUE)
				dc.DrawFrameControl(m_rectArrowDown,DFC_SCROLL,DFCS_SCROLLDOWN);
		}
	}
	
}

BOOL COutLook::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	//------------------------------
	if (m_iDrawFrameUp==TRUE)
	{
		if (m_rectArrowUp.PtInRect(point))
		{
			m_Avance+=50;		
			RecalLayout();		
		}
		else
			dc.DrawFrameControl(m_rectArrowUp,DFC_SCROLL,DFCS_SCROLLUP);
	}
	//-----------------------------
	if (m_iDrawFrameDown==TRUE)
	{
		if (m_rectArrowDown.PtInRect(point))
		{
			m_Avance-=50;
			RecalLayout();
		}
		else
			dc.DrawFrameControl(m_rectArrowDown,DFC_SCROLL,DFCS_SCROLLDOWN);
	}
	//------------------------------
	return TRUE;
}

void COutLook::RecalLayout()
{
	static int m_iLastHeigh=0; //se almacena el ultimo valor de altura del area cliente
	CRect rect;
	CRect m_rectC;
	GetClientRect(&m_rectC);
	CClientDC dc(this);
	int iMitad;
	int iMinRequerido=0;
	iMitad= m_rectC.Width()/2;
	iMitad-=(m_sizeImage.cx/2); //posición a partir del cual se pintan los botones
	iMitad--;
	m_iDrawFrameUp=FALSE;		//dibujar o no los botones arriba 
	m_iDrawFrameDown=FALSE;	    //y abajo
	
	int m_iNumBotton= m_ArrayButtons.GetSize();
{	for( int iCont=0; iCont< m_iNumBotton;iCont++)
	{
		CItems* cit=(CItems*)m_ArrayButtons[iCont];
		CSize sz=cit->m_bt.GetSizeButton();
		iMinRequerido+=sz.cy; //+18;
	}
}
	int iy=5+m_Avance; //a partir de esta posición se comienza a escribir
	//calculo real del espacio que ocuparan los botones
	CRect rcMsg;
	int iCont=0;
	for( iCont=0; iCont< m_iNumBotton;iCont++)
	{

		CItems* cit=(CItems*)m_ArrayButtons[iCont];
		if (m_TypeOutLook)
		{
			rect.left=iMitad;
			rect.top=iy;
			rect.bottom=rect.top+m_sizeImage.cy+6;
			rect.right=rect.left+m_sizeImage.cx+6;
			cit->m_bt.MoveWindow(rect);
			iy+=rect.Height()+18;
		}
		else
		{
			rect.left=m_rectC.left;
			rect.top=iy;
			rect.bottom=rect.top+m_sizeImage.cy+6;
			rect.right=m_rectC.right-20;
			cit->m_bt.MoveWindow(rect);
			iy+=rect.Height()+1;

		}

	}	
	
	
	DeleteDC(dc.m_hDC);
	if (iy > m_rectC.Height())
		m_iDrawFrameDown=TRUE;

	if (m_Avance < 0)
		m_iDrawFrameUp=TRUE;
	m_iLastHeigh=m_rectC.Height();
	Invalidate();
	UpdateWindow();

}


BOOL COutLook::OnSysColorChange() 
{
	//CWin::OnSysColorChange();
	int m_iNumBotton= m_ArrayButtons.GetSize();
	for( int iCont=0; iCont< m_iNumBotton;iCont++)
	{
		CItems* cit=(CItems*)m_ArrayButtons[iCont];
		cit->m_bt.SetColor(CDrawLayer::GetRGBColorXP());
	}
	Invalidate ();
	UpdateWindow ();
	return TRUE;
}

BOOL COutLook::OnSize(UINT nType, int cx, int cy) 
{
	//CWin::OnSize(nType, cx, cy);
	if (m_NumBottoms > 0)
		RecalLayout();
	return TRUE;
}


BOOL COutLook::OnCommand(WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND) lParam;	
	for (int i=0; i < m_NumBottoms+1;i++)
	{
		if (((CItems*) m_ArrayButtons [i])->m_bt.GetSafeHwnd()== hwnd)
			{
				int x=((CItems*) m_ArrayButtons [i])->m_bt.GetDlgCtrlID();
				CWin* pParent= (CWin*)GetParent();
			//	::SendMessage (pParent->GetSafeHwnd(),WM_COMMAND,x,0);
				::SendMessage (theApp->m_WinMain->GetSafeHwnd(),WM_COMMAND,x,0);
				return TRUE;
			}
	
	}
	return FALSE;

}

BOOL COutLook::OnPaint(HDC hDC) 
{
	CPaintDC dc(GetSafeHwnd()); // device context for painting
	CRect rect,rcClient;
	GetClientRect(&rect);
	CRect rcMsg;
	int iy=0;
	int m_iNumBotton= m_ArrayButtons.GetSize();
	int iMitad= rect.Width()/2;
	iMitad-=(m_sizeImage.cx/2); //posición a partir del cual se pintan los botones
	iMitad--;
	int nMode; 
	rcClient=rect;
	CBrush cbr;
	cbr.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
	
	CGDI			MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(dc.m_hDC);
	m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,
				  rect.Width(),rect.Height());	
	CBitmap m_bitmapOld=MemDC.SelectObject(&m_BitmapMemDC);

	MemDC.FillRect(&rect,&cbr);
	nMode  =MemDC.SetBkMode(TRANSPARENT);
	CFont cfont(MemDC.SelectObject((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	for( int iCont=0; iCont< m_iNumBotton;iCont++)
	{
		CItems* cit=(CItems*)m_ArrayButtons[iCont];
		CRect rcWin;
		cit->m_bt.GetWindowRect(rcWin);
		ScreenToClient(rcWin);
		rcMsg=rcWin;
		rcMsg.top=rcWin.bottom+2;
		rcMsg.bottom=rcMsg.top+16;
		rcMsg.left=rect.left;
		rcMsg.right=rect.right;
		if (m_TypeOutLook)
			MemDC.DrawText(cit->m_szMessage,rcMsg,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}	
	MemDC.SetBkMode(nMode);
	MemDC.SelectObject(cfont.GetFont());
	if (m_iDrawFrameUp==TRUE)
	{
		m_rectArrowUp.top=5;
		m_rectArrowUp.bottom=m_rectArrowUp.top+16;
		m_rectArrowUp.right=rect.right-5;
		m_rectArrowUp.left=m_rectArrowUp.right-16;
		MemDC.DrawFrameControl(m_rectArrowUp,DFC_SCROLL,DFCS_SCROLLUP);
	}
	if (m_iDrawFrameDown==TRUE)
	{
		m_rectArrowDown.bottom=rect.bottom-5;
		m_rectArrowDown.top=m_rectArrowDown.bottom-16;
		m_rectArrowDown.right=rect.right-5;
		m_rectArrowDown.left=m_rectArrowDown.right-16;
		MemDC.DrawFrameControl(m_rectArrowDown,DFC_SCROLL,DFCS_SCROLLDOWN);

	}


	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(&m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	return TRUE;	
}
void COutLook::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP hbmp;
	cbmp.LoadBitmap(theApp->GetInstance(),(LPCTSTR)nBitmapID);
	cbmp.GetBitmap(&hbmp);
	m_imageList.Create(nBitmapID,cx,nGrow,crMask);
	m_imageList.Add(&cbmp,crMask);
	m_sizeImage=CSize(cx,hbmp.bmHeight);
}

void  COutLook::AddItem(UINT Cmd,LPCSTR m_szCaption,int nIndex,LPCSTR m_ToolTip)
{
	m_ArrayButtons.SetAtGrow(m_NumBottoms, new CItems
			(this,m_imageList.ExtractIcon(nIndex),Cmd, m_szCaption,m_ToolTip,m_TypeOutLook));
	m_NumBottoms++;
	RecalLayout();

}

int COutLook::OnDestroy()
{
	// Libera la memoria
   /* for( int i=0; i<m_NumBottoms; i++ )
    {
		CItems *pTab = (CItems*)m_ArrayButtons.GetAt(i);
		if( pTab )
			delete pTab;
    }*/
	
	return 1;
	

	// TODO: Add your message handler code here
}
