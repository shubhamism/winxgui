/*
 * CHeaderView.cpp		1.0  23/09/2003
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. 
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 *  ----------------------
 * 
 *   Windows Wrapper function
 *
 *****/
#include "stdafx.h"
#include "CHeaderCtrl.h"


#define UPDATEWIN  Invalidate();\
				   UpdateWindow(); 

/////////////////////////////////////////////////////////////////////////////
// CHeaderView

CHeaderView::CHeaderView()
{
	m_clrFace= ::GetSysColor(COLOR_3DFACE);
	m_clrShadow= ::GetSysColor(COLOR_BTNSHADOW);
	m_clrLight= ::GetSysColor(COLOR_BTNHIGHLIGHT);
	m_nNumbottomSelect=-1;
	m_bSentido=TRUE;
	m_bMouserOver=FALSE;
	m_selected=-1;
	m_cfontNormal.CreateFont(14,0,0,0,400,0,0,0,0,1,2,1,34,"MS Sans Serif");
	m_cfontBold.CreateFont(14,0,0,0,700,0,0,0,0,1,2,1,34,"MS Sans Serif");
	
}

CHeaderView::~CHeaderView()
{
	m_cfontNormal.m_hFont=NULL;
	m_cfontBold.m_hFont=NULL;}



/////////////////////////////////////////////////////////////////////////////
// CHeaderView message handlers

//***************************************************************************
BOOL CHeaderView::DrawItem(HDITEM hdi,CGDI* pDC)
{
	CRect	rcitem;
	CSize	siImg=CSize(0,0);
	IMAGEINFO pImageInfo;
	int OldMode=pDC->SetBkMode(TRANSPARENT);
	GetItemRect(hdi.iOrder, rcitem);
	HFONT m_fontOldBold;
	HFONT m_fontOld;
	//---------------------------------------------------------
	//se mueve la imagen para dar la sensacion
	//de seleccion del item
	//---------------------------------------------------------
	if (m_nNumbottomSelect==hdi.iOrder)
	{
		DrawArrow(pDC,rcitem,m_bSentido);
		rcitem.right-=12;
	}
	
	if (hdi.iImage > -1)
	{
		m_img.GetImageInfo(hdi.iImage,&pImageInfo);
		CRect rcima =pImageInfo.rcImage;
		siImg=CSize(rcima.Width(),rcima.Height());
		CPoint pti(rcitem.left+2,rcitem.top+1);
		m_img.Draw( hdi.iImage,pDC->m_hDC, pti, ILD_TRANSPARENT);
	}
	
	if (hdi.cchTextMax > 0)
		{
			
			CRect m_rctext=rcitem;
			m_rctext.left+=siImg.cx+4;
			m_rctext.bottom-=2;
			if (m_bMouserOver && m_selected==hdi.iOrder)
				m_fontOldBold=pDC->SelectFont(m_cfontBold);
			else
				m_fontOld=pDC->SelectFont(m_cfontNormal);

			DrawTextExt(hdi.pszText,pDC,&rcitem);
		}

	
	
	pDC->SetBkMode(OldMode);
	return TRUE;
	
}

//**********************************************************************************
void CHeaderView::DrawTextExt(LPCSTR Cad,CGDI* pDC,CRect* rc)
{

	
	TCHAR m_cadBreak[64];
	memset(m_cadBreak,0x00,64);
	lstrcpy(m_cadBreak,Cad);
	int contt;
	int cont =contt=strlen(m_cadBreak);
	CSize coor=pDC->GetTextExtent(m_cadBreak,cont);
	if ( coor.cx > rc->Width())
	{
		rc->left+=1;
		while(cont > 1 )
		{
			TCHAR m_scadtemp[64];
			memset(m_scadtemp,0x00,64);
			lstrcpy(m_scadtemp,m_cadBreak);
			lstrcat(m_scadtemp,_T("..."));
			CSize coor=pDC->GetTextExtent(m_scadtemp,lstrlen(m_scadtemp));
			if(coor.cx > rc->Width())
				*(m_cadBreak+cont)=NULL;
			else
				break;
			cont--;
		}
		lstrcat(m_cadBreak,_T("..."));
		
		rc->right+=3;
		
	}

	pDC->DrawText(m_cadBreak,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);

}


void CHeaderView::PreSubClassWnd() 
{
	m_pParentWnd = GetParent();
	ASSERT(m_pParentWnd);
	ClearImages();
	ReDraw(); 
}

