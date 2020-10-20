#pragma once
class CArcUtil
{
public:
	CArcUtil();
	~CArcUtil();

	//����Բ����������Բ�ġ�ƽ�淨�������뾶����ʼ�Ƕȡ���ֹ�Ƕȣ�
	static AcDbObjectId Add(const AcGePoint3d &ptCenter, const AcGeVector3d &vec, double radius, double startAngle, double endAngle);
	//��XOYƽ�洴��Բ����������Բ�ġ��뾶����ʼ�Ƕȡ���ֹ�Ƕȣ�
	static AcDbObjectId Add(const AcGePoint2d &ptCenter, double radius, double startAngle, double endAngle);
	//����Բ������������㡢�յ㡢����һ�㣩
	static AcDbObjectId Add(const AcGePoint2d &ptStart, const AcGePoint2d &ptOnArc, const AcGePoint2d &ptEnd);
	//����Բ������������㡢�յ㡢Բ�ģ�
	static AcDbObjectId AddSCE(const AcGePoint2d &ptStart, const AcGePoint2d &ptCenter, const AcGePoint2d &ptEnd);
	//����Բ������������㡢Բ�ġ�Բ���Ƕȣ�
	static AcDbObjectId Add(const AcGePoint2d &ptStart, const AcGePoint2d &ptCenter, double angle);
};

