#pragma once
class CDwgDatabaseUtil
{
public:
	CDwgDatabaseUtil();
	~CDwgDatabaseUtil();

	//���ʵ�嵽ģ�Ϳռ�
	static AcDbObjectId PostToModelSpace(AcDbEntity *pEnt);
	//��ȡ��ǰģ�Ϳռ�ָ��ͼ��������ʵ�����ID,����ΪNULLʱ��ȡ���ж���ID
	static AcDbObjectIdArray GetAllEntityIds(const TCHAR* layerName = NULL);
};

