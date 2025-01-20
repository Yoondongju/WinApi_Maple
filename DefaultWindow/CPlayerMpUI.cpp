#include "stdafx.h"
#include "CPlayerMpUI.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "Player.h"

CPlayerMpUI::CPlayerMpUI()
    : m_vOffset(10.f, 21.f)
{
    
}

CPlayerMpUI::~CPlayerMpUI()
{
}

void CPlayerMpUI::Initialize()
{
    Vec2 vPos = m_pParentUI->GetPos();
    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y  , 200.f , 12.f };


    m_eObjType = OBJID::OBJ_UI;
    m_eUItype = UI_TYPE::MP;

    m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_Mp_UI", L"../API/UI/mp.png");
}

int CPlayerMpUI::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CPlayerMpUI::Late_Update()
{
}

void CPlayerMpUI::Render(HDC hDC)
{
    float iMp = m_pPlayer->GetMp();
    float iMaxMP = m_pPlayer->GetMaxMP();

    float fMpRatio = iMp / iMaxMP;


   AlphaBlend(hDC
       , m_tRect.left		            // ( 고정위치 )						// 이미지를 출력할 x
       , m_tRect.top		            // ( 고정위치 )						// 이미지를 출력할 y
       , m_tInfo.fCX * fMpRatio						// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
       , m_tInfo.fCY
       , m_pUITex->GetDC()
       , 0								// 가져올 이미지의 시작위치
       , 0
       , m_pUITex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
       , m_pUITex->Height()
       , this->GetBf());
}

void CPlayerMpUI::Release()
{
}
