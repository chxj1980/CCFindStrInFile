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