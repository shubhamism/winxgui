/* -------------------------------------------------------------------------
//	文件名		：	kfc/algo/kmpfind.h
//	创建者		：	许式伟
//	创建时间	：	2004-4-5 20:30:40
//	功能描述	：	
//
//  $Id: kmpfind.h,v 1.2 2006/05/30 00:22:59 xushiwei Exp $
// -----------------------------------------------------------------------*/
#ifndef __KFC_ALGO_KMPFIND2_H__
#define __KFC_ALGO_KMPFIND2_H__

#include <kfc/algo/kmpfind.h>

namespace kfc {

/*
@fn string_FindLimit
@brief	
@arg ar
	输入数据流。
@arg str_to_find
	输入的指定查找的标准string类字符串。
@arg limit
	输入的限制数，查找字符串的范围为当前指针处到限制数处，默认为无限制，即查找范围为到文件结尾为止。
@return
@remark
@*/
template <class ArchiveIn, class String>
KFC_ALGO_API string_FindLimit(
						 ArchiveIn& ar,
						 const String& str_to_find,
						 int limit
						 )
{
	typedef typename ArchiveIn::char_type char_type;
	
	kmp_find<char_type> finder;
	
	HRESULT hr = finder.Init(str_to_find.c_str(), str_to_find.size());
	if (FAILED(hr))
		return hr;
	
	return finder.Next(ar, limit);
}

};

// -------------------------------------------------------------------------
// $Log: kmpfind.h,v $
// Revision 1.2  2006/05/30 00:22:59  xushiwei
// kmpfind.h直接引用kfc的。
//

#endif /* __KFC_ALGO_KMPFIND2_H__ */
