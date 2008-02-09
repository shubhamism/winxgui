// CWpsDib类存盘结构(WPS98, WPS2001)，就是一个位图
class CWpsDib
{
	DWORD	m_dwLength;
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD bmiColors[DIBNumColors()];
	BYTE	rgDIBBits[];
};

// CWpsWmf类存盘结构(WPS98, WPS2001)
class CWpsWmf
{
	DWORD	dwBitsSize;
	BYTE	rgWmfData[];
};

// CWpsImage类存盘结构(WPS98, WPS2001)
class CWpsImage
{
	ImgPara		m_ImgPara;
	ImgCrop		m_ImgCrop;		// 剪切框
	ImgColor	m_ImgColor;		// 色彩
	COLORREF	m_colorTran;	// 透明色
	BOOL		m_bNotScreen;	// 不显示图象, always=FALSE, 由综合设置来控制，此属性不再有用

	if m_ImgPara.nSetSize == 2
		LONG	m_nDrawWidth;
		LONG	m_nDrawHeight;
	endif

	WORD		wWM;			// Image类型
	CString		m_szImgName;

	switch wWM
	case 0x4D58					// --> (WMF文件)
		WORD	wWM2;			// canbe zero or 0x4143， if zero，m_bSaveInFile = FALSE.
		if wWM2 == 0x4143
			CWpsWmf	m_pWmf;
		endif
	
	case 0x4D42					// --> (BMP文件)
		WORD	wWM2;			// canbe zero or 0x4142， if zero, m_bSaveInFile = FALSE.
		if wWM2 == 0x4142		// m_bSaveInFile = TRUE.
			CWpsDib	m_pDib;
		endif
	
	case 0x4D48					// --> (多个DIB, m_bHasAnimate = 1)
		int		m_nTotalDIBNum;	// 动画帧总数

		if m_nTotalDIBNum > 0
			int	 m_nDibNumber;	// 当前动画帧
			int  m_OrgXArray[m_nTotalDIBNum];
			int	 m_OrgYArray[m_nTotalDIBNum];
			byte m_DisposalArray[m_nTotalDIBNum];
			int	 m_DelayTimeArray[m_nTotalDIBNum];
			CWpsDib m_AnimateDIBArray[m_nTotalDIBNum];
			DWORD	m_dwImgWidth;
			DWORD	m_dwImgHeight;
		endif

	case 0x4D56					// WMF不存在文件中
	case 0x4D40					// BMP不存在文件中
	end switch
};

typedef struct tagS_ShadeCtrl	//渐变控制
{
	KCOLORINDEX shadeColor[2];	
	BYTE		shadeDir;		//填充方向
	BYTE		shadeStyle;		//变形(风格)
}S_ShadeCtrl;

class CSlideBackground
{
	SHORT		m_nFillType;
	// enBG_SOLIDFILL:			{{ 固定颜色填充
	//		m_clrSolid;
	// enBG_PATTERNEDFILL:		{{ 图案填充
	//		nothing;
	// enBG_SHADEDFILL:			{{ 渐变填充
	//		m_ShadeCtrl;
	// enBG_TEXTUREDFILL		{{ 纹理填充
	// enBG_PICTUREFILL			{{ 图片填充
	KCOLORINDEX	m_clrSolid;
	S_ShadeCtrl	m_ShadeCtrl;
	int			m_nTextureIndex;
	int			m_nImgId;
};
