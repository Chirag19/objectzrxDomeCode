#pragma once
class CCircleUtil
{
public:
	CCircleUtil();
	~CCircleUtil();

	//����Բ(������Բ�ġ��뾶)
	static AcDbObjectId Add(const AcGePoint3d &centerPoint, double radius);
	//����Բ(������ֱ�����˵�)
	static AcDbObjectId Add(const AcGePoint3d &pt1, const AcGePoint3d &pt2);
	//����Բ��������Բ�����㣩
	static AcDbObjectId Add(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &pt3);
	//����Բ��������Բ�����㣩
	static AcDbObjectId Add(const AcGePoint2d &pt1, const AcGePoint2d &pt2, const AcGePoint2d &pt3);
};

