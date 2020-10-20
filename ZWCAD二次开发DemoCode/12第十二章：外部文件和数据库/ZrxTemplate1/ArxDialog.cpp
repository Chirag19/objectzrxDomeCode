// (C) Copyright 2002-2005 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- ArxDialog.cpp : Implementation of CArxDialog
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "ArxDialog.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CArxDialog, CAcUiDialog)

BEGIN_MESSAGE_MAP(CArxDialog, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CArxDialog::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_ANGLE, &CArxDialog::OnBnClickedButtonAngle)
	ON_EN_KILLFOCUS(IDC_EDIT_XPT, &CArxDialog::OnEnKillfocusEditXpt)
	ON_EN_KILLFOCUS(IDC_EDIT_YPT, &CArxDialog::OnEnKillfocusEditYpt)
	ON_EN_KILLFOCUS(IDC_EDIT_ZPT, &CArxDialog::OnEnKillfocusEditZpt)
	ON_EN_KILLFOCUS(IDC_EDIT_ANGLE, &CArxDialog::OnEnKillfocusEditAngle)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CArxDialog::CArxDialog (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CArxDialog::IDD, pParent, hInstance) {
}

//-----------------------------------------------------------------------------
void CArxDialog::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	DDX_Control(pDX, IDC_BUTTON_ANGLE, m_btnAngle);
	DDX_Control(pDX, IDC_BUTTON_POINT, m_btnPick);
	DDX_Control(pDX, IDC_EDIT_XPT, m_editXPt);
	DDX_Control(pDX, IDC_EDIT_YPT, m_editYPt);
	DDX_Control(pDX, IDC_EDIT_ZPT, m_editZPt);
	DDX_Control(pDX, IDC_EDIT_ANGLE, m_editAngle);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CArxDialog::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}


BOOL CArxDialog::OnInitDialog()
{
	CZcUiDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	// ���������ķ�Χ
	m_editXPt.SetRange(-100.0,100.0);
	m_editYPt.SetRange(-100.0,100.0);
	m_editZPt.SetRange(-100.0,100.0);

	//���ýǶȵ����뷶Χ
	m_editAngle.SetRange(0.0,90.0);

	//����Ĭ�ϵ�λͼ
	m_btnPick.AutoLoad();
	m_btnAngle.AutoLoad();

	//�����ı���Ĭ��ֵ
	m_strAngle=_T("0.0");
	m_strXPt=_T("0.0");
	m_strYPt=_T("0.0");
	m_strZPt=_T("0.0");

	//��ʾ��ʼ�������ͽǶ�ֵ
	DisplayPoint();
	DisplayAngle();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CArxDialog::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//��AutoCAD��������ѡ���Ľ��
	double x=_wtof(m_strXPt);
	double y=_wtof(m_strYPt);
	double z=_wtof(m_strZPt);

	acutPrintf(_T("\nѡ��ĵ�����Ϊ�� %.2f,%.2f,%.2f��."),x,y,z);

	CZcUiDialog::OnClose();
}


void CArxDialog::OnBnClickedButtonPoint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//���ضԻ���ѿ���Ȩ����AutoCAD
	BeginEditorCommand();

	//��ʾ�û�ѡ������һ����
	ads_point pt;
	if(acedGetPoint(NULL,_T("\n����һ����:"),pt)==RTNORM)
	{
		//�������Ч����������
		CompleteEditorCommand();

		m_strXPt.Format(_T("%.2f"),pt[X]);
		m_strYPt.Format(_T("%.2f"),pt[Y]);
		m_strZPt.Format(_T("%.2f"),pt[Z]);

		//��ʾ�������
		DisplayPoint();
	}
	else
	{
		//����ȡ����������Ի���
		CancelEditorCommand();
	}
}


void CArxDialog::OnBnClickedButtonAngle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���ضԻ���ѿ���Ȩ����AutoCAD
	BeginEditorCommand();

	//����ǰѡ�ŵĵ�λ����Ϊ����
	ads_point pt;
	acdbDisToF(m_strXPt,-1,&pt[X]);
	acdbDisToF(m_strYPt,-1,&pt[Y]);
	acdbDisToF(m_strZPt,-1,&pt[Z]);

	//��ʾ�û�����һ�� 
	double angle;
	if(acedGetAngle(pt,_T("\n����Ƕ�:"),&angle)==RTNORM)
	{
		//�����ȷ��ýǶȣ����ضԻ���
		CompleteEditorCommand();
		//���Ƕ�ת��Ϊ����ֵ
		m_strAngle.Format(_T("%.2f"),angle*(180.0/CMathUtil::PI()));

		//��ʾ�Ƕ�
		DisplayAngle();
	}
	else
	{
		//����ȡ����������Ի���
		CancelEditorCommand();
	}
}

void CArxDialog::DisplayPoint()
{
	//�ڶԻ�������ʾ�������
	m_editXPt.SetWindowText(m_strXPt);
	m_editXPt.Convert();	//���¿ռ��������ĳ�Ա����
	m_editYPt.SetWindowText(m_strYPt);
	m_editYPt.Convert();
	m_editZPt.SetWindowText(m_strZPt);
	m_editZPt.Convert();

}

void CArxDialog::DisplayAngle()
{
	m_editAngle.SetWindowText(m_strAngle);
	m_editAngle.Convert();
}


void CArxDialog::OnEnKillfocusEditXpt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ò������û�����ֵ
	m_editXPt.Convert();
	m_editXPt.GetWindowTextW(m_strXPt);
}


void CArxDialog::OnEnKillfocusEditYpt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ò������û�����ֵ
	m_editYPt.Convert();
	m_editYPt.GetWindowTextW(m_strYPt);
}


void CArxDialog::OnEnKillfocusEditZpt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ò������û�����ֵ
	m_editZPt.Convert();
	m_editAngle.GetWindowTextW(m_strZPt);
}


void CArxDialog::OnEnKillfocusEditAngle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ò������û�����ֵ
	m_editAngle.Convert();
	m_editAngle.GetWindowTextW(m_strAngle);
}
