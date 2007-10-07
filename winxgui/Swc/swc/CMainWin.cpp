/*
 * <F> CWin.cpp		1.0  23/09/2007
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/


#include "stdafx.h"

BOOL CWin::OnDestroy()
{
	if (lpfnOldWndProc !=NULL )
		UnSubClassWnd();
	
	if(GetSafeHwnd() == theApp->GetMainWindows()->GetSafeHwnd())
	{
		
	 	PostQuitMessage(0);
		return TRUE;
	}

	return TRUE;
}

void CFrame::CreateDock()
	{
		m_DockLeft = new DockManager;
		if (!m_DockLeft->Create(WS_VISIBLE|WS_CHILD,CRect(0,0,100,100),this,BS_ALIGN_LEFT))
			return ;

		m_DockBottom = new DockManager;
		if (!m_DockBottom->Create(WS_VISIBLE|WS_CHILD,CRect(0,0,100,100),this,BS_ALIGN_BOTTOM))
			return ;

		m_DockRight = new DockManager;
		if (!m_DockRight->Create(WS_VISIBLE|WS_CHILD,CRect(0,0,100,100),this,BS_ALIGN_RIGHT))
			return ;

	}

void CFrame::ShowFloatWindow(HWND hWnd)
{
	//CWin cw(hWnd);
	//cw.ShowWindow(TRUE);
	CContainer *cc=m_DockLeft->GetWichContainerIsTheParent(hWnd);
	if (cc != NULL)
		cc->ShowPane(TRUE);
	else if ((cc=m_DockBottom->GetWichContainerIsTheParent(hWnd))!= NULL) 
		cc->ShowPane(TRUE);
	else if ((cc=m_DockRight->GetWichContainerIsTheParent(hWnd))!= NULL) 
		cc->ShowPane(TRUE);

	UpdateFrame(TRUE);
}
void CFrame::UpdateFrame(BOOL bResizeBars)
{

	CRect rc;
	GetClientRect(rc);
	HDWP hDWP = ::BeginDeferWindowPos(3); 
			
	if (HIWORD(m_ReBar))
		if(m_ReBar->GetSafeHwnd() != NULL &&  m_ReBar->IsWindowVisible())
		{
			if (bResizeBars)
				::SendMessage(m_ReBar->GetSafeHwnd(), WM_SIZE, 0, 0);

			RECT rectTB;
			::GetWindowRect(m_ReBar->GetSafeHwnd(), &rectTB);
			rc.top += rectTB.bottom - rectTB.top;
			rc.top++;
		}
	
		if(m_statusCtrl.GetSafeHwnd() != NULL && m_statusCtrl.IsWindowVisible() )
		{
			if(bResizeBars)
			{
				m_statusCtrl.Size();
				m_statusCtrl.Invalidate();
				m_statusCtrl.UpdateWindow();
			}
			RECT rectSB;
			::GetWindowRect(m_statusCtrl.GetSafeHwnd(), &rectSB);
			rc.bottom -= (rectSB.bottom - rectSB.top)+2;
		}
	
	
	if (HIWORD(m_DockBottom))
	{
		CRect rcw;
		if (m_DockBottom->GetNumChild()> 0)
		{
			int iii=m_DockBottom->GetNumVisibleWindows();
			if (iii<=0)
			 DeferWindow(hDWP,m_DockBottom->GetSafeHwnd(),NULL,rc.left,rc.top,rc.left+3,rc.bottom,SWP_NOZORDER | SWP_NOACTIVATE|SWP_HIDEWINDOW);
			else
			{
				m_DockBottom->GetWindowRect(rcw);
				CSize cz=m_DockBottom->Getsize();
				if (cz.cy == 0)
					cz.cy=120;
				DeferWindow(hDWP,m_DockBottom->GetSafeHwnd(),NULL,rc.left,rc.bottom-((cz.cy<=0)?rcw.Height():cz.cy),rc.Width(),((cz.cy<=0)?rcw.Height():cz.cy),SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);
				rc.bottom-=((cz.cy<=0)?rcw.Height():cz.cy);
				m_DockBottom->RecalLayout();
			}
		}
		else
		{
			DeferWindow(hDWP,m_DockBottom->GetSafeHwnd(),NULL,rc.left,rc.bottom-3,rc.Width(),rc.bottom,SWP_NOZORDER | SWP_NOACTIVATE|SWP_HIDEWINDOW);
		}

	}

	if (HIWORD(m_DockRight))
	{
		CRect rcw;
		if (m_DockRight->GetNumChild()> 0)
		{
			int iii=m_DockRight->GetNumVisibleWindows();
			if (iii<=0)
			 DeferWindow(hDWP,m_DockRight->GetSafeHwnd(),NULL,rc.left,rc.top,rc.left+3,rc.bottom,SWP_NOZORDER | SWP_NOACTIVATE|SWP_HIDEWINDOW);
			else
			{
				m_DockRight->GetWindowRect(rcw);
				CSize cz=m_DockRight->Getsize();
				if (cz.cx == 0)
					cz.cx=120;
				DeferWindow(hDWP,m_DockRight->GetSafeHwnd(),NULL,rc.right-((cz.cx<=0)?rcw.Width()-4:cz.cx-4),rc.top+2,((cz.cx<=0)?rcw.Width()-4:cz.cx-4),rc.Height(),SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);
				rc.right-=((cz.cx<=0)?rcw.Width()-2:cz.cx-2);
				m_DockRight->RecalLayout();
			}
		}
		else
			DeferWindow(hDWP,m_DockRight->GetSafeHwnd(),NULL,rc.right-3,rc.top,rc.right,rc.bottom,SWP_NOZORDER | SWP_NOACTIVATE|SWP_HIDEWINDOW);
		
	}
	if (HIWORD(m_DockLeft))
	{
		CRect rcw;
		if (m_DockLeft->GetNumChild()>0)
		{
			int iii=m_DockLeft->GetNumVisibleWindows();
			if (iii<=0)
			 DeferWindow(hDWP,m_DockLeft->GetSafeHwnd(),NULL,rc.left,rc.top,rc.left+3,rc.bottom,SWP_NOZORDER | SWP_NOACTIVATE|SWP_HIDEWINDOW);
			else
			{
				m_DockLeft->GetWindowRect(rcw);
				ScreenToClient(rcw);
				CSize cz=m_DockLeft->Getsize();
				if (cz.cx == 0)
					cz.cx=120;
				DeferWindow(hDWP,m_DockLeft->GetSafeHwnd(),NULL,rc.left,rc.top+1,((cz.cx<=0)?rcw.Width():cz.cx),rc.Height(),SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);
				
				rc.left+=((cz.cx<=0)?rcw.Width():cz.cx);
				m_DockLeft->RecalLayout();
			}
		}
		else
			DeferWindow(hDWP,m_DockLeft->GetSafeHwnd(),NULL,rc.left,rc.top,rc.left+3,rc.bottom,SWP_NOZORDER | SWP_NOACTIVATE|SWP_HIDEWINDOW);
	}
	if (hMDIClient!=NULL || HIWORD(m_ClientView) )
	{
		DeferWindow(hDWP,hMDIClient==NULL?m_ClientView->GetSafeHwnd():hMDIClient,NULL,rc.left,rc.top+2,rc.Width(),rc.Height()-1,SWP_NOZORDER | SWP_NOACTIVATE);
	}

	if (hDWP != NULL)
		::EndDeferWindowPos(hDWP);

}

BOOL CFrame::LoadFrame(UINT nID,DWORD dwStyle,HWND hParentWnd)
{	
	TCHAR szTemp[256];
	int nLen;
	LPCTSTR lpszName = MAKEINTRESOURCE((nID>>4)+1);
	if (::FindResource(GetModuleHandle(NULL), lpszName, RT_STRING) != NULL &&
		(nLen = ::LoadString(GetModuleHandle(NULL), nID, szTemp, 255) != 0)) {
	}

	BOOL bRes= Create(_T("MotsusMainWindow"),szTemp,dwStyle,CRect(0,0,200,200),hParentWnd,nID);
	uiTimerId = GfxSetSafeTimer(this, 100);
	return bRes;	
}


void CFrame::LoadPositionBar()
{
	//la idea es organizar toda las ventanas una vez se han cargado todas las ventanas
	//incluyendo el frame principal.
	//la idea es recorer cada una de las ventanas y ver cuales son ventanas principales
	// verificar cuales son flotantes de las principales y ponerlas a flotar.
	//luego recorer todas las ventanas e identificar cuales son hijas de un tab y retirarlas
	// de cada uno de los Cwindock y ubicarlas en cada uno de los tab.
	// Si las ventanas flotantes retirarlas creado un nuevo Container y ponderlas a flotar.
	// si no hay informacion de posicion de la ventana debe permanecer en la posicion de Cwindock.
	// si las ventanas son ocultas se deben esconder, pero manteniendo la position.
	
	//primero los criticos son las  ventanas flotantes y los tabs.
	//DockLeft
	if (m_DockLeft->GetNumChild() > 0)
	{
		for (int i=0; i < m_DockLeft->GetNumChild(); i++)
		{
			CDockPanelBase* pWin= (CDockPanelBase*)m_DockLeft->GetNumWnd(i) ;
			if (pWin->uAling == BS_FLOATING)
			{
				//pongamos a volar la ventana

			}

		}
	}
	int iDockWin=0;
	for (; iDockWin < 3; iDockWin++)
	{

		//las ventanas criticas son las flotantes y las principales.




	}// fin del bucle DockWin

	
}

void CFrame::FloatWindow(CWin* pParent, CPoint point, CRect rcw )
	{
		if (!HIWORD(pParent)) return;
		m_MiniFrame= new CMiniDock;
		if (!m_MiniFrame->Create(this,0x1004,
			CRect(point.x-4,point.y-4,point.x+200,point.y+200),pParent))
			return;
		
		m_MiniFrame->PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x+200, point.y+4));
		
	}

int  CFrame::OnPaint(HDC hDC)
{
	//DrawNcMenuBar(hDC);
	//Default();	
	return 0;
}


//-----------------------------------------------------------------------------------------------------------
// CMiniFrame
//
//-----------------------------------------------------------------------------------------------------------

BOOL CMiniFrame::Create(CWin* pParentWnd, UINT nID, CRect& rc, CWin* pControls, DWORD dwStyle)
	{

		pParent=pParentWnd;
		m_ClientView=pControls;
		if (!m_ClientView) 
		{
			delete this;
			return false;
		}
	
		LPCTSTR lpclassname=RegisterDefaultClass();
		dwStyle|=WS_THICKFRAME;
		BOOL rb;
		CPoint pt (rc.left, rc.bottom);
		rb=CWin::Create(lpclassname,NULL,dwStyle,rc, pParentWnd->GetSafeHwnd(), nID);
		m_ClientView->SetWindowPos (NULL, 0, 0, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW);
		m_ClientView->SetParent (this);
		m_ClientView->ShowWindow(SW_SHOW);
		ShowWindow (SW_HIDE);
		return rb;
	}

BOOL CMiniFrame::OnDestroy()
{
	
	return TRUE;
}

//----------------------------------------------------------------
// MIniDock Windows
//----------------------------------------------------------------

void CMiniDock::OnLButtonUp(UINT nHitTest, CPoint pt)
 {
	ReleaseCapture();
	//if (bDrawTab)
	//	DrawFrame(m_OldrcTab);
	
	if (bDrawNormalDock)
		DrawFrame(m_OldrcDock);
	
	if (bDrawNormal)
		DrawFrame(m_Oldrc);
	
	m_Drag=FALSE;
	m_Oldrc.DeflateRect(1,1);
	CRect mWin;
	GetWindowRect(mWin);
	if (bDrawTab || bDrawNormalDock )
	{
			CPoint point;
			CRect rcL;
			CRect rcB;
			CRect rcR;
			GetCursorPos(&point);
			theApp->m_WinMain->m_DockLeft->GetWindowRect(rcL);
			theApp->m_WinMain->m_DockBottom->GetWindowRect(rcB);
			theApp->m_WinMain->m_DockRight->GetWindowRect(rcR);

			if (rcL.PtInRect(point))
			{
				CContainer* m_ct=theApp->m_WinMain->m_DockLeft->PointIsInCaption(point);
				if (m_ct != NULL)
				{
					int iT= ((CContainer*)m_ClientView)->GetCount(); //how many tabs we have?
					for (int i=0; i < iT; i++)
					{
						CTab* ct=((CContainer*)m_ClientView)->GetTab(i);
						ct->pParent->SetParent (m_ct);
						m_ct->Addtab(ct->pParent,ct->lpMsg,ct->nMenu);
					}

				}
				else
				{
					int iNum=theApp->m_WinMain->m_DockLeft->GetNumVisibleWindows();
					CRect rcW;
					int pos;
					int iDock=theApp->m_WinMain->m_DockLeft->PointInDock(point, rcW, pos);
					if (iDock == 0)
					{
						int iNum=theApp->m_WinMain->m_DockLeft->GetNumVisibleWindows();
						if (rcL.PtInRect(point))
							{
								iDock=1;
								pos =0;
							}
						
					}
					m_ClientView->SetParent (theApp->m_WinMain->m_DockLeft);
					if ( iDock==1)
						theApp->m_WinMain->m_DockLeft->AddWindow(m_ClientView,pos);
					else if( iDock==2)
					{
							if (iNum == pos)
								theApp->m_WinMain->m_DockLeft->AddWindow(m_ClientView);
							else
								theApp->m_WinMain->m_DockLeft->AddWindow(m_ClientView,pos+1);
					}
					
					
				}
				SendMessage(WM_CLOSE,0,0);
				theApp->m_WinMain->UpdateFrame();
			}
			else if (rcR.PtInRect(point))
			{
				CContainer* m_ct=theApp->m_WinMain->m_DockRight->PointIsInCaption(point);
				if (m_ct != NULL)
				{
					int iT= ((CContainer*)m_ClientView)->GetCount(); //how many tabs we have?
					for (int i=0; i < iT; i++)
					{
						CTab* ct=((CContainer*)m_ClientView)->GetTab(i);
						ct->pParent->SetParent (m_ct);
						m_ct->Addtab(ct->pParent,ct->lpMsg,ct->nMenu);
					}


				}
				else
				{
					int iNum=theApp->m_WinMain->m_DockRight->GetNumVisibleWindows();
					CRect rcW;
					int pos;
					int iDock=theApp->m_WinMain->m_DockRight->PointInDock(point, rcW, pos);
					if (iDock == 0)
					{
						int iNum=theApp->m_WinMain->m_DockRight->GetNumVisibleWindows();
						if (rcR.PtInRect(point))
							{
								iDock=1;
								pos =0;
							}
						
					}
					m_ClientView->SetParent (theApp->m_WinMain->m_DockRight);
					if ( iDock==1)
						theApp->m_WinMain->m_DockRight->AddWindow(m_ClientView,pos);
					else if( iDock==2)
					{
							if (iNum == pos)
								theApp->m_WinMain->m_DockRight->AddWindow(m_ClientView);
							else
								theApp->m_WinMain->m_DockRight->AddWindow(m_ClientView,pos+1);
					}
					
					
				}

				SendMessage(WM_CLOSE,0,0);
				theApp->m_WinMain->UpdateFrame();
			}

			else if (rcB.PtInRect(point))
			{
				CContainer* m_ct=theApp->m_WinMain->m_DockBottom->PointIsInCaption(point);
				if (m_ct != NULL)
				{
					int iT= ((CContainer*)m_ClientView)->GetCount(); //how many tabs we have?
					for (int i=0; i < iT; i++)
					{
						CTab* ct=((CContainer*)m_ClientView)->GetTab(i);
						ct->pParent->SetParent (m_ct);
						m_ct->Addtab(ct->pParent,ct->lpMsg,ct->nMenu);
					}


				}
				else
				{

					int iNum=theApp->m_WinMain->m_DockBottom->GetNumVisibleWindows();
					CRect rcW;
					int pos;
					int iDock=theApp->m_WinMain->m_DockBottom->PointInDock(point, rcW, pos);
					
					m_ClientView->SetParent (theApp->m_WinMain->m_DockBottom);
					if (iDock == 0)
					{
						int iNum=theApp->m_WinMain->m_DockBottom->GetNumVisibleWindows();
						if (rcB.PtInRect(point))
							{
								iDock=1;
								pos =0;
							}
						
					}
					if ( iDock==1)
						theApp->m_WinMain->m_DockBottom->AddWindow(m_ClientView,pos);
					else if( iDock==2)
					{
							if (iNum == pos)
								theApp->m_WinMain->m_DockBottom->AddWindow(m_ClientView);
							else
								theApp->m_WinMain->m_DockBottom->AddWindow(m_ClientView,pos+1);
					}
				
				}
				SendMessage(WM_CLOSE,0,0);
				theApp->m_WinMain->UpdateFrame();
			}
			bDrawTab=FALSE;
			bDrawNormalDock=FALSE;
			bDrawNormal=FALSE;
	}else
	{
		bDrawNormal=TRUE;
		SetWindowPos(0,m_Oldrc, SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER|SWP_DRAWFRAME|SWP_NOSENDCHANGING|SWP_SHOWWINDOW);
	}
	
	Default();
 }

void CMiniDock::DrawNormal()
{
		CPoint pt;
		GetCursorPos(&pt);
		if ((m_oldPost.x != pt.x) || 
					(m_oldPost.y != pt.y))
				{
									
 				   int widht=mWin.Width();
					int Height=mWin.Height();
					if (m_oldPost.x < pt.x)
						mWin.left+=abs(m_oldPost.x - pt.x);
					else
						mWin.left-=abs(m_oldPost.x - pt.x);

					if (m_oldPost.y < pt.y)
						mWin.top+=abs(m_oldPost.y - pt.y);
					else
						mWin.top-=abs(m_oldPost.y - pt.y);
					mWin.right=mWin.left+widht;
					mWin.bottom=mWin.top+Height;
					SetWindowPos(0,mWin, SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER|SWP_DRAWFRAME|SWP_NOSENDCHANGING|SWP_SHOWWINDOW);
					m_Oldrc=mWin;
					m_oldPost=pt;
						
					
				}

}

void CMiniDock::DrawDock(CRect rc,CPoint point,DockManager* mDock, UINT uALing  )
{
	BOOL bHorz = (uALing == BS_ALIGN_BOTTOM);
	CContainer* m_ct=mDock->PointIsInCaption(point);
	if (m_ct != NULL)
	{
		// Si el ultimo draw era flotante normal debemos eliminarlo
		if (bDrawNormal)
		{
			bDrawNormal=FALSE;
		}
		if (bDrawNormalDock)
		{
			DrawFrame(m_OldrcDock);
			bDrawNormalDock=FALSE;
		}
		if (!bDrawTab)
		{
			bDrawTab=TRUE;
			bDrawNormalDock=FALSE;
			bDrawNormal=FALSE;
			m_ct->GetWindowRect(m_OldrcTab);
		}
		
	

	}
	else // is possible dock
	{
		CRect rcW;
		int pos;
		int iDock=mDock->PointInDock(point, rcW, pos);
		if (iDock == 0)
		{
			int iNum=mDock->GetNumVisibleWindows();
			if (iNum == 0)
			{
				if (rc.PtInRect(point))
					{
						rcW=rc;
						iDock=1;
						pos =0;
					}
			}
			
		}
		if (iDock != 0)
		{
			if (bDrawNormal)
			{
				bDrawNormal=FALSE;
			}
			
			if (bDrawTab)
			{
				bDrawTab=FALSE;
			}
			if (!bDrawNormalDock)
			{
				int iNum=mDock->GetNumVisibleWindows();
				m_OldrcDock=rcW;
				if (!bHorz)
				{
					if (iNum <  1)
					{
						if (uALing == BS_ALIGN_RIGHT)
						{
							m_OldrcDock.left-= m_Oldrc.Width();
							m_OldrcDock.right= m_OldrcDock.left+m_Oldrc.Width();
						}
						else
							m_OldrcDock.left+= m_Oldrc.Width();
					}
					else
					{
						if (iDock ==1)
							m_OldrcDock.bottom=rcW.top+ (rcW.Height()/2);
						else
							m_OldrcDock.top=rcW.bottom- (rcW.Height()/2);
					}
					
				}
				else
				{
					if (iNum <  1)
					{
						m_OldrcDock.top-= m_Oldrc.Height();
						m_OldrcDock.bottom= m_OldrcDock.top+m_Oldrc.Height();
					}
					else
					{
						if (iDock ==1)
							m_OldrcDock.right=rcW.left+ (rcW.Width()/2);
						else
							m_OldrcDock.left=rcW.right- (rcW.Width()/2);
					}
					
				}
				DrawFrame(m_OldrcDock);
				bDrawNormalDock=TRUE;
				bDrawTab=FALSE;
				bDrawNormal=FALSE;
			}
		}
		else
		{
				if (bDrawTab)
				{
					bDrawTab=FALSE;
				}
				
				if (bDrawNormalDock)
				{
					DrawFrame(m_OldrcDock);
					bDrawNormalDock=FALSE;
				}
				if (!bDrawNormal)
				{
					DrawNormal();
					bDrawNormal=TRUE;
					bDrawTab=FALSE;
					bDrawNormalDock=FALSE;
				}
				else
				{
					DrawNormal();
				}

	
		}

	}
}

void CMiniDock::OnMouseMove(UINT nHitTest, CPoint pt)
{
	if (m_Drag)
	{
		CPoint point;
		GetCursorPos(&point);

		if ((m_oldPost.x != point.x) || 
					(m_oldPost.y != point.y))
				{
					CRect rcL;
					CRect rcR;
					CRect rcB;
					theApp->m_WinMain->m_DockLeft->GetWindowRect(rcL);
					theApp->m_WinMain->m_DockRight->GetWindowRect(rcR);
					theApp->m_WinMain->m_DockBottom->GetWindowRect(rcB);
					
					if (rcL.PtInRect(point))
					{
						DrawDock(rcL,point,theApp->m_WinMain->m_DockLeft,BS_ALIGN_LEFT);
					}
					else if (rcR.PtInRect(point))
					{
						DrawDock(rcR,point,theApp->m_WinMain->m_DockRight,BS_ALIGN_RIGHT);
					}
					else if(rcB.PtInRect(point) )
					{
						DrawDock(rcB,point,theApp->m_WinMain->m_DockBottom,BS_ALIGN_BOTTOM);
					}
					else
					{
						if (bDrawTab)
						{
							bDrawTab=FALSE;
						}
						
						if (bDrawNormalDock)
						{
							DrawFrame(m_OldrcDock);
							bDrawNormalDock=FALSE;
						}
						if (!bDrawNormal)
						{
							DrawNormal();
							bDrawNormal=TRUE;
							bDrawTab=FALSE;
							bDrawNormalDock=FALSE;
						}
						else
						{
							DrawNormal();
						}

					}
					
				}
	}
	
	Default();
}

void CMiniDock::OnNcLButtonUp(UINT nHitTest, CPoint point)
{

		  if (m_Drag==TRUE) 
		  {
			ReleaseCapture();
			m_Drag=FALSE;
		  }
		  Default();
}

void CMiniDock::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	
	m_Drag=FALSE;
	if (nHitTest == HTCAPTION){
		m_oldPost=point;
		m_Drag=TRUE;
		SetWindowPos(HWND_TOP,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
		SetCapture();
		GetWindowRect(mWin);
		mWin.InflateRect(1,1);
     	m_Oldrc=mWin;
		bDrawNormal=TRUE;
		bDrawTab=FALSE;
		bDrawNormalDock=FALSE;
	}
	if (nHitTest == HTCLOSE)
	{
		OnNcButtonDblClk(nHitTest, point);
	}
	Default();
	
}

void CMiniDock::OnNcButtonDblClk(UINT nHitTest, CPoint point)
{
		CRect rc;
			theApp->m_WinMain->m_DockLeft->GetWindowRect(rc);
			UINT ds=((CContainer*)m_ClientView)->m_DOCKSITE;
			if (ds == BS_ALIGN_LEFT)
			{
				m_ClientView->SetParent (theApp->m_WinMain->m_DockLeft);
				theApp->m_WinMain->m_DockLeft->AddWindow(m_ClientView);

			}
			else if (ds == BS_ALIGN_RIGHT)
			{
				m_ClientView->SetParent (theApp->m_WinMain->m_DockRight);
				theApp->m_WinMain->m_DockRight->AddWindow(m_ClientView);
			}

			else if (ds == BS_ALIGN_BOTTOM)
			{
				m_ClientView->SetParent (theApp->m_WinMain->m_DockBottom);
				theApp->m_WinMain->m_DockBottom->AddWindow(m_ClientView);
			}
			else if ( ((CContainer*)m_ClientView)->m_pContainer != NULL)
			{
				CTab* ct=((CContainer*)m_ClientView)->GetTab(0);
				ct->pParent->SetParent (((CContainer*)m_ClientView)->m_pContainer);
				((CContainer*)m_ClientView)->m_pContainer->Addtab(ct->pParent);
			}
			else{
				
					
				Default();	
				return;
			}
			SendMessage(WM_CLOSE,0,0);
			theApp->m_WinMain->UpdateFrame();
			Default();	
			
	
}

void CMiniDock::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	Default();	
}

void CMiniDock::OnWindowPostChanging(LPWINDOWPOS lpWindowsPos)
 {
	 
	Default();

}

void CMiniDock::OnKeyDown(int iKey, DWORD dTime)
{
	if (!m_Drag) return;
	if (iKey == VK_ESCAPE)
		OnLButtonUp(0, CPoint(0,0));
}

void CMiniDock::OnRButtonDown(UINT nHitTest, CPoint point)
 {
	OnLButtonUp(0, CPoint(0,0));
 }

void CMiniDock::DrawFrame(CRect rc, BOOL bDrawTab)
{
	if (bDrawNormal) return;
	CWin cm(theApp->m_WinMain->GetDesktopWindow());
	CGDI pDC(cm.GetDCEx(NULL,DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE));
	CBrush* pBrush = CGDI::HalftGray();
    CBrush pBrushOld(pDC.SelectObject(pBrush));
	CRect rc1=rc;
	HRGN hRgn=	 CreateRectRgnIndirect(rc);
	rc.DeflateRect(3,3);
	rc.IntersectRect(rc,rc1);
	HRGN hRgnIn= CreateRectRgnIndirect(rc);
	HRGN hRgnDif=CreateRectRgn(0,0,0,0);
	CombineRgn(hRgnDif,hRgnIn,hRgn,RGN_XOR);
	pDC.SelectClipRgn(hRgnDif);	
	pDC.GetClipBox(rc);
	pDC.PatBlt(rc, PATINVERT);
	::DeleteObject(hRgn);
	::DeleteObject(hRgnIn);
	::DeleteObject(hRgnDif);
	pDC.SelectObject(&pBrushOld);
    cm.ReleaseDC(pDC.m_hDC);
	pBrush->DeleteObject();
	delete pBrush;

}

//-----------------------------------------------------------
//-----------------------------------------------------------
//AutoHide Routines

static CFont m_fontHorzMenu, m_fontVertMenu;
static int _cyHorzFont, _cyMenuOnBar, _cyTextMargin;
const int CXTEXTMARGIN = 5;

static BOOL InitGlobalFont()
{

	if (m_fontHorzMenu.m_hFont != NULL &&  m_fontVertMenu.m_hFont != NULL)
		return TRUE;
	m_fontHorzMenu.DeleteObject();
	m_fontVertMenu.DeleteObject();

	// create fonts
	NONCLIENTMETRICS info; info.cbSize = sizeof(info);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
	if(!m_fontHorzMenu.CreateFontIndirect(&info.lfMenuFont))
		return FALSE;

	// create vertical font
	info.lfMenuFont.lfEscapement = -900;
	info.lfMenuFont.lfOrientation = -900;
	_tcscpy(info.lfMenuFont.lfFaceName, _T("verdana") );
	if(!m_fontVertMenu.CreateFontIndirect(&info.lfMenuFont))
		return FALSE;

	_cyHorzFont = abs(info.lfMenuFont.lfHeight);

	// calc Y text margin
	_cyMenuOnBar = info.iMenuHeight;
	_cyMenuOnBar = max(_cyMenuOnBar, ::GetSystemMetrics(SM_CYSMICON));
	_cyTextMargin = (_cyMenuOnBar - _cyHorzFont) / 2;

	return TRUE;
}

DockAutoHide::DockAutoHide()
{
	m_DockWindows.RemoveAll();
	n_numBars=0;

}

DockAutoHide::~DockAutoHide()
{

}
	
BOOL DockAutoHide::Create(DWORD dwStyle, const RECT& rect, CWin* pParentWnd, UINT nID)
{
	pParent= pParentWnd;
	m_uID=nID;
	LPCTSTR lpclassname=RegisterDefaultClass(NULL,WS_CHILD|WS_VISIBLE);
	return CWin::Create(lpclassname, _T(""), dwStyle, rect, pParentWnd->GetSafeHwnd(), nID);

}

void DockAutoHide::DrawTextVert(CGDI* pDC, CRect m_rect,LPCSTR m_Caption)
{
	COLORREF clr = ::GetSysColor(COLOR_MENUTEXT);
	pDC->SetTextColor(clr);

	int iGraphicsMode = ::GetGraphicsMode(pDC->m_hDC);
	::SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->SetBkMode(TRANSPARENT);
	CFont pOldFont = pDC->SelectObject(m_fontVertMenu);
	
	CSize m_sizeHorz;
	CSize m_sizeCad=pDC->GetTextExtent(m_Caption,strlen(m_Caption));
	m_sizeHorz.cx = ( m_sizeCad.cx + CXTEXTMARGIN*2)+8;
	m_sizeHorz.cy = (_cyHorzFont + _cyTextMargin*2)+1;
	CRect rcString = CRect(
	CPoint(m_rect.right - _cyTextMargin, m_rect.top + CXTEXTMARGIN), m_sizeHorz);

	pDC->DrawText(m_Caption, rcString,
		DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX);// don't forget DT_NOCLIP
	pDC->SelectObject(pOldFont);

	::SetGraphicsMode( pDC->m_hDC, iGraphicsMode );
}
void DockAutoHide::AddWindow(CWin* pWin)
{

}

BOOL DockAutoHide::OnPaint(HDC hDC)
{
	CPaintDC dc(this); // device context for painting
	CRect m_rect;
	GetClientRect(m_rect);
	CBrush cbr;
	cbr.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
	dc.FillRect(m_rect,&cbr);
	return TRUE;
}
BOOL DockAutoHide::OnLButtonDown(UINT nFlags, CPoint pt)
{
	return Default();
}
BOOL DockAutoHide::OnSize(UINT nType, int cx, int cy)
{
	RecalLayout();
	Default();
	return TRUE;
}
BOOL DockAutoHide::OnEraseBkgnd(HDC hDC )
{
	CGDI pDC(hDC);
	CBrush cbr;
	cbr.CreateSysColorBrush(COLOR_BTNFACE);
	CRect m_rect;
	GetClientRect(m_rect);
	pDC.FillRect(m_rect,&cbr);
	cbr.DeleteObject();
	return TRUE;

}
int  DockAutoHide::OnDestroy()
{
	return TRUE;
}

BOOL DockAutoHide::OnLButtonUp(UINT nFlags, CPoint pt)
{
	return Default();
}
void DockAutoHide::OnMouseMove(UINT nHitTest, CPoint point)
{
}

void DockAutoHide::RecalLayout()
{
	if (m_DockWindows.GetSize() > 0)
		ShowWindow(SW_SHOW);
	else
		ShowWindow(SW_HIDE);


}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
BOOL CChildWnd::LoadFrame(UINT nID,HWND hParentWnd,DWORD dwStyle)
{	
	
	int nLen;
	TCHAR szTemp[256];
	BOOL pbMaximized;
	LPCTSTR lpszName = MAKEINTRESOURCE((nID>>4)+1);
	if (::FindResource(GetModuleHandle(NULL), lpszName, RT_STRING) != NULL &&
		(nLen = ::LoadString(GetModuleHandle(NULL), nID, szTemp, 255) != 0)) {
	}
	HWND hWnd = (HWND)::SendMessage(hParentWnd, WM_MDIGETACTIVE, 0,
		(LPARAM)&pbMaximized);
	if (pbMaximized)
		dwStyle|=WS_MAXIMIZE;
	BOOL bRes=CreateEx(WS_EX_MDICHILD,_T( "MotsusChildWindow" ),_T("Untitled"),dwStyle,CRect(CW_USEDEFAULT,
			CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT),hParentWnd,nID);
	ModifyStyle(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
	hMenu=theApp->LoadMenuMDI((LPCTSTR)nID);		
	SetIcon(theApp->LoadIcon((LPCSTR)nID),FALSE);
	::SendMessage(GetParent(),WM_MDISETMENU,(WPARAM)hMenu,0);
	theApp->m_WinMain->cSpawn.RemapMenu(hMenu);
	theApp->m_WinMain->DrawMenuBar();

	
	return bRes;
}

LRESULT CChildWnd::DefWindowProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam)
{
	if (lpfnOldWndProc !=NULL )
		return CallWindowProc(lpfnOldWndProc, hWnd, uID,wParam, lParam); 
	return ::DefMDIChildProc(hWnd,uID,wParam,lParam);
}

void CChildWnd::MDIActivate(HWND hWndActivate,LPARAM lParam)
{ 
	
	if(  lParam)
		::SendMessage(GetParent(),WM_MDISETMENU,(WPARAM)hMenu,0);
	else
		::SendMessage(GetParent(),WM_MDISETMENU,(WPARAM)theApp->GetMenuDefault(),0);
	
	theApp->m_WinMain->DrawMenuBar();
	
	if (::IsWindow(GetParent()))
		::SendMessage(GetParent(), WM_MDIACTIVATE,(WPARAM)m_hWnd, 0);
	
}

void CChildWnd::MDIMaximize(HWND hWndActivate)
{
	::SendMessage(GetParent(), WM_MDIMAXIMIZE,(WPARAM)m_hWnd, 0);
}


BOOL CFrameMDI::LoadFrame(UINT nID,DWORD dwStyle,HWND hParentWnd)
{	
	BOOL rs=CFrame::LoadFrame(nID,dwStyle,hParentWnd);
	if (rs==TRUE)
		if (theApp != NULL)
			theApp->bMDI=TRUE;
	return rs;

}
		
HWND CFrameMDI::MDIGetActive(BOOL* pbMaximized)
{
	
	if (hMDIClient == NULL)
		return NULL;
	
	HWND hWnd = (HWND)::SendMessage(hMDIClient, WM_MDIGETACTIVE, 0,
		(LPARAM)pbMaximized);
	if (hWnd)
		return hWnd;
		
	return NULL;
	
}
	
void CFrameMDI::MDIActivate(HWND hWndActivate,LPARAM lParam)
{ 

	if (::IsWindow(hMDIClient))
		::SendMessage(hMDIClient, WM_MDIACTIVATE,(WPARAM)hWndActivate, 0);
	
}
void CFrameMDI::MDIIconArrange()
{ 
	 if (::IsWindow(hMDIClient)) 
		::SendMessage(hMDIClient, WM_MDIICONARRANGE, 0, 0); 
}

void CFrameMDI::MDIMaximize(HWND hWndParent)
{
	if (::IsWindow(hMDIClient)) 
		::SendMessage(hMDIClient, WM_MDIMAXIMIZE, (WPARAM)hWndParent, 0); 
}

void CFrameMDI::MDINext()
{ 
	if (::IsWindow(hMDIClient)) 
		::SendMessage(hMDIClient, WM_MDINEXT, 0, 0); 
}

void CFrameMDI::MDIRestore(HWND hWndParent)
{ 
	if (::IsWindow(hMDIClient)) 
		::SendMessage(hMDIClient, WM_MDIRESTORE, (WPARAM)hWndParent, 0); 
}

HMENU CFrameMDI::MDISetMenu(HMENU hMenuParent, HMENU hMenuWindow)
{ 
	if (::IsWindow(hMDIClient)) 
		return (HMENU)::SendMessage(hMDIClient, WM_MDISETMENU, (WPARAM)hMenuParent,
							(LPARAM)hMenuWindow); 
	return NULL;
}

void CFrameMDI::MDITile()
{ 
	if (::IsWindow(m_hWnd)) 
		::SendMessage(hMDIClient, WM_MDITILE, 1, 0); 
}

void CFrameMDI::MDICascade()
{ 
	if (::IsWindow(m_hWnd)) 
		::SendMessage(hMDIClient, WM_MDICASCADE, 0, 0); 
}

void CFrameMDI::MDICascade(int nType)
{ 
	if (::IsWindow(m_hWnd)) 
		::SendMessage(hMDIClient, WM_MDICASCADE, nType, 0); 
}

void CFrameMDI::MDITile(int nType)
{ 
	if (::IsWindow(m_hWnd)) 
		::SendMessage(hMDIClient, WM_MDITILE, nType, 0); 
}


LRESULT CFrameMDI::DefWindowProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam)

{
	
	HWND hWChild=(HWND)::SendMessage(hMDIClient,WM_MDIGETACTIVE,0,0);
	if (hWChild)
		::SendMessage(hWChild,WM_COMMAND,wParam,lParam);
	return ::DefFrameProc(hWnd,hMDIClient,uID,wParam,lParam);
	
}


BOOL CFrameMDI::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
	ccs.hWindowMenu  = ::GetMenu(GetSafeHwnd());
	ccs.idFirstChild = ID_MDI_FIRSTCHILD;
	if (hMDIClient != NULL) return TRUE;
	hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, "MDIclient", NULL,
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | 
			ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE |
			ES_NOHIDESEL | MDIS_ALLCHILDSTYLES|WS_CLIPCHILDREN,
			CW_USEDEFAULT , CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			m_hWnd, (HMENU)ID, GetModuleHandle(NULL), (LPVOID)&ccs);
	::BringWindowToTop(hMDIClient);
	if( hMDIClient==NULL)
		return FALSE;
	return TRUE;		

}


BOOL CFrameMDI::WindowsPosChanged(LPWINDOWPOS lpWindowsPos)
{ 
	BOOL bMaximize;
	HWND hWndChild = MDIGetActive(&bMaximize);
	if(hWndChild != NULL && hMDIClient != m_hWnd)
		return FALSE;
	    
	DWORD dwStyle = ::GetWindowLong(hMDIClient, GWL_EXSTYLE);
	DWORD dwNewStyle = dwStyle;
	dwNewStyle |= WS_EX_CLIENTEDGE;

	::RedrawWindow(hMDIClient, NULL, NULL,
				RDW_INVALIDATE | RDW_ALLCHILDREN);
	::SetWindowLong(hMDIClient, GWL_EXSTYLE, dwNewStyle);
	::SetWindowPos(hMDIClient, NULL, 0, 0, 0, 0,
		SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE |
		SWP_NOZORDER | SWP_NOCOPYBITS);
		return TRUE;
}

void CFrameMDI::OnCloseChild()
{
	BOOL pbMaximized;
	HWND hwndChild = MDIGetActive(&pbMaximized);
        
		if (::SendMessage (hwndChild, WM_QUERYENDSESSION, 0, 0))
			::SendMessage (hMDIClient, WM_MDIDESTROY,(WPARAM) hwndChild, 0) ;
          
}

BOOL CToolBarCtrl::CreateCombo(CComboBoxExt* pControl,UINT nID,int iSize,DWORD dwStyle)
{
	CRect rect;
	int nIndex = CommandToIndex(nID);
    TBBUTTON button;
	GetButton(nIndex, &button);
	UINT Style= MAKELONG(TBSTYLE_SEP, 0);
	button.idCommand = nID;
	button.iBitmap = iSize;
	button.fsStyle = (BYTE)LOWORD(Style);
	button.fsState = (BYTE)HIWORD(Style);
	InsertButton(nIndex, &button);
	GetItemRect(nIndex, &rect);
	rect.top = 1;
	rect.bottom = rect.top + 250 /*drop height*/;
	if(!pControl->Create(GetSafeHwnd(),nID,0,dwStyle, rect))
	{
		return FALSE;
	}
	//pControl->SetImageList(m_imgList);
	return TRUE;
	
}


