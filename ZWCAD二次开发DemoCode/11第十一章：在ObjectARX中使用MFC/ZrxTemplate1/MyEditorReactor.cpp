#include "StdAfx.h"
#include "MyEditorReactor.h"


CMyEditorReactor::CMyEditorReactor()
{

}

CMyEditorReactor::~CMyEditorReactor()
{

}

void CMyEditorReactor::commandEnded( const TCHAR* cmdStr )
{
	acutPrintf(TEXT("\n%s����ִ�н�����."), cmdStr);
}

void CMyEditorReactor::commandWillStart( const char* cmdStr )
{
	acutPrintf(TEXT("\n%s���Ҫ��ʼִ��."), cmdStr);
}
