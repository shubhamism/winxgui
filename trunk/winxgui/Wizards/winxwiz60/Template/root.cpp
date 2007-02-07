$$FileHeader$$

#include "stdafx.h"
#include "resource.h"

// -------------------------------------------------------------------------
// class CImageView

class CImageView : public winx::ScrollWindow<CImageView>
{
	WINX_CLASS("MyView");
	
	WINX_ACCEL(IDR_ACCEL); // accelerator
	
	WINX_CMDS_BEGIN()
		WINX_CMD(ID_FILE_OPEN, OnCmdFileOpen)
	WINX_CMDS_END();

private:
	Gdiplus::Image* m_image;

public:
	LRESULT OnCreate(HWND hWnd, LPCREATESTRUCT lpCS)
	{
		m_image = NULL;
		return 0;
	}

	void OnDestroy(HWND hWnd)
	{
		delete m_image;
		m_image = NULL;
	}

	BOOL OnEraseBkgnd (HWND hWnd, winx::DCHandle dc)
	{
		winx::ClientRect rect(hWnd);
		int x = 0, y = 0;
		if (rect.right > m_sizeAll.cx)
		{
			RECT rectRight = rect;
			rectRight.left = x;
			rectRight.bottom = y;
			dc.FillRect(&rectRight, COLOR_WINDOW);
		}
		if (rect.bottom > m_sizeAll.cy)
		{
			RECT rectBottom = rect;
			rectBottom.top = y;
			dc.FillRect(&rectBottom, COLOR_WINDOW);
		}
		return TRUE;
	}

	void SetImage(Gdiplus::Image* image)
	{
		delete m_image;
		m_image = image;

		SetScrollOffset(0, 0, FALSE);
		if(m_image)
			SetScrollSize(m_image->GetWidth()+1, m_image->GetHeight()+1);
		else
			SetScrollSize(1, 1);
	}

	void OnCmdFileOpen(HWND hWnd)
	{
		winx::OpenFileDialog dlg(
			_T("Images Files(*.jpg;*.png;*.tif;*.bmp;*.gif)\0*.jpg;*.png;*.tif;*.bmp;*.gif\0All Files(*.*)\0*.*\0")
			);
		if (IDOK == dlg.DoModal())
		{
 			USES_CONVERSION;
 			Gdiplus::Image* image = new Gdiplus::Image(T2CW(dlg.lpstrFile));
 			if (image->GetLastStatus() != Gdiplus::Ok)
			{
				delete image;
				winx::ExMsgBoxTrace(hWnd, _T("Error"), _T("Can't load image from %s"), dlg.lpstrFile);
 			}
 			else
 			{
 				SetImage(image);
 			}
		}
	}

	void DoPaint(winx::DCHandle dc)
	{
		if (m_image)
		{
			Gdiplus::Graphics gr(dc);
			Gdiplus::Rect rect(0, 0, m_image->GetWidth(), m_image->GetHeight());
			gr.DrawImage(m_image, rect);
		}
	}
};

// -------------------------------------------------------------------------
// CHelloDlg

class CHelloDlg : public winx::ModalDialog<CHelloDlg, IDD_HELLO>
{
	WINX_DLG_ACCEL(); // enable accelerator

	WINX_CMDS_BEGIN_EX() // command dispatcher
		WINX_CMD(ID_HELP, OnCmdHelp)
	WINX_CMDS_END_EX();

	WINX_DLGRESIZE_BEGIN(FALSE) // layout
		WINX_DLGRESIZE(IDC_CUSTOM1, AnchorAll)
	WINX_DLGRESIZE_END();

public:
	void OnCmdHelp(HWND hWnd)
	{
		winx::MsgBox(hWnd, _T("Welcome to ImageViewer 0.1!"), _T("About ImageViewer"));
	}
};

// -------------------------------------------------------------------------

CComModule _Module;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CImageView::RegisterClass();

	GdiplusAppInit gdiplus;
	CComModuleInit module;
	CHelloDlg dlg;
	dlg.DoModal();
	return 0;
}

// -------------------------------------------------------------------------
// $Log: hello.cpp,v $
