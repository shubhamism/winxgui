/******************************************************************************
	
	Copyright : Adam Straughan 1999

	RuntimeDll.cpp: implementation of the CRuntimeDll class.

******************************************************************************/

#include "stdafx.h"
#include "CallDll.h"
#include "RuntimeDll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// pointer to function in dll
typedef __declspec(dllimport)DWORD (*pfFunc)(void);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRuntimeDll::CRuntimeDll()
{
	m_hDll = NULL;
}

CRuntimeDll::~CRuntimeDll()
{
	Unload();
}

/******************************************************************************
  function : Load
  purpose : load a dll into memory
  args :[return] true on success
		[in] szFilename, the filename of the dll or exe

******************************************************************************/
bool CRuntimeDll::Load(LPCTSTR szFilename)
{
	if (!m_hDll)
		m_hDll = ::LoadLibrary(szFilename);
	if (m_hDll)
		return true;
	return false;
}

/******************************************************************************
  function : Unload
  purpose : frees the library
  args : none

******************************************************************************/
void CRuntimeDll::Unload()
{
	if(m_hDll)
		::FreeLibrary(m_hDll);
	m_hDll = NULL;
}

/******************************************************************************
  function : IsLoaded
  purpose : get the library load state
  args : [return] true if the library has been loaded

******************************************************************************/
bool CRuntimeDll::IsLoaded()
{
	if (m_hDll)
		return true;
	return false;
}

/******************************************************************************
  function : Call
  purpose : call a function in a dll
  args : [in] szFunction, function to call, case sensitive
		 [in] varArg, an array of RT_DLL_ARG's
		 [in] dwArgCount, the number of arguments
		 [out] pRetVal is the returned value, NULL if not required
  Throws: CRuntimeDllException

******************************************************************************/
void CRuntimeDll::Call(LPCTSTR szFunction, RT_DLL_ARG* pArgs,
					   signed int nArgCount, RT_DLL_ARG* pRetVal)
{
	CRuntimeDllException ex;
	Call(szFunction, pArgs, nArgCount, pRetVal, ex);
	if (ex.m_dwError)
		throw ex;
}

/******************************************************************************
  function : Call
  purpose : private version of Call
  args : [in] szFunction, function to call, case sensitive
		 [in] varArg, an array of variants
		 [in] nArgCount, the number of args detailed by varArg
		 [out] pRetVal is the returned value, NULL if not required
		 [in out] ex, for throwing an exception
  
  note: any attempt to throw a local CCallDllException in this function will
	 result in the following warnings:-
     
	 warning C4509: nonstandard extension used: '__CallDll' uses SEH and
	     'CRuntimeDllException' has destructor
     error C2712: Cannot use __try in functions that require object unwinding

	 so we have make this function private and wrapped it in a function that
	 will throw the required Exception.

******************************************************************************/
void CRuntimeDll::Call(LPCTSTR szFunction, RT_DLL_ARG* pArgs,
					   signed int nArgCount, RT_DLL_ARG* pRetVal,
					  CRuntimeDllException &ex)
{
	pfFunc pFun = NULL;	
	DWORD dwTemp;
	DWORD dwRet = 0;
	signed int i;
	
	if (!m_hDll)
	{
		ex.m_strError = "Dll not loaded";
		ex.m_dwError = 1;
		return;
	}
	pFun = (pfFunc)::GetProcAddress(m_hDll, szFunction);
	if (pFun)
	{
		// load the stack (in reverse order)
		for( i=nArgCount-1; i>=0; i--)
		{
			// copy the data to a temporary holder (casts can lose data)
			memcpy(&dwTemp, &(pArgs[i].cVal), sizeof(DWORD));
			// chuck it on the stack
			_asm push dwTemp
		}

		// call the function, data already on the stack
		__try
		{
			if (pRetVal && ARG_R4 == pRetVal->eType)
			{
				// ok I didn't know this bit of asm. I compiled some code and
				// copied it once I had some idea of what the instructions do.
				// call, calls a function
				// fstp, does a store & pop
				_asm
				{
					call dword ptr [pFun]
					fstp dword ptr [dwRet]
				}
			}
			else
			{
				dwRet = (pFun)();
				// equates to this asm, leave it in 'C'
				// call dword ptr [pFun]
				// mov dword ptr [dwRet], eax
			}
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			
			DWORD dwError = GetExceptionCode();
			char* pszMsgBuf = NULL;
			::FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				dwError & 0xFFFF,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &pszMsgBuf,
				0,
				NULL);

			ex.m_strError.Format("DLL Fatal exception (0x%0x)\n%s", dwError, pszMsgBuf);
			if (pszMsgBuf)
				::LocalFree(pszMsgBuf);

			ex.m_dwError = 3;
		} 

		// unload the stack
		for (i = 0; i<nArgCount; i++)
		{
			_asm pop dwTemp
			// copy the data back in case of altered values
			memcpy(&(pArgs[i].cVal), &dwTemp, sizeof(DWORD));				
		}

		// if they asked for the return value give it to them
		if (pRetVal)
			pRetVal->lVal = dwRet;
	}
	else
	{
		ex.m_strError = "Function not found";
		ex.m_dwError = 2;
	}
}

