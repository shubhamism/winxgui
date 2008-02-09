// CWpsDib����̽ṹ(WPS98, WPS2001)������һ��λͼ
class CWpsDib
{
	DWORD	m_dwLength;
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD bmiColors[DIBNumColors()];
	BYTE	rgDIBBits[];
};

// CWpsWmf����̽ṹ(WPS98, WPS2001)
class CWpsWmf
{
	DWORD	dwBitsSize;
	BYTE	rgWmfData[];
};

// CWpsImage����̽ṹ(WPS98, WPS2001)
class CWpsImage
{
	ImgPara		m_ImgPara;
	ImgCrop		m_ImgCrop;		// ���п�
	ImgColor	m_ImgColor;		// ɫ��
	COLORREF	m_colorTran;	// ͸��ɫ
	BOOL		m_bNotScreen;	// ����ʾͼ��, always=FALSE, ���ۺ����������ƣ������Բ�������

	if m_ImgPara.nSetSize == 2
		LONG	m_nDrawWidth;
		LONG	m_nDrawHeight;
	endif

	WORD		wWM;			// Image����
	CString		m_szImgName;

	switch wWM
	case 0x4D58					// --> (WMF�ļ�)
		WORD	wWM2;			// canbe zero or 0x4143�� if zero��m_bSaveInFile = FALSE.
		if wWM2 == 0x4143
			CWpsWmf	m_pWmf;
		endif
	
	case 0x4D42					// --> (BMP�ļ�)
		WORD	wWM2;			// canbe zero or 0x4142�� if zero, m_bSaveInFile = FALSE.
		if wWM2 == 0x4142		// m_bSaveInFile = TRUE.
			CWpsDib	m_pDib;
		endif
	
	case 0x4D48					// --> (���DIB, m_bHasAnimate = 1)
		int		m_nTotalDIBNum;	// ����֡����

		if m_nTotalDIBNum > 0
			int	 m_nDibNumber;	// ��ǰ����֡
			int  m_OrgXArray[m_nTotalDIBNum];
			int	 m_OrgYArray[m_nTotalDIBNum];
			byte m_DisposalArray[m_nTotalDIBNum];
			int	 m_DelayTimeArray[m_nTotalDIBNum];
			CWpsDib m_AnimateDIBArray[m_nTotalDIBNum];
			DWORD	m_dwImgWidth;
			DWORD	m_dwImgHeight;
		endif

	case 0x4D56					// WMF�������ļ���
	case 0x4D40					// BMP�������ļ���
	end switch
};

typedef struct tagS_ShadeCtrl	//�������
{
	KCOLORINDEX shadeColor[2];	
	BYTE		shadeDir;		//��䷽��
	BYTE		shadeStyle;		//����(���)
}S_ShadeCtrl;

class CSlideBackground
{
	SHORT		m_nFillType;
	// enBG_SOLIDFILL:			{{ �̶���ɫ���
	//		m_clrSolid;
	// enBG_PATTERNEDFILL:		{{ ͼ�����
	//		nothing;
	// enBG_SHADEDFILL:			{{ �������
	//		m_ShadeCtrl;
	// enBG_TEXTUREDFILL		{{ �������
	// enBG_PICTUREFILL			{{ ͼƬ���
	KCOLORINDEX	m_clrSolid;
	S_ShadeCtrl	m_ShadeCtrl;
	int			m_nTextureIndex;
	int			m_nImgId;
};
