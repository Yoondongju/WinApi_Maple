#include "stdafx.h"
#include "CUpperCharge.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"

#include "CSkillEffect.h"

CUpperCharge::CUpperCharge()
{
    m_eObjType = OBJID::OBJ_PLAYER_SKILL;
    m_eSkillType = SKILL_TYPE::UPPERCHARGE;
    CreateAnimator();
}

CUpperCharge::~CUpperCharge()
{
    Release();
}

void CUpperCharge::Initialize()
{
    m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
    Vec2 vPos = m_pPlayer->GetPos();




    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y, 800.f , 800.f };

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"UpperCharge_left", L"../API/Skill/uppercharge/effect/test_left.png");
    GetAnimator()->CreateAnimation(L"uppercharge_left", pTex, Vec2(0.f, 8456.f), Vec2(604.f, 604.f), Vec2(0.f, -604.f), 0.06f, 14);

    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"UpperCharge_right", L"../API/Skill/uppercharge/effect/test_right.png");
    GetAnimator()->CreateAnimation(L"uppercharge_right", pTex1, Vec2(0.f, 8456.f), Vec2(604.f, 604.f), Vec2(0.f, -604.f), 0.06f, 14);



    GetAnimator()->Play(L"uppercharge_left", false);

    CreateSkillEffect();
}


int CUpperCharge::Update()
{
    m_fDelay += fDT;

    if (m_bActivate)
    {
        m_pPlayer->SetPlayerState(PLAYER_STATE::UPPERCHAGE);

        if (m_bDead)
            return OBJ_DEAD;


        if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(0.f, -150.f);
            GetAnimator()->Play(L"uppercharge_left", false);
        }
        else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(0.f, -150.f);
            GetAnimator()->Play(L"uppercharge_right", false);
        }

        PlaySkill();

        if (GetAnimator()->GetCurAnimation()->GetFinish())
        {

            GetAnimator()->GetCurAnimation()->SetFrame(0);
            m_pSkillEffect->GetAnimator()->GetCurAnimation()->SetFrame(0);

        }
       



        Vec2 vPos = m_pPlayer->GetPos();
        Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);
        
        __super::Update_Rect();

        return OBJ_NOEVENT;
    }
}

void CUpperCharge::Late_Update()
{
    if (m_bActivate)
    {
        GetAnimator()->Update();
    }
}

void CUpperCharge::Render(HDC hDC)
{
    if (m_bActivate)
    {
        GetAnimator()->GetCurAnimation()->Render(hDC);
    }

}

void CUpperCharge::Release()
{
}


void CUpperCharge::PlaySkill()
{
    INFO playerInfo = m_pPlayer->Get_Info();
    float fY = m_pPlayer->GetTargetLinefY();


    
    playerInfo.fY -= (11 * m_fTime  - ((9.8f * m_fTime * m_fTime) * 0.5));
    m_fTime += 0.015f;


    if (playerInfo.fY + (playerInfo.fCY / 2.f) - 5 > fY)
    {
        m_fTime = 0.f;
        playerInfo.fY = fY - playerInfo.fCY / 2;


        m_bActivate = false;
        m_pPlayer->SetCastingskill(false);
        m_pPlayer->GetAnimator()->GetCurAnimation()->SetFrame(0);
    }


    m_pPlayer->Set_Pos(playerInfo.fX, playerInfo.fY);
}

void CUpperCharge::CreateSkillEffect()
{
    CSkillEffect* pEffect = new CSkillEffect();
    pEffect->Initialize(this);
    CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL_EFFECT, pEffect);
    m_pSkillEffect = pEffect;
}
