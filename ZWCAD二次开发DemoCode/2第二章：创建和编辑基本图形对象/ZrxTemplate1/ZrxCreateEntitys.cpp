#include "stdafx.h"
#include "ZrxCreateEntitys.h"


ZrxCreateEntitys::ZrxCreateEntitys()
{
}


ZrxCreateEntitys::~ZrxCreateEntitys()
{
}

AcDbObjectId ZrxCreateEntitys::PostToModelSpace(AcDbEntity * pEnt)
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
	AcDbObjectId entId=AcDbObjectId::kNull;
	Acad::ErrorStatus es = pBlkTblRcd->appendZcDbEntity(entId, pEnt);
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

AcDbObjectId ZrxCreateEntitys::CreateLine(AcGePoint3d ptStart, AcGePoint3d ptEnd)
{
	
	//�ڶ�������AcDbLine����
	AcDbLine *pLine = new AcDbLine(ptStart, ptEnd);
	return PostToModelSpace(pLine);
}

AcDbObjectId ZrxCreateEntitys::CreateCircle(const AcGePoint3d & centerPoint, double radius)
{
	AcGeVector3d normal(0, 0, 1);
	AcDbCircle *pCircle = new AcDbCircle(centerPoint, normal, radius);
	return PostToModelSpace(pCircle);
}

AcDbObjectId ZrxCreateEntitys::CreateCircle(const AcGePoint3d &pt1, const AcGePoint3d &pt2)
{
	AcGeVector3d normal(0, 0, 1);
	//����Բ�ĺͰ뾶
	AcGePoint3d center = GeoMetryUtil::GetMiddlePoint(pt1, pt2);
	double radius = center.distanceTo(pt1);
	//����Բ
	AcDbCircle *pCircle = new AcDbCircle(center, normal, radius);
	return PostToModelSpace(pCircle);
}

AcDbObjectId ZrxCreateEntitys::CreateCircle(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &pt3)
{
	//ʹ����ѧ����
	double xysm = 0, xyse = 0, xy = 0;
	AcGePoint3d ptCenter;
	double radius = 0;

	xy = pow(pt1.x, 2) + pow(pt1.y, 2);
	xyse = xy - pow(pt3.x, 2) - pow(pt3.y, 2);
	xysm = xy - pow(pt2.x, 2) - pow(pt2.y, 2);
	xy = (pt1.x - pt2.x)*(pt1.y - pt3.y) - (pt1.x - pt3.x)*(pt1.y - pt2.y);

	//�жϲ�����Ч��
	if (fabs(xy) < 0.000001)
	{
		AfxMessageBox(L"������Ĳ����޷�����Բ�Σ�\n");
		return AcDbObjectId::kNull;
	}

	//��ȡԲ�ĺͰ뾶
	ptCenter.x = (xysm*(pt1.y - pt3.y) - xyse*(pt1.y - pt2.y)) / (2 * xy);
	ptCenter.y = (xyse*(pt1.x - pt2.x) - xysm*(pt1.x - pt3.x)) / (2 * xy);
	ptCenter.z = 0;
	radius = sqrt((pt1.x - ptCenter.x)*(pt1.x - ptCenter.x) + (pt1.y - ptCenter.y)*(pt1.y - ptCenter.y));
	if (radius < 0.000001)
	{
		AfxMessageBox(L"�뾶��С��\n");
		return AcDbObjectId::kNull;
	}
	//����Բ
	AcGeVector3d normal(0, 0, 1);
	AcDbCircle *pCricle = new AcDbCircle(ptCenter, normal, radius);
	return PostToModelSpace(pCricle);
}

AcDbObjectId ZrxCreateEntitys::CreateCircle(const AcGePoint2d & pt1, const AcGePoint2d & pt2, const AcGePoint2d & pt3)
{
	AcGeCircArc2d geArc(pt1, pt2, pt3);
	AcGePoint3d ptCenter(geArc.center().x, geArc.center().y, 0);
	AcGeVector3d normal(0, 0, 1);
	AcDbCircle *pCircle = new AcDbCircle(ptCenter, normal, geArc.radius());

	return PostToModelSpace(pCircle);
}

