#ifndef __APPWIZ_PLUGIN_H__
#define __APPWIZ_PLUGIN_H__

//fox lib interface plugin
//2006.10.10
//VisualFC@GMAIL.COM

#include "./simple_plugin.h"

namespace fox
{
	struct appwiz_config : simple_plugin::config_base
	{
		appwiz_config()
		{
			guid = _T("appwiz");
		}
		CString root;
		CString clsname;
		CString runtime;
		CString lang;
		bool empty()
		{
			return name.IsEmpty() || runtime.IsEmpty();
		}
		void load(LPCTSTR lpszIniFile)
		{
			config_base::load(lpszIniFile,_T("plugin"));

			fox::simple_plugin::load_cfg lc;
			lc.cfgApp = _T("plugin");
			lc.cfgPath = lpszIniFile;

			clsname = lc.load_cfg_str(_T("class"));
			lang = lc.load_cfg_str(_T("language"));
			root = lc.load_cfg_str(_T("root"));
			runtime = lc.load_cfg_str(_T("runtime"));
		}
	};
} //namespace fox

#endif //__PLUGIN_H__