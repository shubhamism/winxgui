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
// CContainer

#define  SPACE_TAB		5
#define  DEFAULT_FLAT	16
#define  HTPIN			323


CContainer::CContainer()
{
	m_rectCliente.SetRectEmpty();
	m_rectTab.SetRectEmpty();
	m_ActualVar=0;
	m_Numtabs=0;
	m_iSelectTab=0;
	m_sizeImag=CSize(15,15);
	m_pArray.RemoveAll();
	m_iMinValRec=0;  //minimo valor requerido para mostrar toda las carpetas
	m_cfontBold.CreateFont(-11,2,0,0,FW_BOLD,0,0,0,0,1,2,1,34,"MS Sans Serif");
	m_style=S3D;
	m_cfont=NULL;
	m_ActualTitle=TRUE;
	m_alnTab=ALN_BOTTOM;
	m_TypeTab=TYPE_NORMAL;
	m_bDrawFrame=FALSE;	
	m_stateBtn=NORMAL;
	m_stateAHBtn=NORMAL;
	m_bCaption=TRUE;
	m_DragTab=FALSE;
	m_NCDragWindow=FALSE;
	m_TabMove=0;
	m_DOCKSITE=BS_DOCKINGLEFT;
	m_DOCKFLOAT=0;
	m_rcAutoHideBtn;
	m_rcCloseBtn;
	m_pContainer=NULL;
	m_close=FALSE;
	m_hMenu=NULL;
	m_pointbase=CPoint(0,0);
}

CContainer::~CContainer()
{
	m_pArray.RemoveAll();
	if (m_cfont)
		delete m_cfont;
}





/////////////////////////////////////////////////////////////////////////////
// CContainer message handlers

BOOL CContainer::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_MOUSEMOVE)
		CToolTip.RelayEvent(pMsg);

	return CWin::PreTranslateMessage(pMsg);
}


void CContainer::SetTypeTab(TypeTab Type)
{
	m_TypeTab=Type;
}
//****************************************************************************
BOOL CContainer::OnEraseBkgnd(HDC hDC) 
{
	// TODO: Add your message handler code here and/or call default
	CGDI pDC(hDC);
	if (m_Numtabs == 0)
	{
		CBrush cbr;
		cbr.CreateSysColorBrush(COLOR_BTNFACE);
		CRect m_rect;
		GetClientRect(m_rect);
		pDC.FillRect(m_rect,&cbr);
		cbr.DeleteObject();
		
	}
	return TRUE;
}

void CContainer::SetActualTitle(BOOL bActual)
{
	m_ActualTitle=bActual;
}

void CContainer::SetALingTabs(AlingTab alnTab)
{
	m_alnTab=alnTab;
	Invalidate();
	UpdateWindow();
}

BOOL CContainer::OnPaint(HDC hDC) 
{
	CRect rcClient;
	CPaintDC dc(GetSafeHwnd()); // device context for painting
	CBrush cbr;
	CRect m_rectDraw;
	cbr.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
	GetClientRect(rcClient);
	CGDI		MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(dc.m_hDC);
	m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,rcClient.Width(),rcClient.Height());	
	
	CBitmap *m_bitmapOld=new CBitmap(MemDC.SelectObject(&m_BitmapMemDC));
	MemDC.FillRect(&rcClient,&cbr);
		
	m_rectTab=m_rectCliente;
	m_rectDraw=m_rectCliente;
	if (m_alnTab==ALN_BOTTOM)
	{
		if (m_Numtabs > 1)
		m_rectDraw.bottom=rcClient.bottom-(m_sizeImag.cy+SPACE_TAB+2);	
	}
	else
		m_rectDraw.top=rcClient.top+(m_sizeImag.cy+SPACE_TAB+2);
	
	if (m_style != S3D) //si son carpetas estilo excel o tabbed como devstudio 7
	{
		if (m_alnTab==ALN_BOTTOM)
		{
			m_rectCliente.bottom=rcClient.bottom-(DEFAULT_FLAT);
			m_rectTab.top=rcClient.bottom+2;
		}
		else
		{
			m_rectTab.bottom=rcClient.top+(DEFAULT_FLAT)+3;
		}
	}

	int nVal=0;
	
	if (m_alnTab!=ALN_TOP)
	{
		
		MemDC.FillRect(m_rectTab,&cbr);
		CRect mrc=m_rectDraw;
		
	}
	else
	{
		CRect rc=m_rectDraw;
		for (int i=0; i< 2; i++)
		{
			MemDC.Draw3dRect(rc,CDrawLayer::GetRGBColorFace(),CDrawLayer::GetRGBColorFace());
			rc.DeflateRect(1,1);
		}
		
		rc.InflateRect(3,3);
		if (m_bDrawFrame)
			MemDC.Draw3dRect(rc,GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_BTNSHADOW));
		else
		{
			CRect mrc=m_rectDraw;
			mrc.top+=nVal;
			MemDC.Draw3dRect(mrc,GetSysColor(COLOR_BTNSHADOW),GetSysColor(COLOR_BTNSHADOW));

		}
		rc=m_rectDraw;
		rc.bottom=rc.top+3;
		MemDC.FillRect(rc,&cbr);
		
	}
	
	
	
	Drawtabs(&MemDC);

	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	cbr.DeleteObject();
	m_bitmapOld->DeleteObject();
	dc.DeleteDC();
	delete m_bitmapOld;
	return TRUE;
}



