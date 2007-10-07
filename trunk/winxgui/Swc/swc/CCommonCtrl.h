/*
 * CCommonCtrl.h	1.0  23/09/2003
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * this is a simple wrapper of comctl32 see the commctrl.h
 * BEYONDATA  PROPRIETARY. Use is subject to license terms.
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/

#if !defined(C_COMMONCTRL_H__191265517913803_INCLUDED_)
#define C_COMMONCTRL_H__191265517913803_INCLUDED_

/*
 *  A Commont event for COMCTL32 Controls
 *
 **/

class CComboBoxExt;

class ComControl: public CWin
{

public:
	
	ComControl(){}
	virtual ~ComControl()	{}
public:
	
	virtual BOOL OnChar(	LPNMCHAR pChar, BOOL &bNotify) {return FALSE; }
	virtual BOOL OnClick( LPNMHDR pNMHDR, BOOL &bNotify){return FALSE;}
	virtual BOOL OnCustomDraw( LPNMCUSTOMDRAW pCustomDraw, BOOL &bNotify)	{ return CDRF_DODEFAULT; }
	virtual BOOL OnDblclk( LPNMHDR pNMHDR, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnHover( LPNMHDR pNMHDR, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnKeydown( LPNMKEY pKey, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnKillFocus( LPNMHDR pNMHDR, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnNCHitTest( LPNMMOUSE pMouse, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnOutOfMemory( LPNMHDR pNMHDR, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnRClick( LPNMHDR pNMHDR, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnRDblclk( LPNMHDR pNMHDR, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnReleasedCapture( LPNMHDR pNMHDR, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnReturn( LPNMHDR pNMHDR, BOOL &bNotify){ return FALSE;}
	virtual BOOL OnSetCursor( LPNMMOUSE pMouse, BOOL &bNotify){ return FALSE; }
	virtual BOOL OnSetFocus( LPNMHDR pNMHDR, BOOL &bNotify)	{ return FALSE;}
//	virtual BOOL OnToolTipsCreated( LPNMTOOLTIPSCREATED pToolTipsCreated){ return FALSE;}
	
	virtual LRESULT ReflectChildNotify( LPNMHDR pNMHDR, BOOL &bNotify)
	{
		switch ( pNMHDR->code )
		{
			case	NM_CHAR:	    
				return OnChar(( LPNMCHAR )pNMHDR , bNotify);
			case	NM_CLICK:	    
				return OnClick( pNMHDR ,  bNotify);
			case	NM_CUSTOMDRAW:	    
				return OnCustomDraw( (LPNMCUSTOMDRAW) pNMHDR, bNotify);
			case	NM_DBLCLK:	    
				return OnDblclk( pNMHDR , bNotify);
			case	NM_HOVER:	    
				return OnHover( pNMHDR , bNotify);
			case	NM_KEYDOWN:	    
				return OnKeydown(( LPNMKEY )pNMHDR , bNotify);
			case	NM_KILLFOCUS:	    
				return OnKillFocus( pNMHDR ,  bNotify);
			case	NM_NCHITTEST:	    
				return OnNCHitTest(( LPNMMOUSE )pNMHDR , bNotify);
			case	NM_OUTOFMEMORY:    
				return OnOutOfMemory( pNMHDR ,bNotify);
			case	NM_RCLICK:	    
				return OnRClick( pNMHDR ,bNotify);
			case	NM_RDBLCLK:	    
				return OnRDblclk( pNMHDR , bNotify);
			case	NM_RELEASEDCAPTURE: 
				return OnReleasedCapture( pNMHDR ,  bNotify);
			case	NM_RETURN:	    
				return OnReturn( pNMHDR , bNotify);
			case	NM_SETCURSOR:	    
				return OnSetCursor(( LPNMMOUSE )pNMHDR ,  bNotify);
			case	NM_SETFOCUS:	    
				return OnSetFocus( pNMHDR , bNotify);
//			case	NM_TOOLTIPSCREATED: 
//				return OnToolTipsCreated(( LPNMTOOLTIPSCREATED )pNMHDR );
		}
		return FALSE;
	}
};




class ComControlEX: public ComControl
{
	
	public:
		ComControlEX(){};
		~ComControlEX(){};
	
	public:
		
	virtual DWORD OnPrePaint( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}
	virtual DWORD OnPostPaint( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}
	virtual DWORD OnPreErase( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}
	virtual DWORD OnPostErase( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}
	virtual DWORD OnItemPrePaint( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}
	virtual DWORD OnItemPostPaint( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}
	virtual DWORD OnItemPreErase( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}
	virtual DWORD OnItemPostErase( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}

	virtual DWORD OnSubItemPrePaint( LPNMCUSTOMDRAW , BOOL &bNotify)
	{
		return CDRF_DODEFAULT;
	}
	
	
	virtual LRESULT ReflectChildNotify( LPNMHDR pNMHDR, BOOL &bNotify)
	{
		if (pNMHDR->code == NM_CUSTOMDRAW)
		{	
      			LPNMCUSTOMDRAW lpNMCustomDraw = (LPNMCUSTOMDRAW)pNMHDR;
			switch(lpNMCustomDraw->dwDrawStage)
			{
			case CDDS_PREPAINT:
				return OnPrePaint(lpNMCustomDraw, bNotify);
				break;
			case CDDS_POSTPAINT:
				return OnPostPaint(lpNMCustomDraw, bNotify);
				break;
			case CDDS_PREERASE:
				return OnPreErase(lpNMCustomDraw,bNotify);
				break;
			case CDDS_POSTERASE:
				return OnPostErase(lpNMCustomDraw, bNotify);
				break;
			case CDDS_ITEMPREPAINT:
				return OnItemPrePaint(lpNMCustomDraw,  bNotify);
				break;
			case CDDS_ITEMPOSTPAINT:
				return OnItemPostPaint(lpNMCustomDraw, bNotify);
				break;
			case CDDS_ITEMPREERASE:
				return OnItemPreErase(lpNMCustomDraw,  bNotify);
				break;
			case CDDS_ITEMPOSTERASE:
				return OnItemPostErase(lpNMCustomDraw,  bNotify);
				break;
			#if (_WIN32_IE >= 0x0400)
			case (CDDS_ITEMPREPAINT | CDDS_SUBITEM):
				return OnSubItemPrePaint(lpNMCustomDraw,bNotify);
				break;
			#endif 
			}
		}
	else	
		return ComControl::ReflectChildNotify(pNMHDR, bNotify);
	return TRUE;
	}
	

};	


/*
 *  CToolTipCtrl
 *
 **/

class CToolTipCtrl : public ComControlEX
{
public:
	CToolTipCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}
	~CToolTipCtrl(){};
public:
	BOOL Create(HWND hWndParent,UINT uID=BASE_TOOLTIPS_CLASS)
	{		
		BOOL bRes = CreateEx(0L, TOOLTIPS_CLASS, NULL,
						0L,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}


	void GetText(LPTOOLINFO lpToolInfo) 
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_GETTEXT, 0L, (LPARAM)&lpToolInfo);
	}
	

	BOOL GetToolInfo(LPTOOLINFO lpToolInfo) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TTM_GETTOOLINFO, 0L, (LPARAM)lpToolInfo);
	}
	
	void SetToolInfo(LPTOOLINFO lpToolInfo)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_SETTOOLINFO, 0L, (LPARAM)lpToolInfo);
	}
	void SetToolRect(LPTOOLINFO lpToolInfo)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_NEWTOOLRECT, 0L, (LPARAM)lpToolInfo);
	}
	

	BOOL SetToolRect(HWND hWnd, LPCRECT lpRect, UINT uID )
	{
		
		TOOLINFO tti;
		ASSERT(m_hWnd);
		ASSERT(lpszText != NULL);
		
		memset(&tti,0x00,sizeof(TOOLINFO));
		tti.cbSize=sizeof(TOOLINFO);
		tti.hwnd=hWnd;
		tti.uFlags=0;
		tti.uId=uID;
		tti.lpszText = (LPTSTR)NULL;
		if (lpRect != NULL)
			memcpy(&tti.rect, lpRect, sizeof(RECT));
		return (BOOL) ::SendMessage(m_hWnd, TTM_NEWTOOLRECT, 0, (LPARAM)&tti);

	}


	int GetToolCount() 
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (int)SendMessage( TTM_GETTOOLCOUNT, 0L, 0L);
	}
	
	int GetDelayTime(DWORD dwType) 
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (int)SendMessage( TTM_GETDELAYTIME, dwType, 0L);
	}
	
	void SetDelayTime(DWORD dwType, int nTime)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_SETDELAYTIME, dwType, MAKELPARAM(nTime, 0));
	}
	void GetMargin(LPRECT lpRect) 
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_GETMARGIN, 0L, (LPARAM)lpRect);
	}
	void SetMargin(LPRECT lpRect)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_SETMARGIN, 0L, (LPARAM)lpRect);
	}
	int GetMaxTipWidth() 
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (int)SendMessage( TTM_GETMAXTIPWIDTH, 0L, 0L);
	}
	int SetMaxTipWidth(int nWidth)
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (int)SendMessage( TTM_SETMAXTIPWIDTH, 0L, nWidth);
	}
	COLORREF GetTipBkColor() 
	{
		if (!::IsWindow(m_hWnd)) return RGB(0L,0L,0);
		return (COLORREF)SendMessage( TTM_GETTIPBKCOLOR, 0L, 0L);
	}

	void SetTipBkColor(COLORREF clr)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_SETTIPBKCOLOR, (WPARAM)clr, 0L);
	}

	COLORREF GetTipTextColor() 
	{
		if (!::IsWindow(m_hWnd)) return RGB(0L,0L,0);
		return (COLORREF)SendMessage( TTM_GETTIPTEXTCOLOR, 0L, 0L);
	}

	void SetTipTextColor(COLORREF clr)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_SETTIPTEXTCOLOR, (WPARAM)clr, 0L);
	}
	
	BOOL GetCurrentTool(LPTOOLINFO lpToolInfo) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TTM_GETCURRENTTOOL, 0L, (LPARAM)lpToolInfo);
	}



	void Activate(BOOL bActivate)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_ACTIVATE, bActivate, 0L);
	}

	BOOL AddTool(HWND hWnd, LPCTSTR lpTxt, LPCRECT lpRect,UINT uID)
	{
		TOOLINFO tti;
		ASSERT(m_hWnd);
		ASSERT(lpszText != NULL);
		
		memset(&tti,0x00,sizeof(TOOLINFO));
		tti.cbSize=sizeof(TOOLINFO);
		tti.hwnd=hWnd;
		tti.uFlags=0;
		tti.uId=uID;
		tti.lpszText = (LPTSTR)lpTxt;
		if (lpRect != NULL)
			memcpy(&tti.rect, lpRect, sizeof(RECT));
		return (BOOL) ::SendMessage(m_hWnd, TTM_ADDTOOL, 0, (LPARAM)&tti);
	}

	BOOL AddTool(LPTOOLINFO lpToolInfo)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TTM_ADDTOOL, 0L, (LPARAM)lpToolInfo);
	}
	
	

	BOOL UpdateTipText(HWND hWnd, LPTSTR lpText= LPSTR_TEXTCALLBACK, LPCRECT lpRect = NULL, UINT nID = 0)
	{
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(hWnd != NULL);
		
		TOOLINFO ti;
		
		memset(&ti, 0x00, sizeof(TOOLINFO));
		ti.cbSize = sizeof(TOOLINFO);
		//Why the follow instructions?, well it is count for 1 not 0
		if(nID == 0)
		{
			ti.hwnd = hWnd;
			ti.uFlags |= TTF_IDISHWND;
			ti.uId = (UINT_PTR)hWnd;
		}
		else
		{
			ti.hwnd = hWnd;
			ti.uId = nID;
		}
		if(lpRect != NULL)
			ti.rect = *lpRect;
		ti.lpszText = lpText;

		return (BOOL )::SendMessage(m_hWnd, TTM_UPDATETIPTEXT, 0,(LPARAM)&ti);
	}

	BOOL AddTool(HWND hWnd, LPTSTR lpText = LPSTR_TEXTCALLBACK, LPCRECT lpRect = NULL, UINT nID = 0)
	{
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(hWnd != NULL);
		
		TOOLINFO ti;
		
		memset(&ti, 0x00, sizeof(TOOLINFO));
		ti.cbSize = sizeof(TOOLINFO);
		
		if(nID == 0)
		{
			ti.hwnd = ::GetParent(hWnd);
			ti.uFlags |= TTF_IDISHWND;
			ti.uId = (UINT_PTR)hWnd;
		}
		else
		{
			ti.hwnd = hWnd;
			ti.uId = nID;
		}
		if(lpRect != NULL)
			ti.rect = *lpRect;
		ti.hinst = theApp->GetInstance();
		ti.lpszText = lpText;
		ti.lParam = NULL;
		return (BOOL)::SendMessage(m_hWnd, TTM_ADDTOOL, 0,(LPARAM)&ti);
	}


	void DelTool(LPTOOLINFO lpToolInfo)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_DELTOOL, 0L, (LPARAM)lpToolInfo);
	}
	
	BOOL HitTest(LPTTHITTESTINFO lpHitTestInfo) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TTM_HITTEST, 0L, (LPARAM)lpHitTestInfo);
	}
	
	void RelayEvent(LPMSG lpMsg)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_RELAYEVENT, 0L, (LPARAM)lpMsg);
	}
	void UpdateTipText(LPTOOLINFO lpToolInfo)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_UPDATETIPTEXT, 0L, (LPARAM)lpToolInfo);
	}
	

	BOOL EnumTools(UINT nTool, LPTOOLINFO lpToolInfo) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TTM_ENUMTOOLS, nTool, (LPARAM)lpToolInfo);
	}
	void Pop()
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_POP, 0L, 0L);
	}
	void TrackActivate(LPTOOLINFO lpToolInfo, BOOL bActivate)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_TRACKACTIVATE, bActivate, (LPARAM)lpToolInfo);
	}
	void TrackPosition(int xPos, int yPos)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_TRACKPOSITION, 0L, MAKELPARAM(xPos, yPos));
	}


#if (_WIN32_IE >= 0x0400)
	void Update()
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_UPDATE, 0L, 0L);
	}
#endif //(_WIN32_IE >= 0x0400)

#if (_WIN32_IE >= 0x0500)
	BOOL AdjustRect(LPRECT lpRect, BOOL bLarger= TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TTM_ADJUSTRECT, bLarger, (LPARAM)lpRect);
	}
	DWORD GetBubbleSize(LPTOOLINFO lpToolInfo) 
	{
		if (!::IsWindow(m_hWnd)) return 0;
		return (DWORD)SendMessage( TTM_GETBUBBLESIZE, 0L, (LPARAM)lpToolInfo);
		
	}
	BOOL SetTitle(UINT uIcon, LPCTSTR lpstrTitle)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TTM_SETTITLE, uIcon, (LPARAM)lpstrTitle);
	}
#endif //(_WIN32_IE >= 0x0500)

#if (_WIN32_WINNT >= 0x0501)
	void Popup()
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_POPUP, 0L, 0L);
	}

	void GetTitle(PTTGETTITLE pTTGetTitle) 
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_GETTITLE, 0L, (LPARAM)pTTGetTitle);
	}
	void SetWindowTheme(LPCWSTR lpstrTheme)
	{
		ASSERT(m_hWnd);
		SendMessage( TTM_SETWINDOWTHEME, 0L, (LPARAM)lpstrTheme);
	}

#endif //(_WIN32_WINNT >= 0x0501)

	
};



/*
 *  CImageCtrl
 *
 **/



class CImageCtrl
{
	HIMAGELIST m_hImageList;
public:
	CImageCtrl(HIMAGELIST hImageList=NULL){ m_hImageList=hImageList;};
	~CImageCtrl(){ Destroy();};
public:

	operator HIMAGELIST() {return m_hImageList;}
	
