#pragma once

#include "Resource.h"
#include "afxwin.h"

// CMfcDialog �Ի���

class CMfcDialog : public CDialog
{
	DECLARE_DYNAMIC(CMfcDialog)

public:
	CMfcDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMfcDialog();

// �Ի�������
	enum { IDD = IDD_MFC_MODAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
};
