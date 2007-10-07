/* This is a part of the Simple Windows Class.
 * Copyright (C) 2005 Francisco Campos G.
 * All rights reserved.
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/


#if !defined(C_GDI_H__191265517913802_INCLUDED_)
#define C_GDI_H__191265517913802_INCLUDED_

#pragma once
#pragma warning( disable : 4244 )  

/*
 * The follow class are including in this file
 *
 *
 * class CPoint;
 * class CSize;
 * class CRect;
 * class CGDI;
 * class CBrush;
 * class CArray
 * class CBitmap
 * class CPen
 * class CMenu;
 * class CFont
 * class CPaintDC
 * class CGradient  
 * class CClientDC
 * class CWindowDC 
 *
 ***/


class CWin;
class CPoint;
class CSize;
class CRect;
class CGDI;
class CBrush;
class CMenu;


#define 	GUISTYLE_XP   0x08001 	
#define		GUISTYLE_2003 0x08002
#define		GUISTYLE_2003MENUBTN 0x08021
#define		WIN_NT		  0x08003 	
#define		WIN_2000	0x08004
#define		WIN_XP		0x08005
#define		WIN_95		0x08006
#define		WIN_98		0x08007
#define		WIN_32		0x08008
#define		WIN_ME		0x08009
#define		WIN_95OSR2	0x0800A
#define		WIN_98_SE	0x0800B

#pragma warning( disable : 4996 )


/*
 * CDrawlayer: This class is a wrapper of color and look for our future controls
 *
 **/

class CDrawLayer  
{

public:

	static COLORREF DarkenColor( long lScale, COLORREF lColor)
	{ 
	  long R = MulDiv(GetRValue(lColor),(255-lScale),255);
	  long G = MulDiv(GetGValue(lColor),(255-lScale),255);
	  long B = MulDiv(GetBValue(lColor),(255-lScale),255);

	  return RGB(R, G, B); 
	}

	
	static COLORREF GetRGBColorWhite()
	{
		return RGB(255,255,255);
	}

	

	static COLORREF GetRGBActiveBorder()
	{
		COLORREF clrPress = ::GetSysColor (COLOR_INACTIVEBORDER);
		BYTE byRvalue =GetRValue(clrPress);
		BYTE byGvalue =GetGValue(clrPress);
		BYTE byBvalue =GetBValue(clrPress);
		return RGB(byRvalue,byGvalue,byBvalue);	
	}

	static COLORREF GetRGBColorTabs()
	{
		BYTE byRvalue =GetRValue(GetRGBColorXP());
		BYTE byGvalue =GetGValue(GetRGBColorXP());
		BYTE byBvalue =GetBValue(GetRGBColorXP());
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.51);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
		
	}


	static COLORREF GetRGBSkinMenu()
	{
		BYTE byRvalue =GetRValue(CDrawLayer::GetRGBColorFace());
		BYTE byGvalue =GetGValue(CDrawLayer::GetRGBColorFace());
		BYTE byBvalue =GetBValue(CDrawLayer::GetRGBColorFace());
		byRvalue =byRvalue>>2;
		byGvalue =byGvalue>>2;
		byBvalue =byBvalue>>2;
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.018);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
		
	}

	static COLORREF GetRGBColorBTNHigh()
	{
		return ::GetSysColor(COLOR_BTNHIGHLIGHT);
	}



	static COLORREF GetRGBColorGrayText()
	{
		BYTE byRvalue =0;
		BYTE byGvalue =0;
		BYTE byBvalue =0;
		byRvalue =byRvalue>>1;
		byGvalue =byGvalue>>1;
		byBvalue =byBvalue>>1;
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.60);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
		
	}


	static COLORREF CDrawLayer::GetRGBColorFace()
	{
		return ::GetSysColor(COLOR_BTNFACE);
	}

	static COLORREF GetRGBColorShadow()
	{
		return ::GetSysColor(COLOR_BTNSHADOW);
	}

	static COLORREF GetRGBPressBXP()
	{
		
		BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
		BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
		BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
		byRvalue =byRvalue>>2;
		byGvalue =byGvalue>>2;
		byBvalue =byBvalue>>2;
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.21);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
		
	}

	static COLORREF GetRGBMenu()
	{
		BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
		BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
		BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
		byRvalue =byRvalue>>3;
		byGvalue =byGvalue>>3;
		byBvalue =byBvalue>>3;
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.47);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
		
	}

	static COLORREF GetRGBTitleMenu()
	{
		COLORREF clrPress = ::GetSysColor (COLOR_BTNSHADOW);

		BYTE byRvalue =GetRValue(::GetSysColor(clrPress));
		BYTE byGvalue =GetGValue(::GetSysColor(clrPress));
		BYTE byBvalue =GetBValue(::GetSysColor(clrPress));
		byRvalue =byRvalue>>2;
		byGvalue =byGvalue>>2;
		byBvalue =byBvalue>>2;
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.8);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
		
	}

	static COLORREF GetRGBCaptionXP()
	{

		BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
		BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
		BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
		return RGB(byRvalue+10,byGvalue+10,byBvalue+10);	
	}

	static COLORREF GetRGBFondoXP()
	{
		BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
		BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
		BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
		byRvalue =byRvalue>>2;
		byGvalue =byGvalue>>2;
		byBvalue =byBvalue>>2;
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.14);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	}

	
	static COLORREF GetRGBGray()
	{
		BYTE byRvalue =GetRValue(::GetSysColor(COLOR_BTNSHADOW));
		BYTE byGvalue =GetGValue(::GetSysColor(COLOR_BTNSHADOW));
		BYTE byBvalue =GetBValue(::GetSysColor(COLOR_BTNSHADOW));
		byRvalue =byRvalue>>2;
		byGvalue =byGvalue>>2;
		byBvalue =byBvalue>>2;
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.30);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
		//return RGB(182,179,171);	
	}

	static BOOL IsGrayed()
	{
		BYTE byRvalue =GetRValue(::GetSysColor(COLOR_3DFACE));
		BYTE byGvalue =GetGValue(::GetSysColor(COLOR_3DFACE));
		BYTE byBvalue =GetBValue(::GetSysColor(COLOR_3DFACE));
		if ((byRvalue ==byGvalue) && (byGvalue == byBvalue) &&
			 (byBvalue > 190 && byBvalue < 193) || (byBvalue == 216))
			return TRUE;
		else
			return FALSE;
	}

	static COLORREF GetRGBColorXP()
	{

		
		COLORREF clr3DFace = ::GetSysColor (COLOR_3DFACE);
		return RGB (((3*GetRValue (clr3DFace)+240)/4)+1,
					((3*GetGValue (clr3DFace)+240)/4)+1,
					((3*GetBValue (clr3DFace)+240)/4)+1);

	}

	static COLORREF GetRGBSemiShadow()
	{

		
		COLORREF clr3DFace = ::GetSysColor (COLOR_3DFACE);
		BYTE byRvalue =GetRValue(clr3DFace);
		BYTE byGvalue =GetGValue(clr3DFace);
		BYTE byBvalue =GetBValue(clr3DFace);
		byRvalue =byRvalue>>2;
		byGvalue =byGvalue>>2;
		byBvalue =byBvalue>>2;
		int iMaximo=max(byRvalue,byGvalue);
		iMaximo=max(iMaximo,byBvalue);
		iMaximo= 255-iMaximo;
		iMaximo=iMaximo-(int)(iMaximo*0.25);
		return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	}
	int GetDropDownWidth()
	{
		int iSize;
		HDC hDC = GetDC(NULL);
		ASSERT(hDC != NULL);
		HFONT hFont;
		if ((hFont = CreateFont(GetSystemMetrics(SM_CYMENUCHECK), 0, 0, 0,
			FW_NORMAL, 0, 0, 0, SYMBOL_CHARSET, 0, 0, 0, 0, _T("Marlett"))) != NULL)
			hFont = (HFONT)SelectObject(hDC, hFont);
			GetCharWidth(hDC, '6', '6', &iSize);
		if (hFont != NULL)
		{
			SelectObject(hDC, hFont);
			DeleteObject(hFont);
		}
		ReleaseDC(NULL, hDC);
		ASSERT(iSize != -1);
		return iSize;
	}


	static int SWCFindChar(TCHAR Buffer[], TCHAR ch)
	{
		int i=0;
		for( i=0; i < lstrlen(Buffer); i++)
		{
			if (Buffer[i] == ch)
				break;
		}
		if (i== lstrlen(Buffer))
			return -1;
		return i;	
	}


	static void  SWCCopyRight(TCHAR BufferSrc[], int pos, char BufferTarget[])
	{
		lstrcpynA(BufferTarget,BufferSrc+pos,lstrlen(BufferSrc)-(pos-1));
		
	}

	static void  SWCCopyLeft(TCHAR BufferSrc[], int pos, char BufferTarget[])
	{
		lstrcpynA(BufferTarget,BufferSrc,pos);
	}

	//function of Bruno Podetti
	static void DrawCheck(CGDI* pDC,CRect m_rcTemp);
	static void DrawShade( CRect Rect,CPoint screen,CGDI* pDC);

};


/*
 *  CSize this class is a wrapper of SIZE Struct
 *
 **/

class CSize : public SIZE
{
public:
	//------------------------------------------------
	CSize()
	{cx=0; cy=0;}
	CSize(SIZE sz)
	{cx=sz.cx; cy=sz.cy;}
	CSize(long x, long y)
	{cx=x; cy=y;}

	//------------------------------------------------
	inline BOOL operator==(SIZE size) 
	{ return (size.cx== cx && size.cy == cy);	}
	inline BOOL operator!=(SIZE size) 
	{ return (size.cx != cx && size.cy != cy);	}	
	inline void operator+=(SIZE size)
	{ cx += size.cx; cy+=size.cy;}	
	inline void operator-=(SIZE size)
	{ cx -= size.cx; cy-=size.cy;}	
	
	//------------------------------------------------
	inline CSize operator+(SIZE size) 
	{return CSize (cx+size.cx,cy+size.cy);}
	

	inline CSize operator-(SIZE size) 
	{	return CSize (cx-size.cx,cy-size.cy);	}

	inline CSize operator-() 
	{ return CSize(-cx, -cy); }

	//------------------------------------------------
	inline CPoint operator+(POINT point) ;
	inline CPoint operator-(POINT point) ;

};


/*
 *    CPoint
 *    
 **/

class CPoint : public POINT
{
public:

	//-------------------------------------------------
	CPoint (long  lx, long ly)
	{ x=lx; y=ly;}
	CPoint(){ x=0; y=0;}
	CPoint(POINT pt)
	{x=pt.x; y=pt.y;}

	CPoint::CPoint(DWORD dwPoint)
	{
		x = (short)LOWORD(dwPoint);
		y = (short)HIWORD(dwPoint);
	}
	operator POINT() {this;}
	//-------------------------------------------------
	inline BOOL operator==(POINT point) 
	{return (point.x== x && point.y==y);}
	inline BOOL operator!=(POINT point) 
	{return (point.x!= x && point.y!=y);}
	inline void operator+=(SIZE size)
	{ x+=size.cx; y+=size.cy;}
	inline void operator-=(SIZE size)
	{ x-=size.cx; y-=size.cy;}
	inline void operator+=(POINT point)
	{ x+=point.x; y+=point.y;}
	inline void operator-=(POINT point)
	{ x-=point.x; y-=point.y;}

	//-------------------------------------------------
	inline CPoint operator+(SIZE size) 
	{return CPoint(size.cx+x,size.cy+y);}
	inline CPoint operator-(SIZE size) 
	{return CPoint(size.cx-x,size.cy-y);}
	inline CPoint operator-() 
	{return CPoint(-x,-y);}
	inline CPoint operator+(POINT point) 
	{return CPoint(point.x+x,point.y+y);}

	//-------------------------------------------------
	inline CSize operator-(POINT point) 
	{return CSize(x-point.x,y-point.y);}

};


/*
 *  CRect class
 * 
 **/

class CRect : public RECT
{
public:
	CRect(){ CRect (0,0,0,0);}

	CRect (CPoint ptLt, CPoint ptBr)
	{
		CRect(ptLt.x,ptLt.y,ptBr.x,ptBr.y);	
	}

	CRect (int x, int y, int Right, int Bottom)
	{
		left=x;
		top=y;
		right=Right;
		bottom=Bottom;
	}
	
	CRect(POINT point, SIZE size)
	{ right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
	CRect(POINT topLeft, POINT bottomRight)
	{ left = topLeft.x; top = topLeft.y;right = bottomRight.x; bottom = bottomRight.y; }
	
	CRect::CRect(const RECT& srcRect)
	{	::CopyRect(this, &srcRect); }

	inline int  Width()	{	return (int )right-left;}

	inline int Height()	{	return (int )bottom-top;}
	
	inline CSize Size() 			{ return CSize(right - left, bottom - top); }
	inline CPoint  TopLeft()			{ return CPoint(top,left); }
	inline CPoint  BottomRight()		{ return CPoint(bottom,right); }
	
	inline CPoint  CenterPoint() 	{ return CPoint((left + right) / 2, (top + bottom) / 2); }
	inline operator LPRECT()			{ return this; }
	inline operator LPCRECT() 	{ return this; }
	inline BOOL  IsRectEmpty() 	{ return ::IsRectEmpty(this); }
	inline BOOL  IsRectNull() 	{ return (left == 0 && right == 0 && top == 0 && bottom == 0); }
	inline BOOL  PtInRect(POINT point) 		{ return ::PtInRect(this, point); }
	inline void  SetRect(int x1, int y1, int x2, int y2)	{ ::SetRect(this, x1, y1, x2, y2); }
	inline void  SetRect(POINT topLeft, POINT bottomRight)	{ ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
	inline void  SetRectEmpty()		{ ::SetRectEmpty(this); }
	inline void  CopyRect(LPCRECT lpSrcRect)		{ ::CopyRect(this, lpSrcRect); }
	inline BOOL  EqualRect(LPCRECT lpRect) 	{ return ::EqualRect(this, lpRect); }
	inline void  InflateRect(int x, int y)			{ ::InflateRect(this, x, y); }
	inline void  InflateRect(SIZE size)			{ ::InflateRect(this, size.cx, size.cy); }
	inline void  DeflateRect(int x, int y)			{ ::InflateRect(this, -x, -y); }
	inline void  DeflateRect(SIZE size)			{ ::InflateRect(this, -size.cx, -size.cy); }
	inline void  OffsetRect(int x, int y)			{ ::OffsetRect(this, x, y); }
	inline void  OffsetRect(POINT point)			{ ::OffsetRect(this, point.x, point.y); }
	inline void  OffsetRect(SIZE size)				{ ::OffsetRect(this, size.cx, size.cy); }
	inline BOOL  IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2)	{ return ::IntersectRect(this, lpRect1, lpRect2);}
	inline BOOL  UnionRect(LPCRECT lpRect1, LPCRECT lpRect2)		{ return ::UnionRect(this, lpRect1, lpRect2); }
	inline void  operator=( RECT& srcRect)					{ ::CopyRect(this, &srcRect); }
	inline BOOL  operator==( RECT& rect) 				{ return ::EqualRect(this, &rect); }
	inline BOOL  operator!=( RECT& rect) 				{ return !::EqualRect(this, &rect); }
	inline void  operator+=(POINT point)							{ ::OffsetRect(this, point.x, point.y); }
	inline void  operator+=(SIZE size)								{ ::OffsetRect(this, size.cx, size.cy); }
	inline void  operator+=(LPCRECT lpRect)						{ InflateRect(lpRect); }
	inline void  operator-=(POINT point)							{ ::OffsetRect(this, -point.x, -point.y); }
	inline void  operator-=(SIZE size)								{ ::OffsetRect(this, -size.cx, -size.cy); }
	inline void  operator-=(LPCRECT lpRect)						{ DeflateRect(lpRect); }
	inline void  operator&=( RECT& rect)						{ ::IntersectRect(this, this, &rect); }
	inline void  operator|=( RECT& rect)						{ ::UnionRect(this, this, &rect); }
	inline CRect  operator+(POINT pt) 	{ CRect rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect; }
	inline CRect  operator-(POINT pt) 	{ CRect rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect; }
	inline CRect  operator+(SIZE size) 	{ CRect rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect; }
	inline CRect  operator-(SIZE size) 	{ CRect rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect; }
	inline BOOL  SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2)	{ return ::SubtractRect(this, lpRectSrc1, lpRectSrc2); }
	inline CRect operator&(const RECT& rc) { CRect rect; ::IntersectRect(&rect, this, &rc);	return rect; }
	inline CRect operator|(const RECT& rc)	{ CRect rect; ::UnionRect(&rect, this, &rc);}
	
