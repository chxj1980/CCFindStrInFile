#pragma once
#include <iostream>
#include <vector>
#include <afx.h>
#include <atlbase.h>
#include <stdlib.h>


/*
���е���������CSIDL_APPDATA����Ϊ���µ�ֵ��

CSIDL_BITBUCKET   ����վ
CSIDL_CONTROLS   �������
CSIDL_DESKTOP   Windows   ����Desktop
CSIDL_DESKTOPDIRECTORY   Desktop��Ŀ¼
CSIDL_DRIVES   �ҵĵ���
CSIDL_FONTS   ����Ŀ¼
CSIDL_NETHOOD   �����ھ�
CSIDL_NETWORK   �����ھ�����Ŀ¼
CSIDL_PERSONAL   �ҵ��ĵ�
CSIDL_PRINTERS   ��ӡ��
CSIDL_PROGRAMS   ������
CSIDL_RECENT   ����򿪵��ĵ�
CSIDL_SENDTO   �����͵����˵���
CSIDL_STARTMENU   �����������˵���
CSIDL_STARTUP   ����Ŀ¼
CSIDL_TEMPLATES   �ĵ�ģ��

*/
void ReverseDirectory(std::string strPath, std::vector<std::string>& arrFilepath);

void FindString(std::vector<std::string>& arrDesPath, std::vector<std::string> arrSrcPath, std::string strStrFind);

std::string GetFileDirectory(std::string strFilePath);

int DisInFile(std::vector<std::string> arrSrcPath);