AcDbObjectId ZrxCreateEntitys::CreateArc(const AcGePoint3d & ptCenter, const AcGeVector3d & vec, double radius, double startAngle, double endAngle)
{
	AcDbArc *pArc = new AcDbArc(ptCenter, vec, radius, startAngle, endAngle);
	return PostToModelSpace(pArc);
}

AcDbObjectId ZrxCreateEntitys::CreateArc(const AcGePoint2d & ptCenter, double radius, double startAngle, double endAngle)
{
	AcGeVector3d vec(0, 0, 1);
	AcDbArc *pArc = new AcDbArc(GeoMetryUtil::ToPoint3d(ptCenter), vec, radius, startAngle, endAngle);
	return PostToModelSpace(pArc);
}

AcDbObjectId ZrxCreateEntitys::CreateArc(const AcGePoint2d & ptStart, const AcGePoint2d& ptCenter_or_ptOnArc, const AcGePoint2d & ptEnd, BOOL flay)
{
	if (flay)
	{
		//����뾶
		double radius = ptCenter_or_ptOnArc.distanceTo(ptStart);

		//�������յ�Ƕ�
		AcGeVector2d vecStart(ptStart.x - ptCenter_or_ptOnArc.x, ptStart.y - ptCenter_or_ptOnArc.y);
		AcGeVector2d vecEnd(ptEnd.x - ptCenter_or_ptOnArc.x, ptEnd.y - ptCenter_or_ptOnArc.y);
		double startAngle = vecStart.angle();
		double endAngle = vecEnd.angle();
		return CreateArc(ptCenter_or_ptOnArc, radius, startAngle, endAngle);
	}
	else
	{
		//ʹ�ü������ȡԲ�ģ��뾶
		AcGeCircArc2d geArc(ptStart, ptCenter_or_ptOnArc, ptEnd);
		AcGePoint2d ptCenter = geArc.center();
		double radius = geArc.radius();

		//������ʼ����ֹ�Ƕ�
		AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
		AcGeVector2d vecEnd(ptEnd.x - ptCenter.x, ptEnd.y - ptCenter.y);
		double startAngle = vecStart.angle();
		double endAngle = vecEnd.angle();
		return CreateArc(ptCenter, radius, startAngle, endAngle);
	}
}

AcDbObjectId ZrxCreateEntitys::CreateArc(const AcGePoint2d & ptStart, const AcGePoint2d  &ptCenter, double angle)
{
	//����뾶
	double radius = ptCenter.distanceTo(ptStart);
	//�������յ�Ƕ�
	AcGeVector2d vecStart(ptStart.x - ptCenter.x, ptStart.y - ptCenter.y);
	double startAngle = vecStart.angle();
	double endAngle = startAngle + angle;
	//����Բ��
	AcDbArc *pArc = new AcDbArc(GeoMetryUtil::ToPoint3d(ptCenter), radius, startAngle, endAngle);
	return PostToModelSpace(pArc);
}

AcDbObjectId ZrxCreateEntitys::CreatePolyLine(const AcGePoint2dArray & points, double width)
{
	int numVertices = points.length();
	AcDbPolyline *pPoly = new AcDbPolyline(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		pPoly->addVertexAt(i, points.at(i), 0, width, width);
	}
	return PostToModelSpace(pPoly);
}

AcDbObjectId ZrxCreateEntitys::CreatePolyOneLine(const AcGePoint2d & ptStart, const AcGePoint2d & ptEnd, double width)
{
	AcGePoint2dArray points;
	points.append(ptStart);
	points.append(ptEnd);
	return  CreatePolyLine(points, width);
}

