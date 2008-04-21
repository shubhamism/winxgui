#ifndef _SIMPLE_PLUGIN_H_
#define _SIMPLE_PLUGIN_H_

//fox lib interface simple_plugin
//2006.10.10
//VisualFC@GMAIL.COM

#include <atlmisc.h>
#include <vector>

namespace fox
{
namespace simple_plugin
{
	class loadlib
	{
	protected:
		HMODULE	hLib;
	public:
		loadlib()
		{
			hLib = NULL;
		}
		~loadlib()
		{
			if (hLib)
			{
				::FreeLibrary(hLib);
				hLib = NULL;
			}
		}
		bool load(LPCTSTR lpszLibFileName)
		{
			hLib = ::LoadLibrary(lpszLibFileName);
			return hLib != NULL;
		}
		template <typename FUNC>
		bool GetFunc(FUNC & pfn, LPCSTR lpProcName)
		{
			if (hLib == NULL)
				return false;
			pfn = (FUNC)::GetProcAddress(hLib,lpProcName);
			return pfn != NULL;
		}
	};
	class load_cfg
	{
	public:
		CString load_cfg_str(LPCTSTR lpszKey, LPCTSTR lpszDef = _T(""))
		{
			TCHAR buf[MAX_PATH] = {0};
			::GetPrivateProfileString(cfgApp,lpszKey,lpszDef,buf,MAX_PATH,cfgPath);
			return buf;
		}
		bool load_cfg_bool(LPCTSTR lpszKey, bool bdef)
		{
			return ::GetPrivateProfileInt(cfgApp,lpszKey,bdef ? 1 : 0,cfgPath) != 0;
		}
		CString cfgApp;
		CString cfgPath;
	};

	struct config_base
	{
		CString	guid;
		CString name;
		CString icon;
		CString version;
		CString email;
		CString anchor;
		CString website;
		CString rootPath;
		CString templates;
		CString info;
		int iIcon;
		bool empty()
		{
			return name.IsEmpty() != FALSE;
		}
		void make(CString & str, const CString & key, const CString & value, LPCTSTR sz = _T(":\t"), LPCTSTR end = _T("\r\n"))
		{
			if (!value.IsEmpty())
			{
				str += key;
				str += sz;
				str += value;
				str += end;
			}
		}
		CString get_title()
		{
			CString title;
			make(title,_T("Name"),name);
			make(title,_T("Version"),version);
			make(title,_T("Info"),info);
			make(title,_T("Anchor"),anchor);
			make(title,_T("Email"),email);
			make(title,_T("Website"),website);
			return title;
		}
		void load(LPCTSTR lpszIniFile, LPCTSTR lpszAppName)
		{
			load_cfg lc;
			lc.cfgApp = lpszAppName;
			lc.cfgPath = lpszIniFile;
			name = lc.load_cfg_str(_T("name"));
			anchor = lc.load_cfg_str(_T("anchor"));
			icon = lc.load_cfg_str(_T("icon"));
			version = lc.load_cfg_str(_T("version"));
			website = lc.load_cfg_str(_T("website"));
			email = lc.load_cfg_str(_T("email"));
			info = lc.load_cfg_str(_T("info"));
			templates = lc.load_cfg_str(_T("templates"),_T("Templates"));
		}
	};

	template <class config_t>
	class manager
	{
	public:
		std::vector<config_t>	ar;
	public:
		bool load(LPCTSTR lpszPathName)
		{
			CFindFile ff;
			CString root = lpszPathName;
			root += _T("\\*.*");
			BOOL b = ff.FindFile(root);
			while (b)
			{
				CString ini;
				config_t cfg;
				if ( ff.IsDirectory() )
				{
					ini = ff.GetFilePath()+_T("\\plugin.ini");
					cfg.rootPath = ff.GetFilePath();
				}
				else if (ff.GetFilePath().Right(4) == _T(".ini"))
				{
					ini = ff.GetFilePath();
					cfg.rootPath = lpszPathName;
				}
				if (!ini.IsEmpty())
				{
					cfg.load(ini);
					if (!cfg.empty())
					{
						ar.push_back(cfg);
					}
				}
				b = ff.FindNextFile();	
			}	
			return !ar.empty();
		}
	};
}; //namespace simple_plugin
}; //namespace fox

#endif