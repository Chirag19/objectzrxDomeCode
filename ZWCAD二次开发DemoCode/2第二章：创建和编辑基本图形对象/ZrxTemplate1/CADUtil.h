#pragma once
class CCADUtil
{
public:
	CCADUtil();
	~CCADUtil();

	//��ȡ��ǰģ�Ϳռ�����ʵ�����ID
	static AcDbObjectIdArray GetAllEntityIds();
	//��ȡ��ǰģ�Ϳռ�ָ��ͼ��������ʵ�����ID
	static AcDbObjectIdArray GetAllEntityIdsByLayerName(const TCHAR* layerName = NULL);
	

};

