#pragma once
class CGeRectangleUtil
{
public:
	CGeRectangleUtil();
	~CGeRectangleUtil();

	//�ж����������Ƿ��ཻ
	static bool IntersectWithRectangle(const AcGePoint2d &rect1Point1, const AcGePoint2d &rect1Point2, const AcGePoint2d &rect2Point1, const AcGePoint2d &rect2Point2);
};

