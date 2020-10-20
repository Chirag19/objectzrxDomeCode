#include "stdafx.h"
#include "ViewUtil.h"


CViewUtil::CViewUtil()
{
}


CViewUtil::~CViewUtil()
{
}

void CViewUtil::GetCurrentView(AcDbViewTableRecord &view)
{
	struct resbuf rb;
	struct resbuf wcs, ucs, dcs;	//ת������ʱʹ�õ�����ϵͳ���
	
	wcs.restype = RTSHORT;	//��������ϵ
	wcs.resval.rint = 0;

	ucs.restype = RTSHORT;	//�û�����ϵ
	ucs.resval.rint = 1;
		
	dcs.restype = RTSHORT;	//��ʾ����ϵ
	dcs.resval.rint = 2;

	//��ȡ��ǰ�ӿڵġ��鿴��ģʽ
	acedGetVar(_T("VIEWMODE"), &rb);
	view.setPerspectiveEnabled((rb.resval.rint & 1) != 0);
	view.setFrontClipEnabled((rb.resval.rint & 2) != 0);
	view.setBackClipEnabled((rb.resval.rint & 3) != 0);
	view.setFrontClipEnabled((rb.resval.rint & 16) == 0);

	//��ǰ�ӿ�����ͼ�����ĵ㣨UCS���꣩
	acedGetVar(_T("VIEWCTR"), &rb);
	acedTrans(rb.resval.rpoint, &ucs, &dcs, 0, rb.resval.rpoint);
	view.setCenterPoint(AcGePoint2d(rb.resval.rpoint[X], rb.resval.rpoint[Y]));

	//��ǰ�ӿ�͸��ͼ�еľ�ͷ���೤�ȣ���λ���ף�
	acedGetVar(_T("LENSLENGTH"),&rb);
	view.setLensLength(rb.resval.rreal);

	//��ǰ�ӿ���Ŀ����λ��(��USC�����ʾ)
	acedGetVar(_T("TARGET"), &rb);
	acedTrans(rb.resval.rpoint, &ucs, &wcs, 0, rb.resval.rpoint);
	view.setTarget(AcGePoint3d(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]));

	//�����ӿڵ���ͼ�߶ȣ�ͼ�ε�λ��
	acedGetVar(_T("VIEWSIZE"), &rb);
	view.setHeight(rb.resval.rreal);
	double height = rb.resval.rreal;

	//������Ϊ��λ�ĵ�ǰ�ӿڵĴ�С��X��Yֵ��
	acedGetVar(_T("SCREENSIZE"), &rb);
	view.setWidth(rb.resval.rpoint[X] / rb.resval.rpoint[Y] * height);

	//��ǰ�ӿڵ���ͼŤת��
	acedGetVar(_T("VIEWTWIST"), &rb);
	view.setViewTwist(rb.resval.rreal);

	//��ģ��ѡ������һ������ѡ���Ϊ��ǰ
	acedGetVar(_T("TILEMODE"), &rb);
	int tileMode = rb.resval.rint;
	//���õ�ǰ�ӿڱ�ʶ��
	acedGetVar(_T("CVPORT"), &rb);
	int cvport = rb.resval.rint;

	//�Ƿ���ģ�Ϳռ����ͼ
	bool paperspace = ((tileMode == 0) && (cvport == 1) ? true : false);
	view.setIsPaperspaceView(paperspace);

	if (!paperspace)
	{
		//��ǰ�ӿ�����ǰ�ü�ƽ�浽Ŀ��ƽ���ƫ����
		acedGetVar(_T("FRONTZ"), &rb);
		view.setFrontClipDistance(rb.resval.rreal);
		
		//��õ�ǰ�ӿں���ü�ƽ�浽Ŀ��ƽ���ƫ����
		acedGetVar(_T("BACKZ"), &rb);
		view.setBackClipDistance(rb.resval.rreal);
	}
	else
	{
		view.setFrontClipDistance(0.0);
		view.setBackClipDistance(0.0);
	}
}

