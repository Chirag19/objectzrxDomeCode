// MfcDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MfcDialog.h"
#include "afxdialogex.h"


// CMfcDialog �Ի���

IMPLEMENT_DYNAMIC(CMfcDialog, CDialog)

CMfcDialog::CMfcDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMfcDialog::IDD, pParent)
{

}

CMfcDialog::~CMfcDialog()
{
}

void CMfcDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMfcDialog, CDialog)
END_MESSAGE_MAP()


// CMfcDialog ��Ϣ�������

