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




CFolderBar::CFolderBar(CWin* m_wnd,LPCSTR lp_msg,UINT uImg)
{
	m_CWin=m_wnd;
	m_lpMsg=lp_msg;
	m_img=uImg;
	m_rect=CRect(0,0,0,0);
	m_posUp=TRUE;
	
}


CFolderBar::~CFolderBar()
{
	if (HIWORD(m_CWin))
		DestroyWindow(m_CWin->GetSafeHwnd());
}

CFolder::CFolder()
{
	m_ArrayFolder.RemoveAll();
	m_NumFolders=0;
	m_numFolderDown=0;
	m_numFolderUp=0;
	m_iSelected=0;	
	m_ultimoFolderResal =-1;
	m_itemp=0;
	m_typel=mOutlook;//by default
	m_iWhatFolderIsDrawNow=0;
	cfont=NULL;
}


CFolder::~CFolder()
{
	if (cfont)
		delete cfont;
}


/////////////////////////////////////////////////////////////////////////////
// CFolder message handlers
BOOL CFolder::Create(CWin* pParentWnd, CRect& rect, DWORD dwStyle,   UINT nID)
{
	LPCTSTR lpclassname=RegisterDefaultClass(NULL,CS_HREDRAW|CS_VREDRAW);
	return CWin::Create(lpclassname,NULL,dwStyle, CRect(0,0,0,0), pParentWnd->GetSafeHwnd(), nID);
}

BOOL CFolder::OnLButtonDown(UINT nFlags,  CPoint point) 
{
	int m_iNumBotton=m_ArrayFolder.GetSize();
	for( int iCont=0; iCont< m_iNumBotton;iCont++)
	{
		CFolderBar* cit=(CFolderBar*)m_ArrayFolder[iCont];
		if (cit->m_rect.PtInRect(point))
		{
			DrawFolder(cit,mPush);
		}
	}
	return TRUE;
}

void CFolder::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	
}

BOOL CFolder::OnLButtonUp(UINT nFlags,   CPoint point) 
{
	int m_iNumBotton=m_ArrayFolder.GetSize();
	for( int iCont=0; iCont< m_iNumBotton;iCont++)
	{
		CFolderBar* cit=(CFolderBar*)m_ArrayFolder[iCont];
		if (cit->m_rect.PtInRect(point))
		{
			DrawFolder(cit,mFlat);
			m_itemp=m_iSelected;
			m_iSelected=iCont;
			EfectoScroll();
		}
	}	
	return TRUE;

}

BOOL CFolder::IsThisSelected() 
{
	if (m_ultimoFolderResal==m_iSelected)
		return TRUE;
	return FALSE;

}


void CFolder::TypeLook(TypeFolder tol)
{
	m_typel=tol;
}

