// wiz_file.cpp: implementation of the wiz_file class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wiz_file.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

wiz_file::wiz_file()
{

}

wiz_file::~wiz_file()
{

}

static CString make_guid()
{
	GUID m_guid;
	m_guid = GUID_NULL;
	::CoCreateGuid(&m_guid);
	TCHAR rString[256];
	wsprintf(rString, _T("%08lX-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X"), 
		// first copy...
		m_guid.Data1, m_guid.Data2, m_guid.Data3, 
		m_guid.Data4[0], m_guid.Data4[1], m_guid.Data4[2], m_guid.Data4[3],
		m_guid.Data4[4], m_guid.Data4[5], m_guid.Data4[6], m_guid.Data4[7],
		// second copy...
		m_guid.Data1, m_guid.Data2, m_guid.Data3, 
		m_guid.Data4[0], m_guid.Data4[1], m_guid.Data4[2], m_guid.Data4[3],
		m_guid.Data4[4], m_guid.Data4[5], m_guid.Data4[6], m_guid.Data4[7]);

	return rString;
}

static CString make_symbol()
{
	GUID m_guid;
	m_guid = GUID_NULL;
	::CoCreateGuid(&m_guid);
	TCHAR rString[256];
	wsprintf(rString, _T("%08lX_%04X_%04x_%02X%02X_%02X%02X%02X%02X%02X%02X"), 
		// first copy...
		m_guid.Data1, m_guid.Data2, m_guid.Data3, 
		m_guid.Data4[0], m_guid.Data4[1], m_guid.Data4[2], m_guid.Data4[3],
		m_guid.Data4[4], m_guid.Data4[5], m_guid.Data4[6], m_guid.Data4[7],
		// second copy...
		m_guid.Data1, m_guid.Data2, m_guid.Data3, 
		m_guid.Data4[0], m_guid.Data4[1], m_guid.Data4[2], m_guid.Data4[3],
		m_guid.Data4[4], m_guid.Data4[5], m_guid.Data4[6], m_guid.Data4[7]);

	return rString;
}

static bool is_all_true(std::vector<bool> & v)
{
	if (v.size() == 0)
		return false;
	for (std::vector<bool>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (*it == false)
			return false;
	}
	return true;
}

static bool line2array(const CString & line, std::vector<CString> & ar, LPCTSTR sz = _T("||"))
{
	int l = line.Find(_T("("));
	int r = line.Find(_T(")"));
	if( l == -1 || r == -1)
		return false;
	CString text = line.Mid(l+1,r-l-1);
	CString tmp;
	int pos = -1;
	int start = 0;
	while(true)
	{
		pos = text.Find(sz,start);
		if (pos != -1)
		{
			tmp = text.Mid(start,pos-start);
			tmp.TrimLeft();
			tmp.TrimRight();
			ar.push_back(tmp);
			start = pos + lstrlen(sz);
		}
		else
		{
			tmp = text.Right(text.GetLength()-start);
			tmp.TrimLeft();
			tmp.TrimRight();
			ar.push_back(tmp);
			break;
		}
	}
	return true;
}


bool wiz_file::conv_file(LPCTSTR lpszInFile, LPCTSTR lpszOutFile)
{
	std::vector<CString> ar;
	if (!conv_file_to_ar(lpszInFile,ar))
		return false;

	CTextWriteFile	out;
	if (!out.Open(lpszOutFile))
		return false;
	
	int size = ar.size();
	for (int i = 0; i < size; i++)
	{
		out.WriteLine(ar[i],ar[i].GetLength());
	}
	out.Close();

	return true;
}

bool wiz_file::conv_file_to_ar(LPCTSTR lpszInFile, std::vector<CString> & out)
{
	CTextFile	in;
	if (!in.Open(lpszInFile))
		return false;

	CString line;
	std::vector<CString> ar;
	std::vector<bool>	 b_ar;
	typedef std::vector<CString>::iterator it;
	while (in.ReadLine(line))
	{
		if (line.Find(_T("$$IF(")) != -1)
		{
			bool b = get_line_if(line);
			b_ar.push_back(b);
			ATLTRACE("%d ",b_ar.size());
			ATLTRACE(line);
			ATLTRACE(",%d\r\n",b);
		}
		else if (line.Find(_T("$$ENDIF")) != -1)
		{
			b_ar.pop_back();
				ATLTRACE("%d ",b_ar.size());
				ATLTRACE(line);
				ATLTRACE("\r\n");
		}
		else if (line.Find(_T("$$ELIF(")) != -1)
		{
			if (!b_ar.empty())
			{
				bool b = b_ar[b_ar.size()-1] = get_line_if(line);
				ATLTRACE("%d ",b_ar.size());
				ATLTRACE(line);
				ATLTRACE(",%d\r\n",b);
			}
		}
		else if (line.Find(_T("$$ELSE")) != -1)
		{
			if (!b_ar.empty())
			{
				bool b = b_ar[b_ar.size()-1] = !b_ar[b_ar.size()-1];
				ATLTRACE("%d ",b_ar.size());
				ATLTRACE(line);
				ATLTRACE(",%d\r\n",b);
			}
		}
		else if (is_all_true(b_ar))
		{
			ar.push_back(line);
		}
		else if (b_ar.empty())
		{
			ar.push_back(line);
		}
	}

	int size = ar.size();
	CString tmp;
	for (int i = 0; i < size; i++)
	{
		replace_line(ar[i],tmp);
		out.push_back(tmp);
	}

	in.Close();

	return true;
}


