#include "stdafx.h"
#include "CSixSkill.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"

CSixSkill::CSixSkill()
{
    m_bAffectedCamera = false;
    m_eObjType = OBJID::OBJ_PLAYER_SKILL;
    m_eSkillType = SKILL_TYPE::SIX;
    CreateAnimator();
}

CSixSkill::~CSixSkill()
{
    Release();
}

void CSixSkill::Initialize()
{
    m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
    Vec2 vPos = m_pPlayer->GetPos();
    m_iAttackCount = 18;

    m_fSkillAttackInfo = 270;

    m_rtSkillRange = { 0,0,WINCX,WINCY };

    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y, WINCX , WINCY };

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"six", L"../API/Skill/six/six_A.png");


    
    float iSizeY = 768;
    GetAnimator()->CreateAnimation(L"six_1", pTex, Vec2(0.f, 0.f), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_2", pTex, Vec2(0.f, iSizeY), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_3", pTex, Vec2(0.f, iSizeY *2), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_4", pTex, Vec2(0.f, iSizeY *3), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_5", pTex, Vec2(0.f, iSizeY *4), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_6", pTex, Vec2(0.f, iSizeY *5), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_7", pTex, Vec2(0.f, iSizeY *6), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_8", pTex, Vec2(0.f, iSizeY *7), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_9", pTex, Vec2(0.f, iSizeY * 8), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_10", pTex, Vec2(0.f, iSizeY * 9), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 11);
    GetAnimator()->CreateAnimation(L"six_11", pTex, Vec2(0.f, iSizeY * 10), Vec2(1368.f, 768.f), Vec2(1368.f, 0.f), 0.06f, 7);

    GetAnimator()->Play(L"six_1", false);

    
}

int CSixSkill::Update()
{
    m_fDelay += fDT;

    if (m_bActivate)
    {     
        if (m_bDead)
            return OBJ_DEAD;

        m_pPlayer->SetPlayerState(PLAYER_STATE::SIX);


       

        if (GetAnimator()->GetCurAnimation()->GetFinish())
        {
            if (L"six_1" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_2", false);
            }
               
            else  if (L"six_2" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_3", false);
            }
               
            else  if (L"six_3" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_4", false);
            }

            else  if (L"six_4" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_5", false);
            }

            else  if (L"six_5" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_6", false);
            }

            else  if (L"six_6" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_7", false);
            }

            else  if (L"six_7" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_8", false);
            }

            else  if (L"six_8" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_9", false);
            }

            else  if (L"six_9" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_10", false);
            }

            else  if (L"six_10" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_11", false);
            }

            else  if (L"six_11" == GetAnimator()->GetCurAnimation()->GetKey())
            {
                GetAnimator()->GetCurAnimation()->SetFrame(0);
                GetAnimator()->Play(L"six_1", false);
                m_bActivate = false;
                m_pPlayer->SetCastingskill(false);
            }
        }

        //m_pPlayer->GetAnimator()->GetCurAnimation()->SetFrame(0);
 
            


        __super::Update_Rect();

        return OBJ_NOEVENT;
    }
}

void CSixSkill::Late_Update()
{  
    if (m_bActivate)
    {
        GetAnimator()->Update();
    }
        
}

void CSixSkill::Release()
{
  
}

void CSixSkill::CreateSkillEffect()
{
}

void CSixSkill::PlaySkill()
{
}

void CSixSkill::Render(HDC hDC)
{
    if (m_bActivate)
    {
        GetAnimator()->GetCurAnimation()->Render(hDC);

    }
}
