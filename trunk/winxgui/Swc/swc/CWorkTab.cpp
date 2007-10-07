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
#include "resource1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define ID_WTABSPIN		501
#define ID_SCROLLWINDOW 0x9666

#define  SPACE_TAB		4
#define  DEFAULT_FLAT	18

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

#define MIN_SCROLL ::GetSystemMetrics(SM_CXHSCROLL)*2






CWorkTab::CWorkTab()
{
	SetStyle(CContainer::SHADOW);
	SetALingTabs(CContainer::ALN_BOTTOM);
	m_deplaza = 0;
	m_btndesplaza.SetRectEmpty();
	bIniciaArrastre = FALSE;
	m_EnableL = FALSE;
	m_EnableR = FALSE;
}

CWorkTab::~CWorkTab()
{

}



void CWorkTab::PintaSeparador(CGDI* dc)
{
	CRect m_rClient = m_rectTab;
	// se pinta el boton de desplazamiento
	if (m_btndesplaza.IsRectNull())
	{
		m_rClient.left    = m_rClient.Width()/2;	
		m_rClient.top    -= 3;
		m_rClient.left   -= 5;
		m_rClient.right   = m_rClient.left + 5;	
		m_rClient.bottom -= 1;
		m_btndesplaza     = m_rClient;
		m_scroll.SetWindowPos(NULL, m_btndesplaza.right,
			m_rectTab.top, m_rectTab.right- (m_rClient.left + 5), m_rectTab.Height() - 1,
			SWP_NOACTIVATE | SWP_NOCOPYBITS);	        

		m_scroll.Invalidate();
		m_scroll.UpdateWindow();

		return;
	}
	else
	{
		CRect rcCli;
		GetClientRect(&rcCli);
		if (m_btndesplaza.left + 40 > rcCli.right)
		{
			m_btndesplaza.left=	rcCli.right - 40;
			m_btndesplaza.right = m_btndesplaza.left + 5;
		}
		m_btndesplaza.top = m_rectTab.top;
		m_btndesplaza.bottom = m_rectTab.bottom;
		m_rClient = m_btndesplaza;
	}
	if (!bIniciaArrastre)
	{
		dc->Draw3dRect(m_rClient, ::GetSysColor(BLACK_PEN),
			::GetSysColor(COLOR_BTNHIGHLIGHT));
		m_rClient.DeflateRect(1, 1);
		dc->Draw3dRect(m_rClient, ::GetSysColor(COLOR_BTNHIGHLIGHT),
			::GetSysColor(COLOR_BTNSHADOW));
	}
}


void CWorkTab::OnSpiNiz(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	if (m_EnableL == TRUE)
	{
		m_PresLeft   = TRUE;
		m_PresRight  = FALSE;
		m_deplaza   += 10;
		CClientDC dc(this);
		Drawtabs(&dc);
	}
}
void CWorkTab::OnSpiNde(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
	if (m_EnableR == TRUE)
	{
		m_PresLeft = FALSE;
		m_PresRight = TRUE;
		m_deplaza -= 10; 	
		CClientDC dc(this);
		Drawtabs(&dc);	
		dc.DeleteDC();
	}
}


BOOL CWorkTab::OnPaint(HDC hDC)
{
	CPaintDC dc(this); // device context for painting
	CBrush cbr;
	CRect m_rectDraw;
	cbr.CreateSolidBrush(CDrawLayer::GetRGBColorXP());
	
	GetClientRect(m_rectCliente);
	m_rectTab = m_rectCliente;
	m_rectDraw = m_rectCliente;
	
	if (m_alnTab == ALN_BOTTOM)
		m_rectDraw.bottom = m_rectCliente.bottom- (theApp->m_WinMain->m_sizeImagDocks.cy + SPACE_TAB + 2);	
	
	CRect rc = m_rectDraw;
	rc.top += 1;
	rc.bottom = rc.top + 1;
	dc.Draw3dRect(rc, CDrawLayer::GetRGBColorFace(), CDrawLayer::GetRGBColorFace());
	
	if (m_alnTab == ALN_BOTTOM)
	{
		m_rectCliente.bottom = m_rectCliente.bottom- (DEFAULT_FLAT);
		m_rectTab.top = m_rectCliente.bottom + 2;
	}
	cbr.DeleteObject();
	Drawtabs(&dc);
	dc.DeleteDC();
	return TRUE;
}

