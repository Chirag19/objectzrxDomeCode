#pragma once
class CDoubleClickCircle :
	public AcDbDoubleClickEdit
{
public:
	CDoubleClickCircle();
	virtual ~CDoubleClickCircle();

	//��ʼ�༭ʱ���õĺ���
	void startEdit(AcDbEntity *pEnt, AcGePoint3d pt);

	//��ɱ༭֮����õĺ���
	void finishEdit(void);

};

