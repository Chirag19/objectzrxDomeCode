#pragma once
class CHatchUtil
{
public:
	CHatchUtil();
	~CHatchUtil();

	//������䣨���������߽�ID���顢�����������������
	static AcDbObjectId Add(const AcDbObjectIdArray &loopIds, const TCHAR* patName, double patternScale);
};