void CWorkTab::Drawtabs(CGDI* dc)
{
	int m_StrPos      = 0;
	BOOL m_ViewAlltab = TRUE;
	CRect m_rClient;
	CBrush cbr;
	CPen cp; 
	cp.CreatePen(PS_SOLID, 1,::GetSysColor(COLOR_BTNSHADOW));
	int m_ianchoScroll=::GetSystemMetrics(SM_CXHSCROLL) * 2;
	m_EnableR = TRUE;
	m_EnableL = TRUE;
	cbr.CreateSolidBrush(m_wd.GetRGBColorXP());
	GetClientRect(m_rClient);
	CRect rectT = m_rectTab;
	rectT.right = m_btndesplaza.left;
	rectT.right += 4;
	dc->FillRect(rectT, &cbr);
	HPEN hPen = dc->SelectObject(&cp);
	dc->MoveTo(m_rectTab.left, m_rectTab.top);
	dc->LineTo(m_btndesplaza.right + 1, m_rectTab.top);
	dc->Draw3dRect(m_rClient, ::GetSysColor(COLOR_BTNSHADOW),
		::GetSysColor(COLOR_BTNHIGHLIGHT));
	if (!::IsWindow(m_toolBtn[0].GetSafeHwnd()))
	{
		CRect r = m_rectTab;
		r.right = r.left + 35;
		r.top += 1;
		// r.bottom-=1;
		if (!m_img.Create(IDB_GUI_DOCKBAR, 9, 11, RGB(255, 0, 255)))
		{
			//TRACE0("error imagelist");
		}
		
		m_toolBtn[0].Create(GetSafeHwnd(),SCROLLLEFT, _T(""), 
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
			CRect(0, 0, 0, 0));
		m_toolBtn[0].SetToolTip(_T("Scroll Left"));
		m_toolBtn[0].SethIcon(m_img.ExtractIcon(4));
		m_toolBtn[0].ShowDark(FALSE);
		m_toolBtn[0].SetScrollButton();
		m_toolBtn[1].Create(GetSafeHwnd(),SCROLLRIGHT, _T(""), 
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
			CRect(0, 0, 0, 0));
		m_toolBtn[1].SetToolTip(_T("Scroll Right"));
		m_toolBtn[1].SethIcon(m_img.ExtractIcon(2));
		m_toolBtn[1].ShowDark(FALSE);
		m_toolBtn[1].SetScrollButton();
	}
	
	if (!::IsWindow(m_scroll.GetSafeHwnd()))
	{
		m_scroll.Create(GetSafeHwnd(),0L,NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ, m_rectTab);
	}
	
	CSize szBtn_1 = m_toolBtn[0].GetSizeButton();
	CSize szBtn_2 = m_toolBtn[0].GetSizeButton();
	
	CRect rcSpin = CRect(0, 0, szBtn_1.cx + szBtn_2.cx + 2, szBtn_1.cy + szBtn_2.cy);
	m_StrPos = rcSpin.Width();
	if ((m_btndesplaza.left < rcSpin.right) && ! m_btndesplaza.IsRectEmpty())
	{
		m_btndesplaza.left = rcSpin.right + 5;
		m_btndesplaza.right = m_btndesplaza.left + 5;
	}

	PintaSeparador(dc);
	
	int m_Space = 8;
	int m_Pos   = 10;
	int m_right = m_StrPos;
	if (m_iMinValRec - 26 > m_btndesplaza.left) // No existe suficioente espacio para los tabs
	{
		m_ViewAlltab = FALSE;
		// m_spin.EnableScrollBar();
		if (m_PresLeft == TRUE)
			m_right += m_deplaza;
		if (m_PresRight == TRUE)
			m_right += m_deplaza;
		if (m_deplaza == 0)
		{
			m_EnableL = FALSE;
			m_EnableR = TRUE;
			//m_spin.EnableScrollBar(ESB_DISABLE_LTUP);
		}
		if ((m_iMinValRec + m_deplaza) - 26 <= m_btndesplaza.left)
		{
			//m_spin.EnableScrollBar(ESB_DISABLE_RTDN);
			m_EnableR = FALSE;
			m_EnableL = TRUE;
		}
	}
	else
	{
		m_EnableL = FALSE;
		m_EnableR = FALSE;
		// m_spin.EnableScrollBar(ESB_DISABLE_BOTH);
		m_ViewAlltab = TRUE;
		m_deplaza = 0;
	}
	CRect rectScroll; 
	CRect rectRecorte;
	rectRecorte.left = m_rectTab.left + m_ianchoScroll;
	rectRecorte.top = m_rectTab.top;
	rectRecorte.bottom = m_rectTab.bottom;
	rectRecorte.right = m_btndesplaza.left;
	HRGN hRgn= CreateRectRgnIndirect(rectRecorte);
	dc->SelectClipRgn(hRgn);
	for (int iCont = 0; iCont < m_Numtabs; iCont++)
	{	
		//;
		CTab* ctb = (CTab*)m_pArray[iCont];
		CRect mrt = ctb->rect;		
		int ancho = mrt.Width();
		mrt.left = m_right;
		mrt.right = mrt.left + ancho;
		CPoint Coor[4];
		// dibujar la hoja seleccionada
		if (iCont == 0)
		{
			dc->MoveTo(mrt.left, mrt.top);
			dc->LineTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
			dc->MoveTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
			dc->LineTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
			dc->MoveTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
			if (m_iSelectTab ==iCont)
				dc->LineTo(mrt.right - 2, mrt.top + 2);
			else
				dc->LineTo((mrt.right) - 3, mrt.top+ (m_rectTab.Height()/2));
			
			m_right = mrt.right;
		}
		else
		{
			// Se dibuja la hoja siguiente a la seleccionada
			// no se dibuja toda la diagonal y no es la ultima hoja
			
			if (iCont - 1 == m_iSelectTab) 
			{	
				dc->MoveTo(mrt.left+ (m_rectTab.Height()/4) + 1, mrt.top + m_rectTab.Height()/2);
				dc->LineTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
				dc->MoveTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
				dc->LineTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
				dc->MoveTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
				if (iCont == m_Numtabs - 1)
					dc->LineTo((mrt.right - 2), mrt.top + 2);
				else
					dc->LineTo((mrt.right) - 3, mrt.top+ (m_rectTab.Height()/2));
			}
			else
			{
				dc->MoveTo(mrt.left, mrt.top);
				dc->LineTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
				dc->MoveTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
				dc->LineTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
				dc->MoveTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
				if (iCont == m_iSelectTab || iCont == m_Numtabs - 1)
					dc->LineTo((mrt.right - 2), mrt.top + 2);
				else
					dc->LineTo((mrt.right) - 3, mrt.top + 3+ (m_rectTab.Height()/2));
			}
			m_right = mrt.right;
		}
		if (iCont == m_iSelectTab)
		{
			Coor[0].x = mrt.left;
			Coor[0].y = mrt.top;
			Coor[1].x = (mrt.left) + m_rectTab.Height()/2;
			Coor[1].y = mrt.bottom - 1;
			Coor[2].x = (mrt.right) - m_rectTab.Height()/2; 
			Coor[2].y = mrt.bottom - 1;
			Coor[3].x = (mrt.right - 1);
			Coor[3].y = mrt.top + 3;
			dc->Polygon(Coor, 4);	
			dc->SelectStockObject(WHITE_PEN);
			dc->MoveTo(mrt.left + 3, mrt.top + 3);
			dc->LineTo(mrt.right - 1, mrt.top + 3);
			dc->MoveTo(mrt.left + 2, mrt.top + 2);
			dc->LineTo(mrt.right, mrt.top + 2);
			dc->SelectObject(&cp);
		}
		
		HFONT hFont= dc->SelectObject(CFont((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
		dc->SetBkMode(TRANSPARENT);
		CRect mrtt = mrt;
		mrtt.top += 2;
		dc->DrawText(ctb->lpMsg, mrtt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ctb->rect = mrt;
		m_right -= (m_rectTab.Height()/2);	
		if (!bIniciaArrastre)
		{
			CRect m_rectCli;
			GetClientRect(m_rectCli);
			if (m_btndesplaza.left <m_rectCli.left + rcSpin.left + 1)
			{
				m_btndesplaza.left = m_rectCli.left + rcSpin.left + 5;
				m_btndesplaza.right = m_btndesplaza.left + 5;
				PintaSeparador(dc);
			}
			m_scroll.SetWindowPos(NULL, 
				m_btndesplaza.right, m_rectTab.top, m_rectCli.right - (m_btndesplaza.left + 5), 
				m_rectTab.Height() - 1, SWP_NOACTIVATE | SWP_NOCOPYBITS);	        
			m_scroll.Invalidate();
			m_scroll.UpdateWindow();
			CSize szBtn = m_toolBtn[0].GetSizeButton();
			m_toolBtn[0].MoveWindow(m_rectTab.left + 1, 
				m_rectTab.top + 1, szBtn.cx, m_rectTab.Height() - 2);
			CSize szBtn1 = m_toolBtn[1].GetSizeButton();
			m_toolBtn[1].MoveWindow(m_rectTab.left + szBtn.cx + 1, m_rectTab.top + 1, 
				szBtn1.cx, m_rectTab.Height() - 2);
		}

	}

	cbr.DeleteObject();
	dc->SelectClipRgn(NULL);
	::DeleteObject(hRgn);
	cp.DeleteObject();
	m_toolBtn[0].Invalidate();
    m_toolBtn[0].UpdateWindow();	
	m_toolBtn[1].Invalidate();
    m_toolBtn[1].UpdateWindow();	
}


void CWorkTab::OnHScroll(UINT nSBCode, UINT nPos, HWND hScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	Default();
	
	if (hScrollBar == m_scroll.GetSafeHwnd())
	{
		CTab* ct = (CTab*) m_pArray[m_iSelectTab];
		CWin* ViewAc = reinterpret_cast<CWin*>(ct->pParent);
		ViewAc->SendMessage(WM_HSCROLL, MAKEWPARAM(nSBCode, nPos),0);  
		SizeScroll();
		
		return;
	}

    CClientDC dc(this);
	Drawtabs(&dc);
	dc.DeleteDC();
}



BOOL CWorkTab::OnSetCursor(HWND hWnd, UINT nHitTest, UINT message)
{
	CPoint ptCurPos;
	GetCursorPos(&ptCurPos);
	ScreenToClient(&ptCurPos);
	
	if (m_btndesplaza.PtInRect(ptCurPos))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return TRUE;
	}
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return TRUE;
}

BOOL CWorkTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_btndesplaza.PtInRect(point) && !bIniciaArrastre)
	{
		bIniciaArrastre = TRUE;		
		SetCapture();
		InvalidateRect(m_btndesplaza, TRUE);
	}
	else
	{
		CContainer::OnLButtonDown(nFlags, point);
		ReleaseCapture();
		CTab* ct = (CTab*) m_pArray[m_iSelectTab];
		CWin* ViewAc = reinterpret_cast<CWin*>(ct->pParent);
		int rangmin, rangMax;
		ct->pParent->GetScrollRange(SB_HORZ, &rangmin, &rangMax);
		m_scroll.SetScrollRange(SB_HORZ,rangmin, rangMax);
		m_scroll.SetScrollPos(SB_HORZ,ViewAc->GetScrollPos(SB_HORZ));
	}
	//Default();
	return TRUE;
}


BOOL CWorkTab::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (bIniciaArrastre == TRUE)
	{
		bIniciaArrastre = FALSE;
		int iDiferencia = m_rectTab.right - 31;
		if (point.x < m_rectTab.left + 31)
			point.x = m_rectTab.left + 31;
		if (point.x > iDiferencia)
			point.x= iDiferencia;
		m_btndesplaza.left = point.x;
		m_btndesplaza.right = m_btndesplaza.left + 5;
		ReleaseCapture();	
		Invalidate();
		UpdateWindow();
	}
	
	Default();
	return TRUE;
}