//********************************************************************************
void CHeaderView::DrawArrow(CGDI* pDC,CRect rc,BOOL bUp)
{
	CPen cp;
	CPen cps;
	CPen cpw;

	cp.CreatePen(PS_SOLID,1, m_clrFace);
	cps.CreatePen(PS_SOLID,1, m_clrShadow);
	cpw.CreatePen(PS_SOLID,1, m_clrLight);
	HPEN hPen;
	
	rc.left=rc.right-12;
	rc.right=rc.left+8;
	rc.bottom=rc.top+12;
	rc.top+=2;	
	int m_mitad=rc.left+4;
	
	if (bUp == TRUE)
	{
			//linea izquierda
			hPen=pDC->SelectObject(&cps);
			pDC->MoveTo(rc.left,rc.bottom);
			pDC->LineTo(m_mitad,rc.top);
			//linea derecha
			pDC->SelectObject(&cpw);
			pDC->MoveTo(rc.right,rc.bottom);
			pDC->LineTo(m_mitad,rc.top);
			//linea de abajo
			pDC->MoveTo(rc.left,rc.bottom);
			pDC->LineTo(rc.right,rc.bottom);
	}
	else
	{
			rc.bottom=rc.top+12;
			rc.top+=4;	
			//linea izquierda
			hPen=pDC->SelectObject(&cps);
			pDC->MoveTo(rc.left,rc.top);
			pDC->LineTo(m_mitad,rc.bottom);
			//linea superior
			pDC->MoveTo(rc.left,rc.top);
			pDC->LineTo(rc.right,rc.top);
			//linea derecha
				pDC->SelectObject(&cpw);
			pDC->MoveTo(rc.right,rc.top);
			pDC->LineTo(m_mitad,rc.bottom);

	}

	cp.DeleteObject();
	cps.DeleteObject();
	cpw.DeleteObject();
	//pDC->SelectObject(pOld);
}

//*******************************************************************

void CHeaderView::DelImageCol(int icol)
{
	HDITEM hdi;
	GetItem(icol,&hdi);
	hdi.iImage=-1;
	hdi.fmt |=  HDF_IMAGE;
	hdi.mask |= HDI_IMAGE | HDI_FORMAT;
	SetItem(icol,&hdi);
}

//*********************************************************************
void CHeaderView::SetImageCol(int icol,int img)
{
	HDITEM hdi;
	GetItem(icol,&hdi);
	hdi.iImage=img;
	hdi.fmt |=  HDF_IMAGE;
	hdi.mask |= HDI_IMAGE | HDI_FORMAT;
	SetItem(icol,&hdi);
}

//********************************************************************
int CHeaderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	ClearImages();
	ReDraw();
	return 0;
}


//********************************************************************
void CHeaderView::ReDraw() 
{
	int iNumItems=GetItemCount();
	HDITEM m_hditems;
	m_hditems.fmt  |= HDF_OWNERDRAW;
	for (int i =0; i < iNumItems; i++)
		SetItem(i,&m_hditems);

}

//*********************************************************************
void CHeaderView::ClearImages()
{
	HDITEM m_hditems;
	m_hditems.mask |=HDI_FORMAT|HDI_IMAGE;
	int iNumItems=GetItemCount();
	for (int i =0; i < iNumItems; i++)
	{
		m_hditems.iImage=-1;
		SetItem(i,&m_hditems);
	}

}

//********************************************************************
void CHeaderView::OnPaint(HDC hDC) 
{
	
	
	CPaintDC	dc(GetSafeHwnd()); // device context for painting
	CGDI		MemDC;
	CBitmap		m_BitmapMemDC;
	CRect		rcClient;
	CRect		rcWin;
	CBrush		m_brush;
	//******************************************
	GetWindowRect( &rcWin);
	GetClientRect( &rcClient );
	MemDC.CreateCompatibleDC(dc.m_hDC);
	m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,
				  rcClient.Width(),rcClient.Height());	

	CBitmap m_bitmapOld=MemDC.SelectObject(&m_BitmapMemDC);
	m_brush.CreateSysColorBrush(COLOR_3DFACE);
	MemDC.FillRect(rcClient,&m_brush); //evita el horrible color negro
	CGradient M(CSize(rcClient.Width(),rcClient.Height()));	
	M.PrepareVertical(&MemDC);
	M.Draw(&MemDC,rcClient.left,rcClient.top,0,0,rcClient.Width(),rcClient.Height(),SRCCOPY);

	ScreenToClient(rcWin);
	BiselaBoton(rcWin,&MemDC);
	int iNumItems=GetItemCount();
	int sizeOfBuffer = 256 ;
	LPSTR  lpBuffer= new TCHAR[sizeOfBuffer];
	
		
	for (int i =0; i < iNumItems; i++)
	{	
		HDITEM hdi;
		memset(lpBuffer,0x00,sizeOfBuffer);
		memset(&hdi,0x00,sizeof(struct _HD_ITEMW));
		GetItemFull(i,&hdi,lpBuffer,sizeOfBuffer);
		DrawItem(hdi,&MemDC);
		
	}
	delete[] lpBuffer;
	MemDC.Draw3dRect(rcClient,CDrawLayer::GetRGBSemiShadow(),CDrawLayer::GetRGBSemiShadow());
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(&m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();

}