void CFolder::EfectoScroll()
{
	int m_iNumBotton=m_ArrayFolder.GetSize();
	int m_iSentidoScroll=0;	//1=hacia abajo, 2=hacia arriba
	if (m_iNumBotton > 0) //si existe un solo folder no haga nada
	{
		// si es el ultimo folder y no esta abajo no haga nada
		if (m_iSelected == m_NumFolders-1 &&
			((CFolderBar*)m_ArrayFolder[m_iSelected])->m_posUp ==TRUE)	
		{
			m_iSelected=m_itemp;
			return;
		}
		else if (((CFolderBar*)m_ArrayFolder[m_iSelected])->m_posUp ==TRUE )
		{
			if (((CFolderBar*)m_ArrayFolder[m_iSelected+1])->m_posUp ==FALSE)
				return;
			m_iSentidoScroll =1;
				//de esta posición todos los folders hacia abajo 
			for (int iCont=m_iSelected+1;iCont < m_iNumBotton; iCont++)
				((CFolderBar*)m_ArrayFolder[iCont])->m_posUp =FALSE;
				
		}
		else if (((CFolderBar*)m_ArrayFolder[m_iSelected])->m_posUp ==FALSE)
		{
				m_iSentidoScroll =2;
				//de esta posición todos los folders van arriba
				for (int iCont=m_iSelected;iCont >0; iCont--)
					((CFolderBar*)m_ArrayFolder[iCont])->m_posUp =TRUE;
		}
		
	}

	CRect m_rect=((CFolderBar*)m_ArrayFolder[m_iSelected])->m_rect;
	CClientDC dc(GetSafeHwnd());
	if (m_iSentidoScroll >0)
	{
		CWin* pParent=((CFolderBar*)m_ArrayFolder[m_itemp])->m_CWin;
		ASSERT(pParent);
		CWin* pParentn=((CFolderBar*)m_ArrayFolder[m_iSelected])->m_CWin;
		ASSERT(pParentn);
		pParent->ShowWindow(SW_HIDE);
		pParentn->ShowWindow(SW_SHOW);
		m_AntFolder=m_iSelected;
	}
	
	if (m_iSentidoScroll ==1)
	{
		/*CFolderBar* cb=(CFolderBar*)m_ArrayFolder[m_iSelected];
		CWin* m_CWin=((CFolderBar*)m_ArrayFolder[m_iSelected])->m_CWin;
		CRect rctemp=cb->m_rect;
		while (m_rect.bottom < m_iPosDown)
		{
			m_CWin->SetWindowPos(NULL,m_rect.left,cb->m_rect.bottom,m_rect.Width(),m_rect.bottom,
			SWP_NOACTIVATE|SWP_NOZORDER);
			m_rect.bottom+=10;
			//DrawFolder(cb,mFlat);
			//m_CWin->Invalidate();
			//m_CWin->SendMessage(WM_PAINT,0,0);
			
			
			
		}*/
		RecalLayout();	
	}
	else if (m_iSentidoScroll ==2)
	{
		/*CWin* m_CWin=((CFolderBar*)m_ArrayFolder[m_iSelected])->m_CWin;
		CFolderBar* cb=(CFolderBar*)m_ArrayFolder[m_iSelected];
		while (m_rect.top > m_iposUp)
		{
			m_CWin->SetWindowPos(NULL,m_rect.left,m_iposUp-1,m_rect.Width(),m_iPosDown-m_iposUp,
			SWP_NOACTIVATE|SWP_NOZORDER);
			cb->m_rect.top-=10;
			cb->m_rect.bottom-=10;
			Sleep(50);
			DrawFolder(cb,mFlat);
			
			
		}
		*/
		RecalLayout();	
	}
	else
		m_iSelected=m_itemp;
		



}

void CFolder::OnMouseMove(UINT nFlags,  CPoint point) 
{
	int m_iNumBotton= m_ArrayFolder.GetSize();
	static int m_AntTecla=-1;
	for( int iCont=0; iCont< m_iNumBotton;iCont++)
	{
		CFolderBar* cit=(CFolderBar*)m_ArrayFolder[iCont];
		m_iWhatFolderIsDrawNow=iCont;
		if (cit->m_rect.PtInRect(point))
		{
			if (m_ultimoFolderResal==m_AntTecla &&
				(m_ultimoFolderResal!=-1 && m_AntTecla !=-1)) return;
			else
			{
			  if (m_ultimoFolderResal != -1)
			  {
				CFolderBar* cit1=(CFolderBar*)m_ArrayFolder[m_ultimoFolderResal];	
				DrawFolder(cit1,mFlat);
			  }
			}
			DrawFolder(cit,mNormal);
			m_AntTecla=m_ultimoFolderResal;
			m_ultimoFolderResal=iCont;
			SetTimer(1,100,NULL);
			return;			
		}
	}	

	if (m_ultimoFolderResal != -1)
	 {
		CFolderBar* cit1=(CFolderBar*)m_ArrayFolder[m_ultimoFolderResal];	
		DrawFolder(cit1,mFlat);
		m_ultimoFolderResal=-1;
	 }
	m_AntTecla=-1;

}



