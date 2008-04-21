// wiz_file.h: interface for the wiz_file class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIZ_FILE_H__C6F726F3_FD96_4A52_8115_8E991F5F97FE__INCLUDED_)
#define AFX_WIZ_FILE_H__C6F726F3_FD96_4A52_8115_8E991F5F97FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
#include <set>
#include <string>

#include "./public/wtlfile.h"
#include "./public/wtlfileex.h"

struct proj_file
{
	CString source;
	CString dest;
	int		type;
	proj_file()
	{
	}
	proj_file(const CString & s, const CString & d, int t) : source(s), dest(d), type(t)
	{
	}
};

class wiz_file  
{
public:
	bool make_poject(LPCTSTR lpszName);
	void replace_line(const CString & in, CString &out);
	bool get_line_if(const CString & line);
	bool conv_file(LPCTSTR lpszInFile, LPCTSTR lpszOutFile);
	bool conv_file_to_ar(LPCTSTR lpszInFile, std::vector<CString> & out);
	wiz_file();
	virtual ~wiz_file();
	std::map<CString,CString>	map_def;
	std::set<CString>		ar_if;
	CString					dest;
	CString					source;
};

#endif // !defined(AFX_WIZ_FILE_H__C6F726F3_FD96_4A52_8115_8E991F5F97FE__INCLUDED_)
