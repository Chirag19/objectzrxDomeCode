#include "stdafx.h"
#include "AppDirectoryUtil.h"
CAppDirectoryUtil::CAppDirectoryUtil()
{

}

CAppDirectoryUtil::~CAppDirectoryUtil()
{

}

CString CAppDirectoryUtil::GetCurrentDirctory(HMODULE hInstance)
{
	TCHAR szPath[256];

	GetModuleFileName(hInstance,szPath,sizeof(szPath));
	*(_tcsrchr(szPath,'\\'))=0;	//�����һ��\���ڵ�λ���޸�Ϊ\0

	CString strResult=szPath;
	return strResult;
}

CString CAppDirectoryUtil::GetParentDirectory(HMODULE hInstance)
{
	TCHAR szPath[256];
	GetModuleFileName(hInstance,szPath,sizeof(szPath));
	*(_tcsrchr(szPath,'\\'))=0;	//�����һ��\���ڵ�λ���޸�Ϊ\0
	*(_tcsrchr(szPath,'\\'))=0;	//���������һ��\���ڵ�λ���޸�Ϊ\0

	CString strResult=szPath;
	return strResult;

}