	BOOL Create(int cx, int cy, UINT flags, int cInitial, int cGrow)
	{
		if (m_hImageList != NULL) return FALSE;
		m_hImageList=ImageList_Create(cx,cy, flags,cInitial, cGrow);
		if (m_hImageList== NULL)
			return FALSE;
		return TRUE;
	}

	BOOL CreateColor(UINT uTb, int nBtnIni=-1) 
	{
		
		BITMAP		bmp;
		HGDIOBJ hBmp=::LoadImage(theApp->GetInstance(),MAKEINTRESOURCE(uTb),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		::GetObject(hBmp, sizeof(BITMAP), &bmp);
		RGBTRIPLE *pRbg= (RGBTRIPLE*) (bmp.bmBits);
		if (nBtnIni == -1)
			nBtnIni=bmp.bmWidth/bmp.bmBitsPixel;
		WORD cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 

		if (cClrBits == 1) 
			cClrBits = 1; 
		else if (cClrBits <= 4) 
			cClrBits = ILC_COLOR4; 
		else if (cClrBits <= 8) 
			cClrBits = ILC_COLOR8; 
		else if (cClrBits <= 16) 
			cClrBits = ILC_COLOR16; 
		else if (cClrBits <= 24) 
			cClrBits = ILC_COLOR24; 
		else cClrBits = ILC_COLOR32; 

		if(!Create(bmp.bmHeight,bmp.bmHeight,cClrBits|ILC_MASK,nBtnIni,0))
			return FALSE;
		if(Add((HBITMAP)hBmp,RGB(pRbg[0].rgbtRed,pRbg[0].rgbtGreen,pRbg[0].rgbtBlue))==-1)
			return FALSE;
		
		return TRUE;
	}

	HIMAGELIST GetImageHandle()
				{
					return m_hImageList;
				}
	
	BOOL Create( UINT nBitmapID, int cx, int nGrow, COLORREF crMask )
	{
		if (m_hImageList != NULL) return FALSE;
		return Create( MAKEINTRESOURCE(nBitmapID), cx, nGrow,crMask );
	}

	BOOL Create( LPCTSTR lpszBitmapID, int cx, int nGrow, COLORREF crMask )
	{
		if (m_hImageList != NULL) return FALSE;
		m_hImageList = ImageList_LoadBitmap(theApp->GetInstance(), lpszBitmapID, cx, nGrow, crMask);
		return (m_hImageList != NULL) ? TRUE : FALSE;
	}

	BOOL Destroy()
	{
		return ImageList_Destroy(m_hImageList);
	}

	BOOL Attach(HIMAGELIST hNewImageList)
	{
		if (m_hImageList != NULL || hNewImageList == NULL) return FALSE;
		m_hImageList = hNewImageList;
		return TRUE;
	}
	
	HIMAGELIST Detach()
	{
		HIMAGELIST hNewImageList = m_hImageList;
		m_hImageList = NULL;
		return hNewImageList;
	}

	int GetImageCount()
	{
		if (m_hImageList== NULL) return -1;
			return ImageList_GetImageCount(m_hImageList);
	}

	BOOL GetImageInfo(int nImage,IMAGEINFO* pImageInfo)
	{
		return ImageList_GetImageInfo(m_hImageList, nImage, pImageInfo);
	}
	

#if (_WIN32_IE >= 0x0300)
	int SetImageCount(UINT wNewCount)
	{
		if (m_hImageList== NULL) return -1;
		return ImageList_SetImageCount(m_hImageList,wNewCount);
	}
#endif

	int Add(HBITMAP hbmImage, HBITMAP hbmMask)
	{
		if (m_hImageList== NULL) return -1;
		return ImageList_Add(m_hImageList,hbmImage,hbmMask);
	}

	int Add(CBitmap* pbmImage, COLORREF crMask)
	{
		ASSERT(m_hImageList != NULL); 
		return ImageList_AddMasked(m_hImageList, (HBITMAP)pbmImage->GetSafeHandle(), crMask); 
	}

	int Add(HBITMAP hImage, COLORREF crMask)
	{
		ASSERT(m_hImageList != NULL); 
		return ImageList_AddMasked(m_hImageList, (HBITMAP)hImage, crMask); 
	}
	
	int ReplaceIcon(int i,HICON hicon)
	{
		if (m_hImageList== NULL) return -1;
		return ImageList_ReplaceIcon(m_hImageList,i, hicon);
	}

	int AddIcon(HICON hicon)
	{
		if (m_hImageList== NULL) return -1;
		return ImageList_ReplaceIcon(m_hImageList,-1, hicon);
	}
	
	COLORREF SetBkColor(COLORREF clrBk)
	{
		if (m_hImageList== NULL) return -1;
		return ImageList_SetBkColor(m_hImageList, clrBk);
	}

	COLORREF GetBkColor()
	{
		if (m_hImageList== NULL) return -1;
		return ImageList_GetBkColor(m_hImageList);
	}
	
	COLORREF SetOverlayImage(int iImage,int iOverlay)
	{
		if (m_hImageList== NULL) return -1;
		return ImageList_SetOverlayImage(m_hImageList,iImage,iOverlay);
	}

	BOOL Draw(int iImage, HDC hdcDst, int x, int y, UINT fStyle)
	{
		if (m_hImageList== NULL || hdcDst == NULL ) return FALSE;
		return ImageList_Draw(m_hImageList, iImage, hdcDst, x, y, fStyle);
	}

	BOOL Draw(int iImage, HDC hdcDst, POINT pt, UINT fStyle)
	{
		if (m_hImageList== NULL || hdcDst == NULL ) return FALSE;
		return Draw(iImage,hdcDst, pt.x, pt.y,fStyle);
	}


	BOOL Replace(int iImage, HBITMAP hbmImage, HBITMAP hbmMask)
	{
		if (m_hImageList== NULL) return FALSE;
		return ImageList_Replace(m_hImageList, iImage, hbmImage,hbmMask);
	}

	int AddMasked( HBITMAP hbmImage, COLORREF crMask)
	{
		if (m_hImageList== NULL) return -1;
		return ImageList_AddMasked(m_hImageList,hbmImage,crMask);
	}


	BOOL DrawEx(int iImage, HDC hdcDst, int x, int y, int dx, int dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle)
	{
		 if (m_hImageList== NULL) return FALSE;
		 return ImageList_DrawEx(m_hImageList,iImage,hdcDst,x,y,dx,dy,rgbBk,rgbFg,fStyle);
	}

	
#if (_WIN32_IE >= 0x0300)
	
	BOOL DrawIndirect(IMAGELISTDRAWPARAMS* pimldp)
	{
		return ImageList_DrawIndirect(pimldp);
	}
#endif
	
	BOOL Remove(int iImage)
	{
		 if (m_hImageList== NULL) return FALSE;
		 return ImageList_Remove(m_hImageList, iImage);
	}

	BOOL RemoveAll()
	{
		if (m_hImageList== NULL) return FALSE;
		return ImageList_Remove(m_hImageList, -1);
	}

	HICON GetIcon(int iImage,UINT flags)
	{
		if (m_hImageList== NULL) return NULL;
		return ImageList_GetIcon(m_hImageList,iImage,flags);
	}

	
#if (_WIN32_IE >= 0x0300)
	BOOL Copy(int iDst, HIMAGELIST himlSrc, int iSrc, UINT uFlags)
	{
		if (m_hImageList== NULL || himlSrc== NULL ) return NULL;
		return ImageList_Copy(m_hImageList, iDst,himlSrc,iSrc, uFlags);
	}

	BOOL Copy(int iDst, int iSrc, UINT uFlags)
	{
		if (m_hImageList== NULL ) return NULL;
		return ImageList_Copy(m_hImageList, iDst,m_hImageList,iSrc, uFlags);
	}
#endif

	BOOL BeginDrag(int iTrack, int dxHotspot, int dyHotspot)
	{
		if (m_hImageList== NULL ) return NULL;
		return ImageList_BeginDrag(m_hImageList, iTrack, dxHotspot,dyHotspot);
	}
	
	static void EndDrag()
	{
		ImageList_EndDrag();
	}
	

	static BOOL DragEnter(HWND hWndLock,int x, int y)
	{
		if (::IsWindow(hWndLock)) return FALSE;
		return ImageList_DragEnter(hWndLock, x, y);
	}

	static BOOL DragLeave(HWND hWndLock)
	{
		if (::IsWindow(hWndLock)) return FALSE;
		return ImageList_DragLeave( hWndLock);
	}
	
	static BOOL DragLeave(int x, int y)
	{
		return ImageList_DragMove( x, y);
	}
	
	static BOOL DragMove(int x, int y)
	{
		return ImageList_DragMove( x, y);
	}

	BOOL SetDragCursorImage(int iDrag, int dxHotspot, int dyHotspot)
	{
		if (m_hImageList== NULL ) return FALSE;
		return ImageList_SetDragCursorImage(m_hImageList,iDrag,dxHotspot, dyHotspot);
	}

	BOOL  ImageList_DragShowNolock(BOOL fShow)
	{
		return ImageList_DragShowNolock(fShow);
	}

	static HIMAGELIST GetDragImage(POINT FAR* ppt,POINT FAR* pptHotspot)
	{
		return ImageList_GetDragImage(ppt,pptHotspot);
	}

	HICON ExtractIcon( int iImage)
	{
		return GetIcon(iImage,0);
	}
	
	HIMAGELIST LoadBitmap(LPCTSTR lpszBitmapID,int cx,int nGrow, COLORREF crMask)
	{
		return ImageList_LoadBitmap(theApp->GetInstance(), lpszBitmapID, cx, nGrow, crMask);	
	}


#ifdef __IStream_INTERFACE_DEFINED__
	
	static HIMAGELIST Read(LPSTREAM pstm)
	{
		return ImageList_Read(pstm);
	}
	
	BOOL  Write(LPSTREAM pstm)
	{
		if (m_hImageList== NULL ) return FALSE;
		return ImageList_Write(m_hImageList,pstm);
	}
	
#endif

	BOOL GetIconSize(int FAR *cx, int FAR *cy)
	{
		if (m_hImageList== NULL ) return FALSE;
		return ImageList_GetIconSize(m_hImageList,cx, cy);
	}

	BOOL SetIconSize(int cx, int cy)
	{
		if (m_hImageList== NULL ) return FALSE;
		return ImageList_SetIconSize(m_hImageList,cx, cy);
	}

	BOOL GetIconSize(int &cx, int &cy)
	{
		if (m_hImageList== NULL ) return FALSE;
		return ImageList_GetIconSize(m_hImageList,&cx, &cy);
	}

	HIMAGELIST Merge(int i1, HIMAGELIST himl2, int i2, int dx, int dy)
	{
		if (m_hImageList== NULL ) return NULL;
		return ImageList_Merge(m_hImageList, i1,himl2,i2,dx, dy);
	}

#if (_WIN32_IE >= 0x0400)
	static HIMAGELIST  Duplicate(HIMAGELIST himl)
	{
		if (himl== NULL ) return NULL;
		return ImageList_Duplicate(himl);
	}
	
	HIMAGELIST  Duplicate()
	{
		if (m_hImageList== NULL ) return NULL;
		return ImageList_Duplicate(m_hImageList);
	}
#endif


};




/*
 *  CTreeViewCtrl
 *
 **/



class CTreeViewCtrl : public ComControlEX
{
public:

	CTreeViewCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}

	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0)
	{		
		BOOL bRes = CreateEx(0L, WC_TREEVIEW, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}


	UINT GetCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)TreeView_GetCount(m_hWnd) ;
	}
	UINT GetIndent() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)TreeView_GetIndent(m_hWnd) ;
	}
	void SetIndent(UINT indent)
	{
		ASSERT(::IsWindow(m_hWnd));
		TreeView_SetIndent(m_hWnd, indent);
	}
	CImageCtrl GetImageList(UINT iImage) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)TreeView_GetImageList(m_hWnd, iImage));
	}
	void SetImageList(HIMAGELIST himl, int iImage)
	{
		ASSERT(::IsWindow(m_hWnd));
		TreeView_SetImageList(m_hWnd,  himl,iImage);
	}


	BOOL GetItem(LPTVITEM pitem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_GetItem(m_hWnd, pitem) ;
	}
	BOOL SetItem(LPTVITEM pitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SetItem(m_hWnd, pitem);
	}
	
	BOOL GetItemText(HTREEITEM hItem, LPTSTR lpstrText, int nSize) 
	{
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(lpstrText != NULL);
		TVITEM item;
		item.hItem = hItem;
		item.mask = TVIF_TEXT;
		item.pszText = lpstrText;
		item.cchTextMax = nSize;

		return (BOOL)GetItem(&item);
	}


/*	BOOL SetItemText(HTREEITEM hItem, LPCTSTR lpszItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return SetItem(hItem, TVIF_TEXT, lpszItem, 0, 0, 0, 0, NULL);
	}
*/	
	CEdit GetEditControl() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CEdit((HWND)TreeView_GetEditControl(m_hWnd));
	}
	
	UINT GetVisibleCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)TreeView_GetVisibleCount(m_hWnd);
	}
	BOOL GetItemRect(HTREEITEM hitem, LPRECT lpRc, BOOL bCode) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_GetItemRect(m_hWnd, hitem, lpRc, bCode);
	}
	
	BOOL NodeIfChildren(HTREEITEM hItem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		TVITEM Node;
		Node.hItem = hItem;
		Node.mask = TVIF_CHILDREN;
		GetItem(&Node);
		return Node.cChildren;
	}
	
	CToolTipCtrl GetToolTips() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CToolTipCtrl((HWND)TreeView_GetToolTips(m_hWnd) );
	}
	
	void SetToolTips(HWND hWndTT)
	{
		ASSERT(::IsWindow(m_hWnd));
		TreeView_SetToolTips(m_hWnd,  hWndTT)  ;
	}
	int GetISearchString(LPTSTR  lpsz) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TreeView_GetISearchString(m_hWnd, lpsz);
	}

	
#if (_WIN32_IE >= 0x0400)
	COLORREF GetBkColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)TreeView_GetBkColor(m_hWnd);
	}
	COLORREF SetBkColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)TreeView_SetBkColor(m_hWnd, clr);
	}
	COLORREF GetInsertMarkColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)TreeView_GetInsertMarkColor(m_hWnd);
	}
	COLORREF SetInsertMarkColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF) TreeView_SetInsertMarkColor(m_hWnd, clr);
	}
	int GetItemHeight() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TreeView_GetItemHeight(m_hWnd);
	}
	int SetItemHeight(int iHeight)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TreeView_SetItemHeight(m_hWnd,  iHeight) ;
	}
	int GetScrollTime() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TreeView_GetScrollTime(m_hWnd) ;
	}
	int SetScrollTime(int uTime)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TreeView_SetScrollTime(m_hWnd, uTime);
	}
	COLORREF GetTextColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)TreeView_GetTextColor(m_hWnd) ;
	}
	COLORREF SetTextColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)TreeView_SetTextColor(m_hWnd, clr) ;
	}
	BOOL GetUnicodeFormat() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_GetUnicodeFormat(m_hWnd);
	}
	BOOL SetUnicodeFormat(BOOL fUnicode)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SetUnicodeFormat(m_hWnd, fUnicode);
	
	}
