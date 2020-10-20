#include "stdafx.h"
#include "DrawSquareJig.h"


CDrawSquareJig::CDrawSquareJig()
{
	m_pPoly = NULL;
}


CDrawSquareJig::~CDrawSquareJig()
{
}

bool CDrawSquareJig::doIt(const AcGePoint3d & centerPoint, AcDbObjectId & polyId)
{
	m_centerPoint = centerPoint;

	//�϶���ʼֵǮ��������ߴ�������
	m_pPoly = new AcDbPolyline();
	for (int i = 0; i < 4; i++)
	{
		m_pPoly->addVertexAt(i, CConvertUtil::ToPoint2d(m_centerPoint));
	}
	m_pPoly->setClosed(Adesk::kTrue);

	//�����϶�����
	CString prompt = _T("\nָ����ע�����:");
	setDispPrompt(prompt);
	AcEdJig::DragStatus stat = drag();

	//�϶�����������������
	if (stat == kNormal)
	{
		polyId = CDwgDatabaseUtil::PostToModelSpace(m_pPoly);
		return true;
	}
	else
	{
		delete m_pPoly;
		return false;
	}
}

AcEdJig::DragStatus CDrawSquareJig::sampler()
{
	setUserInputControls((UserInputControls)(AcEdJig::kAccept3dCoordinates | AcEdJig::kNoNegativeResponseAccepted | AcEdJig::kNullResponseAccepted));

	//һ��Ҫ�ж���һ���Ƿ����˱仯������update������ͣ�ı����ã�ʵ�巴�����ܱ����Ƴ���
	static AcGePoint3d pointTemp;
	DragStatus stat = acquirePoint(m_curPoint);
	if (pointTemp != m_curPoint)
	{
		pointTemp = m_curPoint;
	}
	else if (stat == AcEdJig::kNormal)
	{
		return AcEdJig::kNoChange;
	}
	return stat;
}

Adesk::Boolean CDrawSquareJig::update()
{
	//ʵ����ĸ��²�������������µ���m_pPoly
	double dist = CConvertUtil::ToPoint2d(m_centerPoint).distanceTo(CConvertUtil::ToPoint2d(m_curPoint));
	for (int i = 0; i < 4; i++)
	{
		double angle = i*CMathUtil::PI()*0.5 + CMathUtil::PI()*0.25;
		AcGePoint2d pt = CGePointUtil::PolarPoint(CConvertUtil::ToPoint2d(m_centerPoint), angle, dist);
		m_pPoly->setPointAt(i, pt);
	}
	return Adesk::kTrue;
}

AcDbEntity * CDrawSquareJig::entity() const
{
	return m_pPoly;
}
