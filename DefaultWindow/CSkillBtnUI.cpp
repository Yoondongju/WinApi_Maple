#include "stdafx.h"
#include "CSkillBtnUI.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "Player.h"
#include "ObjMgr.h"


CSkillBtnUI::CSkillBtnUI()
	: m_vOffset(0.f,0.f)
	, m_pLbtnClickTex(nullptr)
{
}

CSkillBtnUI::~CSkillBtnUI()
{
}



void CSkillBtnUI::Initialize(Vec2 _vOffset, SKILL_TYPE _e)
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player�� ObjMgr�� ��ϵǱ� ���� �̰� �ҷ��� ����������

	Vec2 vPos = m_pParentUI->GetPos();
	m_vOffset = _vOffset;
	m_eSkillType = _e;


	m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y  , 25.f ,25.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::BUTTON;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_SkillBtn_None_UI", L"../API/UI/Skill_None.png");
	m_pLbtnClickTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_SkillBtn_Click_UI", L"../API/UI/Skill_Click.png");
}


int CSkillBtnUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	

	Vec2 vPos = m_pParentUI->GetPos();
	Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}


void CSkillBtnUI::Late_Update()
{
	MouseOnCheck();

	if (nullptr != m_pPlayer->GetSkill(m_eSkillType))
		m_pUITex = m_pLbtnClickTex;
}

void CSkillBtnUI::Render(HDC hDC)
{
	AlphaBlend(hDC
		, m_tRect.left		            // ( ������ġ )						// �̹����� ����� x
		, m_tRect.top		            // ( ������ġ )						// �̹����� ����� y
		, m_tInfo.fCX							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pUITex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
		, m_pUITex->Height()
		, this->GetBf());
}

void CSkillBtnUI::Release()
{
}

void CSkillBtnUI::MouseLBtnDown()
{

}

void CSkillBtnUI::MouseLBtnUp()
{
}

void CSkillBtnUI::MouseClick()
{
	int iPoint = m_pPlayer->GetSkillPoint();


	if (nullptr != m_pPlayer->GetSkill(m_eSkillType))
		return;


	m_pPlayer->SetSkillPoint(--iPoint);
	m_pPlayer->SetCreateSkill(m_eSkillType);
}

void CSkillBtnUI::MouseOn()
{
	
}

void CSkillBtnUI::MouseOut()
{
	
}
