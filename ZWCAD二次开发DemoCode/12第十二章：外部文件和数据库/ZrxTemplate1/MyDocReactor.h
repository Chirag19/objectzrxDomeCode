#pragma once
#include "d:\desktop\zwcad���ο���ѧϰcode\11��ʮһ�£���objectarx��ʹ��mfc\zrx2020\inc\zacdocman.h"
class CMyDocReactor : public AcApDocManagerReactor
{
public:
	CMyDocReactor();
	virtual ~CMyDocReactor();

	//���ڽ���Line����;
	virtual void documentLockModeChanged(AcApDocument* pDoc,
		AcAp::DocLockMode myPreviousMode,
		AcAp::DocLockMode myCurrentMode,
		AcAp::DocLockMode currentMode,
		const char* pGlobalCmdName);

	virtual void documentToBeDestroyed(AcApDocument* pDocToDestroy);
	virtual void documentCreated(AcApDocument* pDocCreating);
};

