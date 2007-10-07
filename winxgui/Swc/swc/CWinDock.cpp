/*
 * <F> CWinDock.cpp		1.0  
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/


#include "stdafx.h"




DockManager::DockManager()
{
	m_DockWindows.RemoveAll();
	m_Splits.RemoveAll();
	m_Aling=0;		
    m_lastAling=0;	
	m_Visible=TRUE;		
	m_MiniDock=NULL;		
  	m_Splitter=CRect(0,0,0,0);	
	m_OldSplitter=CRect(0,0,0,0);
	m_pParent=NULL;
	m_NumWins=0;
	m_NumSep=0;
	m_SplitMove=0;
	m_DragSplitter=FALSE;
	m_DragSplitterInside=FALSE;
}

DockManager::~DockManager()
{
	m_DockWindows.RemoveAll();
	m_Splits.RemoveAll();
	
}

BOOL DockManager::IsFloating()
{
	return m_Aling==BS_ALIGN_FLOAT;
}

BOOL DockManager::IsVertical()
{
	return (m_Aling== BS_ALIGN_LEFT) || (m_Aling== BS_ALIGN_RIGHT);
}

BOOL DockManager::IsHorz()
{
	return m_Aling == BS_ALIGN_BOTTOM;
}
BOOL DockManager::IsLeft()
{
	return m_Aling== BS_ALIGN_LEFT;
}
BOOL DockManager::IsRight()
{
	return m_Aling== BS_ALIGN_RIGHT;
}
/////////////////////////////////////////////////////////////////////////////
// DockManager message handlers


//****************************************************************************
BOOL DockManager::OnEraseBkgnd(HDC hDC) 
{
	// TODO: Add your message handler code here and/or call default
	CGDI pDC(hDC);
	if (m_NumWins == 0)
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


BOOL DockManager::OnPaint(HDC hDC) 
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
		
	//paint routines

	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	cbr.DeleteObject();
	m_bitmapOld->DeleteObject();
	delete m_bitmapOld;
	return TRUE;
}



BOOL DockManager::Create(DWORD dwStyle, const RECT& rect, CWin* pParentWnd, UINT nID) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pParent= pParentWnd;
	m_Aling=nID;
	LPCTSTR lpclassname=RegisterDefaultClass(NULL,WS_CHILD|WS_VISIBLE);
	return CWin::Create(lpclassname, _T(""), dwStyle, rect, pParentWnd->GetSafeHwnd(), nID);
}

int DockManager::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	// TODO: Add your specialized creation code here
	return 0;
}


BOOL DockManager::OnNcCalcSize(BOOL /*bCalcValidRects*/, LPNCCALCSIZE_PARAMS lpncsp)
{
	// adjust non-client area for border space
	//dependiendo de la alineacion se debe crear un pequeño borde
	switch(m_Aling)
	{
	case BS_ALIGN_LEFT:
		lpncsp->rgrc[0].right-=4;
		break;
	case BS_ALIGN_BOTTOM:
		lpncsp->rgrc[0].top+=4;
		break;
	case BS_ALIGN_RIGHT:
		lpncsp->rgrc[0].left+=1;
		break;
	}
	
	return TRUE;
}

CContainer* DockManager::PointIsInCaption(CPoint cp)
{
	int iNumW=GetNumVisibleWindows();
	
	for (int i = 0; i < iNumW; i++) //wich is the size real of the child windows
	{
		CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
		CRect rcW;
		pWin->GetWindowRect(rcW);
		if (pWin->IsWindowVisible())
		{
				rcW.bottom=rcW.top+18;
				if (rcW.PtInRect(cp))
					return (CContainer*)pWin;
		}
	}
	return NULL;

}

int DockManager::PointInDock(CPoint cp, CRect& rc, int& pos )
{
	int iNumW=GetNumVisibleWindows();
	
	for (int i = 0; i < iNumW; i++) //wich is the size real of the child windows
	{
		CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
		CRect rcW;
		pWin->GetWindowRect(rcW);
		if (pWin->IsWindowVisible())
		{
				//primero si es dock superior
			if (m_Aling== BS_ALIGN_LEFT || m_Aling== BS_ALIGN_RIGHT)
			{
				CRect rctop;
				rctop=rcW;
				rctop.top+=18;
                rctop.bottom=rctop.top+22;
				if (rctop.PtInRect(cp))
				{
					rc=rcW;
					pos=i;
					return 1;
				}
				//si es dock inferior
				rctop=rcW;
				rctop.top=rctop.bottom-22;
				if (rctop.PtInRect(cp))
				{
					rc=rcW;
					pos=i;
					return 2;
				}
			
			}
			else
			{
				CRect rctop;
				rctop=rcW;
				rctop.right=rctop.left+22;
				if (rctop.PtInRect(cp))
				{
					rc=rcW;
					pos=i;
					return 1;
				}
				//si es dock inferior
				rctop=rcW;
				rctop.left=rctop.right-22;
				if (rctop.PtInRect(cp))
				{
					rc=rcW;
					pos=i;
					return 2;
				}
			}

		}
	}
	return 0;

}
void DockManager::OnNcPaint(HRGN hRgn)
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
	dc.IntersectClipRect(rcWindow);
    dc.ExcludeClipRect(rcClient);//asi evitamos el parpadeo
	dc.BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),m_dc.m_hDC,0,0,SRCCOPY);
	m_dc.SelectObject(&m_OldBitmap);
	m_bitmap.DeleteObject();
	m_dc.DeleteDC();
	cb.DeleteObject ();
	dc.DeleteDC();
	
	
}

