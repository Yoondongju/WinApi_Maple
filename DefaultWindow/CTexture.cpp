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
	// 호환되지 않는 DC 끼리는 정보를 공유할 수 없기 때문
	// 1. 메모리 DC를 만든다   ( 내화면과 호환되는 DC (MainGame의 DC) 만든다. CreateCompatibleDC함수로 )
	// 2. 비트맵을 읽어온다.	LoadImage함수 호출	
	// 3. Select로 교체한다.  메모리DC에 방금 생성한 내 Bitmap을 달아준다. 
	// 4. 메모리 DC에 그린 Bitmap 데이터를 나의 MainGameDc에 옮긴다.



	m_Bitmap = LoadPng(_pPath.c_str());
	
	m_DC = CreateCompatibleDC(CMainGame::CreateSingleTonInst()->GetMainGameDC());
	//m_Bitmap = (HBITMAP)LoadImage(nullptr, _pPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);



	assert(m_Bitmap);  // bitmap 할당 안대믄

	// Select 해줘야함
	HBITMAP hPreBit = (HBITMAP)SelectObject(m_DC, m_Bitmap);
	DeleteObject(hPreBit);


	// m_BitInfo 비트맵 정보
	GetObject(m_Bitmap, sizeof(BITMAP), &m_BitInfo);

	// m_BitInfo.bmWidth;		// 비트맵의 가로
	// m_BitInfo.bmHeight;		// 비트맵의 세로


}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = CMainGame::CreateSingleTonInst()->GetMainGameDC();


	m_Bitmap = CreateCompatibleBitmap(maindc, _iWidth, _iHeight); // 비트맵 id 할당
	m_DC = CreateCompatibleDC(maindc);							// 비트맵에 그릴 DC id 할당

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_DC, m_Bitmap);   // 내가 그리고싶은 비트맵과 비트맵에 그릴 DC를 연결해줌


	DeleteObject(hOldBit);

	GetObject(m_Bitmap, sizeof(BITMAP), &m_BitInfo);
}


