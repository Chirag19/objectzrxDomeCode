#pragma once
class CGePointUtil
{
public:
	CGePointUtil();
	~CGePointUtil();

	//��������е�
	static AcGePoint3d GetMiddlePoint(const AcGePoint3d &pt1, const AcGePoint3d &pt2);
	//��������е�
	static AcGePoint2d GetMiddlePoint(const AcGePoint2d &pt1, const AcGePoint2d &pt2);
	//������Լ�������ȷ��һ�����λ��
	static AcGePoint3d PolarPoint(const AcGePoint3d &basePoint, double angle, double length);
	//������Լ�������ȷ��һ�����λ��
	static AcGePoint2d PolarPoint(const AcGePoint2d &basePoint, double angle, double length);
	//�������ֱ������������һ�����λ��
	static AcGePoint3d RelativePoint(const AcGePoint3d &pt, double x, double y);
};

