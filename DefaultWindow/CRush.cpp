#include "stdafx.h"
#include "CRush.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CSkillEffect.h"

CRush::CRush()
    :m_fTarGetX(0.f)
{
    m_eObjType = OBJID::OBJ_PLAYER_SKILL;
    m_eSkillType = SKILL_TYPE::RUSH;
    CreateAnimator();
}

CRush::~CRush()
{
    Release();
}

void CRush::Initialize()
{
    m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
    Vec2 vPos = m_pPlayer->GetPos();
    m_iAttackCount = 3;

    m_fSkillAttackInfo = 100;
  
    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y, 700.f , 400.f };
    m_fPower = 400.f;


    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"rush_left", L"../API/Skill/rush/effect/effect_left.png");
    GetAnimator()->CreateAnimation(L"rush_left", pTex, Vec2(0.f, 0.f), Vec2(798.f, 435.f), Vec2(0.f, 435.f), 0.03f, 13);


    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"rush_right", L"../API/Skill/rush/effect/effect_right.png");
    GetAnimator()->CreateAnimation(L"rush_right", pTex1, Vec2(0.f, 0.f), Vec2(798.f, 435.f), Vec2(0.f, 435.f), 0.03f, 13);


    GetAnimator()->Play(L"rush_right", false);

    CreateSkillEffect();
}


int CRush::Update()
{
    m_fDelay += fDT;

    if (m_bActivate)
    {
        m_pPlayer->SetPlayerState(PLAYER_STATE::RUSH);

        if (m_bDead)
            return OBJ_DEAD;


       


        if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(0.f, 0.f);
            GetAnimator()->Play(L"rush_left", false);
        }
        else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(0.f, 0.f);
            GetAnimator()->Play(L"rush_right", false);
        }

       
        Vec2 vPos = m_pPlayer->GetPos();
        Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);
        PlaySkill();


        m_rtSkillRange =
        {
            (LONG)((m_tInfo.fX - (m_tInfo.fCX / 2.f) + 150.f)),
            (LONG)((m_tInfo.fY - (m_tInfo.fCY / 2.f) + 150.f)),
            (LONG)((m_tInfo.fX + (m_tInfo.fCX / 2.f) - 150.f)),
            (LONG)((m_tInfo.fY + (m_tInfo.fCY / 2.f) - 150.f)),

        };

        __super::Update_Rect();

        return OBJ_NOEVENT;
    }
}

void CRush::Late_Update()
{
    if (m_bActivate)
    {
        GetAnimator()->Update();
    }
}

void CRush::Render(HDC hDC)
{
    if (m_bActivate)
    {
        GetAnimator()->GetCurAnimation()->Render(hDC);

   
    }

    
}

void CRush::Release()
{
}


void CRush::PlaySkill()
{ 
    INFO playerInfo = m_pPlayer->Get_Info();
    PLAYER_DIR eDir = m_pPlayer->GetPlayerDir();


    


    if (m_pPlayer->GetLand())
    {
        if (0.f == m_fTarGetX)
        {
            if (PLAYER_DIR::LEFT == eDir)
            {
                m_fTarGetX = playerInfo.fX - m_fPower;
            }
            else if (PLAYER_DIR::RIGHT == eDir)
            {
                m_fTarGetX = playerInfo.fX + m_fPower;
            }
        }

        if (abs(playerInfo.fX - m_fTarGetX) > 40 )
        {
            if (PLAYER_DIR::LEFT == eDir)
            {
                playerInfo.fX -= m_fPower * fDT*4;
            }

            else if (PLAYER_DIR::RIGHT == eDir)
            {
                playerInfo.fX += m_fPower * fDT*4;
            }
        }
        else
        {
            GetAnimator()->GetCurAnimation()->SetFrame(0);
            m_bActivate = false;
            m_pPlayer->SetCastingskill(false);
            m_pPlayer->GetAnimator()->GetCurAnimation()->SetFrame(0);
            m_pSkillEffect->GetAnimator()->GetCurAnimation()->SetFrame(0);

            playerInfo.fX = m_fTarGetX;
            m_fTarGetX = 0.f;
        }
        m_pPlayer->Set_Pos(playerInfo.fX, playerInfo.fY);    

    }
 
}

void CRush::CreateSkillEffect()
{
    CSkillEffect* pEffect = new CSkillEffect();
    pEffect->Initialize(this);
    CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL_EFFECT, pEffect);
    m_pSkillEffect = pEffect;
}