	inline void  InflateRect(LPCRECT lpRect)
	{
		left -= lpRect->left;
		top -= lpRect->top;
		right += lpRect->right;
		bottom += lpRect->bottom;
	}

	inline void  InflateRect(int l, int t, int r, int b)
	{
		left -= l;
		top -= t;
		right += r;
		bottom += b;
	}

	inline void  DeflateRect(LPCRECT lpRect)
	{
		left += lpRect->left;
		top += lpRect->top;
		right -= lpRect->right;
		bottom -= lpRect->bottom;
	}

	inline void  DeflateRect(int l, int t, int r, int b)
	{
		left += l;
		top += t;
		right -= r;
		bottom -= b;
	}

	inline CRect  MulDiv(int nMultiplier, int nDivisor) 
	{
		return CRect(
			::MulDiv(left, nMultiplier, nDivisor),
			::MulDiv(top, nMultiplier, nDivisor),
			::MulDiv(right, nMultiplier, nDivisor),
			::MulDiv(bottom, nMultiplier, nDivisor));
	}


};

CPoint CSize::operator+(POINT point) { return CPoint(point.x+cx, point.y+cy);}
CPoint CSize::operator-(POINT point) { return CPoint(point.x-cx, point.y-cy);}



/*
 *  CFont
 *
 **/


class CFont
{
public:
	HFONT m_hFont;

	CFont(HFONT hFont = NULL) 
	{  m_hFont=hFont;}

	~CFont()
	{
		if(m_hFont != NULL && !::DeleteObject(m_hFont))
			m_hFont = NULL;
	}

public:
	
	operator HFONT() {return m_hFont;}  

	HFONT  GetFont(){ return m_hFont;}
	
	void Attach(HFONT hFont)
	{
		if( m_hFont != NULL)
			::DeleteObject(m_hFont);
		m_hFont = hFont;
	}
	
	HFONT Detach()
	{
		HFONT hFont = m_hFont;
		m_hFont = NULL;
		return hFont;
	}

	void DeleteObject()
	{
		if( m_hFont != NULL)
			::DeleteObject(m_hFont);
	}
	
	HFONT CreateFontIndirect(const LOGFONT* lpLogFont)
	{
		ASSERT(m_hFont == NULL);
		m_hFont = ::CreateFontIndirect(lpLogFont);
		return m_hFont;
	}


	HFONT CreateFont(int nHeight, int nWidth, int nEscapement,
			int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
			BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
			BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
			LPCTSTR lpszFacename)
	{
		ASSERT(m_hFont == NULL);
		m_hFont = ::CreateFont(nHeight, nWidth, nEscapement,
			nOrientation, nWeight, bItalic, bUnderline, cStrikeOut,
			nCharSet, nOutPrecision, nClipPrecision, nQuality,
			nPitchAndFamily, lpszFacename);
		return m_hFont;
	}
	
	
	BOOL GetStockFont( int nStockFont )
	{
	
		HFONT hFont = ( HFONT )::GetStockObject( nStockFont );
		if ( !hFont) 	return FALSE;
		Attach( hFont );
		return TRUE;
	}


	int GetLogFont(LOGFONT* pLogFont) 
	{
		ASSERT(m_hFont != NULL);
		return ::GetObject(m_hFont, sizeof(LOGFONT), pLogFont);
	}
	
	bool GetLogFont(LOGFONT& LogFont) 
	{
		ASSERT(m_hFont != NULL);
		return (::GetObject(m_hFont, sizeof(LOGFONT), &LogFont) == sizeof(LOGFONT));
	}
};

//-------------------------------
// CPen class
//-------------------------------
class CPen
{
	
public:
	HPEN m_hPen;	
	CPen(HPEN hPen=NULL)	{ m_hPen=hPen;}

	~CPen()
	{
		DeleteObject();
	}

	BOOL IsValidPen() {return !(m_hPen==NULL);}
	
	HPEN GetPen() { if (! IsValidPen()) return NULL; return m_hPen;}
	
	HPEN CreatePen(int fnPenStyle=PS_SOLID,int nWidth=1,COLORREF clColor=RGB(0,0,0))
	{
		if (IsValidPen()) return NULL;
		m_hPen=::CreatePen(fnPenStyle,nWidth,clColor);
		return m_hPen;
	}

	HPEN ExtCreatePen( LOGBRUSH* lplb, int fnPenStyle=PS_SOLID,int nWidth=1, int dwStyleCount=0,  DWORD* lpStyle=NULL )
	{
		if (IsValidPen()) return NULL;
		m_hPen=::ExtCreatePen(fnPenStyle,nWidth,lplb,dwStyleCount,lpStyle);
		return m_hPen;
	}


	HPEN CreatePenIndirect( LOGPEN* lplgpen)
	{
		if (IsValidPen()) return NULL;
		m_hPen=::CreatePenIndirect(lplgpen);
		return m_hPen;
	}

	BOOL DeleteObject()
	{
		if (! IsValidPen()) return NULL;
		BOOL brs = ::DeleteObject((HPEN)m_hPen);
		if(brs)	m_hPen = NULL;
		return brs;
	}


	int GetLogPen(LOGPEN* pLogPen) 
	{
		if (!IsValidPen()) return NULL;
		return ::GetObject(m_hPen, sizeof(LOGPEN), pLogPen);
	}

	int GetExtLogPen(EXTLOGPEN* pLogPen) 
	{
		if (!IsValidPen()) return NULL;
		return ::GetObject(m_hPen, sizeof(EXTLOGPEN), pLogPen);
	}


};

//----------------------------------
//CBrush class
//----------------------------------

class CBrush
{
	

	public:
	HBRUSH m_hBrush;
	CBrush(HBRUSH hBrush = NULL) 
	{ 
		m_hBrush=hBrush;
	}
	~CBrush()	{	DeleteObject();	}

	
	HBRUSH GetBrush() { return m_hBrush; }

	HBRUSH GetSafeHandle() { return GetBrush();} //compatibilidad con MFC

	operator HBRUSH() { return GetSafeHandle();}
	BOOL IsValidBrush() {return !(m_hBrush==NULL);}

	CBrush(COLORREF crColor)
	{	
		Attach(::CreateSolidBrush(crColor));
	}
	void Attach(HBRUSH hBrush)
	{
		if(m_hBrush != NULL)
			::DeleteObject(m_hBrush);
		m_hBrush = hBrush;
	}
	
	HBRUSH Detach()
	{
		HBRUSH hBrush = m_hBrush;
		m_hBrush = NULL;
		return hBrush;
	} 
	
	HBRUSH CreateSolidBrush(COLORREF crColor=CDrawLayer::GetRGBColorFace())
	{
		if (IsValidBrush()) return NULL;
		m_hBrush = ::CreateSolidBrush(crColor);
		return m_hBrush;
	}

	HBRUSH CreateHatchBrush(int nIndex=HS_VERTICAL,COLORREF crColor=CDrawLayer::GetRGBColorFace())
	{
		if ( IsValidBrush()) return NULL;
		m_hBrush = ::CreateHatchBrush(nIndex, crColor);
		return m_hBrush;
	}

	HBRUSH CreateBrushIndirect( LOGBRUSH* lpLogBrush)
	{
		if ( IsValidBrush()) return NULL;
		m_hBrush = ::CreateBrushIndirect(lpLogBrush);
		return m_hBrush;
	}

	HBRUSH CreatePatternBrush(HBITMAP hBitmap)
	{
		if ( IsValidBrush()) return NULL;
		m_hBrush = ::CreatePatternBrush(hBitmap);
		return m_hBrush;
	}

	HBRUSH CreateDIBPatternBrush( void* lpPackedDIB, UINT nUsage=DIB_PAL_COLORS)
	{
		if (lpPackedDIB == NULL) return NULL;
		m_hBrush=::CreateDIBPatternBrushPt(lpPackedDIB, nUsage);
		return m_hBrush;
	}
	
	HBRUSH CreateSysColorBrush(int nIndex)
	{
		if (IsValidBrush()) return NULL;
		m_hBrush = ::GetSysColorBrush(nIndex);
		return m_hBrush;
	}

	BOOL DeleteObject()
	{
		if (!IsValidBrush()) return NULL;
		BOOL bres = ::DeleteObject(m_hBrush);
		if(bres)
			m_hBrush = NULL;
		return bres;
	}

	int GetLogBrush(LOGBRUSH* pLogBrush) 
	{
		if (! IsValidBrush()) return NULL;
		return ::GetObject(m_hBrush, sizeof(LOGBRUSH), pLogBrush);
	}
	
};

//-------------------------------------------
// CBitmap class
//-------------------------------------------

class CBitmap
{
	
public:

	HBITMAP m_hBitmap;
	CBitmap(HBITMAP hBitmap = NULL) { m_hBitmap=hBitmap;}

	~CBitmap() { DeleteObject();}

	BOOL IsValidBitmap() { return !(m_hBitmap== NULL);}

	HBITMAP GetBitMap() { if (IsValidBitmap()) return m_hBitmap; return NULL;}
	
	HBITMAP GetSafeHandle() { if (IsValidBitmap()) return m_hBitmap; return NULL;}
	HBITMAP LoadBitmap(HINSTANCE hInsTance,LPCTSTR lpBitmapName)
	{
		if (IsValidBitmap()) return NULL;
		m_hBitmap = ::LoadBitmap(hInsTance,lpBitmapName);
		return m_hBitmap;
	}
	
	HBITMAP LoadOEMBitmap(UINT nIDBitmap) 
	{
		if (IsValidBitmap()) return NULL;
		m_hBitmap = ::LoadBitmap(NULL, MAKEINTRESOURCE(nIDBitmap));
		return m_hBitmap;
	}

	HBITMAP CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitcount,  void* lpBits)
	{
		if (IsValidBitmap()) return NULL;
		m_hBitmap = ::CreateBitmap(nWidth, nHeight, nPlanes, nBitcount, lpBits);
		return m_hBitmap;
	}
	
	BOOL DeleteObject()
	{
		if (!IsValidBitmap()) return NULL;
		BOOL bres = ::DeleteObject(m_hBitmap);
		if(bres)
			m_hBitmap = NULL;
		return bres;
	}

	int GetBitmap(BITMAP* pBitMap) 
	{
		if (!IsValidBitmap()) return NULL;
		return ::GetObject(m_hBitmap, sizeof(BITMAP), pBitMap);
	}

	BOOL GetBitmap(BITMAP& bm) 
	{
		if (!IsValidBitmap()) return NULL;
		return (::GetObject(m_hBitmap, sizeof(BITMAP), &bm) == sizeof(BITMAP));
	}

	BOOL GetSize(SIZE& size) 
	{
		if (!IsValidBitmap()) return NULL;
		BITMAP bm;
		if(!GetBitmap(&bm))
			return false;
		size.cx = bm.bmWidth;
		size.cy = bm.bmHeight;
		return true;
	}

	CSize GetSize() 
	{
		if (!IsValidBitmap()) return CSize(0,0);
		BITMAP bm;
		if(!GetBitmap(&bm))
			return CSize(0,0);
		return CSize(bm.bmWidth,bm.bmHeight);
	}


	DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) 
	{
		if (!IsValidBitmap()) return NULL;
		return ::GetBitmapBits(m_hBitmap, dwCount, lpBits);
	}
	DWORD SetBitmapBits(DWORD dwCount,  void* lpBits)
	{
		if (!IsValidBitmap()) return NULL;
		return ::SetBitmapBits(m_hBitmap, dwCount, lpBits);
	}
	BOOL GetBitmapDimension(LPSIZE lpSize) 
	{
		if (!IsValidBitmap()) return NULL;
		return ::GetBitmapDimensionEx(m_hBitmap, lpSize);
	}
	BOOL SetBitmapDimension(int nWidth, int nHeight, LPSIZE lpSize = NULL)
	{
		if (!IsValidBitmap()) return NULL;
		return ::SetBitmapDimensionEx(m_hBitmap, nWidth, nHeight, lpSize);
	}

	HBITMAP CreateBitmapIndirect(LPBITMAP lpBitmap)
	{
		if (IsValidBitmap()) return NULL;
		m_hBitmap = ::CreateBitmapIndirect(lpBitmap);
		return m_hBitmap;
	}
	HBITMAP CreateCompatibleBitmap(HDC hDC, int nWidth, int nHeight)
	{
		if (IsValidBitmap()) return NULL;
		m_hBitmap = ::CreateCompatibleBitmap(hDC, nWidth, nHeight);
		return m_hBitmap;
	}
	HBITMAP CreateDiscardableBitmap(HDC hDC, int nWidth, int nHeight)
	{
		if (IsValidBitmap()) return NULL;
		m_hBitmap = ::CreateDiscardableBitmap(hDC, nWidth, nHeight);
		return m_hBitmap;
	}


	HBITMAP CreateDIBitmap(HDC hDC,  BITMAPINFOHEADER* lpbmih, DWORD dwInit,  VOID* lpbInit,  BITMAPINFO* lpbmi, UINT uColorUse)
	{
		if (IsValidBitmap()) return NULL;
		m_hBitmap = ::CreateDIBitmap(hDC, lpbmih, dwInit, lpbInit, lpbmi, uColorUse);
		return m_hBitmap;
	}
	HBITMAP CreateDIBSection(HDC hDC,  BITMAPINFO* lpbmi, UINT uColorUse, VOID** ppvBits, HANDLE hSection, DWORD dwOffset)
	{
		if (IsValidBitmap()) return NULL;
		m_hBitmap = ::CreateDIBSection(hDC, lpbmi, uColorUse, ppvBits, hSection, dwOffset);
		return m_hBitmap;
	}
	int GetDIBits(HDC hDC, UINT uStartScan, UINT cScanLines,  LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT uColorUse) 
	{
		if (!IsValidBitmap()) return NULL;
		return ::GetDIBits(hDC, m_hBitmap, uStartScan, cScanLines,  lpvBits, lpbmi, uColorUse);
	}
	int SetDIBits(HDC hDC, UINT uStartScan, UINT cScanLines,  VOID* lpvBits,  BITMAPINFO* lpbmi, UINT uColorUse)
	{
		if (!IsValidBitmap()) return NULL;
		return ::SetDIBits(hDC, m_hBitmap, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
	}

};



