#pragma once
class CTextStyleUtil
{
public:
	CTextStyleUtil();
	~CTextStyleUtil();

	//���������ʽ��¼
	static AcDbObjectId Add(const TCHAR *name, const TCHAR* fontFileName, const TCHAR *bigFontFileName);
	//��ȡָ�����Ƶ�������ʽID
	static AcDbObjectId GetAt(const TCHAR *name);
	//��ȡ��ǰͼ�������е�������ʽ���Ƽ���
	static void GetAll(std::vector<CString> &textStyles);


};

