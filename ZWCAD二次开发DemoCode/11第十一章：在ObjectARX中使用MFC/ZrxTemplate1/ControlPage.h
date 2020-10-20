#pragma once
#include "resource.h"

// CControlPage �Ի���

class CControlPage : public CZcUiTabChildDialog
{
	DECLARE_DYNAMIC(CControlPage)

public:
	CControlPage(CWnd* pParent = NULL,HINSTANCE hInstance=NULL);   // ��׼���캯��
	virtual ~CControlPage();

// �Ի�������
	enum { IDD = IDD_CONTROL_PAGE };
	public:
	virtual void OnTabActivation(BOOL bActivate);
	virtual BOOL OnTabChanging();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//�������
	bool SaveProfiles();

	int m_nRadio1;
	BOOL m_bCheck1;
};