#endif 


	HTREEITEM InsertItem(LPTV_INSERTSTRUCT lpis)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HTREEITEM)TreeView_InsertItem(m_hWnd, lpis);
	}
	


	HTREEITEM InsertItem(LPCTSTR lpszItem, int nImage,int nSelectedImage,
						 HTREEITEM hParent= TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST)
    { 
		ASSERT(::IsWindow(m_hWnd)); 
		return InsertItem(hParent, hInsertAfter,TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE,
			lpszItem, nImage, nSelectedImage, 0, 0, 0 ); 
	}

    HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent= TVI_ROOT, HTREEITEM hInsertAfter= TVI_LAST)
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		return InsertItem(hParent, hInsertAfter, TVIF_TEXT, lpszItem, 0, 0, 0, 0, 0 ); 
	}

	
 
	HTREEITEM InsertItem(HTREEITEM hParent, HTREEITEM hInsertAfter, UINT mask, LPCTSTR pszText, int iImage,
					 int iSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam)
	{
		TV_INSERTSTRUCT tv;
		tv.hParent = hParent;
		tv.hInsertAfter = hInsertAfter;
		tv.item.mask = mask;
		tv.item.pszText = (LPTSTR) pszText;
		tv.item.iImage = iImage;
		tv.item.iSelectedImage = iSelectedImage;
		tv.item.state = nState;
		tv.item.stateMask = nStateMask;
		tv.item.lParam = lParam;
		return (HTREEITEM)InsertItem(&tv); 
	}
	
		
	BOOL DeleteItem(HTREEITEM hitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_DeleteItem(m_hWnd, hitem);
	}
	BOOL DeleteAllItems()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_DeleteAllItems(m_hWnd) ;
	}
	BOOL Expand(HTREEITEM hItem, UINT code)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_Expand(m_hWnd, hItem, code);
	}
	HTREEITEM GetNextItem(HTREEITEM hitem, UINT code) 
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		return (HTREEITEM)TreeView_GetNextItem(m_hWnd, hitem, code);
	}
	HTREEITEM GetChild(HTREEITEM hitem) 
	{
		ASSERT(::IsWindow(m_hWnd)); 
		return (HTREEITEM)TreeView_GetChild(m_hWnd, hitem);
	}
	HTREEITEM GetNextSibling(HTREEITEM hitem) 
	{
		ASSERT(::IsWindow(m_hWnd)); 
		return (HTREEITEM)TreeView_GetNextSibling(m_hWnd, hitem);
	}
	HTREEITEM GetPrevSibling(HTREEITEM hitem) 
	{
		ASSERT(::IsWindow(m_hWnd)); 
		return (HTREEITEM)TreeView_GetPrevSibling(m_hWnd, hitem);
	}
	HTREEITEM GetParent(HTREEITEM hitem) 
	{
		ASSERT(::IsWindow(m_hWnd)); 
		return (HTREEITEM)TreeView_GetParent(m_hWnd, hitem);
	}
	HTREEITEM GetFirstVisibleItem() 
	{
		ASSERT(::IsWindow(m_hWnd)); 
		return (HTREEITEM)TreeView_GetFirstVisible(m_hWnd);
	}
	HTREEITEM GetNextVisible(HTREEITEM hitem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HTREEITEM)TreeView_GetNextVisible(m_hWnd, hitem);
	}
	HTREEITEM GetPrevVisible(HTREEITEM hitem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HTREEITEM)TreeView_GetPrevVisible(m_hWnd, hitem);
	}
	HTREEITEM GetSelected() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HTREEITEM)TreeView_GetSelection(m_hWnd) ;
	}
	HTREEITEM GetDropHilight() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HTREEITEM)TreeView_GetDropHilight(m_hWnd);
	}
	HTREEITEM GetRoot() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HTREEITEM)TreeView_GetRoot(m_hWnd);
	}
	BOOL Select(HTREEITEM hitem, UINT code)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_Select(m_hWnd, hitem, code) ;
	}
	BOOL SelectItem(HTREEITEM hitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SelectItem(m_hWnd, hitem);
	}
	BOOL SelectDropTarget(HTREEITEM hitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SelectDropTarget(m_hWnd, hitem);
	}
	BOOL SelectSetFirstVisible(HTREEITEM hitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SelectSetFirstVisible(m_hWnd, hitem) ;
	}

	CEdit EditLabel(HTREEITEM hitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CEdit((HWND)TreeView_EditLabel(m_hWnd, hitem)) ;
	}
	BOOL EndEditLabelNow(BOOL fCancel)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_EndEditLabelNow(m_hWnd, fCancel);
		
	}
	HTREEITEM HitTest(TV_HITTESTINFO* lpht)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HTREEITEM)TreeView_HitTest(m_hWnd, lpht);
	}
	HTREEITEM HitTest(POINT pt, UINT* pFlags)
	{
		ASSERT(::IsWindow(m_hWnd));
		TV_HITTESTINFO hti;
		hti.pt = pt;
		HTREEITEM hTreeItem = (HTREEITEM)::SendMessage(m_hWnd, TVM_HITTEST, 0, (LPARAM)&hti);
		if (pFlags != NULL)
			*pFlags = hti.flags;
		return hTreeItem;
	}
	BOOL SortChildren(HTREEITEM hitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SortChildren(m_hWnd, hitem, TVM_SORTCHILDREN) ;
	}
	BOOL EnsureVisible(HTREEITEM hitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_EnsureVisible(m_hWnd, hitem);
	}
	BOOL SortChildrenCB(LPTV_SORTCB psort)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SortChildrenCB(m_hWnd, psort, TVM_SORTCHILDRENCB);
	}
	CImageCtrl RemoveImageList(int nImageList)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)::SendMessage(m_hWnd, TVM_SETIMAGELIST, (WPARAM)nImageList, NULL));
	}
	CImageCtrl CreateDragImage(HTREEITEM hitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)TreeView_CreateDragImage(m_hWnd, hitem));
	}

#if (_WIN32_IE >= 0x0400)
	BOOL SetInsertMark(HTREEITEM hItem, BOOL fAfter)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SetInsertMark(m_hWnd, hItem, fAfter) ;
	}
	BOOL RemoveInsertMark()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TreeView_SetInsertMark(m_hWnd,0,0);
	}
#endif //(_WIN32_IE >= 0x0400)


};


/*
 *  CIPAddressCtrl
 *
 **/


class CIPAddressCtrl : public ComControl
{
	
public:

	CIPAddressCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}
	
	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0)
	{		
		BOOL bRes = CreateEx(0L, WC_IPADDRESS, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}
	~CIPAddressCtrl(){}
	
public:

	
	int GetAddress(LPDWORD lpdwAddress) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)SendMessage(IPM_GETADDRESS, 0, (LPARAM)lpdwAddress);
	}
	void SetAddress(DWORD dwAddress)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(IPM_SETADDRESS, 0, dwAddress);
	}
	void ClearAddress()
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( IPM_CLEARADDRESS, 0, 0L);
	}
	void SetRange(int nField, WORD wRange)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(IPM_SETRANGE, nField, wRange);
	}
	void SetRange(int nField, BYTE nMin, BYTE nMax)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage( IPM_SETRANGE, nField, MAKEIPRANGE(nMin, nMax));
	}
	
	BOOL IsBlank() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)SendMessage(IPM_ISBLANK, 0, 0L);
	}
	
	void SetFocus(int nField)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(IPM_SETFOCUS, nField, 0L);
	}
};



/*
 *  CAnimateCtrl
 *
 **/

class CAnimateCtrl : public ComControl
{
public:
	CAnimateCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}

	
	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0)
	{		
		BOOL bRes = CreateEx(0L, ANIMATE_CLASS, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}
	~CAnimateCtrl(){}


public:
	
	BOOL Open(LPCTSTR szName)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Animate_Open(m_hWnd, szName); 
	}
	BOOL Play(UINT uFrom, UINT uTo, UINT uRep)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Animate_Play(m_hWnd, uFrom, uTo, uRep) ;
	}
	BOOL Stop()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Animate_Stop(m_hWnd);
	}
	BOOL Close()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Animate_Close(m_hWnd);
	}
	BOOL Seek(UINT uFrame)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Animate_Seek(m_hWnd, uFrame);
	}
};


/*
 *  CHotKeyCtrl
 *
 **/


class CHotKeyCtrl : public ComControl
{
public:

	CHotKeyCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}

	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0)
	{		
		BOOL bRes = CreateEx(0L, HOTKEY_CLASS, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}
	~CHotKeyCtrl(){}

public:
	
	DWORD GetHotKey() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)SendMessage(HKM_GETHOTKEY, 0, 0L);
	}
	
	void SetHotKey(WORD wVKey, WORD wModif)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(HKM_SETHOTKEY, MAKEWORD(wVKey, wModif), 0L);
	}

	void SetRules(WORD wInvalidComb, WORD wModifi)
	{
		ASSERT(::IsWindow(m_hWnd));
		SendMessage(HKM_SETRULES, wInvalidComb, MAKELPARAM(wModifi, 0));
	}
};




/*
 *  CDateTimePickerCtrl
 *
 **/

class CDateTimePickerCtrl : public ComControl
{
public:

	CDateTimePickerCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}

	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0)
	{		
		BOOL bRes = CreateEx(0L, DATETIMEPICK_CLASS, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}
	~CDateTimePickerCtrl()  { }
public:
	
	BOOL SetFormat(LPTSTR lpszFormat)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)DateTime_SetFormat(m_hWnd, lpszFormat);
	}
	COLORREF GetMonthCalColor(int iColor) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)DateTime_GetMonthCalColor(m_hWnd, iColor) ;
	}
	COLORREF SetMonthCalColor(int iColor, COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)DateTime_SetMonthCalColor(m_hWnd, iColor, clr) ;
	}
	BOOL SetSystemTime(DWORD dwFlags, LPSYSTEMTIME lpPst)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)DateTime_SetSystemtime(m_hWnd, dwFlags, lpPst);
	}
	
	HFONT GetMonthCalFont() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HFONT)DateTime_GetMonthCalFont(m_hWnd);
	}
	void SetMonthCalFont(HFONT hFont, BOOL bRedraw)
	{
		ASSERT(::IsWindow(m_hWnd));
		DateTime_SetMonthCalFont(m_hWnd, hFont, bRedraw) ;
		
	}
	HWND GetMonthCal() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HWND)DateTime_GetMonthCal(m_hWnd);
	}
	
	DWORD GetRange(LPSYSTEMTIME lprgst) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)DateTime_GetRange(m_hWnd, lprgst);
	}
	BOOL SetRange(DWORD dwFlags, LPSYSTEMTIME lprgst)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)DateTime_SetRange(m_hWnd, dwFlags, lprgst);
	}
	DWORD GetSystemTime(LPSYSTEMTIME lpPst) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)DateTime_GetSystemtime(m_hWnd, lpPst);
	}
	

};



/*
 *  CPagerCtrl
 *
 **/

class CPagerCtrl : public ComControl
{
public:

	CPagerCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}

	
	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0)
	{		
		BOOL bRes = CreateEx(0L, WC_PAGESCROLLER, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}
	~CPagerCtrl(){}

public:
	
	void SetChild(HWND hWndChild)
	{
		ASSERT(::IsWindow(m_hWnd));
		Pager_SetChild(m_hWnd, hWndChild);
	}
	
	void RecalcSize()
	{
		ASSERT(::IsWindow(m_hWnd));
		Pager_RecalcSize(m_hWnd) ;
	}
	
	void ForwardMouse(BOOL bForward)
	{
		ASSERT(::IsWindow(m_hWnd));
		Pager_ForwardMouse(m_hWnd, bForward);
	}
	COLORREF SetBkColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF) Pager_SetBkColor(m_hWnd, clr);
	}
	COLORREF GetBkColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)Pager_GetBkColor(m_hWnd);
	}
	int SetBorder(int iBorder)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Pager_SetBorder(m_hWnd, iBorder);
	}
	int GetBorder() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Pager_GetBorder(m_hWnd);
	}
	int SetPos(int iPos)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Pager_SetPos(m_hWnd, iPos);
	}
	int GetPos() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Pager_GetPos(m_hWnd);
	}
	
	int SetButtonSize(int iSize)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Pager_SetButtonSize(m_hWnd, iSize) ;
	}
	int GetButtonSize() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Pager_GetButtonSize(m_hWnd);
	}
	
	DWORD GetButtonState(int iButton) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)Pager_GetButtonState(m_hWnd, iButton);
	}
	
/*	void GetDropTarget(IDropTarget**  ppdt)
	{
		ASSERT(::IsWindow(m_hWnd));
		Pager_GetDropTarget(m_hWnd, ppdt) ;
	}*/
};



/*
 *  CHeaderCtrl
 *
 **/


class CHeaderCtrl : public ComControlEX
{
public:

	CHeaderCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}

	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0)
	{		
		BOOL bRes = CreateEx(0L, WC_HEADER, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}
	
public:
	
	int GetItemCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Header_GetItemCount(m_hWnd);
		
	}
	BOOL GetItem(int nIndex, LPHDITEM phdi) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_GetItem(m_hWnd, nIndex, phdi) ;
	}
	BOOL SetItem(int nIndex, LPHDITEM phdi)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_SetItem(m_hWnd,nIndex, phdi);
	}

	void GetItemText(int nIndex,LPSTR lpBuffer,int nSize)
	{
		HDITEM hdi;
		hdi.mask = HDI_TEXT;
		hdi.pszText = lpBuffer;
		hdi.cchTextMax = nSize;

		GetItem(nIndex, &hdi);
	   		
	}

	void GetItemFull(int nIndex,HDITEM* hdi,LPSTR lpBuffer,int nSize)
	{
		hdi->mask = HDI_TEXT|HDI_WIDTH|HDI_HEIGHT|HDI_FORMAT|HDI_LPARAM|HDI_BITMAP|HDI_IMAGE|HDI_ORDER;
		hdi->pszText = lpBuffer;
		hdi->cchTextMax = nSize;

		GetItem(nIndex, hdi);
		
	   		
	}

	CImageCtrl GetImageList() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)Header_GetImageList(m_hWnd));
	}
	CImageCtrl SetImageList(HIMAGELIST himl)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)Header_SetImageList(m_hWnd, himl));
		
	}
	BOOL GetOrderArray(int iCount, int*  lpi) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_GetOrderArray(m_hWnd, iCount, lpi) ;
	}
	BOOL SetOrderArray(int iCount, int* lpi)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_SetOrderArray(m_hWnd, iCount, lpi);
	}
	BOOL GetItemRect(int iItem, LPRECT lprc) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_GetItemRect(m_hWnd, iItem, lprc) ;
	}
	int SetHotDivider(BOOL fPos, DWORD dwInputVal)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Header_SetHotDivider(m_hWnd, fPos, dwInputVal);
	}
	

#if (_WIN32_IE >= 0x0400)
	BOOL GetUnicodeFormat() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_GetUnicodeFormat(m_hWnd) ;
	
	}
	BOOL SetUnicodeFormat(BOOL fUnicode )
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_SetUnicodeFormat(m_hWnd, fUnicode);
	}
#endif //(_WIN32_IE >= 0x0400)

	int InsertItem(int nItem, LPHDITEM phdi)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Header_InsertItem(m_hWnd,nItem, phdi) ;
	}
	BOOL DeleteItem(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_DeleteItem(m_hWnd,nIndex);
	}
	BOOL Layout(HD_LAYOUT* playout)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)Header_Layout(m_hWnd, playout) ;
	}
	int HitTest(LPHDHITTESTINFO lpHitTest) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)::SendMessage(m_hWnd, HDM_HITTEST, 0, (LPARAM)lpHitTest);
	}
	int OrderToIndex(int nOrder)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)Header_OrderToIndex(m_hWnd, nOrder);
	}
	CImageCtrl CreateDragImage(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)Header_CreateDragImage(m_hWnd, nIndex) );
	}

};


/*
 *  CListView
 *
 **/

