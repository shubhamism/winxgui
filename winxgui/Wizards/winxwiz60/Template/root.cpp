$$RootFileHeader$$
#include "stdafx.h"
#include "resource.h"

$$IF(!DialogApp)
// -------------------------------------------------------------------------
// class C$$Safe_root$$View

class C$$Safe_root$$View : public winx::$$ViewType$$<C$$Safe_root$$View>
{
	WINX_CLASS("$$Safe_root$$View");

$$IF(bAccel)
	WINX_ACCEL(IDR_ACCEL); // accelerator

$$ENDIF
	WINX_CMDS_BEGIN()
	WINX_CMDS_END();
$$IF(ScrollWindow)
$$IF(fGdiplus)

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
$$ELSE

public:
	LRESULT OnCreate(HWND hWnd, LPCREATESTRUCT lpCS)
	{
		SetScrollSize(800, 800);
		return 0;
	}

	void DoPaint(winx::DCHandle dc)
	{
		dc.TextOut(1, 1, _T("Hello, WINX!"));
		dc.TextOut(1, 300, _T("You are welcome!"));
	}
$$ENDIF
$$ENDIF
$$IF(Window)

public:
	void OnPaint(HWND hWnd)
	{
		winx::PaintDC dc(hWnd);
		dc.TextOut(1, 1, _T("Hello, WINX!"));
	}
$$ENDIF
};

$$ENDIF
// -------------------------------------------------------------------------
// C$$Safe_root$$Dlg

class C$$Safe_root$$Dlg : public winx::ModalDialog<C$$Safe_root$$Dlg, IDD_$$SAFE_ROOT$$>
{
$$IF(bAccel)
	WINX_DLG_ACCEL(); // enable accelerator

$$ENDIF
	WINX_CMDS_BEGIN_EX() // command dispatcher
		WINX_CMD(ID_HELP, OnCmdHelp)
	WINX_CMDS_END_EX();

$$IF(!DialogApp)
	WINX_DLGRESIZE_BEGIN_NOGRIPPER(FALSE) // layout
		WINX_DLGRESIZE(IDC_$$SAFE_ROOT$$_VIEW, AnchorAll)
	WINX_DLGRESIZE_END();

$$ENDIF
public:
	void OnCmdHelp(HWND hWnd)
	{
		winx::MsgBox(hWnd, _T("todo!"), _T("About $$Safe_root$$"));
	}
};

// -------------------------------------------------------------------------

CComModule _Module;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	InitCommonControls(ICC_WIN95_CLASSES);
$$IF(!DialogApp)
	C$$Safe_root$$View::RegisterClass();
$$ENDIF

$$IF(fGdiplus)
	GdiplusAppInit gdiplus;
$$ENDIF
	CComModuleInit module;
	C$$Safe_root$$Dlg dlg;
	dlg.DoModal();
	return 0;
}

// -------------------------------------------------------------------------
// $Log: hello.cpp,v $
