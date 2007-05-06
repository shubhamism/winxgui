#ifndef _WIN32_NOTIFY_H__
#define _WIN32_NOTIFY_H__

#include "../public/wtlfileex.h"
#include "./resources/reshelper.h"

enum win32_notify_kind
{
	wkCOMMAND = 0,
	wkNOTIFY
};

struct win32_notify;

struct win32_notify_code
{
	CString code;
	CString func;
	win32_notify_kind	kind;
};

struct win32_notify
{
	CString					  name; //Button,Edit...
	CAtlArray<CString>		  reswords;	//PUSHBUTTON...
	CAtlArray<win32_notify_code>	  codes; //BN_CLICK...
};

class win32_notify_config
{
public:
	CAtlArray<win32_notify>  m_items;
public:
	enum item_kind
	{
		ikBegin = 0,
		ikEnd,
		ikRes,
		ikText
	};
	void parser_notify_kind(win32_notify_code & wnc, const CString & line)
	{
		if (line.Left(3) == _T("BN_") ||
			line.Left(3) == _T("EN_") ||
			line.Left(4) == _T("CBN_") ||
			line.Left(4) == _T("LBN_") ||
			line.Left(4) == _T("STN_") )
		{
			wnc.kind = wkCOMMAND;
		}
		else
			wnc.kind = wkNOTIFY;
		if (line.Left(4) == _T("LEN_"))
			wnc.code = line.Right(line.GetLength()-1);
		else
			wnc.code = line;
		int pos = wnc.code.Find(_T("_"));
		if (pos != -1)
		{
			wnc.func = _T("On");
			for (int i = 0; i < wnc.code.GetLength(); i++)
			{
				CString ch = wnc.code.GetAt(i);
				if (i == 0 || i == pos+1)
				{
					ch.MakeUpper();
					wnc.func += ch;
				}
				else if (i != pos)
				{
					ch.MakeLower();
					wnc.func += ch;
				}
			}
		}
		else
		{
			wnc.func = _T("On");
		}
	}
	item_kind get_item_kind(const CString & line, CString & out)
	{
		out = line;
		if (line.Left(2) == _T("</") )
		{
			out.TrimLeft(_T("</"));
			out.TrimRight(_T(">"));
			return ikEnd;
		}
		else if (line.Left(1) == _T("<") && line.Right(1) == _T(">"))
		{
			out.TrimLeft(_T("<"));
			out.TrimRight(_T(">"));
			return ikBegin;
		}
		else if (line.Left(4).CompareNoCase(_T("res=")) == 0)
		{
			out = line.Right(line.GetLength()-4);
			return ikRes;
		}
		return ikText;
	}
	bool loadex(LPCTSTR lpszFileName)
	{
		CTextFile file;
		if (file.Open(lpszFileName) == FALSE)
			return false;
		CString line;
		CString out;
		win32_notify * pitem = NULL;
		bool bload = false;
		while(file.ReadLine(line))
		{
			line.TrimLeft();
			line.TrimRight();
			item_kind ik = get_item_kind(line,out);
			if (ik == ikBegin)
			{
				win32_notify item;
				m_items.Add(item);
				pitem = &m_items[m_items.GetCount()-1];
				pitem->name = out;
				bload = true;
			}
			else if (ik == ikEnd)
			{
				bload = false;
			}
			if (bload)
			{
				if (ik == ikRes)
				{
					CutString(out,pitem->reswords,_T(","));
				}
				else if (ik == ikText && !out.IsEmpty())
				{
					win32_notify_code wnc;
					parser_notify_kind(wnc,out);
					pitem->codes.Add(wnc);
				}
			}

		}
		file.Close();
		return true;
	}

	win32_notify * get_notify_by_name(LPCTSTR name)
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			win32_notify & wn = m_items[i];
			if (CString(wn.name).CompareNoCase(name) == 0)
			{
				return &wn;
			}
		}
		return NULL;
	}
	win32_notify * get_notify_by_res(LPCTSTR res_type)
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			win32_notify & wn = m_items[i];
			for (int j = 0; j < wn.reswords.GetSize(); j++)
			{
				if (wn.reswords[j] == res_type)
				{
					return &wn;
				}
			}
		}
		return NULL;
	}
};


#endif