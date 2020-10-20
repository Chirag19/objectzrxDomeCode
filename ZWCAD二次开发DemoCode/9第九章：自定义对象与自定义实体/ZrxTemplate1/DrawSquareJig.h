#pragma once
class CDrawSquareJig :AcEdJig
{
public:
	CDrawSquareJig();
	~CDrawSquareJig();

	//�ⲿ���õĺ�����һ������jig�ĳ�ʼ��
	bool doIt(const AcGePoint3d &centerPoint,AcDbObjectId &polyId);

	//�˺�������drag���������Ի���û�����
	virtual AcEdJig::DragStatus sampler();

	//����Ҫ���϶������з�����ʵ������޸�
	virtual Adesk::Boolean update();

	//ָ��jig�������Ķ���
	virtual AcDbEntity *entity() const;

private:
	AcDbPolyline *m_pPoly;	//�϶������ж�̬�仯��ʵ��
	AcGePoint3d m_curPoint;	//�����û�����ƶ�ʱ�����ʱλ��
	AcGePoint3d m_centerPoint;	//�����ε����ĵ�

};

