#include "stdafx.h"
#include "DoubleClickCircle.h"
#include "GetColorDlg.h"

CDoubleClickCircle::CDoubleClickCircle()
{
}


CDoubleClickCircle::~CDoubleClickCircle()
{
}

void CDoubleClickCircle::startEdit(AcDbEntity * pEnt, AcGePoint3d pt)
{
	//��õ�ǰ�ĵ�
	AcApDocument *pDoc = acDocManager->curDocument();

	//��AcDbEntityָ��ת��ΪAcDbCircleָ��
	if (pEnt->isKindOf(AcDbCircle::desc()))
	{
		AcDbCircle *pCircle = AcDbCircle::cast(pEnt);

		//�����ĵ�
		acDocManager->lockDocument(pDoc);

		//��ʵ��Ĵ�״̬����Ϊ��д״̬
		pCircle->upgradeOpen();

		//ָ���µ���ɫ
		//pCircle->setColorIndex(1);
		//pCircle->close();

		//��ʾ�û�����ָ�����µ���ɫ
		int oldColorIndex = pCircle->colorIndex();
		CAcModuleResourceOverride myResource;	//��ֹ��Դ��ͻ
		CGetColorDlg dlg;
		dlg.SetParams(oldColorIndex);
		if (dlg.DoModal() == IDOK)
		{
				
			int newColorIndex = 0;
			dlg.GetParams(newColorIndex);
			pCircle->setColorIndex(newColorIndex);
		}
		pCircle->close();

		//�����ĵ�
		acDocManager->unlockDocument(pDoc);

		//����PickFirstѡ���е�����
		acedSSSetFirst(NULL, NULL);

		//����ͼ����ʾ
		pCircle->draw();	//�ڹر�֮����ʹ��
		actrTransactionManager->flushGraphics();
		acedUpdateDisplay();
	}
	else
	{
		acutPrintf(_T("\n��Ч��AcDbCircle����..."));
		pEnt->close();
		return;
	}
}

void CDoubleClickCircle::finishEdit(void)
{
	//�˴�����
}