bool wiz_file::get_line_if(const CString &line)
{
	std::vector<CString> ar;
	if (line2array(line,ar) == false)
		return false;
	for (int i = 0; i < ar.size(); i++)
	{
		if (ar[i].Left(1) == _T("!"))
		{
			if (ar_if.find(ar[i].Right(ar[i].GetLength()-1)) == ar_if.end())
				return true;
		}
		if (ar_if.find(ar[i]) != ar_if.end())
			return true;
	//	for (int j = 0; j < ar_if.size(); j++)
	//	{
	//		if (ar_if[j] == ar[i])
	//			return true;
	//	}
	}
	return false;
}

void wiz_file::replace_line(const CString &in, CString &out)
{
	out = in;
	for (std::map<CString,CString>::iterator it = map_def.begin(); it != map_def.end(); it++)
	{
		out.Replace(it->first,it->second);
	}
}

bool  make_proj_file(const CString & line, int t, proj_file & f)
{
	int i = line.Find('\t');
	if (i != -1)
	{
		f.source = line.Left(i);
		f.dest = line.Right(line.GetLength()-i-1);
		f.dest.TrimLeft();
		f.type = t;
		return true;
	}
	return false;
}

bool wiz_file::make_poject(LPCTSTR lpszName)
{
	std::vector<CString> out;
	if (!conv_file_to_ar(lpszName,out))
		return false;
	CString text;
	std::vector<CString> files;

	std::vector<proj_file> ar_files;
	int i = 0;
	for ( i = 0; i < out.size(); i++)
	{
		if (out[i].Find(_T("$$")) != -1)
			continue;
		text = out[i];
		text.TrimLeft();
		text.TrimRight();
		if (text.IsEmpty())
			continue;
		ATLTRACE(out[i]);
		ATLTRACE("\r\n");
		//make direct

// newproj.inf = template for list of template files
//  format is 'sourceResName' \t 'destFileName'
//    The source res name may be preceded by any combination of '=', '-',  '!', '?', ':', '#', and/or '*'
//       '=' => the resource is binary
//       '-' => the file should not be added to the project (all files are added to the project by default)
//       '!' => the file should be marked exclude from build
//       '?' => the file should be treated as a help file
//       ':' => the file should be treated as a resource
//       '#' => the file should be treated as a template (implies '!')
//       '*' => bypass the custom AppWizard's resources when loading
//	if name starts with / => create new subdir

		CString text2 = text.Right(text.GetLength()-1);
		
		::CreateDirectory(dest,0);

		int type = 0;
		if (text.Left(1) == _T("/"))
		{
			::CreateDirectory(dest+_T("\\")+text.Right(text.GetLength()-1),0);
			continue;
		}
		else if (text.Left(1) == _T("="))
		{
			type = 7;
		}
		else if (text.Left(1) == _T("-"))
		{
			type = 1;
		}
		else if (text.Left(1) == _T("!"))
		{
			type = 2;
		}
		else if (text.Left(1) == _T("?"))
		{
			type = 3;
		}
		else if (text.Left(1) == _T(":"))
		{
			type = 4;
		}
		else if (text.Left(1) == _T("#"))
		{
			type = 5;
		}
		else if (text.Left(1) == _T("*"))
		{
			type = 6;
		}
		else
		{
			type = 0;
		}
		if (type != 0)
			text = text2;

		proj_file pf;
		if (make_proj_file(text,type,pf))
		{
			ar_files.push_back(pf);

			if (pf.source == _T("frame.h"))
				map_def["$$frame_hfile$$.h"] = pf.dest;
			else if (pf.source == _T("view.h"))
				map_def["$$view_hfile$$.h"] = pf.dest;
			else if (pf.source == _T("ChildFrm.h"))
				map_def["$$child_frame_hfile$$.h"] = pf.dest;
		}	
	}

	map_def["$$INSERT_LOCATION_COMMENT$$"] = _T("VisualFC AppWizard will insert additional declarations immediately before the previous line.");
	map_def["$$TLID_ODL$$"] = make_guid();
	map_def["$$APPID_ODL$$"] = make_guid();
	map_def["$$ATL_CURRENT_YEAR$$"] = _T("2008");


	for (i = 0; i < ar_files.size(); i++)
	{
		proj_file & pf = ar_files[i];
		if (pf.type == 0 || pf.type == 1)
		{
			CString tmp = pf.dest;
			tmp.Replace(_T("."),_T("_"));
			tmp.MakeUpper();
			map_def["$$FILE_NAME_SYMBOL$$"] = _T("AFX_")+tmp+make_symbol();
			ATLTRACE("-------- conv file: %s %s -------\r\n",source+_T("\\")+pf.source,dest+_T("\\")+pf.dest);
			conv_file(source+_T("\\")+pf.source,dest+_T("\\")+pf.dest);
		}
		else
		{
			ATLTRACE("-------- copy file: %s %s -------\r\n",source+_T("\\")+pf.source,dest+_T("\\")+pf.dest);
			::CopyFile(source+_T("\\")+pf.source,dest+_T("\\")+pf.dest,TRUE);
		}
	}

	return true;
}