BOOL DockManager::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	if (m_DragSplitter)
	{
		ReleaseCapture();
		m_DragSplitter=FALSE;
		DrawSppliter(m_Splitter);
		if (m_Aling == BS_ALIGN_LEFT || m_Aling == BS_ALIGN_RIGHT)
		{

			if (abs(m_Splitter.left - m_ptStartPos.x)<= 2 ) return TRUE; 
		}
		else
		{
			if (abs(m_Splitter.top-m_ptStartPos.y)<=2)  return TRUE;
		}

		RecalLayout(TRUE);	
		return TRUE;
	}


	if (m_DragSplitterInside)
	{
	//	ScreenToClient(&point);
		DrawSppliterInside(	m_ptOldPos);
		ReleaseCapture();
		m_DragSplitterInside=FALSE;
		if (m_Aling == BS_ALIGN_LEFT || m_Aling == BS_ALIGN_RIGHT)
		{

			if (abs(point.y - m_ptStartPos.y)<= 2 ) return TRUE; 
		}
		else
		{
			if (abs(point.x-m_ptStartPos.x)<=2)  return TRUE;
		}
		ResizeWindow(point);
		//RecalLayout(TRUE);				
	}

	return TRUE;
}

void DockManager::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	Default();
}

void DockManager::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (BS_SPLIT_VERT ==nHitTest || nHitTest ==BS_SPLIT_HORTZ)
	{
		if (!m_DragSplitterInside)
		{
			m_DragSplitterInside=TRUE;
			SetCapture();
			SetFocus();
			m_ptStartPos=point;
			ScreenToClient(&point);
			m_ptOldPos=point;
			DrawSppliterInside(point);
		}
		return;
	}

	if (!m_DragSplitter)
	{
		m_DragSplitter=TRUE;
		m_ptStartPos=point;
		SetCapture();
		SetFocus();
		DrawSppliter(m_Splitter);
		return;
	}

	//Default();	
}


void DockManager::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	Default();
}

UINT DockManager::OnNcHitTest(CPoint cp)
{
	CRect rcWindow;
	GetWindowRect(rcWindow);
	if(m_Aling== BS_ALIGN_LEFT)
	{
		rcWindow.left=rcWindow.right-4;
		m_Splitter=rcWindow;
		if (rcWindow.PtInRect(cp))
			return BS_BORDER_RIGHT;
	}
	else if (m_Aling== BS_ALIGN_BOTTOM)
	{
		rcWindow.bottom=rcWindow.top+4;
		m_Splitter=rcWindow;
		if (rcWindow.PtInRect(cp))
			return BS_BORDER_TOP;
	}
	else if (m_Aling== BS_ALIGN_RIGHT)
	{
		rcWindow.right=rcWindow.left+4;
		m_Splitter=rcWindow;
		if (rcWindow.PtInRect(cp))
			return BS_BORDER_LEFT;
	}
	

	ScreenToClient(&cp);
	cp.y-=1;
	cp.x-=1;
	if(m_Aling== BS_ALIGN_LEFT || m_Aling== BS_ALIGN_RIGHT)
	{

		for( int i=0; i<m_NumSep; i++ )
		{
			
			if (m_Splits[i].PtInRect(cp))
			{
				m_Splitter=m_Splits[i];
				m_OldSplitter=m_Splitter;
				return BS_SPLIT_VERT;
			}
		}
	}

	if (m_Aling== BS_ALIGN_BOTTOM)
	{

		for( int i=0; i<m_NumSep; i++ )
		{
			if (m_Splits[i].PtInRect(cp))
			{
				m_Splitter=m_Splits[i];
				m_OldSplitter=m_Splitter;
				return BS_SPLIT_HORTZ;
			}
		}
	}
	
	return Default();
}

void DockManager::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Default();
}

int  DockManager::GetNumChild()
{
	return m_DockWindows.GetSize();
}