void CFolder::DrawFolder(CFolderBar* cfb,Style m_Style)
{
	CRect rc=cfb->m_rect;
	CBrush cb;
	CClientDC pDC(GetSafeHwnd());
	cb.CreateSysColorBrush(COLOR_BTNFACE);
	
	pDC.FillRect(&rc,&cb);
	CGradient M(CSize(rc.Width(),rc.Height()));	
	M.PrepareVertical(&pDC);
	M.Draw(&pDC,rc.left,rc.top,0,0,rc.Width(),rc.Height(),SRCCOPY);
	
	
	int OldMode=pDC.SetBkMode(TRANSPARENT);
	cfont = (CFont*)pDC.SelectObject(CFont((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	TCHAR m_cadBreak[64];
	memset(m_cadBreak,0x00,64);
	lstrcpy(m_cadBreak,cfb->m_lpMsg);
	int contt;
	int cont =contt=strlen(m_cadBreak);
	CSize coor=pDC.GetTextExtent(m_cadBreak,cont);
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
	{
	  if (m_typel!=mOutlook)
			pDC.DrawText(cfb->m_lpMsg,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	  else	
			pDC.DrawText(cfb->m_lpMsg,rc,DT_WORDBREAK|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}

	

   	pDC.SetBkColor(OldMode);
	DeleteDC(pDC.m_hDC);
}


BOOL CFolder::OnPaint(HDC hDC) 
{
	CPaintDC dc(this); 
	CRect mrect;
	int m_iNumFolder=m_ArrayFolder.GetSize();
	for ( int iCont=0; iCont< m_iNumFolder; iCont++)
	{
		m_iWhatFolderIsDrawNow=iCont;
		if (m_iSelected== iCont)
			DrawFolder((CFolderBar*) m_ArrayFolder[iCont],mFlat);
		else
			DrawFolder((CFolderBar*) m_ArrayFolder[iCont],mFlat);		

	}	
	return TRUE;
}

BOOL CFolder::OnSize(UINT nType, int cx, int cy) 
{
	if (m_NumFolders > 0)
	{
		RecalLayout();
		return TRUE;
	}
	return FALSE;
	
	
}

void CFolder::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		CRect rc;
		CPoint pt(GetMessagePos());
		ScreenToClient (&pt);
		GetClientRect(&rc);
		if (m_ultimoFolderResal != -1)
		{
			CFolderBar* cfd=(CFolderBar*) m_ArrayFolder[m_ultimoFolderResal];
			rc=cfd->m_rect;
		}
		
		if (!rc.PtInRect(pt))
		{
			if (m_ultimoFolderResal != -1)
			{
			CFolderBar* cfd=(CFolderBar*) m_ArrayFolder[m_ultimoFolderResal];
			CClientDC dc(GetSafeHwnd());
			DrawFolder(cfd,mFlat);
			m_ultimoFolderResal=-1;
			}
			KillTimer(1);
		}
		
	}

}

int CFolder::PointInFolder(CPoint pt)
{
	for (int i=0; i <	m_ArrayFolder.GetSize(); i++)
	{
		if ( ((CFolderBar*) m_ArrayFolder[i])->m_rect.PtInRect(pt) )
			return i;
	}
	return -1;
}

BOOL CFolder::PreTranslateMessage(MSG* pMsg) 
{
	return TRUE;
}

void CFolder::RecalLayout()
{
	CRect m_rect;
	CRect m_rectFolder;
	m_iPosDown=0; //a partir de donde se ubica el anterior folder
	m_iposUp=0;   //a partir de donde se ubica el siguiente folder
	int m_iNumFolder=m_ArrayFolder.GetSize();
	GetClientRect(&m_rect);
	m_rectFolder=m_rect;
	m_iPosDown=m_rect.bottom;
	for ( int iCont=0; iCont< m_iNumFolder; iCont++)
	{
		CFolderBar* cfd=(CFolderBar*) m_ArrayFolder[iCont];
		if (iCont==0) //inevitablemente arriba
		{
			m_rectFolder.bottom=m_rect.top+20;
			m_iposUp+=m_rectFolder.Height()-1;
			cfd->m_rect=m_rectFolder;
		}
		else
		{
			if (cfd->m_posUp)
			{
				m_rectFolder.top=m_iposUp;
				m_rectFolder.bottom=m_rectFolder.top+20;
				m_iposUp+=m_rectFolder.Height();
				cfd->m_rect=m_rectFolder;
			}
			else
			{
				
				for(int iRev=m_iNumFolder-1; iRev>=iCont; iRev--)
				{
					CFolderBar* cfd=(CFolderBar*) m_ArrayFolder[iRev];
					m_rectFolder.bottom=m_iPosDown;
					m_rectFolder.top=m_rectFolder.bottom-20;
					m_iPosDown-=m_rectFolder.Height();
					cfd->m_rect=m_rectFolder;
				}
				break;
			}
		}
		
	}
	CFolderBar* cfd=(CFolderBar*) m_ArrayFolder[m_iSelected];
	CWin*	m_CWin=cfd->m_CWin;
	int nAddPos;
	if (m_iSelected == 0)
		nAddPos=1;
	else
		nAddPos=0;
	m_CWin->SetWindowPos(NULL,m_rect.left,m_iposUp+nAddPos,m_rectFolder.Width(),(m_iPosDown-m_iposUp),
		SWP_NOZORDER |SWP_DRAWFRAME);
}

void CFolder::AddFolder(CWin* pParent,LPCSTR lpMsg, UINT uIMg)
{
	m_ArrayFolder.SetAtGrow(m_NumFolders, new CFolderBar(pParent,lpMsg,uIMg));
	if (m_NumFolders == 0)
	  m_numFolderUp=1;
	if (m_NumFolders > 0)
	{
		for( int iCont=0; iCont< m_NumFolders;iCont++)
		{
			CFolderBar* cit=(CFolderBar*)m_ArrayFolder[iCont];
			cit->m_CWin->ShowWindow(SW_HIDE);
		}		
	}
	pParent->ShowWindow(SW_SHOW);
	m_iSelected=m_NumFolders;
	m_AntFolder=m_iSelected;
	m_NumFolders++;
	RecalLayout();
}


BOOL CFolder::OnEraseBkgnd(HDC hDC) 
{
	CBrush cbr;
	CGDI  pDC(hDC);
	cbr.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
	CRect m_rect;
	GetClientRect(m_rect);
	if (m_NumFolders<= 0)
		pDC.FillRect(m_rect,&cbr);
	else
	{
		for (int i=0;i<2; i++)
		{
			pDC.Draw3dRect(m_rect,CDrawLayer::GetRGBColorFace(),CDrawLayer::GetRGBColorFace());
			m_rect.DeflateRect(1,1);
		}
	}
	return TRUE;
}

void CFolder::DeleteFolder(int m_iNumFolder, BOOL bUpdate)
{
	if (m_iNumFolder < m_NumFolders)
	{
		if (bUpdate && m_iNumFolder == m_NumFolders -1)
			SelectFolder(0);
		if (m_iNumFolder == m_iSelected && m_iNumFolder != 0)
		{
			SelectFolder(1);
			m_iSelected = 1;
		}
		CFolderBar* pBar = (CFolderBar*)m_ArrayFolder.GetAt(m_iNumFolder); 
		m_ArrayFolder.RemoveAt(m_iNumFolder,1);
		delete pBar;
		m_NumFolders--;
		if (m_iNumFolder == m_NumFolders)
			m_iSelected = m_iNumFolder - 1;
		if (m_iNumFolder == 0)
			m_iSelected = m_NumFolders - 1;
		else if(m_iNumFolder > 0)
			m_iSelected = m_iNumFolder - 1;
		if (bUpdate) 
		{
			int OldSel = m_iSelected;
			RecalLayout();
			SelectFolder(0);
			SelectFolder(m_NumFolders - 1);
			SelectFolder(OldSel);
		}
	}
}


void CFolder::SelectFolder(int m_iNumFolder)
{
	CFolderBar* cf = (CFolderBar*) m_ArrayFolder[m_iNumFolder];
	if (cf)
	{
		DrawFolder(cf,mFlat);
		m_itemp = m_iSelected;
		m_iSelected = m_iNumFolder;
		EfectoScroll();
	}
}



void CFolder::RemoveAllFolder()
{
	m_ArrayFolder.RemoveAll();
	Invalidate();
	m_NumFolders=-1;
	m_iSelected=-1;
}

	
int CFolder::OnDestroy()
{
	for( int i=0; i<m_NumFolders; i++ )
    {
	    CFolderBar *pArr = (CFolderBar*)m_ArrayFolder.GetAt(i);
	    if( HIWORD(pArr) )
		{
			pArr->m_CWin->OnDestroy();
		}
    }
	m_ArrayFolder.RemoveAll();
	return TRUE;
}





