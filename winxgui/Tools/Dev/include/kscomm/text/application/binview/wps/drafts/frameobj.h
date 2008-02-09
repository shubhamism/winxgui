#include "wpsobj.h"

/*
CTFPBase
    CFPBase
        CFrameObj
            CFrameImage
            CFrameOLE
            CFramePT
                CFrameChart
            CFrameText
                CWPPFrame
        CMciDevice
            CCdAudio
            CMidiWav
        CPTObj
            CBarCodeObj
            CCurveObj
            CLineObj
            CLtxtObj
                KSDomainCalendar
                KSDomainComboBox
                KSDomainMailButton
                KSDomainText
            CObjOxy
            CPolyObj
                CPolyLine
            CRectObj
                CCake
                CCakeBox
                CChartAxes
                CCropRect
                CHistogram
                KSDomainCheckBox
                KSDomainOption
            CRectPoly
                CCropRectPoly
        CTextObj
            CRotateText
                KSDomainMLText
        CWPSWndCtrl
            CWPSVideo
*/

enum BkMode
{
	// (反白，复盖，透明, 渐变色)
	INVERT=0, TRANSPARENT, OPAQUE, GRADIENT = 10
};

// {{ ColorDirection 填充路径
#define GRAD_HORIZ		0	//水平渐变
#define GRAD_VERT		1	//垂直渐变
#define GRAD_LEANUP		2	//倾斜向上(从左上偏向右下)
#define GRAD_LEANDOWN	3	//倾斜向下(从左下偏向右上)
#define GRAD_CORNER		4	//从角度渐变
#define GRAD_CENTER		5	//从中心渐变

// {{ ColorDistortion 四个方向变形
#define GRAD_LEFTTOP			0
#define GRAD_LEFTBOTTOM			1
#define GRAD_RIGHTTOP			2
#define GRAD_RIGHTBOTTOM		3

class CTFPBase
{
	CWPSObj			base;
	int				m_nBkMode;		// 背景填充方式(反白，复盖，透明, 渐变色) BkMode
	KCOLORINDEX		m_bkColor;
	LOGBRUSH		m_logbrush;
	int				m_nColorDirection;	//	用于渐变色方向	ColorDirection
	int				m_nColorDistortion;	//	渐变色扭曲	ColorDistortion
};

//	排版位置属性: Composing Location
enum ComposingLocation
{
	CL_Current, CL_FollowPara, CL_FollowText,
	CL_EachPage, CL_OddPage,    CL_EvenPage
};

//	对象显示风格: DispStyle 
enum {	DS_ONTEXT =0, DS_UNDERTEXT, DS_DONTCARE	};

//	阴影风格(纯色、雾色)
enum ShadowStyle
{
	SW_PURE = 0, SW_FOG
};

class CFPBase
{
	CTFPBase		base;
	int				m_nCompLoca;	// 排版位置属性 ComposingLocation
	int				m_nDispStyle;	// 对象显示风格: DispStyle 
	BOOL			m_bNoPrint;
	UINT			m_uLPenStyle;
	UINT			m_uLPenSize;
	COLORREF		m_LPenColor;
	CPoint			m_shadowPnt;
	KCOLORINDEX		m_shadowColor;
	int				m_shadowStyle;	// ShadowStyle
	BOOL			m_bLock;
	DWORD			m_dwObjID;
	int				nNum;
	DWORD			m_SlvObjIDArray[nNum];
	CPoint			m_ObjConnPnt;
};

enum FrmShape	// 框形状(直、圆角，上下、左右边), 用于多对象框形状不同时设之
{
	FS_NULL = -1,
	FS_ROUNDRECT = 0x00,
	FS_L = 0x01,
	FS_T = 0x02,
	FS_R = 0x04,
	FS_B = 0x08,
	FS_RECT = 0x0F,
	FS_TB   = 0x0A,
	FS_LR   = 0x05
};

enum MrgSideType //	框边内外留空类型
{
	None =0, All, LeftRight, TopBottom, 
	Left, Right, Top, Bottom
};

class CFrameObj
{
	CFPBase			base;	
	int				m_nfrmShape;	// FrmShape
	CPoint			m_roundness;
	int				m_wrapMode;
	int				m_mgOutsideType;
	CRect			m_MarginOutside; // MrgSideType
	CSize			m_extent;
	CWpsImage*		m_pImg;
};

