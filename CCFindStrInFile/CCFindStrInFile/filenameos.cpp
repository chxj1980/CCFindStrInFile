#include "stdafx.h"
#include "filenameos.h"
#include "CCFindStrInFile.h"


std::string GetFileDirectory(std::string strFilePath)
{
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath(strFilePath.c_str(), drive, dir, fname, ext);

	//�ϳ�·������ȥ
	std::string strFileDir = drive;
	strFileDir += dir;
	return strFileDir;
}

//д���ļ����������浯��
int DisInFile(std::vector<std::string> arrSrcPath)
{
	TCHAR MyDir[_MAX_PATH];
	SHGetSpecialFolderPath(theApp.GetMainWnd()->m_hWnd, MyDir, CSIDL_DESKTOP, 0);
	std::string strFile = "";
	sprintf(const_cast<char*>(strFile.c_str()), "%s", MyDir);
	strFile += "\\result.txt";
	//FILE* fp = fopen(strFile.c_str(), "wt");
	//if (fp == NULL)
	//	AfxMessageBox(_T("Open File Error in read Result"));
	
	if (arrSrcPath.size() <= 0)
	{
		AfxMessageBox(_T("No File"));
		return 0;
	}


	//write file
	AllocConsole();
	freopen(strFile.c_str(), "wt", stdout);
	std::vector<std::string>::iterator iter = arrSrcPath.begin();
	for (; iter != arrSrcPath.end(); iter++)
	{
		printf("%s\n", iter->data());
	}
	fclose(stdout);
	FreeConsole();
	std::string strCmd = "notepad.exe ";
	strCmd += strFile;
	WinExec(strCmd.c_str(), SW_SHOW);
	return (int)arrSrcPath.size();
}

//����������ļ��н������ļ�·�����
void ReverseDirectory(std::string strPath, std::vector<std::string>& arrFilepath)
{
	//������ļ���
	CFileFind finder;
	//const char*ת����LPCTSTR�ļ�
	//���ﱾ����ȡ����һ���ļ�·��
	//�����ļ�·���ҵ�����Ŀ¼
	std::string strFilePathG = GetFileDirectory(strPath);
	strFilePathG += "*.*";

	// = (LPCTSTR)strFilePathG.c_str();
	CString strFilePathW;
	char* p = const_cast<char*>(strFilePathG.c_str());
	//strFilePathW.Format("%s", p);//error C2664: 'void ATL::CStringT<wchar_t,StrTraitMFC_DLL<wchar_t,ATL::ChTraitsCRT<wchar_t>>>::Format(UINT,...)': cannot convert argument 1 from 'const char [3]' to 'const wchar_t *'
	strFilePathW = p;
	BOOL bResult = finder.FindFile(strFilePathW);
	while (bResult)
	{
		bResult = finder.FindNextFile();
		if (finder.IsDots())
			continue;
		USES_CONVERSION;
		if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			std::string strs = W2A(str);
			strs += "\\";
			::SendMessage(theApp.GetMainWnd()->m_hWnd, MSG_SHOW_MSG, 0, (LPARAM)&str);
			ReverseDirectory(strs, arrFilepath);
		}
		CString strFilePath = finder.GetFilePath();
		std::string strFilePaths = W2A(strFilePath);
		arrFilepath.push_back(strFilePaths);
	}
	return;
}


//�����ַ���
bool FindString(std::string strData, std::string strFilePath)
{
	//���ļ�,�����ַ������ر��ļ�����ֵ
	FILE* fp = fopen(strFilePath.c_str(), "rt");
	if (fp == NULL)
		return false;

	//�����ַ���
	char chValue[2048] = "";
	while (!feof(fp))
	{
		fgets(chValue, 2047, fp);
		if (strstr(chValue, strData.c_str()) != NULL)
			return true;
	}
	return false;
}

void FindString(std::vector<std::string>& arrDesPath, std::vector<std::string> arrSrcPath, std::string strStrFind)
{
	//�����ַ�������������Ӧ�ַ������ļ�д�뵽д�뵽ָ���ַ�����
	std::vector<std::string>::iterator iter = arrSrcPath.begin();
	for (; iter != arrSrcPath.end(); iter++)
	{
		if (FindString(strStrFind, iter->data()))
		{
			arrDesPath.push_back(iter->data());
			::SendMessage(theApp.GetMainWnd()->m_hWnd, MSG_SHOW_MSG, 0, (LPARAM)((*iter).c_str()));
		}	
	}
}