class CGDI 
{
public:
	HDC m_hDC;
public:
	
	CGDI(HDC hDC=NULL)
	{ 
		m_hDC=hDC;
	}

	/*~CGDI()
	{
		if (m_hDC != NULL)
			::DeleteDC(m_hDC);
	}*/
		
	BOOL IsValidHandle() {return m_hDC != NULL;}
	//---------------------------------------------------------------------
	int SaveDC()
	{
		if (IsValidHandle())
			return ::SaveDC(m_hDC);
		return 0;
	}

	operator HDC() {return m_hDC;}
	BOOL RestoreDC(int nSavedDC)
	{
		if (IsValidHandle())
			return ::RestoreDC(m_hDC, nSavedDC);
		return 0;
	}

	int GetDeviceCaps(int nIndex) 
	{
		if (IsValidHandle())
			return ::GetDeviceCaps(m_hDC, nIndex);
		return 0;
	}

	COLORREF GetNearestColor(COLORREF crColor) 
	{ 
		if (IsValidHandle())
			return ::GetNearestColor(m_hDC, crColor); 
		else
			return 0;
	}


	UINT SetBoundsRect(LPCRECT lpRectBounds, UINT flags)
	{
		if (IsValidHandle())
			return ::SetBoundsRect(m_hDC, lpRectBounds, flags);
		return 0;
	}
	UINT GetBoundsRect(LPRECT lpRectBounds, UINT flags) 
	{
		if (IsValidHandle())
			return ::GetBoundsRect(m_hDC, lpRectBounds, flags);
		return 0;
	}
	BOOL ResetDC( DEVMODE* lpDevMode)
	{
		if (IsValidHandle())
			if(::ResetDC(m_hDC, lpDevMode)) return TRUE;
		return 0;
	}

	
	HFONT SelectFont(HFONT hFont)
	{

		return ((HFONT)::SelectObject((m_hDC), (HGDIOBJ)(HFONT)(hFont)));
	}




	HFONT SelectObject(CFont cf)
	{
		if (IsValidHandle())
			return (HFONT) ::SelectObject(m_hDC,(HFONT)cf.GetFont());
		return NULL;
	}
	//---------------------------------------------------------------------
	HPEN SelectObject(CPen* cp)
	{
		if (IsValidHandle())
			return (HPEN) ::SelectObject(m_hDC,(HPEN)cp->GetPen());
		return NULL;
	}

	HBRUSH SelectObject(CBrush* cb)
	{
		if (IsValidHandle())
			return (HBRUSH) ::SelectObject(m_hDC,(HBRUSH)cb->GetBrush());
		return NULL;
	}
	//--------------------------------------------------------------------
	HBITMAP SelectObject(CBitmap* cb)
	{
		if (IsValidHandle())
			return (HBITMAP) ::SelectObject(m_hDC,(HBITMAP)cb->GetBitMap());
		return NULL;
	}

	//---------------------------------------------------------------------


	HGDIOBJ SelectStockObject(int fnObjec)
	{
		if (IsValidHandle())
			return ::SelectObject(m_hDC,GetStockObject(fnObjec));
		return NULL;
	}

	HWND WindowFromDC() 
	{
		if (IsValidHandle())
			return ::WindowFromDC(m_hDC);
		return NULL;
	}

	CPen GetCurrentPen() 
	{
		if (IsValidHandle())
			return CPen((HPEN)::GetCurrentObject(m_hDC, OBJ_PEN));
		return CPen(NULL);

	}
	CBrush GetCurrentBrush() 
	{
		if (IsValidHandle())
			return CBrush((HBRUSH)::GetCurrentObject(m_hDC, OBJ_BRUSH));
		return CBrush();
	}
	/*CPalette GetCurrentPalette() 
	{
		if (IsValidHandle())
		return CPaletteHandle((HPALETTE)::GetCurrentObject(m_hDC, OBJ_PAL));
	}
	CFont GetCurrentFont() 
	{
		if (IsValidHandle())
		return CFontHandle((HFONT)::GetCurrentObject(m_hDC, OBJ_FONT));
	}*/
	CBitmap GetCurrentBitmap() 
	{
		if (IsValidHandle())
			return CBitmap((HBITMAP)::GetCurrentObject(m_hDC, OBJ_BITMAP));
		return CBitmap();
	}

	HDC CreateDC(LPCTSTR lpszDriverName, LPCTSTR lpszDeviceName, LPCTSTR lpszOutput,  DEVMODE* lpInitData)
	{
		if (IsValidHandle()) return m_hDC;
		m_hDC = ::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, lpInitData);
		return m_hDC;
	}

	HDC CreateCompatibleDC(HDC hDC = NULL)
	{
		if (IsValidHandle()) return m_hDC;
			m_hDC = ::CreateCompatibleDC(hDC);
		return m_hDC;
	}

	BOOL DeleteDC()
	{
		if (!IsValidHandle()) return FALSE;
		BOOL bres = ::DeleteDC(m_hDC);
		if(bres)
			m_hDC = NULL;
		return bres;
	}

	//--------------------------------------------------------------------------------
	
	
	COLORREF GetBkColor()
	{
		if (IsValidHandle())
			return ::GetBkColor(m_hDC);
		return RGB(0,0,0);
	}
	int GetBkMode() 
	{
		if (IsValidHandle())
			return ::GetBkMode(m_hDC);
		return 0;

	}
	int GetPolyFillMode() 
	{
		if (IsValidHandle())
			return ::GetPolyFillMode(m_hDC);
		return 0;
	}
	int GetROP2() 
	{
		if (IsValidHandle())
			return ::GetROP2(m_hDC);
		return 0;
	}
	int GetStretchBltMode() 
	{
		if (IsValidHandle())
			return ::GetStretchBltMode(m_hDC);
		return 0;
	}
	COLORREF GetTextColor() 
	{
		if (IsValidHandle())
			return ::GetTextColor(m_hDC);
		return RGB(0,0,0);
	}

	COLORREF SetBkColor(COLORREF crColor)
	{
		if (IsValidHandle())
			return ::SetBkColor(m_hDC, crColor);
		return RGB(0,0,0);
	}
	int SetBkMode(int nBkMode)
	{
		if (IsValidHandle())
			return ::SetBkMode(m_hDC, nBkMode);
		return 0;
	}
	int SetPolyFillMode(int nPolyFillMode)
	{
		if (IsValidHandle())
			return ::SetPolyFillMode(m_hDC, nPolyFillMode);
		return 0;
	}
	int SetROP2(int nDrawMode)
	{
		if (IsValidHandle())
			return ::SetROP2(m_hDC, nDrawMode);
		return 0;
	}
	int SetStretchBltMode(int nStretchMode)
	{
		if (IsValidHandle())
			return ::SetStretchBltMode(m_hDC, nStretchMode);
		return 0;
	}
	COLORREF SetTextColor(COLORREF crColor)
	{
		if (IsValidHandle())
			return ::SetTextColor(m_hDC, crColor);
		return RGB(0,0,0);
	}

	BOOL GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) 
	{
		if (IsValidHandle())
			return ::GetColorAdjustment(m_hDC, lpColorAdjust);
		return FALSE;
	}
	BOOL SetColorAdjustment( COLORADJUSTMENT* lpColorAdjust)
	{
		if (IsValidHandle())
			return ::SetColorAdjustment(m_hDC, lpColorAdjust);
		return FALSE;
	}

// ---------------------------------------------------------------------
	int GetMapMode() 
	{
		if (IsValidHandle())
			return ::GetMapMode(m_hDC);
		return 0;
	}
	BOOL GetViewportOrg(LPPOINT lpPoint) 
	{
		if (IsValidHandle())
			return ::GetViewportOrgEx(m_hDC, lpPoint);
		return 0;
	}
	int SetMapMode(int nMapMode)
	{
		if (IsValidHandle())
			return ::SetMapMode(m_hDC, nMapMode);
		return 0;
	}
	// Viewport Origin
	BOOL SetViewportOrg(int x, int y, LPPOINT lpPoint = NULL)
	{
		if (IsValidHandle())
			return ::SetViewportOrgEx(m_hDC, x, y, lpPoint);
		return FALSE;
	}
	BOOL SetViewportOrg(POINT point, LPPOINT lpPointRet = NULL)
	{
		if (IsValidHandle())
			return SetViewportOrg(point.x, point.y, lpPointRet);
		return FALSE;
	}
	BOOL OffsetViewportOrg(int nWidth, int nHeight, LPPOINT lpPoint = NULL)
	{
		if (IsValidHandle())
			return ::OffsetViewportOrgEx(m_hDC, nWidth, nHeight, lpPoint);
		return FALSE;
	}

	//---------------------------------------------------------------------------
	BOOL GetViewportExt(LPSIZE lpSize) 
	{
		if (IsValidHandle())
			return ::GetViewportExtEx(m_hDC, lpSize);
		return FALSE;
	}
	BOOL SetViewportExt(int x, int y, LPSIZE lpSize = NULL)
	{
		if (IsValidHandle())
			return ::SetViewportExtEx(m_hDC, x, y, lpSize);
		return FALSE;
	}
	BOOL SetViewportExt(SIZE size, LPSIZE lpSizeRet = NULL)
	{
		if (IsValidHandle())
			return SetViewportExt(size.cx, size.cy, lpSizeRet);
		return FALSE;
	}
	BOOL ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom, LPSIZE lpSize = NULL)
	{
		if (IsValidHandle())
			return ::ScaleViewportExtEx(m_hDC, xNum, xDenom, yNum, yDenom, lpSize);
		return FALSE;
	}

	// Window Origin
	BOOL GetWindowOrg(LPPOINT lpPoint) 
	{
		if (IsValidHandle())
			return ::GetWindowOrgEx(m_hDC, lpPoint);
		return FALSE;
	}
	BOOL SetWindowOrg(int x, int y, LPPOINT lpPoint = NULL)
	{
		if (IsValidHandle())
			return ::SetWindowOrgEx(m_hDC, x, y, lpPoint);
		return FALSE;
	}
	BOOL SetWindowOrg(POINT point, LPPOINT lpPointRet = NULL)
	{
		if (IsValidHandle())
			return SetWindowOrg(point.x, point.y, lpPointRet);
		return FALSE;
	}
	BOOL OffsetWindowOrg(int nWidth, int nHeight, LPPOINT lpPoint = NULL)
	{
		if (IsValidHandle())
			return ::OffsetWindowOrgEx(m_hDC, nWidth, nHeight, lpPoint);
		return FALSE;
	}

	
	BOOL GetWindowExt(LPSIZE lpSize) 
	{
		if (IsValidHandle())
			return ::GetWindowExtEx(m_hDC, lpSize);
		return FALSE;
	}
	BOOL SetWindowExt(int x, int y, LPSIZE lpSize = NULL)
	{
		if (IsValidHandle())
			return ::SetWindowExtEx(m_hDC, x, y, lpSize);
		return FALSE;
	}
	BOOL SetWindowExt(SIZE size, LPSIZE lpSizeRet)
	{
		if (IsValidHandle())
			return SetWindowExt(size.cx, size.cy, lpSizeRet);
		return FALSE;
	}
	BOOL ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom, LPSIZE lpSize = NULL)
	{
		if (IsValidHandle())
			return ::ScaleWindowExtEx(m_hDC, xNum, xDenom, yNum, yDenom, lpSize);
		return FALSE;
	}

//-----------------------------------------------------------------------------------
	BOOL DPtoLP(LPPOINT lpPoints, int nCount = 1) 
	{
		if (IsValidHandle())
			return ::DPtoLP(m_hDC, lpPoints, nCount);
		return FALSE;
	}
	BOOL DPtoLP(LPRECT lpRect) 
	{
		if (IsValidHandle())
			return ::DPtoLP(m_hDC, (LPPOINT)lpRect, 2);
		return FALSE;
	}
	
	BOOL LPtoDP(LPPOINT lpPoints, int nCount = 1) 
	{
		if (IsValidHandle())
			return ::LPtoDP(m_hDC, lpPoints, nCount);
		return FALSE;
	}
	BOOL LPtoDP(LPRECT lpRect) 
	{
		if (IsValidHandle())
			return ::LPtoDP(m_hDC, (LPPOINT)lpRect, 2);
		return FALSE;
	}
	
//--------------------------------------------------------------------------
	BOOL FillRgn(HRGN hRgn, HBRUSH hBrush)
	{
		if (IsValidHandle())
			return ::FillRgn(m_hDC, hRgn, hBrush);
		return FALSE;
	}
	BOOL FrameRgn(HRGN hRgn, HBRUSH hBrush, int nWidth, int nHeight)
	{
		if (IsValidHandle())
			return ::FrameRgn(m_hDC, hRgn, hBrush, nWidth, nHeight);
		return FALSE;
	}
	BOOL InvertRgn(HRGN hRgn)
	{
		if (IsValidHandle())
			return ::InvertRgn(m_hDC, hRgn);
		return FALSE;
	}
	BOOL PaintRgn(HRGN hRgn)
	{
		if (IsValidHandle())
			return ::PaintRgn(m_hDC, hRgn);
		return FALSE;
	}

// ----------------------------------------------------------------------------
	int GetClipBox(LPRECT lpRect) 
	{
		if (IsValidHandle())
			return ::GetClipBox(m_hDC, lpRect);
		return 0;
	}
	BOOL PtVisible(int x, int y) 
	{
		if (IsValidHandle())
			return ::PtVisible(m_hDC, x, y);
		return FALSE;
	}
	BOOL PtVisible(POINT point) 
	{
		if (IsValidHandle())
			return ::PtVisible(m_hDC, point.x, point.y);
		return FALSE;
	}
	BOOL RectVisible(LPCRECT lpRect) 
	{
		if (IsValidHandle())
			return ::RectVisible(m_hDC, lpRect);
		return FALSE;
	}
	int SelectClipRgn(HRGN hRgn)
	{
		if (IsValidHandle())
			return ::SelectClipRgn(m_hDC, (HRGN)hRgn);
		return 0;
	}
	int ExcludeClipRect(int x1, int y1, int x2, int y2)
	{
		if (IsValidHandle())
			return ::ExcludeClipRect(m_hDC, x1, y1, x2, y2);
		return 0;
	}
	int ExcludeClipRect(LPCRECT lpRect)
	{
		if (IsValidHandle())
			return ::ExcludeClipRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
		return 0;
	}
	int ExcludeUpdateRgn(HWND hWnd)
	{
		if (IsValidHandle())
			return ::ExcludeUpdateRgn(m_hDC, hWnd);
		return 0;
	}
	int IntersectClipRect(int x1, int y1, int x2, int y2)
	{
		if (IsValidHandle())
			return ::IntersectClipRect(m_hDC, x1, y1, x2, y2);
		return 0;
	}
	int IntersectClipRect(LPCRECT lpRect)
	{
		if (IsValidHandle())
			return ::IntersectClipRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
		return 0;
	}
	int OffsetClipRgn(int x, int y)
	{
		if (IsValidHandle())
			return ::OffsetClipRgn(m_hDC, x, y);
		return 0;
	}
	int OffsetClipRgn(SIZE size)
	{
		if (IsValidHandle())
			return ::OffsetClipRgn(m_hDC, size.cx, size.cy);
		return 0;
	}
	int SelectClipRgn(HRGN hRgn, int nMode)
	{
		if (IsValidHandle())
			return ::ExtSelectClipRgn(m_hDC, hRgn, nMode);
		return 0;
	}

