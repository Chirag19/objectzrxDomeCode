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
class CZrxTemplate1App : public AcRxArxApp{
public:
	CZrxTemplate1App() : AcRxArxApp() {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: �������������������������

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: ��ʼ��

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: �˳�

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: ж������

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

	static void zwzw_CreateLine()
	{
		AcDbObjectId EntId;
		//����ֱ�ߵ������յ�
		AcGePoint3d ptStart(0, 0, 0);
		AcGePoint3d ptEnd(100, 100, 0);
		//����ֱ��
		EntId =ZrxCreateEntitys::CreateLine(ptStart,ptEnd);
		//�޸�ֱ����ɫ
		if (EntId != NULL)
		{
			acutPrintf(L"����ֱ�߳ɹ���\n");
			if (Acad::eOk == ZrxEditObject::SetColor(EntId, 1))
			{
				acutPrintf(L"�޸�ֱ����ɫ�ɹ���\n");
			}
			else
			{
				acutPrintf(L"�޸�ֱ����ɫʧ�ܣ�\n");
			}

		}
		else
		{
			acutPrintf(L"����ֱ��ʧ�ܣ�\n");
		}
	}
	static void zwzw_CreateCircle()
	{
		//"Բ�ġ��뾶"������һ��Բ
		AcGePoint3d ptCenter(100, 100, 0);
		ZrxCreateEntitys::CreateCircle(ptCenter, 20);

		//���㷨����һ��Բ
		AcGePoint3d pt1(70, 100, 0);
		AcGePoint3d pt2(130, 100,0);
		ZrxCreateEntitys::CreateCircle(pt1, pt2);

		//���㷨����һ��Բ
		AcGePoint2d pt01(60, 100);
		AcGePoint2d pt02(140, 100);
		AcGePoint2d pt03(100, 60);
		ZrxCreateEntitys::CreateCircle(pt01, pt02, pt03);
	}
	static void zwzw_CreateArc()
	{
		//����λ��XOYƽ���Բ��
		AcGePoint2d ptCenter(50, 50);
		ZrxCreateEntitys::CreateArc(ptCenter, 100 * sqrt(2) / 2, 5 * GeoMetryUtil::PI() / 4, 7 * GeoMetryUtil::PI() / 4);
		
		//���㷨����Բ��
		AcGePoint2d ptStart(100, 0);
		AcGePoint2d ptCenter_or_OnArc(120, 50);
		AcGePoint2d ptEnd(100, 100);
		ZrxCreateEntitys::CreateArc(ptStart, ptCenter_or_OnArc, ptEnd, FALSE);
		
		//��㡢Բ�ġ��յ㴴��Բ��
		ptStart.set(100, 100);
		ptCenter_or_OnArc.set(50, 50);
		ptEnd.set(0, 100);
		ZrxCreateEntitys::CreateArc(ptStart, ptCenter_or_OnArc, ptEnd);
		
		//��� Բ�� Բ���Ƕȴ���Բ��
		ptStart.set(0, 100);
		ptCenter.set(50, 50);
		ZrxCreateEntitys::CreateArc(ptStart, ptCenter, GeoMetryUtil::PI() / 2);

	}
	static void zwzw_CreatePolyLine()
	{
		//��������һ��ֱ�ߵĶ����
		AcGePoint2d ptStart(0, 0), ptEnd(100, 100);
		ZrxCreateEntitys::CreatePolyOneLine(ptStart, ptEnd, 1);

		//������ά�����
		AcGePoint3d pt1(0, 0, 0), pt2(100, 0, 0), pt3(100, 100, 0);
		AcGePoint3dArray points;
		points.append(pt1);
		points.append(pt2);
		points.append(pt3);
		ZrxCreateEntitys::Create3dPolyLine(points);

		//�����������
		ZrxCreateEntitys::CreatePolygon(AcGePoint2d::kOrigin, 6, 30, 0, 1);

		//��������
		AcGePoint2d pt(60, 70);
		ZrxCreateEntitys::CreatePolyRectangle(pt, ptEnd, 1);

		//����Բ
		pt.set(50, 50);
		ZrxCreateEntitys::CreatePolyCircle(pt, 30, 1);

		//����Բ��
		ZrxCreateEntitys::CreatePolyArc(pt, 50, GeoMetryUtil::AngleToRadian(45), GeoMetryUtil::AngleToRadian(255), 1);
	}
	static void zwzw_CreateEllipse()
	{
		//ʹ���е㡢����ƽ�桢����ʸ���Ͷ����볤��ı���������Բ
		AcGeVector3d vecNormal(0, 0, 1);
		AcGeVector3d majorAxis(40, 0, 0);
		AcDbObjectId entId;
		entId = ZrxCreateEntitys::CreateEillpse(AcGePoint3d::kOrigin, vecNormal, majorAxis, 0.5);

		//ʹ����Ӿ��νǵ���������Բ
		AcGePoint2d pt1(60, 80), pt2(140, 120);
		ZrxCreateEntitys::CreateEillpse(pt1, pt2);
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
		ZrxCreateEntitys::CreateSpline(points);

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
		ZrxCreateEntitys::CreateSpline(points, startTangent, endTangent);
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
		regionIds = ZrxCreateEntitys::CreateRegion(objIds);

		int number = regionIds.length();
		acutPrintf(L"\n�Ѿ����� %d ������", number);

	}
	static void zwzw_CreateText()
	{
		//������������
		AcGePoint3d ptInsert(0, 4, 0);
		ZrxCreateEntitys::CreateText(ptInsert, L"�人��󼪰�");

		//������������
		ptInsert.set(0, 0, 0);
		ZrxCreateEntitys::CreateMText(ptInsert, L"���³�Ʒ�����Ǿ�Ʒ��");

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
ZrxCreateEntitys::CreateHatch(objIds, L"SOLID", 1.0);
	}
	static void zwzw_CreateDimension()
	{
		//ָ����ʼ��λ��
		AcGePoint3d pt1(200, 160, 0);
		AcGePoint3d pt2 = GeoMetryUtil::RelativePoint(pt1, -40, 0);
		AcGePoint3d pt3 = GeoMetryUtil::PolarPoint(pt2, 7 * GeoMetryUtil::PI() / 6, 20);
		AcGePoint3d pt4 = GeoMetryUtil::RelativePoint(pt3, 6, -10);
		AcGePoint3d pt5 = GeoMetryUtil::RelativePoint(pt1, 0, -20);

		//������������
		ZrxCreateEntitys::CreateLine(pt1, pt2);
		ZrxCreateEntitys::CreateLine(pt2, pt3);
		ZrxCreateEntitys::CreateLine(pt3, pt4);
		ZrxCreateEntitys::CreateLine(pt4, pt5);
		ZrxCreateEntitys::CreateLine(pt5, pt1);

		//����Բ��
		AcGePoint3d ptCenter1, ptCenter2;
		ptCenter1 = GeoMetryUtil::RelativePoint(pt3, 16, 0);
		ptCenter2 = GeoMetryUtil::RelativePoint(ptCenter1, 25, 0);
		ZrxCreateEntitys::CreateCircle(ptCenter1, 3);
		ZrxCreateEntitys::CreateCircle(ptCenter2, 4);

		AcGePoint3d ptTemp1, ptTemp2;
		//ˮƽ��ע
		ptTemp1 = GeoMetryUtil::RelativePoint(pt1, -20, 3);
		ZrxCreateEntitys::CreateDimRotated(pt1, pt2, ptTemp1, 0);

		//��ֱ��ע
		ptTemp1 = GeoMetryUtil::RelativePoint(pt1, 4, 0);
		ZrxCreateEntitys::CreateDimRotated(pt1, pt5, ptTemp1, GeoMetryUtil::PI() / 2);

		//ת�Ǳ�ע
		ptTemp1 = GeoMetryUtil::RelativePoint(pt3, -3, -6);
		ZrxCreateEntitys::CreateDimRotated(pt3, pt4, ptTemp1, 7 * GeoMetryUtil::PI() / 4);

		//�����־
		ptTemp1 = GeoMetryUtil::RelativePoint(pt2, -3, 4);
		ZrxCreateEntitys::CreateDimAligned(pt2, pt3, ptTemp1, AcGeVector3d(4, 10, 0), L"new position");

		//�Ƕȱ�ע
		ptTemp1 = GeoMetryUtil::RelativePoint(pt5, -5, 5);
		ZrxCreateEntitys::CreateDim3PtAngular(pt5, pt1, pt4, ptTemp1);

		//�뾶��ע
		ptTemp1 = GeoMetryUtil::PolarPoint(ptCenter1, GeoMetryUtil::PI() / 4, 3);
		ZrxCreateEntitys::CreateDimRadial(ptCenter1, ptTemp1, -3);

		//ֱ����ע
		ptTemp1 = GeoMetryUtil::RelativePoint(ptCenter2, GeoMetryUtil::PI() / 4, 4);
		ptTemp2 = GeoMetryUtil::RelativePoint(ptCenter2, GeoMetryUtil::PI() / 4, -4);
		ZrxCreateEntitys::CreateDimDiameteric(ptTemp1, ptTemp2, 0);

		//�����ע
		ZrxCreateEntitys::CreateDimOrdinate(ptCenter2, AcGeVector3d(0, -10, 0), AcGeVector3d(10, 0, 0));
	}
	static void zwzw_GetAllEntByLayer()
	{
		AcDbObjectIdArray allEntIds = CCADUtil::GetAllEntityIdsByLayerName(L"test");
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
		if (acedGetString(Adesk::kFalse, L"\n����ͼ������ƣ�", blkName) != RTNORM)
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
		pBlkTblRcd->appendZcDbEntity(entId, pLine1);
		pBlkTblRcd->appendZcDbEntity(entId, pLine2);
		pBlkTblRcd->appendZcDbEntity(entId, pCircle);

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
		if (acedGetString(Adesk::kFalse, L"\n����ͼ�������:", blkName) != RTNORM)
		{
			return;
		}
		//��ȡ��ǰ���ݿ�Ŀ��
		AcDbBlockTable *pBlkTbl = NULL;
		acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForWrite);
		//�����û�ָ���Ŀ鶨���Ƿ����
		CString strBlkDef;
		strBlkDef.Format(L"%s", blkName);
		if (!pBlkTbl->has(strBlkDef))
		{
			acutPrintf(L"\n��ǰͼ����δ����ָ�����ƵĿ鶨�壡");
			pBlkTbl->close();
			return;
		}
		//����û�����Ŀ���յĲ����
		ads_point pt;
		if (acedGetPoint(NULL, L"\n�������յĲ����:", pt) != RTNORM)
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
		ZrxCreateEntitys::PostToModelSpace(pBlkRef);
	}
	static void zwzw_InsertBlock2()
	{
		//��ȡ�û�ָ���Ŀ鶨���Ƿ����
		TCHAR blkName[40];
		if (acedGetString(Adesk::kFalse, L"\n����ͼ�������:", blkName) != RTNORM)
		{
			return;
		}
		AcDbObjectId blkDefId = CCADUtil::GetBlkDefId(blkName);
		if (blkDefId.isNull())
		{
			acutPrintf(L"\n��ǰͼ����δ����ָ�����ƵĿ鶨��");
			return;
		}

		//��ȡ�û�����Ŀ���յĲ����
		ads_point pt;
		if (acedGetPoint(NULL, L"\n�������յĲ����", pt) != RTNORM)
		{
			return;
		}
		AcGePoint3d ptInsert = asPnt3d(pt);

		//��������ն���
		AcDbBlockReference *pBlkRef = new AcDbBlockReference(ptInsert, blkDefId);

		//���������ӵ�ģ�Ϳռ�
		ZrxCreateEntitys::PostToModelSpace(pBlkRef);
	}
	static void zwzw_InsertBlock3()
	{
		//��ȡ�û�����Ŀ鶨������
		TCHAR blkName[40];
		if (acedGetString(Adesk::kFalse, L"\n����ͼ������:", blkName) != RTNORM)
		{
			return;
		}
		//�����û�ָ���Ŀ鶨���Ƿ����
		AcDbObjectId blkDefId = CCADUtil::GetBlkDefId(blkName);
		if (blkDefId.isNull())
		{
			acutPrintf(L"\n��ǰͼ����δ����ָ�����ƵĿ鶨�壡");
			return;
		}
		ads_point pt;
		if (acedGetPoint(NULL, L"\n�������յĲ����:", pt) != RTNORM)
		{
			return;
		}
		AcGePoint3d ptInsert = asPnt3d(pt);

		//�������գ�����ֵʹ��Ĭ��ֵ��
		AcDbObjectId blkRefId = CCADUtil::InsertBlockRefWithAttribute(blkDefId, ptInsert, 1, 0);
		
		//���ò���ֵ
		AcDbBlockReference *pBlkRef = NULL;
		if (acdbOpenObject(pBlkRef, blkRefId, AcDb::kForWrite) == Acad::eOk)
		{
			CCADUtil::SetBlockRefAttribute(pBlkRef, L"����", L"���ΰ�");
			CCADUtil::SetBlockRefAttribute(pBlkRef, L"����", L"2.3Kg");
			pBlkRef->close();
		}
	}
	static void zwzw_BlockIntersectWith()
	{
		//��ȡͼ�����ݿ�����Ҫ����Ŀ����
		AcDbObjectIdArray allEntIds = CCADUtil::GetAllEntityIds();
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
						CCADUtil::IntersectWith(pBlkRef, pLine, intPoints, false, false, false);
						//�������ú�ɫ��Բ���Ƴ���
						for (int j = 0; j < intPoints.length(); j++)
						{
							double radius = 4;
							AcDbObjectId circleId = ZrxCreateEntitys::CreateCircle(intPoints[j], radius);
							ZrxEditObject::SetColor(circleId, 1);
						}
						pLine->close();
					}
				}
			}
			pBlkRef->close();
		}

	}
} ;

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
