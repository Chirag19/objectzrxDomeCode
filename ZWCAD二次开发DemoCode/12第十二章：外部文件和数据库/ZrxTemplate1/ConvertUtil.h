#pragma once
class CConvertUtil
{
public:
	CConvertUtil();
	~CConvertUtil();

	static CString ToString(int val);

	//��ά��ת��ά��
	static AcGePoint2d ToPoint2d(const AcGePoint3d &point);
	//��ά��ת��Ϊ��ά��
	static AcGePoint3d ToPoint3d(const AcGePoint2d &point2d, double z = 0);
	//�Ƕ�ת����
	static double AngleToRadian(double angle);
	//����ת�Ƕ�
	static double RadianToAngle(double radian);

	// �ַ���ת��Ϊ�ض�������
	static double ToDouble(const TCHAR* str);

	//��������ת������ʾ����   wcs->dcs
	static AcGePoint3d WcsToDcsPoint(const AcGePoint3d &point);
	//�û�����ת������������	ucs->wcs
	static AcGePoint3d UcsToWcsPoint(const AcGePoint3d &point);
	//��������ת�����û�����	wcs->ucs
	static AcGePoint3d WcsToUcsPoint(const AcGePoint3d &point);
};