BOOL CContainer::Create(DWORD dwStyle, const RECT& rect, CWin* pParentWnd, UINT nID) 
{
	// TODO: Add your specialized code here and/or call the base class
	pParent= pParentWnd;
	m_DOCKSITE=nID;
	LPCTSTR lpclassname=RegisterDefaultClass(NULL,WS_CHILD|WS_VISIBLE);
	return CWin::Create(lpclassname, _T(""), dwStyle, rect, pParentWnd->GetSafeHwnd(), nID);
}

int CContainer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CToolTip.Create(GetSafeHwnd(),TTS_ALWAYSTIP);
	CToolTip.Activate(TRUE);
	CToolTip.BringWindowToTop();
	if (!m_img.Create(IDB_GUI_DOCKBAR,9,11,RGB(255,0,255)))
	{
		return -1;
	}

	m_CloseBtn.SetData(5,_T("Close"));
	m_CloseBtn.SetImageList(IDB_GUI_DOCKBAR,9,10,RGB(255,0,255));
	m_AutoHideBtn.SetData(11,_T("Auto Hide"));
	m_AutoHideBtn.SetImageList(IDB_GUI_DOCKBAR,9,15,RGB(255,0,255));
	// TODO: Add your specialized creation code here
	return 0;
}


BOOL CContainer::OnNcCalcSize(BOOL /*bCalcValidRects*/, LPNCCALCSIZE_PARAMS lpncsp)
{
	// adjust non-client area for border space
	
	if (m_bCaption && m_DOCKFLOAT !=BS_FLOATING)
		lpncsp->rgrc[0].top +=19;
	
	return TRUE;
}

void CContainer::OnNcPaint(HRGN hRgn)
{
	// TODO: Add your message handler code here
	// Do not call CControlBar::OnNcPaint() for painting messages
	// Tomo la misma rutina que se desarrolla para la clase
	// CGuiToolBarWnd.
	CRect rcWindow;
	CRect rcClient;
	CGDI	dc(::GetWindowDC(GetSafeHwnd()));
	CGDI			m_dc;		//contexto de dispositivo en memoria
	CBitmap		m_bitmap;
	//la idea es tomar el area de la ventana y area  cliente , luego debemos
	//igualar el area de coordenadas de ventana al cliente
	GetWindowRect(&rcWindow);
	GetClientRect(&rcClient);
	ScreenToClient(rcWindow);
	
	
    ::OffsetRect(rcClient, -rcWindow.left,-rcWindow.top);
	::OffsetRect(rcWindow, -rcWindow.left,-rcWindow.top);
	
	m_dc.CreateCompatibleDC(dc.m_hDC);
	m_bitmap.CreateCompatibleBitmap(dc.m_hDC,rcWindow.Width(),rcWindow.Height());
	CBitmap m_OldBitmap((HBITMAP)m_dc.SelectObject(&m_bitmap));
	CBrush cb;
	cb.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
	m_dc.FillRect(rcWindow, &cb);
	if (m_bCaption)
		DrawGripper(&m_dc,rcWindow);
	dc.IntersectClipRect(rcWindow);
    dc.ExcludeClipRect(rcClient);//asi evitamos el parpadeo
	dc.BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),m_dc.m_hDC,0,0,SRCCOPY);
	m_dc.SelectObject(&m_OldBitmap);
	m_bitmap.DeleteObject();
	m_dc.DeleteDC();
	cb.DeleteObject ();
	dc.DeleteDC();
	
}
void CContainer::DrawGripper(CGDI* dc,CRect rcWin)
{

	CRect rc=rcWin;
	rc.bottom=rc.top+18;
	
	CBrush cb;
	cb.CreateSolidBrush(CDrawLayer::GetRGBPressBXP());
	dc->FillRect(rc, &cb);
	cb.DeleteObject ();
	dc->Draw3dRect(rc,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
	//CGradient M(CSize(rc.Width(),rc.Height()+4));	
	//M.PrepareVertical(dc);
	//M.Draw(dc,rc.left,rc.top+1,0,0,rc.Width(),rc.Height()+4,SRCCOPY);

	int OldMode=dc->SetBkMode(TRANSPARENT);
	CFont cf;
	
	COLORREF clrtext;
	clrtext=dc->SetTextColor(::GetSysColor (COLOR_MENUTEXT));	
	cf.CreateFont(-11,2,0,0,FW_NORMAL,0,0,0,0,1,2,1,34,"MS Sans Serif");
	
	HFONT cff=dc->SelectObject(cf);	
	
	//guardar espacio para la imagen
	
	CTab* ct=(CTab*) m_pArray[m_iSelectTab];
	
	TCHAR m_cadBreak[126];
	memset(m_cadBreak,0x00,126);
	lstrcpy(m_cadBreak,ct->lpMsg);
	int contt;
	int cont =contt=strlen(m_cadBreak);
	CSize coor=dc->GetTextExtent(m_cadBreak,cont);
	rc.left+=3;
	if ( coor.cx > (rc.Width()-35))
	{
		rc.left+=1;
		while(cont > 1 )
		{
			TCHAR m_scadtemp[64];
			memset(m_scadtemp,0x00,64);
			lstrcpy(m_scadtemp,m_cadBreak);
			lstrcat(m_scadtemp,_T("..."));
			CSize coor=dc->GetTextExtent(m_scadtemp,lstrlen(m_scadtemp));
			if(coor.cx > (rc.Width()-35))
				*(m_cadBreak+cont)=NULL;
			else
				break;
			cont--;
		}
		lstrcat(m_cadBreak,_T("..."));
		rc.right+=3;

		
			dc->DrawText(m_cadBreak,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	}
	else
			dc->DrawText(ct->lpMsg,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);

	//-------------------------
	//No Client Button
	//-------------------------
	rc=rcWin;
	rc.left=rcWin.right-18;
	rc.bottom=rc.top+18;
	rc.right-=7;
	rc.top+=3;
	rc.bottom-=3;
	if (m_DOCKFLOAT !=BS_FLOATING)
	{
		m_rcAutoHideBtn=rc;
		m_rcAutoHideBtn.right-=12;
		m_rcAutoHideBtn.left-=12;
	}
	m_rcCloseBtn=rc;

	if (m_bCaption)
	{
		m_CloseBtn.Paint(dc,m_stateBtn,m_rcCloseBtn,CDrawLayer::GetRGBPressBXP(),TRUE );
		//if (m_DOCKFLOAT !=BS_FLOATING)
		//	m_AutoHideBtn.Paint(dc,m_stateAHBtn,m_rcAutoHideBtn,CDrawLayer::GetRGBGray(),TRUE);
	}
	
    
	dc->SelectObject(cff);	
	cf.DeleteObject();
	
}

BOOL CContainer::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_DragTab)
	{
		m_DragTab=FALSE;
		m_TabMove=0;
		m_pointbase=CPoint(0,0);
		ReleaseCapture();
	}
	Default();
	return TRUE;
}

