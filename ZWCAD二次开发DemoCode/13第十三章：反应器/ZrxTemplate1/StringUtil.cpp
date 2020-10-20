#include "stdafx.h"
#include "StringUtil.h"


CStringUtil::CStringUtil()
{
}


CStringUtil::~CStringUtil()
{
}

void CStringUtil::Split(const CString & text, const TCHAR * separator, std::vector<CString>& result, bool bAddEmptyItem)
{
	int prev = 0, current = 0;	//�ҵ���ǰƥ�����һ��ƥ��
	CString strCopyText = text;
	strCopyText.TrimRight(_T(" "));

	//��һ���Ȳ���Ŀ���ַ�������û�а����ָ���
	if (strCopyText.Find(separator, 0) < 0)
	{
		if (strCopyText.GetLength() > 0)
		{
			result.push_back(strCopyText);
		}
		return;
	}

	//ѭ����ȡ�м��ַ���
	int length = strCopyText.GetLength();
	bool bExit = false;
	while (1)
	{
		current = strCopyText.Find(separator, prev);
		if (current == -1)
		{
			current = length;	//�����һ����
			bExit = true;
		}

		//��һ���ָ���֮�������ָ���֮ǰ���ַ���������Ч���ַ���
		CString item = strCopyText.Mid(prev, current - prev);
		if (bAddEmptyItem || item.GetLength() > 0)
		{
			result.push_back(item);
		}

		if (bExit)
		{
			break;
		}
		prev = current + _tcslen(separator);
	}
	
}

CString CStringUtil::Jion(const std::vector<CString>& item, const TCHAR * separator)
{
	CString strResult;
	for (int i = 0; i < item.size(); i++)
	{
		strResult += item[i] + separator;
	}
	strResult.TrimRight(separator);
	return strResult;
}


