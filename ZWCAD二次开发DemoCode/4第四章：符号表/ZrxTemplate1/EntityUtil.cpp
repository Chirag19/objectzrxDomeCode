#include "stdafx.h"
#include "EntityUtil.h"


CEntityUtil::CEntityUtil()
{
}


CEntityUtil::~CEntityUtil()
{
}

Acad::ErrorStatus CEntityUtil::SetColor(AcDbObjectId entId, Adesk::UInt16 colorIndex)
{
	assert(colorIndex >= 0 && colorIndex <= 256);
	Acad::ErrorStatus eOk;
	AcDbEntity *pEntity;
	//��ͼ�����ݿ�Ķ���
	eOk = acdbOpenAcDbEntity(pEntity, entId, AcDb::kForWrite);
	if (eOk != Acad::eOk)
	{
		return eOk;
	}
	//�޸�ʵ����ɫ
	pEntity->setColorIndex(colorIndex);
	//����֮�󣬼�ʱ�ر�
	pEntity->close();
	return eOk;
}

void CEntityUtil::SetLayer(AcDbObjectId entId, CString strLayer)
{
	AcDbEntity *pEnt = NULL;
	if (acdbOpenObject(pEnt, entId, AcDb::kForWrite) == Acad::eOk)
	{
		pEnt->setLayer(strLayer);
		pEnt->close();
	}
}

void CEntityUtil::SetLineType(AcDbObjectId entId, CString strLineType)
{
	AcDbEntity *pEnt = NULL;
	if (acdbOpenObject(pEnt, entId, AcDb::kForWrite) == Acad::eOk)
	{
		pEnt->setLinetype(strLineType);
		pEnt->close();
	}
}

Acad::ErrorStatus CEntityUtil::Rotate(AcDbObjectId entId, const AcGePoint2d &ptBase, double rotation)
{
	AcGeMatrix3d xform;
	AcGeVector3d vec(0, 0, 1);
	xform.setToRotation(rotation, vec, CConvertUtil::ToPoint3d(ptBase));

	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	if (es == Acad::eOk)
	{
		es = pEnt->transformBy(xform);
		pEnt->close();
	}
	return es;
}

Acad::ErrorStatus CEntityUtil::Move(AcDbObjectId entId, const AcGePoint3d &ptBase, const AcGePoint3d &ptDest)
{
	//����ת������Ĳ���
	AcGeMatrix3d xform;
	AcGeVector3d vec(ptDest.x - ptBase.x, ptDest.y - ptBase.y, ptDest.z - ptBase.z);
	xform.setTranslation(vec);
	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	if (es == Acad::eOk)
	{
		es = pEnt->transformBy(xform);
		pEnt->close();
	}
	return es;

}

Acad::ErrorStatus CEntityUtil::Scale(AcDbObjectId entId, const AcGePoint3d &ptBase, double scaleFactor)
{
	//���ñ任����Ĳ���
	AcGeMatrix3d xform;
	xform.setToScaling(scaleFactor, ptBase);

	AcDbEntity *pEnt = NULL;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	if (es == Acad::eOk)
	{
		pEnt->transformBy(xform);
		pEnt->close();
	}
	return es;
}
