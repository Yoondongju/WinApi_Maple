#include "stdafx.h"
#include "CQuickSlotUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "ObjMgr.h"

CQuickSlotUI::CQuickSlotUI()
	: m_vOffset(490.f, -12.5f)
{

	BLENDFUNCTION bf = GetBf();
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 170;
	SetBf(bf);
}

CQuickSlotUI::~CQuickSlotUI()
{
	
	Release();

}

void CQuickSlotUI::Initialize()
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player�� ObjMgr�� ��ϵǱ� ���� �̰� �ҷ��� ����������

	m_tInfo = { WINCX/2.f + m_vOffset.x , WINCY - 45.f + m_vOffset.y  , 300.f ,80.f };
	

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::QUICK_SLOT;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_QuickSlot_UI", L"../API/UI/quickslot.png");


	m_vSkillOffset[(UINT)SKILL_TYPE::DEATHFAULT];
	m_vSkillOffset[(UINT)SKILL_TYPE::ORABLADE];
	m_vSkillOffset[(UINT)SKILL_TYPE::RAGINGBLOW];
	m_vSkillOffset[(UINT)SKILL_TYPE::UPPERCHARGE];
	m_vSkillOffset[(UINT)SKILL_TYPE::RUSH];

	m_vPortionOffset = Vec2(23.f, -20.f);
	m_vPortionTargetPos = Vec2(m_tInfo.fX + m_vPortionOffset.x, m_tInfo.fY + m_vPortionOffset.y);

}

int CQuickSlotUI::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


	__super::Update_Rect();

	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		iter->Update();

    return OBJ_NOEVENT;
}

void CQuickSlotUI::Late_Update()
{
	MouseOnCheck();

	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		iter->Late_Update();
}

void CQuickSlotUI::Render(HDC hDC)
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


	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		iter->Render(hDC);

}

void CQuickSlotUI::Release()
{
	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		Safe_Delete<CPlayerUI*>(iter);


	m_childUI_List.clear();
}

void CQuickSlotUI::MouseLBtnDown()
{
}

void CQuickSlotUI::MouseLBtnUp()
{
}

void CQuickSlotUI::MouseClick()
{
}

void CQuickSlotUI::MouseOn()
{
}

void CQuickSlotUI::MouseOut()
{
}