void CWorkTab::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect m_rectCli;
	GetClientRect(m_rectCli);
    if (bIniciaArrastre == TRUE)
    {
		int iDiferencia = m_rectCli.right - 31;
		if (point.x < m_rectTab.left + 31)
			point.x = m_rectTab.left + 31;
		if (point.x > iDiferencia)
			point.x= iDiferencia;
		m_scroll.SetWindowPos(NULL, point.x, 
			m_rectTab.top, m_rectCli.right - point.x, m_rectTab.Height() - 1,
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS);	        
		m_scroll.Invalidate();
		m_scroll.UpdateWindow();
		m_btndesplaza.left = point.x;
		m_rectCli = m_btndesplaza;
		m_rectCli.left -= 5;
		InvalidateRect(m_btndesplaza, TRUE);
		UpdateWindow();
	}
	else
	{
		Default();
	}
}

BOOL CWorkTab::OnSysColorChange() 
{
	Default();
	
	m_toolBtn[0].SetColor(CDrawLayer::GetRGBColorFace());	
	m_toolBtn[1].SetColor(CDrawLayer::GetRGBColorFace());	
	m_toolBtn[0].Invalidate();
    m_toolBtn[0].UpdateWindow();	
	m_toolBtn[1].Invalidate();
    m_toolBtn[1].UpdateWindow();

	Invalidate();
	UpdateWindow();
	return TRUE;
}

