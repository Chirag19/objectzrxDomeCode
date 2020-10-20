// TextPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TextPage.h"
#include "afxdialogex.h"


// CTextPage �Ի���

IMPLEMENT_DYNAMIC(CTextPage, CZcUiTabChildDialog)

CTextPage::CTextPage(CWnd* pParent /*=NULL*/,HINSTANCE hInstance)
	: CZcUiTabChildDialog(pParent,hInstance)
	, m_textHeight(0)
{

}

CTextPage::~CTextPage()
{
}

void CTextPage::OnTabActivation(BOOL bActivate)
{

}

BOOL CTextPage::OnTabChanging()
{
	return (TRUE);
}

void CTextPage::DoDataExchange(CDataExchange* pDX)
{
	CZcUiTabChildDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT_HEIGHT, m_textHeight);
	DDX_Control(pDX, IDC_TEXT_STYLE, m_cboTextStyle);
}


BEGIN_MESSAGE_MAP(CTextPage, CZcUiTabChildDialog)
END_MESSAGE_MAP()


// CTextPage ��Ϣ�������


BOOL CTextPage::OnInitDialog()
{
	CZcUiTabChildDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//���������ʽ��Ͽ�
	std::vector<CString> textStyles;
	CTextStyleUtil::GetAll(textStyles);
	for(int i=0;i<textStyles.size();i++)
	{
		m_cboTextStyle.AddString(textStyles[i]);
	}
	if(m_cboTextStyle.GetCount()>0)
	{
		m_cboTextStyle.SetCurSel(0);
	}

	//��INI�ļ��м��ز���ֵ
	CIniFile iniFile(CAppDirectoryUtil::GetCurrentDirctory()+_T("\\OptionSheet.ini"));
	CString field=_T("OptionSheet");
	iniFile.GetValueOfKey(field,_T("textHeight"),m_textHeight);
	CString strTextStyle;
	iniFile.GetValueOfKey(field,_T("textStyle"),strTextStyle);

	//������Ͽ�ĵ�ǰѡ��
	for(int i=0;i<m_cboTextStyle.GetCount();i++)
	{
		CString strItem;
		m_cboTextStyle.GetLBText(i,strItem);
		if(strItem.CompareNoCase(strTextStyle)==0)
		{
			m_cboTextStyle.SetCurSel(i);
			break;
		}
	}

	UpdateData(FALSE);	// ˢ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

bool CTextPage::SaveProfiles()
{
	if(!UpdateData())
	{
		return false;
	}

	//�������
	CIniFile iniFile(CAppDirectoryUtil::GetCurrentDirctory()+_T("\\OptionSheet.ini"));
	CString filed=_T("OptionSheet");
	iniFile.SetValueOfKey(filed,_T("textHeight"),m_textHeight);
	CString strTextStyle;
	m_cboTextStyle.GetLBText(m_cboTextStyle.GetCurSel(),strTextStyle);
	iniFile.SetValueOfKey(filed,_T("textStyle"),strTextStyle);

	return true;
}
