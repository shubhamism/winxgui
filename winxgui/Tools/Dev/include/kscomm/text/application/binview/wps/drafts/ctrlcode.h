#if 0
	typedef WORD	CTRLCODEID;
#	define	MAX_TABSTOPS	20		// һ��֮�����Tab-Stop��Ŀ
#endif

struct UNIT_VALUE
{
	WORD			wUnit;		// ��λ
	int				nValue;		// ֵ���京���� wUnit ����
};

class CCtrlCode
{
	CTRLCODEID		m_wID;
};

class CCtrlCode_Alignment
{
	CCtrlCode		base;
	WORD			m_wAlignment;
};

class CCtrlCode_AspectX
{
	CCtrlCode		base;
	WORD			m_wAspectX;
};

class CCtrlCode_AutoNumber
{
	CCtrlCode		base;
	int				m_nGroupID;
};

class CCtrlCode_BGVein
{
	CCtrlCode		base;
	KCOLORINDEX		m_dwColor;
	int				m_nBrushStyle;
};

class CCtrlCode_Bold
{
	CCtrlCode		base;
	LONG			m_lWeight;
};

class CCtrlCode_CharSet
{
	CCtrlCode		base;
	DWORD			m_dwCharSet;
};

class CCtrlCode_Color
{
	CCtrlCode		base;
	KCOLORINDEX		m_CharColor;
};

class CCtrlCode_DISPLAY
{
	CCtrlCode		base;
	BOOL			m_bDisp;
};

class CCtrlCode_Font
{
	CCtrlCode		base;
	WORD			wLen;
	char			m_szFaceName[wLen];
};

class CCtrlCode_HotRef
{
	CCtrlCode		base;
	WORD			m_wHyperID;
	WORD			wLen;
	char			m_szData[wLen];
	WORD			wLen2;
	char			m_szAnchor[wLen2];
};

class CCtrlCode_HSS
{
	CCtrlCode		base;
	struct			CHARFXHSS
	{
		int			hssFlag;		// ָ����Ϊ����, �������Ӱ��
		int			hssDepth;		// ����/����/��Ӱ�ĳ̶�
		int			hssDegree;		// ����/��Ӱ�ĽǶ�
		KCOLORINDEX	hssFromColor;	// ��ʼ��ɫ
		KCOLORINDEX	hssToColor;		// ��ֹ��ɫ
		int			hssPara;		// ��������
	}				m_Data;
};

class CCtrlCode_Italic
{
	CCtrlCode		base;
	LONG			m_lDegree;
};

class CCtrlCode_Label
{
	CCtrlCode		base;
	int				m_nID;
	WORD			wLength;
	if wLength > 0
		char		pszString[wLength];
		BOOL		bIsBlock;
	endif
};

class CCtrlCode_LineMargin
{
	CCtrlCode		base;
	UNIT_VALUE		m_LineMargin;
};

class CCtrlCode_ObliqueLine
{
	CCtrlCode		base;
	int				m_nObliqueLine;
};

class CCtrlCode_OutRect
{
	CCtrlCode		base;
	KCOLORINDEX		m_dwColor;
	int				m_nPenStyle;
	int				m_nWidth;
};

class CCtrlCode_ParaFrame
{
	CCtrlCode		base;
	struct			PARAFRAME
	{
		DWORD		dwFlag;
		KCOLORINDEX	dwColorLeft;
		int			nPenStyleLeft;
		int			nWidthLeft;
		LONG		lDistanceL;
		KCOLORINDEX	dwColorTop;
		int			nPenStyleTop;
		int			nWidthTop;
		LONG		lDistanceT;
		KCOLORINDEX	dwColorRight;
		int			nPenStyleRight;
		int			nWidthRight;
		LONG		lDistanceR;
		KCOLORINDEX	dwColorBottom;
		int			nPenStyleBottom;
		int			nWidthBottom;
		LONG		lDistanceB;
	}				m_ParaFrame;
};

class CCtrlCode_ParaIndent
{
	CCtrlCode		base;
	UNIT_VALUE		m_Indent;
};

class CCtrlCode_ParaMargin
{
	CCtrlCode		base;
	UNIT_VALUE		m_ParaMargin;
};

class CCtrlCode_Revise
{
	CCtrlCode		base;
	int				m_nCount;
	struct			REVISE_DATA
	{
		WORD		wReviseType;		// �޶�����
		WORD		wUserID;			// �û�ID
		SYSTEMTIME	sReviseTime;		// �޶�ʱ��
	}				m_pDataBuf[m_nCount];	
};

class CCtrlCode_Size
{
	CCtrlCode		base;
	LONG			m_lCharSize;
	WORD			m_Unit;
};

class CCtrlCode_SSScript
{
	CCtrlCode		base;
	WORD			m_wFlag;
	DWORD			nHeight;
	DWORD			nShift;
};

class CCtrlCode_StrikeOut
{
	CCtrlCode		base;
	WORD			m_wFlag;
};

class CCtrlCode_Tabs
{
	CCtrlCode		base;
	struct			TABITEM
	{
		__int16		nTabPosition;	// �����ֿ��߼������¼��Tabλ��
		WORD		wFrontChar;		// ǰ���ַ�
	}				m_Tabs[MAX_TABSTOPS + 1];
};

class CCtrlCode_Tracking
{
	CCtrlCode		base;
	struct
	{
		WORD		wUnit;
		DWORD		nValue;
	}				m_Track;
};

class CCtrlCode_UnderLine
{
	CCtrlCode		base;
	WORD			m_wStyle;
	KCOLORINDEX		m_clrLineColor;
};

class CCtrlCode_Visible
{
	CCtrlCode		base;
	BOOL			m_bVisible;
};