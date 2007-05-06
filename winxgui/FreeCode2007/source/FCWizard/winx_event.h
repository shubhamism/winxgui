#ifndef _WINXEV_H__
#define _WINXEV_H__

#include "../public/wtlfileex.h"

struct winx_kind
{
	int		kind;	//分类
	CString name;	//分类名称
};

struct winx_event 
{
	int		kind;	//分类
	CString name;	//名称
	CString func;	//主函数
	CString body;	//主体
	CString help;	//帮助

	void empty()
	{
		name.Empty();
		func.Empty();
		body.Empty();
		help.Empty();
		kind = 0;
	}
};

class winx_event_config
{
public:
	CSimpleArray<winx_event> m_items;
	CSimpleArray<winx_kind>	 m_kinds;
public:
	bool loadex(LPCTSTR ini)
	{
		int n_kind = 0;
		int n_item = 0;
		n_kind = ::GetPrivateProfileInt(_T("event"),_T("kind"),32,ini);
		n_item = ::GetPrivateProfileInt(_T("event"),_T("item"),128,ini);
		TCHAR sz[256] = {0};
		DWORD ret = 0; 
		CString key;
		winx_kind kind;
		for (int i = 0; i < n_kind; i++)
		{
			key.Format(_T("%d"),i+1);
			ret = ::GetPrivateProfileString(_T("kind"),key,_T(""),sz,255,ini);
			if (ret == 0)
			{
				continue;
			}
			else
			{
				kind.kind = i+1;
				kind.name = sz;
				m_kinds.Add(kind);
			}
		}
		
		CTextFile file;
		if (!file.Open(ini))
			return FALSE;
		CString line;
		bool b_item = false;
		int  n_text = 0;
		CString text;
		winx_event ev;

		while (file.ReadLine(line))
		{
			line.TrimLeft();
			line.TrimRight();
			if (line.IsEmpty())
			{
				continue;
			}
			int n_kind = 0;
			int n_item = 0;
			if (line.Compare(_T("<item>")) == 0)
			{
				if (!ev.name.IsEmpty())
				{
					MessageBox(NULL,ev.name+_T(" No find </item>"),_T("Error"),0);
				}
				ev.empty();
				b_item = true;
				continue;
			}
			else if (line.Compare(_T("</item>")) == 0)
			{
				if (b_item == true && !ev.name.IsEmpty())
				{
					m_items.Add(ev);
					ev.empty();
				}
				b_item = false;
			}

			n_text = line.Find(_T('='),4);
			if (n_text == -1)
			{
				continue;
			}
			text = line.Right(line.GetLength()-n_text-1);
			text.TrimLeft();

			if (b_item == true)
			{
				if (line.Left(4).Compare(_T("name")) == 0)
				{
					ev.name = text;
				}
				else if (line.Left(4).Compare(_T("kind")) == 0)
				{
					ev.kind = ::_ttoi(text);
				}
				else if (line.Left(4).Compare(_T("func")) == 0)
				{
					ev.func = text;
				}
				else if (line.Left(4).Compare(_T("body")) == 0)
				{
					ev.body = text;
				}
				else if (line.Left(4).Compare(_T("help")) == 0)
				{
					ev.help = text;
				}
			}
		}
		file.Close();
		return TRUE;
	}
};

#endif