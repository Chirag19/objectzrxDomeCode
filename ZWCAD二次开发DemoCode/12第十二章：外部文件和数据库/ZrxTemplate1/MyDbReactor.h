#pragma once
#include "d:\desktop\zwcad���ο���ѧϰcode\11��ʮһ�£���objectarx��ʹ��mfc\zrx2020\inc\zdbmain.h"
class CMyDbReactor : public AcDbDatabaseReactor
{
public:
	CMyDbReactor();
	virtual ~CMyDbReactor();

	virtual void objectAppended (const AcDbDatabase* dwg, const AcDbObject* dbObj);
};

