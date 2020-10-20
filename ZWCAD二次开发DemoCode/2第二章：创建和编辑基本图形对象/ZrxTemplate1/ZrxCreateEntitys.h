#pragma once
#include <gedxfio.h>
class ZrxCreateEntitys
{
public:
	ZrxCreateEntitys();
	~ZrxCreateEntitys();
public:
	//���ʵ�嵽ģ�Ϳռ�
	static AcDbObjectId PostToModelSpace(AcDbEntity *pEnt);


	//����ֱ�ߣ���������㡢�յ㣩
	static AcDbObjectId CreateLine(AcGePoint3d ptStart, AcGePoint3d ptEnd);


	//����Բ(������Բ�ġ��뾶)
	static AcDbObjectId CreateCircle(const AcGePoint3d &centerPoint,double radius );
	//����Բ(������ֱ�����˵�)
	static AcDbObjectId CreateCircle(const AcGePoint3d &pt1, const AcGePoint3d &pt2);
	//����Բ��������Բ�����㣩
	static AcDbObjectId CreateCircle(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &pt3);
	//����Բ��������Բ�����㣩
	static AcDbObjectId CreateCircle(const AcGePoint2d &pt1, const AcGePoint2d &pt2, const AcGePoint2d &pt3);


	//����Բ����������Բ�ġ�ƽ�淨�������뾶����ʼ�Ƕȡ���ֹ�Ƕȣ�
	static AcDbObjectId CreateArc(const AcGePoint3d &ptCenter, const AcGeVector3d &vec, double radius, double startAngle, double endAngle);
	//��XOYƽ�洴��Բ����������Բ�ġ��뾶����ʼ�Ƕȡ���ֹ�Ƕȣ�
	static AcDbObjectId CreateArc(const AcGePoint2d &ptCenter, double radius, double startAngle, double endAngle);
	//����Բ��  ������1����㡢�յ㡢Բ�� or ����2����㡢�յ㡢����һ�㣩
	static AcDbObjectId CreateArc(const AcGePoint2d &ptStart, const AcGePoint2d &ptCenter_or_ptOnArc, const AcGePoint2d &ptEnd, BOOL flay = TRUE);
	//����Բ������������㡢Բ�ġ�Բ���Ƕȣ�
	static AcDbObjectId CreateArc(const AcGePoint2d &ptStart, const AcGePoint2d &ptCenter, double angle);


	//��������ߣ���������ߣ����������㼯����ȣ�
	static AcDbObjectId CreatePolyLine(const AcGePoint2dArray &points, double width = 0);
	//��������ߣ�һ��ֱ�ߣ�(��������ʼ�㡢��ʼ�㡢�߿�)
	static AcDbObjectId CreatePolyOneLine(const AcGePoint2d &ptStart, const AcGePoint2d &ptEnd, double width);
	//������ά����ߣ��������㼯��
	static AcDbObjectId Create3dPolyLine(const AcGePoint3dArray &points);
	//����������Σ����������ġ����������Բ�뾶����ת�Ƕȣ�����ֵ�����߿����ɶ���߹�����
	static AcDbObjectId CreatePolygon(const AcGePoint2d &ptCenter, int number,double radius, double rotation, double width);
	//�������Σ������������ǵ㡢�߿����ɶ���߹�����
	static AcDbObjectId CreatePolyRectangle(const AcGePoint2d &pt1, const AcGePoint2d &pt2, double width);
	//����Բ��������Բ�ġ��뾶���߿����ɶ���߹�����
	static AcDbObjectId CreatePolyCircle(const AcGePoint2d &ptCenter, double radius, double width);
	//����Բ����������Բ�ġ��뾶����ʼ�Ƕȡ���ֹ�Ƕȡ��߿����ɶ���߹�����
	static AcDbObjectId CreatePolyArc(const AcGePoint2d &ptCenter, double radius ,double angleStart, double angleEnd, double width);

	//������Բ(����:��Բ���ġ�ƽ�淨������1/2����ʸ��������/�������)
	static AcDbObjectId CreateEillpse(const AcGePoint3d &ptCenter, const AcGeVector3d &vecNormal, const AcGeVector3d &majorAxis, double ratio);
	//������Բ����������Ӿ��ε������ǵ㣩
	static AcDbObjectId CreateEillpse(const AcGePoint2d &pt1, const AcGePoint2d &pt2);


	//�����������ߣ���������ϵ㡢���������������
	static AcDbObjectId CreateSpline(const AcGePoint3dArray &points, int order = 4, double fitTolerance = 0.0);
	//�����������ߣ���������ϵ㡢������߷����յ����߷��򡢽��������������
	static AcDbObjectId CreateSpline(const AcGePoint3dArray &points, const AcGeVector3d &startTangent, const AcGeVector3d &endTangent, int order = 4, double fitTolerance = 0.0);

	
	//�������򣨲���������������������ID���飩
	static AcDbObjectIdArray CreateRegion(const AcDbObjectIdArray &curveIds);


