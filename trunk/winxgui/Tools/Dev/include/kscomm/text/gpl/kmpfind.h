/* -------------------------------------------------------------------------
//	�ļ���		��	kfc/algo/kmpfind.h
//	������		��	��ʽΰ
//	����ʱ��	��	2004-4-5 20:30:40
//	��������	��	
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
	������������
@arg str_to_find
	�����ָ�����ҵı�׼string���ַ�����
@arg limit
	������������������ַ����ķ�ΧΪ��ǰָ�봦������������Ĭ��Ϊ�����ƣ������ҷ�ΧΪ���ļ���βΪֹ��
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
// kmpfind.hֱ������kfc�ġ�
//

#endif /* __KFC_ALGO_KMPFIND2_H__ */