AcDbObjectId ZrxCreateEntitys::Create3dPolyLine(const AcGePoint3dArray & points)
{
	AcGePoint3dArray verts = points;
	AcDb3dPolyline *pPoly3d = new AcDb3dPolyline(AcDb::k3dSimplePoly, verts);
	return PostToModelSpace(pPoly3d);
}

AcDbObjectId ZrxCreateEntitys::CreatePolygon(const AcGePoint2d & ptCenter, int number, double radius ,double rotation, double width)
{
	double angle = 2 * GeoMetryUtil::PI() / (double)number;
	AcGePoint2dArray points;
	for (int i = 0; i < number; i++)
	{
		AcGePoint2d pt;
		pt.x = ptCenter.x + radius*cos(i*angle);
		pt.y = ptCenter.y + radius*sin(i*angle);
		points.append(pt);
	}
	AcDbObjectId polyId = CreatePolyLine(points, width);

	//����ر�
	AcDbEntity *pEnt = NULL;
	if (acdbOpenAcDbEntity(pEnt, polyId, AcDb::kForWrite) == Acad::eOk)
	{
		AcDbPolyline *pPoly = AcDbPolyline::cast(pEnt);
		if (pPoly != NULL)
		{
			pPoly->setClosed(Adesk::kTrue);
		}
		pEnt->close();
	}
	ZrxEditObject::Rotate(polyId, ptCenter, rotation);
	return polyId;
}

AcDbObjectId ZrxCreateEntitys::CreatePolyRectangle(const AcGePoint2d & pt1, const AcGePoint2d & pt2, double width)
{
	//��ȡ�����ǵ������ֵ
	double x1 = pt1.x, x2 = pt2.x;
	double y1 = pt1.y, y2 = pt2.y;

	//������εĽǵ�
	AcGePoint2d ptLeftBottom(min(x1, x2), min(y1, y2));
	AcGePoint2d ptRightBottm(max(x1, x2), min(y1, y2));
	AcGePoint2d ptRightTop(max(x1, x2), max(y1, y2));
	AcGePoint2d ptLeftTop(min(x1, x2), max(y1, y2));

	//������Ӧ�Ķ����
	AcDbPolyline *pPoly = new AcDbPolyline(4);
	pPoly->addVertexAt(0, ptLeftBottom, 0, width, width);
	pPoly->addVertexAt(1, ptRightBottm, 0, width, width);
	pPoly->addVertexAt(2, ptRightTop, 0, width, width);
	pPoly->addVertexAt(3, ptLeftTop, 0, width, width);
	pPoly->setClosed(Adesk::kTrue);

	//���������ӵ�ģ�Ϳռ�
	return PostToModelSpace(pPoly);
}

AcDbObjectId ZrxCreateEntitys::CreatePolyCircle(const AcGePoint2d & ptCenter, double radius, double width)
{
	//���㶥���λ��
	AcGePoint2d pt1, pt2, pt3;
	pt1.x = ptCenter.x + radius;
	pt1.y = ptCenter.y;
	pt2.x = ptCenter.x - radius;
	pt2.y = ptCenter.y;
	pt3.x = ptCenter.x + radius;
	pt3.y = ptCenter.y;

	//���������
	AcDbPolyline *pPoly = new AcDbPolyline(3);
	pPoly->addVertexAt(0, pt1, 1, width, width);
	pPoly->addVertexAt(1, pt2, 1, width, width);
	pPoly->addVertexAt(2, pt3, 1, width, width);
	pPoly->setClosed(Adesk::kTrue);

	//���պ϶������ӵ�ģ�Ϳռ�
	return PostToModelSpace(pPoly);
}