	//�������֣�����������㡢�������ݡ�������ʽID�����ָ߶ȡ����ֵ���ת�Ƕȣ�
	static AcDbObjectId CreateText(const AcGePoint3d &ptInsert, const TCHAR* text, AcDbObjectId style = AcDbObjectId::kNull , double height = 2.5, double rotation=0);
	//�����������֣�����������㡢�����������ݡ�������ʽID�����ָ߶ȡ���ȣ�
	static AcDbObjectId CreateMText(const AcGePoint3d &ptInsert, const TCHAR* text, AcDbObjectId style = AcDbObjectId::kNull, double height = 2.5, double width = 10);


	//������䣨���������߽�ID���顢�����������������
	static AcDbObjectId CreateHatch(const AcDbObjectIdArray &loopIds, const TCHAR* patName, double patternScale);


	//���������ע����������һ���ߴ�߽��ߵ���㡢�ڶ����ߴ�߽��ߵ���㡢ͨ���ߴ��ߵ�һ�㡢��ע���֡�������ʽ��
	static AcDbObjectId CreateDimAligned(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//���������ע����������һ���ߴ�߽��ߵ���㡢�ڶ����ߴ�߽��ߵ���㡢ͨ���ߴ��ߵ�һ�㡢����ƫ��������ע���֡�������ʽ��
	static AcDbObjectId CreateDimAligned(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine,const AcGeVector3d &vecOffset=AcGeVector3d::kIdentity, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//����ת�Ǳ�ע����������ע����ת�Ƕȡ���һ���ߴ�߽��ߵ���㡢�ڶ����ߴ�߽��ߵ���㡢ͨ���ߴ��ߵ�һ�㡢��ע���֡�������ʽ��
	static AcDbObjectId CreateDimRotated(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &ptLine, double rotation, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//�����뾶��ע�����������ߵ����ĵ㡢���߸������ꡢ���߳��ȡ���ע���֡�������ʽ��
	static AcDbObjectId CreateDimRadial(const AcGePoint3d &ptCenter, const AcGePoint3d &ptChord, double leaderLength, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//�����뾶��ע��������Բ�ġ��뾶���ߴ�����ת�Ƕȡ����߳��ȣ�
	static AcDbObjectId CreateDimRadial(const AcGePoint3d &ptCenter, double radius, double angle, double leaderLength = 5);
	//����ֱ����ע��������ֱ���������˵㣬���߳��ȡ���ע���֡�������ʽ��
	static AcDbObjectId CreateDimDiameteric(const AcGePoint3d &ptChord1, const AcGePoint3d &ptChord2, double leaderLength, const TCHAR* dimText=NULL, AcDbObjectId dimStyle=AcDbObjectId::kNull);
	//����ֱ����ע��������Բ�ġ��뾶���ߴ��ע�ߵ���ת�Ƕȡ����߳��ȣ�
	static AcDbObjectId CreateDimDiameteric(const AcGePoint3d &ptCenter, double radius , double angle, double leaderLength=5);
	//�����Ƕȱ�ע����������������ֱ�ߵĹ�ϵ������
	static AcDbObjectId CreateDim2LineAngular(const AcGePoint3d &ptStart1, const AcGePoint3d &ptEnd1, const AcGePoint3d &ptStart2, const AcGePoint3d &ptEnd2, const AcGePoint3d &ptArc, const TCHAR* dimText, AcDbObjectId dimStyle);
	//�����Ƕȱ�ע�����������㡢��ʼ�㡢��ֹ�㡢��ע�ߴ���ͨ���㣩
	static AcDbObjectId CreateDim3PtAngular(const AcGePoint3d &ptCenter, const AcGePoint3d &ptEnd1, const AcGePoint3d &ptEnd2, const AcGePoint3d &ptArc, const TCHAR* dimText = NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//���������ע���������Ƿ���X���ע����ע��ͷ����ʼλ�á���ע��ͷ����ֹλ�á���ע���֡�������ʽ��
	static AcDbObjectId CreateDimOrdinate(Adesk::Boolean xAxis, const AcGePoint3d &ptStart, const AcGePoint3d &ptEnd, const TCHAR* dimText=NULL, AcDbObjectId dimStyle = AcDbObjectId::kNull);
	//���������ע��ͬʱ����һ�����X��Y�����ע��
	static AcDbObjectIdArray CreateDimOrdinate(const AcGePoint3d &ptDef, const AcGePoint3d &ptTextX, const AcGePoint3d &ptTextY);
	//���������ע����������ע����㡢Xƫ������Yƫ������
	static AcDbObjectIdArray CreateDimOrdinate(const AcGePoint3d &ptDef, const AcGeVector3d &vecOffsetX, const AcGeVector3d &vecOffsetY);



};

