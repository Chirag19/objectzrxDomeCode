// ControlPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ControlPage.h"
#include "afxdialogex.h"


// CControlPage �Ի���

IMPLEMENT_DYNAMIC(CControlPage, CZcUiTabChildDialog)

CControlPage::CControlPage(CWnd* pParent /*=NULL*/,HINSTANCE hInstance /*=NULL*/)
	: CZcUiTabChildDialog(pParent,hInstance)
	, m_nRadio1(0)
	, m_bCheck1(FALSE)
{

}

CControlPage::~CControlPage()
{
}

void CControlPage::OnTabActivation(BOOL bActivate)
{

}

BOOL CControlPage::OnTabChanging()
{
	return (TRUE);
}

void CControlPage::DoDataExchange(CDataExchange* pDX)
{
	CZcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_RADIO1, m_nRadio1);
	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
}


BEGIN_MESSAGE_MAP(CControlPage, CZcUiTabChildDialog)
END_MESSAGE_MAP()


// CControlPage ��Ϣ�������


BOOL CControlPage::OnInitDialog()
{
	CZcUiTabChildDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��INI�ļ��м��ز���ֵ
	CIniFile iniFile(CAppDirectoryUtil::GetCurrentDirctory()+_T("\\OptionSheet.ini"));
	CString field=_T("OptionSheet");
	iniFile.GetValueOfKey(field,_T("nRadiol"),m_nRadio1);
	iniFile.GetValueOfKey(field,_T("bCheckl"),m_bCheck1);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

bool CControlPage::SaveProfiles()
{
	if(!UpdateData())
	{
		return false;
	}

	//�������ֵ
	CIniFile iniFile(CAppDirectoryUtil::GetCurrentDirctory()+_T("\\OptionSheet.ini"));
	CString filed=_T("OptionSheet");
	iniFile.SetValueOfKey(filed,_T("nRadiol"),m_nRadio1);
	iniFile.SetValueOfKey(filed,_T("bCheckl"),m_bCheck1);

	return true;
}