void CContainer::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	BOOL bDif=FALSE;
	if (m_NCDragWindow)
		bDif=abs(m_pointbase.x -point.x) >3 || abs(m_pointbase.y -point.y) >3;
	

	if (m_NCDragWindow)
	{
		if( (m_DOCKFLOAT !=BS_FLOATING) && bDif)
		{
		
			if (!m_NCDragWindow) return; 
		
			CRect rcw;
            //GetWindowRect(rcw);		
			ClientToScreen(&point);
			ReleaseCapture();
			m_DOCKFLOAT=BS_FLOATING;
			m_DragTab=FALSE;
			m_NCDragWindow=FALSE;
			UINT uFirstTab=0;
			int iCont=0;
			for (iCont=0; iCont< m_Numtabs;iCont++)
			{
				CTab* ct=(CTab*) m_pArray[iCont];
				if (ct->rect.PtInRect(point) != 0)
				{	
				
					if (iCont==0)
						uFirstTab=((CDockPanelBase*)ct->pParent)->GetDlgCtrlID();
					((CDockPanelBase*)ct->pParent)->uAling=BS_FLOATING;
					((CDockPanelBase*)ct->pParent)->iLasPosition=iCont;
					((CDockPanelBase*)ct->pParent)->bIsPartOfTabbed=iCont==0? FALSE:TRUE;
					((CDockPanelBase*)ct->pParent)->bIsShow=TRUE;
					((CDockPanelBase*)ct->pParent)->m_IdCtrlParent=iCont==0? 0:uFirstTab;	
					rcw=ct->rect;
				
				}
			}

			theApp->m_WinMain->FloatWindow(this,point,rcw);
		
			DockManager* mDoc;
			if (m_DOCKSITE == BS_ALIGN_BOTTOM)
				mDoc=(DockManager*)theApp->m_WinMain->m_DockBottom;
			if (m_DOCKSITE == BS_ALIGN_LEFT)
				mDoc=(DockManager*)theApp->m_WinMain->m_DockLeft;
			if (m_DOCKSITE == BS_ALIGN_RIGHT)
				mDoc=(DockManager*)theApp->m_WinMain->m_DockRight;
			mDoc->DeleteWindow(
			mDoc->FindItem(GetSafeHwnd())
				);
			theApp->m_WinMain->UpdateFrame();

		}
		
		return ;
	}

	if (nHitTest == HTCLOSE)
		if (m_stateBtn != NORMAL) 
			return;

	if (nHitTest == HTPIN)
		if (m_stateAHBtn != NORMAL) 
			return;

	if (nHitTest == HTCLOSE)
	{
		m_stateBtn=OVER;
		SetTimer(1,100,0);
	}

	if (nHitTest == HTPIN)
	{
		m_stateAHBtn=OVER;
		SetTimer(2,100,0);
	}

	SendMessage(WM_NCPAINT,0,0);
	Default();

}

void CContainer::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (m_NCDragWindow) return;

	if( nHitTest == HTCAPTION)
	{
		m_NCDragWindow=TRUE;
		//SetCapture();
		m_pointbase=point;
		SetFocus();
		return ;
	}
	else if( nHitTest == HTCLOSE)
	{
		m_stateBtn=PRESS;
		SendMessage(WM_NCPAINT,0,0);
		return;
	}
	else if( nHitTest == HTPIN)
	{
		m_stateAHBtn=PRESS;
		SendMessage(WM_NCPAINT,0,0);
		return;
	}
	//--------------------------

	Default();	


}


void CContainer::ShowPane(BOOL bShow) 
	 { 
		 m_close=!bShow; 
		 ShowWindow(bShow==TRUE?SW_SHOW:SW_HIDE);
	 }
BOOL CContainer::IsClosePane()
	 { 
		 return m_close;
	 }