class CListView: public ComControlEX
{
public:
	CListView(HWND hWnd=NULL){m_hWnd=hWnd;}


	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0,LPCTSTR lpWindowName=NULL)
	{		
		BOOL bRes = CreateEx(0L, WC_LISTVIEW, lpWindowName,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}

public:

	COLORREF GetBkColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)ListView_GetBkColor(m_hWnd);
	}

	BOOL SetBkColor(COLORREF clrBk)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetBkColor(m_hWnd, clrBk);
	}
	CImageCtrl GetImageList(int nImageListType) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)ListView_GetImageList(m_hWnd,nImageListType));
	}
	CImageCtrl SetImageList(HIMAGELIST hImageList, int nImageList)
	{
		ASSERT(::IsWindow(m_hWnd)); 
		return CImageCtrl((HIMAGELIST)ListView_SetImageList(m_hWnd, hImageList, hImageList));
	}
	int GetItemCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_GetItemCount(m_hWnd);
	}
	BOOL SetItemCount(int nItems)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetItemCount(m_hWnd, nItems);
	}
	BOOL GetItem(LPLVITEM pItem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetItem(m_hWnd, pItem);
	}
	BOOL SetItem( LVITEM* pItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetItem(m_hWnd, pItem); 
	}
	
	UINT GetItemState(int nItem, UINT mask) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)ListView_GetItemState(m_hWnd, nItem, mask);
	}

	void SetItemState(int nIndex, UINT nState, UINT nMask)
	{
		ASSERT(::IsWindow(m_hWnd));
		ListView_SetItemState(m_hWnd, nIndex, nState, nMask);
	}
	

	void GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen)
	{
		ASSERT(::IsWindow(m_hWnd));
		ListView_GetItemText(m_hWnd, nItem, nSubItem, lpszText, nLen);
	}
	void SetItemText(int nItem, int nSubItem, LPSTR lpszText)
	{
		ASSERT(::IsWindow(m_hWnd));
		ListView_SetItemText(m_hWnd, nItem, nSubItem, lpszText);
	}
	
	BOOL GetItemData(int nItem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetItem(m_hWnd, nItem);
	}
	
	UINT GetCallbackMask() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)ListView_GetCallbackMask(m_hWnd);
	}
	BOOL SetCallbackMask(UINT nMask)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetCallbackMask(m_hWnd, nMask);
	}
	BOOL GetItemPosition(int nItem, LPPOINT ppt) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetItemPosition(m_hWnd, nItem, ppt);
	}
	
	void SetItemPosition(int nItem, POINT pt)
	{
		ASSERT(::IsWindow(m_hWnd));
		ListView_SetItemPosition32(m_hWnd, nItem, pt.x, pt.y);
	}
	
	void SetItemPosition(int nItem, int x, int y)
	{
		POINT pt;
		pt.x=x; pt.y=y;
		ASSERT(::IsWindow(m_hWnd));
		SetItemPosition(nItem, pt);

	}
	int GetStringWidth(LPCTSTR psz) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_GetStringWidth(m_hWnd, psz);
	}
	CEdit GetEditControl() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CEdit((HWND)ListView_GetEditControl(m_hWnd));
	}
	BOOL GetColumn(int nCol, LV_COLUMN* pCol) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetColumn(m_hWnd, nCol, pCol);
	}
	BOOL SetColumn(int nCol,  LV_COLUMN* pCol)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetColumn(m_hWnd, nCol, pCol);
	}
	
	int GetColumnWidth(int iCol) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_GetColumnWidth(m_hWnd, iCol);
	}
	
	BOOL SetColumnWidth(int nCol, int nCx)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetColumnWidth(m_hWnd, nCol, nCx);
	}
	
	BOOL GetViewRect(LPRECT lpRc) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetViewRect(m_hWnd, lpRc);
	}
	
	COLORREF GetTextColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)ListView_GetTextColor(m_hWnd); 
	}
	
	BOOL SetTextColor(COLORREF clrText)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetTextColor(m_hWnd, clrText);
	}
	
	COLORREF GetTextBkColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)ListView_GetTextBkColor(m_hWnd);
	}

	BOOL SetTextBkColor(COLORREF clrTextBk)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetTextBkColor(m_hWnd, clrTextBk);
	}

	int GetTopIndex() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_GetTopIndex(m_hWnd);
	}
	
	int GetCountPerPage() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_GetCountPerPage(m_hWnd);
	}
	
	BOOL GetOrigin(LPPOINT ppt) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetOrigin(m_hWnd, ppt);
	}
	
	UINT GetSelectedCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)ListView_GetSelectedCount(m_hWnd);
	}

	BOOL GetItemRect(int nIndex, LPRECT lpRect, UINT nCode) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetItemRect(m_hWnd, nIndex, lpRect, nCode);
	}

	HCURSOR GetHotCursor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HCURSOR)ListView_GetHotCursor(m_hWnd);
	}

	HCURSOR SetHotCursor(HCURSOR hcur)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HCURSOR) ListView_SetHotCursor(m_hWnd, hcur);
	}
	int GetHotItem() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) ListView_GetHotItem(m_hWnd);
	}
	
	int SetHotItem(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) ListView_SetHotItem(m_hWnd, nIndex);
	}
	
	BOOL GetColumnOrderArray(int nCount, int* pi) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_GetColumnOrderArray(m_hWnd, nCount, pi);
	}
	
	BOOL SetColumnOrderArray(int nCount, int* pi)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_SetColumnOrderArray(m_hWnd, nCount, pi);
	}
	
	CHeaderCtrl GetHeader() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CHeaderCtrl((HWND)::SendMessage(m_hWnd, LVM_GETHEADER, 0, 0L));
	}

	BOOL GetSubItemRect(int nItem, int nSubItem, int code, LPRECT prc) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_GetSubItemRect(m_hWnd, nItem, nSubItem, code, prc);
	}
	
	DWORD SetIconSpacing(int cx, int cy)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD) ListView_SetIconSpacing(m_hWnd, cx, cy);
	}
	
	int GetISearchString(LPTSTR lpsz) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) ListView_GetISearchString(m_hWnd, lpsz);
	}
	
	void GetItemSpacing(SIZE& pSize, BOOL fSmallIcon) 
	{
		ASSERT(::IsWindow(m_hWnd));
		DWORD dwRt=ListView_GetItemSpacing(m_hWnd, fSmallIcon);
		pSize.cx = HIWORD(dwRt);
		pSize.cy = LOWORD(dwRt);
	}

	
	int GetNextItem() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) ListView_GetNextItem(m_hWnd, -1, MAKELPARAM(LVNI_ALL | LVNI_SELECTED, 0));
	}

	DWORD GetExtendedListViewStyle() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)ListView_GetExtendedListViewStyle(m_hWnd);
	}
	DWORD SetExtendedListViewStyle(DWORD dwExStyle)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD) ListView_SetExtendedListViewStyle(m_hWnd, dwExStyle);
	}

	
	BOOL GetCheckState(int nItem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return ListView_GetCheckState( m_hWnd, nItem );
		
	}

	
	BOOL GetBkImage(LPLVBKIMAGE plvbki) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetBkImage(m_hWnd, plvbki);
	}
	
	BOOL SetBkImage(LPLVBKIMAGE plvbki)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetBkImage(m_hWnd, plvbki);
			
	}
	int GetSelectionMark() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) ListView_GetSelectionMark(m_hWnd);
	}

	int SetSelectionMark(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_SetSelectionMark(m_hWnd, nIndex);
	}
	
	BOOL GetWorkAreas(int nWrka, LPRECT lpRect) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetWorkAreas(m_hWnd, nWrka, lpRect);
	}

	BOOL SetWorkAreas(int nWrka, LPRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_SetWorkAreas(m_hWnd, nWrka, lpRect);
	}

	DWORD GetHoverTime() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)(DWORD)SendMessage(LVM_GETHOVERTIME, 0, 0);
	}
	DWORD SetHoverTime(DWORD dwHoverTime)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD) SendMessage(LVM_SETHOVERTIME, 0, dwHoverTime);

	}

	BOOL GetNumberOfWorkAreas(int* pnWrka) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetNumberOfWorkAreas(m_hWnd, pnWrka);
		
	}

	BOOL SetItemCountEx(int cItems, DWORD dwFlags)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetItemCountEx(m_hWnd, cItems, dwFlags);
			
	}

	CToolTipCtrl GetToolTips() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CToolTipCtrl((HWND) SendMessage(LVM_GETTOOLTIPS, 0, 0) );
	}

	CToolTipCtrl SetToolTips(HWND hWnd)
	{
		ASSERT(::IsWindow(hWnd));
		return CToolTipCtrl((HWND)SendMessage(LVM_SETTOOLTIPS, (int)hWnd, 0));

	}
	BOOL GetUnicodeFormat() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_GetUnicodeFormat(m_hWnd);
	}
	BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_SetUnicodeFormat(m_hWnd, fUnicode);
	}


	int InsertColumn(int nCol,  LV_COLUMN* pCol)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_InsertColumn(m_hWnd, nCol, pCol);
		
	}
	
	int InsertColumn(int nCol, LPCTSTR lpszText, int Flag, int nWidth, int nSubItem)
	{
		LV_COLUMN lvNewColumn;
		lvNewColumn.mask = LVCF_TEXT|LVCF_FMT;
		lvNewColumn.pszText = (LPTSTR)lpszText;
		lvNewColumn.fmt = Flag;
		lvNewColumn.cx = nWidth;
		lvNewColumn.iSubItem = nSubItem;
		if (nWidth != -1) lvNewColumn.mask |= LVCF_WIDTH;
		if (nSubItem != -1) lvNewColumn.mask |= LVCF_SUBITEM;
		return InsertColumn(nCol, &lvNewColumn);
	}

	BOOL DeleteColumn(int nCol)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_DeleteColumn(m_hWnd, nCol);

	}
	
	int InsertItem( LVITEM* pitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_InsertItem(m_hWnd, pitem);
	}
	
	int InsertItem(int nMask=LVIF_TEXT, int nItem=LVM_INSERTITEM, LPCTSTR lpszText=0, int nSubItem=0,
				   int nState=0, UINT nStateMask=0, int nImage=0, LPARAM lParam=0)
	{
		ASSERT(::IsWindow(m_hWnd));
		LVITEM stitem;
		stitem.mask = nMask;
		stitem.iItem = nItem;
		stitem.iSubItem = nSubItem;
		stitem.pszText = (LPTSTR)lpszText;
		stitem.state = nState;
		stitem.stateMask = nStateMask;
		stitem.iImage = nImage;
		stitem.lParam = lParam;
		return InsertItem(&stitem);
	}

	int InsertItemText(int nItem, LPCTSTR lpszText)
	{
		ASSERT(::IsWindow(m_hWnd));
		return InsertItem(LVIF_TEXT, nItem,lpszText);
	}
	
	int InsertItemText(int nItem, int nSubItem, LPCTSTR lpszText)
	{
		ASSERT(::IsWindow(m_hWnd));
		LVITEM stitem;
		stitem.iSubItem = nSubItem;
		stitem.pszText = (LPTSTR) lpszText;
		return ::SendMessage(m_hWnd, LVM_SETITEMTEXT, nItem, (LPARAM)&stitem);
	}

	int InsertItemTextImage(int nItem, LPCTSTR lpszText, int nImage)
	{
		ASSERT(::IsWindow(m_hWnd));
		return InsertItem(LVIF_TEXT|LVIF_IMAGE, nItem,lpszText, 0, 0, nImage, 0);
	}
	int GetNextItem(int nItem, int nFlags) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) ListView_GetNextItem(m_hWnd, nItem, nFlags);
	}
	
	BOOL DeleteItem(int nItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_DeleteItem(m_hWnd, nItem); 
	}
	BOOL DeleteAllItems()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_DeleteAllItems(m_hWnd);
		
	}
	int FindItem(LV_FINDINFO* plvfi, int nStart) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) ListView_FindItem(m_hWnd, nStart, plvfi);
	}
	int HitTest(LV_HITTESTINFO* pInfo) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int) ListView_HitTest(m_hWnd, pInfo);
		
	}
	
	BOOL EnsureVisible(int nItem, BOOL bPartialOK)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_EnsureVisible(m_hWnd, nItem, bPartialOK);
		
	}
	BOOL Scroll(SIZE size)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_Scroll(m_hWnd, size.cx, size.cy);
	}
	
	BOOL RedrawItems(int nFirst, int nLast)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)ListView_RedrawItems(m_hWnd, nFirst, nLast);

	}
	BOOL Arrange(UINT nCode)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_Arrange(m_hWnd, nCode);
	}
	
	CEdit EditLabel(int nItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CEdit((HWND)ListView_EditLabel(m_hWnd, nItem));
	}

	BOOL Update(int nItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_Update(m_hWnd, nItem);

	}
	BOOL SortItems(PFNLVCOMPARE pCompare, LPARAM lpSort)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) ListView_SortItems(m_hWnd, pCompare, lpSort);
	}

	CImageCtrl RemoveImageList(int nImgList)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)ListView_SetImageList(m_hWnd, nImgList, NULL));
	}

	CImageCtrl CreateDragImage(int nItem, LPPOINT lpptUpLeft)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)ListView_CreateDragImage(m_hWnd, nItem, lpptUpLeft));
	}
	DWORD ApproximateViewRect(int nCx ,int nCy,  int nCount )
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)ListView_ApproximateViewRect(m_hWnd, nCx, nCy, nCount);
	}
	int SubItemHitTest(LPLVHITTESTINFO plvhti)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)ListView_SubItemHitTest(m_hWnd, plvhti);
	}

	
	
};



/*
 *  CTabCtrl
 *
 **/

class CTabCtrl : public ComControl
{
public:

	CTabCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}



	BOOL Create(HWND hWndParent,DWORD dwStyle=0,
			UINT uID=0)
	{		
		BOOL bRes = CreateEx(0L, WC_TABCONTROL, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}

public:
	
	
	int GetItemCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TabCtrl_GetItemCount(m_hWnd);
	}
	BOOL GetItem(int iItem, LPTCITEM pitem) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_GetItem(m_hWnd, iItem, pitem);
	}
	BOOL SetItem(int iItem, LPTCITEM pitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_SetItem(m_hWnd, iItem, pitem);
	}
	BOOL GetItemRect(int iItem, LPRECT lpRect) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_GetItemRect(m_hWnd, iItem, lpRect);
	}
	int GetCurSel() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TabCtrl_GetCurSel(m_hWnd);
	}
	int SetCurSel(int iItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TabCtrl_SetCurSel(m_hWnd, iItem);
	}
	void SetItemSize(int iX,int iY)
	{
		ASSERT(::IsWindow(m_hWnd));
		TabCtrl_SetItemSize(m_hWnd, iX, iY);
	}
	void SetPadding(int cx, int cy)
	{
		ASSERT(::IsWindow(m_hWnd));
		TabCtrl_SetPadding(m_hWnd,  cx, cy);
	}
	int GetRowCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TabCtrl_GetRowCount(m_hWnd);
	}
	CToolTipCtrl GetTooltips() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CToolTipCtrl((HWND)TabCtrl_GetToolTips(m_hWnd));
	}
	void SetTooltips(HWND m_hWndTT)
	{
		ASSERT(::IsWindow(m_hWnd));
		TabCtrl_SetToolTips(m_hWnd, m_hWndTT);
	}
	
	int GetCurFocus() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TabCtrl_GetCurFocus(m_hWnd) ;
	}

	void SetCurFocus(int nItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		TabCtrl_SetCurFocus(m_hWnd, nItem);
	}
	BOOL SetItemExtra(int cb)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL) TabCtrl_SetItemExtra(m_hWnd, cb);
	}
	int SetMinTabWidth(int nWidth )
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TabCtrl_SetMinTabWidth(m_hWnd, nWidth) ;
	}

#if (_WIN32_IE >= 0x0400)
	DWORD GetExtendedStyle() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)TabCtrl_GetExtendedStyle(m_hWnd);
	}
	DWORD SetExtendedStyle(DWORD dwExStyle)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (DWORD)TabCtrl_SetExtendedStyle(m_hWnd, dwExStyle);
	}
	BOOL GetUnicodeFormat() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_GetUnicodeFormat(m_hWnd);
	}
	BOOL SetUnicodeFormat(BOOL bUnicode )
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_SetUnicodeFormat(m_hWnd, bUnicode) ;
	}
