// SDIDemoDoc.cpp : implementation of the CSDIDemoDoc class
//

#include "stdafx.h"
#include "SDIDemo.h"

#include "SDIDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoDoc

IMPLEMENT_DYNCREATE(CSDIDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CSDIDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoDoc construction/destruction

CSDIDemoDoc::CSDIDemoDoc()
{
	// TODO: add one-time construction code here

}

CSDIDemoDoc::~CSDIDemoDoc()
{
}

BOOL CSDIDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSDIDemoDoc serialization

void CSDIDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoDoc diagnostics

#ifdef _DEBUG
void CSDIDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoDoc commands