AcDbObjectId ZrxCreateEntitys::CreatePolyArc(const AcGePoint2d &ptCenter, double radius, double angleStart, double angleEnd, double width)
{
	//���㶥���λ��
	AcGePoint2d pt1, pt2;
	pt1.x = ptCenter.x + radius*cos(angleStart);
	pt1.y = ptCenter.y + radius*sin(angleStart);
	pt2.x = ptCenter.x + radius*cos(angleEnd);
	pt2.y = ptCenter.y + radius*sin(angleEnd);

	//���������
	AcDbPolyline *pPoly = new AcDbPolyline(3);
	pPoly->addVertexAt(0, pt1, tan((angleEnd - angleStart) / 4), width, width);
	pPoly->addVertexAt(1, pt2, 0, width, width);

	//���������ӵ�ģ�Ϳռ�
	return PostToModelSpace(pPoly);
	
}

AcDbObjectId ZrxCreateEntitys::CreateEillpse(const AcGePoint3d &ptCenter, const AcGeVector3d &vecNormal, const AcGeVector3d &majorAxis, double ratio)
{
	AcDbEllipse *pEllipse = new AcDbEllipse(ptCenter, vecNormal, majorAxis, ratio);
	return PostToModelSpace(pEllipse);
}

AcDbObjectId ZrxCreateEntitys::CreateEillpse(const AcGePoint2d &pt1, const AcGePoint2d &pt2)
{
	//������Բ�����ĵ�
	AcGePoint3d ptCenter;
	ptCenter = GeoMetryUtil::GetMiddlePoint(GeoMetryUtil::ToPoint3d(pt1), GeoMetryUtil::ToPoint3d(pt2));
	AcGeVector3d vecNormal(0, 0, 1);
	AcGeVector3d majorAxis(fabs(pt1.x - pt2.x) / 2, 0, 0);
	double ratio = fabs((pt1.y - pt2.y) / (pt1.x - pt2.x));
	return CreateEillpse(ptCenter, vecNormal, majorAxis, ratio);
}

AcDbObjectId ZrxCreateEntitys::CreateSpline(const AcGePoint3dArray & points, int order /* = 4 */, double fitTolerance /* =0.0 */)
{
	assert(order >= 2 && order <= 26);
	AcDbSpline *pSpline = new AcDbSpline(points, order, fitTolerance);
	return PostToModelSpace(pSpline);
}

AcDbObjectId ZrxCreateEntitys::CreateSpline(const AcGePoint3dArray & points, const AcGeVector3d & startTangent, const AcGeVector3d & endTangent, int order /* = 4 */, double fitTolerance /* = 0.0 */)
{
	assert(order >= 2 && order <= 26);
	AcDbSpline *pSpline = new AcDbSpline(points, startTangent, endTangent, order, fitTolerance);
	return PostToModelSpace(pSpline);
}

AcDbObjectIdArray ZrxCreateEntitys::CreateRegion(const AcDbObjectIdArray & curveIds)
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
			regionId = PostToModelSpace(pRegion);
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

AcDbObjectId ZrxCreateEntitys::CreateText(const AcGePoint3d & ptInsert, const TCHAR* text, AcDbObjectId style, double height, double rotation)
{
	AcDbText *pText = new AcDbText(ptInsert, text, style, height , rotation);
	return PostToModelSpace(pText);
}

AcDbObjectId ZrxCreateEntitys::CreateMText(const AcGePoint3d & ptInsert, const TCHAR * text, AcDbObjectId style, double height, double width)
{
	AcDbMText *pMText = new AcDbMText();

	//���ö������ֵ�����
	pMText->setTextStyle(style);
	pMText->setContents(text);
	pMText->setLocation(ptInsert);
	pMText->setTextHeight(height);
	pMText->setWidth(width);
	pMText->setAttachment(AcDbMText::kBottomLeft);

	return PostToModelSpace(pMText);
}

