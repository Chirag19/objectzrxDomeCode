#include "stdafx.h"
#include "ArcUtil.h"


CArcUtil::CArcUtil()
{
}


CArcUtil::~CArcUtil()
{
}

AcDbObjectId CArcUtil::Add(const AcGePoint3d & ptCenter, const AcGeVector3d & vec, double radius, double startAngle, double endAngle)
{
	AcDbArc *pArc = new AcDbArc(ptCenter, vec, radius, startAngle, endAngle);
	return CDwgDatabaseUtil::PostToModelSpace(pArc);
}

AcDbObjectId CArcUtil::Add(const AcGePoint2d & ptCenter, double radius, double startAngle, double endAngle)
{
	AcGeVector3d vec(0, 0, 1);
	return Add(CConvertUtil::ToPoint3d(ptCenter), vec, radius, startAngle, endAngle);
}

AcDbObjectId CArcUtil::Add(const AcGePoint2d & ptStart, const AcGePoint2d & ptOnArc, const AcGePoint2d & ptEnd)
{
		//ʹ�ü������ȡԲ�ģ��뾶
		AcGeCircArc2d geArc(ptStart, ptOnArc, ptEnd);
		AcGePoint2d ptCenter = geArc.center();
		double radius = geArc.radius();

		//������ʼ����ֹ�Ƕ�
		AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
		AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
		double startAngle = vecStart.angle();
		double endAngle = vecEnd.angle();

		//����Բ��
		return Add(ptCenter, radius, startAngle, endAngle);
}

AcDbObjectId CArcUtil::AddSCE(const AcGePoint2d & ptStart, const AcGePoint2d & ptCenter, const AcGePoint2d & ptEnd)
{
	//����뾶
	double radius = ptCenter.distanceTo(ptStart);

	//�������յ�Ƕ�
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = vecEnd.angle();

	//����Բ��
	return Add(ptCenter, radius, startAngle, endAngle);
}

AcDbObjectId CArcUtil::Add(const AcGePoint2d & ptStart, const AcGePoint2d & ptCenter, double angle)
{
	//����뾶
	double radius = ptCenter.distanceTo(ptStart);
	//�������յ�Ƕ�
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = startAngle + angle;
	//����Բ��
	AcDbArc *pArc = new AcDbArc(CConvertUtil::ToPoint3d(ptCenter), radius, startAngle, endAngle);
	return CDwgDatabaseUtil::PostToModelSpace(pArc);
}
