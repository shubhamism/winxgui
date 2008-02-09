/* -----------------------------------------------------------------------*\
 * ���ڶ������ļ���ʽ����Script��Rule���ɹ�������

  1). �û��������� - �ṹ��(struct)����(class)
		Rule = struct { ... };
		Rule = class  { ... };
		Rule = struct(BaseRule) { ... };
		Rule = class(BaseRule) { ... };

  2). �������� - DWORD��WORD��BYTE��LONG��SHORT��CHAR��etc

  3). ��λ��� - org
		org(offset);		// ����Ϊ: seek(offset, SEEK_SET);
		org(+offset);		// ����Ϊ: seek(offset, SEEK_CUR);
		org(-offset);		// ����Ϊ: seek(-offset, SEEK_CUR);
	  ���offset���������⸴�ӵ�C���Ա��ʽ��

  4). ������� - if
		if (cond) { ... }
	  ���cond�������������C���Թ��������ж�

  5). ��Ա���ʣ������Ժ����ɵĳ����ڸ��ֵط���eg.
		org(wpsHeader.wfhTemplateInfo);
		BYTE data[hdr.cbData];
		if (hdr.cbData)	{...}

  6). ֵԼ��
		DWORD dwData = 0x10101010;
		BYTE tag[] = "Hello\0";
 *
\* -----------------------------------------------------------------------*/

FILETIME = struct
{
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
};

WPSFILEHEADER = struct
{
	WORD	wfhVersion;
	BYTE	wfhCopyright[42];
	WORD	wfhHeaderSize;
	DWORD	wfhTemplateInfo;		// Template Info offset
	DWORD	wfhDocInfo;				// Document Data offset
	DWORD	wfhMainText;
	DWORD	wfhFramePT;				// WPS Pages offset
	SHORT	wfhNumOfPage;
	DWORD	wfhAutoSaveInfo;		// AutoSave Info offset
	WORD	wfhHeaderVersion;
	DWORD	wfhSumInfo;				// Summary Info offset
	WORD	wfhSumSize;				// Summary Info size
	DWORD	wfhLocale;
	DWORD	wfhEncrypt;
	DWORD	wfhStyleSheet;			// style sheet offset
	DWORD	wfhSerialNum;			// serial number offset
	DWORD	wfhBookMarkInfo;		// BookMark offset
	DWORD	wfhBookMarkSize;		// BookMark size
	DWORD	wfhGWInfo;
	WORD	wfhGWInfoSize;
	WORD	wfhCompress;			// ����ѹ����־
	FILETIME wfFileTime;
	DWORD	wfhSystemCodePage;		// ���ɵ�ϵͳ����
	DWORD	wfhOLEBlock;			// OLE Data offset
	DWORD	wfhOLEBlockSize;		// OLE Data size
	DWORD	wMultiLanguageID;		// ���Ӷ����԰汾��ʶ[shq	July 23,2001]
	DWORD	wReserve[17];			// Reserve 17 * DWORD - ole block
};

