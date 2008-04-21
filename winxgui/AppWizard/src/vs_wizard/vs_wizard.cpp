// vs_wizard.cpp: implementation of the vs_wizard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vs_wizard.h"
#include "../public/wtlfile.h"
#include "../public/wtlfileex.h"

vs_wizard_info::vs_wizard_info()
{
	templatePath = GetModulePath(_Module.m_hInst)+_T("\\templates");
	cfgPath = GetModulePath(NULL)+_T("\\setup.ini");
	cfgApp = _T("AppWizard");

	nWizardRet = -1;
}

CString vs_wizard_info::GetModulePath(HMODULE hMod)
{
	CString path;
	//取得程序所在路径
	TCHAR exeFullPath[MAX_PATH];
	::GetModuleFileName(hMod,exeFullPath,MAX_PATH);
	CString strPath = exeFullPath;
	int r = strPath.ReverseFind(_T('\\'));
	if (r != -1)
	{
		path = strPath.Left(r);
	}
	return path;
}

bool vs_wizard_info::load_cfg_bool(LPCTSTR lpszKey, bool bdef)
{
	return ::GetPrivateProfileInt(cfgApp,lpszKey,bdef ? 1 : 0,cfgPath) != 0;
}

void vs_wizard_info::save_cfg_bool(LPCTSTR lpszKey, bool bval)
{
	::WritePrivateProfileString(cfgApp,lpszKey,bval ? _T("1") : _T("0"),cfgPath);
}

int vs_wizard_info::load_cfg_int(LPCTSTR lpszKey, int def)
{
	return ::GetPrivateProfileInt(cfgApp,lpszKey,def,cfgPath);
}

void vs_wizard_info::save_cfg_int(LPCTSTR lpszKey, int val)
{
	TCHAR buf[20] = {0};
	_stprintf(buf,"%d",val);
	::WritePrivateProfileString(cfgApp,lpszKey,buf,cfgPath);
}


CString vs_wizard_info::load_cfg_str(LPCTSTR lpszKey, LPCTSTR lpszDef)
{
	TCHAR buf[MAX_PATH] = {0};
	::GetPrivateProfileString(cfgApp,lpszKey,lpszDef,buf,MAX_PATH,cfgPath);
	return buf;
}

void vs_wizard_info::save_cfg_str(LPCTSTR lpszKey, LPCTSTR lpszVal)
{
	::WritePrivateProfileString(cfgApp,lpszKey,lpszVal,cfgPath);
}

