#include "stdafx.h"
#include "CExpUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "Player.h"

CExpUI::CExpUI()
    : m_vOffset(0.f, 40.f)
{
   
}


CExpUI::~CExpUI()
{
}

void CExpUI::Initialize()
{
    Vec2 vPos = m_pParentUI->GetPos();
    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y  , WINCX , 12.f };


    m_eObjType = OBJID::OBJ_UI;
    m_eUItype = UI_TYPE::EXP;

    m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_Exp_UI", L"../API/UI/exp.png");
}

int CExpUI::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CExpUI::Late_Update()
{
}

void CExpUI::Render(HDC hDC)
{
    float iExp = m_pPlayer->GetExp();
    float iMaxExp = m_pPlayer->GetMapExp();

    float fExpRatio = iExp / iMaxExp;


    AlphaBlend(hDC
        , m_tRect.left		            // ( 고정위치 )						// 이미지를 출력할 x
        , m_tRect.top		            // ( 고정위치 )						// 이미지를 출력할 y
        , m_tInfo.fCX * fExpRatio		// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
        , m_tInfo.fCY
        , m_pUITex->GetDC()
        , 0								// 가져올 이미지의 시작위치
        , 0
        , m_pUITex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
        , m_pUITex->Height()
        , this->GetBf());

}

void CExpUI::Release()
{
}
