/*
 * <F> CMenuSpawn.cpp		1.0  23/09/2007
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/

// MenuSpawn.cpp: implementation of the CMenuSpawn class.
//
//////////////////////////////////////////////////////////////////////
//Se modifico el codigo, para corregir bugs y adecuar el software al
//estilo de office 2003
//Modificado por Francisco Campos.
//////////////////////////////////////////////////////////////

#include "stdafx.h"	

#define ID_SEPARATOR -3
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuSpawn::CMenuSpawn()
{
	Init();
}

CMenuSpawn::CMenuSpawn(const bool _IsPopup)
{
	Init();
	bIsPopup = _IsPopup;
}

CMenuSpawn::~CMenuSpawn()
{
	if (iSpawnItem > 0)
	{
		for (int t = 0; t < iSpawnItem; t++)
			if (pSpawnItem[t]) delete pSpawnItem[t];

		GlobalFree((HGLOBAL) pSpawnItem);
	}
	if (iImageItem > 0)
	{
		GlobalFree((HGLOBAL) pImageItem);
	}
	if (hMenuFont) ::DeleteObject((HGDIOBJ)hMenuFont);
	if (hGuiFont) ::DeleteObject((HGDIOBJ)hGuiFont);


}


void CMenuSpawn::Init()
{
	crMenuText = RGB(0,0,0);
	crMenuTextSel = crMenuText;

	cr3dFace = GetSysColor(COLOR_3DFACE);
	crMenu = CDrawLayer::GetRGBSkinMenu();
	crHighlight =CDrawLayer::GetRGBCaptionXP();
	cr3dHilight = GetSysColor(COLOR_3DHILIGHT);
	cr3dShadow = GetSysColor(COLOR_3DSHADOW);
	crGrayText = GetSysColor(COLOR_GRAYTEXT);

	m_clrBtnFace = GetSysColor(COLOR_BTNFACE);
	m_clrBtnHilight = CDrawLayer::GetRGBCaptionXP();
	m_clrBtnShadow = GetSysColor(COLOR_BTNSHADOW);

	iSpawnItem = 0;
	pSpawnItem = NULL;

	iImageItem = 0;
	pImageItem = NULL;

	szImage = CSize(20,20);

	hMenuFont = NULL;
	COLORMAP cMap[3] = { 
		{ RGB(128,128,128), cr3dShadow }, 
		{ RGB(192,192,192), cr3dFace }, 
		{ RGB(255,255,255), cr3dHilight }
	};
	CBitmap bmp;

	ilOther.Create(19, 19, ILC_COLOR4|ILC_MASK, 1, 0);
	ilOther.Add(&bmp, cr3dFace);
	bmp.DeleteObject();

	NONCLIENTMETRICS ncm;
	memset(&ncm, 0, sizeof(ncm));
	ncm.cbSize = sizeof(ncm);

	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, (PVOID) &ncm, 0);

	hGuiFont = ::CreateFontIndirect(&ncm.lfMenuFont);

	bIsPopup = false;
	bBackBitmap = false;
}

bool CMenuSpawn::AddToolBarResource(unsigned int resId, UINT uBitmap)
{
	HRSRC hRsrc = ::FindResource(theApp->GetInstance(), MAKEINTRESOURCE(resId), RT_TOOLBAR);
	if (hRsrc == NULL) return false;

	HGLOBAL hGlb = ::LoadResource(theApp->GetInstance(), hRsrc);
	if (hGlb == NULL) return false;

	ToolBarData* pTBData = (ToolBarData*) ::LockResource(hGlb);
	if (pTBData == NULL) return false;
	
	ASSERT(pTBData->wVersion == 1);

	CBitmap bmp;
	bmp.LoadBitmap(theApp->GetInstance(),(LPCSTR)resId);
	int nBmpItems = ilList.Add(&bmp, RGB(192,192,192));
	bmp.DeleteObject();

	WORD* pItem = (WORD*)(pTBData+1);
	
	for(int i=0; i<pTBData->wItemCount; i++, pItem++)
	{
		if(*pItem != ID_SEPARATOR)
			AddImageItem(nBmpItems++, (WORD) *pItem);
	}
// ** it seem that Windows doesn't free these resource (from Heitor Tome)
    UnlockResource(hGlb);
    FreeResource(hGlb);
// **
	return true;
}


bool CMenuSpawn::LoadToolBarResource(unsigned int resId, UINT uBitmap)
{
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(resId), RT_TOOLBAR);
	if (hRsrc == NULL) return false;

	HGLOBAL hGlb = ::LoadResource(theApp->GetInstance(), hRsrc);
	if (hGlb == NULL) return false;

	ToolBarData* pTBData = (ToolBarData*) ::LockResource(hGlb);
	if (pTBData == NULL) return false;
	
	ASSERT(pTBData->wVersion == 1);

	szImage.cx = (int) pTBData->wWidth;
	szImage.cy = (int) pTBData->wHeight;
	if (uBitmap != -1)
	{
		if(!ilList.CreateColor(uBitmap)) 
			return FALSE;
	}
	else
	{
		if (ilList.Create(szImage.cx, szImage.cy, ILC_COLOR4|ILC_MASK, pTBData->wItemCount, 0) == false)
			return false;
		ilList.SetBkColor(cr3dFace);
		CBitmap bmp;
		bmp.LoadBitmap(theApp->GetInstance(),(LPCSTR)resId);
		ilList.Add(&bmp, RGB(192,192,192));
		bmp.DeleteObject();

	}

	
	WORD* pItem = (WORD*)(pTBData+1);
	int nBmpItems = 0;
	for(int i=0; i<pTBData->wItemCount; i++, pItem++)
	{
		if(*pItem != ID_SEPARATOR)
			AddImageItem(nBmpItems++, (WORD) *pItem);
	}
// ** it seem that Windows doesn't free these resource (from Heitor Tome)
    UnlockResource(hGlb);
    FreeResource(hGlb);
// **
	return true;
}

void CMenuSpawn::AddImageItem(const int idx, WORD cmd)
{
	if (iImageItem == 0)
		pImageItem = (ImageItem *) GlobalAlloc(GPTR, sizeof(ImageItem));
	else
		pImageItem = (ImageItem *) GlobalReAlloc((HGLOBAL) pImageItem, sizeof(ImageItem) * (iImageItem + 1), GMEM_MOVEABLE|GMEM_ZEROINIT);
	
	ASSERT(pImageItem);
	pImageItem[iImageItem].iCmd = (int) cmd;
	pImageItem[iImageItem].iImageIdx = idx;
	iImageItem ++;
}


void CMenuSpawn::RemapMenu(HMENU hMenu)
{
	static int iRecurse = 0;
	iRecurse ++;

	CMenu pMenu;
	pMenu.Attach(hMenu);
	
	ASSERT(pMenu);
	int nItem = pMenu.GetMenuItemCount();
	while ((--nItem)>=0)
	{
		UINT itemId = pMenu.GetMenuItemID(nItem);
		if (itemId == (UINT) -1)
		{
			CMenu pops(pMenu.GetSubMenu(nItem));
			if (pops.GetHandleMenu()) RemapMenu(pops.GetHandleMenu());
			if (bIsPopup || iRecurse > 0)
			{
				TCHAR cs[128];
				memset(cs,0x00,128);
				pMenu.GetMenuString(nItem, cs, 128,MF_BYPOSITION);
				if (lstrlen(cs)>0)
				{
					SpawnItem * sp = AddSpawnItem(cs, (!bIsPopup && iRecurse == 1) ? -4 : -2);
					pMenu.ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW, (UINT) -1, (LPCTSTR)sp);
				}
			}
		}
		else
		{
			if (itemId != 0)
			{
				UINT oldState = pMenu.GetMenuState(nItem,MF_BYPOSITION);
				if (!(oldState&MF_OWNERDRAW) && !(oldState&MF_BITMAP))
				{
					ASSERT(oldState != (UINT)-1);
					TCHAR cs[128];
					memset(cs,0x00,128);
					pMenu.GetMenuString(nItem, cs, 128, MF_BYPOSITION);
					SpawnItem * sp = AddSpawnItem(cs, itemId);
					if (itemId!=SC_CLOSE)
					pMenu.ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW|oldState, (LPARAM)itemId, (LPCTSTR)sp);
				}
			}
			else
			{
				UINT oldState = pMenu.GetMenuState(nItem,MF_BYPOSITION);
				if (!(oldState&MF_OWNERDRAW) && !(oldState&MF_BITMAP))
				{
					ASSERT(oldState != (UINT)-1);
					SpawnItem * sp = AddSpawnItem("--", -3);
					pMenu.ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW|oldState, (LPARAM)itemId, (LPCTSTR)sp);
				}
			}
		}
	}
	iRecurse --;
	pMenu.Detach();
}

CMenuSpawn::SpawnItem * CMenuSpawn::AddSpawnItem(const char * txt, const int cmd)
{
	if (iSpawnItem == 0)
		pSpawnItem = (SpawnItem **) GlobalAlloc(GPTR, sizeof(SpawnItem));
	else
		pSpawnItem = (SpawnItem **) GlobalReAlloc((HGLOBAL) pSpawnItem, sizeof(SpawnItem) * (iSpawnItem + 1), GMEM_MOVEABLE|GMEM_ZEROINIT);

	ASSERT(pSpawnItem)

	SpawnItem * p = new SpawnItem;
	ASSERT(p);
	pSpawnItem[iSpawnItem] = p;
	lstrcpy(p->cText, txt);
	p->iCmd = cmd;

	if (cmd >= 0) p->iImageIdx = FindImageItem(cmd);
	else p->iImageIdx = cmd;

	iSpawnItem ++;
	return p;
}

int CMenuSpawn::FindImageItem(const int cmd)
{
	for (int t = 0; t < iImageItem; t++)
		if (pImageItem[t].iCmd == cmd) return pImageItem[t].iImageIdx;

	return -1;
}

bool CMenuSpawn::DrawItem(LPDRAWITEMSTRUCT lp)
{
	bool res = false;
	//pDC1.Draw3dRect(rcClient,CDrawLayer::GetRGBColorFace(),CDrawLayer::GetRGBColorShadow());
	if (lp->CtlType == ODT_MENU)
	{
		UINT id = lp->itemID;
		UINT state = lp->itemState;
		bool bEnab = !(state & ODS_DISABLED);
		bool bSelect = (state & ODS_SELECTED) ? true : false;
		bool bChecked = (state & ODS_CHECKED) ? true : false;
		bool bHotLight =(state & ODS_HOTLIGHT) ? true : false;
		CGDI  pDC(lp->hDC);
		SpawnItem * pItem = (SpawnItem *) lp->itemData;
		if (pItem)
		{
			CFont  pft=((HFONT) hMenuFont ? hMenuFont : hGuiFont);
			CFont  of=(pDC.SelectObject(pft));
			CRect rc=lp->rcItem;
			CRect rcImage(rc), rcText(rc);
			rcImage.right = rcImage.left + rc.Height();
			rcImage.bottom = rc.bottom;

			CBrush brush;
			brush.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
			
			CRect rcImg=rcImage;
			rcImg.right+=1;
			pDC.FillRect(rcImg,&brush);
			if (pItem->iCmd != -4)
			{
				CGradient M(CSize(rcImg.Width(),rcImg.Height()));	
				M.PrepareHorizontal(&pDC,CDrawLayer::GetRGBColorWhite(),CDrawLayer::GetRGBColorFace());
				M.Draw(&pDC,rcImg.left,rcImg.top,0,0,rcImg.Width()+2,rcImg.Height(),SRCCOPY);	
			}
			if (bBackBitmap) 
			{
				CGDI tempDC;
				tempDC.CreateCompatibleDC(pDC);
				tempDC.FillSolidRect(rcText, crMenu);
				CBitmap  ob = tempDC.SelectObject(&bmpBack);
				pDC.FillSolidRect(rcText, crMenu);
				pDC.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), tempDC, rc.left, rc.top, SRCCOPY );
			}
			int obk = pDC.SetBkMode(TRANSPARENT);
			if (pItem->iCmd == -3) // is a separator
			{
				CBrush brush;
				CRect m_rc=rc;
				brush.CreateSolidBrush(CDrawLayer::GetRGBSkinMenu());
				rc.left+=rcImage.Width()+15;
				pDC.FillRect(rc,&brush);
				rc.top += rc.Height()>>1;	
				rc.left+= 5;
				brush.DeleteObject();
				pDC.DrawEdge(rc, EDGE_ETCHED, BF_TOP);	
				rcImg.right= rc.left-4;
				CGradient M(CSize(rcImg.Width(),rcImg.Height()));	
				M.PrepareHorizontal(&pDC);
				M.Draw(&pDC,rcImg.left,rcImg.top,0,0,rcImg.Width()-1,rcImg.Height(),SRCCOPY);	
				fltMenu.iCmd=-1;
		
			}
			else if (pItem->iCmd == -4) // is a title item
			{
				//CString cs(pItem->cText), cs1;
				CRect rcBdr(rcText);
				
				if (pItem->iCmd == -4) 
				{
					fltMenu.iCmd=-4;
					fltMenu.Width=rcText.Width();
					
				}
				if (bSelect && bEnab)
				{
					CPen Dark; 
					Dark.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW));
					rcText.top+=1;
					rcText.bottom+=1;
					CGradient M(CSize(rcText.Width(),rcText.Height()));	
					M.PrepareVertical(&pDC);
					M.Draw(&pDC,rcText.left+1,rcText.top+1,0,0,rcText.Width()-1,rcText.Height()-1,SRCCOPY);	
					rcText.bottom-=1;
					CPen oldPen= pDC.SelectObject(&Dark);
					pDC.MoveTo(rcText.left,rcText.bottom-1);
					pDC.LineTo(rcText.left,rcText.top);
					
					pDC.MoveTo(rcText.left,rcText.top);
					pDC.LineTo(rcText.right-1,rcText.top);

					pDC.MoveTo(rcText.right-1,rcText.top);
					pDC.LineTo(rcText.right-1,rcText.bottom);
					
					CBrush cb;
					cb.CreateSolidBrush(CDrawLayer::GetRGBSkinMenu());
					//rc.top+=1;
					rcText.DeflateRect(1,1);
					rcText.bottom+=1;
					pDC.FillRect(&rcText,&cb);
					//pDC.Draw3dRect(rcText,CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
					rcText.top-=1;
					pDC.SelectObject(&oldPen);
					Dark.DeleteObject();
				}
				else if (bHotLight && bEnab) 
				{
					rcText.top+=1;
					pDC.FillSolidRect(rcText, CDrawLayer::GetRGBFondoXP());
					pDC.Draw3dRect(rcText,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
					rcText.top-=1;
					fltMenu.iCmd=-1;fltMenu.Width=-1;
						

				}
				else
					pDC.FillRect(rcText,&brush);
			
				pDC.DrawText(pItem->cText, rcText, DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				
			}
			else
			{
				rcText.left += rcImage.right + 1;
				COLORREF ocr;
				if (bSelect)
				{
					if (pItem->iImageIdx >= 0 || (state & ODS_CHECKED))
						pDC.FillSolidRect(rc, CDrawLayer::GetRGBFondoXP());
					else
						pDC.FillSolidRect(rc, CDrawLayer::GetRGBFondoXP());
					pDC.Draw3dRect(rc,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
					ocr = pDC.SetTextColor(crMenuTextSel);
				}
				else
				{
					if (!bBackBitmap) 
					{
						if (pItem->iImageIdx >= 0 || (state & ODS_CHECKED))
							pDC.FillSolidRect(rcText, crMenu);
						else
							pDC.FillSolidRect(rcText/*rcText*/, crMenu);
					}
					ocr = pDC.SetTextColor(crMenuText);
				}

				if (pItem->iImageIdx >= 0)
				{
					int ay = (rcImage.Height() - szImage.cy) / 2;
					int ax = (rcImage.Width()  - szImage.cx) / 2;

					if (bEnab)
					{
						if (bSelect)
						{
							HICON hIcon = ilList.ExtractIcon( pItem->iImageIdx );
							CPoint p=CPoint(rcImage.left + ax, rcImage.top + ay );
							ilList.Draw(pItem->iImageIdx,pDC,p,ILD_TRANSPARENT);
							::DestroyIcon(hIcon);
						}

						else
							ilList.Draw( pItem->iImageIdx,pDC, CPoint(rcImage.left + ax, rcImage.top +ay), ILD_TRANSPARENT);
					}
					else
					{
						HICON hIcon = ilList.ExtractIcon( pItem->iImageIdx );
						
						pDC.DrawState( CPoint(rcImage.left + ax, rcImage.top + ay ), szImage, (HICON)hIcon, DST_ICON | DSS_DISABLED,(HBRUSH) NULL );
						::DestroyIcon(hIcon);
					}
				}
				else
				{
					if (bChecked)
					{
						int ay = (rcImage.Height() - szImage.cy) / 2;
						int ax = (rcImage.Width()  - szImage.cx) / 2;

						ilOther.Draw( 0, pDC.m_hDC,CPoint(rcImage.left + ax, rcImage.top + ay - 2), ILD_NORMAL);
					}
				}

				char BufferLeft[128];
				char BufferRight[128];
				//BufferLeft[0]=0;
				//BufferRight[0]=0;
				SIZE sz;
				pDC.GetTextExtent(pItem->cText,lstrlen(pItem->cText),&sz);
				int ay1 = (rcText.Height() - sz.cy) / 2;
				rcText.top += ay1;
				rcText.left += 2;
				rcText.right -= 15;
				rcText.left+=4;
				int tf = CDrawLayer::SWCFindChar(pItem->cText,'\t');
				if (tf >= 0)
				{
					
					CDrawLayer::SWCCopyRight(pItem->cText, tf+1,BufferRight);
					CDrawLayer::SWCCopyLeft(pItem->cText, tf+1,BufferLeft);
					if (!bEnab)
					{
						if (!bSelect)
						{
							CRect rcText1(rcText);
							pDC.SetTextColor(cr3dHilight);
							pDC.DrawText(BufferLeft, rcText1, DT_VCENTER|DT_LEFT);
							pDC.DrawText(BufferRight, rcText1, DT_VCENTER|DT_RIGHT);
							pDC.SetTextColor(crGrayText);
							pDC.DrawText(BufferLeft, rcText, DT_VCENTER|DT_LEFT);
							pDC.DrawText(BufferRight, rcText, DT_VCENTER|DT_RIGHT);
						}
						else
						{
							pDC.SetTextColor(crMenu);
							pDC.DrawText(BufferLeft, rcText, DT_VCENTER|DT_LEFT);
							pDC.DrawText(BufferRight, rcText, DT_VCENTER|DT_RIGHT);
						}
					}
					else
					{
						pDC.DrawText(BufferLeft, rcText, DT_VCENTER|DT_LEFT);
						pDC.DrawText(BufferRight, rcText, DT_VCENTER|DT_RIGHT);
					}
				}
				else 
				{
					if (!bEnab)
					{
						
						if (!bSelect)
						{
							CRect rcText1(rcText);
							rcText1.InflateRect(-1,-1);
							pDC.SetTextColor(cr3dHilight);
							pDC.DrawText(pItem->cText, rcText1, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
							pDC.SetTextColor(crGrayText);
							pDC.DrawText(pItem->cText, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
						}
						else
						{
							pDC.SetTextColor(crMenu);
							pDC.DrawText(pItem->cText, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
						}
					}
					else
						pDC.DrawText(pItem->cText, rcText, DT_VCENTER|DT_LEFT|DT_EXPANDTABS);
				}
				pDC.SetTextColor(ocr);
				pDC.SetBkMode(obk);
			}

			pDC.SelectObject(of);
		}
		res = true;
		
	
	}
	return res;
}

