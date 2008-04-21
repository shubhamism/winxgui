// AppUIPage.cpp: implementation of the CAppUIPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppUIPage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppUIPage::CAppUIPage()
{
	SetTitle("WinxGui AppWizard 8.0 - Step 3 of 3");
	SetHeaderTitle("User Interface Features");
	SetHeaderSubTitle("Selection Application User Interface Features");
	m_dwButton = PSWIZB_BACK | PSWIZB_FINISH;
}

CAppUIPage::~CAppUIPage()
{

}