#endif 


	BOOL InsertItem(int iItem, LPTCITEM pitem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_InsertItem(m_hWnd, iItem, pitem);
	}
	BOOL DeleteItem(int nItem)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_DeleteItem(m_hWnd, nItem) ;
	}
	BOOL DeleteAllItems()
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_DeleteAllItems(m_hWnd);
	}
	void AdjustRect(BOOL bLarger, LPRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWnd));
		TabCtrl_AdjustRect(m_hWnd, bLarger, lpRect);
	}
	void RemoveImage(int nImage)
	{
		ASSERT(::IsWindow(m_hWnd));
		TabCtrl_RemoveImage(m_hWnd, nImage);
	}
	int HitTest(TC_HITTESTINFO* pinfo) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)TabCtrl_HitTest(m_hWnd, pinfo);
	}
	void DeselectAll(BOOL bExcludeFocus)
	{
		ASSERT(::IsWindow(m_hWnd));
		TabCtrl_DeselectAll(m_hWnd, bExcludeFocus);
	}
	CImageCtrl GetImageList() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)TabCtrl_GetImageList(m_hWnd) );
	}
	CImageCtrl SetImageList(HIMAGELIST himl)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CImageCtrl((HIMAGELIST)TabCtrl_SetImageList(m_hWnd, himl) );
	}
#if (_WIN32_IE >= 0x0400)
	BOOL HighlightItem(int nIndex, BOOL bHighlight)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)TabCtrl_HighlightItem(m_hWnd, nIndex,  bHighlight);
	}
#endif 
};


/*
 *  CStatusCtrl
 *
 **/


class CStatusCtrl: public ComControl
{

public:
	CStatusCtrl(){}; 
	~CStatusCtrl(){};
public:
	
	
	BOOL Create(HWND hWndParent,DWORD dwStyle=WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | SBARS_SIZEGRIP,
			UINT uID=BASE_STATUS_BAR)
	{		
		BOOL bRes = CreateEx(0L, STATUSCLASSNAME, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}
	

#if (_WIN32_IE >= 0x0400)
	
	HICON GetIcon(int nIndex) 
	{
		if (nIndex < 256)
			return (HICON)SendMessage(SB_GETICON, nIndex, 0L);
	}

	BOOL SetIcon(int nIndex, HICON hIcon)
	{
		if(nIndex < 256)
			return (BOOL)SendMessage(SB_SETICON, nIndex, (LPARAM)hIcon);
	}


	COLORREF SetBkColor(COLORREF clrBk=CDrawLayer::GetRGBColorFace())
	{
		return (COLORREF)SendMessage(SB_SETBKCOLOR, 0L, (LPARAM)clrBk);
	}
	
	BOOL GetUnicodeFormat() 
	{
		return (BOOL)SendMessage(SB_GETUNICODEFORMAT, 0L, 0L);
	}
	
	BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
	{
		return (BOOL)SendMessage(SB_SETUNICODEFORMAT, bUnicode, 0L);
	}

	void GetTipText(int nPane, LPTSTR lpstrText, int nSize) 
	{
		 if(nPane < 256)
			SendMessage(SB_GETTIPTEXT, MAKEWPARAM(nPane, nSize), (LPARAM)lpstrText);
	}
	
	void SetTipText(int nPane, LPCTSTR lpstrText)
	{
		
		if(nPane < 256)
			SendMessage(SB_SETTIPTEXT, nPane, (LPARAM)lpstrText);
	}

#endif 


	

	BOOL GetBorders(int* pBorders) 
	{
		return (BOOL)SendMessage(SB_GETBORDERS, 0L, (LPARAM)pBorders);
	}
	

	void SetIndicators(int nArray[],int nIDCount)
	{
		SendMessage(SB_SETPARTS, nIDCount, (LPARAM)nArray);
	}
	
	
	BOOL GetPaneRect(int nIndex,CRect* rc)
	{
		RECT lpRect;
		if (nIndex < 256)
		{
			SendMessage(SB_GETRECT, nIndex, (LPARAM) &lpRect);
			rc->CopyRect(&lpRect);
			return TRUE;
		}
		return FALSE;
	}

	int GetNumPanels()
	{
		return SendMessage(SB_GETPARTS, 0L, 0);
	}

	int GetParts(int nIndex, int* pParts) 
	{
		return (int)SendMessage(SB_GETPARTS, nIndex, (LPARAM)pParts);
	}
	
	BOOL SetParts(int nIndex, int* pWidths)
	{
		return (BOOL)SendMessage(SB_SETPARTS, nIndex, (LPARAM)pWidths);
	}
	
	//---------------------------------------------------
	int GetTextLength(int nIndex, int* pType = NULL) 
	{
		DWORD dwRet;
		if(nIndex < 256)
			dwRet = (DWORD)SendMessage(SB_GETTEXTLENGTH, (WPARAM)nIndex, 0L);
		if (pType != NULL)
			*pType = (int)(short)HIWORD(dwRet);
		return (int)(short)LOWORD(dwRet);
	}

	int GetText(int nIndex, LPTSTR lpszText, int* pType = NULL) 
	{
		DWORD dwRet;
		if(nIndex < 256)
			dwRet = (DWORD)SendMessage(SB_GETTEXT, (WPARAM)nIndex, (LPARAM)lpszText);
		if(pType != NULL)
			*pType = (int)(short)HIWORD(dwRet);
		return (int)(short)LOWORD(dwRet);
	}

	BOOL SetPaneText(int nIndex,LPCTSTR plszNewText,int nType=0 )
	{
		if (nIndex < 256)
			return (BOOL)SendMessage(SB_SETTEXT, nIndex| nType, (LPARAM)plszNewText);
		return FALSE;
	}

	//---------------------------------------------------
	
	
	void SetMinHeight(int nMin)
	{
		SendMessage(SB_SETMINHEIGHT, nMin, 0L);
	}
	
	BOOL SetSimple(BOOL bSimple = TRUE)
	{
		return (BOOL)SendMessage(SB_SIMPLE, bSimple, 0L);
	}
	
	BOOL IsSimple() 
	{
		return (BOOL)SendMessage( SB_ISSIMPLE, 0L, 0L);
	}

	virtual void Size()
	{
		SendMessage(WM_SIZE,0L,0);
	}


};



/*
 *  CToolBarCtrl
 *
 **/

class CToolBarCtrl : public ComControlEX
{
	
	struct TBData
	{
		WORD wVersion;
		WORD wWidth;
		WORD wHeight;
		WORD wItemCount;
		WORD* items()
			{ return (WORD*)(this+1); }
	};
		
public:
	CImageCtrl	cImgCtrl;
	CToolBarCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}
	~CToolBarCtrl(){cImgCtrl.Destroy();};
	COLORREF cl;
public:

	BOOL Create(HWND hWndParent,UINT uID=BASE_TOOLBAR_CLASS, 
			DWORD dwStyle=WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NORESIZE | CCS_NOPARENTALIGN | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT|TBSTYLE_LIST)
	{		
		BOOL bRes = CreateEx(0L, TOOLBARCLASSNAME, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		cl=CDrawLayer::GetRGBColorXP();
		SubclassWnd(GetSafeHwnd());
		return bRes;
	}


	BOOL AddTrueColor(UINT uTb, UINT uTbType) 
	{
		
		if (!cImgCtrl.CreateColor(uTb))
			return FALSE;
		
		//SetImageList(cImgCtrl.GetImageHandle());
		//SendMessage(uTbType, 0, (LPARAM)cImgCtrl.GetImageHandle());
	
		return TRUE;
	}

	
	BOOL IsButtonEnabled(int nID) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_ISBUTTONENABLED, nID, 0L);
	}
	BOOL IsButtonChecked(int nID) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_ISBUTTONCHECKED, nID, 0L);
	}
	BOOL IsButtonPressed(int nID) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_ISBUTTONPRESSED, nID, 0L);
	}
	BOOL IsButtonHidden(int nID) 
	{
		ASSERT(m_hWnd);
		return(BOOL) SendMessage( TB_ISBUTTONHIDDEN, nID, 0L);
	}
	BOOL IsButtonIndeterminate(int nID) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_ISBUTTONINDETERMINATE, nID, 0L);
	}
	int GetState(int nID) 
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_GETSTATE, nID, 0L);
	}
	BOOL SetState(int nID, UINT nState)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETSTATE, nID, MAKELPARAM(nState, 0));
	}
	BOOL GetButton(int nIndex, LPTBBUTTON lpButton) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_GETBUTTON, nIndex, (LPARAM)lpButton);
	}
	int GetButtonCount() 
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_BUTTONCOUNT, 0L, 0L);
	}
	BOOL GetItemRect(int nIndex, LPRECT lpRect) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_GETITEMRECT, nIndex, (LPARAM)lpRect);
	}
	void SetButtonStructSize(int nSize = sizeof(TBBUTTON))
	{
		ASSERT(m_hWnd);
		SendMessage( TB_BUTTONSTRUCTSIZE, nSize, 0L);
	}
	BOOL SetButtonSize(SIZE size)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETBUTTONSIZE, 0L, MAKELPARAM(size.cx, size.cy));
	}
	BOOL SetButtonSize(int cx, int cy)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETBUTTONSIZE, 0L, MAKELPARAM(cx, cy));
	}
	BOOL SetBitmapSize(SIZE size)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETBITMAPSIZE, 0L, MAKELPARAM(size.cx, size.cy));
	}
	BOOL SetBitmapSize(int cx, int cy)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETBITMAPSIZE, 0L, MAKELPARAM(cx, cy));
	}
	CToolTipCtrl GetToolTips() 
	{
		return CToolTipCtrl((HWND)SendMessage( TB_GETTOOLTIPS, 0L, 0L));
	}
	void SetToolTips(HWND hWndToolTip)
	{
		ASSERT(m_hWnd);
		SendMessage( TB_SETTOOLTIPS, (WPARAM)hWndToolTip, 0L);
	}
	void SetNotifyWnd(HWND hWnd)
	{
		ASSERT(m_hWnd);
		SendMessage( TB_SETPARENT, (WPARAM)hWnd, 0L);
	}
	int GetRows() 
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (int)SendMessage( TB_GETROWS, 0L, 0L);
	}
	void SetRows(int nRows, BOOL bLarger, LPRECT lpRect)
	{
		ASSERT(m_hWnd);
		SendMessage( TB_SETROWS, MAKELPARAM(nRows, bLarger), (LPARAM)lpRect);
	}
	BOOL SetCmdID(int nIndex, UINT nID)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETCMDID, nIndex, nID);
	}
	DWORD GetBitmapFlags() 
	{
		ASSERT(m_hWnd);
		return (DWORD)SendMessage( TB_GETBITMAPFLAGS, 0L, 0L);
	}
	int GetBitmap(int nID) 
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_GETBITMAP, nID, 0L);
	}
	int GetButtonText(int nID, LPTSTR lpstrText) 
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_GETBUTTONTEXT, nID, (LPARAM)lpstrText);
	}

	CImageCtrl GetImageList() 
	{
		if (!::IsWindow(m_hWnd)) return NULL;
		return CImageCtrl((HIMAGELIST)SendMessage( TB_GETIMAGELIST, 0L, 0L));
	}
	CImageCtrl SetImageList(HIMAGELIST hImageList)
	{
		if (!::IsWindow(m_hWnd)) return NULL;
		return CImageCtrl((HIMAGELIST)SendMessage( TB_SETIMAGELIST, 0L, (LPARAM)hImageList));
	}
	CImageCtrl GetDisabledImageList() 
	{
		if (!::IsWindow(m_hWnd)) return NULL;
		return CImageCtrl((HIMAGELIST)SendMessage( TB_GETDISABLEDIMAGELIST, 0L, 0L));
	}
	CImageCtrl SetDisabledImageList(HIMAGELIST hImageList)
	{
		if (!::IsWindow(m_hWnd)) return NULL;
		return CImageCtrl((HIMAGELIST)SendMessage( TB_SETDISABLEDIMAGELIST, 0L, (LPARAM)hImageList));
	}
	CImageCtrl GetHotImageList() 
	{
		if (!::IsWindow(m_hWnd)) return NULL;
		return CImageCtrl((HIMAGELIST)SendMessage( TB_GETHOTIMAGELIST, 0L, 0L));
	}
	CImageCtrl SetHotImageList(HIMAGELIST hImageList)
	{
		if (!::IsWindow(m_hWnd)) return NULL;
		return CImageCtrl((HIMAGELIST)SendMessage( TB_SETHOTIMAGELIST, 0L, (LPARAM)hImageList));
	}
	DWORD GetStyle() 
	{
		ASSERT(m_hWnd);
		return (DWORD)SendMessage( TB_GETSTYLE, 0L, 0L);
	}
	void SetStyle(DWORD dwStyle)
	{
		ASSERT(m_hWnd);
		SendMessage( TB_SETSTYLE, 0L, dwStyle);
	}
	DWORD GetButtonSize() 
	{
		ASSERT(m_hWnd);
		return (DWORD)SendMessage( TB_GETBUTTONSIZE, 0L, 0L);
	}
	void GetButtonSize(SIZE& size) 
	{
		ASSERT(m_hWnd);
		DWORD dwRet = (DWORD)SendMessage( TB_GETBUTTONSIZE, 0L, 0L);
		size.cx = LOWORD(dwRet);
		size.cy = HIWORD(dwRet);
	}
	BOOL GetRect(int nID, LPRECT lpRect) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_GETRECT, nID, (LPARAM)lpRect);
	}
	int GetTextRows() 
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_GETTEXTROWS, 0L, 0L);
	}
	BOOL SetButtonWidth(int cxMin, int cxMax)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETBUTTONWIDTH, 0L, MAKELPARAM(cxMin, cxMax));
	}
	BOOL SetIndent(int nIndent)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETINDENT, nIndent, 0L);
	}
	BOOL SetMaxTextRows(int nMaxTextRows)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETMAXTEXTROWS, nMaxTextRows, 0L);
	}

#if (_WIN32_IE >= 0x0400)
	BOOL GetAnchorHighlight() 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_GETANCHORHIGHLIGHT, 0L, 0L);
	}
	BOOL SetAnchorHighlight(BOOL bEnable = TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETANCHORHIGHLIGHT, bEnable, 0L);
	}

	void GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) 
	{
		
		ASSERT(::IsWindow(m_hWnd));

		TBBUTTON button;
		GetButton(nIndex, &button);
		nID = button.idCommand;
		nStyle = MAKELONG(button.fsStyle, button.fsState);
		iImage = button.iBitmap;
	}

	
	int GetButtonInfo(int nID, LPTBBUTTONINFO lptbbi) 
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (int)SendMessage( TB_GETBUTTONINFO, nID, (LPARAM)lptbbi);
	}
	BOOL SetButtonInfo(int nID, LPTBBUTTONINFO lptbbi)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETBUTTONINFO, nID, (LPARAM)lptbbi);
	}
	int GetHotItem() 
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (int)SendMessage( TB_GETHOTITEM, 0L, 0L);
	}
	int SetHotItem(int nItem)
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (int)SendMessage( TB_SETHOTITEM, nItem, 0L);
	}
	BOOL IsButtonHighlighted(int nButtonID) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_ISBUTTONHIGHLIGHTED, nButtonID, 0L);
	}
	DWORD SetDrawTextFlags(DWORD dwMask, DWORD dwFlags)
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (DWORD)SendMessage( TB_SETDRAWTEXTFLAGS, dwMask, dwFlags);
	}
	BOOL GetColorScheme(LPCOLORSCHEME lpcs) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_GETCOLORSCHEME, 0L, (LPARAM)lpcs);
	}
	void SetColorScheme(LPCOLORSCHEME lpcs)
	{
		ASSERT(m_hWnd);
		SendMessage( TB_SETCOLORSCHEME, 0L, (LPARAM)lpcs);
	}
	DWORD GetExtendedStyle() 
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (DWORD)SendMessage( TB_GETEXTENDEDSTYLE, 0L, 0L);
	}
	DWORD SetExtendedStyle(DWORD dwStyle)
	{
		if (!::IsWindow(m_hWnd)) return -1;
		return (DWORD)SendMessage( TB_SETEXTENDEDSTYLE, 0L, dwStyle);
	}
	void GetInsertMark(LPTBINSERTMARK lptbim) 
	{
		ASSERT(m_hWnd);
		SendMessage( TB_GETINSERTMARK, 0L, (LPARAM)lptbim);
	}
	void SetInsertMark(LPTBINSERTMARK lptbim)
	{
		ASSERT(m_hWnd);
		SendMessage( TB_SETINSERTMARK, 0L, (LPARAM)lptbim);
	}
	COLORREF GetInsertMarkColor() 
	{
		if (!::IsWindow(m_hWnd)) return RGB(0L,0L,0);
		return (COLORREF)SendMessage( TB_GETINSERTMARKCOLOR, 0L, 0L);
	}
	COLORREF SetInsertMarkColor(COLORREF clr)
	{
		if (!::IsWindow(m_hWnd)) return RGB(0L,0L,0);
		return (COLORREF)SendMessage( TB_SETINSERTMARKCOLOR, 0L, (LPARAM)clr);
	}
	BOOL GetMaxSize(LPSIZE lpSize) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_GETMAXSIZE, 0L, (LPARAM)lpSize);
	}
	void GetPadding(LPSIZE lpSizePadding) 
	{
		ASSERT(m_hWnd);
		DWORD dwRet = (DWORD)SendMessage( TB_GETPADDING, 0L, 0L);
		lpSizePadding->cx = LOWORD(dwRet);
		lpSizePadding->cy = HIWORD(dwRet);
	}
	void SetPadding(int cx, int cy, LPSIZE lpSizePadding = NULL)
	{
		ASSERT(m_hWnd);
		DWORD dwRet = (DWORD)SendMessage( TB_SETPADDING, 0L, MAKELPARAM(cx, cy));
		if(lpSizePadding != NULL)
		{
			lpSizePadding->cx = LOWORD(dwRet);
			lpSizePadding->cy = HIWORD(dwRet);
		}
	}
	BOOL GetUnicodeFormat() 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_GETUNICODEFORMAT, 0L, 0L);
	}
	BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_SETUNICODEFORMAT, bUnicode, 0L);
	}
