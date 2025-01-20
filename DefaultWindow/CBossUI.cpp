#include "stdafx.h"
#include "CBossUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CMonster.h"
#include "ObjMgr.h"

CBossUI::CBossUI()
	: m_pBoss(nullptr)
{
}

CBossUI::~CBossUI()
{
}

void CBossUI::Initialize(int _pageCount)
{	
	m_pBoss = (CMonster*)CObjMgr::Get_Instance()->Get_Will();
	m_tInfo = { WINCX/2.f , 70.f  , 1000.f , 50.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::BOSS_HP;

	if(_pageCount == 1)
		m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"BossPage1_bar", L"../API/Boss/page1_hpbar.png");
	else if (_pageCount == 2 )
		m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"BossPage2_bar", L"../API/Boss/page2_hpbar.png");



	m_pBossHp = CResMgr::CreateSingleTonInst()->LoadTexture(L"BossHp", L"../API/Boss/BossHp.png");

}

int CBossUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBossUI::Late_Update()
{
}

void CBossUI::Render(HDC hDC)
{
	float iHp = m_pBoss->GetHp();
	float iMaxHP = m_pBoss->GetMaxHP();

	float fHpRatio = iHp / iMaxHP;

	if (iHp <= 0)
		Set_Dead();

	AlphaBlend(hDC
		, m_tRect.left		// ( 고정위치 )						// 이미지를 출력할 x
		, m_tRect.top		// ( 고정위치 )						// 이미지를 출력할 y
		, m_tInfo.fCX 						// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pUITex->Width()
		, m_pUITex->Height()
		, GetBf());


	AlphaBlend(hDC
		, m_tRect.left +45		// ( 고정위치 )						// 이미지를 출력할 x
		, m_tRect.top + 3		// ( 고정위치 )						// 이미지를 출력할 y
		, (m_tInfo.fCX-40) * fHpRatio							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, 20
		, m_pBossHp->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pBossHp->Width() 			// 잘라낼 크기니까 항상 800 이여야함
		, m_pBossHp->Height()
		, this->GetBf());
}

void CBossUI::Release()
{
}
