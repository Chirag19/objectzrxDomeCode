#pragma once
class CTextUtil
{
public:
	CTextUtil();
	~CTextUtil();


	//�������֣�����������㡢�������ݡ�������ʽID�����ָ߶ȡ����ֵ���ת�Ƕȣ�
	static AcDbObjectId AddText(const AcGePoint3d &ptInsert, const TCHAR* text, AcDbObjectId style = AcDbObjectId::kNull, double height = 2.5, double rotation = 0);
	//�����������֣�����������㡢�����������ݡ�������ʽID�����ָ߶ȡ���ȣ�
	static AcDbObjectId AddMText(const AcGePoint3d &ptInsert, const TCHAR* text, AcDbObjectId style = AcDbObjectId::kNull, double height = 2.5, double width = 10);
};

