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


void CMMedia::DrawFolder(CFolderBar* cfb,Style m_Style)
{
	CRect rc;CRect rcWin;
	rc=cfb->m_rect;
	rcWin=cfb->m_rect;
	int nNuImage=cfb->m_img;
	CClientDC pDC(this);
	CGradient M(CSize(rc.Width(),rc.Height()));	
	M.PrepareReverseVert(&pDC,GUISTYLE_XP);
	M.Draw(&pDC,rc.left,rc.top,0,0,rc.Width(),rc.Height(),SRCCOPY);
	
	CRect rct;
	rct=rc;
	rct.top=rct.bottom-1;
	pDC.Draw3dRect(rct, CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
	rct=rc;
	rct.top+=(rct.Height()/2)-6;
	rct.bottom=rct.top+9;
	rct.left+=4;
	rct.right=rct.left+9;
	CRect rctemp; rctemp=rct;
	pDC.Draw3dRect(rct, CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
	rct.DeflateRect(1,1);
	CGradient M1(CSize(rct.Width(),rct.Height()));	
	M.PrepareVertical(&pDC,GUISTYLE_XP);
	M.Draw(&pDC,rct.left,rct.top,0,0,rct.Width(),rct.Height(),SRCCOPY);
	
	if (m_iSelected== m_iWhatFolderIsDrawNow)
	{
		rct=rctemp;
		rct.top+=rct.Height()/2;
		rct.bottom=rct.top+1;
		rct.left+=2;
		rct.right-=2;
		pDC.Draw3dRect(rct, CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
	}
	else
	{
		rct=rctemp;
		rct.top+=rct.Height()/2;
		rct.bottom=rct.top+1;
		rct.left+=2;
		rct.right-=2;
		pDC.Draw3dRect(rct, CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
		rct=rctemp;
		rct.top+=2;
		rct.bottom-=2;
		rct.left+=(rct.Width()/2);
		rct.right=rct.left+1;
		pDC.Draw3dRect(rct, CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());	
	}
	int OldMode=pDC.SetBkMode(TRANSPARENT);
	CFont cf;
	
	COLORREF clrtext;
	clrtext=pDC.SetTextColor(::GetSysColor (COLOR_MENUTEXT));	
	cf.CreateFont(-11,2,0,0,700,0,0,0,0,1,2,1,34,"MS Sans Serif");
	
	cfont=(CFont*)pDC.SelectObject(cf);	
	//guardar espacio para la imagen
	TCHAR m_cadBreak[64];
	memset(m_cadBreak,0x00,64);
	lstrcpy(m_cadBreak,cfb->m_lpMsg);
	int contt;
	int cont =contt=strlen(m_cadBreak);
	CSize coor=pDC.GetTextExtent(m_cadBreak,cont);
	rc.left+=16;
	if ( coor.cx > rc.Width())
	{
		rc.left+=1;
		while(cont > 1 )
		{
			TCHAR m_scadtemp[64];
			memset(m_scadtemp,0x00,64);
			lstrcpy(m_scadtemp,m_cadBreak);
			lstrcat(m_scadtemp,_T("..."));
			CSize coor=pDC.GetTextExtent(m_scadtemp,lstrlen(m_scadtemp));
			if(coor.cx > rc.Width())
				*(m_cadBreak+cont)=NULL;
			else
				break;
			cont--;
		}
		lstrcat(m_cadBreak,_T("..."));
		rc.right+=3;

		
			pDC.DrawText(m_cadBreak,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	}
	else
			pDC.DrawText(cfb->m_lpMsg,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	pDC.SetTextColor(clrtext);
   	pDC.SetBkColor(OldMode);
	
}

void CMMedia::DrawGripper(CGDI* dc,CRect rcWin,BOOL bHorz)
{

		if (bHorz)
		{
			
			rcWin.top+=7;
			rcWin.left+=3;
			rcWin.right=rcWin.left+2;
			rcWin.bottom-=4;
			CRect rcBlack;
	
			for (int i=0; i < rcWin.Height(); i+=4)
			{
				CRect rcWindow;
				CBrush cb;
				cb.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
				rcWindow=rcWin;
				rcWindow.top=rcWin.top+i;
				rcWindow.bottom=rcWindow.top+2;
				dc->FillRect(rcWindow,&cb);
				rcBlack=rcWindow;
				rcBlack.left-=1;
				rcBlack.top=(rcWin.top+i)-1;
				rcBlack.bottom=rcBlack.top+2;
				rcBlack.right=rcBlack.left+2;
				cb.DeleteObject();
				cb.CreateSolidBrush(CDrawLayer::GetRGBColorShadow());
				dc->FillRect(rcBlack,&cb);
		
			}
		
			
		}
		else
		{
			rcWin.top+=3;
			rcWin.left+=3;
			rcWin.right-=2;
			rcWin.bottom=rcWin.top+2;
			CRect rcBlack;
			for (int i=0; i < rcWin.Width(); i+=4)
			{
				CRect rcWindow;
				CBrush cb;
				cb.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
				rcWindow=rcWin;
				rcWindow.left=rcWindow.left+i;
				rcWindow.right=rcWindow.left+2;
				dc->FillRect(rcWindow,&cb);
				rcBlack=rcWindow;
				rcBlack.top-=1;
				rcBlack.left-=1;
				rcBlack.bottom=rcBlack.top+2;
				rcBlack.right=rcBlack.left+2;
				cb.DeleteObject();
				cb.CreateSolidBrush(CDrawLayer::GetRGBColorShadow());
				dc->FillRect(rcBlack,&cb);
		
			}
		}

		
}


CMMedia::CMMedia(void)
{
	
}

CMMedia::~CMMedia(void)
{
}

void CMMedia::OnCloseBtn(WPARAM wParam, LPARAM lParam, HWND handle)
{
	if (IsWindowVisible())
		ShowWindow(FALSE);
	else
		ShowWindow();
	::SendMessage(GetParent(),WM_SIZE,0,0);
}

BOOL CMMedia::OnLButtonUp(UINT nFlags, CPoint pt)
{
	return CFolder::OnLButtonUp(nFlags,pt);
}


void CMMedia::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CFolder::OnMouseMove(nFlags, point);
	//::SetCursor(::LoadCursor(NULL,MAKEINTRESOURCE(32649)));//IDC_HAND));
	
}



BOOL CMMedia::OnLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//::SetCursor(::LoadCursor(NULL,MAKEINTRESOURCE(32649)));
	return CFolder::OnLButtonDown(nHitTest, point);
}



BOOL CMMedia::OnSize(UINT nType, int cx, int cy) 
{
	return CFolder::OnSize(nType,cx,cy); 
}


BOOL CMMedia::OnEraseBkgnd(HDC hDC) 
{
	CGDI  pDC(hDC);
	CRect m_rect;
	GetClientRect(m_rect);
	return TRUE;
}

int CMMedia::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!m_img.Create(IDB_GUI_DOCKBAR,9,11,RGB(255,0,255)))
	{
		return -1;
	}
	m_toolBtnC.Create(hWndt,SCLOSE,_T("X"),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0));
	m_toolBtnC.SetToolTip(_T("Close"));
	m_toolBtnC.SethIcon(m_img.ExtractIcon(6));
//	m_toolBtnC.SetColor(CDrawLayer::GetRGBActiveBorder());
//	m_toolBtnC.ShowDark(FALSE);

	return 0;
}
