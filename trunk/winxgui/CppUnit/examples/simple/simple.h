
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SIMPLE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SIMPLE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SIMPLE_EXPORTS
#define SIMPLE_API __declspec(dllexport)
#else
#define SIMPLE_API __declspec(dllimport)
#endif

SIMPLE_API int DoubleOf(int n);
SIMPLE_API int DoubleOf2(int n);
