#include "stdafx.h"
#include "LineUtil.h"


CLineUtil::CLineUtil()
{
}


CLineUtil::~CLineUtil()
{
}

AcDbObjectId CLineUtil::Add(const AcGePoint3d & startPoint, const AcGePoint3d & endPoint)
{
	//�ڶ�������AcDbLine����
	AcDbLine *pLine = new AcDbLine(startPoint, endPoint);
	return CDwgDatabaseUtil::PostToModelSpace(pLine);
}
