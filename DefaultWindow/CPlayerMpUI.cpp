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
       , m_tRect.left		            // ( ������ġ )						// �̹����� ����� x
       , m_tRect.top		            // ( ������ġ )						// �̹����� ����� y
       , m_tInfo.fCX * fMpRatio						// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
       , m_tInfo.fCY
       , m_pUITex->GetDC()
       , 0								// ������ �̹����� ������ġ
       , 0
       , m_pUITex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
       , m_pUITex->Height()
       , this->GetBf());
}

void CPlayerMpUI::Release()
{
}
