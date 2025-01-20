#include "stdafx.h"
#include "CSkill_IconUI.h"


#include "CResMgr.h"
#include "CTexture.h"

#include "ObjMgr.h"
#include "CKeyMgr.h"
#include "Player.h"


CSkill_IconUI::CSkill_IconUI()
    : m_vOffset(0.f, 0.f)
	, m_pLbtnClickTex(nullptr)
    , m_pRenderTex(nullptr)
{
}


CSkill_IconUI::~CSkill_IconUI()
{
}

void CSkill_IconUI::Initialize()
{
	// �Ű��������� ������ ����
	assert(nullptr);
}

void CSkill_IconUI::Initialize(CTexture* _pTex, CTexture* _pClickTex ,Vec2 _vOffset , SKILL_TYPE _e)
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player�� ObjMgr�� ��ϵǱ� ���� �̰� �ҷ��� ����������

	Vec2 vPos = m_pParentUI->GetPos();
	m_vOffset = _vOffset;
	m_tInfo = { vPos .x + m_vOffset.x , vPos.y + m_vOffset.y  , 35.f ,35.f };


	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::SKILL_ICON;
	m_eSkillType = _e;

	m_pUITex = _pTex;					// ��Ȱ��ȭ
	m_pRenderTex = _pClickTex;			// Ȱ��ȭ
}

int CSkill_IconUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	

	Vec2 vPos = m_pParentUI->GetPos();
	Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSkill_IconUI::Late_Update()
{
	MouseOnCheck();
	MouseOn();


	if (nullptr != m_pPlayer->GetSkill(m_eSkillType))   // ��ų�� �����Ѵٸ�
	{
		m_pUITex = m_pRenderTex;
	}
		
}

void CSkill_IconUI::Render(HDC hDC)
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

void CSkill_IconUI::Release()
{
}

void CSkill_IconUI::MouseLBtnDown()
{

	
}

void CSkill_IconUI::MouseLBtnUp()
{
	
}

void CSkill_IconUI::MouseClick()
{
}

void CSkill_IconUI::MouseOn()
{
	

}

void CSkill_IconUI::MouseOut()
{
}