//--------------------------------------------------------------------------
	BOOL GetCurrentPosition(LPPOINT lpPoint) 
	{
		if (IsValidHandle())
			return ::GetCurrentPositionEx(m_hDC, lpPoint);
		return FALSE;
	}
	BOOL MoveTo(int x, int y, LPPOINT lpPoint = NULL)
	{
		if (IsValidHandle())
			return ::MoveToEx(m_hDC, x, y, lpPoint);
		return FALSE;

	}
	BOOL MoveTo(POINT point, LPPOINT lpPointRet = NULL)
	{
		if (IsValidHandle())
			return MoveTo(point.x, point.y, lpPointRet);
		return FALSE;
	}
	BOOL LineTo(int x, int y)
	{
		if (IsValidHandle())
			return ::LineTo(m_hDC, x, y);
		return FALSE;
	}
	BOOL LineTo(POINT point)
	{
		if (IsValidHandle())
			return LineTo(point.x, point.y);
		return FALSE;
	}

	BOOL DrawLine(POINT pointOr,POINT pointTar)
	{
		if (IsValidHandle())
		{
			MoveTo(pointOr);
			LineTo(pointTar);
			return TRUE;
		}
		return FALSE;
	}

	BOOL DrawLine(POINT pointOr,POINT pointTar,COLORREF clColor)
	{
		if (IsValidHandle())
		{
			CPen Color;
			Color.CreatePen(PS_SOLID,1,clColor);
			CPen pOldPen=CPen(SelectObject(&Color));
			MoveTo(pointOr);
			LineTo(pointTar);
			SelectObject(&pOldPen);	
			return TRUE;
		}
		return FALSE;
	}

	void DrawRect(CRect* rclt,COLORREF clLT,COLORREF clBR)
	{
		DrawLine(CPoint(rclt->left,rclt->top),CPoint(rclt->left,rclt->bottom),clLT);
		DrawLine(CPoint(rclt->left,rclt->top+1),CPoint(rclt->right,rclt->top+1),clLT);
		DrawLine(CPoint(rclt->right,rclt->top+1),CPoint(rclt->right,rclt->bottom),clBR);
		DrawLine(CPoint(rclt->left,rclt->bottom-1),CPoint(rclt->right,rclt->bottom-1),clBR);
	}


	BOOL Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	{
		if (IsValidHandle())
			return ::Arc(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
		return FALSE;
	}
	BOOL Arc(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		if (IsValidHandle())
			return ::Arc(m_hDC, lpRect->left, lpRect->top,
				lpRect->right, lpRect->bottom, ptStart.x, ptStart.y,
				ptEnd.x, ptEnd.y);
		return FALSE;
	}
	BOOL Polyline(LPPOINT lpPoints, int nCount)
	{
		if (IsValidHandle())
			return ::Polyline(m_hDC, lpPoints, nCount);
		return FALSE;
	}

	BOOL AngleArc(int x, int y, int nRadius, float fStartAngle, float fSweepAngle)
	{
		if (IsValidHandle())
			return ::AngleArc(m_hDC, x, y, nRadius, fStartAngle, fSweepAngle);
		return FALSE;
	}
	BOOL ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	{
		if (IsValidHandle())
			return ::ArcTo(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
		return FALSE;
	}
	BOOL ArcTo(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		if (IsValidHandle())
			return ArcTo(lpRect->left, lpRect->top, lpRect->right,
			lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
		return FALSE;
	}
	int GetArcDirection() 
	{
		if (IsValidHandle())
			return ::GetArcDirection(m_hDC);
		return FALSE;
	}
	int SetArcDirection(int nArcDirection)
	{
		if (IsValidHandle())
			return ::SetArcDirection(m_hDC, nArcDirection);
		return FALSE;
	}

	BOOL PolyDraw( POINT* lpPoints,  BYTE* lpTypes, int nCount)
	{
		if (IsValidHandle())
			return ::PolyDraw(m_hDC, lpPoints, lpTypes, nCount);
		return FALSE;
	}
	BOOL PolylineTo( POINT* lpPoints, int nCount)
	{
		if (IsValidHandle())
			return ::PolylineTo(m_hDC, lpPoints, nCount);
		return FALSE;
	}
	BOOL PolyPolyline( POINT* lpPoints,
		 DWORD* lpPolyPoints, int nCount)
	{
		if (IsValidHandle())
			return ::PolyPolyline(m_hDC, lpPoints, lpPolyPoints, nCount);
		return FALSE;
	}

	BOOL PolyBezier( POINT* lpPoints, int nCount)
	{
		if (IsValidHandle())
			return ::PolyBezier(m_hDC, lpPoints, nCount);
		return FALSE;
	}
	BOOL PolyBezierTo( POINT* lpPoints, int nCount)
	{
		if (IsValidHandle())
			return ::PolyBezierTo(m_hDC, lpPoints, nCount);
		return FALSE;
	}

// ----------------------------------------------------------------------
	
	void FillRect(LPCRECT lprc,CBrush* pBruhs)
	{
		if (IsValidHandle())
			::FillRect(m_hDC,lprc,(HBRUSH)pBruhs->GetBrush());
	}
	
	void FillRect(LPCRECT lprc,HBRUSH hBruhs)
	{
		if (IsValidHandle())
			::FillRect(m_hDC,lprc,hBruhs);
	}
	
	BOOL FrameRect(LPCRECT lpRect, HBRUSH hBrush)
	{
		if (IsValidHandle())
			return ::FrameRect(m_hDC, lpRect, hBrush);
		return FALSE;
	}
	BOOL InvertRect(LPCRECT lpRect)
	{
		if (IsValidHandle())
			return ::InvertRect(m_hDC, lpRect);
		return FALSE;
	}
	BOOL DrawIcon(int x, int y, HICON hIcon)
	{
		if (IsValidHandle())
			return ::DrawIcon(m_hDC, x, y, hIcon);
		return FALSE;
	}
	BOOL DrawIcon(POINT point, HICON hIcon)
	{
		if (IsValidHandle())
			return ::DrawIcon(m_hDC, point.x, point.y, hIcon);
		return FALSE;
	}
	BOOL DrawIconEx(int x, int y, HICON hIcon, int cxWidth, int cyWidth, UINT uStepIfAniCur = 0, HBRUSH hbrFlickerFreeDraw = NULL, UINT uFlags = DI_NORMAL)
	{
		if (IsValidHandle())
			return ::DrawIconEx(m_hDC, x, y, hIcon, cxWidth, cyWidth, uStepIfAniCur, hbrFlickerFreeDraw, uFlags);
		return FALSE;
	}
	BOOL DrawIconEx(POINT point, HICON hIcon, SIZE size, UINT uStepIfAniCur = 0, HBRUSH hbrFlickerFreeDraw = NULL, UINT uFlags = DI_NORMAL)
	{
		if (IsValidHandle())
			return ::DrawIconEx(m_hDC, point.x, point.y, hIcon, size.cx, size.cy, uStepIfAniCur, hbrFlickerFreeDraw, uFlags);
		return FALSE;
	}


	BOOL DrawState(CPoint pt, CSize size, HICON hIcon, UINT nFlags, CBrush* pBrush)
	{ 
		ASSERT(m_hDC != NULL); 
		return ::DrawState(m_hDC, (HBRUSH)pBrush->GetSafeHandle(), NULL,(LPARAM)hIcon, 0, 
			pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON); 
	}

	BOOL DrawState(POINT pt, SIZE size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush = NULL)
	{
		if (IsValidHandle())
			return ::DrawState(m_hDC, hBrush, NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_BITMAP);
		return FALSE;
	}
	BOOL DrawState(POINT pt, SIZE size, HICON hIcon, UINT nFlags, HBRUSH hBrush = NULL)
	{
		if (IsValidHandle())
			return ::DrawState(m_hDC, hBrush, NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags | DST_ICON);
		return FALSE;
	}


	BOOL DrawState(CPoint pt, CSize size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
	{ 
		ASSERT(m_hDC != NULL); 
		return ::DrawState(m_hDC, hBrush, NULL,	(LPARAM)hIcon, 0,
			pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON); 
	}

	BOOL DrawState(CPoint pt, CSize size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
	{ 
		ASSERT(m_hDC != NULL); 
		return ::DrawState(m_hDC, hBrush,NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP); 
	}

	


	BOOL DrawState(CPoint pt, CSize size, CBitmap* pBitmap, UINT nFlags, CBrush* pBrush)
	{ 
		ASSERT(m_hDC != NULL); 
		return ::DrawState(m_hDC, (HBRUSH)pBrush->GetSafeHandle(),NULL, 
			(LPARAM)pBitmap->GetSafeHandle(), 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP); 
	}

	BOOL DrawState(CPoint pt, CSize size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText, int nTextLen, CBrush* pBrush)
	{ 
		ASSERT(m_hDC != NULL); 
		return ::DrawState(m_hDC, (HBRUSH)pBrush->GetSafeHandle(),NULL, (LPARAM)lpszText, 
			(WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)); 
	}

	//	pdc->DrawState(p,m_SizeImage,m_Icon,DSS_MONO,CDrawLayer::GetRGBColorShadow());

	
	BOOL DrawState(CPoint pt, CSize size, LPCTSTR lpszText, UINT nFlags, BOOL bPrefixText, int nTextLen, HBRUSH hBrush)
	{ 
		ASSERT(m_hDC != NULL); 
		return ::DrawState(m_hDC, hBrush,NULL, (LPARAM)lpszText, 
			(WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)); 
	}
	
	

	BOOL DrawState(CPoint pt, CSize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
	{ 
		ASSERT(m_hDC != NULL); 
		return ::DrawState(m_hDC, hBrush,lpDrawProc, lData, 0, pt.x, pt.y,
			size.cx, size.cy, nFlags|DST_COMPLEX); 
	}

	BOOL DrawState(CPoint pt, CSize size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, CBrush* pBrush)
	{ 
		ASSERT(m_hDC != NULL); 
		return ::DrawState(m_hDC, (HBRUSH)pBrush->GetSafeHandle(),lpDrawProc, lData, 0, pt.x, pt.y, 
		size.cx, size.cy, nFlags|DST_COMPLEX); 
	}

	
//----------------------------------------------------------------------------------------------
	BOOL Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	{
		if (IsValidHandle())
			return ::Chord(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
		return FALSE;
	}
	BOOL Chord(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		if (IsValidHandle())
			return ::Chord(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
		return FALSE;
	}
	void DrawFocusRect(LPCRECT lpRect)
	{
		if (IsValidHandle())
			::DrawFocusRect(m_hDC, lpRect);
	}
	
	BOOL Ellipse(int x1, int y1, int x2, int y2)
	{
		if (IsValidHandle())
			return ::Ellipse(m_hDC, x1, y1, x2, y2);
		return FALSE;
	}
	BOOL Ellipse(LPCRECT lpRect)
	{
		if (IsValidHandle())
			return ::Ellipse(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
		return FALSE;
	}
	BOOL Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	{
		if (IsValidHandle())
			return ::Pie(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
		return FALSE;
	}
	BOOL Pie(LPCRECT lpRect, POINT ptStart, POINT ptEnd)
	{
		if (IsValidHandle())
			return ::Pie(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
		return FALSE;
	}
	BOOL Polygon(LPPOINT lpPoints, int nCount)
	{
		if (IsValidHandle())
			return ::Polygon(m_hDC, lpPoints, nCount);
		return FALSE;
	}
	BOOL PolyPolygon(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount)
	{
		if (IsValidHandle())
			return ::PolyPolygon(m_hDC, lpPoints, lpPolyCounts, nCount);
		return FALSE;
	}
	BOOL Rectangle(int x1, int y1, int x2, int y2)
	{
		if (IsValidHandle())
			return ::Rectangle(m_hDC, x1, y1, x2, y2);
		return FALSE;
	}
	BOOL Rectangle(LPCRECT lpRect)
	{
		if (IsValidHandle())
			return ::Rectangle(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
		return FALSE;
	}
	BOOL RoundRect(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		if (IsValidHandle())
			return ::RoundRect(m_hDC, x1, y1, x2, y2, x3, y3);
		return FALSE;
	}
	BOOL RoundRect(LPCRECT lpRect, POINT point)
	{
		if (IsValidHandle())
			return ::RoundRect(m_hDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, point.x, point.y);
		return FALSE;
	}

//------------------------------------------------------------------------------------
	BOOL PatBlt(int x, int y, int nWidth, int nHeight, DWORD dwRop)
	{
		if (IsValidHandle())
			return ::PatBlt(m_hDC, x, y, nWidth, nHeight, dwRop);
		return FALSE;
	}
	BOOL PatBlt(CRect rc, DWORD dwRop)
	{
		if (IsValidHandle())
			return ::PatBlt(m_hDC, rc.left,rc.top, rc.Width(),rc.Height(), dwRop);
		return FALSE;
	}
	BOOL BitBlt(int x, int y, int nWidth, int nHeight, HDC hSrcDC,
		int xSrc, int ySrc, DWORD dwRop)
	{
		if (IsValidHandle())
			return ::BitBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, dwRop);
		return FALSE;
	}
	BOOL BitBlt(CRect rc, HDC hSrcDC,
		int xSrc, int ySrc, DWORD dwRop)
	{
		if (IsValidHandle())
			return ::BitBlt(m_hDC, rc.left, rc.top, rc.right, rc.bottom, hSrcDC, xSrc, ySrc, dwRop);
		return FALSE;
	}
	BOOL StretchBlt(int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop)
	{
		if (IsValidHandle())
			return ::StretchBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop);
		return FALSE;
	}
	COLORREF GetPixel(int x, int y) 
	{
		if (IsValidHandle())
			return ::GetPixel(m_hDC, x, y);
		return FALSE;
	}
	COLORREF GetPixel(POINT point) 
	{
		if (IsValidHandle())
			return ::GetPixel(m_hDC, point.x, point.y);
		return FALSE;
	}
	COLORREF SetPixel(int x, int y, COLORREF crColor)
	{
		if (IsValidHandle())
			return ::SetPixel(m_hDC, x, y, crColor);
		return FALSE;
	}
	COLORREF SetPixel(POINT point, COLORREF crColor)
	{
		if (IsValidHandle())
			return ::SetPixel(m_hDC, point.x, point.y, crColor);
		return FALSE;
	}
	BOOL FloodFill(int x, int y, COLORREF crColor)
	{
		if (IsValidHandle())
			return ::FloodFill(m_hDC, x, y, crColor);
		return FALSE;
	}
	BOOL ExtFloodFill(int x, int y, COLORREF crColor, UINT nFillType)
	{
		if (IsValidHandle())
			return ::ExtFloodFill(m_hDC, x, y, crColor, nFillType);
		return FALSE;
	}
	BOOL MaskBlt(int x, int y, int nWidth, int nHeight, HDC hSrcDC, int xSrc, int ySrc, HBITMAP hMaskBitmap, int xMask, int yMask, DWORD dwRop)
	{
		if (IsValidHandle())
			return ::MaskBlt(m_hDC, x, y, nWidth, nHeight, hSrcDC, xSrc, ySrc, hMaskBitmap, xMask, yMask, dwRop);
		return FALSE;
	}
	BOOL PlgBlt(LPPOINT lpPoint, HDC hSrcDC, int xSrc, int ySrc, int nWidth, int nHeight, HBITMAP hMaskBitmap, int xMask, int yMask)
	{
		if (IsValidHandle())
			return ::PlgBlt(m_hDC, lpPoint, hSrcDC, xSrc, ySrc, nWidth, nHeight, hMaskBitmap, xMask, yMask);
		return FALSE;
	}
	BOOL SetPixelV(int x, int y, COLORREF crColor)
	{
		if (IsValidHandle())
			return ::SetPixelV(m_hDC, x, y, crColor);
		return FALSE;
	}
	BOOL SetPixelV(POINT point, COLORREF crColor)
	{
		if (IsValidHandle())
			return ::SetPixelV(m_hDC, point.x, point.y, crColor);
		return FALSE;
	}

	//------------------------------------------------------------------------------------------
	
	BOOL TextOut(int x, int y, LPCTSTR lpszString, int nCount = -1)
	{
		if (IsValidHandle())
		{
			if(nCount == -1)
				nCount = lstrlen(lpszString);
			return ::TextOut(m_hDC, x, y, lpszString, nCount);
		}
		return FALSE;

	}
	BOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect, LPCTSTR lpszString, UINT nCount = -1, LPINT lpDxWidths = NULL)
	{
		if (IsValidHandle())
		{
			if(nCount == -1)
				nCount = lstrlen(lpszString);
			return ::ExtTextOut(m_hDC, x, y, nOptions, lpRect, lpszString, nCount, lpDxWidths);
		}
		return FALSE;
	}

	long  TabbedTextOut(int x, int y, LPCTSTR lpszString, int nCount = -1, int nTabPositions = 0, LPINT lpnTabStopPositions = NULL, int nTabOrigin = 0)
	{
		if (IsValidHandle())
		{
			if(nCount == -1)
				nCount = lstrlen(lpszString);
			LONG lres = ::TabbedTextOut(m_hDC, x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
		}
		return 0;
			
	}
	int DrawText(LPCTSTR lpstrText, int cchText, LPRECT lpRect, UINT uFormat)
	{
		if (IsValidHandle())
			return ::DrawText(m_hDC, lpstrText, cchText, lpRect, uFormat);
		return 0;
	}
	int DrawTextEx(LPTSTR lpstrText, int cchText, LPRECT lpRect, UINT uFormat, LPDRAWTEXTPARAMS lpDTParams = NULL)
	{
		if (IsValidHandle())
			return ::DrawTextEx(m_hDC, lpstrText, cchText, lpRect, uFormat, lpDTParams);
		return 0;
	}

	int  DrawText(LPCTSTR lpstrText, LPRECT lpRect,UINT uFormat=0)
	{
		return DrawText(lpstrText, _tcslen(lpstrText), lpRect, uFormat);
	}


	BOOL GetTextExtent(LPCTSTR lpszString, int nCount, LPSIZE lpSize) 
	{
		if (IsValidHandle())
		{
			if(nCount == -1)
				nCount = lstrlen(lpszString);
			return ::GetTextExtentPoint32(m_hDC, lpszString, nCount, lpSize);
		}
		return FALSE;
	}


	CSize GetTextExtent(LPCTSTR lpszString, int nCount) 
	{
		CSize sc;
		GetTextExtent(lpszString, nCount, &sc); 
		return sc;
	}

	DWORD GetTabbedTextExtent(LPCTSTR lpszString, int nCount = -1, int nTabPositions = 0, LPINT lpnTabStopPositions = NULL) 
	{
		if (IsValidHandle())
		{
			if(nCount == -1)
				nCount = lstrlen(lpszString);
			return ::GetTabbedTextExtent(m_hDC, lpszString, nCount, nTabPositions, lpnTabStopPositions);
		}
		return FALSE;
	}
	BOOL GrayString(HBRUSH hBrush, BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount, int x, int y, int nWidth, int nHeight)
	{
		if (IsValidHandle())
			return ::GrayString(m_hDC, hBrush, (GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight);
		return FALSE;
	}
	UINT GetTextAlign() 
	{
		if (IsValidHandle())
			return ::GetTextAlign(m_hDC);
		return 0;
	}
	UINT SetTextAlign(UINT nFlags)
	{
		if (IsValidHandle())
			return ::SetTextAlign(m_hDC, nFlags);
		return 0;
	}
	int GetTextFace(LPTSTR lpszFacename, int nCount) 
	{
		if (IsValidHandle())
			return ::GetTextFace(m_hDC, nCount, lpszFacename);
		return 0;
	}
	int GetTextFaceLen() 
	{
		if (IsValidHandle())
			return ::GetTextFace(m_hDC, 0, NULL);
		return 0;
	}

	BOOL GetTextMetrics(LPTEXTMETRIC lpMetrics) 
	{
		if (IsValidHandle())
			return ::GetTextMetrics(m_hDC, lpMetrics);
		return FALSE;
	}
	int SetTextJustification(int nBreakExtra, int nBreakCount)
	{
		if (IsValidHandle())
			return ::SetTextJustification(m_hDC, nBreakExtra, nBreakCount);
		return 0;
	}
	int GetTextCharacterExtra() 
	{
		if (IsValidHandle())
			return ::GetTextCharacterExtra(m_hDC);
		return 0;
	}
	int SetTextCharacterExtra(int nCharExtra)
	{
		if (IsValidHandle())
			return ::SetTextCharacterExtra(m_hDC, nCharExtra);
		return 0;
	}

// -----------------------------------------------------------------------------
	BOOL DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
	{
		if (IsValidHandle())
			return ::DrawEdge(m_hDC, lpRect, nEdge, nFlags);
		return FALSE;
	}
	BOOL DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
	{
		if (IsValidHandle())
			return ::DrawFrameControl(m_hDC, lpRect, nType, nState);
		return FALSE;
	}

//-------------------------------------------------------------------------------
	BOOL ScrollDC(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate)
	{
		if (IsValidHandle())
			return ::ScrollDC(m_hDC, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate);
		return FALSE;
	}

	BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) 
	{
		if (IsValidHandle())
			return ::GetCharWidth(m_hDC, nFirstChar, nLastChar, lpBuffer);
		return FALSE;
	}

	BOOL GetCharWidth32(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) 
	{
		if (IsValidHandle())
			return ::GetCharWidth32(m_hDC, nFirstChar, nLastChar, lpBuffer);
		return FALSE;
	}
	DWORD SetMapperFlags(DWORD dwFlag)
	{
		if (IsValidHandle())
			return ::SetMapperFlags(m_hDC, dwFlag);
		return FALSE;
	}
	BOOL GetAspectRatioFilter(LPSIZE lpSize) 
	{
		if (IsValidHandle())
			return ::GetAspectRatioFilterEx(m_hDC, lpSize);
		return FALSE;
	}

	BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) 
	{
		if (IsValidHandle())
			return ::GetCharABCWidths(m_hDC, nFirstChar, nLastChar, lpabc);
		return FALSE;
	}
	DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) 
	{
		if (IsValidHandle())
			return ::GetFontData(m_hDC, dwTable, dwOffset, lpData, cbData);
		return FALSE;
	}
	int GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair) 
	{
		if (IsValidHandle())
			return ::GetKerningPairs(m_hDC, nPairs, lpkrnpair);
		return FALSE;
	}
	UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) 
	{
		if (IsValidHandle())
			return ::GetOutlineTextMetrics(m_hDC, cbData, lpotm);
		return FALSE;
	}
	DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer,  MAT2* lpmat2) 
	{
		if (IsValidHandle())
			return ::GetGlyphOutline(m_hDC, nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);
		return FALSE;
	}

	BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) 
	{
		if (IsValidHandle())
			return ::GetCharABCWidthsFloat(m_hDC, nFirstChar, nLastChar, lpABCF);
		return FALSE;
	}
	BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer) 
	{
		if (IsValidHandle())
			return ::GetCharWidthFloat(m_hDC, nFirstChar, nLastChar, lpFloatBuffer);
		return FALSE;
	}

//-------------------------------------------------------------------------------------
	int Escape(int nEscape, int nCount, LPCSTR lpszInData, LPVOID lpOutData)
	{
		if (IsValidHandle())
			return ::Escape(m_hDC, nEscape, nCount, lpszInData, lpOutData);
		return FALSE;
	}
	int Escape(int nEscape, int nInputSize, LPCSTR lpszInputData,
		int nOutputSize, LPSTR lpszOutputData)
	{
		if (IsValidHandle())
			return ::ExtEscape(m_hDC, nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
		return FALSE;
	}
	int DrawEscape(int nEscape, int nInputSize, LPCSTR lpszInputData)
	{
		if (IsValidHandle())
			return ::DrawEscape(m_hDC, nEscape, nInputSize, lpszInputData);
		return FALSE;
	}

	
	int StartDoc(LPDOCINFO lpDocInfo)
	{
		if (IsValidHandle())
			return ::StartDoc(m_hDC, lpDocInfo);
		return FALSE;
	}
	int StartPage()
	{
		if (IsValidHandle())
			return ::StartPage(m_hDC);
		return FALSE;
	}
	int EndPage()
	{
		if (IsValidHandle())
			return ::EndPage(m_hDC);
		return FALSE;
	}
	int SetAbortProc(BOOL (CALLBACK* lpfn)(HDC, int))
	{
		if (IsValidHandle())
			return ::SetAbortProc(m_hDC, (ABORTPROC)lpfn);
		return FALSE;
	}
	int AbortDoc()
	{
		if (IsValidHandle())
			return ::AbortDoc(m_hDC);
		return FALSE;
	}
	int EndDoc()
	{
		if (IsValidHandle())
			return ::EndDoc(m_hDC);
		return FALSE;
	}


	//-----------------------------------------------------------------------
	BOOL AbortPath()
	{
		if (IsValidHandle())
			return ::AbortPath(m_hDC);
		return FALSE;
	}
	BOOL BeginPath()
	{
		if (IsValidHandle())
			return ::BeginPath(m_hDC);
		return FALSE;
	}
	BOOL CloseFigure()
	{
		if (IsValidHandle())
			return ::CloseFigure(m_hDC);
		return FALSE;
	}
	BOOL EndPath()
	{
		if (IsValidHandle())
			return ::EndPath(m_hDC);
		return FALSE;
	}
	BOOL FillPath()
	{
		if (IsValidHandle())
			return ::FillPath(m_hDC);
		return FALSE;
	}
	BOOL FlattenPath()
	{
		if (IsValidHandle())
			return ::FlattenPath(m_hDC);
		return FALSE;
	}
	BOOL StrokeAndFillPath()
	{
		if (IsValidHandle())
			return ::StrokeAndFillPath(m_hDC);
		return FALSE;
	}
	BOOL StrokePath()
	{
		if (IsValidHandle())
			return ::StrokePath(m_hDC);
		return FALSE;
	}
	BOOL WidenPath()
	{
		if (IsValidHandle())
			return ::WidenPath(m_hDC);
		return FALSE;
	}
	BOOL GetMiterLimit(PFLOAT pfMiterLimit) 
	{
		if (IsValidHandle())
			return ::GetMiterLimit(m_hDC, pfMiterLimit);
		return FALSE;
	}
	BOOL SetMiterLimit(float fMiterLimit)
	{
		if (IsValidHandle())
			return ::SetMiterLimit(m_hDC, fMiterLimit, NULL);
		return FALSE;
	}
	int GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int nCount) 
	{
		if (IsValidHandle())
			return ::GetPath(m_hDC, lpPoints, lpTypes, nCount);
		return FALSE;
	}
	BOOL SelectClipPath(int nMode)
	{
		if (IsValidHandle())
			return ::SelectClipPath(m_hDC, nMode);
		return FALSE;
	}

	
	//-----------------------------------------------------------------------------------
	int SetDIBitsToDevice(int x, int y, DWORD dwWidth, DWORD dwHeight, int xSrc, int ySrc, UINT uStartScan, UINT cScanLines,  VOID* lpvBits,  BITMAPINFO* lpbmi, UINT uColorUse)
	{
		if (IsValidHandle())
			return ::SetDIBitsToDevice(m_hDC, x, y, dwWidth, dwHeight, xSrc, ySrc, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
		return 0;
	}
	int StretchDIBits(int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight,  VOID* lpvBits,  BITMAPINFO* lpbmi, UINT uColorUse, DWORD dwRop)
	{
		if (IsValidHandle())
			return ::StretchDIBits(m_hDC, x, y, nWidth, nHeight, xSrc, ySrc, nSrcWidth, nSrcHeight, lpvBits, lpbmi, uColorUse, dwRop);
		return 0;
	}
	UINT GetDIBColorTable(UINT uStartIndex, UINT cEntries, RGBQUAD* pColors) 
	{
		if (IsValidHandle())
			return ::GetDIBColorTable(m_hDC, uStartIndex, cEntries, pColors);
		return 0;
	}
	UINT SetDIBColorTable(UINT uStartIndex, UINT cEntries,  RGBQUAD* pColors)
	{
		if (IsValidHandle())
			return ::SetDIBColorTable(m_hDC, uStartIndex, cEntries, pColors);
		return 0;
	}


#if (_WIN32_WINNT >= 0x0500)

	COLORREF GetDCPenColor() 
	{
		if (IsValidHandle())
			return ::GetDCPenColor(m_hDC);
		return RGB(0,0,0);
	}
	COLORREF SetDCPenColor(COLORREF clr)
	{
		if (IsValidHandle())
			return ::SetDCPenColor(m_hDC, clr);
		return RGB(0,0,0);
	}
	COLORREF GetDCBrushColor() 
	{
		if (IsValidHandle())
			return ::GetDCBrushColor(m_hDC);
		return RGB(0,0,0);
	}
	COLORREF SetDCBrushColor(COLORREF clr)
	{
		if (IsValidHandle())
			return ::SetDCBrushColor(m_hDC, clr);
		return RGB(0,0,0);
	}

	DWORD GetFontUnicodeRanges(LPGLYPHSET lpgs) 
	{
		if (IsValidHandle())
			return ::GetFontUnicodeRanges(m_hDC, lpgs);
		return 0;
	}
	DWORD GetGlyphIndices(LPCTSTR lpstr, int cch, LPWORD pgi, DWORD dwFlags) 
	{
		if (IsValidHandle())
			return ::GetGlyphIndices(m_hDC, lpstr, cch, pgi, dwFlags);
		return 0;
	}

	BOOL GetTextExtentPointI(LPWORD pgiIn, int cgi, LPSIZE lpSize) 
	{
		if (IsValidHandle())
			return ::GetTextExtentPointI(m_hDC, pgiIn, cgi, lpSize);
		return FALSE;
	}
	BOOL GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) 
	{
		if (IsValidHandle())
			return ::GetTextExtentExPointI(m_hDC, pgiIn, cgi, nMaxExtent, lpnFit, alpDx, lpSize);
		return FALSE;
	}
	BOOL GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) 
	{
		if (IsValidHandle())
			return ::GetCharWidthI(m_hDC, giFirst, cgi, pgi, lpBuffer);
		return FALSE;
	}
	BOOL GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) 
	{
		if (IsValidHandle())
			return ::GetCharABCWidthsI(m_hDC, giFirst, cgi, pgi, lpabc);
		return FALSE;
	}

#endif 


#if (WINVER >= 0x0500)

	BOOL ColorCorrectPalette(HPALETTE hPalette, DWORD dwFirstEntry, DWORD dwNumOfEntries)
	{
		if (IsValidHandle())
			return ::ColorCorrectPalette(m_hDC, hPalette, dwFirstEntry, dwNumOfEntries);
		return FALSE;
	}
#endif
	
	void FillSolidRect(LPCRECT lpRect, COLORREF clr)
	{
		
		if (!IsValidHandle()) return ;
		::SetBkColor(m_hDC, clr);
		::ExtTextOut(m_hDC, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
	}

	void FillSolidRect(int x, int y, int cx, int cy, COLORREF clr)
	{
		if (!IsValidHandle()) return ;

		::SetBkColor(m_hDC, clr);
		CRect rect(x, y, x + cx, y + cy);
		::ExtTextOut(m_hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
	}

	void Draw3dRect(LPCRECT lpRect,	COLORREF clrTopLeft, COLORREF clrBottomRight)
	{
		Draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left,
			lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
	}

	void Draw3dRect(int x, int y, int cx, int cy,
		COLORREF clrTopLeft, COLORREF clrBottomRight)
	{
		FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
		FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
		FillSolidRect(x + cx, y, -1, cy, clrBottomRight);
		FillSolidRect(x, y + cy, cx, -1, clrBottomRight);
	}

	void DrawTextAjust(CRect rc,LPCSTR lpString, UINT uFormatDrop, UINT uFormatNormal)
	{
		TCHAR m_cadBreak[64];
		memset(m_cadBreak,0x00,64);
		lstrcpy(m_cadBreak,lpString);
		int contt;
		int cont =contt=strlen(m_cadBreak);
		CSize coor=GetTextExtent(m_cadBreak,cont);
		if ( coor.cx > rc.Width())
		{
			rc.left+=1;
			while(cont > 1 )
			{
				TCHAR m_scadtemp[64];
				memset(m_scadtemp,0x00,64);
				lstrcpy(m_scadtemp,m_cadBreak);
				lstrcat(m_scadtemp,_T("..."));
				CSize coor=GetTextExtent(m_scadtemp,lstrlen(m_scadtemp));
				if(coor.cx > rc.Width())
					*(m_cadBreak+cont)=NULL;
				else
					break;
				cont--;
			}
			lstrcat(m_cadBreak,_T("..."));
			rc.right+=3;
			
				DrawText(m_cadBreak,rc,uFormatDrop);
		}
		else
				DrawText(lpString,rc,uFormatNormal);
		
	}

	static CBrush* HalftGray()
	{
		const WORD GrayBmp[] = {0x0055, 0x00AA, 0x0055, 0x00AA,
				0x0055, 0x00AA, 0x0055, 0x00AA};
		HBITMAP hGray= ::CreateBitmap(8, 8, 1, 1, &GrayBmp);
		CBrush* cb=new CBrush();
		cb->CreatePatternBrush(hGray);
		DeleteObject((HGDIOBJ)hGray);
		return cb;

	}

	
	
};



/*
 *  CGradient Class, draw a gradient background and special color
 * 
 **/

class CGradient  
{
public:
	CGradient(CSize Size=CSize(800,600))
	{
		m_Size=Size;
		m_dcMem=NULL;
	}

	CGradient::~CGradient()
	{
		if(m_dcMem!=NULL)
		{
			m_dcMem->DeleteDC();
			delete m_dcMem;
		}
	}
	CSize CGradient::GetDimensions()
	{
		return m_Size;
	}

	void  CGradient::SetDimensions(CSize Size)
	{
		m_Size=Size;
	}

	virtual void PrepareVertical(CGDI* pDC,DWORD m_StyleDisplay=GUISTYLE_XP,COLORREF m_clr=CDrawLayer::GetRGBColorTabs(), int nRate=40)
		{
		BYTE byRvalue =GetRValue(m_clr);//+(nRate==40 ?10:(15));
		BYTE byGvalue =GetGValue(m_clr);//+(nRate==40 ?10:(15));
		BYTE byBvalue =GetBValue(m_clr);//+(nRate==40 ?10:(15));
	/*	if (m_StyleDisplay!= GUISTYLE_XP )
		{
			COLORREF clrNear=pDC->GetNearestColor(CDrawLayer::GetRGBCaptionXP());
			if (clrNear==13595707)
				PrepareVertical(pDC,222,234,253,141,178,223);
			else if(clrNear==8039069)
				PrepareVertical(pDC,243,251,221,179,194,138);
			else if(clrNear==13221564)
				PrepareVertical(pDC,248,248,250,165,160,184);
		}
		else*/
			PrepareVertical(pDC,255,255,255,byRvalue-10,byGvalue-10,byBvalue-10);
	}

	void PrepareCaption(CGDI* pDC,DWORD m_StyleDisplay=GUISTYLE_XP)
	{
		
		COLORREF clrNear=pDC->GetNearestColor(CDrawLayer::GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareVertical(pDC,222,234,253,141,178,223);
		else if(clrNear==8039069)
			PrepareVertical(pDC,243,251,221,179,194,138);
		else if(clrNear==13221564)
			PrepareVertical(pDC,248,248,250,165,160,184);
		else
		{
			PrepareVertical(pDC);
		}
	}

	void PrepareCaptionVert(CGDI* pDC,DWORD m_StyleDisplay=GUISTYLE_XP)
	{
		BYTE byRvalue ;
		BYTE byGvalue ;
		BYTE byBvalue ;
		
		if (m_StyleDisplay!= GUISTYLE_XP)
		{
			PrepareHorizontal(pDC,249,200,102,248,248,205);
			return;
		}
		else if (m_StyleDisplay == GUISTYLE_2003)
		{
			byRvalue =GetRValue(CDrawLayer::GetRGBPressBXP());
			byGvalue =GetGValue(CDrawLayer::GetRGBPressBXP());
			byBvalue =GetBValue(CDrawLayer::GetRGBPressBXP());
		}
		else
		{
			byRvalue =GetRValue(CDrawLayer::GetRGBColorShadow());
			byGvalue =GetGValue(CDrawLayer::GetRGBColorShadow());
			byBvalue =GetBValue(CDrawLayer::GetRGBColorShadow());
		}
		PrepareHorizontal(pDC,byRvalue,byGvalue,byBvalue,byRvalue-40,byGvalue-40,byBvalue-40);
	}

	void CGradient::PrepareTabs(CGDI* pDC, COLORREF m_clrL,COLORREF m_clrH)
	{

		BYTE byRvalueL =GetRValue(m_clrL);
		BYTE byGvalueL =GetGValue(m_clrL);
		BYTE byBvalueL =GetBValue(m_clrL);

		BYTE byRvalueH =GetRValue(m_clrH);
		BYTE byGvalueH =GetGValue(m_clrH);
		BYTE byBvalueH =GetBValue(m_clrH);
		PrepareVertical(pDC,byRvalueL,byGvalueL,byBvalueL,byRvalueH,byGvalueH,byBvalueH);
	}
	
	void PrepareReverseVert(CGDI* pDC,DWORD m_StyleDisplay=GUISTYLE_XP, COLORREF m_clr=CDrawLayer::GetRGBColorTabs())
	{

		BYTE byRvalue =GetRValue(CDrawLayer::GetRGBColorFace());
		BYTE byGvalue =GetGValue(CDrawLayer::GetRGBColorFace());
		BYTE byBvalue =GetBValue(CDrawLayer::GetRGBColorFace());
	/*	if (m_StyleDisplay!= GUISTYLE_XP)
		{
			COLORREF clrNear=pDC->GetNearestColor(CDrawLayer::GetRGBCaptionXP());
			if (clrNear==13595707)
				PrepareVertical(pDC,141,178,223,222,234,253);
			else if(clrNear==8039069)
				PrepareVertical(pDC,179,194,138,243,251,221);
			else if(clrNear==13221564)
				PrepareVertical(pDC,165,160,184,248,248,250);
		}
		else*/
			PrepareVertical(pDC,byRvalue-40,byGvalue-40,byBvalue-40,255,255,255);
		//PrepareVertical(pDC,byRvalue-2,byGvalue-2,byBvalue-2,byRvalue,byGvalue,byBvalue);
	}

	void PrepareReverseVertTab(CGDI* pDC,DWORD m_StyleDisplay=GUISTYLE_XP, COLORREF m_clr=CDrawLayer::GetRGBColorTabs())
	{

		BYTE byRvalue =GetRValue(m_clr);
		BYTE byGvalue =GetGValue(m_clr);
		BYTE byBvalue =GetBValue(m_clr);
		if (m_StyleDisplay!= GUISTYLE_XP)
		{
			COLORREF clrNear=pDC->GetNearestColor(CDrawLayer::GetRGBCaptionXP());
			if (clrNear==13595707)
				PrepareVertical(pDC,216,228,243,255,255,255);
			else if(clrNear==8039069)
				PrepareVertical(pDC,233,237,220,255,255,255);
			else if(clrNear==13221564)
				PrepareVertical(pDC,234,233,239,255,255,255);
		}
		else
		PrepareVertical(pDC,byRvalue-10,byGvalue-10,byBvalue-10,byRvalue,byGvalue,byBvalue);
	}

	void PrepareReverseColorTab(CGDI* pDC,DWORD m_StyleDisplay=GUISTYLE_XP, COLORREF m_clrL=CDrawLayer::GetRGBColorTabs(), COLORREF m_clrH=CDrawLayer::GetRGBColorTabs())
	{

		BYTE byRvalueL =GetRValue(m_clrL);
		BYTE byGvalueL =GetGValue(m_clrL);
		BYTE byBvalueL =GetBValue(m_clrL);

		BYTE byRvalueH =GetRValue(m_clrH);
		BYTE byGvalueH =GetGValue(m_clrH);
		BYTE byBvalueH =GetBValue(m_clrH);

		PrepareVertical(pDC,byRvalueL,byGvalueL,byBvalueL,byRvalueH,byGvalueH,byBvalueH);
	}
		
	virtual void PrepareReverseHor(CGDI* pDC,COLORREF m_clr=CDrawLayer::GetRGBColorFace(),COLORREF m_clr1=CDrawLayer::GetRGBColorShadow())
	{
		BYTE byRvalue =GetRValue(m_clr);
		BYTE byGvalue =GetGValue(m_clr);
		BYTE byBvalue =GetBValue(m_clr);
		BYTE byRvalue1 =GetRValue(m_clr1);
		BYTE byGvalue1 =GetGValue(m_clr1);
		BYTE byBvalue1 =GetBValue(m_clr1);
		/*if (m_StyleDisplay!= GUISTYLE_XP)
		{
			COLORREF clrNear=pDC->GetNearestColor(CDrawLayer::GetRGBCaptionXP());
			if (clrNear==13595707)
				PrepareHorizontal(pDC,222,234,253,141,178,223);
			else if(clrNear==8039069)
				PrepareHorizontal(pDC,243,251,221,179,194,138);
			else if(clrNear==13221564)
				PrepareHorizontal(pDC,248,248,250,165,160,184);
		}
		else*/
			PrepareHorizontal(pDC,byRvalue1,byGvalue1,byBvalue1,byRvalue,byGvalue,byBvalue);
			//PrepareHorizontal(pDC,byRvalue,byGvalue,byBvalue,byRvalue-40,byGvalue-40,byBvalue-40);
		
	}
	
	virtual void PrepareHorizontal(CGDI* pDC,COLORREF m_clrBase=CDrawLayer::GetRGBColorTabs(),COLORREF m_clr=CDrawLayer::GetRGBColorFace())
	{
		BYTE byRvalue =GetRValue(m_clrBase)+10;
		BYTE byGvalue =GetGValue(m_clrBase)+10;
		BYTE byBvalue =GetBValue(m_clrBase)+10;
		BYTE byRvalue1 =GetRValue(m_clr);
		BYTE byGvalue1 =GetGValue(m_clr);
		BYTE byBvalue1 =GetBValue(m_clr);
		PrepareHorizontal(pDC,byRvalue1-10,byGvalue1-10,byBvalue1-10,255,255,255);
	}
	
	virtual void PrepareVertical(CGDI *pDC,UINT RTop,UINT GTop,UINT BTop,UINT RBot,UINT GBot,UINT BBot)
	{
		//Here we will create a memory bitmap and draw the colored bitmap on it
		//using my pretty Algorithm for generating colors.

		//if we have already a drawn DC then delete it so we will not have a
		//memory leak

		if(m_dcMem!=NULL)
		{
			m_dcMem->DeleteDC();
			delete m_dcMem;
			
		}

		//create the Memory Bitmap
		CBitmap Bitmap;
		m_dcMem=new CGDI;	//new Device Context
		m_dcMem->CreateCompatibleDC(pDC->m_hDC);	//Make it Compatible with pDC
		m_dcMem->SetMapMode(MM_TEXT);		//Pixels Mapping Mode
		//Make the Bitmap compatible with the memory DC
		Bitmap.CreateCompatibleBitmap(pDC->m_hDC,m_Size.cx,m_Size.cy);	
		//Select the bitmap into the memory DC
		m_dcMem->SelectObject(&Bitmap);

		////////////////////////////////////////////////////////////////
		////Drawing The Gradient in a MemDC
		////////////////////////////////////////////////////////////////
		//ALGORITHM:
		//We will have the RGB values of the color at which we will start
		//and the RGB values of the color at which we will end
		//we will fill 256 rectangles using all colors that lie between
		//these two colors. this is done by moving the R,G, and B values slowly
		//from the Starting color to the Ending Color.
		//For example: if we have RTop=100 and RBot=150 then we will draw 256
		//rectangles colored with the R-values of 100,100+(150-100)/256,
		//100+2*(150-100)/256,100+3*(150-100)/256,...
		//and the same will happen to G and B values.
		
		//rStep,gStep, and bStep are variables that will be used
		//to hold the values at which R,G,B will be changed respectivily
		//For example: if we have RTop=100 and RBot=150 then 
		//rStep=(150-100)/256 so when we start at R=100 and draw 256 rectangles
		//we will end at R=150 when we finish drawing these rectangles
		double rStep,gStep,bStep;
		double rCount,gCount,bCount;
		double RectHeight=m_Size.cy/256.0;
		const int NUM_COLORS=256;
		//We will start counting from TopColor to BottomColor
		//So we give an initial value of the TopColor
		rCount=RTop;
		gCount=GTop;
		bCount=BTop;
		//Calcualte the step of R,G,B values
		rStep=-((double)RTop-RBot)/NUM_COLORS;
		gStep=-((double)GTop-GBot)/NUM_COLORS;
		bStep=-((double)BTop-BBot)/NUM_COLORS;
		for(int ColorCount=0;ColorCount<NUM_COLORS;ColorCount++)
		{
			//Draw using current RGB values and Change RGB values
			//to represent the next color in the chain
			m_dcMem->FillRect(CRect(0,ColorCount*RectHeight,m_Size.cx,(ColorCount+1)*RectHeight),&CBrush(RGB(rCount,gCount,bCount)));
			rCount+=rStep;
			gCount+=gStep;
			bCount+=bStep;
			
		}
		Bitmap.DeleteObject();
		
	}

	void PrepareHorizontal(CGDI *pDC,UINT RLeft,UINT GLeft,UINT BLeft,UINT RRight,UINT GRight,UINT BRight)
	{
		if(m_dcMem!=NULL)
		{
			m_dcMem->DeleteDC();
			delete m_dcMem;
			
		}
		CBitmap Bitmap;
		m_dcMem=new CGDI;
		m_dcMem->CreateCompatibleDC(pDC->m_hDC);
		m_dcMem->SetMapMode(MM_TEXT);
		Bitmap.CreateCompatibleBitmap(pDC->m_hDC,m_Size.cx,m_Size.cy);
		m_dcMem->SelectObject(&Bitmap);

		////////////////////////////////////////////////////////////////
		////Drawing The Gradient in a MemDC
		double rStep,gStep,bStep;
		double rCount,gCount,bCount;
		double RectWidth=m_Size.cx/256.0;
		const int NUM_COLORS=256;
		rCount=RRight;
		gCount=GRight;
		bCount=BRight;
		rStep=-((double)RRight-RLeft)/NUM_COLORS;
		gStep=-((double)GRight-GLeft)/NUM_COLORS;
		bStep=-((double)BRight-BLeft)/NUM_COLORS;
	
		for(int ColorCount=0;ColorCount<NUM_COLORS;ColorCount++)
		{
			m_dcMem->FillRect(CRect(ColorCount*RectWidth,0,(ColorCount+1)*RectWidth,m_Size.cy),&CBrush(RGB(rCount,gCount,bCount)));
			rCount+=rStep;
			gCount+=gStep;
			bCount+=bStep;
		
		}
	
		Bitmap.DeleteObject();
	}

	void CGradient::Draw(CGDI *pDC, int xDest,int yDest,int xSrc, int ySrc, int Width, int Height,DWORD Rop)
	{
		//Use BitBlt to Draw on a DC
		
		pDC->BitBlt(xDest,yDest,Width,Height,m_dcMem->m_hDC,xSrc,ySrc,Rop);
	

		
	}
	

protected:
	CGDI *m_dcMem;
	CSize m_Size;
	HDC memDC;


};



/*
 *  Menu Class
 *   
 **/




class CMenu
{
	HMENU m_hMenu;
public:
	CMenu(HMENU hMenu=NULL)
	{
		m_hMenu=hMenu; 
	};
	~CMenu()
	{
		DestroyMenu(); 
	};

public:

	

	BOOL DestroyMenu()
	{
		if (m_hMenu == NULL)
			return FALSE;
		return ::DestroyMenu(m_hMenu);
	}

	HMENU	GetHandleMenu()
	{
		return m_hMenu;
	}

	BOOL LoadMenu(LPCTSTR lpszMenuName)
	{
		if (lpszMenuName != NULL)
		{
			
			if ((m_hMenu = ::LoadMenu(GetModuleHandle(NULL), lpszMenuName)) == NULL)
			{
				return FALSE;
			}
			
			return TRUE;
		}
		return FALSE;
	}

	BOOL LoadMenuIndirect( void* lpMenuTemplate)
	{
		ASSERT(m_hMenu == NULL);
		if(!(m_hMenu = ::LoadMenuIndirect(lpMenuTemplate)))
			return FALSE;
		return TRUE;
	}

	BOOL CreateMenu()
	{
		ASSERT(m_hMenu == NULL);
		if (!(m_hMenu = ::CreateMenu()))
			return FALSE;
		return TRUE;
	}

	BOOL CreatePopupMenu()
	{
		ASSERT(m_hMenu == NULL);
		if (!(m_hMenu = ::CreatePopupMenu()))
			 return FALSE;
		return TRUE;
	}

	BOOL DeleteMenu(UINT uPosition, UINT uFlags=MF_BYCOMMAND)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::DeleteMenu(m_hMenu, uPosition, uFlags);
	}

	BOOL TrackPopupMenu(UINT uFlags, int x, int y, HWND hWndParent,LPCRECT lpRect = NULL,int nReserve=0)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::TrackPopupMenu(m_hMenu, uFlags, x, y, nReserve, hWndParent, lpRect);
	}

	BOOL TrackPopupMenuEx(UINT fuFlags, int x, int y, HWND hWnd, LPTPMPARAMS lptpm = NULL)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::TrackPopupMenuEx(m_hMenu, fuFlags, x, y, hWnd, lptpm);
	}


	BOOL AppendMenu(UINT uFlags=MF_STRING, UINT uIDNewItem = 0, LPCTSTR lpszNewItem = NULL)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::AppendMenu(m_hMenu, uFlags, uIDNewItem, lpszNewItem);
	}

	UINT CheckMenuItem(UINT uIDCheckItem, UINT uCheck=MF_BYCOMMAND)
	{
		ASSERT(::IsMenu(m_hMenu));
		return (UINT)::CheckMenuItem(m_hMenu, uIDCheckItem, uCheck);
	}

	UINT EnableMenuItem(UINT uIDEnableItem, UINT uEnable)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::EnableMenuItem(m_hMenu, uIDEnableItem, uEnable);
	}
	BOOL HiliteMenuItem(HWND hWnd, UINT uIDHiliteItem, UINT uHilite)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::HiliteMenuItem(hWnd, m_hMenu, uIDHiliteItem, uHilite);
	}
	int GetMenuItemCount() 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuItemCount(m_hMenu);
	}
	UINT GetMenuItemID(int nPos) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuItemID(m_hMenu, nPos);
	}
	UINT GetMenuState(UINT uID, UINT uFlags) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuState(m_hMenu, uID, uFlags);
	}
	int GetMenuString(UINT uIDItem, LPTSTR lpString, int nMaxCount, UINT uFlags=MF_BYCOMMAND) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuString(m_hMenu, uIDItem, lpString, nMaxCount, uFlags);
	}
	int GetMenuStringLen(UINT uIDItem, UINT uFlags=MF_BYCOMMAND) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuString(m_hMenu, uIDItem, NULL, 0, uFlags);
	}


	HMENU GetSubMenu(int nPos) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetSubMenu(m_hMenu, nPos);
	}
	BOOL InsertMenu(UINT uPosition, UINT uFlags, UINT uIDNewItem = 0, LPCTSTR lpszNewItem = NULL)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::InsertMenu(m_hMenu, uPosition, uFlags, uIDNewItem, lpszNewItem);
	}
	

	BOOL ModifyMenu(UINT uPosition, UINT uFlags, UINT uIDNewItem = 0, LPCTSTR lpszNewItem = NULL)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::ModifyMenu(m_hMenu, uPosition, uFlags, uIDNewItem, lpszNewItem);
	}
	
	BOOL RemoveMenu(UINT uPosition, UINT uFlags)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::RemoveMenu(m_hMenu, uPosition, uFlags);
	}
	BOOL SetMenuItemBitmaps(UINT uPosition, UINT uFlags, HBITMAP hBmpUnchecked, HBITMAP hBmpChecked)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::SetMenuItemBitmaps(m_hMenu, uPosition, uFlags, hBmpUnchecked, hBmpChecked);
	}
	BOOL CheckMenuRadioItem(UINT uIDFirst, UINT uIDLast, UINT uIDItem, UINT uFlags)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::CheckMenuRadioItem(m_hMenu, uIDFirst, uIDLast, uIDItem, uFlags);
	}

	BOOL GetMenuItemInfo(UINT uItem, BOOL bByPosition, LPMENUITEMINFO lpmii) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return (BOOL)::GetMenuItemInfo(m_hMenu, uItem, bByPosition, lpmii);
	}
	BOOL SetMenuItemInfo(UINT uItem, BOOL bByPosition, LPMENUITEMINFO lpmii)
	{
		ASSERT(::IsMenu(m_hMenu));
		return (BOOL)::SetMenuItemInfo(m_hMenu, uItem, bByPosition, lpmii);
	}
	BOOL InsertMenuItem(UINT uItem, BOOL bByPosition, LPMENUITEMINFO lpmii)
	{
		ASSERT(::IsMenu(m_hMenu));
		return (BOOL)::InsertMenuItem(m_hMenu, uItem, bByPosition, lpmii);
	}

	UINT GetMenuDefaultItem(BOOL bByPosition = FALSE, UINT uFlags = 0U) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuDefaultItem(m_hMenu, (UINT)bByPosition, uFlags);
	}
	BOOL SetMenuDefaultItem(UINT uItem = (UINT)-1,  BOOL bByPosition = FALSE)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::SetMenuDefaultItem(m_hMenu, uItem, (UINT)bByPosition);
	}
	BOOL GetMenuItemRect(HWND hWnd, UINT uItem, LPRECT lprcItem) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuItemRect(hWnd, m_hMenu, uItem, lprcItem);
	}
	int MenuItemFromPoint(HWND hWnd, POINT point) 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::MenuItemFromPoint(hWnd, m_hMenu, point);
	}


	BOOL SetMenuContextHelpId(DWORD dwContextHelpId)
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::SetMenuContextHelpId(m_hMenu, dwContextHelpId);
	}
	DWORD GetMenuContextHelpId() 
	{
		ASSERT(::IsMenu(m_hMenu));
		return ::GetMenuContextHelpId(m_hMenu);
	}

	

	void Attach(HMENU hMenu)
	{
		ASSERT(::IsMenu(hMenu));
		DestroyMenu();
		m_hMenu = hMenu;
	}

	HMENU Detach()
	{
		HMENU hMenu = m_hMenu;
		m_hMenu = NULL;
		return hMenu;
	}


};

