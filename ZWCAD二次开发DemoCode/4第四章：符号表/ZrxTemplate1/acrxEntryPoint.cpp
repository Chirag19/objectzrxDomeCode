//////////////////////////////////////////////////////////////////////////
// ���ļ���������
// 

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CZrxTemplate1App : public AcRxArxApp {
public:
	CZrxTemplate1App() : AcRxArxApp() {}

	virtual AcRx::AppRetCode On_kInitAppMsg(void *pkt) {
		// TODO: �������������������������

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);

		// TODO: ��ʼ��

		return (retCode);
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg(void *pkt) {
		// TODO: �˳�

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);

		// TODO: ж������

		return (retCode);
	}

	virtual void RegisterServerComponents() {
	}

	static void zwzw_CreateLine()
	{
		AcDbObjectId EntId;
		//����ֱ�ߵ������յ�
		AcGePoint3d ptStart(0, 0, 0);
		AcGePoint3d ptEnd(100, 100, 0);
		//����ֱ��
		EntId = CLineUtil::Add(ptStart, ptEnd);
		//�޸�ֱ����ɫ
		if (EntId != NULL)
		{
			acutPrintf(_T("\n����ֱ�߳ɹ���"));
			if (Acad::eOk == CEntityUtil::SetColor(EntId, 1))
			{
				acutPrintf(_T("\n�޸�ֱ����ɫ�ɹ���"));
			}
			else
			{
				acutPrintf(_T("\n�޸�ֱ����ɫʧ�ܣ�"));
			}

		}
		else
		{
			acutPrintf(_T("\n����ֱ��ʧ�ܣ�"));
		}
	}
	static void zwzw_CreateCircle()
	{
		//"Բ�ġ��뾶"������һ��Բ
		AcGePoint3d ptCenter(100, 100, 0);
		CCircleUtil::Add(ptCenter, 20);

		//���㷨����һ��Բ
		AcGePoint3d pt1(70, 100, 0);
		AcGePoint3d pt2(130, 100, 0);
		CCircleUtil::Add(pt1, pt2);

		//���㷨����һ��Բ
		AcGePoint2d pt01(60, 100);
		AcGePoint2d pt02(140, 100);
		AcGePoint2d pt03(100, 60);
		CCircleUtil::Add(pt01, pt02, pt03);
	}
	static void zwzw_CreateArc()
	{
		//����λ��XOYƽ���Բ��
		AcGePoint2d ptCenter(50, 50);
		CArcUtil::Add(ptCenter, 100 * sqrt(2) / 2, 5 * CMathUtil::PI() / 4, 7 * CMathUtil::PI() / 4);

		//���㷨����Բ��
		AcGePoint2d ptStart(100, 0);
		AcGePoint2d ptOnArc(120, 50);
		AcGePoint2d ptEnd(100, 100);
		CArcUtil::Add(ptStart, ptOnArc, ptEnd);

		//��㡢Բ�ġ��յ㴴��Բ��
		ptStart.set(100, 100);
		ptCenter.set(50, 50);
		ptEnd.set(0, 100);
		CArcUtil::AddSCE(ptStart, ptCenter, ptEnd);

		//��� Բ�� Բ���Ƕȴ���Բ��
		ptStart.set(0, 100);
		ptCenter.set(50, 50);
		CArcUtil::Add(ptStart, ptCenter, CMathUtil::PI() / 2);

	}
	static void zwzw_CreatePolyLine()
	{
		//��������һ��ֱ�ߵĶ����
		AcGePoint2d ptStart(0, 0), ptEnd(100, 100);
		CPolylineUtil::Add(ptStart, ptEnd, 1);

		//������ά�����
		AcGePoint3d pt1(0, 0, 0), pt2(100, 0, 0), pt3(100, 100, 0);
		AcGePoint3dArray points;
		points.append(pt1);
		points.append(pt2);
		points.append(pt3);
		CPolylineUtil::Add3dPolyline(points);

		//�����������
		CPolylineUtil::AddPolygon(AcGePoint2d::kOrigin, 6, 30, 0, 1);

		//��������
		AcGePoint2d pt(60, 70);
		CPolylineUtil::AddPolyRectangle(pt, ptEnd, 1);

		//����Բ
		pt.set(50, 50);
		CPolylineUtil::AddPolyCircle(pt, 30, 1);

		//����Բ��
		CPolylineUtil::AddPolyArc(pt, 50, CConvertUtil::AngleToRadian(45), CConvertUtil::AngleToRadian(255), 1);
	}
	static void zwzw_CreateEllipse()
	{
		//ʹ���е㡢����ƽ�桢����ʸ���Ͷ����볤��ı���������Բ
		AcGeVector3d vecNormal(0, 0, 1);
		AcGeVector3d majorAxis(40, 0, 0);
		AcDbObjectId entId;
		entId = CEllipseUtil::Add(AcGePoint3d::kOrigin, vecNormal, majorAxis, 0.5);

		//ʹ����Ӿ��νǵ���������Բ
		AcGePoint2d pt1(60, 80), pt2(140, 120);
		CEllipseUtil::Add(pt1, pt2);
	}
	static void zwzw_CreateSpline()
	{
		//ʹ��������ֱ�Ӵ�����������
		AcGePoint3d pt1(0, 0, 0), pt2(10, 30, 0), pt3(60, 80, 0), pt4(100, 100, 0);
		AcGePoint3dArray points;
		points.append(pt1);
		points.append(pt2);
		points.append(pt3);
		points.append(pt4);
		CSplineUtil::Add(points);

		//ָ����ʼ�����߷������ֹ�����߷���
		pt2.set(30, 10, 0);
		pt3.set(80, 60, 0);

		points.removeSubArray(0, 3);
		points.append(pt1);
		points.append(pt2);
		points.append(pt3);
		points.append(pt4);

		AcGeVector3d startTangent(5, 1, 0);
		AcGeVector3d endTangent(5, 1, 0);
		CSplineUtil::Add(points, startTangent, endTangent);
	}
	static void zwzw_CreateRegion()
	{
		//ʹ��ѡ�񼯣���ʾ�û�ѡ����Ϊ�߽�Ķ���
		ads_name ss;
		int rt = acedSSGet(NULL, NULL, NULL, NULL, ss);		//��ʾ�û�ѡ�����
		//����ѡ���еĶ���߽�����ID����
		AcDbObjectIdArray objIds;
		if (rt == RTNORM)
		{
			long length;
			acedSSLength(ss, &length);	//��ȡѡ���еĶ������
			for (int i = 0; i < length; i++)
			{
				ads_name ent;
				acedSSName(ss, i, ent);
				AcDbObjectId objId;
				acdbGetObjectId(objId, ent);

				objIds.append(objId);
			}
		}
		acedSSFree(ss);	//��ʱ�ͷ�ѡ��

		AcDbObjectIdArray regionIds;
		regionIds = CRegionUtil::Add(objIds);

		int number = regionIds.length();
		acutPrintf(_T("\n�Ѿ����� %d ������"), number);

	}
	static void zwzw_CreateText()
	{
		//������������
		AcGePoint3d ptInsert(0, 4, 0);
		CTextUtil::AddText(ptInsert, _T("�人��󼪰�"));

		//������������
		ptInsert.set(0, 0, 0);
		CTextUtil::AddMText(ptInsert, _T("���³�Ʒ�����Ǿ�Ʒ��"));

	}
	static void zwzw_CreateHatch()
	{
		//��ʾ�û�ѡ�����߽�
		ads_name ss;
		int rt = acedSSGet(NULL, NULL, NULL, NULL, ss);
		AcDbObjectIdArray objIds;
		//��ʼ�����߽��ID����
		if (rt == RTNORM)
		{
			long length;
			acedSSLength(ss, &length);
			for (int i = 0; i < length; i++)
			{
				ads_name ent;
				acedSSName(ss, i, ent);
				AcDbObjectId objId;
				acdbGetObjectId(objId, ent);

				objIds.append(objId);
			}
		}
		acedSSFree(ss);
		CHatchUtil::Add(objIds, _T("SOLID"), 1.0);
	}
	static void zwzw_CreateDimension()
	{
		//ָ����ʼ��λ��
		AcGePoint3d pt1(200, 160, 0);
		AcGePoint3d pt2 = CGePointUtil::RelativePoint(pt1, -40, 0);
		AcGePoint3d pt3 = CGePointUtil::PolarPoint(pt2, 7 * CMathUtil::PI() / 6, 20);
		AcGePoint3d pt4 = CGePointUtil::RelativePoint(pt3, 6, -10);
		AcGePoint3d pt5 = CGePointUtil::RelativePoint(pt1, 0, -20);

		//������������
		CLineUtil::Add(pt1, pt2);
		CLineUtil::Add(pt2, pt3);
		CLineUtil::Add(pt3, pt4);
		CLineUtil::Add(pt4, pt5);
		CLineUtil::Add(pt5, pt1);

		//����Բ��
		AcGePoint3d ptCenter1, ptCenter2;
		ptCenter1 = CGePointUtil::RelativePoint(pt3, 16, 0);
		ptCenter2 = CGePointUtil::RelativePoint(ptCenter1, 25, 0);
		CCircleUtil::Add(ptCenter1, 3);
		CCircleUtil::Add(ptCenter2, 4);

		AcGePoint3d ptTemp1, ptTemp2;
		//ˮƽ��ע
		ptTemp1 = CGePointUtil::RelativePoint(pt1, -20, 3);
		CDimensionUtil::AddDimRotated(pt1, pt2, ptTemp1, 0);

		//��ֱ��ע
		ptTemp1 = CGePointUtil::RelativePoint(pt1, 4, 0);
		CDimensionUtil::AddDimRotated(pt1, pt5, ptTemp1, CMathUtil::PI() / 2);

		//ת�Ǳ�ע
		ptTemp1 = CGePointUtil::RelativePoint(pt3, -3, -6);
		CDimensionUtil::AddDimRotated(pt3, pt4, ptTemp1, 7 * CMathUtil::PI() / 4);

		//�����־
		ptTemp1 = CGePointUtil::RelativePoint(pt2, -3, 4);
		CDimensionUtil::AddDimAligned(pt2, pt3, ptTemp1, AcGeVector3d(4, 10, 0), _T("new position"));

		//�Ƕȱ�ע
		ptTemp1 = CGePointUtil::RelativePoint(pt5, -5, 5);
		CDimensionUtil::AddDim3PtAngular(pt5, pt1, pt4, ptTemp1);

		//�뾶��ע
		ptTemp1 = CGePointUtil::PolarPoint(ptCenter1, CMathUtil::PI() / 4, 3);
		CDimensionUtil::AddDimRadial(ptCenter1, ptTemp1, -3);

		//ֱ����ע
		ptTemp1 = CGePointUtil::RelativePoint(ptCenter2, CMathUtil::PI() / 4, 4);
		ptTemp2 = CGePointUtil::RelativePoint(ptCenter2, CMathUtil::PI() / 4, -4);
		CDimensionUtil::AddDimDiameteric(ptTemp1, ptTemp2, 0);

		//�����ע
		CDimensionUtil::AddDimOrdinate(ptCenter2, AcGeVector3d(0, -10, 0), AcGeVector3d(10, 0, 0));
	}
	static void zwzw_GetAllEntByLayer()
	{
		AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds(_T("test"));
		for (int i = 0; i < allEntIds.length(); i++)
		{
			AcDbLine *pLine = NULL;
			if (acdbOpenObject(pLine, allEntIds[i], AcDb::kForWrite) == Acad::eOk)
			{
				pLine->setColorIndex(1);
				pLine->close();
			}
		}
	}
	static void zwzw_CreateBlock()
	{
		//��õ�ǰͼ�����ݿ�
		AcDbBlockTable *pBlkTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);

		//�����µĿ���¼
		AcDbBlockTableRecord *pBlkTblRcd = new AcDbBlockTableRecord();

		//�����û����������ÿ���¼������
		TCHAR blkName[40];
		if (acedGetString(Adesk::kFalse, _T("\n����ͼ������ƣ�"), blkName) != RTNORM)
		{
			pBlkTbl->close();
			delete pBlkTblRcd;
			return;
		}

		pBlkTblRcd->setName(blkName);

		//������¼��ӵ������
		AcDbObjectId blbDefId;
		pBlkTbl->add(blbDefId, pBlkTblRcd);
		pBlkTbl->close();

		//���������ʵ��
		AcGePoint3d ptStart(-10, 0, 0), ptEnt(10, 0, 0);
		AcDbLine *pLine1 = new AcDbLine(ptStart, ptEnt);	//����һ��ֱ��
		ptStart.set(0, -10, 0);
		ptEnt.set(0, 10, 0);
		AcDbLine *pLine2 = new AcDbLine(ptStart, ptEnt);	//����һ��ֱ��
		AcGeVector3d vecNormal(0, 0, 1);
		AcDbCircle *pCircle = new AcDbCircle(AcGePoint3d::kOrigin, vecNormal, 6);

		AcDbObjectId entId;
		pBlkTblRcd->appendAcDbEntity(entId, pLine1);
		pBlkTblRcd->appendAcDbEntity(entId, pLine2);
		pBlkTblRcd->appendAcDbEntity(entId, pCircle);

		//�رտ���¼
		pLine1->close();
		pLine2->close();
		pCircle->close();
		pBlkTblRcd->close();

	}
	static void zwzw_InsertBlock()
	{
		//��ȡ�û�����Ŀ鶨������
		TCHAR blkName[40];
		if (acedGetString(Adesk::kFalse, _T("\n����ͼ�������:"), blkName) != RTNORM)
		{
			return;
		}
		//��ȡ��ǰ���ݿ�Ŀ��
		AcDbBlockTable *pBlkTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);
		//�����û�ָ���Ŀ鶨���Ƿ����
		CString strBlkDef;
		strBlkDef.Format(_T("%s"), blkName);
		if (!pBlkTbl->has(strBlkDef))
		{
			acutPrintf(_T("\n��ǰͼ����δ����ָ�����ƵĿ鶨�壡"));
			pBlkTbl->close();
			return;
		}
		//����û�����Ŀ���յĲ����
		ads_point pt;
		if (acedGetPoint(NULL, _T("\n�������յĲ����:"), pt) != RTNORM)
		{
			pBlkTbl->close();
			return;
		}
		AcGePoint3d ptInsert = asPnt3d(pt);

		//��ȡ�û�ָ���Ŀ���¼
		AcDbObjectId blkDefId;
		pBlkTbl->getAt(strBlkDef, blkDefId);
		pBlkTbl->close();

		//�������ն���
		AcDbBlockReference *pBlkRef = new AcDbBlockReference(ptInsert, blkDefId);

		//���������ӵ�ģ�Ϳռ�
		CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
	}
	static void zwzw_InsertBlock2()
	{
		//��ȡ�û�ָ���Ŀ鶨���Ƿ����
		TCHAR blkName[40];
		if (acedGetString(Adesk::kFalse, _T("\n����ͼ�������:"), blkName) != RTNORM)
		{
			return;
		}
		AcDbObjectId blkDefId = CBlockUtil::GetBlkDefId(blkName);
		if (blkDefId.isNull())
		{
			acutPrintf(_T("\n��ǰͼ����δ����ָ�����ƵĿ鶨��"));
			return;
		}

		//��ȡ�û�����Ŀ���յĲ����
		ads_point pt;
		if (acedGetPoint(NULL, _T("\n�������յĲ����"), pt) != RTNORM)
		{
			return;
		}
		AcGePoint3d ptInsert = asPnt3d(pt);

		//��������ն���
		AcDbBlockReference *pBlkRef = new AcDbBlockReference(ptInsert, blkDefId);

		//���������ӵ�ģ�Ϳռ�
		CDwgDatabaseUtil::PostToModelSpace(pBlkRef);
	}
	static void zwzw_InsertBlock3()
	{
		//��ȡ�û�����Ŀ鶨������
		TCHAR blkName[40];
		if (acedGetString(Adesk::kFalse, _T("\n����ͼ������:"), blkName) != RTNORM)
		{
			return;
		}
		//�����û�ָ���Ŀ鶨���Ƿ����
		AcDbObjectId blkDefId = CBlockUtil::GetBlkDefId(blkName);
		if (blkDefId.isNull())
		{
			acutPrintf(_T("\n��ǰͼ����δ����ָ�����ƵĿ鶨�壡"));
			return;
		}
		ads_point pt;
		if (acedGetPoint(NULL, _T("\n�������յĲ����:"), pt) != RTNORM)
		{
			return;
		}
		AcGePoint3d ptInsert = asPnt3d(pt);

		//�������գ�����ֵʹ��Ĭ��ֵ��
		AcDbObjectId blkRefId = CBlockUtil::InsertBlockRefWithAttribute(blkDefId, ptInsert, 1, 0);

		//���ò���ֵ
		AcDbBlockReference *pBlkRef = NULL;
		if (acdbOpenObject(pBlkRef, blkRefId, AcDb::kForWrite) == Acad::eOk)
		{
			CBlockUtil::SetBlockRefAttribute(pBlkRef, _T("����"), _T("���ΰ�"));
			CBlockUtil::SetBlockRefAttribute(pBlkRef, _T("����"), _T("2.3Kg"));
			pBlkRef->close();
		}
	}
	static void zwzw_BlockIntersectWith()
	{
		//��ȡͼ�����ݿ�����Ҫ����Ŀ����
		AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
		AcDbObjectId blkRefId;
		for (int i = 0; i < allEntIds.length(); i++)
		{
			AcDbBlockReference *pBlkRef = NULL;
			if (acdbOpenObject(pBlkRef, allEntIds[i], AcDb::kForRead) == Acad::eOk)
			{
				blkRefId = pBlkRef->objectId();
				pBlkRef->close();
			}
		}
		//����պ�ֱ�߼�����ʵ����
		AcDbBlockReference *pBlkRef = NULL;
		if (acdbOpenObject(pBlkRef, blkRefId, AcDb::kForRead) == Acad::eOk)
		{
			for (int i = 0; i < allEntIds.length(); i++)
			{
				if (allEntIds[i] != blkRefId)
				{
					AcDbLine *pLine = NULL;
					if (acdbOpenObject(pLine, allEntIds[i], AcDb::kForRead) == Acad::eOk)
					{
						AcGePoint3dArray intPoints;
						CBlockUtil::IntersectWith(pBlkRef, pLine, intPoints, false, false, false);
						//�������ú�ɫ��Բ���Ƴ���
						for (int j = 0; j < intPoints.length(); j++)
						{
							double radius = 4;
							AcDbObjectId circleId = CCircleUtil::Add(intPoints[j], radius);
							CEntityUtil::SetColor(circleId, 1);
						}
						pLine->close();
					}
				}
			}
			pBlkRef->close();
		}

	}
	static void zwzw_NewLayer()
	{
		//��ʾ�û�����ͼ������
		TCHAR layerName[100];
		if (acedGetString(Adesk::kFalse, _T("\n����ͼ�������:"), layerName) != RTNORM)
		{
			return;
		}
		//�½�ͼ��
		AcDbObjectId layerId = CLayerUtil::GetLayerId(layerName);
		if (layerId.isValid())
		{
			acutPrintf(_T("\nͼ�����Ѵ���ͬ����ͼ��."));
		}
		else
		{
			CLayerUtil::Add(layerName);
			acutPrintf(_T("\n�ɹ�����ͼ��."));
		}
	}
	static void zwzw_LayerColor()
	{
		//��ʾ�û�����ͼ������
		TCHAR layerName[100];
		if (acedGetString(Adesk::kFalse, _T("\n����ͼ�������:"), layerName) != RTNORM)
		{
			return;
		}
		//�½�ͼ��
		AcDbObjectId layerId = CLayerUtil::GetLayerId(layerName);
		if (layerId.isValid())
		{
			//��ȡͼ�㵱ǰ��ɫ
			AcCmColor oldColor;
			AcDbLayerTableRecord *pLayerTblRcd = NULL;
			if (acdbOpenObject(pLayerTblRcd, layerId, AcDb::kForRead) == Acad::eOk)
			{
				oldColor = pLayerTblRcd->color();
				pLayerTblRcd->close();
			}
			int nCurColor = oldColor.colorIndex();	//ͼ���޸�ǰ����ɫ
			int nNewColor = oldColor.colorIndex();	//�û�ѡ�����ɫ

			//��������ɫ���Ի���
			if (acedSetColorDialog(nNewColor, Adesk::kFalse, nCurColor))
			{
				CLayerUtil::SetColor(layerName, nNewColor);
			}
		}
		else
		{
			acutPrintf(_T("\nͼ���в�����ָ������ͼ��."));
		}
	}
	static void zwzw_DeleteLayer()
	{
		//��ʾ�û�����ͼ������
		TCHAR layerName[100];
		if (acedGetString(Adesk::kFalse, _T("\n����ͼ�������:"), layerName) != RTNORM)
		{
			return;
		}
		//�½�ͼ��
		AcDbObjectId layerId = CLayerUtil::GetLayerId(layerName);
		if (layerId.isValid())
		{
			//ɾ��ͼ��
			AcDbLayerTableRecord *pLayerTblRcd = NULL;
			if (acdbOpenObject(pLayerTblRcd, layerId, AcDb::kForWrite) == Acad::eOk)
			{
				pLayerTblRcd->erase();
				pLayerTblRcd->close();
				acutPrintf(_T("\nɾ��ͼ�㣺%s �ɹ�."), layerName);
			}
		}
		else
		{
			acutPrintf(_T("\nͼ���в�����ָ������ͼ��."));
		}
	}
	static void zwzw_ExportLayer()
	{
		//��ȡͼ���б�
		AcDbObjectIdArray layerIds;
		CLayerUtil::GetLayerList(layerIds);

		//����ͼ���б�������Ҫд�뵽�ı��ļ����ַ�������
		std::vector<CString> lines;
		for (int i = 0; i < layerIds.length(); i++)
		{
			AcDbLayerTableRecord *pLayerTblRcd = NULL;
			if (acdbOpenObject(pLayerTblRcd, layerIds[i], AcDb::kForRead) == Acad::eOk)
			{
				//���ͼ�����Ϣ
				std::vector<CString> layerInfos;
				TCHAR *szLayerName;	//ͼ������
				pLayerTblRcd->getName(szLayerName);
				layerInfos.push_back(szLayerName);
				acutDelString(szLayerName);

				AcCmColor color = pLayerTblRcd->color();	//ͼ����ɫ
				layerInfos.push_back(CConvertUtil::ToString(color.colorIndex()));

				AcDbLinetypeTableRecord *pLinetypeTblRcd = NULL;	//ͼ������
				acdbOpenObject(pLinetypeTblRcd, pLayerTblRcd->linetypeObjectId(), AcDb::kForRead);
				TCHAR *szLinetypeName;
				pLinetypeTblRcd->getName(szLinetypeName);
				layerInfos.push_back(szLinetypeName);
				acutDelString(szLinetypeName);

				AcDb::LineWeight lineWeight = pLayerTblRcd->lineWeight();	//ͼ���߿�
				int nVal = (int)lineWeight;		//ö��ת��Ϊ����
				layerInfos.push_back(CConvertUtil::ToString(nVal));

				CString strLayerInfo = CStringUtil::Jion(layerInfos, _T(","));	//Ҫ���ͼ�������Ϣ

				lines.push_back(strLayerInfo);

				pLayerTblRcd->close();
			}
		}

		//д���ı��ļ�
		CString fileNmae = _T("D:\\layers.txt");
		CTextFileUtil::Save(fileNmae, lines);

	}
	static void zwzw_ImportLayer()
	{
		//��ȡ�ı��е�����
		CString fileName = _T("D:\\layers.txt");
		if (_taccess(fileName, 0) != -1)
		{
			std::vector<CString> lines;
			CTextFileUtil::Load(fileName, lines);

			//����ÿһ���ַ���������ǰͼ���е�ͼ��
			for (int i = 0; i < lines.size(); i++)
			{
				std::vector<CString> layerInfos;
				CStringUtil::Split(lines[i], _T(","), layerInfos, false);
				if (layerInfos.size() == 4)
				{
					CString layerName = layerInfos[0];
					AcDbObjectId layerId = CLayerUtil::GetLayerId(layerName);
					if (layerId.isNull())
					{
						CLayerUtil::Add(layerName);
						layerId = CLayerUtil::GetLayerId(layerName);
					}

					AcDbLayerTableRecord *pLayerTblRcd = NULL;
					if (acdbOpenObject(pLayerTblRcd, layerId, AcDb::kForWrite) == Acad::eOk)
					{
						//������ɫ
						AcCmColor color;
						Adesk::UInt16 colorIndex = _ttoi(layerInfos[1]);
						color.setColorIndex(colorIndex);
						pLayerTblRcd->setColor(color);

						//��������
						AcDbLinetypeTable *pLinetypeTbl = NULL;
						AcDbObjectId linetypeId;
						acdbHostApplicationServices()->workingDatabase()->getLinetypeTable(pLinetypeTbl, AcDb::kForRead);
						if (pLinetypeTbl->has(layerInfos[2]))
						{
							pLinetypeTbl->getAt(layerInfos[2], linetypeId);
							pLayerTblRcd->setLinetypeObjectId(linetypeId);
						}
						pLinetypeTbl->close();

						//�����߿�
						AcDb::LineWeight lineWeight = (AcDb::LineWeight)_ttoi(layerInfos[3]);

						pLayerTblRcd->setLineWeight(lineWeight);

						pLayerTblRcd->close();
					}
				}
			}
		}
		else
		{
			acutPrintf(_T("\nδ�ҵ�ָ�����ļ�."));
		}
	}
	static void zwzw_AddTextStyle()
	{
		CString textStyleName = _T("��������");
		AcDbObjectId textStyleId = CTextStyleUtil::GetAt(textStyleName);
		if (textStyleId.isNull())
		{
			CTextStyleUtil::Add(textStyleName, _T("txt.shx"), _T("hztxt.shx"));
		}

	}
	static void zwzw_ZoomWindow()
	{
		//��ʾ�û�ѡ�������Ŵ��ڵ������ǵ�
		ads_point pt1, pt2;
		if (acedGetPoint(NULL, _T("\n�����һ���ǵ�:"), pt1) != RTNORM)
			return;
		if (acedGetCorner(pt1, _T("\n����ڶ����ǵ�:"), pt2) != RTNORM)
			return;

		//�������ǵ������ת������������
		AcGePoint3d pt1Wcs = CConvertUtil::WcsToDcsPoint(asPnt3d(pt1));
		AcGePoint3d pt2Wcs = CConvertUtil::WcsToDcsPoint(asPnt3d(pt2));

		CViewUtil::Set(pt1Wcs, pt2Wcs, 1.0);
	}
	static void zwzw_ZoomExtents()
	{
		CViewUtil::ZoomExtent();
	}
	static void zwzw_ZoomEntity()
	{
		//Ѱ��ͼ���еĿ�ԭ�Եİ�Χ��
		AcDbObjectIdArray allEntIds = CDwgDatabaseUtil::GetAllEntityIds();
		bool bFound = false;
		AcDbExtents ext;
		for (int i = 0; i < allEntIds.length(); i++)
		{
			AcDbCircle *pCircle = NULL;
			if (acdbOpenObject(pCircle, allEntIds[i], AcDb::kForRead) == Acad::eOk)
			{
				pCircle->getGeomExtents(ext);
				bFound = true;
				pCircle->close();
			}
		}

		//��ͼ���е�Բ����ʾ��ͼ�δ�������
		if (bFound)
		{
			CViewUtil::Set(ext.minPoint(), ext.maxPoint(), 5.0);
		}
	}
	static void zwzw_Create4VPotrs()
	{
		//��ȡ�ӿڱ�
		AcDbViewportTable *pVPortTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()->getViewportTable(pVPortTbl, AcDb::kForWrite);

		//�ֱ𴴽��ĸ��ӿ�
		AcGePoint2d pt1, pt2;

		AcDbViewportTableRecord *pVPortTblRcd1 = new AcDbViewportTableRecord();
		pt1.set(0, 0);
		pt2.set(0.5, 0.5);
		pVPortTblRcd1->setLowerLeftCorner(pt1);
		pVPortTblRcd1->setUpperRightCorner(pt2);
		pVPortTblRcd1->setName(_T("4VPorts"));

		AcDbViewportTableRecord *pVPortTblRcd2 = new AcDbViewportTableRecord();
		pt1.set(0.5, 0);
		pt2.set(1.0, 0.5);
		pVPortTblRcd2->setLowerLeftCorner(pt1);
		pVPortTblRcd2->setUpperRightCorner(pt2);
		pVPortTblRcd2->setName(_T("4VPorts"));

		AcDbViewportTableRecord *pVPortTblRcd3 = new AcDbViewportTableRecord();
		pt1.set(0, 0.5);
		pt2.set(0.5, 1);
		pVPortTblRcd3->setLowerLeftCorner(pt1);
		pVPortTblRcd3->setUpperRightCorner(pt2);
		pVPortTblRcd3->setName(_T("4VPorts"));

		AcDbViewportTableRecord *pVPortTblRcd4 = new AcDbViewportTableRecord();
		pt1.set(0.5, 0.5);
		pt2.set(1.0, 1.0);
		pVPortTblRcd4->setLowerLeftCorner(pt1);
		pVPortTblRcd4->setUpperRightCorner(pt2);
		pVPortTblRcd4->setName(_T("4VPorts"));

		pVPortTbl->add(pVPortTblRcd1);
		pVPortTbl->add(pVPortTblRcd2);
		pVPortTbl->add(pVPortTblRcd3);
		pVPortTbl->add(pVPortTblRcd4);

		pVPortTbl->close();
		pVPortTblRcd1->close();
		pVPortTblRcd2->close();
		pVPortTblRcd3->close();
		pVPortTblRcd4->close();

		//�жϵ�ǰ�Ŀռ�
		struct resbuf rb;
		acedGetVar(_T("TILEMODE"), &rb);
		if (rb.resval.rint == 1)	//��ǰ�ռ���ģ�Ϳռ�
		{
			acedCommand(RTSTR, _T(".-VPORTS"), RTSTR, _T("R"), RTSTR, _T("4VPorts"), RTNONE);
		}
		else  //��ǰ�ռ���ͼֽ�ռ�
		{
			acedCommand(RTSTR, _T(".-VPORTS"), RTSTR, _T("R"), RTSTR, _T("4VPorts"), RTSTR, _T(""), RTNONE);
		}
	}
	static void zwzw_CreateVPotrInSpace()
	{
		//ָ����ǰ����
		Acad::ErrorStatus es = acdbHostApplicationServices()->layoutManager()->setCurrentLayout(_T("����1"));

		if (es != Acad::eOk)
		{
			return;
		}

		//��ñ�
		AcDbBlockTable *pBlkTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForRead);

		//���ͼֽ�տռ�Ŀ���¼
		AcDbBlockTableRecord *pBlkTblRcd = NULL;
		pBlkTbl->getAt(ACDB_PAPER_SPACE, pBlkTblRcd, AcDb::kForWrite);
		pBlkTbl->close();

		//�����µĲ��ֶ���
		AcDbViewport *pViewport = new AcDbViewport();
		pViewport->setCenterPoint(AcGePoint3d(100, 50, 0));
		pViewport->setHeight(80);
		pViewport->setWidth(120);

		//���µĲ��ֶ�����ӵ�ͼֽ�ռ����¼��
		AcDbObjectId viewportId;
		pBlkTblRcd->appendAcDbEntity(viewportId, pViewport);

		pViewport->close();
		pBlkTblRcd->close();

		//���½����ӿ���Ϊ��ǰ�ӿ�
		AcDbViewport *pVP = NULL;
		if (acdbOpenObject(pVP, viewportId, AcDb::kForWrite) == Acad::eOk)
		{
			pViewport->setOn();
			acedSetCurrentVPort(pVP);
			pVP->close();
		}
	}
	static void zwzw_NewUCS()
	{
		//��õ�ǰ��UCS��
		AcDbUCSTable *pUcsTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()->getUCSTable(pUcsTbl, AcDb::kForWrite);

		//����UCS�Ĳ���
		AcGePoint3d ptOrigin(0, 0, 0);
		AcGeVector3d vecXAxis(1, 1, 0);
		AcGeVector3d vecYAxis(-1, 1, 0);

		//�����µ�UCS���¼
		AcDbUCSTableRecord *pUCSTblRcd = new AcDbUCSTableRecord();

		//����UCS�Ĳ���
		Acad::ErrorStatus es = pUCSTblRcd->setName(_T("NewUcs"));
		if (es != Acad::eOk)
		{
			delete pUCSTblRcd;
			pUcsTbl->close();
			return;
		}

		pUCSTblRcd->setOrigin(ptOrigin);
		pUCSTblRcd->setXAxis(vecXAxis);
		pUCSTblRcd->setYAxis(vecYAxis);

		//��������UCS���¼��ӵ�UCS����
		es = pUcsTbl->add(pUCSTblRcd);
		if (es != Acad::eOk)
		{
			delete pUCSTblRcd;
			pUcsTbl->close();
			return;
		}

		//�رն���
		pUCSTblRcd->close();
		pUcsTbl->close();
	}
	static void zwzw_SetCurUcs()
	{
		//��ʾ�û�����UCS������
		TCHAR ucsName[40];
		if (acedGetString(NULL, _T("\n�����û�����ϵ������:"), ucsName) != RTNORM)
			return;

		//��ȡָ����UCS���¼
		AcDbUCSTable *pUcsTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()->getUCSTable(pUcsTbl, AcDb::kForRead);
		if (!pUcsTbl->has(ucsName))
		{
			pUcsTbl->close();
			return;
		}
		AcDbUCSTableRecord *pUcsTblRcd;
		pUcsTbl->getAt(ucsName, pUcsTblRcd, AcDb::kForRead);

		//���UCS�ı任����
		AcGeMatrix3d mat;
		AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
		vecXAxis = pUcsTblRcd->xAxis();
		vecYAxis = pUcsTblRcd->yAxis();
		vecZAxis = vecXAxis.crossProduct(vecYAxis);
		mat.setCoordSystem(pUcsTblRcd->origin(), vecXAxis, vecYAxis, vecZAxis);

		//�ر�UCS���UCS���¼
		pUcsTblRcd->close();
		pUcsTbl->close();

		//���õ�ǰUCS
		acedSetCurrentUCS(mat);

	}
	static void zwzw_MoveUcsOrigin()
	{
		//��õ�ǰUCS�ı任����
		AcGeMatrix3d mat;
		Acad::ErrorStatus es = acedGetCurrentUCS(mat);

		//���ݱ任������UCS����
		AcGePoint3d ptOrigin;
		AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
		mat.getCoordSystem(ptOrigin, vecXAxis, vecYAxis, vecZAxis);

		//�ƶ�UCS��ԭ��
		AcGeVector3d vec(100, 100, 0);
		ptOrigin += vec;

		//���±任����
		mat.setCoordSystem(ptOrigin, vecXAxis, vecYAxis, vecZAxis);

		//Ӧ�ø��µ�UCS
		acedSetCurrentUCS(mat);
	}
	static void zwzw_RotateUcs()
	{
		//��õ�ǰUCS�ı任����
		AcGeMatrix3d mat;
		Acad::ErrorStatus es = acedGetCurrentUCS(mat);

		//���ݱ任������UCS����
		AcGePoint3d ptOrigin;
		AcGeVector3d vecXAxis, vecYAxis, vecZAxis;
		mat.getCoordSystem(ptOrigin, vecXAxis, vecYAxis, vecZAxis);

		//��Z����ת60��
		vecXAxis.rotateBy(60 * atan(1) * 4 / 180, vecZAxis);
		vecYAxis.rotateBy(60 * atan(1) * 4 / 180, vecZAxis);

		//���±任����
		mat.setCoordSystem(ptOrigin, vecXAxis, vecYAxis, vecZAxis);

		//Ӧ�ø��µ�UCS
		acedSetCurrentUCS(mat);
	}
	static void zwzw_AddEntInUcs()
	{
		//��ʾ�û�����ֱ�ߵ������յ�
		ads_point pt1, pt2;
		if (acedGetPoint(NULL, _T("\nʰȡֱ�ߵ���㣺"), pt1) != RTNORM)
			return;
		if (acedGetPoint(NULL, _T("\nʰȡֱ�ߵ��յ㣺"), pt2) != RTNORM)
			return;

		//����UCS���괴��ʵ��
		AcDbLine *pLIne = new AcDbLine(asPnt3d(pt1), asPnt3d(pt2));

		//��ʵ����м���ת��
		AcGeMatrix3d mat;
		Acad::ErrorStatus es = acedGetCurrentUCS(mat);
		pLIne->transformBy(mat);

		//���뵽ģ�Ϳռ�
		CDwgDatabaseUtil::PostToModelSpace(pLIne);
	}
};

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CZrxTemplate1App)

