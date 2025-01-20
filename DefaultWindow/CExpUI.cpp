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
        , m_tRect.left		            // ( ������ġ )						// �̹����� ����� x
        , m_tRect.top		            // ( ������ġ )						// �̹����� ����� y
        , m_tInfo.fCX * fExpRatio		// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
        , m_tInfo.fCY
        , m_pUITex->GetDC()
        , 0								// ������ �̹����� ������ġ
        , 0
        , m_pUITex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
        , m_pUITex->Height()
        , this->GetBf());

}

void CExpUI::Release()
{
}
