#pragma once
class CLayerUtil
{
public:
	CLayerUtil();
	~CLayerUtil();
	//���ͼ���¼
	static void Add(const TCHAR* layerName, int colorIndex=7);
	//����ָ��ͼ�����ƻ�ȡָ��ͼ��ID
	static AcDbObjectId GetLayerId(const TCHAR* layerName);
	//�޸�ͼ����ɫ
	static bool SetColor(const TCHAR *layerName, int colorIndex);
	//��ȡ��ǰͼ��������ͼ���ID����
	static void GetLayerList(AcDbObjectIdArray &layers);

};

