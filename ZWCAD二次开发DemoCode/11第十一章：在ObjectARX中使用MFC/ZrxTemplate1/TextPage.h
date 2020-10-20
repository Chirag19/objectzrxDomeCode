#pragma once
#include "resource.h"
#include "afxwin.h"

// CTextPage �Ի���

class CTextPage : public CZcUiTabChildDialog
{
	DECLARE_DYNAMIC(CTextPage)

public:
	CTextPage(CWnd* pParent = NULL,HINSTANCE hInstance=NULL);   // ��׼���캯��
	virtual ~CTextPage();

// �Ի�������
	enum { IDD = IDD_TEXT_PAGE };
public:
	virtual void OnTabActivation(BOOL bActivate);
	virtual BOOL OnTabChanging();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_textHeight;
	CComboBox m_cboTextStyle;
	virtual BOOL OnInitDialog();

	//�����û�����Ĳ������浽INI�ļ�
	bool SaveProfiles();

	 
};