class CFrameImage
{
	CFrameObj		base;
	CSize			m_extent;
	BOOL			m_bTiled;																 
	CRect			m_regRect;
	CWpsImage*		m_pImg;
	ObjType			objtype;
};

class CFrameOLE
{
	CFrameObj		base;
	CSize			m_extent;
	CWpsOleItem*	m_pClientItem;
	ObjType			objType;
};

class CFramePT
{
	CFrameObj		base;
	CObList			m_ptobjList;
	ObjType			objType;
};

class CFrameChart
{
	CFramePT		base;
	int				m_bNeedSample;
	int				m_bNeedSource;
	CRect			m_AxesObj;
	int				m_nChartType;
	double			m_fMinY;
	double			m_fMaxY;
	double			m_fStep;
	UINT			m_uMaxX;
	UINT			m_uGroup;
	int				readcount;
	struct
	{
		int			x;
		int			y;
	}				m_ReadOnlyList[readcount];
	struct
	{
		double		dcount;
		double		pList[dcount];
	}				m_DataList[m_uGroup];
};

class CFrameText
{
	CFrameObj		base;
	int				m_mgInsideType;
	CRect			m_MarginInside;
	BOOL			m_bScriptSheet;
	struct			FRAMETEXTNODE
	{
		WORD		wPageNum;
		WORD		wFrameID;
	};
	FRAMETEXTNODE	s_PrevFrame;
	FRAMETEXTNODE	s_NextFrame;
	FRAMETEXTNODE	s_ThisFrame;
	CTextPool		c_pTextPool;
	ObjType			objType;
};

class CWPPFrame
{
	BOOL			m_bIsTitleFrame;
	CFrameText		base;
};

class CMciDevice
{
	CFPBase			base;
	DWORD			dw1;		// 8字节缓冲
	DWORD			dw2;
};

class CCdAudio
{
	CMciDevice		base;
	DWORD			dw1;						// 8字节缓冲
	DWORD			dw2;
	WORD			wSize;
	struct			bmPresBgMusicPara
	{
		DWORD		lpVtbl;						//该类有虚函数
		TCHAR		m_tchCDID[16];				//CD的鉴定码.
		int			m_nBeginTrack;				//开始磁道.
		int			m_nEndTrack;				//结束磁道.
		int			m_nBeginMinute;				//开始分钟.
		int			m_nBeginSecond;				//开始秒数.
		int			m_nEndMinute;				//结束分钟.
		int			m_nEndSecond;				//结束秒数.
		BOOL		m_bCDLoop;					//是否循环播放CD.
		TCHAR		m_tchMidiName[MAX_PATH];	//MIDI文件名.
		BOOL		m_bMidiLoop;				//是否循环播放MIDI.
		TCHAR		m_tchWavName[MAX_PATH];		//WAV文件名.
		BOOL		m_bWavLoop;					//是否循环播放WAV.
	}				m_MciPara;
	ObjType			objType;
};

class CMidiWav
{
	CMciDevice		base;
	DWORD			dw1;		// 8字节缓冲
	DWORD			dw2;
	WORD			wSize;
	struct tagPresMciPara
	{	
		TCHAR		strCDID[16];			//CD的鉴定码.
		int			nBeginTrack;			//开始磁道.
		int			nEndTrack;				//结束磁道.
		int			nBeginMinute;			//开始分钟.
		int			nBeginSecond;			//开始秒数.
		int			nEndMinute;				//结束分钟.
		int			nEndSecond;				//结束秒数.
		BOOL		bCDLoop;				//是否循环播放CD.
		TCHAR		strMidiName[MAX_PATH];	//MIDI文件名.
		BOOL		bMidiLoop;				//是否循环播放MIDI.
		TCHAR		strWavName[MAX_PATH];	//wav文件名.
		BOOL		bWavLoop;				//是否循环播放wav.
		TCHAR		strMP3Name[MAX_PATH];	//MP3文件名.
		BOOL		bMP3Loop;				//是否循环播放MP3.
	}				m_MciPara;
	ObjType			objType;
};

enum EndShape	//	端点类型
{
	es_null = -1, es_none,
	sa_1, sa_2, sa_3, na_1, na_2, na_3, 
	sc_1, sc_2, sc_3, nc_1, nc_2, nc_3,
	sr_1, sr_2, sr_3, nr_1, nr_2, nr_3, ib_1, ib_2, ib_3
};

