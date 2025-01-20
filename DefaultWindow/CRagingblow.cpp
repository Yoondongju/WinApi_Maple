#include "stdafx.h"
#include "CRagingblow.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CSkillEffect.h"

CRagingblow::CRagingblow()
{
    m_eObjType = OBJID::OBJ_PLAYER_SKILL;
    m_eSkillType = SKILL_TYPE::RAGINGBLOW;
    CreateAnimator();
}

CRagingblow::~CRagingblow()
{
    Release();
}

void CRagingblow::Initialize()
{
    m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
    Vec2 vPos = m_pPlayer->GetPos();

    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y, 700.f , 600.f };
    m_iAttackCount = 9;
   
    m_fSkillAttackInfo = 300;


   

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Ragingblow_left", L"../API/Skill/ragingblow/effect/test/test_A.png");
    GetAnimator()->CreateAnimation(L"Ragingblow_left", pTex, Vec2(0.f, 0.f), Vec2(935.f, 662.f), Vec2(0.f, 662.f), 0.04f, 15);

    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Ragingblow_right", L"../API/Skill/ragingblow/effect/test/test_A_right.png");
    GetAnimator()->CreateAnimation(L"Ragingblow_right", pTex1, Vec2(0.f, 0.f), Vec2(935.f, 662.f), Vec2(0.f, 662.f), 0.04f, 15);



    GetAnimator()->Play(L"Ragingblow_left", false);

    CreateSkillEffect();
}


int CRagingblow::Update()
{
    m_fDelay += fDT;

    if (m_bActivate)
    {
        m_pPlayer->SetPlayerState(PLAYER_STATE::RAGINGBLOW);

        if (m_bDead)
            return OBJ_DEAD;


  


        if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(-200.f, -40.f);
            GetAnimator()->Play(L"Ragingblow_left", false);
        }
        else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(200.f, -40.f);
            GetAnimator()->Play(L"Ragingblow_right", false);
        }

      
        Vec2 vPos = m_pPlayer->GetPos();
        Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);
        PlaySkill();



        m_rtSkillRange =
        {
            (LONG)((m_tInfo.fX - (m_tInfo.fCX / 2.f) + 80.f)),
            (LONG)((m_tInfo.fY - (m_tInfo.fCY / 2.f) + 80.f)),
            (LONG)((m_tInfo.fX + (m_tInfo.fCX / 2.f) - 80.f)),
            (LONG)((m_tInfo.fY + (m_tInfo.fCY / 2.f) - 80.f)),

        };
        __super::Update_Rect();

        return OBJ_NOEVENT;
    }
}

void CRagingblow::Late_Update()
{
    if (m_bActivate)
    {
        GetAnimator()->Update();
    }
}

void CRagingblow::Render(HDC hDC)
{
    if (m_bActivate)
    {
        GetAnimator()->GetCurAnimation()->Render(hDC);



    }

    

}


void CRagingblow::Release()
{
}


void CRagingblow::CreateSkillEffect()
{

}




void CRagingblow::PlaySkill()
{
    INFO playerInfo = m_pPlayer->Get_Info();


    if (GetAnimator()->GetCurAnimation()->GetFinish())
    {
        m_bActivate = false;
        m_pPlayer->SetCastingskill(false);
        GetAnimator()->GetCurAnimation()->SetFrame(0);
        m_pPlayer->GetAnimator()->GetCurAnimation()->SetFrame(0);

    }

}