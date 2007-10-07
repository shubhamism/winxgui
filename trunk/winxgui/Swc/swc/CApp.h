/*
 * <F> CApp.h		1.0  23/09/2003
 *
 * Copyright 2003 Francisco Campos. All rights reserved.
 * BEYONDATA  PROPRIETARY. Use is subject to license terms. </F>
 *
 *			 \|||/
 *			 |o_o|
 *	----o00o-------o00o---      
 **/


#if !defined(C_APP_H__INCLUDED_)
#define C_APP_H__INCLUDED_
#pragma once



#include "stdafx.h"

class CFrame;
class CApp 
{
public:
	HINSTANCE m_hInstance;
public:
	HINSTANCE m_prehInstance;
	LPSTR     m_LineCommands;
	LPCTSTR	  m_MenuResource;
	int m_nShow;			/*almacena la forma en que se presenta la aplicacion*/
	WINDOWPLACEMENT wp;	
	CMenu m_Menu;
protected:
	HACCEL hAccelTable;		/*Manejador de accesos rapidos al menu*/
public:
	CFrame* m_WinMain;		/*ventana principal de la aplicacion*/
	BOOL   bMDI;			/*El programa soporta MDI? */
	TCHAR			m_lpBuffer[512];
	LPCTSTR			MlpTitle;
public:
	
	/*
	 *  <Function> class CApp </Function>
	 *  <Description> 
	 *   Constructor por defecto del modulo principal de la aplicacion, se inicializa la ventana principal, la instancia y el soporte
	 *   de ventana a SDI.
	 *  </Description>
	 *  <return>  </return>
	 *****/

	CApp()
	{
		m_WinMain=0;
		m_hInstance=0;
		bMDI=0;
		theApp=this;
		m_MenuResource=0;
	}

	BOOL registerClass(HINSTANCE m_hInstance)
	{
		//---------------------
		//main window
		//---------------------
		WNDCLASSEX	wcex;
		wcex.cbSize			= sizeof(wcex); 
		wcex.lpfnWndProc	= (WNDPROC)CWin::WndProc;
		wcex.style			= 0;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= m_hInstance;
		wcex.hIcon			= LoadIcon (IDI_APPLICATION) ;
		wcex.hCursor		= LoadCursor(IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH) (COLOR_BTNFACE+1);
		wcex.lpszMenuName	= (LPCSTR)NULL;
		wcex.lpszClassName	= _T("MotsusMainWindow");
		wcex.hIconSm		= LoadIcon(IDI_APPLICATION);
		if ( ! RegisterClassEx( &wcex ))
			return FALSE;
		
		//----------------
		//Child Window
		//---------------
		wcex.lpszClassName	= _T( "MotsusChildWindow" );
		
		if ( ! RegisterClassEx( &wcex ))
			return FALSE;
		return TRUE;
	}

	void SetMenuResource(LPCTSTR Rsr)
	{m_MenuResource=Rsr;}
	
	LPCTSTR GetmenuResource()
	{return m_MenuResource;}

	void SetRegistryKey(LPCSTR lpKey);

	/*
	 *  <Function> InitInstance </Function>
	 *  <Description> 
	 *   funcion virtual, en cada nueva aplicacion se debe definir, en ella se incluye el inicio de la ventana principal
	 *  </Description>
	 *  <return> 0/1 </return>
	 *****/

	virtual int InitInstance(){return 0;};

	
	/*
	 *  <Function> ~CApp() </Function>
	 *  <Description> 
	 *   Destructor del modulo principal de la aplicacion, incialmente se verifica si existe una ventana principal definida
	 *   en caso afirmativo se envia un mensaje de WM_DESTROY	
	 *  </Description>
	 *  <return> </return>
	 *****/
	
	virtual ~CApp();	

	
	/*
	 *  <Function>LoadMain </Function>
	 *  <Description> 
	 *   En esta funcion se captura los parametros pasados por la funcion WinMain y se almacenan para uso posterior
	 *  </Description>
	 * <param> hInstance,Prehinstance,cmdLine,Show : parametros de la funcion WinMain </param>
	 *  <return> </return>
	 *****/
	
	void LoadMain(HINSTANCE hinstace, HINSTANCE PrehInstance, LPSTR cmdLine, int show);

	/*
	 *  <Function>LoadAccelerators </Function>
	 *  <Description> 
	 *   En esta funcion carga las teclas aceleradoras de la aplicacion
	 *  </Description>
	 *  <param> LPCTSTR lpTableName : Nombre de la tabla de teclas aceleradoras </param>
	 *  <return> El handle del objeto</return>
	 *****/
		
	HACCEL LoadAccelerators(LPCTSTR lpTableName);
	
	/*
	 *  <Function>FindResource </Function>
	 *  <Description> 
	 *   Esta funcion es un wrapper de la funcion ::FindResource (Ver referencia del api de windows)
	 *  </Description>
	 *  <param> UINT nResourceID : ID del recurso </param>
	 *  <param> LPCTSTR lpType : Tipo del Recurso </param>
	 *  <return> El handle del objeto</return>
	 *****/
	
	HRSRC FindResource(UINT nResourceID, LPCTSTR lpType);
	