CApp::~CApp()
{
	if (HIWORD(m_WinMain))
	{
		delete m_WinMain;

	}
}
		

	
	
void CApp::LoadMain(HINSTANCE hinstace, HINSTANCE PrehInstance, LPSTR cmdLine, int show)
{
	m_hInstance=hinstace;
	m_prehInstance=PrehInstance;
	m_LineCommands=cmdLine;
	m_nShow=show;
	#if (_WIN32_IE >= 0x0300)
		INITCOMMONCONTROLSEX iccex;
		iccex.dwSize = sizeof(iccex);
		iccex.dwICC =  ICC_COOL_CLASSES | ICC_USEREX_CLASSES;	
		InitCommonControlsEx(&iccex);
	#else
		InitCommonControls();
	#endif
	registerClass(m_hInstance);
}

		
HACCEL CApp::LoadAccelerators(LPCTSTR lpTableName)
{
	return ::LoadAccelerators(GetInstance(),lpTableName);
}


HRSRC CApp::FindResource(UINT nResourceID, LPCTSTR lpType)
{
	return ::FindResource(m_hInstance, MAKEINTRESOURCE(nResourceID),lpType);
}

	
HRSRC CApp::FindResourceToolBar(UINT nResourceID)
{
	return FindResource(nResourceID,RT_TOOLBAR);
}


