/*
CFormula
CFormulae
    CFormObj
CTFPBase
	...
CWPSGroup
CWPSPage
    CWPPSildeBase
        CWPPSlide
        CWPPMaster
*/

// ֻ��Ϊ���Ű�ÿ�
#if 0
	typedef int		KCOLORINDEX;
	typedef int		CWpsImage;
	typedef int		CWpsOleItem;
	typedef int		CTextPool;
	typedef int		KSTextString;
	typedef int		KSTextStringList;

	const int		linkLine = 0, linkBezier = 1;

	struct CHARFXHSS
	{
		int			hssFlag;		// ָ����Ϊ����, �������Ӱ��
		int			hssDepth;		// ����/����/��Ӱ�ĳ̶�
		int			hssDegree;		// ����/��Ӱ�ĽǶ�
		KCOLORINDEX	hssFromColor;	// ��ʼ��ɫ
		KCOLORINDEX	hssToColor;		// ��ֹ��ɫ
		int			hssPara;		// ��������
	};
#endif
// 

//���������Ͷ���
enum OBJACTIONTYPE
{
	enumObjAction_None = 0,		//�޶���
	enumObjAction_PageJump,		//ҳ��ת
	enumObjAction_DocJump,		//�ĵ���ת
	enumObjAction_Run,			//���г���
	enumObjAction_HLink,		//��������
	enumObjAction_Email,		//�����ʼ�
	enumObjAction_Comment		//����ע��
};

// CWPSObj����̽ṹ(WPS2001)
class CWPSObj
{
	CRect	m_rect;
	
	OBJACTIONTYPE m_nLBObjActionType;	//����������
	CString	m_strLBObjAction;
	BOOL	m_bLBObjActionValid;
	BOOL	m_bLBPlaySound;
	int		m_nLBSoundId;
	CString m_strLBSoundName;
	
	OBJACTIONTYPE m_nMoveObjActionType;	//����ƹ�����
	CString m_strMoveObjAction;
	BOOL	m_bMoveObjActionValid;
	BOOL	m_bMovePlaySound;
	int		m_nMoveSoundId;
	CString m_strMoveSoundName;
	
	BOOL	m_bUserEditFlag;	//�û��༭���
	
	int		m_nWPPLayoutFlag;	//�˶�����WPP��ʽ������־
	int		m_nWPPCreateByWho;	//�ö�����˭����
	
	bmDialogPara m_bmPresPara;	//����Ч���ı�����Ϣ
};

class bmDialogPara
{
	DWORD	dwReserved[2];
	DWORD	m_showType;
	DWORD	m_bMouseType;
	LONG	m_nTime;
	DWORD	m_bmSpeed;
	DWORD	m_bSoundLoopPlay;	
	CString	m_cstrSoundName;	//�����ļ���

	//WPS2001��ʾWPP�¼�...start
	LONG	m_nSoundId;			//����Id
	CString	m_strObjName;		//��������
	LONG	m_nOverStatus;		//������״̬
	LONG	m_nDryRunTime;		//������ʱ��ʱ��
	LONG	m_nObjPresType;		//������ʾ����
	LONG	m_nTextEffectId;	//������ϸ����Ч��
	DWORD	m_bTextGroup;		//�����Ƿ�������
	LONG	m_nTextGroup;		//��������
	DWORD	m_bTextFrameAnimation;//���ֿ�"�߿򶯻�����"��
	DWORD	m_bTextReverseOrder;  //�Ƿ������
	BYTE	byBufReserved[64];
	//WPS2001��ʾWPP�¼�...end
};

struct ObjType
{
	WORD			m_wObjType;
};

// ����Ķ�������

class CFormula
{
	CWPSObj			base;
	int				m_nFSIndex;
	int				m_nHor;
	int				m_nVer;
	CObList			m_objList;
	ObjType			objType;
};

class CFormulae
{
	CWPSObj			base;
	CObList			m_objList;
	ObjType			objType;
};

class CFormObj
{
	CFormulae		base;
	int				m_nCompLoca;
	int				m_nType;
	BOOL			m_bHasFather;
	if !m_bHasFather				//�ޡ�����������ֺ�
		int			m_nFontSize[4];
		int			m_nFormulaCharMrg;
	endif
	ObjType			objType;
};

class CWPSGroup
{
	CWPSObj			base;
	int				m_nobjsType;
	BOOL			m_bLock;
	DWORD			m_dwObjID;
	int				nNum;
	DWORD			m_SlvObjIDArray[nNum];
	CPoint			m_ObjConnPnt;
	CObList			m_grpobjList;
	ObjType			objType;
};

#if 0
#define		FILEID_PAGE			_T("[WPSPage]")
#endif

class CWPSPage
{
	char			szPageID[strlen(FILEID_PAGE)];
	WORD			m_wPageNumber;
	struct			tagKPAGERECT
	{
		int			nStyle;				//ҳ��߿�������񣬼����ʷ��
		int			nWidth;				//�߿��������
		COLORREF	dwColor;			//�߿���ɫ
		int			nRange;				//����Ӱ�췶Χ
		int			nDistance;			//���о����
	}				m_PageRect;
	BOOL			m_bHasPageRect;
	CWPSObj			base;
	CObList			m_WPSObjectList;
};

class CWPPSlideBase
{
};

class CWPPSlide
{
};

class CWPPMaster
{
};