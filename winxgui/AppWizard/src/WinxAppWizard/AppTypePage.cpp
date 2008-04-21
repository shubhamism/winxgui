// AppTypePage.cpp: implementation of the CAppTypePage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppTypePage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppTypePage::CAppTypePage()
{
	SetTitle("WinxGui AppWizard 8.0 - Step 2 of 3");
	SetHeaderTitle("Application Type");
	SetHeaderSubTitle("Selection Application Type");
	m_dwButton = PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_FINISH;
}

CAppTypePage::~CAppTypePage()
{

}
