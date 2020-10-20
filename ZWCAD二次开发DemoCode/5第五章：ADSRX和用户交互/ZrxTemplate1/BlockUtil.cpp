#include "stdafx.h"
#include "BlockUtil.h"


CBlockUtil::CBlockUtil()
{
}


CBlockUtil::~CBlockUtil()
{
}

AcDbObjectId CBlockUtil::InsertBlockRef(AcDbObjectId blkDefId, const AcGePoint3d & insertPoint, double scale, double rotation)
{
	//����ͼ��Ĳ���㡢��ת�Ƕȡ�������
	AcDbBlockReference *pBlkRef = new AcDbBlockReference(insertPoint, blkDefId);
	pBlkRef->setRotation(rotation);
	SetScaleFactor(pBlkRef, scale);

	//���½���ͼ�����ʵ����뵽�½��Ŀ���¼�У���ȡ�ò���ͼ���ʵ��ID
	//���ڷ���ֵ
	return CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
}

void CBlockUtil::SetScaleFactor(AcDbBlockReference * pBlkRef, double scale)
{
	assert(pBlkRef);
	AcGeScale3d geScale(scale, scale, scale);
	pBlkRef->setScaleFactors(geScale);
}

AcDbObjectId CBlockUtil::GetBlkDefId(const TCHAR * blkDefName)
{
	AcDbBlockTable *pBlockTable = NULL;
	Acad::ErrorStatus es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);
	AcDbObjectId blkDefId;
	es = pBlockTable->getAt(blkDefName, blkDefId);
	if (es == Acad::eOk)
	{
		return blkDefId;
	}
	else
	{
		return AcDbObjectId::kNull;
	}
}

