#pragma once
class CTextFileUtil
{
public:
	CTextFileUtil();
	~CTextFileUtil();

	//����(����)
	static void Save(const TCHAR* fileName, const std::vector<CString> &lines);
	//���ص������У����У�
	static void Load(const TCHAR *fileName, std::vector<CString> &lines);



};

