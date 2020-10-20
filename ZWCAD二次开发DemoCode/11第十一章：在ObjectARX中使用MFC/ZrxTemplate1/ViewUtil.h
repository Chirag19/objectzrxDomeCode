#pragma once
class CViewUtil
{
public:
	CViewUtil();
	~CViewUtil();
	
	//��ȡ��ǰ��ͼ��Ϣ
	static void GetCurrentView(AcDbViewTableRecord &view);
	//������ʾ��Χ�������С����������ű������޸ĵ�ǰ��ͼ
	static void Set(const AcGePoint3d &pMin, const AcGePoint3d &pMax, double scale);
	//����ͼ�ƶ������������ĵ�
	static void SetCenter(const AcGePoint3d &center);
	//������ͼ����ʾģ�Ϳռ������ʵ��
	static void ZoomExtent();
	//ZOOM E
	static void DwgZoomExtent(AcDbDatabase *pDb);


};

