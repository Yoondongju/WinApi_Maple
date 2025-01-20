#include "stdafx.h"
#include "CKariainUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CMonster.h"
#include "ObjMgr.h"

CKariainUI::CKariainUI()
	: m_pBoss(nullptr)
{
}

CKariainUI::~CKariainUI()
{
}

void CKariainUI::Initialize(CMonster* _pOwner)
{
	m_pBoss = _pOwner;

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::BOSS_HP;

	


	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Kariain_face", L"../API/kariain/face.png");
	m_pBossHp = CResMgr::CreateSingleTonInst()->LoadTexture(L"BossHp", L"../API/Boss/BossHp.png");

}

int CKariainUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CKariainUI::Late_Update()
{
}

void CKariainUI::Render(HDC hDC)
{
	float iHp = m_pBoss->GetHp();
	float iMaxHP = m_pBoss->GetMaxHP();

	float fHpRatio = iHp / iMaxHP;

	if (iHp <= 0)
		Set_Dead();


	AlphaBlend(hDC
		, 90		// ( 고정위치 )						// 이미지를 출력할 x
		, 35		// ( 고정위치 )						// 이미지를 출력할 y
		, 50 						// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, 50
		, m_pUITex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pUITex->Width()
		, m_pUITex->Height()
		, GetBf());


	AlphaBlend(hDC
		, 100 + 45		// ( 고정위치 )						// 이미지를 출력할 x
		, 60 + 3		// ( 고정위치 )						// 이미지를 출력할 y
		, (1000 - 40) * fHpRatio							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, 20
		, m_pBossHp->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pBossHp->Width() 			// 잘라낼 크기니까 항상 800 이여야함
		, m_pBossHp->Height()
		, this->GetBf());
}

void CKariainUI::Release()
{
}
