/* -----------------------------------------------------------------------*\
 * 关于二进制文件格式描述Script的Rule，可归纳如下

  1). 用户定义类型 - 结构体(struct)、类(class)
		Rule = struct { ... };
		Rule = class  { ... };
		Rule = struct(BaseRule) { ... };
		Rule = class(BaseRule) { ... };

  2). 内置类型 - DWORD、WORD、BYTE、LONG、SHORT、CHAR、etc

  3). 定位语句 - org
		org(offset);		// 含义为: seek(offset, SEEK_SET);
		org(+offset);		// 含义为: seek(offset, SEEK_CUR);
		org(-offset);		// 含义为: seek(-offset, SEEK_CUR);
	  这里，offset可以是任意复杂的C语言表达式。

  4). 条件语句 - if
		if (cond) { ... }
	  这里，cond可以是任意符合C语言规格的条件判断

  5). 成员访问，它可以很自由的出现在各种地方。eg.
		org(wpsHeader.wfhTemplateInfo);
		BYTE data[hdr.cbData];
		if (hdr.cbData)	{...}

  6). 值约束
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
	WORD	wfhCompress;			// 增加压缩标志
	FILETIME wfFileTime;
	DWORD	wfhSystemCodePage;		// 生成的系统代码
	DWORD	wfhOLEBlock;			// OLE Data offset
	DWORD	wfhOLEBlockSize;		// OLE Data size
	DWORD	wMultiLanguageID;		// 增加多语言版本标识[shq	July 23,2001]
	DWORD	wReserve[17];			// Reserve 17 * DWORD - ole block
};

doc = struct // WPS 2002 以前版本的文件格式
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
		LONG		nPara;	// selection 段序号
		LONG		nSen;	// selection 句序号
		DWORD		wChar;	// selection 句内偏移
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
	BYTE	piID[16];					// ID字符串, 为"[PageInfo]"
	WORD	piHeaderSize;				// 本结构的大小
	WORD	piNumOfPage;				// 本文件共分多少页
	DWORD	piPageOffset[piNumOfPage];	// 每页数据在文件中的起始位置
};

KPAGERECT = struct					// 页面边框信息
{
	int			nStyle;				//页面边框线条风格，即画笔风格
	int			nWidth;				//边框线条宽度
	COLORREF	dwColor;			//边框颜色
	int			nRange;				//设置影响范围
	int			nDistance;			//距版芯距离
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
