
class CFrameObj;
class CFrameTable
{
	CFrameObj	base;
	CObList		m_Row;		// ֻ�����������б�Ԫ����
	WORD		m_InsMarg_left;
	WORD		m_InsMarg_top;
	WORD		m_InsMarg_right;
	WORD		m_InsMarg_bottom;
	CObArray	m_AttribArray;
	WORD		m_objType;
};

class CTableBrc	// �߿�
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
	int			m_nType;	// ��Ԫ����: TT_free, TT_formula, xxx
	KSTextString strText;	// include m_stringSAV(���֡���ʽ)
							// m_LineMode(horz, vertr2l, vertl2r)
							// m_bDefText(Ĭ��������Ϣ)
	SIZE		m_extent;
	CWpsImage*	m_pImg;
	
	if (m_nType & TT_oblique || m_nType & TT_frametext)
		CObList	m_objList;
	endif
	
	CObList		m_AttribList;
	WORD		m_objType;
};

