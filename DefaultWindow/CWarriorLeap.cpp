#include "stdafx.h"
#include "CWarriorLeap.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CResMgr.h"
#include "CTexture.h"

CWarriorLeap::CWarriorLeap()
{
    m_eObjType = OBJID::OBJ_PLAYER_SKILL;
    CreateAnimator();
}

CWarriorLeap::~CWarriorLeap()
{
    Release();
}

void CWarriorLeap::Initialize()
{
    m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
    Vec2 vPos = m_pPlayer->GetPos();




    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y, 270.f , 270.f };

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"warriorleap_left", L"../API/Skill/warriorleap/effect/effect_left.png");
    GetAnimator()->CreateAnimation(L"warriorleap_left", pTex, Vec2(0.f, 0.f), Vec2(352.f, 216.f), Vec2(0.f, 216.f), 0.03f, 7);

    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"warriorleap_right", L"../API/Skill/warriorleap/effect/effect_right.png");
    GetAnimator()->CreateAnimation(L"warriorleap_right", pTex1, Vec2(0.f, 0.f), Vec2(352.f, 216.f), Vec2(0.f, 216.f), 0.03f, 7);


    GetAnimator()->Play(L"warriorleap_right", false);
}

int CWarriorLeap::Update()
{
     //��ų���� ��Ȱ��ȭ �ϴ� ������ �ִϸ��̼��� ���������� �ƴ϶� ��ų�� �´� �ൿ�� ���� ���Ŀ�����
    if (m_bActivate)
    {
        if (m_bDead)
            return OBJ_DEAD;

        CAnimation* pAni = GetAnimator()->GetCurAnimation();
        if (pAni->GetFinish())
        {
            pAni->SetFrame(0);
            m_bActivate = false;
        }



        if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(160.f, 30.f);
            GetAnimator()->Play(L"warriorleap_left", false);
        }
        else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(-160.f, 30.f);
            GetAnimator()->Play(L"warriorleap_right", false);
        }


        Vec2 vPos = m_pPlayer->GetPos();
        Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);

        __super::Update_Rect();

        return OBJ_NOEVENT;
    }  
}

void CWarriorLeap::Late_Update()
{
    if (m_bActivate)
    {
        GetAnimator()->Update();
    }    
}

void CWarriorLeap::Render(HDC hDC)
{
    if (m_bActivate) 
    {
        GetAnimator()->GetCurAnimation()->Render(hDC);
    }
   
}

void CWarriorLeap::Release()
{
}