void DockManager::RecalLayout(BOOL bReSize)
{

	// first ajust the docking bars in the frame window
	if (GetNumChild()<=0) 
	{
		ShowWindow(SW_HIDE);
		return;
	}
	if (bReSize)
	{
		
		if(m_Aling== BS_ALIGN_LEFT)
		{
			
			CRect rc,rcw,rcc;
			GetWindowRect(rc);
			GetClientRect(rcc);
			theApp->m_WinMain->GetClientRect(rcw);
			ClientToScreen(rcw);
			::OffsetRect(rcw, -rc.left,-rc.top);
		
			rc.right=m_Splitter.right;
			m_size.cx=rc.Width();
			m_size.cy=rc.Height();
			theApp->m_WinMain->ScreenToClient(rc);
			//SetWindowPos(NULL,rc,SWP_HIDEWINDOW);
			theApp->m_WinMain->UpdateFrame(FALSE);
		}

		if(m_Aling== BS_ALIGN_RIGHT)
		{
			CRect rc,rcw,rcc;
			this->GetWindowRect(rc);
			GetClientRect(rcc);
			theApp->m_WinMain->GetClientRect(rcw);
			if (m_Splitter.left < 0)
				rc.left+=m_Splitter.left;
			else
				rc.left=m_Splitter.left;
			theApp->m_WinMain->ScreenToClient(rc);
			m_size.cx=rc.Width();
			m_size.cy=rc.Height();
			//SetWindowPos(NULL,rc,SWP_HIDEWINDOW );
			theApp->m_WinMain->UpdateFrame(FALSE);
		}
		if(m_Aling== BS_ALIGN_BOTTOM)
		{
			CRect rc,rcw,rcc;
			this->GetWindowRect(rc);
			GetClientRect(rcc);
			theApp->m_WinMain->GetClientRect(rcw);
			ClientToScreen(rcw);
			::OffsetRect(rcw, -rc.left,-rc.top);
			if (m_Splitter.top < 0)
				rc.top+=m_Splitter.top;
			else
				rc.top=m_Splitter.top;
			theApp->m_WinMain->ScreenToClient(rc);
			m_size.cx=rc.Width();
			m_size.cy=rc.Height();
			//SetWindowPos(NULL,rc,SWP_HIDEWINDOW );
			theApp->m_WinMain->UpdateFrame(FALSE);
		}
	}
	else // now the child windows in the new container windows size
	{
		CalSizeWindow();
	}
}

int  DockManager::GetNumVisibleWindows()
{
	int iNumW=m_DockWindows.GetSize();
	int count=0;
	for (int i = 0; i < iNumW; i++)
	{
		CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
		if (!((CContainer*)pWin)->IsClosePane()) count++;
		
	}
	return count;
}

CContainer*  DockManager::GetWichContainerIsTheParent(HWND hWnd)
{
	int iNumW=m_DockWindows.GetSize();
	int count=0;
	for (int i = 0; i < iNumW; i++)
	{
		CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
		if (((CContainer*)pWin)->GetSafeHwnd()== hWnd)
			return (CContainer*)pWin; 
		
	}
	return NULL;
}

void DockManager::EveryWindowsInsert()
{
		int iSizeW=0;
		int iSizeH=0;
		int iSizeWDock=0;
		int iSizeHDock=0;
		int iNumW=GetNumVisibleWindows();
		int FirstVisible=GetFirstVisible();
		int LastVisible=GetLastVisible();
		if (FirstVisible == -1) return;
		m_Splits.RemoveAll();
		m_NumSep=0;
		CRect rcSplit;
		if (IsWindowVisible() && iNumW > 0)
		{
			CRect rcClient;
			GetClientRect(rcClient); //area client of the docking bar
			iSizeW=rcClient.Width()/iNumW; //size actual
			iSizeH=rcClient.Height()/iNumW;
		
			if (m_Aling == BS_ALIGN_LEFT || m_Aling == BS_ALIGN_RIGHT)
			{
				if (rcClient.Width() < 4)
					rcClient.right=iSizeW;
			}else
			{
				if (rcClient.Height() < 4)
					rcClient.right=iSizeH;
			}
			CRect rcW=CRect(0,0,0,0);
			int  iContPos=0;
			HDWP hDWP = ::BeginDeferWindowPos(iNumW); 
			
			//Ok, we going to adjust all child window in the new docking bar size
			for (int i = FirstVisible; i <= LastVisible; i++)
			{
				CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
				CRect rcW=CRect(0,0,0,0);
				if (pWin->IsWindowVisible())
				{
					switch(m_Aling)
					{
					case BS_ALIGN_LEFT:
					case BS_ALIGN_RIGHT:
						pWin->GetWindowRect(rcW);
						ScreenToClient(rcW);
						if (m_Aling==BS_ALIGN_RIGHT)
							rcW.left=rcClient.left+2;
						else
							rcW.left=rcClient.left;
						rcW.right=rcClient.right;
						if (i==0) // si es la primera ventana hija donde esta la primera posicion del arriba
						{
							iContPos=rcClient.top;
							rcW.top=rcClient.top;
						}
						else
							rcW.top=iContPos; // si no, aqui se inicia la siguiente ventana.
						
						rcW.bottom=iSizeH;
						rcSplit=rcW;
						rcSplit.top=rcSplit.bottom;
						rcSplit.bottom=rcSplit.top+2;
						m_NumSep++;
						iContPos+=rcW.bottom+3;
						((CDockStruct*)m_DockWindows[i])->m_rectPost=rcW;
						DeferWindow(hDWP,pWin->GetSafeHwnd(),NULL,rcW,SWP_NOZORDER | SWP_NOACTIVATE||SWP_SHOWWINDOW);
						break;
					case BS_ALIGN_BOTTOM:
						pWin->GetWindowRect(rcW);
						ScreenToClient(rcW);
						rcW.top=rcClient.top;
						rcW.bottom=rcClient.bottom;
						if (i==0) 
						{
							iContPos=rcClient.left;
							rcW.left=rcClient.left;
						}
						else
							rcW.left=iContPos;
						
						rcW.right=iSizeW;
						rcSplit=rcW;
						rcSplit.left=rcSplit.right;
						rcSplit.right=rcSplit.left+2;
						m_Splits.InsertAt(m_NumSep,rcSplit);
						m_NumSep++;
						iContPos+=rcW.right+3;
						((CDockStruct*)m_DockWindows[i])->m_rectPost=rcW;
						DeferWindow(hDWP,pWin->GetSafeHwnd(),NULL,rcW,SWP_NOZORDER | SWP_NOACTIVATE||SWP_SHOWWINDOW);
						break;				
					}
					
				}
				
			}
			if (hDWP != NULL)
				::EndDeferWindowPos(hDWP);
		}

}

