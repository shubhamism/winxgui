// DynaCall.cpp : Defines the entry point for the console application.
//

//------------------------------------------------------------------
//  DoCall.c - Test app for the DynaCall DLL. Ton Plooy 1998
//------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "../dynacall.h"

//------------------------------------------------------------------

int test_dynacall()
{
    UINT       t_uint;
    DYNAPARM   Parm[10];
    HINSTANCE  hInst;
    DWORD      lpFunction;
    RESULT     rc;
    double     d = 3.14159;

    // Call the MessageBox function. 
    hInst      = LoadLibrary("USER32.DLL");
    lpFunction = _dc_SearchProcAddress(hInst, "MessageBoxA");
    if ((LPVOID)lpFunction != NULL) {
        // MessageBox(HWND hWnd, LPCTSTR lpText,
        //            LPCTSTR lpCaption, UINT uType)
        memset(Parm, 0, sizeof(Parm));
        t_uint          = MB_YESNO;
        Parm[0].nWidth  = sizeof(HWND);    
        Parm[1].nWidth  = sizeof(LPCTSTR);
        Parm[2].nWidth  = sizeof(LPCTSTR);
        Parm[3].nWidth  = sizeof(UINT);
        Parm[0].pArg    = NULL;
        Parm[1].pArg    = "Dynacall Demo";
        Parm[2].pArg    = "WDJ";
        Parm[3].dwArg   = MB_YESNO;          
        rc = _dc_DynaCall(DC_CALL_STD, lpFunction, 4, Parm, NULL, 0);
        FreeLibrary(hInst);
        printf("MessageBox: %d\n", rc.Int);
    }
/*
    hInst      = LoadLibrary("msvcrt.dll");
    lpFunction = _dc_SearchProcAddress(hInst, "sin");
    if ((LPVOID)lpFunction != NULL) {
        memset(Parm, 0, sizeof(Parm));
        Parm[0].nWidth  = sizeof(double);
        Parm[0].pArg    = &d;               // Arg is > 4 bytes,
        Parm[0].dwFlags = DC_FLAG_ARGPTR;   //   use pointer
        rc = _dc_DynaCall(DC_CALL_STD_M8, lpFunction, 1, Parm, NULL, 0);
        FreeLibrary(hInst);

        printf("sin(%lf): %.12lf\n", d, rc.Double);
    }
*/
    return 0;
}
//End of File