bool CMenuSpawn::MeasureItem(LPMEASUREITEMSTRUCT lpm)
{
	bool res = false;
	if (lpm->CtlType == ODT_MENU)
	{
		UINT id = lpm->itemID;

		SpawnItem * pItem = (SpawnItem *) lpm->itemData;
		if (pItem)
		{
			if (pItem->iCmd == -3) // is a separator
			{
				lpm->itemWidth  = 10;
				lpm->itemHeight = 6;
			}
			else
			{
				if (_tcslen(pItem->cText) > 0)
				{
					CClientDC dc(theApp->GetMainWindows());
					CFont  pft = hMenuFont ? hMenuFont : hGuiFont;
					CFont  of = dc.SelectObject(pft);
					CSize osz= dc.GetTextExtent(pItem->cText,_tcslen(pItem->cText));
				//	CSize osz(LOWORD(dSize), HIWORD(dSize) );
					if (pItem->iCmd == -4)
					{
						CRect rci(0,0,0,0);
						
						dc.DrawText(pItem->cText, rci, DT_CALCRECT|DT_TOP|DT_VCENTER|DT_SINGLELINE);
						lpm->itemHeight = rci.Height();
						lpm->itemWidth = rci.Width();
					}
					else
					{
						lpm->itemHeight = szImage.cy + 5;
						if (osz.cy > (int) lpm->itemHeight) lpm->itemHeight = (int) osz.cy;
						lpm->itemWidth  = osz.cx + 2 + 15;
						lpm->itemWidth += lpm->itemHeight > (UINT) szImage.cx ? (UINT) lpm->itemHeight : (UINT) szImage.cx;
					}
					dc.SelectObject(of);
				}
				else
				{
					lpm->itemHeight = szImage.cy + 5;
					lpm->itemWidth  = 100;
				}
			}
		}
		res = true;
	}
	return res;
}