class CMenuItemInfo : public MENUITEMINFO
{
public:
	CMenuItemInfo()
	{
		memset(this, 0, sizeof(MENUITEMINFO));
		cbSize = sizeof(MENUITEMINFO);
	}
	
	operator LPMENUITEMINFO()
	{ 
		return this; 
	}
};

/*
 *   CArray class
 *   
 **/


class CArray
{
	void** m_pData;
	int	   m_MaxSize;
	
	public:

	CArray()
	{
		m_pData=NULL;
		m_MaxSize=0;
	}


	~CArray() 
	{
		delete [] (LPBYTE) m_pData;
	}
	
	void Reset()
	{
		AllocMemory(0);
		delete [] (LPBYTE) m_pData;
		m_pData=NULL;
		m_MaxSize=0;
	}
	void AllocMemory(int NewSize)
	{
		
		if(NewSize < 0)
			return;
		if(NewSize==0)
		{
			delete[] (LPBYTE) m_pData;
			m_pData=NULL;
			m_MaxSize=0;
		}
		else if (m_pData == NULL)
		{
			m_pData = (void**) new BYTE[NewSize * sizeof(void*)];

			memset(m_pData, 0, NewSize * sizeof(void*));  

			m_MaxSize = NewSize;
		}
		else
		{
			if(NewSize > m_MaxSize) //se incrementa el arreglo en NewSize- m_MaxSize
			{
				void** m_pTempData= (void** ) new BYTE[NewSize* sizeof(void*)];
				memcpy(m_pTempData,m_pData,m_MaxSize * sizeof(void*));
				//memset(&m_pTempData,0x00,(NewSize-m_MaxSize)* sizeof(void*));
				delete[] (LPBYTE) m_pData;
				m_pData=m_pTempData;
				m_MaxSize=NewSize;
			}
			else  
				memset(&m_pData,0x00,(m_MaxSize-NewSize)* sizeof(void*));
			
		}
		
	}