bool vs_wizard_info::load_lang()
{
	CString path = templatePath+_T("\\lang.inf");
	CTextFile file;
	if (!file.Open(path))
		return false;
	CString text;
	ar_lang.clear();
	char buf[100] = {0};
	::GetLocaleInfo(0,1,buf,100);
	int lang = 0;
	while(file.ReadLine(text))
	{
		text.TrimLeft();
		text.TrimRight();
		if (!text.IsEmpty())
		{
			ar_lang.push_back(text);
			char buf2[100] = {0};
			::GetLocaleInfo(_ttol(text),1,buf2,100);
			if (lstrcmp(buf2,buf) == 0)
			{
				nAppLang = lang;
			}
			lang++;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

vs_wizard::vs_wizard()
{

}

vs_wizard::~vs_wizard()
{

}

bool vs_wizard::make_file(LPCTSTR lpszFileIn, LPCTSTR lpszFileOut)
{
	str_vector ar;
	if (!load_file_vector(lpszFileIn,ar))
		return false;

	CTextWriteFile	out;
	if (!out.Open(lpszFileOut))
		return false;
	
	int size = ar.size();
	for (int i = 0; i < size; i++)
	{
		out.WriteLine(ar[i],ar[i].GetLength());
	}
	out.Close();
	return true;
}

bool vs_wizard::load_file_vector(LPCTSTR lpszFileIn, str_vector & out)
{
	ATLTRACE("load_file_vector %s\r\n",lpszFileIn);
	CTextFile	in;
	if (!in.Open(lpszFileIn))
		return false;

	CString line;
	str_vector ar;
	std::vector<bool>	 b_ar;

	typedef std::vector<CString>::iterator it;
	//[!if	x ]
	//[!if	!x ]
	//[!if x && x]
	//[!if x || x ]
	//[!else]
	//[!endif]
	//[!output ]
	while (in.ReadLine(line))
	{
		if (line.Find(_T("[!if")) == 0)
		{
			bool b = get_define_line(line);
			b_ar.push_back(b);
			ATLTRACE("%d ",b_ar.size());
			ATLTRACE(line);
			ATLTRACE(",%d\r\n",b);
		}
		else if (line.Find(_T("[!endif")) == 0)
		{
			b_ar.pop_back();
			ATLTRACE("%d ",b_ar.size());
			ATLTRACE(line);
			ATLTRACE("\r\n");
		}
		else if (line.Find(_T("[!elif")) == 0)
		{
			if (!b_ar.empty())
			{
				//bool b = b_ar[b_ar.size()-1] = get_define_line(line);
				if (b_ar[b_ar.size()-1] == true)
				{
					b_ar[b_ar.size()-1] = false;
				}
				else
				{
					bool b = b_ar[b_ar.size()-1] = get_define_line(line);
					ATLTRACE("%d ",b_ar.size());
					ATLTRACE(line);
					ATLTRACE(",%d\r\n",b);
				}
			}
		}
		else if (line.Find(_T("[!else")) == 0)
		{
			if (!b_ar.empty())
			{
				bool b = b_ar[b_ar.size()-1] = !b_ar[b_ar.size()-1];
				ATLTRACE("%d ",b_ar.size());
				ATLTRACE(line);
				ATLTRACE(",%d\r\n",b);
			}
		}
		else if (get_vector_alltrue(b_ar))
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

bool vs_wizard::get_define_line(LPCTSTR lpszLine)
{
	str_vector ar;
	int flag = 0;
	if (line_to_array(lpszLine,ar,flag) == false)
		return false;
	if (flag == 0)
	{
		for (int i = 0; i < ar.size(); i++)
		{
			if (ar[i].Left(1) == _T("!"))
			{
				if (m_define.find(ar[i].Right(ar[i].GetLength()-1)) == m_define.end())
					return true;
			}
			if (m_define.find(ar[i]) != m_define.end())
				return true;
		}
		return false;
	}
	else if (flag == 1)
	{
		for (int i = 0; i < ar.size(); i++)
		{
			if (ar[i].Left(1) == _T("!"))
			{
				if (m_define.find(ar[i].Right(ar[i].GetLength()-1)) != m_define.end())
				{
					break;
				}
			}
			else if (m_define.find(ar[i]) == m_define.end())
			{
				break;
			}
		}
		if (i == ar.size())
			return true;
		return false;
	}
	return false;
}

bool vs_wizard::line_to_array(LPCTSTR lpszLine, str_vector & ar, int &flag)
{
	CString line = lpszLine;
	int _pos = -1;
	_pos = line.Find(_T("//"));
	if (_pos != -1)
	{
		line = line.Left(_pos);
	}
	int l = line.Find(_T("[!if"));
	if (l != -1)
	{
		l += 4;
	}
	else
	{
		l = line.Find(_T("[!elif"));
		if (l != -1)
			l += 6;
	}
	int r = line.Find(_T("]"));
	if( l == -1 || r == -1)
		return false;
	CString text = line.Mid(l,r-l);
	CString tmp;
	int pos = -1;
	int start = 0;
	while(true)
	{
		pos = text.Find(_T("||"),start);

		if (pos != -1)
			flag = 0;
		else
		{
			pos = text.Find(_T("&&"),start);
			if (pos != -1)
			{
				flag = 1;
			}
		}

		if (pos != -1)
		{
			tmp = text.Mid(start,pos-start);
			tmp.TrimLeft();
			tmp.TrimRight();
			ar.push_back(tmp);
			start = pos + 2;
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

bool vs_wizard::get_vector_alltrue(std::vector<bool> &array)
{
	if (array.size() == 0)
		return false;
	for (std::vector<bool>::iterator it = array.begin(); it != array.end(); it++)
	{
		if (*it == false)
			return false;
	}
	return true;
}

void vs_wizard::replace_line(LPCTSTR in, CString &out)
{
	out = in;

	int l = -1;
	int r = -1;
	int start = 0;
	CString text;
	CString tmp;
	while(true)
	{
		int l = out.Find(_T("[!output"),start);
		if (l == -1)
			break;
		r = out.Find(_T("]"),r+8);
		//is find [!output]
		if (l != -1 && r!= -1)
		{
			text = out.Mid(l,r-l+1);
			tmp = out.Mid(l+8,r-l-8);
			tmp.TrimLeft();
			tmp.TrimRight();
			for (str_map::iterator it = m_output.begin(); it != m_output.end(); it++)
			{
				if (tmp == it->first)
				{
					out.Replace(text,it->second);
					break;
				}
			}
			start += 1;
		}
	}
}

void vs_wizard::AddSymbol(LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	m_output[lpszKey] = lpszValue;
}

void vs_wizard::AddSymbol(LPCTSTR lpszDefine, bool bAdd)
{
	if (bAdd)
	{
		m_define.insert(lpszDefine);
	}
	else
	{
		str_set::iterator it = m_define.find(lpszDefine);
		if (it != m_define.end())
		{
			m_define.erase(it);
		}
	}
}

bool vs_wizard::FindSymbol(LPCTSTR lpszKey)
{
	return (m_define.find(lpszKey) != m_define.end());
}

CString vs_wizard::FindSymbolVal(LPCTSTR lpszKey)
{
	str_map::iterator it = m_output.find(lpszKey);
	if (it != m_output.end())
		return it->second;
	return _T("");
}

CString vs_wizard::make_guid()
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

void vs_wizard::get_define_info(CString & text)
{
	for (str_set::iterator it = m_define.begin(); it != m_define.end(); it++)
	{
		text += (CString)(*it);
		text += _T("\r\n");
	}
}

void vs_wizard::get_output_info(CString & text)
{
	for (str_map::iterator it = m_output.begin(); it != m_output.end(); it++)
	{
		text += it->first+_T(" = ")+it->second;
		text += _T("\r\n");
	}
}

void vs_wizard::clear()
{
	m_define.clear();
	m_output.clear();
}

CString vs_wizard::make_include_guid()
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

bool vs_wizard_info::check_project_name(LPCTSTR lpszFileName)
{
	int len = lstrlen(lpszFileName);
	if (len == 0)
		return false;
	for (int i = 0; i < len; i++)
	{
		if ( (::isalnum(lpszFileName[i]) == 0 ) && (lpszFileName[i] != '_'))
		{
			return false;
		}
	}
	return true;
}