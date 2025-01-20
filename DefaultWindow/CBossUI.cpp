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
		, m_tRect.left		// ( ������ġ )						// �̹����� ����� x
		, m_tRect.top		// ( ������ġ )						// �̹����� ����� y
		, m_tInfo.fCX 						// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pUITex->Width()
		, m_pUITex->Height()
		, GetBf());


	AlphaBlend(hDC
		, m_tRect.left +45		// ( ������ġ )						// �̹����� ����� x
		, m_tRect.top + 3		// ( ������ġ )						// �̹����� ����� y
		, (m_tInfo.fCX-40) * fHpRatio							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, 20
		, m_pBossHp->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pBossHp->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
		, m_pBossHp->Height()
		, this->GetBf());
}

void CBossUI::Release()
{
}
