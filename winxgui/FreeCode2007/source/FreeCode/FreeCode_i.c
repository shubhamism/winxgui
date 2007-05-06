/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 02 18:34:58 2007
 */
/* Compiler settings for E:\FreeCode\FreeCode2007\source\FreeCode\FreeCode.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_FreeCode = {0xE7D439DC,0x0961,0x4BCE,{0xAA,0x93,0xD5,0xAF,0xCF,0x2F,0x57,0xD3}};


const IID IID_ICommands = {0xA5B5FB6C,0x1BBE,0x4B0F,{0xB3,0x8D,0x2A,0xF0,0xD9,0x22,0xC9,0x58}};


const CLSID CLSID_Commands = {0xEBBB095D,0xED60,0x4798,{0xB5,0x61,0xCF,0x18,0xD6,0x1F,0xC0,0x8E}};


const CLSID CLSID_ApplicationEvents = {0x07410535,0x8442,0x428D,{0xA2,0xD5,0x12,0x32,0xE5,0xDC,0xAB,0xF7}};


const CLSID CLSID_DebuggerEvents = {0xD45A4DB0,0x1B67,0x418F,{0x92,0x05,0x49,0x2B,0x8E,0x77,0x14,0x4D}};


#ifdef __cplusplus
}
#endif

