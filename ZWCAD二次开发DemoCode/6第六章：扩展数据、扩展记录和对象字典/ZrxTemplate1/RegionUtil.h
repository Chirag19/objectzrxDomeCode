#pragma once
class CRegionUtil
{
public:
	CRegionUtil();
	~CRegionUtil();

	//�������򣨲���������������������ID���飩
	static AcDbObjectIdArray Add(const AcDbObjectIdArray &curveIds);
};