//************************************************************************
void CHeaderView::BiselaBoton(CRect rcWin,CGDI* pDC)
{
	CPen cp;
	CPen cps;
	CPen cpw;

	cp.CreatePen(PS_SOLID,1, m_clrFace);
	cps.CreatePen(PS_SOLID,1, CDrawLayer::GetRGBSemiShadow());
	cpw.CreatePen(PS_SOLID,1, m_clrLight);
	/***************************************************
	pDC->Draw3dRect(rcWin,m_clrLight,m_clrShadow);
	rcWin.DeflateRect(1,1);
	pDC->Draw3dRect(rcWin,m_clrFace,m_clrFace);
	***************************************************/

	int iNumItems=GetItemCount();
	int iContx=0;
	for (int i =0; i < iNumItems; i++)
	{
		CRect recItem;
		GetItemRect(i, recItem);
		iContx+=recItem.Width();
		//quitamos todas las lineas
		recItem.DeflateRect(1,1);
		pDC->SelectObject(&cpw);
		pDC->MoveTo(iContx-2,rcWin.top+1);
		pDC->LineTo(iContx-2,rcWin.bottom-1);
		pDC->SelectObject(&cps);
		pDC->MoveTo(iContx-1,rcWin.top+1);
		pDC->LineTo(iContx-1,rcWin.bottom-1);
		pDC->SelectObject(&cpw);
		pDC->MoveTo(iContx,rcWin.top+1);
		pDC->LineTo(iContx,rcWin.bottom-1);
		
	}

	cp.DeleteObject();
	cps.DeleteObject();
	cpw.DeleteObject();
	
}

//*********************************************************************
void CHeaderView::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	Default();
	Invalidate();
	UpdateWindow();
	ReDraw();

}

//*********************************************************************************
BOOL CHeaderView::OnEraseBkgnd(HDC pDC) 
{
	return TRUE;
}

//*********************************************************************************
void CHeaderView::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_img.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(theApp->GetInstance(),(LPCTSTR)nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_img.Add(&cbmp,crMask);
	m_sizeImag=CSize(cx,bmp.bmHeight);	
	
}

int CHeaderView::GetSortColumn(BOOL* bSortCol )
{
	*bSortCol =m_bSentido;
	return m_nNumbottomSelect;

}

void CHeaderView::SetSortColumn(int nCol,BOOL sentido)
{
	m_nNumbottomSelect	=nCol;
	m_bSentido=sentido;
	Invalidate();
	UpdateWindow();
}

BOOL CHeaderView::OnSetCursor(HWND hWnd, UINT nHitTest, UINT message)
{
	Default();
	if (m_bMouserOver) return 0;
	CRect rc;
	GetClientRect(rc);
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	m_selected=-1;
	if (rc.PtInRect(pt))
	{
		int iNumItems=GetItemCount();
		for (int i =0; i < iNumItems; i++)
		{	
			CRect recItem;
			GetItemRect(i, recItem);
			if (recItem.PtInRect(pt))
			{
				m_selected=i;
				break;
			}
		}
		m_bMouserOver=TRUE;
		SetTimer(1,50,0);
		UPDATEWIN 		
	}
	
	return TRUE;
}

void CHeaderView::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bMouserOver) return;
	CRect rc;
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	GetClientRect(rc);

	CRect recItem;
	GetItemRect(m_selected, recItem);
	if (!rc.PtInRect(pt)||!recItem.PtInRect(pt))
	{

		m_bMouserOver=FALSE;
		KillTimer(1);
		m_selected=-1;
		UPDATEWIN 		
	}

}

BOOL CHeaderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Default();
	int iNumItems=GetItemCount();
	
	for (int i =0; i < iNumItems; i++)
	{	
		CRect recItem;
		GetItemRect(i, recItem);
		if (recItem.PtInRect(point))
		{
			if (m_nNumbottomSelect==i)
				m_bSentido=!m_bSentido;
			else
				m_bSentido=TRUE;
			m_nNumbottomSelect=i;
			break;
		}
	}
	UPDATEWIN 	
	return TRUE;
	
}