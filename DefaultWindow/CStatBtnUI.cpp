#include "stdafx.h"
#include "CStatBtnUI.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "ObjMgr.h"
#include "Player.h"

CStatBtnUI::CStatBtnUI()
    : m_vOffset(50.f, 35.f)
	, m_pLbtnDownTex(nullptr)
	, m_pLbtnClickTex(nullptr)
{
}

CStatBtnUI::~CStatBtnUI()
{
	Release();
}

void CStatBtnUI::Initialize()
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player�� ObjMgr�� ��ϵǱ� ���� �̰� �ҷ��� ����������

	Vec2 vPos = m_pParentUI->GetPos();
	m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y  , 80.f ,40.f };


	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::BUTTON;


	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_Stat_None_UI", L"../API/UI/Button_None.png");
	m_pLbtnDownTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_Stat_Lbtndown_UI", L"../API/UI/Button_Lbtndown.png");
	m_pLbtnClickTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_Stat_LbtnClick_UI", L"../API/UI/Button_Click.png");

}

int CStatBtnUI::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

	

	Vec2 vPos = m_pParentUI->GetPos();
	Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);

    __super::Update_Rect();




	

    return OBJ_NOEVENT;
}

void CStatBtnUI::Late_Update()
{
	MouseOnCheck();

	CPlayer* pPlayer = (CPlayer*)(CObjMgr::Get_Instance()->Get_Player());

	if (0 == pPlayer->GetAbilityPoint())
		m_pRenderTex = m_pLbtnClickTex;

}

void CStatBtnUI::Render(HDC hDC)
{
	
	AlphaBlend(hDC
		, m_tRect.left							 // ( ������ġ )						// �̹����� ����� x
		, m_tRect.top							 // ( ������ġ )						// �̹����� ����� y
		, m_tInfo.fCX							 // ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, m_tInfo.fCY
		, m_pRenderTex->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pRenderTex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
		, m_pRenderTex->Height()
		, this->GetBf());

}

void CStatBtnUI::Release()
{

	
}

void CStatBtnUI::MouseLBtnDown()
{
	
}

void CStatBtnUI::MouseLBtnUp()
{
}

void CStatBtnUI::MouseClick()			// �ڵ� ����̴ϱ� ����������Ŵ
{
	m_pPlayer->SetSTR(m_pPlayer->GetSTR() + m_pPlayer->GetAbilityPoint());
	m_pPlayer->SetAbilityPoint(0);

}

void CStatBtnUI::MouseOn()      // CUIMgr �� ȣ������
{
	m_pRenderTex = m_pLbtnDownTex;
}

void CStatBtnUI::MouseOut()    // CUIMgr �� ȣ������
{
	m_pRenderTex = m_pUITex;
}