enum EndStyle { ES_Open, ES_Close, ES_none };//	端点风格

class CPTObj
{
	CFPBase			base;
	CPoint			m_center;
	int				m_theta;
	int				m_nEndStyle;	// EndStyle
	int				m_nEndShape[2];	// EndShape
};

class CBarCodeObj
{
	CPTObj			base;
	int				m_nBCSTD;
	CString			m_strBCID;
	int				m_nBCFontH;
	ObjType			objType;
};

class CCurveObj
{
	CPTObj			base;
	CPoint			m_curvepnt[4];
	ObjType			objType;
};

class CLineObj
{
	CPTObj			base;
	CPoint			m_linepnt[2];
	int				m_nlineobjShape;
	if m_nlineobjShape == linkLine || m_nlineobjShape == linkBezier
		int			m_bVert;
		CPoint		m_handle3;
	endif
	ObjType			objType;
};

enum LTxtObjShape
{
	rectangle, roundRect, ellipse, diam, para, trap, trapI, 
	ellipseComment, roundRectComment, rectComment, sizeComment,	 //xu 7.28
	oblique, chartSoureData = 1000, chartSampleTxt, chartTitle
};//表元斜线文字行

class CLtxtObj
{
	CPTObj			base;
*	int				m_nltxtobjShape;	// LTxtObjShape
	if m_nltxtobjShape == ellipseComment || m_nltxtobjShape == para	|| m_nltxtobjShape == trap || m_nltxtobjShape == rectComment
*		CPoint		m_activePnt;		//标注对象用到的可拖动点
	endif
	if m_nltxtobjShape == roundRect
*		CPoint		m_roundnessPnt;
	endif
	if m_nltxtobjShape == roundRectComment
*		CPoint		m_activePnt;
*		CPoint		m_roundnessPnt;
	endif
*	KSTextString	m_string;
	COLORREF		m_stringColor;
	int				m_nAspectX;
	int				m_nCharMrg;		//	字间距
	WORD			m_nAlig;
	LOGFONT			m_lfChn;
	LOGFONT			m_lfEng;
	char			m_szFSname[uFontNameSize];	// uFontNameSize从常量获取
	int				m_nFSsize;
	WORD			m_wFSunit;
*	int				m_nFlipMode;
	CHARFXHSS		m_ccHSS;
	ObjType			objType;
};

class KSDomainCalendar
{
	CLtxtObj		base
	BOOL			m_bSelect;
	CString			m_sSelectDate;
	int				m_nStyleIndex;
	int				m_nTimeIndex;
	BOOL			m_bBackGround;
	ObjType			objType;
};

class KSDomainComboBox
{
	CLtxtObj		base;
	BOOL			m_bSelect;
	BOOL			m_bBackGround;
	int				nCount;
	CString			m_strArray[nCount];
	ObjType			objType;
};

class KSDomainMailButton
{
	CLtxtObj		base;
	BOOL			m_bSelect;
	CString			m_sSubject;
	CString			m_sSendTo;
	CString			m_sSendCc;
 	ObjType			objType;
};

class KSDomainText
{
	CLtxtObj		base;
	CString			m_sTitle;
	BOOL			m_bBackGround;
 	ObjType			objType;
};

class CObjOxy		// 没有实现自己的Serialize
{
	CPTObj			base;
};

class CPolyObj
{
	CPTObj			base;
	int				m_nPolyobjShape;
	int				nNum;
	CPoint			m_pointList[nNum];
 	ObjType			objType;
};

class CPolyLine
{
	CPolyObj		base;
	int				m_nPolyShap;
	int				m_nHandleStyle;
	int				m_bDraw;
	USHORT			m_uWidth; 
	UINT			m_uDataNum;
	UINT			m_uCurGroup;
	BOOL			m_bDisplyedSource;
	double			m_pData[m_uDataNum] ;	
};

class CRectObj
{
	CPTObj			base;
	int				m_nrectobjShape;
	int				m_nellipseArcType;
	CPoint			m_roundness;
	if m_nrectobjShape == cube
		int			m_nScale;
		int			m_nCubeView; 
	endif
	if m_nrectobjShape == cylinder || m_nrectobjShape == pieColumn
		int			m_nScale;
	endif
 	ObjType			objType;
};

