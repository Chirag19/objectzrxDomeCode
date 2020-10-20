#include "stdafx.h"
#include "DwgDatabaseUtil.h"


CDwgDatabaseUtil::CDwgDatabaseUtil()
{
}


CDwgDatabaseUtil::~CDwgDatabaseUtil()
{
}

AcDbObjectId CDwgDatabaseUtil::PostToModelSpace(AcDbEntity *pEnt)
{
	//��������������Ч��
	assert(pEnt);	//��Ч�� assert (pEnt!=NULL)

					//��ȡ��ǰͼ�����ݿ�Ŀ��
	AcDbBlockTable *pBlkTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForRead);

	//���ģ�Ϳռ��Ӧ�Ŀ���¼
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);
	pBlkTbl->close();

	//��ʵ����ӵ�ģ�Ϳռ�Ŀ���¼
	AcDbObjectId entId = AcDbObjectId::kNull;
	Acad::ErrorStatus es = pBlkTblRcd->appendAcDbEntity(entId, pEnt);
	if (es != Acad::eOk)
	{
		pBlkTblRcd->close();
		delete pEnt;	//���ʧ��ʱ��Ҫdelete
		pEnt = NULL;
		return AcDbObjectId::kNull;
	}
	//�ر�ģ�Ϳռ����¼��ʵ��
	pBlkTblRcd->close();
	pEnt->close();

	return entId;
}

AcDbObjectIdArray CDwgDatabaseUtil::GetAllEntityIds(const TCHAR * layerName)
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
		Acad::ErrorStatus es = it->getEntity(pEnt, AcDb::kForRead);
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
			acutPrintf(_T("\nCADUtil::GetAllEntityIdsByLayer�д�ʵ��ʧ�ܣ�������룺%d ��"), (int)es);
		}
	}
	delete it;
	pBlkTblRcd->close();
	return entIds;
}
