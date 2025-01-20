#include "stdafx.h"
#include "Mouse.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CSound.h"

CMouse::CMouse()
	: m_pTexNon(nullptr)
	, m_pTexClick(nullptr)
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 37.f;
	m_tInfo.fCY = 37.f;

	m_pTexNon = CResMgr::CreateSingleTonInst()->LoadTexture(L"Mouse_Non", L"../API/UI/Mouse1.png");
	m_pTexClick = CResMgr::CreateSingleTonInst()->LoadTexture(L"Mouse_Click", L"../API/UI/Mouse2.png");
}

int CMouse::Update()
{
	m_tInfo.fX = CKeyMgr::CreateSingleTonInst()->GetMousePos().x;
	m_tInfo.fY = CKeyMgr::CreateSingleTonInst()->GetMousePos().y;

	__super::Update_Rect();

	ShowCursor(false);

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
}


void CMouse::Render(HDC hDC)
{
	CTexture* pTex = m_pTexNon;

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::TAP
		|| CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::HOLD)
	{
		CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_click");
		pNewSound1->Play(false);
		pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
		pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

		pTex = m_pTexClick;
	}
	else if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::AWAY)
	{
		pTex = m_pTexNon;
	}



	AlphaBlend(hDC
		, m_tInfo.fX		            // ( 고정위치 )						// 이미지를 출력할 x
		, m_tInfo.fY					// ( 고정위치 )						// 이미지를 출력할 y
		, m_tInfo.fCX					// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, pTex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, pTex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
		, pTex->Height()
		, this->GetBf());
}


void CMouse::Release()
{
}
