// CModelessDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModelessDialog.h"
#include "afxdialogex.h"


// CModelessDialog �Ի���

IMPLEMENT_DYNAMIC(CModelessDialog, CAcUiDialog)
BEGIN_MESSAGE_MAP(CModelessDialog, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS,OnACADKeepFocus)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ST, &CModelessDialog::OnBnClickedButtonSt)
	ON_BN_CLICKED(IDC_BUTTON_EN, &CModelessDialog::OnBnClickedButtonEn)
	ON_BN_CLICKED(IDC_BUTTON_LINE, &CModelessDialog::OnBnClickedButtonLine)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CModelessDialog::OnBnClickedButtonClose)
END_MESSAGE_MAP()
CModelessDialog::CModelessDialog(CWnd* pParent /*=NULL*/,HINSTANCE hInstance /*=NULL*/)
	: CAcUiDialog(CModelessDialog::IDD, pParent,hInstance)
	, m_strStX(_T(""))
	, m_strStY(_T(""))
	, m_strStZ(_T(""))
	, m_strEnX(_T(""))
	, m_strEnY(_T(""))
	, m_strEnZ(_T(""))
{

}

CModelessDialog::~CModelessDialog()
{
}

void CModelessDialog::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STX, m_strStX);
	DDX_Text(pDX, IDC_EDIT_STY, m_strStY);
	DDX_Text(pDX, IDC_EDIT_STZ, m_strStZ);
	DDX_Text(pDX, IDC_EDIT_ENX, m_strEnX);
	DDX_Text(pDX, IDC_EDIT_ENY, m_strEnY);
	DDX_Text(pDX, IDC_EDIT_ENZ, m_strEnZ);
	DDX_Control(pDX, IDC_BUTTON_ST, m_btnPickStart);
	DDX_Control(pDX, IDC_BUTTON_EN, m_btnPickEnd);
}


LRESULT CModelessDialog::OnACADKeepFocus(WPARAM,LPARAM)
{
	return (TRUE);
}




// CModelessDialog ��Ϣ�������


void CModelessDialog::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	//�ͷŷ�ģ̬�Ի�����ڴ�
	delete this;
	
	if(pDialog!=NULL)
	{
		pDialog=NULL;
	}

	CZcUiDialog::PostNcDestroy();
}


BOOL CModelessDialog::OnInitDialog()
{
	CZcUiDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	//��ʰȡ�㡱��ťλͼ
	m_btnPickStart.AutoLoad();
	m_btnPickEnd.AutoLoad();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CModelessDialog::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CZcUiDialog::OnClose();

	//���ٶԻ���
	DestroyWindow();
}


void CModelessDialog::OnBnClickedButtonSt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	//���ضԻ���ѿ���Ȩ����AutoCAD
	BeginEditorCommand();

	//��ʾ�û�����һ����
	AcGePoint3d pt;
	if(CGetInputUtil::GetPoint(_T("\n����һ����:"),pt))
	{
		//�������Ч������ִ��
		CompleteEditorCommand();
		m_strStX.Format(_T("%.2f"),pt.x);
		m_strStY.Format(_T("%.2f"),pt.y);
		m_strStZ.Format(_T("%.2f"),pt.z);
	}
	else
	{
		//����ȡ����������Ի���
		CancelEditorCommand();
	}

	//�ó�Ա������ֵ�����ı���ʾ������
	UpdateData(FALSE);
}


void CModelessDialog::OnBnClickedButtonEn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���ضԻ���ѿ���Ȩ����AutoCAD
	BeginEditorCommand();

	//��ʾ�û�����һ����
	AcGePoint3d pt;
	if(CGetInputUtil::GetPoint(_T("\n����һ����:"),pt))
	{
		//�������Ч������ִ��
		CompleteEditorCommand();
		m_strEnX.Format(_T("%.2f"),pt.x);
		m_strEnY.Format(_T("%.2f"),pt.y);
		m_strEnZ.Format(_T("%.2f"),pt.z);
	}
	else
	{
		//����ȡ����������Ի���
		CancelEditorCommand();
	}

	//�ó�Ա������ֵ�����ı���ʾ������
	UpdateData(FALSE);
}


void CModelessDialog::OnBnClickedButtonLine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��������յ������
	AcGePoint3d ptStart(_wtof(m_strStX),_wtof(m_strStY),_wtof(m_strStZ));
	AcGePoint3d ptEnd(_wtof(m_strEnX),_wtof(m_strEnY),_wtof(m_strEnZ));

	//�����ĵ�
	acDocManager->lockDocument(curDoc());

	//����ֱ��
	CLineUtil::Add(ptStart,ptEnd);

	//ˢ��ͼ��
	actrTransactionManager->queueForGraphicsFlush();
	actrTransactionManager->flushGraphics();
	acedUpdateDisplay();

	//�����ĵ�
	acDocManager->unlockDocument(curDoc());
}


void CModelessDialog::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���ٶԻ���
	DestroyWindow();
}
