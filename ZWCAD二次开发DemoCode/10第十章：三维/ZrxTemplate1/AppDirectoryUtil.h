#pragma once
class CAppDirectoryUtil
{
public:
	CAppDirectoryUtil();
	~CAppDirectoryUtil();

	//���ڻ�ȡ�������е�ARX�ļ����ڵ��ļ���
	static CString GetCurrentDirctory(HMODULE hInstance= _hdllInstance);
	//���ڻ�ȡ�������е�ARX�ļ�����Ŀ¼����һ���ļ���
	static CString GetParentDirectory(HMODULE hInstance= _hdllInstance);
};