doc = struct // WPS 2002 ��ǰ�汾���ļ���ʽ
{
	WPSFILEHEADER	wpsHeader;
	
	if (wpsHeader.wfhTemplateInfo)
	{
		org(wpsHeader.wfhTemplateInfo);		// Template info, template-file only
		BYTE	tagTempateInfo[] = "[TemplateInfo]";
		WORD	nSizeSum;					// nSizeName + nSizeCom + 3*sizeof(WORD)
		WORD	nTplType;
		WORD	nSizeName;
		BYTE	lpszTplName[nSizeName];		// WPTName
		WORD	nSizeCom;
		BYTE	lpszTplComment[nSizeCom];	// WPTDesc
	}
	
	if (wpsHeader.wfhAutoSaveInfo)
	{
		org(wpsHeader.wfhAutoSaveInfo);		// Auto-Save info, afsfile only
		BYTE	tagAutoSaveInfo[] = "[AutoSaveInfo]";
		DWORD	nSizeSum;
		DWORD	nSizeFileName;
		BYTE	csStrFile[nSizeFileName];
		DWORD	nSizeTitle;
		BYTE	csStrTitle[nSizeTitle];
	}
	
	if (wpsHeader.wfhStyleSheet)
	{
		org(wpsHeader.wfhStyleSheet);		// style sheet
		BYTE	tagStyleSheet[] = "[StyleSheet]";
		CStyleSheet_Text m_StySht_Text;
	}
	
	if (wpsHeader.wfhSerialNum)
	{
		org(wpsHeader.wfhSerialNum);		// serial number
		BYTE	tagSerialNum[] = "[SerialNum]\0";
		WORD	cbNum;
		BYTE	szNum[cbNum];
	}
	
	if (wpsHeader.wfhDocInfo)				// Document Data
	{
		org(wpsHeader.wfhDocInfo);
		CWpsDoc	docInfo;
	}
	
	if (wpsHeader.wfhMainText)
	{
		org(wpsHeader.wfhMainText);			// Main text
		BYTE		tagMainText[] = "[WPSText]";
		CTextPool	c_pTextPool;
		CTextPool	c_pFootnoteTextPool;
		CFootnoteMan m_FootnoteMan;
		LONG		nPara;	// selection �����
		LONG		nSen;	// selection �����
		DWORD		wChar;	// selection ����ƫ��
	}
	
	if (wpsHeader.wfhFramePT)
	{
		org(wpsHeader.wfhFramePT);			// WPS Pages
		PAGEINFOHEADER	PIH;
		CWPSPage		m_WPSPages[PIH.piNumOfPage];
	}
	
	if (wpsHeader.wfhSumInfo)
	{
		org(wpsHeader.wfhSumInfo);			// Summary info
		BYTE	tagSummaryInfo[] = "[Summary]\0";
		BYTE	SummaryInfo[wpsHeader.wfhSumSize];
	}
	
	if (wpsHeader.wfhBookMarkInfo)
	{
		org(wpsHeader.wfhBookMarkInfo);		// Book Mark
		BYTE	tagBookMark[] = "[BookMark]\0";
		BYTE	BookMark[wpsHeader.wfhBookMarkSize];
	}
	
	if (wpsHeader.wfhOLEBlock)
	{
		org(wpsHeader.wfhOLEBlock);
		// Comment					{{ --> OLE Data
		// Extend Document Data		{{ --> OLE Data
		// TOC						{{ --> OLE Data
		// OLE Data
		DWORD		tagOLEData = 0x10101010;
		DWORD		nSize;
		COLEData	m_OleDataArray[nSize];
	}
};

PAGEINFOHEADER = struct
{
	BYTE	piID[16];					// ID�ַ���, Ϊ"[PageInfo]"
	WORD	piHeaderSize;				// ���ṹ�Ĵ�С
	WORD	piNumOfPage;				// ���ļ����ֶ���ҳ
	DWORD	piPageOffset[piNumOfPage];	// ÿҳ�������ļ��е���ʼλ��
};

KPAGERECT = struct					// ҳ��߿���Ϣ
{
	int			nStyle;				//ҳ��߿�������񣬼����ʷ��
	int			nWidth;				//�߿��������
	COLORREF	dwColor;			//�߿���ɫ
	int			nRange;				//����Ӱ�췶Χ
	int			nDistance;			//���о����
};

CStyleSheet_Text = class
{
	//CObArray<CStyle_Text*> m_aryStyle;
};

CStyle_Text = class(CStyleBase)
{
	/* to do:
	DWORD		m_dwStyle;
	DWORD		m_dwBaseStyle;
	CString		m_strBaseStyleName;
	DWORD		dwReserved[4];
	CObList<>	m_PAList;
	CObList<>	m_CAList;
	DWORD		m_dwPreStyle;
	CString		m_strPreStyleName;
	DWORD		m_dwFollowStyle;
	CString		m_strFollowStyleName; */
};

CStyleBase = class
{
	//CString	m_strName;
};

CFootnoteMan = class
{
	BYTE	tagFootnote[] = "[Footnote]\0";
	DWORD	dwLength;
	BYTE	pBuffer[dwLength];
	// COLEData: FNPrefix, FNSuffix, ENPrefix, ENSuffix
};

CWPSPage = class
{
	BYTE	tagWPSPage[] = "[WPSPage]";
	WORD	m_wPageNumber;
	KPAGERECT m_PageRect;
	DWORD	m_bHasPageRect;
	//CWPSObj base;
	//CObList<CWPSObj*> m_WPSObjectList;
};

COLEData = class
{
	DWORD	dwflag;
	DWORD	nStrLen;
	BYTE	m_strName[nStrLen];
	DWORD	m_nBufSize;
	BYTE	m_pData[m_nBufSize];
};

CWpsDoc = class
{
	// to do:
};

// -------------------------------------------------------------------------

CTextPool = class // WPS97, WPS2000, WPS2001
{
	/* to do:
	DWORD	m_TextLineMode;
	DWORD	m_nColumns;
	DWORD	m_nColumnGap;
	DWORD	m_nColLineWidth;
	DWORD	m_nColLineStyle;
	DWORD	m_clrColLine;
	DWORD	nSize;
	CParagraph	m_ParagraphArray[nSize];
	CParaAttr	m_ParaAttr[nSize];
	KABGroupInfoMan	m_pKABGroupInfoMan; */
};

// -------------------------------------------------------------------------