	void SetAtGrow(int nIndex, void* newElement)
	{	
	
		if(nIndex < 0)
			return;
		if (nIndex >= m_MaxSize)
			AllocMemory(nIndex+1);
		
		m_pData[nIndex] = newElement;
	}
	
	void RemoveAt(int nIndex, int nNumItem)
	{
		if(nIndex >= 0 && nNumItem >= 0)
		{
			if(nIndex + nNumItem <= m_MaxSize)
			{	
			
				int nDiff = m_MaxSize - (nIndex + nNumItem);

				if (nDiff)
					memmove(&m_pData[nIndex], &m_pData[nIndex + nNumItem],nDiff * sizeof(void*));
				m_MaxSize -= nNumItem;
			}
		}
	}

	void InsertAt(int nIndex, void* newElement)
	{

		ASSERT(nIndex >= 0);  

		if (nIndex >= m_MaxSize)
			AllocMemory(nIndex+1);  
		else
		{
			int nSize = m_MaxSize;
			AllocMemory(m_MaxSize + 1);  
			memmove(&m_pData[nIndex+1], &m_pData[nIndex],
				(nSize-nIndex) * sizeof(void*));

			memset(&m_pData[nIndex], 0, sizeof(void*));
		}

		m_pData[nIndex] = newElement;

	}

