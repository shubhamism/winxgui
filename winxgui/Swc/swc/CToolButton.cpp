/*
 * <F> CToolButton.cpp		1.0  23/09/2003
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/

#include "stdafx.h"



// CToolButton

#define UPDATEWIN  Invalidate();\
				   UpdateWindow();  

CToolButton::CToolButton()
{
	m_bMouserOver=FALSE;
	m_SizeImage=CSize(0,0);
	m_SizeText=CSize(0,0);
	m_clColor=CDrawLayer::GetRGBColorFace();
	m_bShowDark=TRUE;
	m_ScrollButton=FALSE;
	m_clrFont=RGB(0,0,0);
	m_bSimple=FALSE;
	m_Icon=NULL;
	memset(m_szText,0x00,128);
	
}

CToolButton::~CToolButton()
{
	if (m_Icon!=NULL) DestroyIcon(m_Icon);
	
}

// CToolButton message handlers
BOOL CToolButton::Create( HWND hwndParent,UINT nID,LPCTSTR lpWindowName,
	   DWORD dwStyle,CRect rc,LPVOID lpParam)
{
	BOOL rs= CButton::Create(hwndParent,nID,lpWindowName,
		   dwStyle);
	return rs;
}

BOOL CToolButton::OnLButtonDown(UINT nFlags,  CPoint point) 
{
	Default();
	return TRUE;
}

void CToolButton::SetFontColor(COLORREF clrFont)
{
	m_clrFont=clrFont;
}


void CToolButton::ShowDark(BOOL bShow)
{
	m_bShowDark=bShow;
}

BOOL CToolButton::OnSysColorChange( )
{
	m_clColor=CDrawLayer::GetRGBColorFace();
	Invalidate ();
	UpdateWindow ();
	return TRUE;
}

void CToolButton::PreSubClassWnd() 
{
	ModifyStyle(0,BS_OWNERDRAW);

}

void CToolButton::SetScrollButton(BOOL bScroll)
{
	m_ScrollButton=bScroll;
}

BOOL CToolButton::OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CGDI  pdc= lpDrawItemStruct->hDC;
	CRect rc=lpDrawItemStruct->rcItem;
	UINT  uState=lpDrawItemStruct->itemState;
	CBrush cb;
	TCHAR     lpszText [64 + MAX_PATH] ;
	CFont m_font;
	m_font.CreateFont(-11,2,0,0,400,0,0,0,0,1,2,1,34,"MS Sans Serif");
	cfont=(CFont*)pdc.SelectObject(m_font);
    if (!lstrlen(m_szText))
	{
		GetWindowText(lpszText, sizeof(lpszText));
		lstrcpy(m_szText,lpszText);
	}	
	if( uState & ODS_SELECTED ) //the button is pressed
		cb.CreateSolidBrush(CDrawLayer::GetRGBPressBXP());
	else
		if (m_bMouserOver)
			cb.CreateSolidBrush(CDrawLayer::GetRGBFondoXP());
		
		else
			cb.CreateSolidBrush(m_clColor);
	
	
	if (( uState & ODS_SELECTED) || m_bMouserOver)
	{
		pdc.Draw3dRect(rc,CDrawLayer::GetRGBCaptionXP(),CDrawLayer::GetRGBCaptionXP());
		rc.DeflateRect(1,1);
		
	}
	else if(m_ScrollButton || m_bSimple)
	{
		pdc.Draw3dRect(rc,CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
		rc.DeflateRect(1,1);
	}


	pdc.FillRect(rc,&cb);
	int calculodify;
	calculodify=rc.Height()-(m_SizeImage.cy);
	calculodify/=2;
	int nHeigh=calculodify+(m_bShowDark?1:0);
	int nWidth=m_ScrollButton?rc.Width()/2 :2;
	CPoint m_point=CPoint(nWidth,nHeigh);
	
	if (m_SizeImage.cx > 2)
	{
		if(m_bMouserOver == 1 && !(uState & ODS_DISABLED) && !(uState & ODS_SELECTED) && m_bShowDark)
		{
			CPoint p(m_point.x+1,m_point.y+1);
			//pdc.DrawState(p,m_SizeImage,m_Icon,DSS_MONO,CDrawLayer::GetRGBColorShadow());
			m_point.x-=1; m_point.y-=1;
		}

		pdc.DrawIconEx(m_point,m_Icon, m_SizeImage,
					(uState==ODS_DISABLED?DSS_DISABLED:DSS_NORMAL));
	}
	if (m_SizeText.cx > 2)
	{
		int nMode = pdc.SetBkMode(TRANSPARENT);
		CRect rectletra=rc;
		int nt=m_ScrollButton?0:8;
		rectletra.left+=m_SizeImage.cx+nt;
		CPoint pt=CPoint(rectletra.top,rectletra.left);
		if (uState & ODS_DISABLED)
			pdc.DrawState(pt, m_SizeText, m_szText, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
		else
		{
			if(m_bMouserOver != 1) 
				pdc.SetTextColor(m_clrFont);
			pdc.DrawText(m_szText,rectletra,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		}
		pdc.SetBkMode(nMode);
	}
	cb.DeleteObject();
	return 1;
	// TODO:  Add your code to draw the specified item
}

void CToolButton::SetColor(COLORREF clColor)
{
	m_clColor=clColor;
}

BOOL CToolButton::OnEraseBkgnd(HDC pDC)
{
	return FALSE;
}



BOOL CToolButton::OnSetCursor(HWND hWnd, UINT nHitTest, UINT message)
{

	if (m_bMouserOver) return 0;
	CRect rc;
	GetClientRect(rc);
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	if (rc.PtInRect(pt))
	{
		m_bMouserOver=TRUE;
		SetTimer(1,50,0);
		UPDATEWIN 		
	}
	return TRUE;
}



void CToolButton::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bMouserOver) return;
	CRect rc;
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	GetClientRect(rc);

	if (!rc.PtInRect(pt))
	{
		m_bMouserOver=FALSE;
		KillTimer(1);
		UPDATEWIN 		
	}

}

BOOL CToolButton::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_MOUSEMOVE)
		if (m_toolTip.GetSafeHwnd())
			m_toolTip.RelayEvent(pMsg);
	return TRUE;
}

void CToolButton::SetToolTip(LPCTSTR lpMsg)
{
	if (GetSafeHwnd ()== NULL) return;
	if (lpMsg != NULL)
	{
		if (m_toolTip.GetSafeHwnd () == NULL) 
		{
			m_toolTip.Create(GetSafeHwnd(),TTS_ALWAYSTIP);
			m_toolTip.Activate(TRUE);
			m_toolTip.AddTool(GetSafeHwnd(),(LPTSTR)lpMsg);
		}
		else
		{
			m_toolTip.UpdateTipText(GetSafeHwnd(),(LPTSTR)lpMsg);	
		}
	}
	else
	{
		if (m_toolTip.GetSafeHwnd () == NULL) 
		{
			m_toolTip.Create(GetSafeHwnd(),TTS_ALWAYSTIP);
			m_toolTip.AddTool(GetSafeHwnd(),(LPTSTR)lpMsg);
		}
		else
			m_toolTip.UpdateTipText(GetSafeHwnd(),(LPTSTR)lpMsg);	
		m_toolTip.Activate(FALSE);
	}
		
}

CSize CToolButton::GetSizeButton()
{
	m_ReposWindow=FALSE;
	RecalSize();
	m_ReposWindow=TRUE;
	return m_szButton;
}

void CToolButton::RecalSize()
{
	CRect m_rect;
	int m_High=0;
	if (GetSafeHwnd() == NULL) return;
	CClientDC dc(GetSafeHwnd());
	GetClientRect(&m_rect);
	CSize SizeCad=CSize(0,0);
	m_High=max(m_SizeImage.cy,m_SizeText.cy);
	m_High=max(m_High,m_rect.Height());
	m_szButton= CSize(m_SizeText.cx+m_SizeImage.cx+7,m_High);
	if (m_ReposWindow==TRUE)
		SetWindowPos (NULL, -1,-1, m_szButton.cx, m_High,
			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	dc.DeleteDC();
}

void CToolButton::SetCaption(LPCTSTR szCaption)
{
	lstrcpy(m_szText,szCaption);
	CClientDC dc(GetSafeHwnd());
	SIZE m_size;
	dc.GetTextExtent(m_szText,strlen(m_szText),&m_size);
	m_SizeText=m_size;
	m_SizeText.cx-=7;
	dc.DeleteDC();
}


void CToolButton::SethIcon(HICON hIcon)
{
	m_Icon=hIcon;
	ICONINFO bm;
	ZeroMemory(&bm, sizeof(ICONINFO));
	::GetIconInfo(m_Icon,&bm);
	m_SizeImage =CSize((BYTE)(bm.xHotspot*2),(BYTE)(bm.yHotspot*2));
	::DeleteObject(bm.hbmMask);
	::DeleteObject(bm.hbmColor);

}

void CToolButton::ShowMenu()
{
	CRect rcW;
	int x,y;
	GetWindowRect(&rcW);
	
	x=rcW.left;
	y=rcW.bottom;
	
	if (m_hMenu != NULL )
	{
	   UINT m_iResMenu= ::TrackPopupMenu (m_hMenu,TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, 
		x, y, 0, GetSafeHwnd (), NULL);
		if (m_iResMenu!=0)
		{
			CWin pParent(GetParent());
			pParent.SendMessage (	WM_COMMAND,
									MAKEWPARAM (GetDlgCtrlID (), BN_CLICKED),
									(LPARAM) m_hWnd);
		}
		
	}
	else
		return;
	Invalidate ();
	UpdateWindow ();
	ReleaseCapture();
	
}

//---------------------------------------------------------------------------------

CNormalButton::CNormalButton(void)
{
	m_stlbtn=STL_NORMAL;
	m_clColor=CDrawLayer::GetRGBColorFace();
}

CNormalButton::~CNormalButton(void)
{
}

void CNormalButton::SetStyleButton(StyleBtn StlButton)
{
	m_stlbtn=StlButton;
}


void CNormalButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CGDI  pdc= lpDrawItemStruct->hDC;
	CRect rc=lpDrawItemStruct->rcItem;
	UINT  uState=lpDrawItemStruct->itemState;
	CBrush cb;
	cb.CreateSolidBrush(m_clColor);
	COLORREF clrTL =CDrawLayer::GetRGBColorBTNHigh();
	COLORREF clrBR =CDrawLayer::GetRGBColorShadow();
	pdc.FillRect(rc,&cb);
	

	if( uState & ODS_SELECTED) //the button is pressed
	{
		switch(m_stlbtn)
		{
		case STL_FLAT:	
		case STL_NORMAL:
		case STL_SEMIFLAT:
			pdc.Draw3dRect(rc,clrBR,clrTL);
			rc.DeflateRect(1,1);
			break;

		}
		
	}

	else if(m_bMouserOver)
	{
		switch(m_stlbtn)
		{
		case STL_FLAT:	
		case STL_NORMAL:
		case STL_SEMIFLAT:
			pdc.Draw3dRect(rc,clrTL,clrBR);
			rc.DeflateRect(1,1);
			break;

		}
	}else
	{
		switch(m_stlbtn)
		{
		case STL_NORMAL:
			pdc.Draw3dRect(rc,clrTL,clrBR);
			rc.DeflateRect(1,1);
			break;
		case STL_SEMIFLAT:
			pdc.Draw3dRect(rc,clrTL,clrBR);
			rc.DeflateRect(1,1);
			break;
		case STL_FLAT:
			break;
		}	
	}
	

	
	int calculodify;
	calculodify=rc.Height()-(m_SizeImage.cy);
	calculodify/=2;
	int nHeigh=calculodify+(m_bShowDark?1:0);
	int nWidth=rc.Width()/2 ;
	CPoint m_point=CPoint(nWidth,nHeigh);
	
	if (m_SizeImage.cx > 2)
	{
		if(m_bMouserOver == 1 && !(uState & ODS_DISABLED) && !(uState & ODS_SELECTED) && m_bShowDark)
		{
			CPoint p(m_point.x+1,m_point.y+1);
			pdc.DrawState(p,  m_SizeImage,m_Icon,DSS_MONO,(CBrush*)NULL);
			m_point.x-=1; m_point.y-=1;
		}
		pdc.DrawState (m_point, m_SizeImage,m_Icon,DSS_MONO,(CBrush*)NULL);
	}
	if (m_SizeText.cx > 2)
	{
		int nMode = pdc.SetBkMode(TRANSPARENT);
		CRect rectletra=rc;
		rectletra.left+=m_SizeImage.cx;
		CPoint pt(rectletra.top,rectletra.left);
		if (uState & ODS_DISABLED)
			pdc.DrawState(pt, m_SizeText, m_szText, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
		else
			pdc.DrawText(m_szText,rectletra,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		pdc.SetBkMode(nMode);
	}
	cb.DeleteObject();
}



//-------------------------------------------------------------------

CTabbedButton::CTabbedButton()
{
	bPress=FALSE;
	m_iMilliseconds=50;
}

CTabbedButton::~CTabbedButton()
{

}


BOOL CTabbedButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Default();
	if (!bPress) return TRUE;
	bPress=FALSE;
	KillTimer(1001);
	return TRUE;
}
BOOL CTabbedButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Default();
	if (bPress) return TRUE;
	bPress=TRUE;
	SetTimer(1001,m_iMilliseconds,NULL);
	return TRUE;
	
}

void CTabbedButton::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Default();
	if (bPress == FALSE) return;
	CRect rc;
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	GetClientRect(rc);
	if (rc.PtInRect(pt))
	{
		CWin* pParent=reinterpret_cast<CWin*>(GetParent());
		if (IsWindowEnabled())
			pParent->SendMessage(WM_COMMAND,GetDlgCtrlID(),0);
		//bPress=FALSE;
		//KillTimer(1);
	}
	else
	{
		bPress=FALSE;
		KillTimer(1001);
		CNormalButton::OnTimer(nIDEvent);
	}
	
}

//----------------------------
//CControlBarButton
//----------------------------

CControlBarButton::CControlBarButton()
{
	bTypeButton=(Type)NORMAL;
	m_bEnabled=TRUE;
}


CControlBarButton::~CControlBarButton()
{

}

void CControlBarButton::SetTypeButton(Type bTypeb)
{
	bTypeButton=bTypeb;
}


void CControlBarButton::SetEnabled(BOOL bEnabled)
{
	m_bEnabled=bEnabled;
}

void CControlBarButton::Paint(CGDI* pDC,int st,CRect rc,COLORREF clrFondo,BOOL isBackDark)
{
	CBrush cb;
	if(bTypeButton==NORMAL) 
		cb.CreateSolidBrush(clrFondo);
	else
	{
		if (m_bEnabled)
			if (st == OVERBTN)
				cb.CreateSolidBrush(CDrawLayer::GetRGBFondoXP());
			else if(st == PRESSBTN)
				cb.CreateSolidBrush(CDrawLayer::GetRGBPressBXP());
			else
				cb.CreateSolidBrush(clrFondo);
	}

	if (m_bEnabled)
	{
		pDC->FillRect(rc,&cb);
		if (st == OVERBTN)
			pDC->Draw3dRect(rc,bTypeButton==NORMAL?::GetSysColor(COLOR_BTNSHADOW):CDrawLayer::GetRGBCaptionXP(),
							   bTypeButton==NORMAL?::GetSysColor(COLOR_BTNSHADOW):CDrawLayer::GetRGBCaptionXP());
		if (st == PRESSBTN)
			pDC->Draw3dRect(rc,bTypeButton==NORMAL?::GetSysColor(COLOR_BTNHIGHLIGHT):CDrawLayer::GetRGBCaptionXP(),
			bTypeButton==NORMAL?::GetSysColor(COLOR_BTNHIGHLIGHT):CDrawLayer::GetRGBCaptionXP());
	}
	if(bTypeButton==NORMAL) 
		m_imgList.Draw(isBackDark? m_nIcon+1:m_nIcon, pDC->m_hDC,
						CPoint(rc.left+1,rc.top+2), ILD_TRANSPARENT);				
	else
	{
		HICON m_Icon=m_imgList.ExtractIcon(!isBackDark?m_nIcon:m_nIcon+1);
		//if (m_bEnabled)
		IMAGEINFO* pImageInfo = new IMAGEINFO;
		m_imgList.GetImageInfo(m_nIcon,pImageInfo);
		CRect rcbt=pImageInfo->rcImage;
		int difh= rc.Height()-rcbt.Height();
		int difw= rc.Width()-rcbt.Width();
		if (difh< 0) difh=0;
		if (difw< 0) difw=1;
		difh/=2;
		difw/=2;
		m_imgList.Draw(m_nIcon, pDC->m_hDC,CPoint(rc.left+1+difw,bTypeButton==NORMAL?rc.top+difh+1:rc.top+difh+1),m_bEnabled?ILD_TRANSPARENT:ILD_BLEND25);				
		delete pImageInfo;
		DestroyIcon (m_Icon);

	}
	cb.DeleteObject();
}

void CControlBarButton::SetData(int nIcon,LPCTSTR lpMsg)
{
	m_nIcon=nIcon;
	m_lpMsg=lpMsg;
}

void  CControlBarButton::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_imgList.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(theApp->GetInstance(),(LPCTSTR)nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_imgList.Add(&cbmp,crMask);
	cbmp.DeleteObject();

}


