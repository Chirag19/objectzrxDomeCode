#pragma once
class CArcBlockJigEntity : public AcDbEntity
{
public:
	// ����startPoint:��ʼ��; endPoint:��ֹ��; thirdPoint:������; blockId:���Id; 
	// count: �����ĸ���;
	CArcBlockJigEntity(const AcGePoint3d &startPoint, const AcGePoint3d &thirdPoint, const AcGePoint3d &endPoint,
		AcDbObjectId blkDefId, int count);
	virtual ~CArcBlockJigEntity();

	// �Զ���ʵ��Ļ��ƺ���
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);

	// ����Բ���յ��λ��
	void SetEndPoint(const AcGePoint3d &pt);

	// ��Բ���Ϳ���ӵ�ģ�Ϳռ�
	void PostToModelSpace();

	// �����ӵĿ���ռ���
	AcDbObjectIdArray GetBlkRefIds();

private:
	// ����ʵ�����ӵ�ģ�Ϳռ�
	void DrawOrAddSubEnts(AcGiWorldDraw* mode);

private:
	AcGePoint3d m_startPoint, m_endPoint, m_thirdPoint;	// Բ������㡢�յ�͵����㣨Բ����λ�������յ��м��һ�㣩
	AcDbObjectId m_blkDefId;		// �鶨��ID
	int m_blockCount;		// Ҫ���õĿ���յ�����
	AcDbObjectIdArray m_blkRefIds;		// ��ӵĿ���ռ���
};

