#include "stdafx.h"
#include "CEquipUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"


CEquipUI::CEquipUI()
	: m_vDragStart(Vec2(0.f, 0.f))
{
	m_bMovement = true;
	m_bActivate = false;


	BLENDFUNCTION bf = GetBf();
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	SetBf(bf);
}

CEquipUI::~CEquipUI()
{
	Release();
}

void CEquipUI::Initialize()
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player�� ObjMgr�� ��ϵǱ� ���� �̰� �ҷ��� ����������

	m_tInfo = { WINCX / 2.f - WINCX / 3.f, WINCY / 2.f, 230.f , 350.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::EQUIPMENT;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player__Equip_UI", L"../API/UI/Equipment.png");		// ���� ����




		// RING,
		// BELT,
		// EYE_PATCH,
		// NECKLACE,
		// EARRING,
		// PORTION,
		// PET,

}

int CEquipUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bActivate)
	{
		m_bMovement = true;


		m_vItemOffset[(UINT)ITEM_TYPE::RING] = Vec2(-82.f, -104.f);
		m_vItemOffset[(UINT)ITEM_TYPE::BELT] = Vec2(-42.f, 67.f);
		m_vItemOffset[(UINT)ITEM_TYPE::EYE_PATCH] = Vec2(-2.f, -18.f);
		m_vItemOffset[(UINT)ITEM_TYPE::NECKLACE] = Vec2(-42.f, -18.f);
		m_vItemOffset[(UINT)ITEM_TYPE::EARRING] = Vec2(37.f, -18.f);

		m_vItemTargetPos[(UINT)ITEM_TYPE::RING] = Vec2(m_tInfo.fX - 82.f, m_tInfo.fY - 104.f);
		m_vItemTargetPos[(UINT)ITEM_TYPE::BELT] = Vec2(m_tInfo.fX - 42.f, m_tInfo.fY + 67.f);
		m_vItemTargetPos[(UINT)ITEM_TYPE::EYE_PATCH] = Vec2(m_tInfo.fX - 2.f, m_tInfo.fY - 18.f);
		m_vItemTargetPos[(UINT)ITEM_TYPE::NECKLACE] = Vec2(m_tInfo.fX - 42.f, m_tInfo.fY - 18.f);
		m_vItemTargetPos[(UINT)ITEM_TYPE::EARRING] = Vec2(m_tInfo.fX + 37.f, m_tInfo.fY - 18.f);

		

		__super::Update_Rect();

		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Update();
	}


	return OBJ_NOEVENT;
}

void CEquipUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();
		MouseOn();


		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Late_Update();
	}
}

void CEquipUI::Render(HDC hDC)
{
	if (m_bActivate)
	{
		AlphaBlend(hDC
			, m_tRect.left		            // ( ������ġ )						// �̹����� ����� x
			, m_tRect.top		            // ( ������ġ )						// �̹����� ����� y
			, m_tInfo.fCX							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
			, m_tInfo.fCY
			, m_pUITex->GetDC()
			, 0								// ������ �̹����� ������ġ
			, 0
			,m_pUITex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
			,m_pUITex->Height()
			, this->GetBf());






		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Render(hDC);
	}


}

void CEquipUI::Release()
{
	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		Safe_Delete<CPlayerUI*>(iter);


	m_childUI_List.clear();
}


void CEquipUI::MouseLBtnDown()
{
	m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
}


void CEquipUI::MouseLBtnUp()
{
}


void CEquipUI::MouseClick()
{

	


}


void CEquipUI::MouseOn()
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


void CEquipUI::MouseOut()
{

}
