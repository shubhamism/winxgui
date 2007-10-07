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
#include "CComboBoxExt.h"


/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt

CComboBoxExt::CComboBoxExt()
{
	m_clrBtnFace= CDrawLayer::GetRGBColorFace();
	m_clrBtnLight=::GetSysColor(COLOR_3DHILIGHT);
	m_clrBtnDark=::GetSysColor(COLOR_3DSHADOW);
	m_iWidthDrowDown=GetSystemMetrics(SM_CXHTHUMB);
	m_bOverCombo=FALSE;
	m_Font.CreateFont(-11,2,0,0,FW_BOLD,0,0,0,0,1,2,1,34,"MS Sans Serif");
	m_bPress=FALSE;
	m_imgArrow.Create(IDB_GUI_DOCKBAR,9,10,RGB(255,0,255));
	CBitmap cbmp;
	BITMAP bmp;
	cbmp.LoadBitmap(theApp->GetInstance(),(LPCTSTR)IDB_GUI_DOCKBAR);
	cbmp.GetBitmap(&bmp);
	mHeight=CPoint(bmp.bmWidth,bmp.bmHeight);
	m_bFondoXp=FALSE;
	m_IsCallMiniTool=FALSE;
	bColor=TRUE;
	bhistory=FALSE;
	cbmp.DeleteObject();
	
}
CComboBoxExt::~CComboBoxExt()
{
	m_Font.DeleteObject();
}

BOOL CComboBoxExt::PreTranslateMessage(MSG* pMsg) 
{
	
	if (pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_RETURN )
		{
			//if (!(GetStyle( ) & CBS_DROPDOWNLIST))
			//{
				//*CString sCad;
				//GetWindowText(sCad);
				//AddString(sCad);
			//}
			HWND pParent=GetParent();
			::SendMessage(pParent,WM_COMMAND,GetDlgCtrlID(),0);
			return 1;//nonzero so app does not get the esc key and exit
		}
	}
	//return Default();
	return TRUE;
}

BOOL CComboBoxExt::OnSysColorChange( )
{
	Default();
	m_clrBtnLight=::GetSysColor(COLOR_3DHILIGHT);
	m_clrBtnDark=::GetSysColor(COLOR_3DSHADOW);
	if (bColor)
		m_clrBtnFace= CDrawLayer::GetRGBColorFace();
	return TRUE;
}

void CComboBoxExt::AutoColor(BOOL bAColor)
{
	bColor=bAColor;
}


/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt message handlers


BOOL CComboBoxExt::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_bOverCombo=TRUE;
	m_bPress=TRUE;
	CClientDC dc(this);
	DrawCombo(CM_SELECCIONADO,&dc);			
	Default();
	dc.DeleteDC();
	return TRUE;
}




int	 CComboBoxExt::AddString(LPCTSTR lpszString)
{
	
	if (lpszString == NULL) return -1;
	if(bhistory!=TRUE)
		return CComboBox::AddString(lpszString);
	//szCadAdd.TrimLeft(_T(" "));
	//szCadAdd.TrimRight(_T(" "));
	int nret=CComboBox::InsertString(0,lpszString);
	int nFindCad=FindStringExact(0, lpszString);
	if (nFindCad != -1 && nFindCad != 0)
		DeleteString(nFindCad );
	SetCurSel(nret);	
	return nret;
}


void CComboBoxExt::PreSubClassWnd() 
{
	ModifyStyle(0,BS_OWNERDRAW);
}

BOOL CComboBoxExt::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		Default(); 
	return TRUE;
}

BOOL CComboBoxExt::OnPaint(HDC hDC) 
{
	CPaintDC dc(this); // device context for painting
	/*
	 * Se hace un llamamdo a la función definida por defecto
	 * para el procesamiento de mensajes que la aplicación definitivamente
	 * no esta interesado en manejar
	 **/ 
	m_clrBtnFace=CDrawLayer::GetRGBColorFace();
	//CComboBox::DefWindowProc(m_hWnd,WM_PAINT,(WPARAM)dc.m_hDC,0);
	if (m_bPress != TRUE)
		DrawCombo(CM_NORMAL,&dc);
	else
		DrawCombo(CM_SELECCIONADO,&dc);
	dc.DeleteDC();
	// Do not call CComboBox::OnPaint() for painting messages
	return TRUE;
}

void CComboBoxExt::OnSetFocus(HWND pOldWnd) 
{
	Default(); 
	CClientDC dc(this);
	DrawCombo(CM_SELECCIONADO,&dc);			
	dc.DeleteDC();
	
}


BOOL CComboBoxExt::OnSetCursor(HWND pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptCurPos;
	CRect m_rcCli;
	GetCursorPos (&ptCurPos);
	ScreenToClient (&ptCurPos);
	GetClientRect(&m_rcCli);
	if (m_rcCli.PtInRect (ptCurPos) && m_bOverCombo==FALSE && m_bPress==FALSE)
		{
			m_bOverCombo=TRUE;
			CClientDC dc(this);
			DrawCombo(CM_ONFOCUS,&dc);			
			SetTimer(1001,10,NULL);
			dc.DeleteDC();
			//OnTimer(1001);
			return TRUE;
		}
	
			
	return 	Default(); 
}