void CContainer::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (nHitTest == HTCAPTION) 
	{
		
		if(nHitTest == HTCAPTION)
		{
				if (m_NCDragWindow) 
				{
					ReleaseCapture();
					m_NCDragWindow=FALSE;	
					return;
				}

		}

	}

	CRect rc;
	//------------------ para el boton
	CRect rcT=m_rcCloseBtn;
	ClientToScreen(rcT);
	point.y+=20;
	point.x+=1;
	if (rcT.PtInRect(point))
	{
		if (m_stateBtn ==PRESS)
		{
			if (IsWindowVisible())
			{
				//if (m_Numtabs==1)
					ShowPane(FALSE);
				//else
				//	DeleteTab(m_iSelectTab);
			}
			else
				ShowPane(TRUE);
			if (m_DOCKSITE == BS_ALIGN_BOTTOM)
				((DockManager*)theApp->m_WinMain->m_DockBottom)->EveryWindowsInsert();
			if (m_DOCKSITE == BS_ALIGN_LEFT)
				((DockManager*)theApp->m_WinMain->m_DockLeft)->EveryWindowsInsert();
			if (m_DOCKSITE == BS_ALIGN_RIGHT)
				((DockManager*)theApp->m_WinMain->m_DockRight)->EveryWindowsInsert();
			theApp->m_WinMain->UpdateFrame();
			//::SendMessage(GetParent(),WM_SIZE,0,0);
		}

	}

	if (m_stateBtn ==PRESS)
	{
		m_stateBtn=NORMAL;
		KillTimer(1);
		SendMessage(WM_NCPAINT,0,0);
		return;

	}

	rcT=m_rcAutoHideBtn;
	ClientToScreen(rcT);
	if (rcT.PtInRect(point))
	{
	
	}

	if (m_stateAHBtn ==PRESS)
	{
		m_stateAHBtn=NORMAL;
		KillTimer(1);
		SendMessage(WM_NCPAINT,0,0);
		return;
	}
	

	Default();
}

UINT CContainer::OnNcHitTest(CPoint cp)
{

	CRect rcWindow;
	//no se convierte las coordenadas de pantalla porque el punto
	//entregado por esta función esta dado en el mismo sentido.
	GetWindowRect(rcWindow);
	rcWindow.bottom=rcWindow.top+16;
	CRect rcT=m_rcCloseBtn;
	CPoint cpn;
	ClientToScreen(rcT);
	CPoint pt=cp;
	pt.y+=20; //I don't know? but if you don't make this no check the point.
	pt.x+=1;
	if (rcT.PtInRect(pt))
		return HTCLOSE;
	
	rcT=m_rcAutoHideBtn;
	
	ClientToScreen(rcT);
	pt=cp;
	pt.y+=20;
	pt.x+=1;
	if (rcT.PtInRect(pt))
		return HTPIN;
	
	
	if (rcWindow.PtInRect(cp))
	{
		SetCursor(::LoadCursor(NULL,IDC_ARROW));
		return HTCAPTION;
	}

	return Default();
}


void CContainer::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	
	//button routines
	if (nIDEvent == 1)
	{
		if (m_stateBtn==NORMAL) return;
		CRect rc;
		CPoint pt(GetMessagePos());

		CRect rcT=m_rcCloseBtn;
		ClientToScreen(rcT);
		pt.y+=23;
		pt.x+=5;
		if (!rcT.PtInRect(pt))
		{
			m_stateBtn=NORMAL;
			KillTimer(1);
			SendMessage(WM_NCPAINT,0,0);
		}
	}

	if (nIDEvent == 2)
	{
		if (m_stateAHBtn==NORMAL) return;
		CRect rc;
		CPoint pt(GetMessagePos());

		CRect rcT=m_rcAutoHideBtn;
		ClientToScreen(rcT);
		pt.y+=23;
		pt.x+=5;
		if (!rcT.PtInRect(pt))
		{
			m_stateAHBtn=NORMAL;
			KillTimer(2);
			SendMessage(WM_NCPAINT,0,0);
		}
	}

	
	Default();
}

void CContainer::RecalLayout()
{
	GetClientRect(m_rectCliente);

	if (m_style == S3D)
	{
		if (m_Numtabs > 1)
			m_rectCliente.bottom=m_rectCliente.bottom-(m_sizeImag.cy+SPACE_TAB-1);
	}
	else
	{
		if (m_alnTab==ALN_BOTTOM)
			m_rectCliente.bottom=m_rectCliente.bottom-(DEFAULT_FLAT+1);
		else
		{
			m_rectCliente.top+=DEFAULT_FLAT;
			m_rectCliente.bottom=m_rectCliente.bottom-(DEFAULT_FLAT+4);

		}
	}

	for (int iCont=0; iCont< m_Numtabs;iCont++)
	{
		CTab* ct=(CTab*) m_pArray[iCont];
		CWin* m_tempWin= ct->pParent;
		ASSERT(m_tempWin);
		CRect mrc;
				
		if (m_style == S3D)
		{
			   m_tempWin->SetWindowPos(NULL,m_rectCliente.left+(SPACE_TAB-4),
			   m_rectCliente.top+(SPACE_TAB/2),m_rectCliente.right-(SPACE_TAB-4),
			   m_rectCliente.bottom-((SPACE_TAB)),SWP_NOACTIVATE|
			   SWP_NOZORDER);
		}
		else
		{
			if (m_alnTab==ALN_BOTTOM)	
			{
			   	   
			   m_tempWin->SetWindowPos(NULL,m_rectCliente.left+(SPACE_TAB-3),
			   m_rectCliente.top+1,m_rectCliente.right-1,
			   m_rectCliente.bottom-1,SWP_NOACTIVATE|SWP_NOZORDER);
			}
			else
			{ 
				  m_tempWin->SetWindowPos(NULL,m_rectCliente.left+(SPACE_TAB-4),
				  m_rectCliente.top+7,m_rectCliente.right-4,
				  m_rectCliente.bottom-4,SWP_NOACTIVATE|SWP_NOZORDER);
			}
		}
	}
	AjustTabs();
	Invalidate();
	UpdateWindow();
}


