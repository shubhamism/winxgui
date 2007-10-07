//============================================================================
//					Configuration file for entire project
//============================================================================

#ifndef __NEWB_CONFIG_H__
#define __NEWB_CONFIG_H__

//============================================================================
//									Includes
//============================================================================


//============================================================================
//									Win 32
//============================================================================
#ifdef _WIN32

//============================================================================
//									Defines
//============================================================================

	//Use MFC?
#ifdef _AFX

#define NEWB_ASSERT(x) ASSERT(x)
#define NEWB_ASSERT_VALID(x)

#else
//		Use your own debug function here
#define NEWB_ASSERT(x)
#define NEWB_ASSERT_VALID(x)

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif

#define NEWB_INLINE inline

//============================================================================
//									Typedefs
//============================================================================
typedef void						NEWB_VOID;
	// Numeric Types.
typedef bool						NEWB_BOOL;
typedef unsigned char				NEWB_BYTE;
typedef unsigned short				NEWB_WORD;
typedef unsigned long				NEWB_DWORD;
typedef int							NEWB_INT;
typedef unsigned int				NEWB_UINT;
typedef long						NEWB_LONG;

//============================================================================
//									Constants
//============================================================================
static const NEWB_BOOL NEWB_TRUE = true;
static const NEWB_BOOL NEWB_FALSE = false;

#else
#error Only support Win32 platform.
#endif

#endif //__NEWB_CONFIG_H__