//����ֱ��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateLine, CreateLine, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//����Բ
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateCircle, CreateCircle, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//����Բ��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateArc, CreateArc, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//���������
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreatePolyLine, CreatePolyLine, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//������Բ
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateEllipse, CreateEllipse, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//������������
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateSpline, CreateSpline, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//��������
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateRegion, CreateRegion, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//�������ֺͶ�������
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateText, CreateText, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//�������
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateHatch, CreateHatch, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//���������ע
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateDimension, CreateDimension, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//��ȡָ��ͼ��������ʵ��  �޸�ֱ����ɫΪ��ɫ
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_GetAllEntByLayer, GetAllEntByLayer, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)


//�����鶨��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateBlock, CreateBlock, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//��������
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_InsertBlock, InsertBlock, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//��������
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_InsertBlock2, InsertBlock2, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//��������Կ����
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_InsertBlock3, InsertBlock3, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//����ͼ����ֱ�������յ���ʵ����
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_BlockIntersectWith, BlockIntersectWith, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)

//������ͼ��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_NewLayer, NewLayer, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//�޸�ָ��ͼ�����ɫ
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_LayerColor, LayerColor, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//ɾ��ָ��ͼ��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_DeleteLayer, DeleteLayer, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//����ǰͼ���ļ��д��ڵ�����ͼ�㼰�����Ե�����һ���ı���
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_ExportLayer, ExportLayer, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//�����ı���ͼ���������CAD�д���ͼ��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_ImportLayer, ImportLayer, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)


//�����µ�����������ʽ��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_AddTextStyle, AddTextStyle, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)

//ģ�ⴰ�����Ź���
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_ZoomWindow, ZoomWindow, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//ģ��Zoom E
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_ZoomExtents, ZoomExtents, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
//��Բ��Ϊ�е㣬������Բ�İ�Χ��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_ZoomEntity, ZoomEntity, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)


//����4���ȴ���ӿ�
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_Create4VPotrs, Create4VPotrs, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
// ��ͼֽ�ռ䴴��һ���µ��ӿ�
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_CreateVPotrInSpace, CreateVPotrInSpace, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)

// ����һ���µ�UCS������ӵ�UCS����
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_NewUCS, NewUCS, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
// ���õ�ǰUCS
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_SetCurUcs, SetCurUcs, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
// ���õ�ǰUCS
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_MoveUcsOrigin, MoveUcsOrigin, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
// ��ת��ǰUCS
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_RotateUcs, RotateUcs, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
// ����UCS�е����괴��ʵ��
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, zw_AddEntInUcs, AddEntInUcs, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)