AcDbObjectId ZrxCreateEntitys::CreateHatch(const AcDbObjectIdArray & loopIds, const TCHAR * patName, double patternScale)
{
	Acad::ErrorStatus es;
	AcDbHatch *pHatch = new AcDbHatch();

	//�������ƽ��
	AcGeVector3d normal(0, 0, 1);
	pHatch->setNormal(normal);
	pHatch->setElevation(0);

	//���ù�����
	pHatch->setAssociative(true);

	//�������ͼ��
	pHatch->setPattern(AcDbHatch::kPreDefined, patName);

	//������߽�
	es = pHatch->appendLoop(AcDbHatch::kExternal, loopIds);

	//��ʾ������
	es = pHatch->evaluateHatch();

	//��ӵ�ģ�Ϳռ�
	AcDbObjectId hatchId = PostToModelSpace(pHatch);

	//����ǹ����Ե���䣬��������߽�󶨣�ʹ���ܻ�ñ߽�����޸�֪ͨ
	if (acdbOpenObject(pHatch, hatchId, AcDb::kForWrite) == Acad::eOk)
	{
		AcDbObjectIdArray assocEntIds;
		pHatch->getAssocObjIds(assocEntIds);
		for (int i = 0; i < assocEntIds.length(); i++)
		{
			AcDbEntity *pEnt = NULL;
			if (acdbOpenObject(pEnt, assocEntIds[i], AcDb::kForWrite) == Acad::eOk)
			{
				//���һ�����÷�Ӧ��
				pEnt->addPersistentReactor(hatchId);
				pEnt->close();
			}
		}
		pHatch->close();
	}
	return hatchId;
}

AcDbObjectId ZrxCreateEntitys::CreateDimAligned(const AcGePoint3d & pt1, const AcGePoint3d & pt2, const AcGePoint3d & ptLine, const TCHAR * dimText, AcDbObjectId dimStyle)
{
	AcDbAlignedDimension *pDim = new AcDbAlignedDimension(pt1, pt2, ptLine, dimText, dimStyle);
	return PostToModelSpace(pDim);
}

AcDbObjectId ZrxCreateEntitys::CreateDimAligned(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine, const AcGeVector3d &vecOffset/*=AcGeVector3d::kIdentity*/, const TCHAR* dimText /*= NULL*/, AcDbObjectId dimStyle /*= AcDbObjectId::kNull*/)
{
	AcDbAlignedDimension *pDim = new AcDbAlignedDimension(pt1, pt2, ptLine, dimText, dimStyle);
	AcDbObjectId dimensionId;
	dimensionId = PostToModelSpace(pDim);

	//���Ѿ������˵��ע�������ֵ�λ�ý����޸�
	AcDbAlignedDimension *pDimension = NULL;
	if (acdbOpenObject(pDimension, dimensionId, AcDb::kForWrite) == Acad::eOk)
	{
		//�ƶ�����λ��֮ǰ����Ҫָ���ߴ��ߵı仯���������ָ��Ϊ���ߴ��߲����������ֺͳߴ���֮��Ӽ�ͷ��
		pDimension->setDimtmove(1);
		//����ƫ�����������ֲ�����λ��
		AcGePoint3d pText = pDimension->textPosition();
		pText = pText + vecOffset;
		pDimension->setTextPosition(pText);

		pDimension->close();
	}
	return dimensionId;
}

AcDbObjectId ZrxCreateEntitys::CreateDimRotated(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine, double rotation, const TCHAR* dimText /*= NULL*/, AcDbObjectId dimStyle /*= AcDbObjectId::kNull*/)
{
	AcDbRotatedDimension *pDim = new AcDbRotatedDimension(rotation, pt1, pt2, ptLine, dimText, dimStyle);
	return PostToModelSpace(pDim);
}

AcDbObjectId ZrxCreateEntitys::CreateDimRadial(const AcGePoint3d & ptCenter, const AcGePoint3d & ptChord, double leaderLength, const TCHAR * dimText, AcDbObjectId dimStyle)
{
	AcDbRadialDimension *pDim = new AcDbRadialDimension(ptCenter, ptChord, leaderLength, dimText, dimStyle);
	return PostToModelSpace(pDim);
}

