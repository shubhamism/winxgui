/*
 * <F> CToolButton.h		1.0  23/09/2007
 *
 * Copyright 2007 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/


class  CToolButton : public CButton
{

public:
	CToolButton();
	virtual ~CToolButton();
public:
	virtual BOOL Create( HWND hwndParent,UINT nID=0L,LPCTSTR lpWindowName=NULL,
					 DWORD dwStyle=WS_VISIBLE,CRect rc=CRect(0L,0L,0L,0),LPVOID lpParam=NULL);
	void SetToolTip(LPCTSTR szToolTip);
	void SetCaption(LPCTSTR szCaption);
	void SethIcon(HICON hIcon);
	void SetColor(COLORREF clColor);
	void RecalSize();
	void ShowDark(BOOL bShow);
	CSize GetSizeButton();
	void ShowMenu();
	void SetScrollButton(BOOL bScroll=TRUE);
	void SetSimpleButton(BOOL bSimple=TRUE){m_bSimple=bSimple;};
	void SetFontColor(COLORREF clrFont);

protected:

	virtual BOOL OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	BOOL OnEraseBkgnd(HDC pDC);
	void OnTimer(UINT nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubClassWnd();
	BOOL OnSysColorChange( );
	BOOL OnSetCursor(HWND hWnd, UINT nHitTest, UINT message);
	BOOL OnLButtonDown(UINT nFlags, CPoint pt);
	
protected:
	CToolTipCtrl m_toolTip;
	HICON		 m_Icon;
	CSize		 m_SizeImage;
	CSize		 m_SizeText;
	TCHAR		 m_szText[128];
	COLORREF	 m_clColor;
	BOOL		 m_bMouserOver;
	BOOL		 m_ReposWindow;
	CSize		 m_szButton;
	BOOL		 m_bShowDark;
	BOOL		 m_ScrollButton;	
	COLORREF	 m_clrFont;
	BOOL		 m_bSimple;
	BOOL		 m_bMousePress;
	CFont*		 cfont;
public:
	HMENU		 m_hMenu;
protected:


	BEGIN_MSG_MAP()
		ON_WM_SETCURSOR(OnSetCursor)
		ON_WM_SYSCOLORCHANGE(OnSysColorChange)
		ON_WM_ERASEBKGND(OnEraseBkgnd)
		ON_WM_TIMER(OnTimer)
		ON_WM_LBUTTONDOWN(OnLButtonDown) 
	END_MSG_MAP(CButton)
public:
	
};


class CNormalButton :public CToolButton
{
	public:
		enum StyleBtn{STL_NORMAL=0,STL_FLAT=1,STL_SEMIFLAT=2,STL_XP=3};
	public:
		CNormalButton(void);
		virtual ~CNormalButton(void);
		void SetStyleButton(StyleBtn StlButton);
	private:
		StyleBtn m_stlbtn;
	protected:
		virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

    BEGIN_MSG_MAP()
	END_MSG_MAP(CToolButton)
};



class CTabbedButton: public CNormalButton
{
	public:
		CTabbedButton();
		virtual ~CTabbedButton();
		
	protected:
		BOOL	bPress;
		int		m_iMilliseconds;

	protected:
		BOOL OnLButtonDown(UINT nFlags, CPoint point);
		BOOL OnLButtonUp(UINT nFlags, CPoint pt);
		void  OnTimer(UINT nIDEvent);
	public:
		void SetWait(int iMilliseconds = 50)
		{
			m_iMilliseconds = iMilliseconds;
		};

		BEGIN_MSG_MAP()
		ON_WM_LBUTTONDOWN(OnLButtonDown)
		ON_WM_TIMER(OnTimer)
		ON_WM_LBUTTONUP(OnLButtonUp)
		END_MSG_MAP(CNormalButton)
	
};


#define NORMALBTN   1
#define OVERBTN     1
#define PRESSBTN    2

class  CControlBarButton 
{
public:
	enum Type
	{
		NORMAL    = 0,
		TOOLBUTTON
	};
	
	CRect rcArea;
protected:
	
	int m_nIcon;
	LPCTSTR m_lpMsg;
	CImageCtrl m_imgList;
	Type bTypeButton;
	BOOL m_bEnabled;
	CToolTipCtrl   m_toolTip;
	
public:
	
	CControlBarButton();
	void SetData(int nIcon, LPCTSTR lpMsg);
	~CControlBarButton();
	void Paint(CGDI* pDC, int st, CRect rc, COLORREF clrFondo,BOOL isBackDark=FALSE);
	void SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void SetTypeButton(Type bTypeb = NORMAL);
	void SetEnabled(BOOL bEnabled);
};