HGLOBAL CApp::LoadResource(HRSRC hRsrc)
{
	HGLOBAL hGlobal= ::LoadResource(m_hInstance, hRsrc);
	if (hGlobal == NULL)
		return NULL;
	return hGlobal;
}
		
	
BOOL CApp::LoadMenu(LPCTSTR lpszMenuName)
{
	if (!m_Menu.LoadMenu(lpszMenuName))
		return FALSE;
	::SetMenu(m_WinMain->GetSafeHwnd(),m_Menu.GetHandleMenu());
	m_WinMain->cSpawn.RemapMenu(m_Menu.GetHandleMenu());	
	
	return TRUE;
	
}
	
	
	
HMENU CApp::LoadMenuMDI(LPCTSTR lpszMenuName)
{
	HMENU hMenul;
		if (lpszMenuName != NULL)
		{
			
			if ((hMenul = ::LoadMenu(GetModuleHandle(NULL), lpszMenuName)) == NULL)
			{
				return NULL;
			}
				
			return hMenul;
		}
		return NULL;
}		
	
	
HMENU CApp::LoadMenuWindow()
{
	if (m_WinMain->GetMenu() !=m_Menu.GetHandleMenu())
	{
		::SetMenu(m_WinMain->GetSafeHwnd(),m_Menu.GetHandleMenu());
	}

	return m_WinMain->GetMenu();

}