	void SetAt(int nIndex, void* newElement)
	{

		ASSERT(nIndex >= 0);  

		if (nIndex >= m_MaxSize)
			return;  
		else
			m_pData[nIndex] = newElement;

	}

	void RemoveAll()
	{
		AllocMemory(0);
	}

	int GetSize()
	{
		return m_MaxSize;
	}

	void* operator[](int nIndex) 
	{
		ASSERT(nIndex <= m_MaxSize && nIndex >= 0);
		return m_pData[nIndex];
	}
	
	void* GetAt(int nIndex)
	{
		ASSERT(nIndex <= m_MaxSize && nIndex >= 0);
		return m_pData[nIndex];
	}
		
};	

class CString
{

	int m_nSize;
	int	m_nRef;

protected:
	LPTSTR	m_pData;
public:

	CString()
	{
		InitString();
	}

	
	CString(TCHAR ch, int nRepeat = 1)
	{
		InitString();
		if (nRepeat >= 1)
		{
			AllocMemory(nRepeat);
			memset(m_pData, ch, nRepeat);
		}
	}
	

	CString(LPCSTR lpsz)
	{
		InitString();
		m_nSize=strlen(lpsz);
		if (m_nSize > 0)
		{
			AllocMemory(m_nSize);
			memcpy(m_pData,lpsz, m_nSize* sizeof(TCHAR));
		}
	}