int DockManager::GetFirstVisible()
{

	int iNumW=m_DockWindows.GetSize();
	int count=0;
	for (int i = 0; i < iNumW; i++)
	{
		CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
		if (pWin->IsWindowVisible()) return i;
		
	}
	return -1;
}

int DockManager::GetLastVisible()
{

	int iNumW=m_DockWindows.GetSize();
	int count=0;
	for (int i = 0; i < iNumW; i++)
	{
		CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
		if (pWin->IsWindowVisible()) count= i;
		
	}
	return count;
}
void DockManager::CalSizeWindow()
{
		int iSizeW=0;
		int iSizeH=0;
		int iSizeWDock=0;
		int iSizeHDock=0;
		BOOL bGrow=FALSE;
		int  iDif=0;
		int iNumW=GetNumVisibleWindows();
		if (GetFirstVisible()== -1) return;
		m_Splits.RemoveAll();
		m_Splits.FreeExtra();
		m_NumSep=0;
		CRect rcSplit;
		int FirstVisible=GetFirstVisible();
		int LastVisible=GetLastVisible();
		if (IsWindowVisible() && iNumW > 0)
		{
			CRect rcClient;
			GetClientRect(rcClient); //area client of the docking bar
			iSizeW=rcClient.Width(); //size actual
			iSizeH=rcClient.Height();
			int iNumSeparador=0;
			for (int i =FirstVisible; i <= LastVisible; i++) //wich is the size real of the child windows
			{
				CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
				CRect rcW;
				pWin->GetWindowRect(rcW);
				if (pWin->IsWindowVisible())
				{
						iSizeWDock+=rcW.Width();
						iSizeHDock+=rcW.Height();
						iNumSeparador++;
				}
			}
			if (m_Aling == BS_ALIGN_LEFT || m_Aling == BS_ALIGN_RIGHT)
			{
				if (rcClient.Width() < 4)
					rcClient.right=iSizeWDock;
			}else
			{
				if (rcClient.Height() < 4)
					rcClient.right=iSizeHDock;
			}

			if (m_Aling == BS_ALIGN_LEFT || m_Aling == BS_ALIGN_RIGHT)
			{
				 
				 bGrow= ((iSizeH- ((iNumSeparador-1)*3)-1 )-iSizeHDock) < 0 ? FALSE: TRUE;
				 iDif= abs((iSizeH- ((iNumSeparador-1)*3)-1) -iSizeHDock);

			}
			else
			{
				 bGrow= ((iSizeW- ((iNumSeparador-1)*5)-1 )-iSizeWDock) < 0 ? FALSE: TRUE;
				 iDif= abs((iSizeW- ((iNumSeparador-1)*5)-1) -iSizeWDock);
				
			}

			CRect rcW=CRect(0,0,0,0);
			
			HDWP hDWP = ::BeginDeferWindowPos(GetNumVisibleWindows()); 
			
			//Ok, we going to adjust all child window in the new docking bar size
			if(iNumW ==1) // if it´s contains a only one window
			{
				rcW=rcClient;
				rcW.bottom-=1;
				iDif=0;
				((CDockStruct*)m_DockWindows[FirstVisible])->m_rectPost=rcW;
			}
			else
			{
				while(iDif > 0)
				{
					if (iDif <= 0)
						break;
					int  iContPos=0;
					int bFirst=TRUE;
					for (int i = FirstVisible; i <= LastVisible; i++)
					{
						CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
						CRect rcW=((CDockStruct*)m_DockWindows[i])->m_rectPost;
						if (pWin->IsWindowVisible())
						{
							switch(m_Aling)
							{
							case BS_ALIGN_LEFT:
							case BS_ALIGN_RIGHT:
								if (m_Aling==BS_ALIGN_RIGHT)
								{
									rcW.left=rcClient.left+2;
								}
								else
									rcW.left=rcClient.left;
								rcW.right=rcClient.right;
								if (i==0) // si es la primera ventana hija donde esta la primera posicion del arriba
								{
									iContPos=rcClient.top;
									rcW.top=rcClient.top;
								}
								else
								{
									if (iContPos >rcClient.top)
										rcW.top=iContPos; // si no, aqui se inicia la siguiente ventana.
									else
										rcW.top=rcClient.top;
								}
								if(iNumW ==1) // if it´s contains a only one window
								{
									if (bGrow)
										rcW.bottom+=iDif;
									else
										rcW.bottom-=iDif;
									iDif=0;
								}
								else
								{
									if (bGrow)
									{
										rcW.bottom+=1; 
										iDif--;
									}
									else
									{
										rcW.bottom-=1;
										iDif--;
									}
								}

								
								iContPos+=rcW.bottom+3;
								((CDockStruct*)m_DockWindows[i])->m_rectPost=rcW;
								
								break;
							case BS_ALIGN_BOTTOM:
								rcW.top=rcClient.top;
								rcW.bottom=rcClient.bottom;
								if (i==0) 
								{
									iContPos=rcClient.left;
									rcW.left=rcClient.left;
								}
								else
									rcW.left=iContPos;
								
								if(iNumW ==1) // if it´s contains a only one window
								{
									if (bGrow)
										rcW.right+=iDif;
									else
										rcW.right-=iDif;
									iDif=0;
								}
								else
								{
									if (bGrow)
									{
										rcW.right+=1; 
										iDif--;
									}
									else
									{
										rcW.right-=1;
										iDif--;
									}
								}
								
								iContPos+=rcW.right+5;
								((CDockStruct*)m_DockWindows[i])->m_rectPost=rcW;
								break;				
							}
							
						}
						
					}
					
				}
			}
			
			if(1)
				for (int i = FirstVisible; i <= LastVisible; i++)
				{
					CWin* pWin=((CDockStruct*)m_DockWindows[i])->m_WinDock;
					CRect rcW=((CDockStruct*)m_DockWindows[i])->m_rectPost;
					if (pWin->IsWindowVisible())
					{
						CRect rcWin;
						pWin->GetWindowRect(rcWin);
						if (m_Aling == BS_ALIGN_LEFT || m_Aling == BS_ALIGN_RIGHT)
						{
							if (m_Aling==BS_ALIGN_RIGHT)
								rcW.left=rcClient.left+2;
							else
								rcW.left=rcClient.left;
							rcW.right=rcClient.right;
							rcSplit=rcW;
							rcSplit.top+=rcWin.Height()-2;
							rcSplit.bottom=rcSplit.top+3;
							//if (i< LastVisible)
							m_Splits.InsertAt(m_NumSep,rcSplit);
							m_NumSep++;
						}
						else
						{
							rcW.top=rcClient.top;
							rcW.bottom=rcClient.bottom;
							rcSplit=rcW;
							rcSplit.left+=rcWin.Width()-1;
							rcSplit.right=rcSplit.left+5;
							m_Splits.InsertAt(m_NumSep,rcSplit);
							m_NumSep++;
						}

						((CDockStruct*)m_DockWindows[i])->m_rectPost=rcW;
						
						DeferWindow(hDWP,pWin->GetSafeHwnd(),NULL,rcW,SWP_NOZORDER | SWP_NOACTIVATE);

					}
				}
			if (hDWP != NULL)
				::EndDeferWindowPos(hDWP);
		}

}

