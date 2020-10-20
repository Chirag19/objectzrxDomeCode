#include "stdafx.h"
#include "RegionUtil.h"


CRegionUtil::CRegionUtil()
{
}


CRegionUtil::~CRegionUtil()
{
}

AcDbObjectIdArray CRegionUtil::Add(const AcDbObjectIdArray & curveIds)
{
	AcDbObjectIdArray regionIds;	//���ɵ������ID����
	AcDbVoidPtrArray curves;		//ָ����Ϊ����߽�����ߵ�ָ������
	AcDbVoidPtrArray regions;		//ָ�򴴽����������ָ�������
	AcDbEntity *pEnt = NULL;		//��ʱָ�룬�����رձ߽�����
	AcDbRegion *pRegion = NULL;		//��ʱ����������������ӵ�ģ�Ϳռ�

									//��curveTds��ʼ��curves
	for (int i = 0; i < curveIds.length(); i++)
	{
		acdbOpenAcDbEntity(pEnt, curveIds.at(i), AcDb::kForRead);
		if (pEnt->isKindOf(AcDbCurve::desc()))
		{
			curves.append(static_cast<void*>(pEnt));
		}
	}
	Acad::ErrorStatus es = AcDbRegion::createFromCurves(curves, regions);
	if (es == Acad::eOk)
	{
		//�����ɵ�������ӵ�ģ�Ϳռ�
		for (int i = 0; i < regions.length(); i++)
		{
			pRegion = static_cast<AcDbRegion*>(regions[i]);
			pRegion->setDatabaseDefaults();
			AcDbObjectId regionId;
			regionId = CDwgDatabaseUtil::PostToModelSpace(pRegion);
			regionIds.append(regionId);
		}
	}
	else
	{
		//����������ɹ���ҲҪɾ���Ѿ����ɵ�����
		for (int i = 0; i < regions.length(); i++)
		{
			delete (AcRxObject*)regions[i];
		}

	}

	//�ر���Ϊ�߽����
	for (int i = 0; i < curves.length(); i++)
	{
		pEnt = static_cast<AcDbCurve*>(curves[i]);
		pEnt->close();
	}
	return regionIds;
}
