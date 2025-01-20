#include "stdafx.h"
#include "CTexture.h"

#include "MainGame.h"


CTexture::CTexture()
	: m_DC(0)
	, m_Bitmap(0)
	, m_BitInfo{ }
{
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;
	SetBf(bf);
}

CTexture::~CTexture()
{
	DeleteDC(m_DC);
	DeleteObject(m_Bitmap);

}

HBITMAP LoadPng(const wchar_t* filename)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	HBITMAP hBitmap = nullptr;
	Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromFile(filename);

	if (pBitmap != nullptr)
	{
		pBitmap->GetHBITMAP(Gdiplus::Color::White, &hBitmap);
		delete pBitmap;
	}

	GdiplusShutdown(gdiplusToken);

	return hBitmap;
}

void CTexture::Load(const wstring& _pPath)
{
	// ȣȯ���� �ʴ� DC ������ ������ ������ �� ���� ����
	// 1. �޸� DC�� �����   ( ��ȭ��� ȣȯ�Ǵ� DC (MainGame�� DC) �����. CreateCompatibleDC�Լ��� )
	// 2. ��Ʈ���� �о�´�.	LoadImage�Լ� ȣ��	
	// 3. Select�� ��ü�Ѵ�.  �޸�DC�� ��� ������ �� Bitmap�� �޾��ش�. 
	// 4. �޸� DC�� �׸� Bitmap �����͸� ���� MainGameDc�� �ű��.



	m_Bitmap = LoadPng(_pPath.c_str());
	
	m_DC = CreateCompatibleDC(CMainGame::CreateSingleTonInst()->GetMainGameDC());
	//m_Bitmap = (HBITMAP)LoadImage(nullptr, _pPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);



	assert(m_Bitmap);  // bitmap �Ҵ� �ȴ��

	// Select �������
	HBITMAP hPreBit = (HBITMAP)SelectObject(m_DC, m_Bitmap);
	DeleteObject(hPreBit);


	// m_BitInfo ��Ʈ�� ����
	GetObject(m_Bitmap, sizeof(BITMAP), &m_BitInfo);

	// m_BitInfo.bmWidth;		// ��Ʈ���� ����
	// m_BitInfo.bmHeight;		// ��Ʈ���� ����


}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = CMainGame::CreateSingleTonInst()->GetMainGameDC();


	m_Bitmap = CreateCompatibleBitmap(maindc, _iWidth, _iHeight); // ��Ʈ�� id �Ҵ�
	m_DC = CreateCompatibleDC(maindc);							// ��Ʈ�ʿ� �׸� DC id �Ҵ�

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_DC, m_Bitmap);   // ���� �׸������ ��Ʈ�ʰ� ��Ʈ�ʿ� �׸� DC�� ��������


	DeleteObject(hOldBit);

	GetObject(m_Bitmap, sizeof(BITMAP), &m_BitInfo);
}


