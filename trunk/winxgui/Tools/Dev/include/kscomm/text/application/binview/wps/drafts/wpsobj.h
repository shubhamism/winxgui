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

// 只是为了排版好看
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
		int			hssFlag;		// 指定设为空心, 立体或阴影等
		int			hssDepth;		// 空心/立体/阴影的程度
		int			hssDegree;		// 立体/阴影的角度
		KCOLORINDEX	hssFromColor;	// 起始颜色
		KCOLORINDEX	hssToColor;		// 终止颜色
		int			hssPara;		// 辅助参数
	};
#endif
// 

//对象动作类型定义
enum OBJACTIONTYPE
{
	enumObjAction_None = 0,		//无动作
	enumObjAction_PageJump,		//页跳转
	enumObjAction_DocJump,		//文档跳转
	enumObjAction_Run,			//运行程序
	enumObjAction_HLink,		//超级链接
	enumObjAction_Email,		//电子邮件
	enumObjAction_Comment		//对象注释
};

// CWPSObj类存盘结构(WPS2001)
class CWPSObj
{
	CRect	m_rect;
	
	OBJACTIONTYPE m_nLBObjActionType;	//鼠标左键动作
	CString	m_strLBObjAction;
	BOOL	m_bLBObjActionValid;
	BOOL	m_bLBPlaySound;
	int		m_nLBSoundId;
	CString m_strLBSoundName;
	
	OBJACTIONTYPE m_nMoveObjActionType;	//鼠标移过动作
	CString m_strMoveObjAction;
	BOOL	m_bMoveObjActionValid;
	BOOL	m_bMovePlaySound;
	int		m_nMoveSoundId;
	CString m_strMoveSoundName;
	
	BOOL	m_bUserEditFlag;	//用户编辑标记
	
	int		m_nWPPLayoutFlag;	//此对象与WPP版式关联标志
	int		m_nWPPCreateByWho;	//该对象由谁创建
	
	bmDialogPara m_bmPresPara;	//动画效果的保存信息
};

class bmDialogPara
{
	DWORD	dwReserved[2];
	DWORD	m_showType;
	DWORD	m_bMouseType;
	LONG	m_nTime;
	DWORD	m_bmSpeed;
	DWORD	m_bSoundLoopPlay;	
	CString	m_cstrSoundName;	//声音文件名

	//WPS2001演示WPP新加...start
	LONG	m_nSoundId;			//声音Id
	CString	m_strObjName;		//对象名称
	LONG	m_nOverStatus;		//动画后状态
	LONG	m_nDryRunTime;		//排练计时的时间
	LONG	m_nObjPresType;		//对象演示类型
	LONG	m_nTextEffectId;	//文字详细动画效果
	DWORD	m_bTextGroup;		//文字是否分组出现
	LONG	m_nTextGroup;		//分组的组号
	DWORD	m_bTextFrameAnimation;//文字框"边框动画出现"？
	DWORD	m_bTextReverseOrder;  //是否反序出现
	BYTE	byBufReserved[64];
	//WPS2001演示WPP新加...end
};

struct ObjType
{
	WORD			m_wObjType;
};

// 具体的对象数据

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
	if !m_bHasFather				//无“父”，则读字号
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
		int			nStyle;				//页面边框线条风格，即画笔风格
		int			nWidth;				//边框线条宽度
		COLORREF	dwColor;			//边框颜色
		int			nRange;				//设置影响范围
		int			nDistance;			//距版芯距离
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