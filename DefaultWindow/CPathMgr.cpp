#include "stdafx.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	:m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}


//void CPathMgr::init()
//{
//	GetCurrentDirectory(255, m_szContentPath); // ���� ����� ���α׷��� ��θ� �˷���  
//
//	int iLen = wcslen(m_szContentPath);
//
//	// ���������� �����Ŀ�  + bin // content // textrue �������
//
//	for (int i = iLen - 1; i >= 0; i--)
//	{
//		if ('\\' == m_szContentPath[i])
//		{
//			m_szContentPath[i] = '\0';
//			break;
//		}
//	}
//
//	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
//
//	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
//
//
//}
//wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
//{
//	wstring strFilePath = _filepath;
//
//	// C:\Users\User\Desktop\Engine\Output\bin\content
//	// C:\Users\User\Desktop\Engine\Output\bin\content\Tile
//
//	size_t iAbsLen = wcslen(m_szContentPath);  // 48 ��
//	size_t iFulllen = strFilePath.length();    // 62 ��
//
//
//	// iFulllen- iAbsLen == 14��
//	wstring strRelativePath = strFilePath.substr(iAbsLen, iFulllen - iAbsLen); // iAbsLen ��ġ���� iFulllen- iAbsLen���� ���ڱ���
//
//	return strRelativePath;
//}