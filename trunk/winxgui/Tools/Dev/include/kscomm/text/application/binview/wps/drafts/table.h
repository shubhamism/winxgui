
class CFrameObj;
class CFrameTable
{
	CFrameObj	base;
	CObList		m_Row;		// 只保存行链表及行表元数组
	WORD		m_InsMarg_left;
	WORD		m_InsMarg_top;
	WORD		m_InsMarg_right;
	WORD		m_InsMarg_bottom;
	CObArray	m_AttribArray;
	WORD		m_objType;
};

class CTableBrc	// 边框
{
	UINT		m_uLPenStyle;
	UINT		m_uLPenSize;
	COLORREF	m_LPenColor;
};

class CTFPBase;
class KSTextString;
class CWpsImage;
class CTableElement
{
	CTFPBase	base;
	CTableBrc	brc[2];
	int			m_nType;	// 表元类型: TT_free, TT_formula, xxx
	KSTextString strText;	// include m_stringSAV(文字、公式)
							// m_LineMode(horz, vertr2l, vertl2r)
							// m_bDefText(默认文字信息)
	SIZE		m_extent;
	CWpsImage*	m_pImg;
	
	if (m_nType & TT_oblique || m_nType & TT_frametext)
		CObList	m_objList;
	endif
	
	CObList		m_AttribList;
	WORD		m_objType;
};

