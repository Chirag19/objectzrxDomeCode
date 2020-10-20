// OptionSheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OptionSheet.h"
#include "afxdialogex.h"
//#include "..\Zrx2020\inc\zaduiTabChildDialog.h"
#include "..\Zrx2020\arxport\aduiTabChildDialog.h"

// COptionSheet �Ի���

IMPLEMENT_DYNAMIC(COptionSheet, CZcUiTabMainDialog)

COptionSheet::COptionSheet(CWnd* pParent /*=NULL*/,HINSTANCE HInstance /*=NULL*/)
	: CZcUiTabMainDialog(COptionSheet::IDD, pParent,HInstance)
{

}

COptionSheet::~COptionSheet()
{
}

void COptionSheet::DoDataExchange(CDataExchange* pDX)
{
	CZcUiTabMainDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tabCtrl);
}


LRESULT COptionSheet::OnAcadKeepFocus(WPARAM,LPARAM)
{
	return (TRUE);
}

BEGIN_MESSAGE_MAP(COptionSheet, CZcUiTabMainDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
END_MESSAGE_MAP()


// COptionSheet ��Ϣ�������


BOOL COptionSheet::OnInitDialog()
{
	CZcUiTabMainDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//���ѡ�
	//SetAcadTabChildFocus(&m_tabCtrl);
	m_tabCtrl.AddTab(0,_T("����"),CTextPage::IDD,&m_textPage);
	m_tabCtrl.AddTab(1,_T("�ؼ�"),CControlPage::IDD,&m_controlPage);
	m_tabCtrl.SetActiveTab(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void COptionSheet::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(!m_textPage.SaveProfiles()||!m_controlPage.SaveProfiles())
	{
		return;
	}


	CZcUiTabMainDialog::OnOK();
}
