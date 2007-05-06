#ifndef _DSPPARSER_H__
#define _DSPPARSER_H__

//time 2007-4-24
//copyright QWL1996@GMAIL.COM
#include "../public/wtlfileex.h"

class dspparser
{
public:
	CSimpleArray<CString>	source;
	CString					root_path;
public:
	dspparser()
	{
	}
public:
	bool load_dsp(LPCTSTR lpszFileName);
};

inline CString get_file_root(const CString & filename)
{
	int i = filename.ReverseFind(_T('\\'));
	if (i != -1) 
	{
		return filename.Left(i+1);
	}
	return _T("");
}

inline CString get_file_ext(const CString & filename)
{
	int i = filename.ReverseFind(_T('.'));
	if (i != -1) 
	{
		return filename.Right(filename.GetLength()-i);
	}
	return _T("");
}

inline bool dspparser::load_dsp(LPCTSTR lpszFileName)
{
	root_path = get_file_root(lpszFileName);
	CTextFile file;
	if (file.Open(lpszFileName,CFile::modeRead | CFile::shareDenyNone) == FALSE)
	{
		return false;
	}
	CString line;
	CString tmp;
	while(file.ReadLine(line))
	{
		if (line.Left(7) == _T("SOURCE=")) 
		{
			source.Add(line.Right(line.GetLength()-7));
		}
	}
	file.Close();
	return true;
}



#endif //_DSPPARSER_H__