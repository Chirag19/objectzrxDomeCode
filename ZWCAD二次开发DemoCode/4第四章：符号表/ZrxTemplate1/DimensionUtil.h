#pragma once
class CDimensionUtil
{
public:
	CDimensionUtil();
	~CDimensionUtil();


	//���������ע����������һ���ߴ�߽��ߵ���㡢�ڶ����ߴ�߽��ߵ���㡢ͨ���ߴ��ߵ�һ�㡢��ע���֡�������ʽ��
	static AcDbObjectId AddDimAligned(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//���������ע����������һ���ߴ�߽��ߵ���㡢�ڶ����ߴ�߽��ߵ���㡢ͨ���ߴ��ߵ�һ�㡢����ƫ��������ע���֡�������ʽ��
	static AcDbObjectId AddDimAligned(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine, const AcGeVector3d &vecOffset = AcGeVector3d::kIdentity, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//����ת�Ǳ�ע����������ע����ת�Ƕȡ���һ���ߴ�߽��ߵ���㡢�ڶ����ߴ�߽��ߵ���㡢ͨ���ߴ��ߵ�һ�㡢��ע���֡�������ʽ��
	static AcDbObjectId AddDimRotated(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine, double rotation, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//�����뾶��ע�����������ߵ����ĵ㡢���߸������ꡢ���߳��ȡ���ע���֡�������ʽ��
	static AcDbObjectId AddDimRadial(const AcGePoint3d &ptCenter, const AcGePoint3d &ptChord, double leaderLength, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//�����뾶��ע��������Բ�ġ��뾶���ߴ�����ת�Ƕȡ����߳��ȣ�
	static AcDbObjectId AddDimRadial(const AcGePoint3d &ptCenter, double radius, double angle, double leaderLength = 5);
	//����ֱ����ע��������ֱ���������˵㣬���߳��ȡ���ע���֡�������ʽ��
	static AcDbObjectId AddDimDiameteric(const AcGePoint3d &ptChord1, const AcGePoint3d &ptChord2, double leaderLength, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//����ֱ����ע��������Բ�ġ��뾶���ߴ��ע�ߵ���ת�Ƕȡ����߳��ȣ�
	static AcDbObjectId AddDimDiameteric(const AcGePoint3d &ptCenter, double radius, double angle, double leaderLength = 5);
	//�����Ƕȱ�ע����������������ֱ�ߵĹ�ϵ������
	static AcDbObjectId AddDim2LineAngular(const AcGePoint3d &ptStart1, const AcGePoint3d &ptEnd1, const AcGePoint3d &ptStart2, const AcGePoint3d &ptEnd2, const AcGePoint3d &ptArc, const TCHAR* dimText, AcDbObjectId dimStyle);
	//�����Ƕȱ�ע�����������㡢��ʼ�㡢��ֹ�㡢��ע�ߴ���ͨ���㣩
	static AcDbObjectId AddDim3PtAngular(const AcGePoint3d &ptCenter, const AcGePoint3d &ptEnd1, const AcGePoint3d &ptEnd2, const AcGePoint3d &ptArc, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//���������ע���������Ƿ���X���ע����ע��ͷ����ʼλ�á���ע��ͷ����ֹλ�á���ע���֡�������ʽ��
	static AcDbObjectId AddDimOrdinate(Adesk::Boolean xAxis, const AcGePoint3d &ptStart, const AcGePoint3d &ptEnd, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//���������ע��ͬʱ����һ�����X��Y�����ע��
	static AcDbObjectIdArray AddDimOrdinate(const AcGePoint3d &ptDef, const AcGePoint3d &ptTextX, const AcGePoint3d &ptTextY);
	//���������ע����������ע����㡢Xƫ������Yƫ������
	static AcDbObjectIdArray AddDimOrdinate(const AcGePoint3d &ptDef, const AcGeVector3d &vecOffsetX, const AcGeVector3d &vecOffsetY);
};

