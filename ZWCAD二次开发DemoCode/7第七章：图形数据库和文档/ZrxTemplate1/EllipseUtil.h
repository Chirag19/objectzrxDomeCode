#pragma once
class CEllipseUtil
{
public:
	CEllipseUtil();
	~CEllipseUtil();

	//������Բ(����:��Բ���ġ�ƽ�淨������1/2����ʸ��������/�������)
	static AcDbObjectId Add(const AcGePoint3d &ptCenter, const AcGeVector3d &vecNormal, const AcGeVector3d &majorAxis, double ratio);
	//������Բ����������Ӿ��ε������ǵ㣩
	static AcDbObjectId Add(const AcGePoint2d &pt1, const AcGePoint2d &pt2);
};

