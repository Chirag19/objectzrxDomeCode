#pragma once
class CMathUtil
{
public:
	CMathUtil();
	~CMathUtil();

	//PI
	static double PI();

	// �ж��������Ƿ����
	static bool IsEqual(double a, double b, double tol = 1.0E-7);

	// ��ȡ��������֮��������
	// ע�����֮ǰ��Ӧ��ִ��һ�� srand((unsigned)time(NULL));
	static int GetRand(int minValue, int maxValue);

	// ��һ��������ָ����С��λ��������������
	static double Round(double a, int precision);
	static int Round(double a);
};

