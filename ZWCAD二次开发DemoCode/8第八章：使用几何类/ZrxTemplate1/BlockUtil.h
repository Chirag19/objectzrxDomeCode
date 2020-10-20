#pragma once
class CBlockUtil
{
public:
	CBlockUtil();
	~CBlockUtil();

	//�������գ��������鶨��ID������㡢���ű�������ת�Ƕȣ�
	static AcDbObjectId InsertBlockRef(AcDbObjectId blkDefId, const AcGePoint3d &insertPoint, double scale, double rotation);
	//�޸Ĳ������յĲ������
	static void SetScaleFactor(AcDbBlockReference *pBlkRef, double scale);
	// ���ָ�����ƵĿ鶨��
	static AcDbObjectId GetBlkDefId(const TCHAR* blkDefName, AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase());

	//����һ�����������Զ����ͼ�飬���е�����ֵʹ�ö������Զ����Ĭ��ֵ
	static AcDbObjectId InsertBlockRefWithAttribute(const AcDbObjectId &blkDefId, const AcGePoint3d &insertPoint, double scale, double rotation);
	//��������Ĳ����е����Զ��壬���������Զ���ƥ������Զ��󣬽�����ӵ�����Ŀ����
	static void AppendAttributeToBlkRef(AcDbBlockReference *pBlkRef, AcDbAttributeDefinition *pAttDef);
	//�޸Ŀ�������ض����Ƶ����Զ�����ַ�������
	static bool SetBlockRefAttribute(AcDbBlockReference *pBlikRef, const TCHAR *tag, const TCHAR *val);
	//�ӿ��������ȡ����ֵ
	static bool GetAttributeValue(AcDbBlockReference *pBlkRef, const TCHAR *tag, CString &value);
	//��ȡ����պ�����ʵ���ཻ����ʵ�ཻ
	static void IntersectWith(AcDbBlockReference *pBlkRef, AcDbEntity *pEnt, AcGePoint3dArray &intPonts, bool bIntersectWithText = true, bool bProjectToXOY = false, bool bExtendEntArg = false);

	// ����: ��������DWGͼ�θ���һ���鶨�嵽��ǰͼ��
	// ����: const TCHAR * fileName, Dwg�ļ�����ȫ·����
	// ����: const TCHAR * blkDefName, �鶨�������
	// ����ֵ:   AcDbObjectId, ���Ƶ���ǰͼ���ж�Ӧ�Ŀ鶨��ID(�����ǰͼ���д���ͬ���Ŀ鶨�壬ֱ�ӷ��ص�ǰͼ����ͬ���Ŀ鶨���ID)
	static AcDbObjectId CopyBlockDefFromOtherDwg(const TCHAR* fileName, const TCHAR* blkDefName);

	// ��DWG�ļ���Ϊ�鶨����뵽ָ����ͼ�����ݿ�
	// bOverwriteIfExist: ���ָ����ͼ�����ݿ����Ѿ�������ͬ���Ŀ飬�Ƿ񸲸�ԭ�еĶ���
	static AcDbObjectId InsertDwgBlockDef(const TCHAR* dwgFileName, const TCHAR* blkName, bool bOverwriteIfExist,AcDbDatabase *pDb=acdbHostApplicationServices()->workingDatabase());


};