	CString(const unsigned char* lpsz)
	{ 
		InitString();
		*this=(LPCSTR)lpsz;
	}
	

	~CString()
	{
		if(m_nRef <= 0)
			delete [] (BYTE*)m_pData;
		m_pData=NULL;
	}

public:

	void InitString()
	{
		m_pData=NULL;
		m_nSize=0;
		m_nRef=0;
	}
	

	int GetLength() 
	{
		return m_nSize;
	}
	BOOL IsEmpty() 
	{
		return (BOOL) !m_nSize;
	}
	
	void Empty()
	{
		if (m_nSize) return;
		if(m_nRef <= 0)
			delete [] (BYTE*)m_pData;
	}

	TCHAR GetAt(int nIndex) 
	{
		ASSERT(nIndex >=0  && nIndex < GetLength());
		return m_pData[nIndex];
	}
	
	void SetAt(int nIndex, TCHAR ch)
	{
		ASSERT(nIndex < m_nSize);
		CopyBeforeWrite();
		if (m_pData)
			m_pData[nIndex]=ch;
		
	}
		
	
	LPCTSTR GetData()
	{
		return m_pData;
	}

	
	TCHAR operator[](int nIndex) 
	{
		return GetAt(nIndex);
	}
	
	operator LPCTSTR(){return m_pData;};

	const CString& CString::operator=(const CString& stCopy)
	{	
		if (m_pData != stCopy.m_pData)
		{
			if ((m_nRef < 0 && m_pData) || m_nRef < 0)
				 CopyString(stCopy.m_pData);
			else
			{
				if(m_nRef <= 0)
				{
					delete [] (BYTE*)m_pData;
					m_pData=NULL;
					m_nSize=0;
					m_nRef=0;
				}
				ASSERT(stCopy.m_pData);
				m_pData = stCopy.m_pData;
				m_nSize = strlen(m_pData);
				m_nRef++;
			}
		}
		return *this;
	}

	const CString& operator=(TCHAR ch)
	{
		ASSERT( ch != _T( '\0' )); 
	
		CopyBeforeWrite();
		AllocMemory( 2 );
		m_pData[ 0 ] = ch;
		return *this;
	}
	
	const CString& operator=(LPCSTR lpsz)
	{
		ASSERT(lpsz == NULL);
		CopyString( lpsz);
		return *this;
	}
	
	const CString& CString::operator=(const unsigned char* lpsz)
	{ 
		*this = (LPCSTR)lpsz;
		return *this; 
	}
	
	const CString& operator+=( TCHAR ch )
	{
		ASSERT( ch != _T( '\0' )); 
		CopyBeforeWrite();
		int nLen = GetLength();
		AllocMemory( nLen + 1);
		m_pData[ nLen ] = ch;
		return *this;
	}

	const CString& operator+=(LPCTSTR lpsz)
	{

		ASSERT( lpsz ); 
		LPTSTR m_pDatat=NULL;
		int nLen= GetLength();
		int nSrc =strlen(lpsz);
		m_pDatat=(LPTSTR) new BYTE[GetLength()*sizeof(TCHAR)];
		memcpy(m_pDatat,m_pData,GetLength()*sizeof(TCHAR));
		CopyBeforeWrite();
		AllocMemory( nLen +  nSrc );
		memcpy(m_pData, m_pDatat, nLen *sizeof(TCHAR));
		memcpy(m_pData+nLen, lpsz,nSrc *sizeof(TCHAR));
		return *this;
	}
	
	const CString& CString::operator+=(CString& string)
	{
		ASSERT( lpsz ); 
		LPTSTR m_pDatat=NULL;
		int nLen= GetLength();
		int nSrc = string.GetLength();
		m_pDatat=(LPTSTR) new BYTE[GetLength()*sizeof(TCHAR)];
		memcpy(m_pDatat,m_pData,GetLength()*sizeof(TCHAR));
		CopyBeforeWrite();
		AllocMemory( nLen +  nSrc );
		m_pData=m_pDatat;
		memcpy(m_pData+GetLength(), string.m_pData, (nLen +  nSrc )*sizeof(TCHAR));
		return *this;
		
	}
	
	

	friend CString  operator+(const CString& str1,
			const CString& str2)
	{
		CString cs;
		cs.ConcatString(str1.m_pData,str2.m_pData);
		return cs;
	}
	friend CString  operator+(const CString& str1, TCHAR ch)
	{
		CString cs;
		cs.ConcatString(str1.m_pData, (LPCTSTR)ch);
		return cs;
	}
	friend CString  operator+(TCHAR ch, const CString& str)
	{
		CString cs;
		cs.ConcatString((LPCTSTR)ch,str.m_pData);
		return cs;
	}
	friend CString  operator+(const CString& str, LPCTSTR lpsz)
	{
		CString cs;
		cs.ConcatString(str.m_pData,lpsz);
		return cs;
	}
	friend CString  operator+(LPCTSTR lpsz, const CString& str)
	{
		CString cs;
		cs.ConcatString(lpsz,str.m_pData);
		return cs;
	}

	BOOL  operator==( const CString& s2)
	{
		return _tcscmp(m_pData,s2.m_pData)? 1: 0;
	}
	BOOL  operator==( LPCTSTR s2)
	{
		return _tcscmp(m_pData,s2)? 1: 0;
	}
	BOOL  operator!=(const CString& s2)
	{
		return _tcscmp(m_pData,s2.m_pData)!=0;
	}
	BOOL  operator!=( LPCTSTR s2)
	{
		return _tcscmp(m_pData,s2)!=0;
	}

	BOOL  operator<(const CString& s2)
	{
		return _tcscmp(m_pData,s2.m_pData) <0;
	}
	BOOL  operator<(LPCTSTR s2)
	{
		return _tcscmp(m_pData,s2) <0;
	}

	BOOL  operator>(const CString& s2)
	{
		return _tcscmp(m_pData,s2.m_pData)>0;
	}
	BOOL  operator>(LPCTSTR s2)
	{
		return _tcscmp(m_pData,s2) >0;
	}

	BOOL  operator<=(const CString& s2)
	{
		return _tcscmp(m_pData,s2.m_pData) <=0;
	}
	BOOL  operator<=(LPCTSTR s2)
	{
		return _tcscmp(m_pData,s2) <=0;
	}

	BOOL  operator>=(const CString& s2)
	{
		return _tcscmp(m_pData,s2.m_pData) >=0;
	}
	BOOL  operator>=(LPCTSTR s2)
	{
		return _tcscmp(m_pData,s2) >=0;
	}

	int CompareNoCase(LPCTSTR lpsz) 
	{
		return _tcsicmp(m_pData,lpsz);
	}
	
	void LoadString(HINSTANCE hInst,int idCtrl)
	{
		AllocMemory(256);
		::LoadStringA(hInst, idCtrl, m_pData, 256);	

	}
	
	CString Mid(int nFirst, int nCount) 
	{
		CString lpMid;
		if (nFirst <0) nFirst=0;
		if(nCount ==0) nCount=GetLength();
		if (nCount > (GetLength()-nFirst) ) nCount =GetLength()-nFirst;
		lpMid.AllocMemory( nCount );
		_tcsncpy( lpMid.m_pData, &m_pData[nFirst], nCount );
		return lpMid;
	}
	CString Mid(int nFirst)
	{
		return Mid(nFirst);
	}
	
	CString Left(int nCount) 
	{
		ASSERT( nCount <= GetLength());
		
		CString	cdest;
		cdest.AllocMemory( nCount );
		_tcsncpy( cdest.m_pData, m_pData, nCount );
		return cdest;
	}
	CString Right(int nCount) 
	{
		ASSERT( nCount <= GetLength());
		
		CString	cdest;
		cdest.AllocMemory( nCount );
		_tcsncpy( cdest.m_pData, &m_pData[GetLength()-nCount], nCount );
		return cdest;
	}


	void MakeUpper()
	{
		CopyBeforeWrite();
		_tcsupr(m_pData);
	}
	
	void MakeLower()
	{
		CopyBeforeWrite();
		_tcslwr(m_pData);
	}
	
	void MakeReverse()
	{
		CopyBeforeWrite();
		_tcsrev(m_pData);
	}
	
	int Collate( LPCTSTR pszStr ) 
	{
		ASSERT( m_pData!= NULL &&  pszStr != NULL);
		return _tcscoll( m_pData, pszStr );
	}
	
	int CollateNoCase( LPCTSTR pszString ) const
	{
		ASSERT( m_pData!= NULL &&  pszString != NULL);
		return _tcsicoll( m_pData, pszString );
	
	}

	void TrimRight(){};
	void TrimLeft(){};

		
	CString SpanIncluding(LPCTSTR lpszStr) 
	{
		ASSERT(lpszStr);
		return Left(_tcsspn(m_pData, lpszStr));
	}
	
	
	CString SpanExcluding(LPCTSTR lpszStr) 
	{
		ASSERT(lpszStr);
		return Left(_tcscspn(m_pData, lpszStr));
	}
	
	
	int Find(TCHAR ch) 
	{
		return Find(ch, 0);
	}
	
	int Find(TCHAR ch, int nStart)
	{
		if(nStart >= GetLength() )
			return -1;
		LPTSTR lpszSub;
		if(!( lpszSub = _tcsrchr(m_pData+nStart, (TCHAR) ch)))
			return -1;
		return (int) (lpszSub-m_pData);
		
	}
	int Find(LPCTSTR lpszStr) 
	{
		return Find(lpszStr, 0);
	}

	int Find(LPCTSTR lpszStr, int nStart)
	{
		if(nStart >= GetLength() ) return -1;
		LPTSTR lpSub;
		if(!(lpSub=_tcsstr(m_pData+nStart,lpszStr)))
			return -1;
		return (int)(lpszStr-m_pData);
	}
	

protected:
	
	void AllocMemory(int nLen)
	{
		ASSERT(nLen > 0)
		
		if ((nLen % 64) != 0 && nLen < 512)
		{
			if (nLen < 64 )  m_nSize=64;
			else
			{
				int res=(nLen % 128);
				m_nSize=nLen+(128-res);
			}
		}
		
		m_pData=(LPTSTR) new BYTE[(m_nSize+1)*sizeof(TCHAR)];
		
		m_nRef   = 1;
		m_nSize  = nLen;
		m_pData[ m_nSize ] = _T( '\0' );

	}
	
	void CopyBeforeWrite()
	{
		LPTSTR m_pDatat=NULL;
		m_pDatat=(LPTSTR) new BYTE[GetLength()*sizeof(TCHAR)];
		memcpy(m_pDatat,m_pData,GetLength()*sizeof(TCHAR));
		if(m_nRef <= 0)
			delete [] (BYTE*)m_pData;
		m_pData=m_pDatat;
	}
	
	void CopyString(LPCTSTR lpsz)
	{
		int nSize=strlen(lpsz);
		if (m_nRef > 1 || nSize > m_nSize )
		{
			if (m_nRef <= 0)
			 AllocMemory(nSize);
		}
		if (nSize <=0) return;
		memset(m_pData,0x00,nSize);
		memcpy(m_pData, lpsz, nSize*sizeof(TCHAR));
		m_nSize = nSize;
		m_pData[nSize] = '\0';
	}
	
	void ConcatString(LPCTSTR lpszSrc1, LPCTSTR lpszSrc2)
	{
	 	int nSize1=strlen(lpszSrc1);
		int nSize2=strlen(lpszSrc2);
		if (nSize1+nSize2 != 0)
		{
			AllocMemory(nSize1+nSize2);
			memcpy(m_pData, lpszSrc1, nSize1 *sizeof(TCHAR));
			memcpy(m_pData+nSize1, lpszSrc2, nSize2*sizeof(TCHAR));
		}
	}
	
};

/*
 *  CPaintDC 
 *
 **/



//#define TRANSPARENTROP 0xb8074a

void CDrawLayer::DrawShade( CRect Rect,CPoint screen,CGDI* pDC)
	{ 
	//  if(!SystemParametersInfo(SPI_GETDROPSHADOW,0,&bEnabled,0))
	  //  return;

	  // Get the size of the menu... 
  
	  long winW = Rect.Width(); 
	  long winH = Rect.Height(); 
	  long xOrg = screen.x;  
	  long yOrg = screen.y;

	  // Get the desktop hDC... 
	  HDC hDcDsk = GetWindowDC(0) ;
  
	  int X,Y;
	  // Simulate a shadow on right edge... 
	  for (X=1; X<=2 ;X++)
	  { 
		for (Y=0; Y<2 ;Y++)
		{
		  SetPixel(pDC->m_hDC,winW-X,Y, GetPixel(hDcDsk,xOrg+winW-X,yOrg+Y) );
		}
		for (Y=4; Y<8 ;Y++)
		{
		  COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
		  SetPixel(pDC->m_hDC,winW-X,Y,DarkenColor(3 * X * (Y - 3), c)) ;
		}
		for (Y=8; Y<=(winH-5) ;Y++)
		{
		  COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
		  SetPixel(pDC->m_hDC, winW - X, Y, DarkenColor(15 * X, c) );
		}
		for (Y=(winH-4); Y<=(winH-1) ;Y++)
		{
		  COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
		  SetPixel( pDC->m_hDC, winW - X, Y, DarkenColor(3 * X * -(Y - winH), c)) ;
		}
	  } 

	  // Simulate a shadow on the bottom edge... 
	  for(Y=1; Y<=2 ;Y++)
	  {
		for(X=0; X<=2 ;X++)
		{
		  SetPixel(pDC->m_hDC,X,winH-Y, GetPixel(hDcDsk,xOrg+X,yOrg+winH-Y)) ;
		}
		for(X=4; X<=7 ;X++)
		{
		  COLORREF c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y) ;
		  SetPixel(pDC->m_hDC, X, winH - Y, DarkenColor(3 * (X - 3) * Y, c)) ;
		}
		for(X=8; X<=(winW-5) ;X++)
		{
		  COLORREF  c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y); 
		  SetPixel(pDC->m_hDC, X, winH - Y, DarkenColor(15 * Y, c)) ;
		}
	  }   
	  // Release the desktop hDC... 
	  ReleaseDC(0,hDcDsk);
	}		
	
void CDrawLayer::DrawCheck(CGDI* pDC,CRect m_rcTemp)
	{
		int iMediaAltura=(m_rcTemp.Height()/2)-2;
		int iMedioBox= m_rcTemp.Width()/2;
		CPen cp;
		cp.CreatePen(PS_SOLID,1,CDrawLayer::GetRGBCaptionXP());
		CPen pOld=pDC->SelectObject(&cp);
		pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+3);
		pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-2);
		pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-2);
		pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top+2);
					
		pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+2);
		pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-3);
		pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-3);
		pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top+1);

		pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+1);
		pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-4);
		pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-4);
		pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top);
		pDC->SelectObject(&pOld);;
	
	}



#endif //C_GDI_H__191265517913802_INCLUDED_