#include "stdafx.h"
#include "CPlayerHpUI.h"

#include "CResMgr.h"

#include "CTexture.h"

#include "Player.h"

CPlayerHpUI::CPlayerHpUI()
	: m_vOffset(10.f,2.f)
{
	
}

CPlayerHpUI::~CPlayerHpUI()
{
}

void CPlayerHpUI::Initialize()
{
	Vec2 vPos = m_pParentUI->GetPos();
	m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y  , 200.f , 12.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::HP;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_Hp_UI", L"../API/UI/hp.png");

}

int CPlayerHpUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayerHpUI::Late_Update()
{
}

void CPlayerHpUI::Render(HDC hDC)
{
	float iHp = m_pPlayer->GetHp();
	float iMaxHP = m_pPlayer->GetMaxHP();

	float fHpRatio = iHp / iMaxHP;



	AlphaBlend(hDC
		, m_tRect.left		// ( 고정위치 )						// 이미지를 출력할 x
		, m_tRect.top		// ( 고정위치 )						// 이미지를 출력할 y
		, m_tInfo.fCX * fHpRatio							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pUITex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
		, m_pUITex->Height()
		, this->GetBf());
}

void CPlayerHpUI::Release()
{
}
