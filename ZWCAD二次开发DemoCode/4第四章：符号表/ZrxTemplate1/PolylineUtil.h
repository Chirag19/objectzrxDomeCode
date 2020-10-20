#pragma once
class CPolylineUtil
{
public:
	CPolylineUtil();
	~CPolylineUtil();

	//��������ߣ���������ߣ����������㼯����ȣ�
	static AcDbObjectId Add(const AcGePoint2dArray &points, double width = 0);
	//��������ߣ�һ��ֱ�ߣ�(��������ʼ�㡢��ʼ�㡢�߿�)
	static AcDbObjectId Add(const AcGePoint2d &ptStart, const AcGePoint2d &ptEnd, double width);
	//������ά����ߣ��������㼯��
	static AcDbObjectId Add3dPolyline(const AcGePoint3dArray &points);
	//����������Σ����������ġ����������Բ�뾶����ת�Ƕȣ�����ֵ�����߿����ɶ���߹�����
	static AcDbObjectId AddPolygon(const AcGePoint2d &ptCenter, int number, double radius, double rotation, double width);
	//�������Σ������������ǵ㡢�߿����ɶ���߹�����
	static AcDbObjectId AddPolyRectangle(const AcGePoint2d &pt1, const AcGePoint2d &pt2, double width);
	//����Բ��������Բ�ġ��뾶���߿����ɶ���߹�����
	static AcDbObjectId AddPolyCircle(const AcGePoint2d &ptCenter, double radius, double width);
	//����Բ����������Բ�ġ��뾶����ʼ�Ƕȡ���ֹ�Ƕȡ��߿����ɶ���߹�����
	static AcDbObjectId AddPolyArc(const AcGePoint2d &ptCenter, double radius, double angleStart, double angleEnd, double width);
};

