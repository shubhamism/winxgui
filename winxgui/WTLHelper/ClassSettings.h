#pragma	   once

#include "settings.h"

#define SETTINGS_NAME_SAVE_RECT(name, variable)\
	ATLVERIFY(Archive.StartObject(name));\
	ATLVERIFY(Archive.SaveVariable(_T("left"), variable.left));\
	ATLVERIFY(Archive.SaveVariable(_T("top"), variable.top));\
	ATLVERIFY(Archive.SaveVariable(_T("right"), variable.right));\
	ATLVERIFY(Archive.SaveVariable(_T("bottom"), variable.bottom));\
	ATLVERIFY(Archive.EndObject(name));

#define SETTINGS_NAME_LOAD_RECT(name, variable)\
	ATLVERIFY(Archive.StartObject(name));\
	ATLVERIFY(Archive.LoadVariable(_T("left"), variable.left));\
	ATLVERIFY(Archive.LoadVariable(_T("top"), variable.top));\
	ATLVERIFY(Archive.LoadVariable(_T("right"), variable.right));\
	ATLVERIFY(Archive.LoadVariable(_T("bottom"), variable.bottom));\
	ATLVERIFY(Archive.EndObject(name));

#define SETTINGS_NAME_RECT(name, variable)\
	{\
		if (bSave)\
		{\
			SETTINGS_NAME_SAVE_RECT(name, variable)\
		}\
		else\
		{\
			SETTINGS_NAME_LOAD_RECT(name, variable)\
		}\
	}

#define SETTINGS_RECT(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_RECT(lpName, variable)\
	}

#define SETTINGS_NAME_LOAD_RECT_OPT(name, variable)\
	if (Archive.StartObject(name))\
	{\
		Archive.LoadVariable(_T("left"), variable.left);\
		Archive.LoadVariable(_T("top"), variable.top);\
		Archive.LoadVariable(_T("right"), variable.right);\
		Archive.LoadVariable(_T("bottom"), variable.bottom);\
		ATLVERIFY(Archive.EndObject(name));\
	}

#define SETTINGS_NAME_RECT_OPT(name, variable)\
	{\
		if (bSave)\
		{\
			SETTINGS_NAME_SAVE_RECT(name, variable)\
		}\
		else\
		{\
			SETTINGS_NAME_LOAD_RECT_OPT(name, variable)\
		}\
	}

#define SETTINGS_RECT_OPT(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_RECT_OPT(lpName, variable)\
	}

#define SETTINGS_NAME_POINT(name, variable)\
	{\
		if (bSave)\
		{\
			ATLVERIFY(Archive.StartObject(name));\
			ATLVERIFY(Archive.SaveVariable(_T("x"), variable.x));\
			ATLVERIFY(Archive.SaveVariable(_T("y"), variable.y));\
			ATLVERIFY(Archive.EndObject(name));\
		}\
		else\
		{\
			ATLVERIFY(Archive.StartObject(name));\
			ATLVERIFY(Archive.LoadVariable(_T("x"), variable.x));\
			ATLVERIFY(Archive.LoadVariable(_T("y"), variable.y));\
			ATLVERIFY(Archive.EndObject(name));\
		}\
	}

#define SETTINGS_POINT(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_POINT(lpName, variable)\
	}

#define SETTINGS_NAME_POINT_OPT(name, variable)\
	{\
	if (bSave)\
		{\
		ATLVERIFY(Archive.StartObject(name));\
		ATLVERIFY(Archive.SaveVariable(_T("x"), variable.x));\
		ATLVERIFY(Archive.SaveVariable(_T("y"), variable.y));\
		ATLVERIFY(Archive.EndObject(name));\
		}\
		else\
		{\
			if (Archive.StartObject(name))\
			{\
				Archive.LoadVariable(_T("x"), variable.x); \
				Archive.LoadVariable(_T("y"), variable.y); \
				ATLVERIFY(Archive.EndObject(name));\
			}\
		}\
	}

#define SETTINGS_POINT_OPT(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_POINT_OPT(lpName, variable)\
	}

#define SETTINGS_NAME_SIZE(name, variable)\
	{\
	if (bSave)\
		{\
		ATLVERIFY(Archive.StartObject(name));\
		ATLVERIFY(Archive.SaveVariable(_T("cx"), variable.cx));\
		ATLVERIFY(Archive.SaveVariable(_T("cy"), variable.cy));\
		ATLVERIFY(Archive.EndObject(name));\
		}\
		else\
		{\
		ATLVERIFY(Archive.StartObject(name));\
		ATLVERIFY(Archive.LoadVariable(_T("cx"), variable.cx));\
		ATLVERIFY(Archive.LoadVariable(_T("cy"), variable.cy));\
		ATLVERIFY(Archive.EndObject(name));\
		}\
	}

#define SETTINGS_SIZE(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_SIZE(lpName, variable)\
	}

#define SETTINGS_NAME_SIZE_OPT(name, variable)\
	{\
	if (bSave)\
		{\
			ATLVERIFY(Archive.StartObject(name));\
			ATLVERIFY(Archive.SaveVariable(_T("cx"), variable.cx));\
			ATLVERIFY(Archive.SaveVariable(_T("cy"), variable.cy));\
			ATLVERIFY(Archive.EndObject(name));\
		}\
		else\
		{\
			if (Archive.StartObject(name))\
			{\
				Archive.LoadVariable(_T("cx"), variable.cx); \
				Archive.LoadVariable(_T("cy"), variable.cy); \
				{\
					ATLVERIFY(Archive.EndObject(name));\
				}\
			}\
		}\
	}

#define SETTINGS_SIZE_OPT(variable)\
	{\
		SKIP_PREFIX(_T(#variable))\
		SETTINGS_NAME_SIZE_OPT(lpName, variable)\
	}

#define SETTINGS_WINDOW_RECT(variable)\
	{\
		RECT r;\
		if (bSave)\
		{\
			::GetWindowRect(variable, &r);\
			SETTINGS_NAME_SAVE_RECT(_T("WINDOW_RECT"), r)\
		}\
		else\
		{\
			SETTINGS_NAME_LOAD_RECT(_T("WINDOW_RECT"), r)\
			::MoveWindow(variable, &r);\
		}\
	}

#define SETTINGS_WINDOW_RECT_DEFAULT(variable, defvalue)\
	{\
		RECT r;\
		if (bSave)\
		{\
			::GetWindowRect(variable, &r);\
			SETTINGS_NAME_SAVE_RECT(_T("WINDOW_RECT"), r)\
		}\
		else\
		{\
			SETTINGS_NAME_LOAD_RECT_DEFAULT(_T("WINDOW_RECT"), r, defvalue)\
			::MoveWindow(variable, &r);\
		}\
	}

#define SETTINGS_NAME_WINDOW_RECT(name, variable)\
	{\
	RECT r;\
	if (bSave)\
		{\
		::GetWindowRect(variable, &r);\
		SETTINGS_NAME_SAVE_RECT(name, r)\
		}\
		else\
		{\
		SETTINGS_NAME_LOAD_RECT(name, r)\
		::MoveWindow(variable, &r);\
		}\
	}

#define SETTINGS_NAME_WINDOW_RECT_DEFAULT(name, variable, defvalue)\
	{\
	RECT r;\
	if (bSave)\
		{\
		::GetWindowRect(variable, &r);\
		SETTINGS_NAME_SAVE_RECT(name, r)\
		}\
		else\
		{\
		SETTINGS_NAME_LOAD_RECT_DEFAULT(name, r, defvalue)\
		::MoveWindow(variable, &r);\
		}\
	}
			