void CApp::SetRegistryKey(LPCSTR lpKey)
{
 lstrcpy(m_lpBuffer,lpKey);
}

int CApp::Run()
{
	
	MSG msg;
	BOOL bresult;
	BOOL bPeekMsg=TRUE;
	while (bPeekMsg || GetMessage(&msg, NULL, 0, 0)) 
	{
		
		if (bPeekMsg)
		{
			if(!PeekMessage(&msg,NULL,0,0,PM_REMOVE))
				bPeekMsg=m_WinMain->OnIdle();
			continue;
		}

		if (bMDI)
		{
			bresult=(
					(!TranslateMDISysAccel (m_WinMain->GetSafeClientHwnd(), &msg)) 
					&&  	(!TranslateAccelerator (msg.hwnd,hAccelTable, &msg)));
		}
		else
			bresult=(!TranslateAccelerator (msg.hwnd, hAccelTable, &msg));
	
		CWin* pActive= reinterpret_cast<CWin*>((HWND)::GetWindowLong(msg.hwnd,GWL_USERDATA)); //CWin::GetUserPointerWindow(msg.hwnd); 
		BOOL bPre=TRUE;
		if (pActive)
			bPre=pActive->PreTranslateMessage(&msg);
		if (bresult && bPre) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
	}
	return  msg.wParam;
	

}

	
	
CWin* CApp::GetMainWindows() 
{
	if (::IsWindow(m_WinMain->GetSafeHwnd()))
		return m_WinMain;
	else 
		return NULL;
}