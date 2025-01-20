#include "stdafx.h"
#include "CNoGoldUI.h"

#include "CTexture.h"
#include "CResMgr.h"

#include "CKeyMgr.h"
#include "CSound.h"


CNoGoldUI::CNoGoldUI()
	: m_vDragStart(0.f,0.f)
{
	m_bMovement = true;
}

CNoGoldUI::~CNoGoldUI()
{
}

void CNoGoldUI::Initialize()
{
	m_tInfo = { WINCX / 2.f,WINCY / 2.f, 200,100.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::NOGOLD;

	__super::Update_Rect();

    m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"NoGold", L"../API/UI/NoGold.png");


	CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"nomeso");
	pNewSound1->Play(false);
	pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound1->SetVolume(100.f); // 소리 볼륨 크기
}

int CNoGoldUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CNoGoldUI::Late_Update()
{
	MouseOnCheck();
	MouseOn();
}

void CNoGoldUI::Render(HDC hDC)
{
	AlphaBlend(hDC
		, m_tRect.left		            // ( 고정위치 )						// 이미지를 출력할 x
		, m_tRect.top		            // ( 고정위치 )						// 이미지를 출력할 y
		, m_tInfo.fCX							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pUITex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
		, m_pUITex->Height()
		, this->GetBf());


}

void CNoGoldUI::Release()
{
}

void CNoGoldUI::MouseLBtnDown()
{
	m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
}

void CNoGoldUI::MouseLBtnUp()
{
}

void CNoGoldUI::MouseClick()
{
}

void CNoGoldUI::MouseOn()
{
	if (m_bMovement)
	{
		if (IsLbtnDown())
		{
			Vec2 vCurMousePos = CKeyMgr::CreateSingleTonInst()->GetMousePos();
			Vec2 vDiff = m_vDragStart - vCurMousePos;
			Set_Pos(m_tInfo.fX - vDiff.x, m_tInfo.fY - vDiff.y);

			m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
		}
	}
}

void CNoGoldUI::MouseOut()
{
}
