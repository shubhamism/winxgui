// MenuSpawn.h: interface for the CMenuSpawn class.
//
//////////////////////////////////////////////////////////////////////
/*
 * <F> CMenuSpawn.h		1.0  23/09/2003
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/


#if !defined(AFX_MENUSPAWN_H__BB6F2F01_91FA_11D1_8B78_0000B43382FE__INCLUDED_)
#define AFX_MENUSPAWN_H__BB6F2F01_91FA_11D1_8B78_0000B43382FE__INCLUDED_

#pragma once


class CMenuSpawn  
{
public:
	struct ToolBarData	
	{ // struct for toolbar resource; guess you already know it ;)
		WORD wVersion;
		WORD wWidth;			
		WORD wHeight;			
		WORD wItemCount;		
	};
	struct SpawnItem
	{
		int		iImageIdx;
		int		iCmd;
		char	cText[128];
		
	};
	struct ImageItem
	{
		int		iImageIdx;
		int		iCmd;
	};

	struct FlotMenu
	{
		int iCmd;
		int Width;
		int iSubMenu;
	};

public:
	bool IsSpawnMenu(CMenu pMenu, const int iItem, const bool bByPos);
	bool GetMenuItemText(LPSTR csText, CMenu * pMenu, const int cmd, bool bByPos);
	void SetBackBitmap(const int iRes, COLORREF crBackColor);
	void SetBackBitmap(const int iRes);
	void SetTextColor(const COLORREF crNormal, const COLORREF crSelected);
	bool FindKeyboardShortcut(UINT nChar, UINT nFlags, HMENU pMenu, LRESULT &lRes);
	bool SetFont(LOGFONT * lf);
	
	HFONT	hMenuFont, hGuiFont;
	CSize szImage;
	bool MeasureItem(LPMEASUREITEMSTRUCT lpm);
	bool DrawItem(LPDRAWITEMSTRUCT lp);
	int FindImageItem(const int cmd);
	SpawnItem * AddSpawnItem(const char * txt, const int cmd);
	void RemapMenu(HMENU pMenu);
	void AddImageItem(const int idx, WORD cmd);

	CImageCtrl ilList;
	CImageCtrl ilOther;

	COLORREF crMenuText, crMenuTextSel;
	COLORREF cr3dFace, crMenu, crHighlight, cr3dHilight, cr3dShadow, crGrayText;
	COLORREF m_clrBtnFace, m_clrBtnHilight, m_clrBtnShadow;

	int iSpawnItem;
	SpawnItem ** pSpawnItem;

	int iImageItem;
	ImageItem * pImageItem;
	FlotMenu  fltMenu;
	bool bIsPopup;
	bool bBackBitmap;
	CBitmap	bmpBack;

	bool LoadToolBarResource(unsigned int resId, UINT uBitmap=-1);
	bool AddToolBarResource(unsigned int resId, UINT uBitmap=-1);
	void EnableMenuItems(CMenu * pMenu, CWin * pParent);
	CMenuSpawn();
	CMenuSpawn(const bool _IsPopup);
	virtual ~CMenuSpawn();

protected:
	void Init();
};

#endif // !defined(AFX_MENUSPAWN_H__BB6F2F01_91FA_11D1_8B78_0000B43382FE__INCLUDED_)
