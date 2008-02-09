/* -------------------------------------------------------------------------
//	�ļ���		��	example/script.h
//	������		��	��ʽΰ
//	����ʱ��	��	4/20/2003 11:55:19 AM
//	��������	��	
//
// -----------------------------------------------------------------------*/
#ifndef __EXAMPLE_SCRIPT_H__
#define __EXAMPLE_SCRIPT_H__

#ifndef __IO_STDIO_H__
#include "io/stdio.h"
#endif

#ifndef __KFC_TEXT_SCRIPT_H__
#include "../script.h"
#endif

// -------------------------------------------------------------------------

inline
void test_textconvert()
{
	typedef KStdioReadArchive ArchiveIn;
	typedef KWriteArchiveImpl<FILE*, StdioAdapter> ArchiveOut;

	ArchiveIn script_in_ar("interface.in");
	ArchiveIn script_out_ar("interface.out");
	ArchiveIn in("datalayer.h");
	ArchiveOut out(stdout);

	_TEXT_SCRIPT TextConvert(script_in_ar, script_out_ar, in, out);
}

// -------------------------------------------------------------------------

#endif /* __EXAMPLE_SCRIPT_H__ */
