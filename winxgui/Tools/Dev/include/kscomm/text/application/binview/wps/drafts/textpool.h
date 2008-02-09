class CFrameText;
class CFrameImage;
struct KCOldDefProp;

struct tagKPAGERECT	// 页面边框信息
{
	int			nStyle;				//页面边框线条风格，即画笔风格
	int			nWidth;				//边框线条宽度
	COLORREF	dwColor;			//边框颜色
	int			nRange;				//设置影响范围
	int			nDistance;			//距版芯距离
};

struct WPSTOCPARAS
{
	int		nHowToGetTOC;	// 根据样式还是属性提取目录
	int		nTOCPos;		// 在何处插入目录: TOCPOS_FIRSTPAGE, etc.
	int		nTOCLevels;		// 提取目录的级数: 1 ~ 16
	int		nTOCStyle;		// 目录样式: 目前的取值范围是 0 ~ 1
	BOOL	bPageSeparator;	// 是否插入分页符
	BOOL	bPageRef;		// 是否在目录中包含页号
};

struct CountRef
{
	WORD	wCount;
	if (wCount == 0xFFFF)
		DWORD dwCount;
	else
		dwCount = wCount;
	endif
};

class CObList
{
	CountRef cnt;
	CObject	m_pOb[cnt.dwCount];
};

class KSObArray_CUser
{
	CObArray	m_pThis;
};

class KSObArray_AnchoredObjs
{
	CObArray	m_pThis;
};

class KSObList_MasterObjs
{
	CObList	m_pThis;
};

class bmPresBgMusicPara
{
	DWORD	dw[2];			// reserved
	BYTE	m_tchCDID[16];	// CD的鉴定码
	LONG	m_nBeginTrack;
	LONG	m_nEndTrack;
	LONG	m_nBeginMinute;
	LONG	m_nBeginSecond;
	LONG	m_nEndMinute;
	LONG	m_nEndSecond;
	DWORD	m_bCDLoop;
	DWORD	m_cchMidiName;
	BYTE	m_tchMidiName[m_cchMidiName];
	DWORD	m_bMidiLoop;
	DWORD	m_cchWavName;
	BYTE	m_tchWavName[m_cchWavName];
	DWORD	m_bWavLoop;
};

class CWpsDoc
{
	BYTE	szDocID[9];		// = [DocInfo]
	LONG	m_nHeaderToTop;
	LONG	m_nFooterToBottom;
	DWORD	m_bMultiHeader;
	DWORD	m_bMultiFooter;
	DWORD	m_bNoHeaderAtStart;
	DWORD	m_bNoFooterAtStart;
	DWORD	m_bSymmetric;
	DWORD	m_bStartFromLeft;
	DWORD	m_nPaperOrient;
	DWORD	m_nPaperType;
	DWORD	m_bScriptSheet;
	DWORD	m_nScriptSheetType;
	SIZE	m_cszPageSize;
	RECT	m_crcOddMargin;
	LONG	reserved;
	LONG	m_nHeaderHeight; // 4个WORD, 相当于1个m_crcEvenMargin
	LONG	m_nFooterHeight;
	LONG	m_nPageNumOrg;

	LONG	m_nCurrentPage;

	CFrameText c_pHeaderOdd;
	CFrameText c_pFooterOdd;
	CFrameText c_pHeaderEven;
	CFrameText c_pFooterEven;
	
	CFrameImage m_pBkGndImg;

	WPSTOCPARAS	m_TOCParas;

	COLORREF	m_clrScriptSheet;
	BYTE		byBufReserved[60];

	KCOldDefProp m_oldDefProp;

	DWORD	m_bReadOnly;		//amend:wdb
	CString	m_sDomainPassword;
	DWORD	m_bBackGround;

	tagKPAGERECT m_PageRect;	//页面边框 by shq
	LONG	m_nRectRange;		//页面边框应用范围取值	// PR_NULL(0x0000)	表示无边框
														// PR_ALL(0x0002)	全部页
														// PR_EXCEPTFIRST(0x0003) 除首页以外的所有页

	KSObArray_CUser m_UserArray;

	bmPresBgMusicPara m_BgMusic;

	KSObArray_AnchoredObjs m_newAryAnchoredObjs;
	KSObList_MasterObjs m_lstMasterObjs;
};

struct KABGROUPINFO
{
	int nType;			// 是自动编号还是项目符号
	int	nStyle;			// 本组的具体风格(基于1)
	int	nLevel;			// 本组的层次(基于0)
	int	nStartNumber;	// 本组自动编号的起始编号，如项目符号则无效	
};

class KABGroupInfoMan
{
	DWORD	nSize;
	KABGROUPINFO elem[nSize];
};

class CTextPool	// WPS97, WPS2000, WPS2001
{
	DWORD	m_TextLineMode;
	DWORD	m_nColumns;
	DWORD	m_nColumnGap;
	DWORD	m_nColLineWidth;
	DWORD	m_nColLineStyle;
	DWORD	m_clrColLine;
	DWORD	nSize;
	CParagraph	m_ParagraphArray[nSize];
	CParaAttr	m_ParaAttr[nSize];
	KABGroupInfoMan	m_pKABGroupInfoMan;
};

class CParagraph	// WPS2000, WPS2001
{
	int			m_paraEndCode;
	LONG		m_lSerialID;
	WORD		nSenCount;
	WORD		m_wRevFlag;
	int			m_nFN_ID;

	if (m_wRevFlag != 0)
		int		m_nRevCount;
		REVISE_DATA	m_ReviseData[m_nRevCount];
	endif

	CSentence	m_SentenceArray[nSenCount];
};

class CParaAttr		// WPS2000, WPS2001
{
	DWORD		m_dwStyleID;
	CString		m_strStyleName;
	CObList		m_pAttribList;
	CSentAttr	m_SentAttr[nSenCount];
};

class CSentence		// WPS2001
{
	KSTextString m_tsBuf;
};

class CSentAttr
{
	DWORD		m_dwStyleID;
	CString		m_strStyleName;
	CObList		m_pAttribList;
};