AcDbObjectId ZrxCreateEntitys::CreateDimRadial(const AcGePoint3d & ptCenter, double radius, double angle, double leaderLength)
{
	AcGePoint3d ptChord = GeoMetryUtil::PolarPoint(ptCenter, angle, radius);
	return CreateDimRadial(ptCenter, ptChord, leaderLength);
}

AcDbObjectId ZrxCreateEntitys::CreateDimDiameteric(const AcGePoint3d & ptChord1, const AcGePoint3d & ptChord2, double leaderLength, const TCHAR * dimText, AcDbObjectId dimStyle)
{
	AcDbDiametricDimension *pDim = new AcDbDiametricDimension(ptChord1, ptChord2, leaderLength, dimText, dimStyle);
	return PostToModelSpace(pDim);
}

AcDbObjectId ZrxCreateEntitys::CreateDimDiameteric(const AcGePoint3d & ptCenter, double radius, double angle, double leaderLength)
{
	//�����עͨ����λ��
	AcGePoint3d ptChord1, ptChord2;
	ptChord1 = GeoMetryUtil::PolarPoint(ptCenter, angle, radius);
	ptChord2 = GeoMetryUtil::PolarPoint(ptCenter, angle + GeoMetryUtil::PI(), radius);
	return CreateDimDiameteric(ptChord1, ptChord2, leaderLength);
}

AcDbObjectId ZrxCreateEntitys::CreateDim2LineAngular(const AcGePoint3d & ptStart1, const AcGePoint3d & ptEnd1, const AcGePoint3d & ptStart2, const AcGePoint3d & ptEnd2, const AcGePoint3d & ptArc, const TCHAR * dimText, AcDbObjectId dimStyle)
{
	AcDb2LineAngularDimension *pDim = new AcDb2LineAngularDimension(ptStart1, ptEnd1, ptStart2, ptEnd2, ptArc, dimText, dimStyle);
	return PostToModelSpace(pDim);
}

AcDbObjectId ZrxCreateEntitys::CreateDim3PtAngular(const AcGePoint3d &ptCenter, const AcGePoint3d &ptEnd1, const AcGePoint3d &ptEnd2, const AcGePoint3d &ptArc, const TCHAR* dimText /*= NULL*/, AcDbObjectId dimStyle /*= AcDbObjectId::kNull*/)
{
	AcDb3PointAngularDimension *pDim = new AcDb3PointAngularDimension(ptCenter, ptEnd1, ptEnd2, ptArc, dimText, dimStyle);
	return PostToModelSpace(pDim);
}

AcDbObjectId ZrxCreateEntitys::CreateDimOrdinate(Adesk::Boolean xAxis, const AcGePoint3d & ptStart, const AcGePoint3d & ptEnd, const TCHAR* dimText, AcDbObjectId dimStyle)
{
	AcDbOrdinateDimension *pDim = new AcDbOrdinateDimension(xAxis, ptStart, ptEnd, dimText, dimStyle);
	return PostToModelSpace(pDim);
}

AcDbObjectIdArray ZrxCreateEntitys::CreateDimOrdinate(const AcGePoint3d & ptDef, const AcGePoint3d & ptTextX, const AcGePoint3d & ptTextY)
{
	AcDbObjectId dimId;
	AcDbObjectIdArray dimIds;

	dimId = CreateDimOrdinate(Adesk::kTrue, ptDef, ptTextX);
	dimIds.append(dimId);
	dimId = CreateDimOrdinate(Adesk::kFalse, ptDef, ptTextY);
	dimIds.append(dimId);
	return dimIds;
}

AcDbObjectIdArray ZrxCreateEntitys::CreateDimOrdinate(const AcGePoint3d & ptDef, const AcGeVector3d & vecOffsetX, const AcGeVector3d & vecOffsetY)
{
	AcGePoint3d ptTextX = ptDef + vecOffsetX;
	AcGePoint3d ptTextY = ptDef + vecOffsetY;
	return CreateDimOrdinate(ptDef, ptTextX, ptTextY);
}