void CWorkTab::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	Default();
	CTab* ct  = (CTab*) m_pArray[m_iSelectTab];
	CWin* ViewAc = ct->pParent;
}

BOOL CWorkTab::OnSize(UINT nType, int cx, int cy)
{
	CContainer::OnSize(nType, cx, cy);
	SizeScroll();
	return TRUE;
}


void CWorkTab::SizeScroll()
{
	SCROLLINFO sCrollInfo;
	ASSERT(this);	
	
	if (!m_pArray.GetSize()) 
		return;
	
	CTab* ct  = (CTab*) m_pArray[m_iSelectTab];
	CWin* ViewAc =reinterpret_cast<CWin*>(ct->pParent);
	
	memset(&sCrollInfo, 0, sizeof(SCROLLINFO));
	sCrollInfo.cbSize = sizeof(SCROLLINFO);
	sCrollInfo.fMask  = SIF_ALL;
	
	ViewAc->GetScrollInfo(SB_HORZ, &sCrollInfo);
	if (::IsWindow(m_scroll.GetSafeHwnd()))
		m_scroll.SetScrollInfo(SB_HORZ,&sCrollInfo);
	
	ViewAc->ShowScrollBar(SB_HORZ, FALSE);
	ViewAc->ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);	
}

int CWorkTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CContainer::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}