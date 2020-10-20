#pragma once
class CEntityUtil
{
public:
	CEntityUtil();
	~CEntityUtil();

	//�޸�ʵ����ɫ
	static Acad::ErrorStatus SetColor(AcDbObjectId entId, Adesk::UInt16 colorIndex);
	//�޸�ʵ��ͼ��
	static void SetLayer(AcDbObjectId entId, CString strLayer);
	//�޸�ʵ������
	static void SetLineType(AcDbObjectId entId, CString strLineType);
	//����ָ���ĽǶȣ��û���ֵ��ʾ����תָ����ʵ��
	static Acad::ErrorStatus Rotate(AcDbObjectId entId, const AcGePoint2d &ptBase, double rotation);
	//�ƶ�ʵ��
	static Acad::ErrorStatus Move(AcDbObjectId entId, const AcGePoint3d &ptBase, const AcGePoint3d &ptDest);
	//����ʵ��
	static Acad::ErrorStatus Scale(AcDbObjectId entId, const AcGePoint3d &ptBase, double scaleFactor);
};

