#pragma once
#include "d:\desktop\zwcad���ο���ѧϰcode\11��ʮһ�£���objectarx��ʹ��mfc\zrx2020\inc\zaced.h"
class CMyEditorReactor : public AcEditorReactor
{
public:
	CMyEditorReactor();
	virtual ~CMyEditorReactor();

	virtual void commandWillStart(const char* cmdStr);
	virtual void commandEnded(const TCHAR* cmdStr);
};