#endif 

#if (_WIN32_IE >= 0x0500)
	int GetString(int nString, LPTSTR lpstrString, int cchMaxLen) 
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_GETSTRING, MAKEWPARAM(cchMaxLen, nString), (LPARAM)lpstrString);
	}
	
#endif 

#if (_WIN32_WINNT >= 0x0501)
	void GetMetrics(LPTBMETRICS lptbm) 
	{
		ASSERT(m_hWnd);
		SendMessage( TB_GETMETRICS, 0L, (LPARAM)lptbm);
	}
	void SetMetrics(LPTBMETRICS lptbm)
	{
		ASSERT(m_hWnd);
		SendMessage( TB_SETMETRICS, 0L, (LPARAM)lptbm);
	}
	void SetWindowTheme(LPCWSTR lpstrTheme)
	{
		ASSERT(m_hWnd);
		SendMessage( TB_SETWINDOWTHEME, 0L, (LPARAM)lpstrTheme);
	}
#endif 


	BOOL EnableButton(int nID, BOOL bEnable = TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_ENABLEBUTTON, nID, MAKELPARAM(bEnable, 0));
	}
	BOOL CheckButton(int nID, BOOL bCheck = TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_CHECKBUTTON, nID, MAKELPARAM(bCheck, 0));
	}
	BOOL PressButton(int nID, BOOL bPress = TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_PRESSBUTTON, nID, MAKELPARAM(bPress, 0));
	}
	BOOL HideButton(int nID, BOOL bHide = TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_HIDEBUTTON, nID, MAKELPARAM(bHide, 0));
	}
	BOOL Indeterminate(int nID, BOOL bIndeterminate = TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_INDETERMINATE, nID, MAKELPARAM(bIndeterminate, 0));
	}
	
	int AddBitmap(int nNumButtons, HBITMAP hBitmap)
	{
		ASSERT(m_hWnd);
		TBADDBITMAP tbab;
		tbab.hInst = theApp->GetInstance();
		tbab.nID = (UINT_PTR)hBitmap;
		return (int)SendMessage( TB_ADDBITMAP, (WPARAM)nNumButtons, (LPARAM)&tbab);
	}
	BOOL AddButtons(int nNumButtons, LPTBBUTTON lpButtons)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_ADDBUTTONS, nNumButtons, (LPARAM)lpButtons);
	}
	BOOL InsertButton(int nIndex, LPTBBUTTON lpButton)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_INSERTBUTTON, nIndex, (LPARAM)lpButton);
	}
	BOOL DeleteButton(int nIndex)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_DELETEBUTTON, nIndex, 0L);
	}
	UINT CommandToIndex(UINT nID) 
	{
		ASSERT(m_hWnd);
		return (UINT)SendMessage( TB_COMMANDTOINDEX, nID, 0L);
	}
	void SaveState(HKEY hKeyRoot, LPCTSTR lpszSubKey, LPCTSTR lpszValueName)
	{
		ASSERT(m_hWnd);
		TBSAVEPARAMS tbs;
		tbs.hkr = hKeyRoot;
		tbs.pszSubKey = lpszSubKey;
		tbs.pszValueName = lpszValueName;
		SendMessage( TB_SAVERESTORE, (WPARAM)TRUE, (LPARAM)&tbs);
	}
	void RestoreState(HKEY hKeyRoot, LPCTSTR lpszSubKey, LPCTSTR lpszValueName)
	{
		ASSERT(m_hWnd);
		TBSAVEPARAMS tbs;
		tbs.hkr = hKeyRoot;
		tbs.pszSubKey = lpszSubKey;
		tbs.pszValueName = lpszValueName;
		SendMessage( TB_SAVERESTORE, (WPARAM)FALSE, (LPARAM)&tbs);
	}
	void Customize()
	{
		ASSERT(m_hWnd);
		SendMessage( TB_CUSTOMIZE, 0L, 0L);
	}
	int AddString(UINT nStringID)
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_ADDSTRING, (WPARAM)theApp->GetInstance(), (LPARAM)nStringID);
	}
	int AddStrings(LPCTSTR lpszStrings)
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_ADDSTRING, 0L, (LPARAM)lpszStrings);
	}
	void AutoSize()
	{
		ASSERT(m_hWnd);
		SendMessage( TB_AUTOSIZE, 0L, 0L);
	}

	BOOL ChangeBitmap(int nID, int nBitmap)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_CHANGEBITMAP, nID, MAKELPARAM(nBitmap, 0));
	}
	int LoadImages(int nBitmapID)
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_LOADIMAGES, nBitmapID, (LPARAM)theApp->GetInstance());
	}
	int LoadStdImages(int nBitmapID)
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_LOADIMAGES, nBitmapID, (LPARAM)HINST_COMMCTRL);
	}
	BOOL ReplaceBitmap(LPTBREPLACEBITMAP ptbrb)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_REPLACEBITMAP, 0L, (LPARAM)ptbrb);
	}

#if (_WIN32_IE >= 0x0400)
	int HitTest(LPPOINT lpPoint)
	{
		ASSERT(m_hWnd);
		return (int)SendMessage( TB_HITTEST, 0L, (LPARAM)lpPoint);
	}
	BOOL InsertMarkHitTest(LPPOINT lpPoint, LPTBINSERTMARK lptbim)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_INSERTMARKHITTEST, (WPARAM)lpPoint, (LPARAM)lptbim);
	}
	BOOL InsertMarkHitTest(int x, int y, LPTBINSERTMARK lptbim)
	{
		ASSERT(m_hWnd);
		POINT pt = { x, y };
		return (BOOL)SendMessage( TB_INSERTMARKHITTEST, (WPARAM)&pt, (LPARAM)lptbim);
	}
	BOOL MapAccelerator(TCHAR chAccel, int& nID) 
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_MAPACCELERATOR, (WPARAM)chAccel, (LPARAM)&nID);
	}
	BOOL MarkButton(int nID, BOOL bHighlight = TRUE)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_MARKBUTTON, nID, MAKELPARAM(bHighlight, 0));
	}
	BOOL MoveButton(int nOldPos, int nNewPos)
	{
		ASSERT(m_hWnd);
		return (BOOL)SendMessage( TB_MOVEBUTTON, nOldPos, nNewPos);
	}


	
	BOOL CreateCombo(CComboBoxExt* pControl,UINT nID,int iSize,DWORD dwStyle);
	
	
#endif 
	void OnSize()
	{
		AutoSize();
	}

	//----------------------------------------
	//This funcion load the toolbar resource
	//----------------------------------------
	BOOL  LoadToolBar(UINT nIDResource)
	{
		
		BOOL bInitialSeparator=FALSE;
		HRSRC hRsrc = theApp->FindResourceToolBar(nIDResource);
		if (hRsrc == NULL)
			return FALSE;
	
		HGLOBAL hGlobal = theApp->LoadResource(hRsrc);
		if (hGlobal == NULL)
			return FALSE;
	
		TBData* pData = (TBData*)::LockResource(hGlobal);
		if (pData == NULL)
			return FALSE;
	
		if (pData->wVersion != 1)  
			return FALSE; 
	
		WORD* pItems = pData->items();
		int nItems = pData->wItemCount + (bInitialSeparator ? 1 : 0);
		TBBUTTON *pTBBtn = (TBBUTTON*)_alloca(nItems * sizeof(TBBUTTON));
	
		
		if(bInitialSeparator)
		{
			pTBBtn[0].iBitmap = 4;
			pTBBtn[0].idCommand = 0;
			pTBBtn[0].fsState = 0;
			pTBBtn[0].fsStyle = TBSTYLE_SEP;
			pTBBtn[0].dwData = 0;
			pTBBtn[0].iString = 0;
		}
	
		int nBmp = 0;
		for(int i = 0L, j = bInitialSeparator ? 1 : 0; i < pData->wItemCount; i++, j++)
		{
			if(pItems[i] != 0)
			{
				pTBBtn[j].iBitmap = nBmp++;
				pTBBtn[j].idCommand = pItems[i];
				pTBBtn[j].fsState = TBSTATE_ENABLED;
				pTBBtn[j].fsStyle = TBSTYLE_BUTTON;
				pTBBtn[j].dwData = 0;
				pTBBtn[j].iString = 0;
			}
			else
			{
				pTBBtn[j].iBitmap = 8;
				pTBBtn[j].idCommand = 0;
				pTBBtn[j].fsState = 0;
				pTBBtn[j].fsStyle = TBSTYLE_SEP;
				pTBBtn[j].dwData = 0;
				pTBBtn[j].iString = 0;
			}
		}
		
		SetButtonStructSize(sizeof(TBBUTTON));
		AddBitmap(nItems, (HBITMAP)nIDResource);
		AddButtons(nItems, pTBBtn);
		SetBitmapSize(pData->wWidth,pData->wHeight);
		SetButtonSize(pData->wWidth + 7,pData->wHeight);
		AutoSize();
	
		return TRUE;
	}

/*	void AddButtonText(UINT nID, CString szText)
	 {
	  TBBUTTONINFO tbi = { 0 };
	  tbi.cbSize = sizeof(TBBUTTONINFO),
	  tbi.dwMask  = TBIF_STYLE;
	  GetButtonInfo(nID, &tbi);
	  tbi.dwMask = TBIF_STYLE | TBIF_TEXT;
	  tbi.fsStyle |= TBSTYLE_AUTOSIZE;
	  tbi.pszText = (LPTSTR) (LPCTSTR) szText;
	  SetButtonInfo(nID, &tbi);
	 }
*/	
	 void AddDropDownButton(UINT nID)
	 {
	   SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS); 
	   TBBUTTONINFO tbi = { 0 };
	   tbi.cbSize  = sizeof(TBBUTTONINFO);
	   tbi.dwMask  = TBIF_STYLE;
	   GetButtonInfo(nID, &tbi);
	   tbi.fsStyle |= TBSTYLE_DROPDOWN;
	   SetButtonInfo(nID, &tbi);
   }


};


/*
 *  CRebarCtrl
 *
 **/

class CReBarCtrl : public ComControlEX
{
public:

	CReBarCtrl(HWND hWnd=NULL){m_hWnd=hWnd;}

										
	BOOL Create(HWND hWndParent,DWORD dwStyle=WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | RBS_VARHEIGHT | RBS_BANDBORDERS | RBS_AUTOSIZE|RBS_BANDBORDERS ,
			UINT uID=60000)
	{		

		BOOL bRes = CreateEx(0L, REBARCLASSNAME, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		REBARINFO rbi;
		rbi.cbSize = sizeof(REBARINFO);
		rbi.fMask  = 0;
		if(!::SendMessage(m_hWnd, RB_SETBARINFO, 0L, (LPARAM)&rbi)) //SetBarInfo(&rbi)
		{
			DestroyWindow(m_hWnd);
			return NULL;
		}
		return bRes;
	}


public:
	
	BOOL AddBar(CToolBarCtrl* pToolBar, int nID, LPTSTR lpstrTitle = NULL,
								 BOOL bNewRow = FALSE, DWORD dwStyle= RBBS_GRIPPERALWAYS  )
	{
		
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(::IsWindow(pToolBar->GetSafeHwnd()));

		int nNumButton = pToolBar->GetButtonCount();
		
		REBARBANDINFO rbBand;
		rbBand.cbSize = sizeof(REBARBANDINFO);
		rbBand.fStyle = dwStyle|RBBS_VARIABLEHEIGHT ;
		BOOL bRet;
		SIZE sz;
		bRet = (BOOL) pToolBar->GetMaxSize(&sz);
	
		#if (_WIN32_IE >= 0x0400)
			rbBand.fMask = RBBIM_CHILD | RBBIM_IDEALSIZE |RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID  ;
		#else
			rbBand.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE |RBBIM_IDEALSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE;
		#endif 
		
		if(lpstrTitle != NULL)
			rbBand.fMask |= RBBIM_TEXT;
				
		if(bNewRow)
			rbBand.fStyle |= RBBS_BREAK;

		rbBand.lpText = lpstrTitle;
		rbBand.hwndChild = pToolBar->GetSafeHwnd();
		rbBand.wID = nID;
		rbBand.cxMinChild = sz.cx*0.40;
		//rbBand.fStyle |= RBBS_CHILDEDGE;
		rbBand.cxHeader=1;
		

		
		CRect rc;
		if(nNumButton > 0)
		{
			
			bRet = (BOOL) pToolBar->GetItemRect(nNumButton - 1, rc);
			
			ASSERT(bRet);
			rbBand.cx =  sz.cx;
			rbBand.cyMinChild = rc.Height();
		//	rbBand.cxMinChild = 4;
			rbBand.cyMaxChild= sz.cx;
			
		
		}
		else	
		{
			bRet = ::GetWindowRect(pToolBar->GetSafeHwnd(), rc);
			if(bRet)
			{
				rbBand.cx = rc.Width();
				//rbBand.cxMinChild = rc.Width();
				rbBand.cyMinChild = rc.Height();
				rbBand.cyMaxChild= rc.Width();
			}
		}

		#if (_WIN32_IE >= 0x0400)
			rbBand.cxIdeal = rbBand.cx;
		#endif 
			LRESULT lRes = (BOOL)InsertBand(&rbBand);

		return (BOOL)(lRes !=0);
		
	}

	UINT GetBandCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)::SendMessage(m_hWnd, RB_GETBANDCOUNT, 0, 0L);
	}
	BOOL GetBandInfo(int nBand, LPREBARBANDINFO lprbbi) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_GETBANDINFO, nBand, (LPARAM)lprbbi);
	}
	BOOL SetBandInfo(int nBand, LPREBARBANDINFO lprbbi)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_SETBANDINFO, nBand, (LPARAM)lprbbi);
	}
	BOOL GetBarInfo(LPREBARINFO lprbi) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_GETBARINFO, 0, (LPARAM)lprbi);
	}
	BOOL SetBarInfo(LPREBARINFO lprbi)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_SETBARINFO, 0, (LPARAM)lprbi);
	}
	UINT GetRowCount() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)::SendMessage(m_hWnd, RB_GETROWCOUNT, 0, 0L);
	}
	UINT GetRowHeight(int nBand) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)::SendMessage(m_hWnd, RB_GETROWHEIGHT, nBand, 0L);
	}

	COLORREF GetTextColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)::SendMessage(m_hWnd, RB_GETTEXTCOLOR, 0, 0L);
	}
	COLORREF SetTextColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)::SendMessage(m_hWnd, RB_SETTEXTCOLOR, 0, (LPARAM)clr);
	}
	COLORREF GetBkColor() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)::SendMessage(m_hWnd, RB_GETBKCOLOR, 0, 0L);
	}
	COLORREF SetBkColor(COLORREF clr)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (COLORREF)::SendMessage(m_hWnd, RB_SETBKCOLOR, 0, (LPARAM)clr);
	}
	UINT GetBarHeight() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (UINT)::SendMessage(m_hWnd, RB_GETBARHEIGHT, 0, 0L);
	}
	BOOL GetRect(int nBand, LPRECT lpRect) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_GETRECT, nBand, (LPARAM)lpRect);
	}
	CToolTipCtrl GetToolTips() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return CToolTipCtrl((HWND)::SendMessage(m_hWnd, RB_GETTOOLTIPS, 0, 0L));
	}
	void SetToolTips(HWND hwndToolTip)
	{
		ASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, RB_SETTOOLTIPS, (WPARAM)hwndToolTip, 0L);
	}
	void GetBandBorders(int nBand, LPRECT lpRect) 
	{
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(lpRect != NULL);
		::SendMessage(m_hWnd, RB_GETBANDBORDERS, nBand, (LPARAM)lpRect);
	}
	BOOL GetColorScheme(LPCOLORSCHEME lpColorScheme) 
	{
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(lpColorScheme != NULL);
		return (BOOL)::SendMessage(m_hWnd, RB_GETCOLORSCHEME, 0, (LPARAM)lpColorScheme);
	}
	void SetColorScheme(LPCOLORSCHEME lpColorScheme)
	{
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(lpColorScheme != NULL);
		::SendMessage(m_hWnd, RB_SETCOLORSCHEME, 0, (LPARAM)lpColorScheme);
	}
	HPALETTE GetPalette() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HPALETTE)::SendMessage(m_hWnd, RB_GETPALETTE, 0, 0L);
	}
	HPALETTE SetPalette(HPALETTE hPalette)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (HPALETTE)::SendMessage(m_hWnd, RB_SETPALETTE, 0, (LPARAM)hPalette);
	}
	BOOL GetUnicodeFormat() 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_GETUNICODEFORMAT, 0, 0L);
	}
	BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_SETUNICODEFORMAT, bUnicode, 0L);
	}

	BOOL InsertBand(LPREBARBANDINFO lprbbi,int nBand=-1 )
	{
		ASSERT(::IsWindow(m_hWnd));
		lprbbi->cbSize = sizeof(REBARBANDINFO);
		return (BOOL)::SendMessage(m_hWnd, RB_INSERTBAND, nBand, (LPARAM)lprbbi);
	}
	BOOL DeleteBand(int nBand)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_DELETEBAND, nBand, 0L);
	}
	CWin SetNotifyWnd(HWND hWnd)
	{
		ASSERT(::IsWindow(m_hWnd));
		return CWin((HWND)::SendMessage(m_hWnd, RB_SETPARENT, (WPARAM)hWnd, 0L));
	}

	void BeginDrag(int nBand, DWORD dwPos)
	{
		ASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, RB_BEGINDRAG, nBand, dwPos);
	}
	void BeginDrag(int nBand, int xPos, int yPos)
	{
		ASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, RB_BEGINDRAG, nBand, MAKELPARAM(xPos, yPos));
	}
	void EndDrag()
	{
		ASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, RB_ENDDRAG, 0, 0L);
	}
	void DragMove(DWORD dwPos)
	{
		ASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, RB_DRAGMOVE, 0, dwPos);
	}
	void DragMove(int xPos, int yPos)
	{
		ASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, RB_DRAGMOVE, 0, MAKELPARAM(xPos, yPos));
	}
	void MaximizeBand(int nBand)
	{
		ASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, RB_MAXIMIZEBAND, nBand, 0L);
	}
	void MinimizeBand(int nBand)
	{
		ASSERT(::IsWindow(m_hWnd));
		::SendMessage(m_hWnd, RB_MINIMIZEBAND, nBand, 0L);
	}
	BOOL SizeToRect(LPRECT lpRect)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_SIZETORECT, 0, (LPARAM)lpRect);
	}
	int IdToIndex(UINT uBandID) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)::SendMessage(m_hWnd, RB_IDTOINDEX, uBandID, 0L);
	}
	int HitTest(LPRBHITTESTINFO lprbht) 
	{
		ASSERT(::IsWindow(m_hWnd));
		return (int)::SendMessage(m_hWnd, RB_HITTEST, 0, (LPARAM)lprbht);
	}
	BOOL ShowBand(int nBand, BOOL bShow)
	{
		ASSERT(::IsWindow(m_hWnd));
		return (BOOL)::SendMessage(m_hWnd, RB_SHOWBAND, nBand, bShow);
	}
	BOOL MoveBand(int nBand, int nNewPos)
	{
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(nNewPos >= 0 && nNewPos <= ((int)GetBandCount() - 1));
		return (BOOL)::SendMessage(m_hWnd, RB_MOVEBAND, nBand, nNewPos);
	}

	int  HwndToIndex(HWND hWnd)
	{
		
		REBARBANDINFO rbbi;
		rbbi.cbSize = sizeof(rbbi);
		rbbi.fMask = RBBIM_CHILD|RBBIM_STYLE;
		int nCount = (int) ::SendMessage(GetSafeHwnd(), RB_GETBANDCOUNT, 0, 0L);
		for( int i = 0; i < nCount; i++ ) {
			BOOL bRet = (BOOL)::SendMessage(GetSafeHwnd(), RB_GETBANDINFO, i, (LPARAM) &rbbi);
			if (rbbi.hwndChild==hWnd)
				return i;
		}
		return -1;

	}
	
	LRESULT OnShowBand(HWND hWnd)
	{
		int i=HwndToIndex(hWnd);
		REBARBANDINFO rbbi;
		rbbi.cbSize = sizeof(rbbi);
		rbbi.fMask = RBBIM_CHILD|RBBIM_STYLE;
		BOOL bRet = (BOOL)::SendMessage(GetSafeHwnd(), RB_GETBANDINFO, i, (LPARAM) &rbbi);
		CWin* pBar = reinterpret_cast<CWin*>(rbbi.hwndChild);
	
		BOOL bIsBandVisible= !(rbbi.fStyle & RBBS_HIDDEN);
		ShowBand(i, !bIsBandVisible);
		return 1;
	}


};



/*
 *
 *  Common Controls Extend 
 *
 *
 *
 ****/

class CButtonInfo : public TBBUTTONINFO
{
	int iButton;
	CToolBarCtrl* pTb;
	TCHAR szText[64];
	public:
		CButtonInfo(CToolBarCtrl* pToolbar,  int NumButton)
		{
			ASSERT(pTb->GetSafeHwnd());
			pTb=pToolbar;
			iButton=NumButton;
			memset(this,0x00,sizeof(TBBUTTONINFO));	   
			cbSize = sizeof(TBBUTTONINFO);
			dwMask = TBIF_TEXT | TBIF_STYLE | TBIF_STATE | TBIF_IMAGE;
			pszText = szText;
			cchText = (sizeof(szText) / sizeof(TCHAR)) - 1;
			pTb->GetButtonInfo(iButton, this);
			
	      	}
		~CButtonInfo()
		{

		}
	public:	
		BOOL IsChecked(){ return (fsState & TBSTATE_CHECKED) != 0;}
		BOOL IsPressed(){ return (fsState & TBSTATE_PRESSED )!= 0;}
		BOOL IsEnabled(){ return (fsState & TBSTATE_ENABLED)!= 0;}
		BOOL IsHidden() {return (fsState & TBSTATE_HIDDEN)!= 0;}
		BOOL IsWrap() { return (fsState & TBSTATE_WRAP)!= 0;}
		BOOL IsEllipses() { return (fsState & TBSTATE_ELLIPSES)!= 0;}
		BOOL IsMarked() { return (fsState & TBSTATE_MARKED)!= 0;}
		BOOL IsIndeterminate() { return (fsState & TBSTATE_INDETERMINATE)!= 0;}
		
		BOOL IsStyleFlat() { return (  fsStyle & TBSTYLE_FLAT)!= 0;}
		BOOL IsStyleList() { return (fsStyle & TBSTYLE_LIST )!= 0; }
		BOOL IsSeparator() {return (fsStyle & TBSTYLE_SEP )!= 0;}
		BOOL IsStyleCheck() {return (fsStyle & TBSTYLE_CHECK )!= 0;}
		BOOL IsStyleDropDown(){ return (fsStyle & TBSTYLE_DROPDOWN)!= 0;}
		BOOL IsImage() {return (BOOL)(iImage >= 0)!= 0; }
		
		LPCTSTR GetText()
		{
			if( ::lstrlen(szText) == 0 ) 
			     pTb->GetButtonText(iButton, szText);
			return (LPCTSTR)szText;
			
		}

		int GetID()
		{
			return idCommand;
		}
	
		int GetIndexImage()
		{
			return iImage;
		}
		CRect GetRect()
		{ 
			CRect rcBtn;
			pTb->GetItemRect(iButton,&rcBtn);
			return rcBtn;
		}
		
		CImageCtrl GetImageList()
		{
			return pTb->GetImageList();
		}	
		
		CSize GetButtonSize()
		{
			SIZE sz;
			pTb->GetButtonSize(sz);
			return sz ;
		}
		
};


/*
 *
 *  CToolBarCtrlEx
 *
 ****/


class CToolBarCtrlEx : public CToolBarCtrl
{
	CFont m_cfont;
public:
	
	  CToolBarCtrlEx()
	  {
		//m_cfont.CreateFont(14,0,0,0,400,0,0,0,0,1,2,1,34,_T("Arial"));	
	  }
	
	  ~CToolBarCtrlEx(){}

public:
	  void DrawButton(LPNMTBCUSTOMDRAW lpNMCustomDraw)
	  {
	      CBrush cb;
		  CGDI dc(lpNMCustomDraw->nmcd.hdc);
		  cb.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
	      CButtonInfo cbt(this,lpNMCustomDraw->nmcd.dwItemSpec);
		  UINT uItemState = lpNMCustomDraw->nmcd.uItemState;
		  bool bSelected = (uItemState & CDIS_SELECTED || uItemState & CDIS_HOT || uItemState &CDIS_CHECKED) != 0;
		  #if (_WIN32_IE >= 0x0400)
			CRect rcBtn = lpNMCustomDraw->nmcd.rc;
		  #else //!(_WIN32_IE >= 0x0400)
			CRect rcBtn;
			GetItemRect(0, rcBtn);
		  #endif //!(_WIN32_IE >= 0x0400)
	      BOOL Over=FALSE;
	      if (bSelected)
		  if (cbt.IsSeparator() )
		  {
				if (!cbt.IsWrap())
				{
					CRect m_Separ;
					m_Separ=rcBtn;
					
					int nhalf=(m_Separ.Width()/2)-1;
					m_Separ.top-=1;
					m_Separ.left+=nhalf;
					m_Separ.right=m_Separ.left+1;
					m_Separ.bottom+=1;
					CBrush cbs;
					cbs.CreateSolidBrush(RGB(167, 167, 167));
					if (!(cbt.IsSeparator()  &&(cbt.GetID() !=0)))
						dc.FillRect(m_Separ,&cbs);
					cbs.DeleteObject();
				
				}
		  }
		  else if(cbt.IsEnabled())
		  {
			CPoint pt;
			GetCursorPos(&pt);
			ScreenToClient(&pt);
			CBrush cblu;
			if(!rcBtn.PtInRect(pt))
			{
				if (cbt.IsChecked())
				{
					dc.Draw3dRect(rcBtn,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
					rcBtn.DeflateRect(1,1);
					cblu.CreateSolidBrush(CDrawLayer::GetRGBFondoXP());
					dc.FillRect(rcBtn,&cblu);					
				}
				
			}
			else
			{
				Over=TRUE;
				dc.Draw3dRect(rcBtn,CDrawLayer::GetRGBMenu(),CDrawLayer::GetRGBMenu());
				rcBtn.DeflateRect(1,1);
				if (cbt.IsChecked())
				{
					cblu.CreateSolidBrush(CDrawLayer::GetRGBFondoXP());
					dc.FillRect(rcBtn,&cblu);					
				}
				else
				{
					
					if (cbt.IsPressed())
					{
						cblu.CreateSolidBrush(CDrawLayer::GetRGBPressBXP());
						dc.FillRect(rcBtn,&cblu);
					}
					else
					{
						cblu.CreateSolidBrush(cbt.IsPressed()?CDrawLayer::GetRGBPressBXP():CDrawLayer::GetRGBFondoXP());
						dc.FillRect(rcBtn,&cblu);					
					}
					if (cbt.IsStyleDropDown()) 
					{
						
						CRect rcCli=rcBtn;
						int dif=rcBtn.right-8;
						rcCli.left=dif+1;
						
						if (!cbt.IsPressed())
						{
							CPen Cp;
							Cp.CreatePen( PS_SOLID, 1, CDrawLayer::GetRGBCaptionXP());
							CPen oldPen= dc.SelectObject(&Cp);
							dc.MoveTo(dif,rcBtn.top);
							dc.LineTo(dif,rcBtn.bottom);
							dc.SelectObject(&oldPen);
							Cp.DeleteObject();
						}
						
					}
					
				}
					rcBtn.InflateRect(1,1);
			}
			cblu.DeleteObject();
		}

	  
		if (!cbt.IsSeparator())
		{
	
			
				HIMAGELIST hiImg = (HIMAGELIST)SendMessage (TB_GETIMAGELIST, 0, 0);
				HICON hIcon = ImageList_ExtractIcon (theApp->GetInstance(), hiImg,cbt.GetIndexImage());
				int cxIcon, cyIcon;
				ImageList_GetIconSize(hiImg, &cxIcon, &cyIcon);
				CSize sizeButton( cbt.GetButtonSize());
				CSize siImg=CSize(cxIcon,cyIcon);
				CPoint pti(rcBtn.left+4,rcBtn.top+4);
				LPSTR mszText= (LPSTR)cbt.GetText();
				//HFONT m_fontOld=dc.SelectFont(m_cfont);
				CBrush cbShadow;
				cbShadow.CreateSolidBrush(CDrawLayer::GetRGBColorShadow());
								
				if (cbt.IsEnabled())
				{
					if (cImgCtrl.GetImageHandle())
						cImgCtrl.Draw(cbt.GetIndexImage(),dc,pti,ILD_NORMAL);
					else
						ImageList_Draw(hiImg,cbt.GetIndexImage(),dc,pti.x,pti.y,ILD_NORMAL);
					if (lstrlen(mszText) > 0)
					{
						
						CRect m_rctext=rcBtn;
						m_rctext.left+=siImg.cx+4;
						m_rctext.bottom-=1;
						CSize szText=dc.GetTextExtent(mszText,lstrlen(mszText));
						pti.x= m_rctext.left+8;
						pti.y=(m_rctext.Height()/2)-4;
						dc.DrawState(pti,szText,mszText,DSS_MONO,TRUE,0,(HBRUSH)NULL);
					}
					
					
					
				}
				else
				{
					
					 dc.DrawState(pti,siImg,hIcon,DSS_MONO,&cbShadow);
					 CRect m_rctext=rcBtn;
					 m_rctext.left+=siImg.cx+4;
					 m_rctext.bottom-=1;
					 CSize szText=dc.GetTextExtent(mszText,lstrlen(mszText));
					 pti.x= m_rctext.left+2;
					 pti.y=(m_rctext.Height()/2)-1;
					 dc.DrawState(pti,szText,mszText,DSS_DISABLED,TRUE,0,(HBRUSH)NULL);
				}
				DestroyIcon (hIcon);
				cbShadow.DeleteObject();
			
		}

	
		




	 }

	/*void DrawArrow(CGDI* pDC,CRect m_rc)
	{
		int difh =m_rc.Height()-mHeight.y;
		difh/=2;
		
		m_rc.left=m_rc.right-GetDropDownWidth();
		m_imgArrow.Draw(pDC,0,CPoint(m_rc.left+2,m_rc.top+difh),ILD_TRANSPARENT);		
		
	}*/
	
	DWORD OnPrePaint(LPNMCUSTOMDRAW lpNMCustomDraw,BOOL &bNotify)
	 {
	      CGDI dc(lpNMCustomDraw->hdc);
	      CRect rc=lpNMCustomDraw->rc;
		  SIZE lpSize;
		  ::SendMessage( GetSafeHwnd(),TB_GETMAXSIZE, 0L,(LPARAM) &lpSize);
		  CRect rc1=rc;  	
		  /*if (rc1.Width() > lpSize.cx)
		  {
				rc1.left= (rc1.right- (rc1.Width() - lpSize.cx))+5;
				rc.right=rc1.left;	
		  }*/
			CGradient M(CSize(rc.Width(),rc.Height()));	
			M.PrepareVertical(&dc);
			M.Draw(&dc,0,0,0,0,rc.Width(),rc.Height(),SRCCOPY);
			
		  return CDRF_NOTIFYITEMDRAW;  
	 }
	
	
	 DWORD OnItemPrePaint(LPNMCUSTOMDRAW lpNMCustomDraw,BOOL &bNotify)
	 {
	     
	      DrawButton((LPNMTBCUSTOMDRAW) lpNMCustomDraw );
	      return CDRF_SKIPDEFAULT;
	 }


	 
	

};


/*
 *
 *  CStatusCtrlEx
 *
 ****/


class CStatusCtrlEx: public CStatusCtrl
{

