#pragma once
class CStringUtil
{
public:
	CStringUtil();
	~CStringUtil();
	
	//�ַ����ָ�
	static void Split(const CString &text, const TCHAR *separator, std::vector<CString> &result, bool bAddEmptyItem=true);
	//�ַ���ƴ��
	static CString Jion(const std::vector<CString> &item, const TCHAR *separator);

	
	
};

