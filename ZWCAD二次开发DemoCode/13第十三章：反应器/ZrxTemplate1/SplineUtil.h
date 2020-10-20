#pragma once
class CSplineUtil
{
public:
	CSplineUtil();
	~CSplineUtil();

	//�����������ߣ���������ϵ㡢���������������
	static AcDbObjectId Add(const AcGePoint3dArray &points, int order = 4, double fitTolerance = 0.0);
	//�����������ߣ���������ϵ㡢������߷����յ����߷��򡢽��������������
	static AcDbObjectId Add(const AcGePoint3dArray &points, const AcGeVector3d &startTangent, const AcGeVector3d &endTangent, int order = 4, double fitTolerance = 0.0);
};

