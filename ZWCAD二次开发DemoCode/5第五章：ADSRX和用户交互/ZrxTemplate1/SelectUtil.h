#pragma once
class CSelectUtil
{
public:
	CSelectUtil();
	~CSelectUtil();

	//��ȡ��ǰͼ����λ�ڸ������η�Χ�ڵ�����ʵ��(��ʵ��İ�Χ������ж�
	static void GetEntityInRectangle(const AcGePoint2d &firstPoint, const AcGePoint2d &secondPoint, AcDbObjectIdArray &entIds);
	//��ʾ�û�ѡ����ʵ�壨���ˣ�
	static bool PromptSelectEnts(const TCHAR *prompt, struct resbuf * rb, AcDbObjectIdArray &entIds);
	//��ʾ�û�ѡ����ʵ�壨�޶�����ʵ�����ͣ�
	static bool PromptSelectEnts(const TCHAR *prompt, const std::vector<AcRxClass*> &classDescs, AcDbObjectIdArray &entIds);
	//��ʾ�û�ѡ����ʵ�壨�޶�һ��ʵ�����ͣ�
	static bool PromptSelectEnts(const TCHAR *prompt, AcRxClass* &classDesc, AcDbObjectIdArray &entIds);
	//��ʾ�û�ѡ��һ��ʵ�壨�޶�����ʵ�����ͣ�
	static bool PromptSelectEntity(const TCHAR *prompt, const std::vector<AcRxClass*> &classDescs, AcDbEntity * &pEnt,AcGePoint3d &pickPoint,bool bOpenFoeWrite=true);
	//��ʾ�û�ѡ��һ��ʵ�壨�޶�һ��ʵ�����ͣ�
	static bool PromptSelectEntity(const TCHAR *prompt, AcRxClass* &classDesc, AcDbEntity * &pEnt, AcGePoint3d &pickPoint, bool bOpenFoeWrite = true);


};

