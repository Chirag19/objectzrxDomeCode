#pragma once
class CDwgDatabaseUtil
{
public:
	CDwgDatabaseUtil();
	~CDwgDatabaseUtil();

	//���ʵ�嵽ģ�Ϳռ�
	static AcDbObjectId PostToModelSpace(AcDbEntity *pEnt, AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());
	//��ȡָ��ģ�Ϳռ�ָ��ͼ��������ʵ�����ID,����ΪNULLʱ��ȡ���ж���ID
	static AcDbObjectIdArray GetAllEntityIds(const TCHAR* layerName = NULL, AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());
	//��ȡͼ�����ݿ�ģ�Ϳռ�����·�Χ
	static AcDbExtents GetModelSpaceExtent(AcDbDatabase *pDb);
};