	/*
	 *  <Function>FindResourceToolBar </Function>
	 *  <Description> 
	 *   Esta funcion carga un recurso de tipo toolbar
	 *  </Description>
	 *  <param> UINT nResourceID : ID del recurso </param>
	 *  <return> El handle del objeto</return>
	 *****/
	
	HRSRC FindResourceToolBar(UINT nResourceID);
	
	
	/*
	 *  <Function>LoadResource </Function>
	 *  <Description> 
	 *   Esta funcion es un wrapper de la funcion LoadResource del api de windows
	 *  </Description>
	 *  <param> HRSRC hRsrc: Handle del recurso , previo cargue con la funcion FindResource </param>
	 *  <return> El handle del objeto</return>
	 *****/
	
	HGLOBAL LoadResource(HRSRC hRsrc);
		
	/*
	 *  <Function>LoadMenu </Function>
	 *  <Description> 
	 *   Carga el recurso de menu para una aplicacion
	 *  </Description>
	 *  <param> LPCTSTR lpszMenuName : Nombre del recurso de menu a cargar </param>
	 *  <return> TRUE/FALSE </return>
	 *****/
	
	BOOL LoadMenu(LPCTSTR lpszMenuName);
	
	/*
	 *  <Function>LoadMenuMDI </Function>
	 *  <Description> 
	 *   Carga el recurso de menu para una ventana MDI
	 *  </Description>
	 *  <param> LPCTSTR lpszMenuName : Nombre del recurso de menu a cargar </param>
	 *  <return> El handle del menu MDI </return>
	 *****/
	
	
	HMENU LoadMenuMDI(LPCTSTR lpszMenuName);
	
	/*
	 *  <Function>LoadMenuWindow </Function>
	 *  <Description> 
	 *   Esta funcion efectua la siguiente operacion, si el handle del menu principal es diferente del handle de menu
	 *   almacena en la clase, pone por defecto el menu de la ventana principal 
	 *  </Description>
	 *  <return> El handle del menu actual</return>
	 *****/
	
	HMENU LoadMenuWindow();
	

	HMENU GetMenuDefault()
	{
		return m_Menu.GetHandleMenu();
	}	

	/*
	 *  <Function>Run </Function>
	 *  <Description> 
	 *   Esta funcion dispone del bucle principal de lectura de la cola de mensajes, la funcion hace el direccionamiento del handle
	 *   de la tabla aceleradora de teclas dependiendo del tipo de aplicacion (MDI/SDI)
	 *  </Description>
	 *  <return> devuelve el campo wParam de la estrcutura MSG</return>
	 *****/

	int Run();
		
	/*
	 *  <Function>GetMainWindows </Function>
	 *  <Description> 
	 *   Esta funcion retorna el handle de la ventana principal de la aplicacion
	 *  </Description>
	 *  <return> un apuntador a una variable de tipo CWin </return>
	 *****/
	
	CWin* GetMainWindows();


	int LoadString(UINT uID,LPTSTR lpBuffer,int nBufferMax)
	{
		return ::LoadString(m_hInstance,uID,lpBuffer,nBufferMax);
	}
	
	void SetTitleWindow(LPCTSTR m_title)
	{
		LPCTSTR MlpTitle = m_title;
	}

	/*
	 *  <Function>GetInstance </Function>
	 *  <Description> 
	 *   Retorna la instancia actual de la aplicacion
	 *  </Description>
	 *  <return> El handlde de la aplicacion actual </return>
	 *****/
	
	HINSTANCE GetInstance(){return m_hInstance;};
	
	HICON LoadIcon(UINT hResource)
	{
		return (HICON) ::LoadImage (m_hInstance, 
						MAKEINTRESOURCE (hResource),IMAGE_ICON, 
						::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
		
	}
	HICON LoadIcon(LPCSTR lpIconName)
	{
		return ::LoadIcon(m_hInstance,lpIconName);
	}
     
	HCURSOR LoadCursor(LPCTSTR lpCursorName)
	{
		return ::LoadCursor(m_hInstance,lpCursorName);
	}


	int  DisplaySystemVersion()
	{
	   OSVERSIONINFOEX osvi;
	   BOOL bOsVersionInfoEx;

	   // Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	   //
	   // If that fails, try using the OSVERSIONINFO structure.

	   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	   if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
	   {
		  // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.

		  osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		  if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
			 return FALSE;
	   }

	   switch (osvi.dwPlatformId)
	   {
		  case VER_PLATFORM_WIN32_NT:

		  // Test for the product.

			 if ( osvi.dwMajorVersion <= 4 )
				return WINNT;

			 if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
				return WIN2000;

			 if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
				return WINXP;

      

		  case VER_PLATFORM_WIN32_WINDOWS:

			 if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
			 {
				 printf ("Microsoft Windows 95 ");
				 if ( osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B' )
					printf("OSR2 " );
			 } 

			 if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
			 {
				 printf ("Microsoft Windows 98 ");
				 if ( osvi.szCSDVersion[1] == 'A' )
					printf("SE " );
			 } 

			 if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
			 {
				 printf ("Microsoft Windows Me ");
			 } 
			 break;

		  case VER_PLATFORM_WIN32s:

			 printf ("Microsoft Win32s ");
			 break;
	   }
	   return TRUE; 
	}

	
	friend int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);

	
};

#endif // !defined(C_APP_H__INCLUDED_)