#ifndef __CODEWIZ_PLUGIN_H__
#define __CODEWIZ_PLUGIN_H__

#include "./simple_plugin.h"

namespace fox
{
	struct codewiz_args
	{
		codewiz_args()
		{
			codewiz_name[0] = '\0';
			codewiz_info[0] = '\0';
			project_name[0] = '\0';
			project_path[0] = '\0';
			template_path[0] = '\0';
			idd[0] = '\0';
			idd_num = 0;
			idd_array = NULL;
		}
		char codewiz_name[MAX_PATH];
		char codewiz_info[MAX_PATH];
		char project_name[MAX_PATH];
		char project_path[MAX_PATH];
		char template_path[MAX_PATH];
		char idd[MAX_PATH];
		int			 idd_num;
		const char ** idd_array;
	};

	struct codewiz_config : fox::simple_plugin::config_base
	{
		codewiz_config()
		{
			guid = _T("codewiz");
		}
		bool bUseBase;
		bool bUseExt;
		bool bUseUser;

		bool empty()
		{
			return name.IsEmpty() != FALSE;
		}
		void load(LPCTSTR lpszIniFile, LPCTSTR lpszAppName = _T("plugin"))
		{
			config_base::load(lpszIniFile,lpszAppName);

			fox::simple_plugin::load_cfg lc;
			lc.cfgApp = lpszAppName;
			lc.cfgPath = lpszIniFile;

			bUseBase = lc.load_cfg_bool(_T("USE_BASE"),true);
			bUseExt = lc.load_cfg_bool(_T("USE_EXT"),false);
			bUseUser = lc.load_cfg_bool(_T("USE_USER"),false);
		}
	};
};

#endif //__PLUGIN_H__