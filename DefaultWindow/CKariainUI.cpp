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
		, 90		// ( ������ġ )						// �̹����� ����� x
		, 35		// ( ������ġ )						// �̹����� ����� y
		, 50 						// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, 50
		, m_pUITex->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pUITex->Width()
		, m_pUITex->Height()
		, GetBf());


	AlphaBlend(hDC
		, 100 + 45		// ( ������ġ )						// �̹����� ����� x
		, 60 + 3		// ( ������ġ )						// �̹����� ����� y
		, (1000 - 40) * fHpRatio							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, 20
		, m_pBossHp->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pBossHp->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
		, m_pBossHp->Height()
		, this->GetBf());
}

void CKariainUI::Release()
{
}
