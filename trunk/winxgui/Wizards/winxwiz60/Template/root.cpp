$$RootFileHeader$$
#include "stdafx.h"
#include "resource.h"
$$IF(DialogApp || HTMLPage)
$$ELSE
#include "$$Safe_root$$View.h"
$$ENDIF

// -------------------------------------------------------------------------
// C$$Safe_root$$Dlg

$$IF(bActiveX || HTMLPage)
$$IF(bModeless)
class C$$Safe_root$$MainFrame : public winx::AxMainDlgFrame<C$$Safe_root$$MainFrame, IDD_MAINDLG>
$$ELSE
class C$$Safe_root$$Dlg : public winx::AxModelDialog<C$$Safe_root$$Dlg, IDD_MAINDLG>
$$ENDIF
$$ELSE
$$IF(bModeless)
class C$$Safe_root$$MainFrame : public winx::MainDlgFrame<C$$Safe_root$$MainFrame, IDD_MAINDLG>
$$ELSE
class C$$Safe_root$$Dlg : public winx::ModelDialog<C$$Safe_root$$Dlg, IDD_MAINDLG>
$$ENDIF
$$ENDIF
{
$$IF(!bLookNFeel)
	WINX_ICON(IDI_MAINICON); // icon

$$ENDIF
$$IF(bAccel)
	WINX_DLG_ACCEL(); // enable accelerator
	WINX_ACCEL(IDR_ACCEL);

$$ENDIF
	WINX_CMDS_BEGIN_EX() // command dispatcher
		WINX_CMD(ID_HELP, OnCmdHelp)
	WINX_CMDS_END_EX();

$$IF(!DialogApp)
	WINX_DLGRESIZE_BEGIN_NOGRIPPER(FALSE) // layout
		WINX_DLGRESIZE(IDC_$$SAFE_ROOT$$_VIEW, AnchorAll)
	WINX_DLGRESIZE_END();

$$ENDIF
$$IF(bDDX)
	WINX_DDX_BEGIN() // data exchange
	WINX_DDX_END();

$$ENDIF
$$IF(ListCtrl || TreeCtrl || RichEdit)
private:
	C$$Safe_root$$View* m_pView;

public:
	BOOL OnInitDialog(HWND hDlg, HWND hWndDefaultFocus)
	{
		winx::SubclassDlgItem(&m_pView, hDlg, IDC_$$SAFE_ROOT$$_VIEW);
		return TRUE;
	}

$$ENDIF
$$IF(DialogApp)
public:
	BOOL OnInitDialog(HWND hDlg, HWND hWndDefaultFocus)
	{
$$IF(bDDX)
		DoDataExchange();
$$ENDIF
		return TRUE;
	}
	
$$IF(bDDX)
	void OnOK(HWND hWnd)
	{
		BOOL bSuccess = DoDataExchange(TRUE);
		if (bSuccess)
			CloseDialog(hWnd);
	}

$$ENDIF
$$ENDIF // $$IF(DialogApp)
$$IF(HTMLPage)
private:
	winx::AxCtrlHandle m_ie;

public:
	BOOL OnInitDialog(HWND hDlg, HWND hWndDefaultFocus)
	{
		m_ie.DlgItem(hDlg, IDC_$$SAFE_ROOT$$_VIEW);
		
		CComPtr<IWebBrowser2> spBrowser;
		m_ie.QueryControl(&spBrowser);

		CComVariant v;
		spBrowser->Navigate(CComBSTR("http://www.winxgui.com"), &v, &v, &v, &v);
		return TRUE;
	}
	
$$ENDIF
	void OnCmdHelp(HWND hWnd)
	{
		winx::MsgBox(hWnd, _T("todo!"), _T("About $$Safe_root$$"));
	}
};

// -------------------------------------------------------------------------

$$IF(bModeless)
winx::CAppModule _Module;
$$ELSE
CComModule _Module;
$$ENDIF

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	InitCommonControls(ICC_WIN95_CLASSES);
$$IF(RichEdit)
	InitRichEditControl();
$$ENDIF
$$IF(Window || ScrollWindow)
	C$$Safe_root$$View::RegisterClass();
$$ENDIF
$$IF(bLookNFeel)

	WINX_APP_LOOKNFEEL(hInstance, IDI_MAINICON);
$$ENDIF

$$IF(bGdiplus)
	GdiplusAppInit gdiplus;
$$ENDIF
$$IF(bModeless)
	CAppModuleInit module;

	C$$Safe_root$$MainFrame wndMain;
	wndMain.Create(NULL);
	
	return module.Run();
$$ELSE
	CComModuleInit module;
	C$$Safe_root$$Dlg dlg;
	dlg.DoModal();
	return 0;
$$ENDIF
}

// -------------------------------------------------------------------------