void CViewUtil::Set(const AcGePoint3d & pMin, const AcGePoint3d & pMax, double scale)
{
	AcDbViewTableRecord view;
	GetCurrentView(view);

	//�����������������������ת������ʾ����ϵ
	AcGePoint3d ptMinDcs = CConvertUtil::WcsToDcsPoint(pMin);
	AcGePoint3d ptMaxDcs = CConvertUtil::WcsToDcsPoint(pMax);

	//������ͼ�����ĵ�
	view.setCenterPoint(AcGePoint2d((ptMinDcs.x + ptMaxDcs.x) / 2, (ptMinDcs.y + ptMaxDcs.y) / 2));

	//������ͼ�ĸ߶ȺͿ��
	view.setHeight(fabs(ptMinDcs.x - ptMaxDcs.x));
	view.setWidth(fabs(ptMinDcs.y - ptMaxDcs.y));

	//����ͼ��������Ϊ��ǰ��ͼ
	acedSetCurrentView(&view, NULL);
}

void CViewUtil::SetCenter(const AcGePoint3d & center)
{
	AcDbViewTableRecord view;
	GetCurrentView(view);

	//�������ĵ����������ת������ʾ����ϵ
	AcGePoint3d centerDcs = CConvertUtil::WcsToDcsPoint(center);

	//������ͼ�����ĵ�
	view.setCenterPoint(CConvertUtil::ToPoint2d( centerDcs));

	//����ͼ��������Ϊ��ǰ��ͼ
	acedSetCurrentView(&view, NULL);
}

void CViewUtil::ZoomExtent()
{
	//��ȡ��ǰͼ��������ʵ�����С��Χ��
	AcDbBlockTable *pBlkTbl;
	AcDbBlockTableRecord *pBlkTblRcd;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForRead);
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForRead);
	pBlkTbl->close();

	AcDbExtents extent;		//ģ�Ϳռ�İ�Χ��
	extent.addBlockExt(pBlkTblRcd);
	pBlkTblRcd->close();

	//��Χ���ǳ����壬�����屻�任��DCS��֮��ÿ�����㶼�п����������С�ǵ�
	ZcGePoint3dArray verts;
	verts.append(extent.minPoint());
	verts.append(AcGePoint3d(extent.maxPoint().x, extent.minPoint().y, extent.minPoint().z));
	verts.append(AcGePoint3d(extent.maxPoint().x, extent.maxPoint().y, extent.minPoint().z));
	verts.append(AcGePoint3d(extent.minPoint().x, extent.maxPoint().y, extent.minPoint().z));
	verts.append(AcGePoint3d(extent.minPoint().x, extent.minPoint().y, extent.maxPoint().z));
	verts.append(AcGePoint3d(extent.maxPoint().x, extent.minPoint().y, extent.maxPoint().z));
	verts.append(extent.maxPoint());
	verts.append(AcGePoint3d(extent.minPoint().x, extent.maxPoint().y, extent.maxPoint().z));
	
	//������������нǵ�ת�Ƶ�DCS��
	for (int i = 0; i < verts.length(); i++)
	{
		verts[i] = CConvertUtil::WcsToDcsPoint(verts[i]);
	}

	//��ȡ���нǵ���DCS����С�İ�Χ����
	double xmin = 1.0E30, ymin = 1.0E30;
	double xmax = -1.0E30, ymax = -1.0E30;
	for (int i = 0; i < verts.length(); i++)
	{
		xmin = min(xmin, verts[i].x);
		ymin = min(ymin, verts[i].y);
		xmax = max(xmax, verts[i].x);
		ymax = max(ymax, verts[i].y);
	}

	AcDbViewTableRecord view;
	GetCurrentView(view);

	//�������ĵ�
	view.setCenterPoint(AcGePoint2d((xmin + xmax) / 2, (ymin + ymax) / 2));

	//������ͼ�ĸ߶ȺͿ��
	view.setHeight(fabs(ymax - ymin));
	view.setWidth(fabs(xmax - xmin));

	//����ͼ��������Ϊ��ǰ��ͼ
	Acad::ErrorStatus es = acedSetCurrentView(&view, NULL);
}
