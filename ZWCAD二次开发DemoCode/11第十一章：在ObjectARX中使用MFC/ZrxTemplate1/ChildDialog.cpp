// ChildDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChildDialog.h"
#include "afxdialogex.h"


// CChildDialog �Ի���

IMPLEMENT_DYNAMIC(CChildDialog, CAcUiDialog)

CChildDialog::CChildDialog(CWnd* pParent /*=NULL*/,HINSTANCE hInstance /*=NULL*/)
	: CZcUiDialog(CChildDialog::IDD, pParent,hInstance)
{

}

CChildDialog::~CChildDialog()
{
}

void CChildDialog::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChildDialog, CAcUiDialog)
	ON_BN_CLICKED(IDC_LINE, &CChildDialog::OnBnClickedLine)
END_MESSAGE_MAP()


// CChildDialog ��Ϣ�������


void CChildDialog::OnBnClickedLine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�������ģ̬�Ի�����Ҫ�����ĵ��ͽ����ĵ�
	acDocManager->lockDocument(acDocManager->curDocument());

	//����һ��ֱ��
	CLineUtil::Add(AcGePoint3d(4.0,2.0,2.0),AcGePoint3d(10.0,7.0,0.0));

	acDocManager->unlockDocument(acDocManager->curDocument());
}

