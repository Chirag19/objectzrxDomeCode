#pragma once
class GeoMetryUtil
{
public:
	GeoMetryUtil();
	~GeoMetryUtil();
	//��������е�
	static AcGePoint3d GetMiddlePoint(const AcGePoint3d &pt1, const AcGePoint3d &pt2);
	//��ά��ת��Ϊ��ά��
	static AcGePoint3d ToPoint3d(const AcGePoint2d &point2d, double z = 0);
	//PI
	static double PI();
	//�Ƕ�ת����
	static double AngleToRadian(double angle);
	//����ת�Ƕ�
	static double RadianToAngle(double radian);
	//������Լ�������ȷ��һ�����λ��
	static AcGePoint3d PolarPoint(const AcGePoint3d &basePoint ,double angle, double length);
	//�������ֱ������������һ�����λ��
	static AcGePoint3d RelativePoint(const AcGePoint3d &pt, double x, double y);



};

