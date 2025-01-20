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
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player가 ObjMgr에 등록되기 전에 이걸 불러서 문제가생김

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
		, m_tRect.left							 // ( 고정위치 )						// 이미지를 출력할 x
		, m_tRect.top							 // ( 고정위치 )						// 이미지를 출력할 y
		, m_tInfo.fCX							 // 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, m_pRenderTex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pRenderTex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
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

void CStatBtnUI::MouseClick()			// 자동 배분이니까 힘만증가시킴
{
	m_pPlayer->SetSTR(m_pPlayer->GetSTR() + m_pPlayer->GetAbilityPoint());
	m_pPlayer->SetAbilityPoint(0);

}

void CStatBtnUI::MouseOn()      // CUIMgr 가 호출해줌
{
	m_pRenderTex = m_pLbtnDownTex;
}

void CStatBtnUI::MouseOut()    // CUIMgr 가 호출해줌
{
	m_pRenderTex = m_pUITex;
}
