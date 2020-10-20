
#include "stdafx.h"

#include "SampleDlg.h"
#include "AcExtensionModule.h"
#include "DbConnection.h"
#include "DbCommand.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HWND adsw_acadMainWnd();

AC_IMPLEMENT_EXTENSION_MODULE(theArxDLL);

void dialogCreate()
{

	// Modal
	SampleDlg dlg(CWnd::FromHandle(adsw_acadMainWnd()));
	int nReturnValue = dlg.DoModal();

}
// ������ݿ������ַ���
static CString GetConnectionString()
{
	//CString mdbFileName = CAppDirectoryUtil::GetParentDirectory(_hdllInstance) + TEXT("\\book.mdb");
	CString mdbFileName=TEXT("d:\\book.mdb");
	return TEXT("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + mdbFileName;		
}
// - Zfftest.aaa command (do not rename)
static void aaa(void)
{
	// Add your code for command Zfftest.aaa here
	// �����ݿ�����
	CDbConnection con(GetConnectionString());
	con.Open();

	// �����ѯ����
	CString sql;
	sql.Format(TEXT("Insert Into Book(Name, Author, Press, Price) Values('%s', '%s', '%s', %f)"), 
		TEXT("AutoCAD 2002�����̳�"), TEXT("���� �ŷ� ������"), TEXT("����ϣ�����ӳ�����"), 32.0);
	CDbCommand cmd(sql, &con);
	int rows = cmd.ExecuteNonQuery();

	CDbCommand cmd2(TEXT("Select @@Identity"), &con);
	int bookId = cmd2.ExecuteScalar().ToInteger();
	acutPrintf(TEXT("\n�½���Book���¼����:%d"), bookId);

	// �ر����ݿ�����
	con.Close();

}
void initApp()
{ 
	// register a command with the AutoCAD command mechanism
		CAcModuleResourceOverride resOverride;

	acedRegCmds->addCommand(_T("ZRX_DLG_SAMPLE"), 
		_T("ZRXDLGSAMPLE"), 
		_T("DLGSAMPLE"), 
		ACRX_CMD_MODAL, 
		dialogCreate,
		NULL,
		-1,
		theArxDLL.ModuleResourceInstance());
	
acedRegCmds->addCommand(_T("ZRX_DLG_SAMPLE"), 
	_T("aaa"), 
	_T("aaa"), 
	ACRX_CMD_MODAL, 
	aaa,
	NULL,
	-1,
	theArxDLL.ModuleResourceInstance());
	}

void unloadApp()
{ 
		acedRegCmds->removeGroup(_T("ZRX_DLG_SAMPLE"));  
	}

//////////////////////////////////////////////////////////////
//
// Entry points
//
//////////////////////////////////////////////////////////////
extern "C" int APIENTRY
	DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		theArxDLL.AttachInstance(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		theArxDLL.DetachInstance();  
	}
	return 1;   // ok
}

extern "C" AcRx::AppRetCode zcrxEntryPoint( AcRx::AppMsgCode msg, void* appId)
{
	switch( msg ) 
	{
	case AcRx::kInitAppMsg: 
		acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
		initApp(); 
		break;
	case AcRx::kUnloadAppMsg: 
		unloadApp(); 
		break;
	case AcRx::kInitDialogMsg:

		break;
	default:
		break;
	}
	return AcRx::kRetOK;
}