class CCake
{
	CRectObj		base;
	UINT			m_uCurGroup;
	int				m_bDraw;
	int				m_bDisplyedSource;
	int				m_nCakeShap;
	double			m_dDataTotal;
	double			m_dData;
	struct			CakeDataST
	{
		UINT		uIndex;	//当前数据的索引值,based on 1
		int			percent;	//百分比
		int			alphaS;		//起始角
		int			alphaE;		//终止角
	}				m_CakeDataST;
};

class CCakeBox
{
	CRectObj		base;
	UINT			m_uCurGroup;
};

class CChartAxes
{
	CRectObj		base;
	CString			m_strXFontName;	
	CString			m_strYFontName;	
	long			m_lXStrFontH;	
	long			m_lYStrFontH; 
	long			m_lXStrFontEscapement;
	long			m_lYStrFontEscapement;
	CRect			m_AxesRect;	
	int				m_nAxesType;	
	CSize			m_strSize;			  
	long			m_lOrg;	
	DWORD			m_wflag;	
	int				m_nScalePos;
	KCOLORINDEX		m_XstrClr;
	KCOLORINDEX		m_YstrClr;
	int				m_nFSsize;				//  字符尺寸
	WORD			m_wFSunit;              //  使用何单位表示尺寸(pound, 号, etc.)
	char			m_XszFSname[uFontNameSize];
	char			m_YszFSname[uFontNameSize];
	KSTextStringList m_YScaleList;	//	y轴刻度字符串链表
	KSTextStringList m_XScaleList;	//	x轴刻度字符串链表
};

class CCropRect		// 没有实现自己的Serialize
{
	CRectObj		base;
};

class CHistogram
{
	CRectObj		base;
	int				m_nHistogramShap;
	int				m_bDraw;
	UINT			m_uGroup;
	UINT			m_uDataNum;
	UINT			m_uCurGroup;
	int				m_bDisplyedSource;
	CRect			m_MapRect;
	double			m_pData[m_uDataNum];
	UINT			uCount;
	CRect			m_RectList[uCount];
};

class KSDomainCheckBox
{
	CRectObj		base;
	BOOL			m_bSelect;
	BOOL			m_bDrawFlag;
	BOOL			m_bBackGround;
 	ObjType			objType;
};

class KSDomainOption
{
	CRectObj		base;
	BOOL			m_bSelect;
	BOOL			m_bDrawFlag;
	BOOL			m_bGroup;
	BOOL			m_bBackGround;
 	ObjType			objType;
};

class CRectPoly
{
	CPTObj			base;
	UINT			m_nNum;
	UINT			m_nScale;		
 	UINT			m_bLinkTop;
	UINT			m_bLinkMid;
 	ObjType			objType;
};

class CCropRectPoly	// 没有实现自己的Serialize
{
	CRectPoly		base;
};

class CTextObj
{
	CFPBase			base;
	KSTextString	m_string;
	CObList*		m_pAttribList;
	CPoint			m_center;
	int				m_theta;
};

class CRotateText
{
	CTextObj		base;
	int				m_nTempTheta;
	int				m_nMultitxtShape;
	if m_nMultitxtShape == trap || m_nMultitxtShape == trapi || m_nMultitxtShape == para || m_nMultitxtShape == ellipsecomment || m_nMultitxtShape == rectcomment || m_nMultitxtShape == cross || m_nMultitxtShape == arrow
		CPoint		m_activePnt;	//标注对象用到的可拖动点
	endif
	if m_nMultitxtShape == roundrect
		CPoint		m_roundnessPnt;
	endif
	if m_nMultitxtShape == roundrectcomment
		CPoint		m_activePnt;
		CPoint		m_roundnessPnt;
	endif
	int				m_nFlipMode;
	if m_nMultitxtShape == trap || m_nMultitxtShape == trapi || m_nMultitxtShape == para || m_nMultitxtShape == arrow
		int			m_nDirection;
	endif
 	ObjType			objType;
};

class KSDomainMLText
{
	CRotateText		base;
	CString			m_sTitle;
	BOOL			m_bBackGround;
 	ObjType			objType;
};

class CWPSWndCtrl
{
	CFPBase			base;
	DWORD			dw1, dw2;	// 8字节缓冲
};

class CWPSVideo
{
	CWPSWndCtrl		base;
	BOOL			m_bNonStop;
	UINT			m_uScale;
	DWORD			dw1, dw2;	// 8字节缓冲
	WORD			wSize;
	TCHAR			m_szFile[wSize];
 	ObjType			objType;
};