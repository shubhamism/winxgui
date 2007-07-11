/* -------------------------------------------------------------------------
//	文件名		：	run_all_cpptest.cpp
//	创建者		：	容健行
//	创建时间	：	2004-5-22 10:00:10
//	功能描述	：	运行配置文件里指定的所有测试程序，把所有测试结果保存为xml文件
//
// -----------------------------------------------------------------------*/

#include "stdafx.h"

// -------------------------------------------------------------------------
#include <iostream>
#include <sys/stat.h>
#include <windows.h>

inline
STDMETHODIMP ExecCommand(
						 IN LPSTR szCmd,
						 OUT int* nExitCode = NULL
						 )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
	
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
	
    // Start the child process. 
    if( !CreateProcess( NULL, // No module name (use command line). 
        szCmd,			  // Command line. 
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        0,                // No creation flags. 
        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
    {
		return E_ACCESSDENIED;
    }
	
    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );
	
	if (nExitCode)
	{
		DWORD nCode;
		GetExitCodeProcess(pi.hProcess, &nCode);
		*nExitCode = (int)nCode;
	}
	
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
	return S_OK;
}

HRESULT AddXmlFileHead(char const* pszResultFile)
{
	if (!pszResultFile)
		return S_FALSE;
	
	FILE* pf = fopen(pszResultFile, "w");
	if(!pf)
	{
		std::cerr << "error: can not open the result file!\n";
		return E_FAIL;
	}

	fputs("<?xml version=\"1.0\" encoding='ISO-8859-1' standalone='yes' ?>\n", pf);
	fputs("<TestAllCppunit>\n", pf);
	
	fclose(pf);

	return S_OK;
}

HRESULT AddXmlFileFoot(char const* pszResultFile)
{
	if (!pszResultFile)
		return S_FALSE;
	
	FILE* pf = fopen(pszResultFile, "a");
	if(!pf)
	{
		std::cerr << "error: can not open the result file!\n";
		return E_FAIL;
	}

	fputs("</TestAllCppunit>\n", pf);
	
	fclose(pf);

	return S_OK;
}

HRESULT AddNameNodHead(char const* pszResultFile, char const* pszTestName)
{
	if (!pszResultFile)
		return S_FALSE;
	
	FILE* pf = fopen(pszResultFile, "a");
	if(!pf)
	{
		std::cerr << "error: can not open the result file!\n";
		return E_FAIL;
	}

	std::string strTestName(pszTestName);
	std::string::size_type pos = 0;
	while (std::string::npos != (pos = strTestName.find_first_of('&', pos)))
	{
		strTestName.insert(pos + 1, "amp;");
		pos += 4;
	}
	
	fputs("<TestUnit>\n", pf);
	fputs("<Name>\n", pf);
	fputs(strTestName.c_str(), pf);
	fputs("</Name>\n", pf);

		
	fclose(pf);

	return S_OK;
}

HRESULT AddNameNodFoot(char const* pszResultFile)
{
	if (!pszResultFile)
		return S_FALSE;
	
	FILE* pf = fopen(pszResultFile, "a");
	if(!pf)
	{
		std::cerr << "error: can not open the result file!\n";
		return E_FAIL;
	}

	fputs("</", pf);
	fputs("TestUnit", pf);
	fputs(">\n", pf);
	
	fclose(pf);
	
	return S_OK;
}

std::string GetTestFileName(std::string strPath)
{
	std::string::size_type pos = strPath.find_last_of("\\/");
	if (std::string::npos == pos)
		return strPath;
	else
		return strPath.substr(pos + 1);
}

std::string GetFullPath(char const* pstrAbsolute, char const* pRelativePath)
{
	if (!strstr(pstrAbsolute, ":\\") && !strstr(pstrAbsolute, ":/"))
		std::cerr << "error absolute name\n";

	std::string strFullPath;

	std::string strAbsolute(pstrAbsolute);
	std::string::size_type pos = strAbsolute.find_last_of("\\/");
	if (!strstr(pRelativePath, ":\\") && !strstr(pRelativePath, ":/"))
	{
		strFullPath = strAbsolute.substr(0, pos);
		strFullPath += '/';
	}

	strFullPath += pRelativePath;

	return strFullPath;
}

#undef main

int main(int argc, char* argv[])
{
	char szThisPath[MAX_PATH] ;	
	::GetModuleFileName (NULL, szThisPath, MAX_PATH) ;

	char const* pszConFile = 0;		// 配置文件，里面指定要执行的程序（每个程序一行）
	char const* pszResultFile = 0;	// 测试结果文件，如果没有指定，则把结果输出到控制台

	for (int i = 1; i < argc; ++i)
	{
		if (0 == strcmp(argv[i], "-cf") && i + 1 <= argc)
			pszConFile = argv[i + 1];
		if (0 == strcmp(argv[i], "-rf") && i + 1 <= argc)
			pszResultFile = argv[i + 1];
	}

	if (!pszConFile)
	{
		std::cerr << "error: no configure file!\n";
		return 1;
	}

	std::string strConFile = GetFullPath(szThisPath, pszConFile);
	pszConFile = strConFile.c_str();

	struct _stat file_stat;
	_stat(pszConFile, &file_stat);
	if (0 != _stat(pszConFile, &file_stat))
	{
		std::cerr << "error: can not open the file!\n";
		return 1;
	}

	FILE* pf = fopen(pszConFile, "r");
	if(!pf)
	{
		std::cerr << "error: can not open the file!\n";
		return 1;
	}

	char* pszPath = new char[file_stat.st_size + 1];
	memset(pszPath, 0, sizeof(char) * (file_stat.st_size + 1));

	AddXmlFileHead(pszResultFile);
	while (fgets(pszPath, file_stat.st_size + 1, pf))
	{
		int nLen = strlen(pszPath);
		if ('\n' == pszPath[nLen - 1])
			pszPath[nLen - 1] = '\0';
		
		std::string strFullPath = GetFullPath(pszConFile, pszPath);
		
		AddNameNodHead(pszResultFile, strFullPath.c_str());
		{
			strFullPath += " -rf ";
			strFullPath += pszResultFile;
			ExecCommand(const_cast<char*>(strFullPath.c_str()), NULL);
		}		
		AddNameNodFoot(pszResultFile);
	}
	AddXmlFileFoot(pszResultFile);

	delete[] pszPath;
	fclose(pf);

	return 0;
}


// -------------------------------------------------------------------------



