/* -------------------------------------------------------------------------
//	�ļ���		��	filefmt/filefmt.h
//	������		��	��ʽΰ
//	����ʱ��	��	2002-5-25 16:37:34
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __FILEFMT_FILEFMT_H__
#define __FILEFMT_FILEFMT_H__

#if 0
	typedef int round;
#endif

class CWpsDoc;
class CTextPool;
class CWPSObj;

typedef struct tagWPSFILEHEADER
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
} WPSFILEHEADER;

typedef struct tagPAGEINFOHEADER
{
	BYTE	piID[16];					// ID�ַ���, Ϊ"[PageInfo]"
	WORD	piHeaderSize;				// ���ṹ�Ĵ�С
	WORD	piNumOfPage;				// ���ļ����ֶ���ҳ
	DWORD	piPageOffset[piNumOfPage];	// ÿҳ�������ļ��е���ʼλ��
} PAGEINFOHEADER;

struct tagKPAGERECT
{//ҳ��߿���Ϣ
	int			nStyle;				//ҳ��߿�������񣬼����ʷ��
	int			nWidth;				//�߿��������
	COLORREF	dwColor;			//�߿���ɫ
	int			nRange;				//����Ӱ�췶Χ
	int			nDistance;			//���о����
};

IStream "$"
{
	// wps header
	WPSFILEHEADER	wpsHeader;
	round(16);
	
	// Template info, template-file only
	BYTE	tagTempateInfo[] = "[TemplateInfo]";
	WORD	nSizeSum;					// nSizeName + nSizeCom + 3*sizeof(WORD)
	WORD	nTplType;
	WORD	nSizeName;
	BYTE	lpszTplName[nSizeName];		// WPTName
	WORD	nSizeCom;
	BYTE	lpszTplComment[nSizeCom];	// WPTDesc
	round(16);

	// Auto-Save info, afsfile only
	BYTE	tagAutoSaveInfo[] = "[AutoSaveInfo]";
	DWORD	nSizeSum;
	DWORD	nSizeFileName;
	BYTE	csStrFile[nSizeFileName];
	DWORD	nSizeTitle;
	BYTE	csStrTitle[nSizeTitle];
	round(16);

	// style sheet
	BYTE	tagStyleSheet[] = "[StyleSheet]";
	CStyleSheet_Text m_StySht_Text;
	round(16);
	
	// serial number
	BYTE	tagSerialNum[] = "[SerialNum]\0";
	WORD	cbNum;
	BYTE	szNum[cbNum];
	round(16);

	// Document Data
	CWpsDoc		_this;
	round(16);
	
	// Main text
	BYTE		tagMainText[] = "[WPSText]";
	CTextPool	c_pTextPool;
	CTextPool	c_pFootnoteTextPool;
	CFootnoteMan m_FootnoteMan;
	LONG		nPara;	// selection �����
	LONG		nSen;	// selection �����
	DWORD		wChar;	// selection ����ƫ��
	round(16);

	// WPS Pages
	PAGEINFOHEADER	PIH;
	CWPSPage		m_WPSPages[PIH.piNumOfPage];
	round(16);

	// Summary info
	BYTE	tagSummaryInfo[] = "[Summary]\0";
	BYTE	SummaryInfo[wpsHeader.wfhSumSize];
	round(16);
	
	// Book Mark
	BYTE	tagBookMark[] = "[BookMark]\0";
	BYTE	BookMark[wpsHeader.wfhBookMarkSize];
	round(16);
	
	// Comment					{{ --> OLE Data
	// Extend Document Data		{{ --> OLE Data
	// TOC						{{ --> OLE Data
	// OLE Data
	DWORD		tagOLEData = 0x10101010;
	DWORD		nSize;
	COLEData	m_OleDataArray[nSize];
};

class CStyleSheet_Text
{
	CObArray<CStyle_Text*> m_aryStyle;
};

class CStyle_Text
{
	CStyleBase	base;
	DWORD		m_dwStyle;
	DWORD		m_dwBaseStyle;
	CString		m_strBaseStyleName;
	DWORD		dwReserved[4];
	CObList<>	m_PAList;
	CObList<>	m_CAList;
	DWORD		m_dwPreStyle;
	CString		m_strPreStyleName;
	DWORD		m_dwFollowStyle;
	CString		m_strFollowStyleName;
};

class CStyleBase
{
	CString		m_strName;
};

class CFootnoteMan
{
	BYTE	tagFootnote[] = "[Footnote]\0";
	DWORD	dwLength;
	BYTE	pBuffer[dwLength];
	// COLEData: FNPrefix, FNSuffix, ENPrefix, ENSuffix
};

class CWPSPage
{
	BYTE	tagWPSPage[] = "[WPSPage]";
	WORD	m_wPageNumber;
	tagKPAGERECT m_PageRect;
	DWORD	m_bHasPageRect;
	CWPSObj base;
	CObList<CWPSObj*> m_WPSObjectList;
};

class COLEData
{
	DWORD	dwflag;
	DWORD	nStrLen;
	BYTE	m_strName[nStrLen];
	DWORD	m_nBufSize;
	BYTE	m_pData[m_nBufSize];
};

#endif /* __FILEFMT_FILEFMT_H__ */
