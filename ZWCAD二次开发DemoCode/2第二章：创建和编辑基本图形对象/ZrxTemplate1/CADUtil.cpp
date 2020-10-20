#include "stdafx.h"
#include "CADUtil.h"


CCADUtil::CCADUtil()
{
}


CCADUtil::~CCADUtil()
{
}

AcDbObjectIdArray CCADUtil::GetAllEntityIds()
{
	AcDbObjectIdArray entIds;	//����������ʵ�弯��

	//��ÿ��
	AcDbBlockTable *pBlkTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForRead);

	//���ģ�Ϳռ�Ŀ���¼
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();

	//����������,���η���ģ�Ϳռ��ÿһ��ʵ��
	AcDbBlockTableRecordIterator *it = NULL;
	pBlkTblRcd->newIterator(it);
	AcDbObjectId objId;
	for (it->start(); !it->done(); it->step())
	{
		Acad::ErrorStatus es = it->getEntityId(objId);
		if (es == Acad::eOk)
		{
			entIds.append(objId);
		}
	}
	delete it;
	pBlkTblRcd->close();
	return entIds;
}

AcDbObjectIdArray CCADUtil::GetAllEntityIdsByLayerName(const TCHAR * layerName)
{
	AcDbObjectIdArray entIds;	//����������ʵ�弯��
	bool bFilterLayer = false;	//�Ƿ���Ҫ����ͼ��
	AcDbObjectId layerId;

	if (layerName != NULL)
	{
		AcDbLayerTable *pLayerTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()->getLayerTable(pLayerTbl, AcDb::kForRead);
		if (!pLayerTbl->has(layerName))
		{
			pLayerTbl->close();
			return entIds;
			
		}
		pLayerTbl->getAt(layerName, layerId);
		pLayerTbl->close();

		bFilterLayer = true;
	}

	//��ÿ��
	AcDbBlockTable *pBlkTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForRead);

	//���ģ�Ϳռ�Ŀ���¼
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();

	//����������,���η���ģ�Ϳռ��ÿһ��ʵ��
	AcDbBlockTableRecordIterator *it = NULL;
	pBlkTblRcd->newIterator(it);
	AcDbEntity *pEnt = NULL;
	for (it->start(); !it->done(); it->step())
	{
		Acad::ErrorStatus es = it->getEntity(pEnt,AcDb::kForRead);
		if (es == Acad::eOk)
		{
			if (bFilterLayer)	//����ͼ��
			{
				if (pEnt->layerId() == layerId)
				{
					entIds.append(pEnt->objectId());
				}
			}
			else
			{
				entIds.append(pEnt->objectId());
			}
			pEnt->close();
		}
		else
		{
			acutPrintf(L"\nCADUtil::GetAllEntityIdsByLayer�д�ʵ��ʧ�ܣ�������룺%d ��", (int)es);
		}
	}
	delete it;
	pBlkTblRcd->close();
	return entIds;
}
