class CFrameText;
class CFrameImage;
struct KCOldDefProp;

struct tagKPAGERECT	// ҳ��߿���Ϣ
{
	int			nStyle;				//ҳ��߿�������񣬼����ʷ��
	int			nWidth;				//�߿��������
	COLORREF	dwColor;			//�߿���ɫ
	int			nRange;				//����Ӱ�췶Χ
	int			nDistance;			//���о����
};

struct WPSTOCPARAS
{
	int		nHowToGetTOC;	// ������ʽ����������ȡĿ¼
	int		nTOCPos;		// �ںδ�����Ŀ¼: TOCPOS_FIRSTPAGE, etc.
	int		nTOCLevels;		// ��ȡĿ¼�ļ���: 1 ~ 16
	int		nTOCStyle;		// Ŀ¼��ʽ: Ŀǰ��ȡֵ��Χ�� 0 ~ 1
	BOOL	bPageSeparator;	// �Ƿ�����ҳ��
	BOOL	bPageRef;		// �Ƿ���Ŀ¼�а���ҳ��
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
	BYTE	m_tchCDID[16];	// CD�ļ�����
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
	LONG	m_nHeaderHeight; // 4��WORD, �൱��1��m_crcEvenMargin
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

	tagKPAGERECT m_PageRect;	//ҳ��߿� by shq
	LONG	m_nRectRange;		//ҳ��߿�Ӧ�÷�Χȡֵ	// PR_NULL(0x0000)	��ʾ�ޱ߿�
														// PR_ALL(0x0002)	ȫ��ҳ
														// PR_EXCEPTFIRST(0x0003) ����ҳ���������ҳ

	KSObArray_CUser m_UserArray;

	bmPresBgMusicPara m_BgMusic;

	KSObArray_AnchoredObjs m_newAryAnchoredObjs;
	KSObList_MasterObjs m_lstMasterObjs;
};

struct KABGROUPINFO
{
	int nType;			// ���Զ���Ż�����Ŀ����
	int	nStyle;			// ����ľ�����(����1)
	int	nLevel;			// ����Ĳ��(����0)
	int	nStartNumber;	// �����Զ���ŵ���ʼ��ţ�����Ŀ��������Ч	
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