void CContainer::AjustTabs()
{
	int m_iSizeAct=0;
	m_iMinValRec=4;

	if (m_Numtabs <=1 && m_alnTab==ALN_BOTTOM)
		return;
	CClientDC dc(GetSafeHwnd());
	GetClientRect(m_rectCliente);
	if (m_alnTab==ALN_BOTTOM)
		m_rectCliente.bottom=m_rectCliente.bottom-(m_sizeImag.cy+SPACE_TAB+2);
	else
		m_rectCliente.bottom=m_rectCliente.top+(m_sizeImag.cy+SPACE_TAB+2);

	HFONT hFont= dc.SelectObject(CFont((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	for (int iCont=0; iCont< m_Numtabs;iCont++)
	{
		CTab* ct=(CTab*) m_pArray[iCont];
		CRect m_Arect;
		CSize m_sChar=dc.GetTextExtent(ct->lpMsg,lstrlen(ct->lpMsg));
		m_Arect.left=m_iMinValRec+1;
		CSize m_sz;
		m_sz=theApp->m_WinMain->m_sizeImagDocks;
		m_iMinValRec+=m_alnTab!=ALN_TOP?16+2+m_sChar.cx+6:m_sChar.cx+6;
		if(m_alnTab==ALN_BOTTOM)
		{
			m_Arect.top=m_rectCliente.bottom;
			m_Arect.right=m_iMinValRec;
			m_Arect.bottom=m_rectCliente.bottom+6+m_sizeImag.cy;
		}
		else
		{
			m_Arect.top=m_rectCliente.top;
			m_Arect.right=m_iMinValRec+ (iCont ==m_iSelectTab|| iCont ==0 ?30:0);
			m_Arect.bottom=m_rectCliente.top+6+m_sizeImag.cy;
		}
		ct->rect= m_Arect;
		
	}		
	//si el espacio requerido es mayor que el disponible
	//se debe proporcionar cada tab solo si es 3d
	if (m_style== S3D)
	{
		int m_NewResize=4;
		if (m_iMinValRec > m_rectCliente.Width()-4)
		{
			m_iSizeAct=(m_rectCliente.Width()-12)/m_Numtabs;
			for (int iCont=0; iCont< m_Numtabs;iCont++)
			{
				CTab* ct=(CTab*) m_pArray[iCont];
				CRect m_Arect;
				m_Arect.left=m_NewResize;
				m_Arect.right=m_NewResize+m_iSizeAct;
				m_Arect.top=m_rectCliente.bottom;
				m_Arect.bottom=m_rectCliente.bottom+6+m_sizeImag.cy;
				m_NewResize+=m_iSizeAct+1;
				ct->rect= m_Arect;
			}	
		}
	}
dc.DeleteDC();
}
void CContainer::Drawtabs(CGDI* dc)
{
	CPen light;
	CPen Dark;
	CPen Black;	
	CPen Face;

	if ( m_Numtabs <= 1 && m_alnTab==ALN_BOTTOM) return;
	light.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNHIGHLIGHT));
	Dark.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW));
	Black.CreatePen(PS_SOLID,1,GetSysColor(BLACK_PEN));	
	Face.CreatePen(PS_SOLID,1,CDrawLayer::GetRGBColorFace());	
	CRect rectText;
	HFONT hFONT= dc->SelectObject(CFont((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CPen oldPen= dc->SelectObject(&Dark);
	LPCSTR szStrPoints=_T("...");
	for (int iCont=0; iCont< m_Numtabs;iCont++)
	{
		CTab* ct=(CTab*) m_pArray[iCont];
		if (iCont ==m_iSelectTab)
		{
			CGradient M(CSize(ct->rect.Width(),ct->rect.Height()+1));	
			M.PrepareTabs(dc,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorWhite());
			M.Draw(dc,ct->rect.left,ct->rect.top,0,0,ct->rect.Width(),ct->rect.Height(),SRCCOPY);
			dc->SelectObject(&Dark);
		
			dc->MoveTo(ct->rect.left,ct->rect.top);
			dc->LineTo(ct->rect.left,ct->rect.bottom-2);
			dc->MoveTo(ct->rect.left+1,ct->rect.bottom-2);
			dc->LineTo(ct->rect.left+2,ct->rect.bottom-1);
			
			//corner left corrections begin
			dc->SelectObject(&Face);
			dc->MoveTo(ct->rect.left,ct->rect.bottom-2);
			dc->LineTo(ct->rect.left,ct->rect.bottom-1);

			dc->MoveTo(ct->rect.left,ct->rect.bottom-1);
			dc->LineTo(ct->rect.left+2,ct->rect.bottom-1);
			//---corner corrections end
			
			dc->SelectObject(&Dark);
			dc->MoveTo(m_rectTab.left,ct->rect.top);
			dc->LineTo(ct->rect.left,ct->rect.top);

			dc->MoveTo(ct->rect.right,ct->rect.top);
			dc->LineTo(m_rectTab.right,ct->rect.top);

			//line bottom
			dc->SelectObject(&Dark);
			dc->MoveTo(ct->rect.left+2,ct->rect.bottom-1);
			dc->LineTo(ct->rect.right-3,ct->rect.bottom-1);
			
			dc->SelectObject(&Face);
			dc->MoveTo(ct->rect.left+2,ct->rect.bottom-2);
			dc->LineTo(ct->rect.right-3,ct->rect.bottom-2);

			//right corner
			dc->SelectObject(&Dark);
			dc->MoveTo(ct->rect.right-3,ct->rect.bottom-1);
			dc->LineTo(ct->rect.right,ct->rect.bottom-4);

			dc->SelectObject(&Face);
			dc->MoveTo(ct->rect.right-3,ct->rect.bottom-2);
			dc->LineTo(ct->rect.right-1,ct->rect.bottom-5);
			
			// corner right corrections
			dc->MoveTo(ct->rect.right-1,ct->rect.bottom-2);
			dc->LineTo(ct->rect.right,ct->rect.bottom-2);
			dc->MoveTo(ct->rect.right-2,ct->rect.bottom-1);
			dc->LineTo(ct->rect.right,ct->rect.bottom-1);

			// end corner right corrections


			//right vertical line
			dc->SelectObject(&Dark);
			dc->MoveTo(ct->rect.right-1,ct->rect.top);
			dc->LineTo(ct->rect.right-1,ct->rect.bottom-3);
			
			dc->SelectObject(&Face);
			dc->MoveTo(ct->rect.right-2,ct->rect.top+1);
			dc->LineTo(ct->rect.right-2,ct->rect.bottom-3);
		
		
		}
		else
		{
			if(iCont !=0 && ((iCont-1)!= m_iSelectTab))
			{
				dc->SelectObject(&Dark);
				dc->MoveTo(ct->rect.left,ct->rect.top+3);
				dc->LineTo(ct->rect.left,ct->rect.bottom-3);
			}
		}
	
		//se dibuja el icono
		int nMode = dc->SetBkMode(TRANSPARENT);
		CSize m_sChar=dc->GetTextExtent(ct->lpMsg,strlen(ct->lpMsg));
		COLORREF clrtext=RGB(0,0,0);
		if (iCont !=m_iSelectTab)
			clrtext=dc->SetTextColor(CDrawLayer::GetRGBColorGrayText());
		
		if (theApp->m_WinMain->m_sizeImagDocks.cx+m_sChar.cx < ct->rect.Width()-6)  
		{
			//Image.Draw(ct->uIcon,dc->m_hDC,CPoint(ct->rect.left+5,ct->rect.top+2),ILD_TRANSPARENT);
			theApp->m_WinMain->DrawIconDocks(ct->pParent->GetNumIcon(),CPoint(ct->rect.left+4,ct->rect.top+2),dc);
			rectText=ct->rect;
			rectText.left+=theApp->m_WinMain->m_sizeImagDocks.cx+6;
			rectText.right-=2;
			dc->DrawText(ct->lpMsg,rectText,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
			CToolTip.SetToolRect(GetSafeHwnd(),CRect(0,0,0,0),iCont+1);
		}
		else
		{
			//verificamos si se puede poner algun texto o
			//por lo memos el icono
			if (theApp->m_WinMain->m_sizeImagDocks.cx < ct->rect.Width())
			{
				//Image.Draw(ct->uIcon,dc->m_hDC,CPoint(ct->rect.left+4,ct->rect.top+2),ILD_TRANSPARENT);
				theApp->m_WinMain->DrawIconDocks(ct->pParent->GetNumIcon(),CPoint(ct->rect.left+4,ct->rect.top+2),dc);
				rectText=ct->rect;
				rectText.left+=theApp->m_WinMain->m_sizeImagDocks.cx+6;
				rectText.right-=5;
				LPCSTR m_cadBreak=ct->lpMsg;
				int c=0;
				dc->DrawTextAjust(rectText,ct->lpMsg,DT_SINGLELINE|DT_LEFT|DT_VCENTER,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
				rectText.right+=3;
				CToolTip.SetToolRect(GetSafeHwnd(),&ct->rect,iCont+1);
				
			}
			
		
			
		}
		if (iCont !=m_iSelectTab)
				dc->SetTextColor(clrtext);
		dc->SetBkMode(nMode);
		
	}	
	szStrPoints=NULL;
	dc->SelectObject(&oldPen);
	light.DeleteObject();
	Dark.DeleteObject();
	Black.DeleteObject();	
	Face.DeleteObject();

}



CWin* CContainer::GetActiveWnd () 
{
		return m_Numtabs == -1 ? NULL : 
		((CTab*) m_pArray [m_Numtabs])->pParent;
}

int CContainer::FindItem(HWND hWnd)
{
	for (int iCont=0; iCont< m_Numtabs;iCont++)
	{
		CTab* ct=(CTab*) m_pArray[iCont];
		if (ct->pParent->GetSafeHwnd() == hWnd)
		    return iCont;
	}
	return -1;

}

CTab* CContainer::GetTab(int nTab)
{
		if (nTab > m_Numtabs)
			return NULL;
		else
		{
			if (m_pArray.GetSize() < 1) return NULL;
			return (CTab*) m_pArray [nTab];
		}

	return NULL;
}

CWin*  CContainer::GetNumWnd(int m_numtab) 
{
        if (m_numtab > m_Numtabs)
			return NULL;
		else
		{
			if (m_pArray.GetSize() < 1) return NULL;
			CWin* pw=((CTab*) m_pArray [m_numtab])->pParent;
			if (HIWORD(pw)== NULL) return NULL;
			else
			  return ((CTab*) m_pArray [m_numtab])->pParent;
		}
}

void CContainer::UpdateCaption(CWin* pWnd,LPCSTR m_Title)
{
	for (int iCont=0; iCont< m_Numtabs;iCont++)
	{
		CTab* ct=(CTab*) m_pArray[iCont];
		if (ct->pParent->GetSafeHwnd() == pWnd->GetSafeHwnd())
		{
			LPCSTR x=ct->lpMsg;
			if(x!=m_Title)
			{
				strcpy(ct->lpMsg,m_Title);
				::SendMessage(GetParent(),WM_SIZE,0,0);
				RecalLayout();
			}
			break;
		}
	}
	
}
void CContainer::ShowTitle(LPCSTR m_Caption)
{
	if (m_ActualTitle==TRUE)
	{
		CWin* pParent=reinterpret_cast<CWin*>(GetParent());
		pParent->SetWindowText(m_Caption);
		//pParent->SendMessage(WM_COMMAND,WM_SHOWTITLE);
	}
	
}

void CContainer::Addtab(CWin* pParent, LPCSTR lpMsg, UINT uHmenu)
{
	ASSERT(pParent);
	
			
	m_pArray.SetAtGrow(m_Numtabs,new CTab(pParent,lpMsg, uHmenu));
	if (m_Numtabs==0)
	{
		pParent->ShowWindow(SW_SHOW);
		m_iSelectTab=0;
	}
	else
	{
		pParent->ShowWindow(SW_SHOW);
		CTab* ctn=(CTab*) m_pArray[m_iSelectTab]; 	
		ctn->pParent->ShowWindow(SW_HIDE);
		pParent->SetFocus();
	}
	m_iSelectTab=m_Numtabs;
	CTab* ctn=(CTab*) m_pArray[m_iSelectTab]; 	
	m_Numtabs++;
		
	//if (m_style == S3D)
	CToolTip.AddTool(GetSafeHwnd(),ctn->lpMsg,CRect(0,0,0,0),m_Numtabs);
	RecalLayout();
}



void CContainer::DeleteTab(int m_numtab)
{
	if (m_numtab < m_Numtabs)
	{
		CTab* ctn=(CTab*) m_pArray[m_numtab]; 	
		if (m_alnTab!=ALN_TOP)
			ASSERT(ctn->pParent);
		if (ctn)
			delete ctn;
		m_Numtabs--;
		m_pArray.RemoveAt(m_numtab,1);
		if (m_Numtabs >0)
		{
			if (m_iSelectTab == m_numtab)
			{
				m_iSelectTab=m_iSelectTab-1;
				if (m_iSelectTab< 0) m_iSelectTab=0;
				CTab* ctn =(CTab*) m_pArray[m_iSelectTab];
				CWin* pParentNew=ctn->pParent;
				ASSERT(pParentNew);
				pParentNew->ShowWindow(SW_SHOW);
			}
			else
			{
				if (m_iSelectTab > m_numtab)
				{
					m_iSelectTab--;
				}
			}
			
			RecalLayout();
		}
		
	}
}

BOOL CContainer::OnSize(UINT nType, int cx, int cy) 
{
	if (m_Numtabs > 0)
		RecalLayout();
	Invalidate();
	UpdateWindow();
	return TRUE;
}


void CContainer::SetCurtab(int m_numtab)
{
	if (m_numtab < m_Numtabs && m_numtab != m_iSelectTab )
	{
		CTab* ctn=(CTab*) m_pArray[m_numtab]; 
		CWin* pParentNew= ctn->pParent;
		CTab* ct =(CTab*) m_pArray[m_iSelectTab];
		CWin* pParentActual=ct->pParent;
		ASSERT(pParentNew);
		ASSERT(pParentActual);
	
		{
			pParentActual->ShowWindow(SW_HIDE);
			pParentNew->ShowWindow(SW_SHOW);
			pParentNew->SetFocus();
			
		}
		
		m_iSelectTab=m_numtab;
		SendMessage(WM_NCPAINT,0,0);
		RecalLayout();
	}

}

int CContainer::GetCurtab()
{
	return m_iSelectTab;
}

void CContainer::OnMouseMove(UINT nHitTest, CPoint point)
{

	if (m_NCDragWindow)
	{
		if( ((nHitTest != HTCAPTION) && (m_DOCKFLOAT !=BS_FLOATING)) && m_TypeTab != TYPE_MDI)
		{
		
			if (!m_NCDragWindow) return; 
		
			CRect rcw;
            GetWindowRect(rcw);		
			ClientToScreen(&point);
			ReleaseCapture();
			m_DOCKFLOAT=BS_FLOATING;
			m_DragTab=FALSE;
			m_NCDragWindow=FALSE;
			UINT uFirstTab=0;
			int iCont=0;
			for (iCont=0; iCont< m_Numtabs;iCont++)
			{
				CTab* ct=(CTab*) m_pArray[iCont];
				if (ct->rect.PtInRect(point) != 0)
				{	
				
					if (iCont==0)
						uFirstTab=((CDockPanelBase*)ct->pParent)->GetDlgCtrlID();
					((CDockPanelBase*)ct->pParent)->uAling=BS_FLOATING;
					((CDockPanelBase*)ct->pParent)->iLasPosition=iCont;
					((CDockPanelBase*)ct->pParent)->bIsPartOfTabbed=iCont==0? FALSE:TRUE;
					((CDockPanelBase*)ct->pParent)->bIsShow=TRUE;
					((CDockPanelBase*)ct->pParent)->m_IdCtrlParent=iCont==0? 0:uFirstTab;	
				
				}
			}

			theApp->m_WinMain->FloatWindow(this,point,rcw);
		
			DockManager* mDoc;
			if (m_DOCKSITE == BS_ALIGN_BOTTOM)
				mDoc=(DockManager*)theApp->m_WinMain->m_DockBottom;
			if (m_DOCKSITE == BS_ALIGN_LEFT)
				mDoc=(DockManager*)theApp->m_WinMain->m_DockLeft;
			if (m_DOCKSITE == BS_ALIGN_RIGHT)
				mDoc=(DockManager*)theApp->m_WinMain->m_DockRight;
			mDoc->DeleteWindow(
			mDoc->FindItem(GetSafeHwnd())
				);
			theApp->m_WinMain->UpdateFrame();

		}
		
		return ;
	}
	if (m_DragTab)
	{
		CTab* ct=(CTab*) m_pArray[m_TabMove];
		if (ct->rect.PtInRect(point) != 0)	
		{
			// we are in the same tab so don't do nothing
			return;
		}
		else
		{
			int iCont;
			for (iCont=0; iCont< m_Numtabs;iCont++)
			{
				CTab* ct=(CTab*) m_pArray[iCont];
				if (ct->rect.PtInRect(point) != 0)
				{	
					m_InTab=TRUE;
					m_DragTab=TRUE; //DragTab
					//umm interchange the pointers
					NewBValArray<CTab*> m_pTemp; 
					CTab* Temp=(CTab*) m_pArray[m_TabMove];
					m_pArray.SetAt(m_TabMove,ct);
					m_pArray.SetAt(iCont,Temp);
					SetCurtab(iCont);
					CToolTip.UpdateTipText(GetSafeHwnd(), ct->lpMsg,CRect(0,0,0,0), m_TabMove+1);
					CToolTip.UpdateTipText(GetSafeHwnd(), Temp->lpMsg,CRect(0,0,0,0), iCont+1);
					m_TabMove=iCont; //This is moved
					
					ReleaseCapture();
					break;
				}
				
			}

			if ((iCont >= m_Numtabs) && (m_TypeTab != TYPE_MDI))
			{
				CRect rcClient;
				GetClientRect(&rcClient);

				CContainer* ctn= new CContainer;
				CTab* ct=(CTab*) m_pArray[m_TabMove];
				ctn->m_pContainer=this;
	
				rcClient.top=ct->rect.top;
				rcClient.bottom=ct->rect.bottom;
			
				if (rcClient.PtInRect(point))
				{
					return;
				}
				if (!ctn->Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,ct->pParent->GetDlgCtrlID()))
					return;
				ctn->Addtab(ct->pParent,ct->lpMsg,ct->nMenu);
				ct->pParent->SetParent(ctn);
			
				//ctn->SetImageList(Image);
				ClientToScreen(&point);
				ctn->m_DOCKFLOAT=BS_FLOATING;
				ctn->m_DOCKSITE=GetWindowLong(GetSafeHwnd(),GWL_ID);
				HWND hwnd=(HWND)GetWindowLong(ct->pParent->GetSafeHwnd(),GWL_HWNDPARENT);
				HWND hWnd1=ctn->GetSafeHwnd();
				CRect rcw;
                GetWindowRect(rcw);	
				theApp->m_WinMain->FloatWindow(ctn,point,rcw);
				m_DragTab=FALSE;
				DeleteTab(m_TabMove);
				if (m_pArray.GetSize() > 0)
				{
					ct=(CTab*) m_pArray[0];
					ct->pParent->ShowWindow(SW_SHOW);
					ct->pParent->SetFocus();
				}
				m_TabMove=-1;
				ReleaseCapture();
			}
	
		}
	}
}

BOOL CContainer::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	for (int iCont=0; iCont< m_Numtabs;iCont++)
	{
		CTab* ct=(CTab*) m_pArray[iCont];
		if (ct->rect.PtInRect(point) != 0)
		{
            SetCurtab(iCont);
			m_InTab=TRUE;
			m_DragTab=TRUE; //DragTab
			m_TabMove=iCont; //This is moved
			SetCapture();
			break;
		}
		
	}

	return TRUE;

}

void CContainer::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	ShowMenu(point);
}



void CContainer::ShowMenu(CPoint point)
{
		CMenu m_menu;
		CRect rc;
		GetWindowRect(rc);
		if (((CTab*)m_pArray[m_iSelectTab])->nMenu > 0 )
		{
			CMenu m_menu;
			m_menu.LoadMenu((LPCTSTR)((CTab*)m_pArray[m_iSelectTab])->nMenu);
			CMenu m_SubMenu = m_menu.GetSubMenu(0);
			CRect rc=((CTab*)m_pArray[m_iSelectTab])->rect;
			m_SubMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
					point.x, point.y, theApp->GetMainWindows()->GetSafeHwnd(), &rc);
		
		}
		
}

