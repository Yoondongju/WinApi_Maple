#include "stdafx.h"
#include "MainGame.h"
#include "CMonster.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"


#include "CKeyMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "CSceneMgr.h"


#include "CScene.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CUIMgr.h"

#include "Mouse.h"
#include "CSixSkill.h"

#include "CSoundMgr.h"

CMainGame::CMainGame() 
	: m_iFPS(0)
	, m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);


	// DC란 그리기의 목적지  (어떤 방식으로 그릴지에대한 디바이스 컨텍스트)
	// Bitmap은 내가 그릴 스케치북

	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);


	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::BULE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));




	m_pMemTex = CResMgr::CreateSingleTonInst()->CreateTexture(L"BackBuffer", WINCX,WINCY);

	
	
	AddFontResource(L"../API/Pont/koverwatch.ttf");
	SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
	SetBkMode(m_pMemTex->GetDC(), TRANSPARENT);					// 폰트 배경 투명색


	m_hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("koverwatch"));
	m_hOldFont = (HFONT)SelectObject(CMainGame::CreateSingleTonInst()->GetBackTexture()->GetDC(), m_hFont);
	SetTextColor(CMainGame::CreateSingleTonInst()->GetBackTexture()->GetDC(), RGB(0, 0, 0));		// 폰트 색 검은색
	

	CSoundMgr::CreateSingleTonInst()->init();
	CTimeMgr::CreateSingleTonInst()->init();
	CKeyMgr::CreateSingleTonInst()->init();

	CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_MOUSE, CAbstractFactory<CMouse>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->Late_InitPlayerObj();
	

	CSceneMgr::CreateSingleTonInst()->init();

}

void CMainGame::Update()
{
	CTimeMgr::CreateSingleTonInst()->update();
	CKeyMgr::CreateSingleTonInst()->update();
	CCamera::CreateSingleTonInst()->Update();


	CLineMgr::Get_Instance()->Update();
	CSceneMgr::CreateSingleTonInst()->Update();

	CUIMgr::CreateSingleTonInst()->Update();




}

void CMainGame::Late_Update()
{
	CSceneMgr::CreateSingleTonInst()->Late_Update();
}

void CMainGame::Render()
{
	Rectangle(m_pMemTex->GetDC(), -1,-1, WINCX,WINCY);

	CSceneMgr::CreateSingleTonInst()->Render(m_pMemTex->GetDC());	// 백버퍼 DC에 그려놓고
	//CLineMgr::Get_Instance()->Render(m_pMemTex->GetDC());			// 백버퍼 DC에 그려놓고

	CCamera::CreateSingleTonInst()->Render(m_pMemTex->GetDC());


	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_pMemTex->GetDC(), 0, 0, SRCCOPY); // Main DC에 복사

	//CSceneMgr::CreateSingleTonInst()->Render(m_pMemTex->GetDC());	// 백버퍼 DC에 그려놓고
	//CLineMgr::Get_Instance()->Render(m_pMemTex->GetDC());			// 백버퍼 DC에 그려놓고
	//
	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_pMemTex->GetDC(), 0, 0, SRCCOPY); // Main DC에 복사




	//++m_iFPS;
	//if(m_dwTime + 1000 < GetTickCount())
	//{
	//	swprintf_s(m_szFPS, L"FPS : %d , MousePos.x : %f , MousePos.y : %f", m_iFPS, CKeyMgr::CreateSingleTonInst()->GetMousePos().x , CKeyMgr::CreateSingleTonInst()->GetMousePos().y);
	//	SetWindowText(g_hWnd, m_szFPS);
	//
	//	m_iFPS = 0;
	//	m_dwTime = GetTickCount();
	//}

}

void CMainGame::Release()
{
	CLineMgr::Destroy();
	CObjMgr::Destroy();
	

	DeleteObject(m_hOldFont);
	DeleteObject(m_hFont);

	ReleaseDC(g_hWnd, m_hDC);		// GetDC로 얻어온 DC는 ReleaseDC로 지우고
}
