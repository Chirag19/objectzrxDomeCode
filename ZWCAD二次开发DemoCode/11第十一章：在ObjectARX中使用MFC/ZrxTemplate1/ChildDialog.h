#pragma once
#include "resource.h"

// CChildDialog �Ի���

class CChildDialog : public CZcUiDialog
{
	DECLARE_DYNAMIC(CChildDialog)

public:
	CChildDialog(CWnd* pParent = NULL,HINSTANCE hInstance=NULL);  // ��׼���캯��
	virtual ~CChildDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLine();
};