void CMenuSpawn::EnableMenuItems(CMenu * pMenu, CWin * pParent)
{
/*	ASSERT(pMenu);
	ASSERT(pParent);

	int nItem = pMenu->GetMenuItemCount();
	CCmdUI state;
	state.m_pMenu = pMenu;
	state.m_nIndex = nItem-1;
	state.m_nIndexMax = nItem;

	while ((--nItem)>=0)
	{
		UINT itemId = pMenu->GetMenuItemID(nItem);
		if (itemId == (UINT) -1)
		{
			CMenu pops = pMenu->GetSubMenu(nItem);
			if (pops) EnableMenuItems(&pops, pParent);
		}
		else
		{
			if (itemId != 0)
			{
				state.m_nID = itemId;
				pParent->OnCmdMsg(itemId, CN_UPDATE_COMMAND_UI, &state, NULL);
				state.DoUpdate(pParent, true);
			}
		}
		state.m_nIndex = nItem-1;
	}*/
}


bool CMenuSpawn::SetFont(LOGFONT * lf)
{
	ASSERT(lf);
	if (hMenuFont) ::DeleteObject((HGDIOBJ)hMenuFont);
	hMenuFont = CreateFontIndirect(lf);
	return hMenuFont != NULL ? true : false;
}

bool CMenuSpawn::FindKeyboardShortcut(UINT nChar, UINT nFlags, HMENU hMenu , LRESULT & lRes)
{
	CMenu* pMenu=(CMenu*)hMenu;
	ASSERT(pMenu);
	int nItem = pMenu->GetMenuItemCount();
	CString csChar((CHAR) nChar);
	csChar.MakeLower();
	while ((--nItem)>=0)
	{
		UINT itemId = pMenu->GetMenuItemID(nItem);
		if (itemId != 0)
		{
			MENUITEMINFO lpmi;
			ZeroMemory(&lpmi, sizeof(MENUITEMINFO));
			lpmi.cbSize = sizeof(MENUITEMINFO);
			lpmi.fMask = MIIM_DATA|MIIM_TYPE;
			ASSERT(pMenu->GetSafeHmenu());
			if (GetMenuItemInfo(pMenu->GetHandleMenu(), nItem, TRUE, &lpmi))
			{
				if (lpmi.fType&MFT_OWNERDRAW)
				{
					SpawnItem * si = (SpawnItem *) lpmi.dwItemData;
					if (si)
					{
						CString csItem(si->cText);
						csItem.MakeLower();
						int iAmperIdx = csItem.Find('&');
						if (iAmperIdx >= 0)
						{
							csItem = csItem.Mid(iAmperIdx + 1, 1);
							if (csItem == csChar)
							{
								lRes = MAKELONG((WORD)nItem, 2);
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void CMenuSpawn::SetTextColor(const COLORREF crNormal, const COLORREF crSelected)
{
	crMenuText = crNormal;
	crMenuTextSel = crSelected;
}

void CMenuSpawn::SetBackBitmap(const int iRes)
{
	if (bmpBack.GetSafeHandle()) bmpBack.DeleteObject();
	bmpBack.LoadBitmap(theApp->GetInstance(),(LPSTR)iRes);
	bBackBitmap = true;
}

void CMenuSpawn::SetBackBitmap(const int iRes, COLORREF crBackColor)
{
	if (bmpBack.GetSafeHandle()) bmpBack.DeleteObject();
	COLORMAP cMap1 = { crBackColor, cr3dFace };

	bBackBitmap = true;
}

bool CMenuSpawn::GetMenuItemText(LPSTR csText, CMenu * pMenu, const int cmd, bool bByPos)
{
	ASSERT(pMenu);

	UINT itemId = bByPos ? pMenu->GetMenuItemID(cmd) : cmd;
	if (itemId != 0)
	{
		MENUITEMINFO lpmi;
		ZeroMemory(&lpmi, sizeof(MENUITEMINFO));
		lpmi.cbSize = sizeof(MENUITEMINFO);
		lpmi.fMask = MIIM_DATA|MIIM_TYPE;
		ASSERT(pMenu->GetSafeHmenu());
		if (GetMenuItemInfo(pMenu->GetHandleMenu(), cmd, bByPos, &lpmi))
		{
			if (lpmi.fType&MFT_OWNERDRAW)
			{
				SpawnItem * si = (SpawnItem *) lpmi.dwItemData;
				if (si)
				{
					csText = si->cText;
					return true;
				}
			}
			else
			{
				return pMenu->GetMenuString(cmd, csText, 128, bByPos ? MF_BYPOSITION : MF_BYCOMMAND) > 0;
			}
		}
	}
	return false;
}

bool CMenuSpawn::IsSpawnMenu(CMenu pMenu, const int iItem, const bool bByPos)
{
	ASSERT(pMenu);

	UINT itemId = bByPos ? pMenu.GetMenuItemID(iItem) : iItem;
	if (itemId != 0)
	{
		MENUITEMINFO lpmi;
		ZeroMemory(&lpmi, sizeof(MENUITEMINFO));
		lpmi.cbSize = sizeof(MENUITEMINFO);
		lpmi.fMask = MIIM_DATA|MIIM_TYPE;
		ASSERT(pMenu);
		if (GetMenuItemInfo(pMenu.GetHandleMenu(), iItem, bByPos, &lpmi))
		{
			if (lpmi.fType&MFT_OWNERDRAW)
			{
				SpawnItem * si = (SpawnItem *) lpmi.dwItemData;
				if (si) return true;
			}
		}
	}
	return false;
}
