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
		, m_tRect.left		// ( ������ġ )						// �̹����� ����� x
		, m_tRect.top		// ( ������ġ )						// �̹����� ����� y
		, m_tInfo.fCX * fHpRatio							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pUITex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
		, m_pUITex->Height()
		, this->GetBf());
}

void CPlayerHpUI::Release()
{
}
