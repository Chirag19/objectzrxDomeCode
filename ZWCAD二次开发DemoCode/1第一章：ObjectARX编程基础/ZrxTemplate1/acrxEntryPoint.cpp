//////////////////////////////////////////////////////////////////////////
// ���ļ���������
// 

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CZrxTemplate1App : public AcRxArxApp{
public:
	CZrxTemplate1App() : AcRxArxApp() {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: �������������������������

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: ��ʼ��

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: �˳�

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: ж������

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

	static void zw_HelloWord()
	{
		acutPrintf(L"Hello Word!\n");
	}
	
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CZrxTemplate1App)
ACED_ARXCOMMAND_ENTRY_AUTO(CZrxTemplate1App, zw, _HelloWord, HelloWord, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