	enum Style{DEVSTUDIO=0,OFFICE=1};
	CFont m_cfont;
	Style m_Style;
public:

	CStatusCtrlEx()
	{
		m_Style=DEVSTUDIO;
		m_cfont.CreateFont(14,0,0,0,400,0,0,0,0,1,2,1,34,"Arial");
	}

	~CStatusCtrlEx()
	{
		m_cfont.DeleteObject();
	}

public:
	
	void SetStyle(Style nStyle)
	{
		m_Style=nStyle;
	}

	BOOL OnPaint(HDC hDC)
	{
		CRect rcClient,rcTemp;
		CBrush cb;
		CPaintDC dc(GetSafeHwnd()); 
		GetClientRect(&rcClient);
		cb.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
		rcTemp=rcClient;
		CGDI		MemDC;
		CBitmap		m_BitmapMemDC;
		MemDC.CreateCompatibleDC(dc.m_hDC);
		m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,rcClient.Width(),rcClient.Height());	
		CBitmap *m_bitmapOld=new CBitmap(MemDC.SelectObject(&m_BitmapMemDC));
		MemDC.FillRect(&rcClient,&cb);

		/*CGradient M(CSize(rcClient.Width(),rcClient.Height()));	
		M.PrepareVertical(&dc);
		M.Draw(&MemDC,0,0,0,0,rcClient.Width(),rcClient.Height(),SRCCOPY);
		*/Drawpanels(&MemDC);
		dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		     rcClient.left,rcClient.top,SRCCOPY);
		MemDC.SelectObject(m_bitmapOld);
		m_BitmapMemDC.DeleteObject();
		MemDC.DeleteDC();
		cb.DeleteObject();
		dc.DeleteDC();
		m_bitmapOld->DeleteObject();
		delete m_bitmapOld;
		return TRUE;
	}

	
	void  Drawpanels(CGDI *pDC)
	{
		int iCont=GetNumPanels();
		CRect rcCli,rcCliente;
		CString m_cad;
		int OldMode=pDC->SetBkMode(TRANSPARENT);
		for (int i=0; i < iCont; i++)
		{
			TCHAR lpsText[100];
			GetText(i, lpsText);
			GetPaneRect(i,&rcCli);
			CSize m_sChar(GetTextLength(i),0);
			if (rcCli.Width() < m_sChar.cx)
			{
				int dif=m_sChar.cx-rcCli.Width();
				rcCli.right=rcCli.left+m_sChar.cx-dif;
			}
			
			/*CGradient M(CSize(rcCli.Width(),rcCli.Height()));	
			M.PrepareReverseVert(pDC);
			M.Draw(pDC,rcCli.left,rcCli.top,0,0,rcCli.Width(),rcCli.Height(),SRCCOPY);

			*/
			if (m_Style == DEVSTUDIO)
				pDC->Draw3dRect(rcCli,CDrawLayer::GetRGBColorShadow(),CDrawLayer::GetRGBColorShadow());
			else
				pDC->Draw3dRect(rcCli,CDrawLayer::GetRGBColorTabs(),CDrawLayer::GetRGBColorTabs());
			if (i == iCont-1)
			{
				rcCli.left=rcCli.right;
				rcCli.right=rcCli.left+2;
				pDC->Draw3dRect(rcCli,CDrawLayer::GetRGBColorFace(),CDrawLayer::GetRGBColorFace());
				rcCli.right+=1;
				pDC->Draw3dRect(rcCli,CDrawLayer::GetRGBColorFace(),CDrawLayer::GetRGBColorFace());
				rcCli.right+=1;
				pDC->Draw3dRect(rcCli,CDrawLayer::GetRGBColorFace(),CDrawLayer::GetRGBColorFace());

			}
			CPoint pti;
			HFONT m_fontOld=pDC->SelectFont(m_cfont);
			CSize szText=pDC->GetTextExtent(lpsText,lstrlen(lpsText));
			pti.x= rcCli.left+4;
			pti.y=(rcCli.Height()/2)-4;
			pDC->DrawState(pti,szText,lpsText,DSS_NORMAL,TRUE,0,(HBRUSH)NULL);
			pDC->SelectFont(m_fontOld);
		}
		pDC->SetBkMode(OldMode);
		GetClientRect(&rcCliente);
		if ((rcCliente.right - rcCli.right) != 0)
		{
			CBrush cb;
			cb.CreateSolidBrush(CDrawLayer::GetRGBColorFace());
			rcCliente.left = rcCli.right;
			rcCliente.bottom= rcCliente.top+6;
			cb.DeleteObject();
			//pDC->FillRect(rcCliente,&cb);
		}
		//se dibuja la esquina que permite hacer sizing de la ventana
		CRect rc;
		CRect rc1;
		GetClientRect(&rc);
		rc1=rc;
		rc.left=rc.right-15;
		rc.top=rc.bottom-5;
		DrawGripper(pDC,rc, FALSE);
		rc.left=rc.right-11;
		rc.top=rc.bottom-10;
		DrawGripper(pDC,rc, FALSE);
		rc.left=rc.right-7;
		rc.top=rc.bottom-15;
		DrawGripper(pDC,rc, FALSE);
		
		
		

	}

	void Size()
	{
		SendMessage(WM_SIZE,0L,0);
		CRect rc;
		GetClientRect(rc);
		int width = rc.Width();
		int iSW[10];
		int iCont=GetNumPanels();
		int iAcum=20;
		for (int i=iCont-1; i>-1; i--)
		{
			int val= width-iAcum;
			iSW[i]=val;
			iAcum+=20;
			
		}
		SetIndicators(iSW,iCont);
		
	}

	void DrawGripper(CGDI* dc,CRect rcWin,BOOL bHorz=TRUE)
	{

		if (bHorz)
		{
			
			rcWin.top+=7;
			rcWin.left+=5;
			rcWin.right=rcWin.left+2;
			rcWin.bottom-=4;
			CRect rcBlack;
			CBrush cb;
			for (int i=0; i < rcWin.Height(); i+=4)
			{
				CRect rcWindow;
				cb.CreateSolidBrush(CDrawLayer::GetRGBColorShadow());
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
				cb.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
				dc->FillRect(rcBlack,&cb);
				cb.DeleteObject();
			}
				cb.DeleteObject();
		
			
		}
		else
		{
			rcWin.top+=3;
			rcWin.left+=4;
			rcWin.right-=2;
			rcWin.bottom=rcWin.top+2;
			CRect rcBlack;
			CBrush cb;
			for (int i=0; i < rcWin.Width(); i+=4)
			{
				CRect rcWindow;
				cb.CreateSolidBrush(CDrawLayer::GetRGBColorShadow());
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
				cb.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
				dc->FillRect(rcBlack,&cb);
				cb.DeleteObject();
			}
			cb.DeleteObject();
		}
	}
	

	BEGIN_MSG_MAP()
		ON_WM_PAINT(OnPaint)
	END_MSG_MAP(CStatusCtrl)

};


/*
 *
 *  CRebarCtrlEx
 *
 ****/

class CReBarCtrlEx: public CReBarCtrl
{
	public:
		
	BOOL Create(HWND hWndParent,DWORD dwStyle=WS_CHILD | WS_VISIBLE |  WS_CLIPCHILDREN | WS_CLIPSIBLINGS | RBS_VARHEIGHT | RBS_BANDBORDERS | RBS_AUTOSIZE,
			UINT uID=60000)
	{			

		BOOL bRes = CreateEx(0L, REBARCLASSNAME, NULL,
						dwStyle,CRect(0L, 0L, 0L, 0),hWndParent, uID, NULL);
		SubclassWnd(GetSafeHwnd());
		REBARINFO rbi;
		rbi.cbSize = sizeof(REBARINFO);
		rbi.fMask  = 0;
		if(!::SendMessage(m_hWnd, RB_SETBARINFO, 0L, (LPARAM)&rbi)) //SetBarInfo(&rbi)
		{
			DestroyWindow(m_hWnd);
			return NULL; 
		}
		return bRes;
	}



	int  OnPaint(HDC hDC)
	{
		CPaintDC	dc(GetSafeHwnd());
		CRect rect;
		CGDI		m_dc;	
		CBitmap		m_bitmap;
		GetClientRect(&rect);
		m_dc.CreateCompatibleDC(dc.m_hDC);
		m_bitmap.CreateCompatibleBitmap(dc.m_hDC,rect.Width(),rect.Height());
		CBitmap m_OldBitmap=m_dc.SelectObject(&m_bitmap);
		//aqui debe utilizarse la brocha que define CDrawLayer, si no hacemos la siguiente
		//linea usted vera un horrible color negro, a cambio del dibujo.
		
		/*CGradient M(CSize(rect.Width(),rect.Height()));	
		M.PrepareVertical(&m_dc);
		M.Draw(&m_dc,0,0,0,0,rect.Width(),rect.Height(),SRCCOPY);	*/
		CBrush cb;
		cb.CreateSysColorBrush(COLOR_BTNFACE);
		//rc.top+=1;
		CRect rc1=rect;
		m_dc.FillRect(&rc1,&cb);
		int nCount = (int)::SendMessage(GetSafeHwnd(), RB_GETBANDCOUNT, 0, 0L);
		CRect rc=rect;	
		for(int i = 0; i < nCount; i++)
		{
			 
			REBARBANDINFO rbBand;
			rbBand.cbSize = sizeof(REBARBANDINFO);
			rbBand.fMask = RBBIM_SIZE|RBBIM_CHILD|RBBIM_CHILDSIZE; 

			BOOL bRet = (BOOL)::SendMessage(GetSafeHwnd(), RB_GETBANDINFO, i, (LPARAM)&rbBand);
			ASSERT(bRet);
			RECT rct = { 0, 0, 0, 0 };
			::SendMessage(GetSafeHwnd(), RB_GETRECT, i, (LPARAM)&rct);
			SIZE lpSize;
			if (rbBand.hwndChild == m_hWnd) continue;
			::SendMessage( rbBand.hwndChild,TB_GETMAXSIZE, 0L,(LPARAM) &lpSize);
			rbBand.cx += rct.left + rct.right;
			CRect rc1=rct;
			rc1.left+=1;
			//rc1.right=rc1.left+lpSize.cx+13;
			CRect rc2=rct;
			rc2.left= rc2.right-6;
			CGradient M(CSize(rc2.Width(),rc2.Height()));	
			M.PrepareVertical(&m_dc,GUISTYLE_XP,CDrawLayer::GetRGBPressBXP());
			M.Draw(&m_dc,rc2.left,rc2.top,0,0,rc2.Width(),rc2.Height(),SRCCOPY);	
						
			
			CGradient M1(CSize(rc1.Width(),rc1.Height()));	
			M1.PrepareVertical(&m_dc); //,GUISTYLE_XP,CDrawLayer::GetRGBPressBXP());
			M1.Draw(&m_dc,rc1.left,rc1.top,0,0,9,rc1.Height(),SRCCOPY);	
			
			DrawGripper(&m_dc,rct);
			//round border efects
			rc1=rct;
			rc1.left+=1;
			rc1.right=rc1.left+1;
			rc1.top=rc1.bottom-1;
			m_dc.FillRect(&rc1,&cb);
			rc1=rct;
			rc1.left+=1;
			rc1.right=rc1.left+2;
			rc1.bottom=rc1.top+1;
			m_dc.FillRect(&rc1,&cb);
			rc1=rct;
			rc1.left+=1;
			rc1.right=rc1.left+1;
			rc1.bottom=rc1.top+2;
			m_dc.FillRect(&rc1,&cb);
			
		
		}
		dc.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),m_dc.m_hDC,0L,0L,SRCCOPY);
		m_dc.SelectObject(&m_OldBitmap);
		m_bitmap.DeleteObject();
		m_OldBitmap.DeleteObject();
		m_dc.DeleteDC();
		cb.DeleteObject();
		dc.DeleteDC();
		return 0;
	}

	void DrawGripper(CGDI* dc,CRect rcWin,BOOL bHorz=TRUE)
	{

		if (bHorz)
		{
			
			rcWin.top+=6;
			rcWin.left+=5;
			rcWin.right=rcWin.left+2;
			rcWin.bottom-=2;
			CRect rcBlack;
			CBrush cb;
			for (int i=0; i < rcWin.Height(); i+=4)
			{
				CRect rcWindow;
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
				cb.DeleteObject();
		
			}
			cb.DeleteObject();
			
		}
		else
		{
			rcWin.top+=3;
			rcWin.left+=4;
			rcWin.right-=2;
			rcWin.bottom=rcWin.top+2;
			CRect rcBlack;
			CBrush cb;
			for (int i=0; i < rcWin.Width(); i+=4)
			{
				CRect rcWindow;
				
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
			cb.DeleteObject();
		}
	}

	BOOL OnDblclk( LPNMCHAR pNMHDR )
	{
		return TRUE;   //not use this event i' don't care
	}
	 
	
	/*BOOL OnSetCursor(CWin* pWnd, UINT nHitTest, UINT message) 
	{

		CPoint ptCurPos; 
		CRect rc;GetClientRect(rc);
		GetCursorPos (&ptCurPos);
		ScreenToClient (&ptCurPos);
		if (m_dwStyle & CBRS_ORIENT_HORZ)
		{
			rc.right=rc.left+2;
			if (ptCurPos.x< 0)
			{
				SetCursor (LoadCursor(NULL, IDC_SIZEALL));
				return TRUE;
			}
		}
		else
		{
			rc.bottom=rc.top+2;
			if (ptCurPos.y< 0)
			{
				SetCursor (LoadCursor(NULL, IDC_SIZEALL));
				return TRUE;
			}
		}
		return TRUE;

	}*/	
	   
	BEGIN_MSG_MAP()
		ON_WM_PAINT(OnPaint)
	END_MSG_MAP(CReBarCtrl)
	
};	







#endif // !defined(C_COMMONCTRL_H__191265517913803_INCLUDED_)