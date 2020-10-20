#pragma once
class CArcBlockJig : AcEdJig
{
public:
	CArcBlockJig();
	virtual ~CArcBlockJig();

	// ����startPoint:��ʼ��; endPoint:��ֹ��; thirdPoint:������; blkDefId:���Id; 
	// blockCount: �����ĸ���;
	bool doIt(const AcGePoint3d &startPoint, AcGePoint3d &thirdPoint, AcGePoint3d &endPoint,
		AcDbObjectId blkDefId, int blockCount);
	virtual AcEdJig::DragStatus sampler();		// �˺�������drag���������Ի��һ������
	virtual Adesk::Boolean update();
	virtual AcDbEntity* entity() const;			// ָ����Jig�������Ķ���

												// ��ȡJig�����ɹ������Ŀ���ռ���
	AcDbObjectIdArray GetBlkRefIds();

private:
	CArcBlockJigEntity* m_pJigEnt;
	AcGePoint3d m_curPoint;
	AcDbObjectIdArray m_blkRefIds;
};

