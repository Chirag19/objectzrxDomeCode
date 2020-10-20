#include "stdafx.h"
#include "SelectUtil.h"


CSelectUtil::CSelectUtil()
{
}


CSelectUtil::~CSelectUtil()
{
}

void CSelectUtil::GetEntityInRectangle(const AcGePoint2d & firstPoint, const AcGePoint2d & secondPoint, AcDbObjectIdArray & entIds)
{
	//1.������Ч�Լ��
	//�㲻�ܹ���һ��ֱ�߻��غ�
	assert(fabs(firstPoint.x - secondPoint.x) > 1.0E-7 || fabs(firstPoint.y - secondPoint.y) > 1.0E-7);
	
	//����ģ�Ϳռ�������������ʵ��
	AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds(NULL);
	for (int i = 0; i < allEntIds.length(); i++)
	{
		//���ñ��������ÿһ��ʵ��
		AcDbEntity *pEnt = NULL;
		if (acdbOpenObject(pEnt, allEntIds[i], AcDb::kForRead) == Acad::eOk)
		{
			AcDbExtents exent;
			pEnt->getGeomExtents(exent);

			//���ʵ������Χ��͸��������ཻ���������ʵ���콾��������
			AcGePoint2d extMinPoint = CConvertUtil::ToPoint2d(exent.minPoint());
			AcGePoint2d extMaxPoint = CConvertUtil::ToPoint2d(exent.maxPoint());

			if (CGeRectangleUtil::IntersectWithRectangle(extMinPoint, extMaxPoint, firstPoint, secondPoint))
			{
				entIds.append(pEnt->objectId());
			}
			pEnt->close();
		}
	}
}

bool CSelectUtil::PromptSelectEnts(const TCHAR * prompt, struct resbuf * rb, AcDbObjectIdArray & entIds)
{
	entIds.setLogicalLength(0);

	bool bRet = false;
	ads_name sset;
	acutPrintf(prompt);
	int rc = acedSSGet(NULL, NULL, NULL, rb, sset);

	if (rc == RTNORM)
	{
		long length = 0;
		acedSSLength(sset, &length);

		for (int i = 0; i < length; i++)
		{
			ads_name ename;
			acedSSName(sset, i, ename);

			AcDbObjectId entId;

			acdbGetObjectId(entId, ename);
			entIds.append(entId);
		}
		bRet = true;
	}
	acedSSFree(sset);
	return bRet;
}

bool CSelectUtil::PromptSelectEnts(const TCHAR * prompt, const std::vector<AcRxClass*>& classDescs, AcDbObjectIdArray & entIds)
{
	//��ʼ��
	entIds.setLogicalLength(0);

	//��ʾ�û�ѡ��ʵ��
	ads_name sset;
	int result = 0;
	acutPrintf(prompt);
	result = acedSSGet(NULL, NULL, NULL, NULL, sset);

	if (result != RTNORM)
	{
		return false;
	}

	//��ȡѡ�񼯵ĳ���
	long length = 0;
	acedSSLength(sset, &length);

	Acad::ErrorStatus es;
	AcDbEntity *pEnt = NULL;
	for (long i = 0; i < length; i++)
	{
		ads_name ename;
		acedSSName(sset, i, ename);

		AcDbObjectId curEntId;
		es = acdbGetObjectId(curEntId, ename);
		if (es != Acad::eOk)
		{
			continue;
		}

		//��ʵ��
		es = acdbOpenObject(pEnt, curEntId, AcDb::kForRead);
		if (es!=Acad::eOk)
		{
			continue;
		}

		//�жϵ�ǰʵ���Ƿ���ָ����ʵ������
		for (int j = 0; j < (int)classDescs.size(); j++)
		{
			if (pEnt->isKindOf(classDescs[j]))
			{
				entIds.append(pEnt->objectId());
				break;
			}

		}
		pEnt->close();	//�ر�ʵ��
	}
	acedSSFree(sset);	//�ͷ�ѡ��

	return (entIds.length() > 0);
}

bool CSelectUtil::PromptSelectEnts(const TCHAR *prompt, AcRxClass* &classDesc, AcDbObjectIdArray &entIds)
{
	std::vector<AcRxClass*> vecClassDec;
	vecClassDec.push_back(classDesc);

	return PromptSelectEnts(prompt, vecClassDec, entIds);
}

bool CSelectUtil::PromptSelectEntity(const TCHAR *prompt, const std::vector<AcRxClass*> &classDescs, AcDbEntity * &pEnt, AcGePoint3d &pickPoint, bool bOpenFoeWrite/*=true*/)
{
	ads_name ename;
RETRY:
	if (acedEntSel(prompt, ename, asDblArray(pickPoint)) != RTNORM)
	{
		pEnt = NULL;
		return false;
	}

	AcDbObjectId entId;
	acdbGetObjectId(entId, ename);

	//�ж�ѡ���ʵ���Ƿ���ָ�����͵�ʵ��
	Acad::ErrorStatus es;
	if (bOpenFoeWrite)
	{
		es = acdbOpenObject(pEnt, entId, AcDb::kForWrite);
	}
	else
	{
		es= acdbOpenObject(pEnt, entId, AcDb::kForRead);
	}

	assert(es == Acad::eOk);
	bool bRet = false;
	for (int i = 0; i < (int)classDescs.size(); i++)
	{
		if (pEnt->isKindOf(classDescs[i]))
		{
			bRet = true;
			break;
		}
	}

	if (bRet)
	{
		return true;
	}
	else
	{
		pEnt->close();
		acutPrintf(_T("\nѡ���ʵ�����Ͳ���Ҫ�����ٴ�ѡ��..."));
		goto RETRY;
	}
}

bool CSelectUtil::PromptSelectEntity(const TCHAR * prompt, AcRxClass *& classDesc, AcDbEntity * &pEnt, AcGePoint3d & pickPoint, bool bOpenFoeWrite)
{
	std::vector<AcRxClass*> vecClassDec;
	vecClassDec.push_back(classDesc);
	return PromptSelectEntity(prompt, vecClassDec, pEnt,pickPoint, bOpenFoeWrite);

}