void DockManager::ResizeWindow(CPoint point)
{
		ClientToScreen(&point);
		int iNumW=GetNumVisibleWindows();
		if (m_Aling == BS_ALIGN_LEFT || m_Aling == BS_ALIGN_RIGHT)
		{
			CRect rc;
			CRect rcClient;
			if (abs(m_ptStartPos.y - abs(point.y)) < 1 )
			{
				SetCursorPos(m_ptStartPos.x,m_ptStartPos.y );
				return;
			}
			if (m_ptStartPos.y > point.y) //la ventana inferior se amplia, la superior o anterior se reduce
			{
				int nDif=0;
				((CDockStruct*)m_DockWindows[m_SplitMove])->m_WinDock->GetWindowRect(rc);  
				rcClient=((CDockStruct*)m_DockWindows[m_SplitMove])->m_rectPost;
				if (abs(rc.top - point.y) <= 22)
				{
					nDif=rc.Height()-23;
					rc.bottom=rc.top+23;
				}
				else
				{
					nDif=rc.bottom-point.y;
					rc.bottom=point.y;
					
				}
				rcClient.bottom-=nDif;
				((CDockStruct*)m_DockWindows[m_SplitMove])->m_rectPost=rcClient;
				int NextPos=rcClient.bottom+3;
				((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_WinDock->GetWindowRect(rc);  
				rcClient=((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_rectPost;
				rcClient.top=NextPos;
				rcClient.bottom=rc.Height()+nDif;
				((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_rectPost=rcClient;
			}
			else
			{
				((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_WinDock->GetWindowRect(rc);  
				rcClient=((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_rectPost;
				rcClient.bottom=rc.Height();
				int nDif=0;
				if ( point.y >= rc.bottom-22)
				{
					nDif=rc.Height()-23;
					rc.top=rc.bottom-23;
				}
				else
				{
					nDif=point.y-rc.top;
					rc.top=point.y;
				}

				rcClient.top+=nDif;
				rcClient.bottom-=nDif;
				((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_rectPost=rcClient;
				
				int NextPos=rcClient.top-3;
				
				((CDockStruct*)m_DockWindows[m_SplitMove])->m_WinDock->GetWindowRect(rc);  
				rcClient=((CDockStruct*)m_DockWindows[m_SplitMove])->m_rectPost;
				rcClient.bottom+=nDif;
				((CDockStruct*)m_DockWindows[m_SplitMove])->m_rectPost=rcClient;
			}
		
			
		}
		else //the bottom window
		{
			CRect rc;
			CRect rcClient;
			if (abs(m_ptStartPos.y - abs(point.y)) < 1 )
			{
				SetCursorPos(m_ptStartPos.x,m_ptStartPos.y );
				return;
			}
			if (m_ptStartPos.y > point.y) //la ventana inferior se amplia, la superior o anterior se reduce
			{
				int nDif=0;
				((CDockStruct*)m_DockWindows[m_SplitMove])->m_WinDock->GetWindowRect(rc);  
				rcClient=((CDockStruct*)m_DockWindows[m_SplitMove])->m_rectPost;
				if (abs(rc.right - point.x) <= 22)
				{
					nDif=rc.Width()-23;
					rc.right=rc.left+23;
				}
				else
				{
					nDif=rc.right-point.x;
					rc.right=point.x;
					
				}
				rcClient.right-=nDif;
				((CDockStruct*)m_DockWindows[m_SplitMove])->m_rectPost=rcClient;
				int NextPos=rcClient.right+3;
				((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_WinDock->GetWindowRect(rc);  
				rcClient=((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_rectPost;
				rcClient.left=NextPos;
				rcClient.right=rc.Width()+nDif;
				((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_rectPost=rcClient;
			}
			else
			{
				((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_WinDock->GetWindowRect(rc);  
				rcClient=((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_rectPost;
				rcClient.right=rc.Width();
				int nDif=0;
				if ( point.x >= rc.right-22)
				{
					nDif=rc.Width()-23;
					rc.left=rc.right-23;
				}
				else
				{
					nDif=point.x-rc.left;
					rc.left=point.x;
				}

				rcClient.left+=nDif;
				rcClient.right-=nDif;
				((CDockStruct*)m_DockWindows[m_SplitMove+1])->m_rectPost=rcClient;
				
				int NextPos=rcClient.left-3;
				
				((CDockStruct*)m_DockWindows[m_SplitMove])->m_WinDock->GetWindowRect(rc);  
				rcClient=((CDockStruct*)m_DockWindows[m_SplitMove])->m_rectPost;
				rcClient.right+=nDif;
				((CDockStruct*)m_DockWindows[m_SplitMove])->m_rectPost=rcClient;
			}
		
		}

		CalSizeWindow();
		CalSizeWindow();

}


CSize DockManager::Getsize()
{
	return m_size;
}

int DockManager::FindItem(HWND hWnd)
{
	for (int iCont=0; iCont< m_NumWins;iCont++)
	{
		CDockStruct* ct=(CDockStruct*) m_DockWindows[iCont];
		if (ct->m_WinDock->GetSafeHwnd() == hWnd)
		    return iCont;
	}
	return -1;

}

CWin*  DockManager::GetNumWnd(int m_numWin) 
{
        if (m_numWin > m_NumWins)
			return NULL;
		else
		{
			if (m_DockWindows.GetSize() < 1) return NULL;
			CWin* pw=((CDockStruct*) m_DockWindows [m_numWin])->m_WinDock;
			if (HIWORD(pw)== NULL) return NULL;
			else
			  return ((CDockStruct*) m_DockWindows [m_numWin])->m_WinDock;
		}
}



void DockManager::AddWindow(CWin* pParent,int nPos)
{
	if (!HIWORD(pParent))return;
	if (nPos == -1)
		m_DockWindows.SetAtGrow(m_NumWins,new CDockStruct(pParent));
	else{
		m_DockWindows.InsertAt(nPos,new CDockStruct(pParent));

	}
	pParent->ShowWindow(SW_SHOW);
	((CContainer*)pParent)->m_DOCKFLOAT=((CContainer*)pParent)->m_DOCKSITE=
	GetWindowLong(GetSafeHwnd(),GWL_ID);
	m_NumWins++;
	EveryWindowsInsert();
	RecalLayout(FALSE);
}

UINT DockManager::AddWindow(CDockPanelBase* pParent,UINT dlgCtrl,int nPos)
{

	if (dlgCtrl==NULL)
	{	
		CContainer* ctn= new CContainer;
		if (!ctn->Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,pParent->GetDlgCtrlID()+1))
			return NULL;

		ctn->Addtab(pParent);
		pParent->SetParent(ctn);


		ctn->m_DOCKFLOAT=!BS_FLOATING;
		ctn->m_DOCKSITE=GetWindowLong(GetSafeHwnd(),GWL_ID);
		pParent->uAling=GetWindowLong(GetSafeHwnd(),GWL_ID);
		pParent->iLasPosition=m_NumWins;
		pParent->bIsPartOfTabbed=FALSE;
		pParent->bIsShow=TRUE;
		pParent->m_IdCtrlParent=NULL;	

		if (!HIWORD(pParent))return NULL;
		if (nPos == -1)
		{
			m_DockWindows.SetAtGrow(m_NumWins,new CDockStruct(ctn));
			m_NumWins++;
		}
		else{
			m_DockWindows.InsertAt(nPos,new CDockStruct(ctn));
		
		}
	}else
	{
		for( int i=0; i<m_DockWindows.GetSize(); i++ )
		{
			CDockStruct *pTab = (CDockStruct*)m_DockWindows.GetAt(i);
			CTab*  ctab= ((CContainer*)pTab->m_WinDock)->GetTab(0);
			if ( (UINT)ctab->pParent->GetDlgCtrlID() == dlgCtrl )
			{
				CContainer* pct=(CContainer*)pTab->m_WinDock;
				pParent->SetParent(pct);
				pParent->uAling=NULL;
				pParent->iLasPosition=m_NumWins;
				pParent->bIsPartOfTabbed=TRUE;
				pParent->bIsShow=TRUE;
				pParent->m_IdCtrlParent=dlgCtrl;	
				pct->Addtab(pParent);
				break;
			}
		}
		
	}

	pParent->ShowWindow(SW_SHOW);
	//((CContainer*)pParent)->m_DOCKFLOAT=((CContainer*)pParent)->m_DOCKSITE=
	//GetWindowLong(GetSafeHwnd(),GWL_ID);

	EveryWindowsInsert();
	RecalLayout(FALSE);
	return pParent->GetDlgCtrlID()+1;
}



void DockManager::DeleteWindow(int m_NumW)
{
	if (m_NumW < 0) return;
	if (m_NumW < m_NumWins)
	{
		CDockStruct* ctn=(CDockStruct*) m_DockWindows[m_NumW]; 	
		if (ctn)
			delete ctn;
		m_NumWins--;
		m_DockWindows.RemoveAt(m_NumW,1);
		EveryWindowsInsert();
	}
	
}

BOOL DockManager::OnSize(UINT nType, int cx, int cy) 
{
	//if (m_NumWins > 0)
	RecalLayout(FALSE);
	Invalidate();
	UpdateWindow();
	return TRUE;
}





void DockManager::OnMouseMove(UINT nHitTest, CPoint point)
{
	CPoint cp;
	GetCursorPos(&cp);
	if (GetCapture() != GetSafeHwnd())
		{
			m_DragSplitter=FALSE;
		}
	if (m_DragSplitter)
	{
		DrawSppliter(m_Splitter);
		//nuevos tamaños de la ventana
		if (IsVertical())
		{
			//ClientToScreen(&cp);
	
			m_Splitter.left=cp.x;
			m_Splitter.right=m_Splitter.left+4;

		}
		else
		{
	
			m_Splitter.top=cp.y;
			m_Splitter.bottom=m_Splitter.top+4;
		}
		DrawSppliter(m_Splitter);
		return;
	}
	ScreenToClient(&cp);
	if (m_DragSplitterInside)
	{
		
		DrawSppliterInside(m_ptOldPos);
		if (IsVertical())
		{
			//ClientToScreen(&cp);
	
			m_Splitter.left=cp.x;
			m_Splitter.right=m_Splitter.left+4;

		}
		else
		{
	
			m_Splitter.top=cp.y;
			m_Splitter.bottom=m_Splitter.top+4;
		}
		DrawSppliterInside(cp);
		m_ptOldPos=point;
		
		
	}
		
	//Default();
}

BOOL DockManager::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	
	Default();
	return TRUE;

}

BOOL DockManager::OnRButtonDown(UINT nFlags, CPoint point)
{
	Default();

	return TRUE;

}


int DockManager::OnDestroy()
{
	// Libera la memoria
    for( int i=0; i<m_NumWins; i++ )
    {
    CDockStruct *pTab = (CDockStruct*)m_DockWindows.GetAt(i);
    if( pTab )
        delete pTab;
    }
	return TRUE;

	// TODO: Add your message handler code here
}



void DockManager::DrawSppliter(CRect rc)
{

	CRect rcWindow;
	theApp->m_WinMain->GetWindowRect(rcWindow);
	CGDI pDC(theApp->m_WinMain->GetDCEx(NULL,DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE));
	CBrush* pBrush = CGDI::HalftGray();
    CBrush pBrushOld(pDC.SelectObject(pBrush));
	::OffsetRect(rc, -rcWindow.left,-rcWindow.top);
	//theApp->m_WinMain->GetClientRect(rcWindow);
	CRect rc1;
	GetClientRect (rc1);
	//::OffsetRect(rcWindow, -rcWindow.left,-rcWindow.top);
	
	//rc.OffsetRect(-rcWindow.TopLeft());
	if (IsVertical())
		pDC.PatBlt(rc.left, rc.top, rc.Width(), rc1.Height(), PATINVERT);
	else
		pDC.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATINVERT);
    pDC.SelectObject(&pBrushOld);
    theApp->m_WinMain->ReleaseDC(pDC.m_hDC);
	pBrush->DeleteObject();
	pBrushOld.DeleteObject();
	delete pBrush;

}

void DockManager::DrawSppliterInside(CPoint cp)
{
	CRect rc;
	GetClientRect(rc);
	CGDI pDC(this->GetDCEx(NULL,DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE));
	CBrush* pBrush = CGDI::HalftGray();
    CBrush pBrushOld(pDC.SelectObject(pBrush));

	if (IsVertical())
	{
		rc.top=cp.y;
		rc.bottom=cp.y+3;
		pDC.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATINVERT);
	}
	else
	{
		rc.left=cp.x;
		rc.right=cp.x+5;
		pDC.PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATINVERT);
	}
    pDC.SelectObject(&pBrushOld);
	theApp->m_WinMain->ReleaseDC(pDC.m_hDC);
	pBrush->DeleteObject();
	pBrushOld.DeleteObject();
	delete pBrush;

}

BOOL DockManager::OnSetCursor(HWND hWnd, UINT nHitTest, UINT message)
{
	CPoint cp;
	GetCursorPos(&cp);
	CRect rcWindow;
	GetWindowRect(rcWindow);
	m_SplitMove=0;
	if(m_Aling== BS_ALIGN_LEFT)
	{
		rcWindow.left=rcWindow.right-2;
		if (rcWindow.PtInRect(cp))
		{
            SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZEWE)));
			return TRUE;
		}
		
	}
	else if (m_Aling== BS_ALIGN_BOTTOM)
	{
		rcWindow.bottom=rcWindow.top+2;
		if (rcWindow.PtInRect(cp))
		{
			SetCursor(LoadCursor (NULL,MAKEINTRESOURCE(IDC_SIZENS)));
			return TRUE;
		}

		
	}
	else if (m_Aling== BS_ALIGN_RIGHT)
	{

		rcWindow.right=rcWindow.left+2;
		if (rcWindow.PtInRect(cp))
		{
			SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_SIZEWE)));
			return TRUE;
		}

		
	}
	ScreenToClient(&cp);
	cp.y-=1;
	cp.x-=1;
	if(m_Aling== BS_ALIGN_LEFT || m_Aling== BS_ALIGN_RIGHT)
	{

		for( int i=0; i<m_NumSep; i++ )
		{
			
			if (m_Splits[i].PtInRect(cp))
			{
				m_SplitMove=i;
				SetCursor(LoadCursor (NULL,MAKEINTRESOURCE(IDC_SIZENS)));
				return TRUE;
			}
		}
	}

	if (m_Aling== BS_ALIGN_BOTTOM)
	{

		for( int i=0; i<m_NumSep; i++ )
		{
			if (m_Splits[i].PtInRect(cp))
			{
				m_SplitMove=i;
				SetCursor(LoadCursor (NULL,MAKEINTRESOURCE(IDC_SIZEWE)));
				return TRUE;
			}
		}
	}
	
	SetCursor(LoadCursor (NULL,MAKEINTRESOURCE(IDC_ARROW)));	
	return TRUE;
	
}
