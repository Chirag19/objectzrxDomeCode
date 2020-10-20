#pragma once

class CEntInfoTipHandler : public AcEdInputPointMonitor
{
public:
	CEntInfoTipHandler(const bool storeInDocVars = true, ZcApDocument* pDoc = curDoc());
	virtual ~CEntInfoTipHandler();

	// ������Ҫ���Զ���׽���ų���ʵ��
	virtual bool excludeFromOsnapCalculation(const AcArray<AcDbObjectId>& nestedEntity,
		int gsSelectionMark);

	// ����������Ϣ
	virtual Acad::ErrorStatus monitorInputPoint(
		bool&                             appendToTooltipStr,
		ZTCHAR*&                            additionalTooltipString,

		ZcGiViewportDraw*                   drawContext,

		ZcApDocument*                       document,
		bool                                pointComputed,
		int                                 history,
		const ZcGePoint3d&                  lastPoint,
		const ZcGePoint3d&                  rawPoint,
		const ZcGePoint3d&                  grippedPoint,
		const ZcGePoint3d&                  cartesianSnappedPoint,
		const ZcGePoint3d&                  osnappedPoint,
		ZcDb::OsnapMask                     osnapMask,
		const ZcArray<ZcDbCustomOsnapMode*>& customOsnapModes,
		ZcDb::OsnapMask                     osnapOverrides,
		const ZcArray<ZcDbCustomOsnapMode*>& customOsnapOverrides,
		const ZcArray<ZcDbObjectId>&        apertureEntities,
		const ZcArray< ZcDbObjectIdArray, ZcArrayObjectCopyReallocator< ZcDbObjectIdArray > >&
		nestedApertureEntities,
		const ZcArray<ZSoft::GsMarker>&     gsSelectionMark,
		const ZcArray<ZcDbObjectId>&        keyPointEntities,
		const ZcArray< ZcDbObjectIdArray, ZcArrayObjectCopyReallocator< ZcDbObjectIdArray > >&
		nestedKeyPointEntities,
		const ZcArray<ZSoft::GsMarker>&     keyPointGsSelectionMark,
		const ZcArray<ZcGeCurve3d*>&        alignmentPaths,
		const ZcGePoint3d&                  computedPoint,
		const ZTCHAR*                         tooltipString);

private:
	// ָ����������������ĵ�
	ZcApDocument* m_pDoc;
};

