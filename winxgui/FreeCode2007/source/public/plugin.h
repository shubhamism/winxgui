#ifndef __PLUGIN_H__
#define __PLUGIN_H__

//fox lib interface plugin
//2006.10.10
//QWL1996@GMAIL.COM

#include <atlmisc.h>
#include <vector>

namespace fox
{

template <typename T>
class dynamic_t
{
private:
	HMODULE	hLib;
	T * pT;
public:
	dynamic_t<T>()
	{
		hLib = NULL;
		pT = NULL;
	}
	~dynamic_t<T>()
	{
		if (pT)
			delete pT;
		if (hLib)
			::FreeLibrary(hLib);
	}
	T * operator -> ()
	{
		return pT;
	}
	T * data() const
	{
		return pT;
	}
	bool empty()
	{
		return pT == NULL;
	}
	
	bool load(LPCTSTR lpLibFileName,LPCSTR lpProcName = "fox_get_interface")
	{
		pT = NULL;
		hLib = ::LoadLibrary(lpLibFileName);
		if (hLib)
		{
			typedef T * CREATE_PROC();
			CREATE_PROC * pfn = NULL;
			pfn = (CREATE_PROC*)::GetProcAddress(hLib,lpProcName);
			if (pfn)
			{
				pT = pfn();
			}
		}
		return pT != NULL;
	}
};

template <typename T>
class array_t
{
public:
	array_t<T>()
	{
	}
	~array_t<T>()
	{
		for (std::vector<dynamic_t<T>*>::iterator i = ar.begin(); i != ar.end(); i++)
		{
			delete *i;
		}
		ar.clear();
	}
protected:
	std::vector<dynamic_t<T>*>	ar;
public:
	std::vector<dynamic_t<T>*> & data()
	{
		return ar;
	}
	bool push_back(LPCTSTR lpLibFileName, LPCSTR lpProcName = "fox_get_interface")
	{
		dynamic_t<T> * pT = new dynamic_t<T>;
		if (!pT->load(lpLibFileName,lpProcName))
		{
			delete pT;
			return false;
		}
		ar.push_back(pT);
		return true;
	}
};

} // namespace fox


namespace fox
{
namespace plugin
{
	struct config
	{
		config()
		{
			memset(this,0,sizeof(*this));
		}
		struct _plugin
		{
			TCHAR name[64];
			TCHAR version[64];
			TCHAR classname[64];
		} plugin;
		struct _runtime
		{
			TCHAR library[64];
		} runtime;
		TCHAR	path[MAX_PATH];
		bool empty()
		{
			return lstrlen(plugin.name) == 0 || 
				   lstrlen(plugin.classname) == 0 || 
				   lstrlen(runtime.library) == 0 ;
		}
	};

	class manager
	{
	public:
		std::vector<config>	ar;
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
				config cfg;
				if ( ff.IsDirectory() )
				{
					ini = ff.GetFilePath()+_T("\\plugin.ini");
					lstrcpyn(cfg.path,ff.GetFilePath(),MAX_PATH);
				}
				else if (ff.GetFilePath().Right(4) == _T(".ini"))
				{
					ini = ff.GetFilePath();
					lstrcpyn(cfg.path,lpszPathName,MAX_PATH);
				}
				if (!ini.IsEmpty())
				{
					::GetPrivateProfileString(_T("plugin"),_T("name"),_T(""),cfg.plugin.name,64,ini);
					::GetPrivateProfileString(_T("plugin"),_T("version"),_T(""),cfg.plugin.version,64,ini);
					::GetPrivateProfileString(_T("plugin"),_T("class"),_T(""),cfg.plugin.classname,64,ini);
					::GetPrivateProfileString(_T("runtime"),_T("library"),_T(""),cfg.runtime.library,64,ini);
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

} // namespace plugin
} //namespace fox

#endif //__PLUGIN_H__