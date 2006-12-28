/* -------------------------------------------------------------------------
// WINX: a C++ template GUI library - MOST SIMPLE BUT EFFECTIVE
// 
// This file is a part of the WINX Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.txt at this distribution. By using
// this software in any fashion, you are agreeing to be bound by the terms
// of this license. You must not remove this notice, or any other, from
// this software.
// 
// Module: tpl/toolbox/SmartHtml.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-12-27 19:36:49
// 
// $Id: $
// -----------------------------------------------------------------------*/
#ifndef __TPL_TOOLBOX_SMARTHTML_H__
#define __TPL_TOOLBOX_SMARTHTML_H__

#ifndef _STRING_
#include <string>
#endif

#ifndef _SET_
#include <set>
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef _STACK_
#include <stack>
#endif

namespace tpl { namespace smart_html {

// -------------------------------------------------------------------------
// class TagInfoBuilder

typedef std::string Tag;
typedef const std::string& TagArgT;

enum TagCategoryMask
{
	OptionalEndTag	= 0x0001,
	ForbiddenEndTag	= 0x0002,
};

struct TagInfo
{
	typedef std::set<Tag> AutoEndTagSet;

	int maskCategory;
	AutoEndTagSet onStartTag;
	AutoEndTagSet onEndTag;
};

class TagInfoBuilder
{
private:
	typedef std::map<Tag, const TagInfo*> TagInfoMap;

	TagInfoMap m_data;
	
public:
	TagInfoBuilder()
	{
	}

	const TagInfo* get(TagArgT tag) const
	{
		TagInfoMap::const_iterator it = m_data.find(tag);
		if (it == m_data.end())
			return NULL;
		else
			return (*it).second;
	}
};

// -------------------------------------------------------------------------
// class XHtmlWriter

class XHtmlWriter
{
private:
	typedef std::stack<Tag> TagStack;

	TagStack m_ancestors;

public:
	template <class ArchiveT>
	HRESULT winx_call startTag(ArchiveT& ar, TagArgT tag)
	{
		if (m_onStartTag.count(tag))
		{
		}
	}

	template <class ArchiveT>
	HRESULT winx_call endTag(ArchiveT& ar, TagArgT tag)
	{
	}
};

// -------------------------------------------------------------------------
// $Log: $

}; };

#endif /* __TPL_TOOLBOX_SMARTHTML_H__ */
