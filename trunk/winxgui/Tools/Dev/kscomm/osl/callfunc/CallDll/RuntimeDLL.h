/******************************************************************************
	
	Copyright : Adam Straughan 1999

	RuntimeDLL.h: interface for the CRuntimeDLL class.

******************************************************************************/

#pragma once

class CRuntimeDllException
{
public:
	CRuntimeDllException(){m_dwError=0;};
	CString m_strError;
	DWORD m_dwError;
};

enum ARGTYPE
{
	ARG_NONE=-1,		//    terminator or no args
	ARG_UI1=0,			//    unsigned char
	ARG_I1,				//    signed char	  
	ARG_UI2,			//    unsigned short
	ARG_I2,				//    signed short  
	ARG_UI4,			//	  unsigned long 
	ARG_I4,				//	  signed long   
	ARG_R4,				//	  float         
	ARG_PUI1,			//	  unsigned char*	
	ARG_PI1,			//	  signed char*	
	ARG_PUI2,			//	  unsigned short*	
	ARG_PI2,			//	  signed short*	
	ARG_PUI4,			//	  unsigned long*	
	ARG_PI4,			//	  signed long*	
	ARG_PR4				//	  float*			
};

typedef struct
{
	ARGTYPE  eType;
	union
	{
        unsigned char	ucVal;    // ARG_UI1
        signed char	    cVal;     // ARG_I1
        unsigned short  usVal;    // ARG_UI2
        signed short    sVal;     // ARG_I2
        unsigned long   ulVal;	  // ARG_UI4
        signed long     lVal;	  // ARG_I4
        float           fltVal;   // ARG_R4

		unsigned char*	pucVal;	  // ARG_PUI1
		char*			pcVal;	  // ARG_PI1
		unsigned short*	pusVal;	  // ARG_PUI2
		signed short*	psVal;	  // ARG_PI2
		unsigned long*	pulVal;	  // ARG_PUI4
		signed long*	plVal;	  // ARG_PI4
		float*			pfltVal;  // ARG_PR4
	};
}RT_DLL_ARG;

/******************************************************************************
  
  class : CRuntimeDll
  purpose : represents one dll, load then call as many functions as required

******************************************************************************/
class CRuntimeDll
{
public:
	bool IsLoaded();
	void Unload();
	CRuntimeDll();
	virtual ~CRuntimeDll();

	bool Load(LPCTSTR szFilename);
	void Call(LPCTSTR szFunction, RT_DLL_ARG* pArgs,
					   signed int ArgCount, RT_DLL_ARG* pRetVal);
protected:
	// data
	HINSTANCE m_hDll;
	
	// methods
	void Call(LPCTSTR szFunction, RT_DLL_ARG* pArgs,
					   signed int nArgCount, RT_DLL_ARG* pRetVal,
					  CRuntimeDllException &ex);

};

