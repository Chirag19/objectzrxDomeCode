#pragma once

#include "resource.h"

#include "TextPage.h"
#include "ControlPage.h"
#include "..\..\..\..\ZWCAD_2020_ZRXSDK\inc\zacuiDialog.h"

// COptionSheet �Ի���

class COptionSheet : public CZcUiTabMainDialog
{
	DECLARE_DYNAMIC(COptionSheet)

public:
	COptionSheet(CWnd* pParent = NULL,HINSTANCE hInstance=NULL);   // ��׼���캯��
	virtual ~COptionSheet();

// �Ի�������
	enum { IDD = IDD_OPTION_SHEET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnAcadKeepFocus(WPARAM,LPARAM);

	DECLARE_MESSAGE_MAP()
public:
	CAcUiTab m_tabCtrl;
	CTextPage m_textPage;
	CControlPage m_controlPage;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