AcDbObjectId CBlockUtil::InsertBlockRefWithAttribute(const AcDbObjectId & blkDefId, const AcGePoint3d & insertPoint, double scale, double rotation)
{
	//��������ն���
	AcDbBlockReference *pBlkRef = new AcDbBlockReference(insertPoint, blkDefId);
	SetScaleFactor(pBlkRef, scale);
	pBlkRef->setRotation(rotation);

	//�ж�ָ���Ŀ���¼�Ƿ�������Զ���
	AcDbBlockTableRecord *pBlkDefRcd = NULL;
	if (acdbOpenObject(pBlkDefRcd, pBlkRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
	{
		if (pBlkDefRcd->hasAttributeDefinitions())
		{
			//��������¼�����������ڷ��ʿ鶨�������е�ʵ��
			AcDbBlockTableRecordIterator *pItr = NULL;
			pBlkDefRcd->newIterator(pItr);
			for (pItr->start(); !pItr->done(); pItr->step())
			{
				AcDbEntity *pEnt = NULL;
				if (pItr->getEntity(pEnt, AcDb::kForRead) == Acad::eOk)
				{
					//��������Զ��壬���������������
					AcDbAttributeDefinition *pAttDef = AcDbAttributeDefinition::cast(pEnt);
					if (pAttDef != NULL)
					{
						AppendAttributeToBlkRef(pBlkRef, pAttDef);
					}
					pEnt->close();
				}
			}
			delete pItr;
		}
		pBlkDefRcd->close();
	}
	//���������ӵ�ģ�Ϳռ�
	return CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
}

void CBlockUtil::AppendAttributeToBlkRef(AcDbBlockReference * pBlkRef, AcDbAttributeDefinition * pAttDef)
{
	//����һ���µ����Զ���
	AcDbAttribute *pAtt = new AcDbAttribute();
	//�����Զ��������Զ���Ķ�������
	pAtt->setPropertiesFrom(pBlkRef);
	pAtt->setLayer(pBlkRef->layerId());
	//�������Զ������������
	pAtt->setInvisible(pAttDef->isInvisible());
	pAtt->setPosition(pAttDef->position());
	pAtt->setHeight(pAttDef->height());
	pAtt->setWidthFactor(pAttDef->widthFactor());
	pAtt->setRotation(pAttDef->rotation());
	pAtt->setHorizontalMode(pAttDef->horizontalMode());
	pAtt->setVerticalMode(pAttDef->verticalMode());
	pAtt->setAlignmentPoint(pAttDef->alignmentPoint());
	pAtt->setTextStyle(pAttDef->textStyle());
	pAtt->setAttributeFromBlock(pBlkRef->blockTransform());

	//������Զ����Tag��Promat��TextString
	TCHAR  *pStr = pAttDef->tag();
	pAtt->setTag(pStr);
	acutDelString(pStr);
	pAtt->setFieldLength(pAttDef->fieldLength());
	pAtt->setTextString(pAttDef->textString());

	//������׷�����Զ���
	pBlkRef->appendAttribute(pAtt);
	pAtt->close();
}

bool CBlockUtil::SetBlockRefAttribute(AcDbBlockReference * pBlikRef, const TCHAR * tag, const TCHAR * val)
{
	AcDbBlockTableRecord *pBlkDefRcd = NULL;
	bool bRet = true;
	if (acdbOpenObject(pBlkDefRcd, pBlikRef->blockTableRecord(), AcDb::kForRead) == Acad::eOk)
	{
		//�鶨�����Ƿ�����˶�Ӧ������
		if (pBlkDefRcd->hasAttributeDefinitions())
		{
			AcDbBlockTableRecordIterator *pItr = NULL;
			pBlkDefRcd->newIterator(pItr);
			AcDbEntity *pEnt = NULL;
			for (pItr->start(); !pItr->done(); pItr->step())
			{
				pItr->getEntity(pEnt, AcDb::kForRead);
				AcDbAttributeDefinition *pAttDef = AcDbAttributeDefinition::cast(pEnt);
				if (pAttDef != NULL)
				{
					TCHAR *pszTag = pAttDef->tag();
					CString strTag = pszTag;
					acutDelString(pszTag);
					if (strTag.CompareNoCase(tag) == 0)
					{
						//����������������ԣ��ж��Ƿ�����˶�Ӧ������
						bool bFound = false;
						AcDbObjectIterator *attIt = pBlikRef->attributeIterator();
						for (attIt->start(); !attIt->done(); attIt->step())
						{
							AcDbAttribute *pAtt = NULL;
							Acad::ErrorStatus es = acdbOpenObject(pAtt, attIt->objectId(), AcDb::kForWrite);
							if (es == Acad::eOk)
							{
								pszTag = pAtt->tag();
								strTag = pszTag;
								acutDelString(pszTag);
								if (strTag.CompareNoCase(tag) == 0)
								{
									pAtt->setTextString(val);
									bFound = true;
								}
								pAtt->close();
							}
						}
						delete attIt;
						//���û���ҵ��������Ƶ����ԣ����½��������
						if (!bFound)
						{
							AppendAttributeToBlkRef(pBlikRef, pAttDef);
						}
					}
				}
				pEnt->close();

			}
			delete pItr;
		}
		else
		{
			bRet = false;
		}
		pBlkDefRcd->close();
	}
	return bRet;
}

bool CBlockUtil::GetAttributeValue(AcDbBlockReference * pBlkRef, const TCHAR * tag, CString & value)
{
	//��������¼�����Ա�����
	bool bFound = false;
	AcDbObjectIterator *pItr = pBlkRef->attributeIterator();
	if (pItr)
	{
		while (!pItr->done())
		{
			AcDbObjectId attId = pItr->objectId();
			AcDbAttribute *pAtt = NULL;
			if (pBlkRef->openAttribute(pAtt, attId, AcDb::kForRead) == Acad::eOk)
			{
				//����յ�����Tag��Զ���Ǵ�д��ĸ����˴���Ĳ�����Ҫ����ת��
				TCHAR *szTag = pAtt->tag();
				CString strTag = tag;
				strTag.MakeUpper();
				if (_tcscmp(strTag, szTag) == 0)
				{
					TCHAR *szValue = pAtt->textString();
					value = szValue;
					acutDelString(szValue);
					bFound = true;
				}
				acutDelString(szTag);
				pAtt->close();
			}
			pItr->step();
		}
		delete pItr;
		return bFound;
	}
	else
	{
		return false;
	}
}

void CBlockUtil::IntersectWith(AcDbBlockReference * pBlkRef, AcDbEntity * pEnt, AcGePoint3dArray & intPonts, bool bIntersectWithText, bool bProjectToXOY, bool bExtendEntArg)
{
	assert(pBlkRef);
	assert(pEnt);

	//��ȡ����ն�Ӧ�ı任����
	AcGeMatrix3d xForm = pBlkRef->blockTransform();

	AcDbObjectId blkTblId = pBlkRef->blockTableRecord();
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	if (acdbOpenObject(pBlkTblRcd, blkTblId, AcDb::kForRead) == Acad::eOk)
	{
		//����¼���������ʿ鶨���е�ÿ��ʵ��
		AcDbBlockTableRecordIterator *pIt = NULL;
		pBlkTblRcd->newIterator(pIt);
		for (pIt->start(); !pIt->done(); pIt->step())
		{
			AcDbEntity *pSubEnt = NULL;
			if (pIt->getEntity(pSubEnt, AcDb::kForRead) == Acad::eOk)
			{
				//������������󽻵㣬�жϵ�ǰʵ�����ͣ����������־�����ȥ
				if ((!bIntersectWithText) && (pSubEnt->isKindOf(AcDbText::desc()) || pSubEnt->isKindOf(AcDbMText::desc())))
				{
					pSubEnt->close();
					continue;
				}

				//����һ��ʵ����б任�������޸Ŀ鶨���е���ʵ��
				AcDbEntity *pEntCopy = NULL;
				if (pSubEnt->getTransformedCopy(xForm, pEntCopy) == Acad::eOk)
				{
					//�Ƿ��ӳ�����
					AcDb::Intersect inMode = bExtendEntArg ? AcDb::kExtendArg : AcDb::kOnBothOperands;
					if (bProjectToXOY)
					{
						pEntCopy->intersectWith(pEnt, inMode, AcGePlane::kXYPlane, intPonts);
					}
					else
					{
						pEntCopy->intersectWith(pEnt, inMode, intPonts);
					}
					delete pEntCopy;
				}
				pSubEnt->close();
			}
		}
		delete pIt;
		pBlkTblRcd->close();
	}
}