BOOL CContainer::OnRButtonDown(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	ShowMenu(point);
	return TRUE;
}


void CContainer::SetStyle(Style estyle)
{
	m_style=estyle;
}

int CContainer::OnDestroy()
{
	// Libera la memoria
    for( int i=0; i<m_Numtabs; i++ )
    {
    CTab *pTab = (CTab*)m_pArray.GetAt(i);
    if( pTab )
	{
		pTab->pParent=NULL;
        delete pTab;
	}
    }
	return TRUE;

	// TODO: Add your message handler code here
}



void  CContainer::SetTabMenu(LPCTSTR lpszMenuName)
{
	m_hMenu=lpszMenuName;
}


BOOL CContainer::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	CWin* pParent= reinterpret_cast<CWin*>(GetParent());
	
	if (pParent->GetSafeHwnd())
		pParent->SendMessage(WM_NOTIFY, wParam, lParam);
	
	return TRUE;
}

BOOL CContainer::OnSetCursor(HWND hWnd, UINT nHitTest, UINT message)
{
	CPoint ptCurPos;
	GetCursorPos(&ptCurPos);
	ScreenToClient(&ptCurPos);
	
	//if (m_rectTab.PtInRect(ptCurPos))
	{
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return TRUE;
	}
	
	Default();
	return TRUE;
	
}