void CComboBoxExt::SetColor(COLORREF clrFace)
{
	m_clrBtnFace=clrFace;
	Invalidate();
	UpdateWindow();
	
}

void CComboBoxExt::DrawCombo(enTypeShow enShow,CGDI* pDC)
{

    CRect m_rcClient;
	CRect m_rcDropDown;
	GetClientRect(&m_rcClient);
	CGradient M(CSize(m_rcClient.Width(),m_rcClient.Height()));	
	M.PrepareVertical(pDC);
	M.Draw(pDC,0,0,0,0,m_rcClient.Width(),m_rcClient.Height(),SRCCOPY);
	m_rcClient.bottom-=2;
	m_rcClient.DeflateRect(1,1);

	if (enShow==CM_NORMAL)
		pDC->Draw3dRect(&m_rcClient,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
	else // && !XP
		pDC->Draw3dRect(&m_rcClient,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
	//debemos pintar el borde del boton drawDwon
	m_rcClient.DeflateRect(1,1);
	m_rcClient.left=m_rcClient.right-m_iWidthDrowDown;
	m_rcClient.DeflateRect(1,1);
	if (enShow!=CM_NORMAL)
		pDC->Draw3dRect(&m_rcClient,CDrawLayer::GetRGBFondoXP(),CDrawLayer::GetRGBFondoXP());
	m_rcClient.InflateRect(0,1);
	if (enShow==CM_NORMAL)
	{
		//el boton no esta seleccionado
		m_rcClient.left += 2;
		m_rcClient.right+= 2;
		DrawArrow(pDC,m_rcClient);
	}
	else

	{
		m_rcClient.InflateRect(1,1);
		CBrush cblu;
		cblu.CreateSolidBrush(enShow == CM_ONFOCUS? CDrawLayer::GetRGBFondoXP():CDrawLayer::GetRGBPressBXP());
		pDC->FillRect(&m_rcClient,&cblu);
		m_rcClient.right += 1;
		pDC->Draw3dRect(&m_rcClient,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
		DrawArrow(pDC,m_rcClient);
		cblu.DeleteObject();
	}
	
}

void CComboBoxExt::DrawArrow(CGDI* pDC,CRect m_rc)
{
	int difh =m_rc.Height()-mHeight.y;
	difh/=2;
	
	m_rc.left=m_rc.right-m_iWidthDrowDown;
	m_imgArrow.Draw(0,pDC->m_hDC,CPoint(m_rc.left+3,m_rc.top+difh),ILD_TRANSPARENT);

}

void CComboBoxExt::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent== 1001)
	{
		CPoint pt(GetMessagePos());
		CRect m_rc;
		ScreenToClient(&pt);
		GetClientRect(m_rc);
		if (!m_rc.PtInRect(pt) && m_bPress!=TRUE)
		{
		 	KillTimer(1001);
			m_bOverCombo=FALSE;
			CClientDC dc(this);
			if (m_bPress==FALSE)
		 		DrawCombo(CM_NORMAL,&dc);			
			else
				DrawCombo(CM_ONFOCUS,&dc);	
			m_bPress=FALSE;
			dc.DeleteDC();
		}
		
	}
	
		Default(); 
}

void CComboBoxExt::OnCbnCloseUp()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	m_bPress=FALSE;
	dc.DeleteDC();
	OnTimer(1001);
}

void CComboBoxExt::OnCbnSelendCandel()
{
	CClientDC dc(this);
	m_bPress=FALSE;
	dc.DeleteDC();
	OnTimer(1001);
}

int CComboBoxExt::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	//SetFont(&m_Font);	
	return 0;
}

void CComboBoxExt::OnCbnEditUpdate()
{
  LPTSTR m_szCad;
  m_szCad= (LPTSTR) new BYTE[(100)*sizeof(TCHAR)];
  memset(m_szCad,0x00,100);
  GetWindowText(m_szCad,100);
  
  DWORD m_dwCurRange=GetEditSel();
  DWORD m_dwStart=LOWORD(m_dwCurRange);
  DWORD m_dwEnd = HIWORD(m_dwCurRange);
  //se busca la cadena aprox, si no existe se debe insertar
 
	if (SelectString(-1,m_szCad) == CB_ERR)
	{
		SetWindowText(m_szCad);
		SetEditSel(m_dwStart,m_dwEnd);
	}
	else
	{
		if (m_dwCurRange != CB_ERR)
		{
			if (m_dwEnd <(DWORD) strlen(m_szCad))
				SetEditSel(m_dwStart,m_dwEnd);
			else
				SetEditSel(strlen(m_szCad),-1);
		}
	}

	
	delete [] (BYTE*)m_szCad;
}

void CComboBoxExt::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
}

void CComboBoxExt::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
}


