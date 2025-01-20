#include "stdafx.h"
#include "CDeathfault.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CSkillEffect.h"

CDeathfault::CDeathfault()
{
    m_eObjType = OBJID::OBJ_PLAYER_SKILL;
    m_eSkillType = SKILL_TYPE::DEATHFAULT;
    CreateAnimator();
}

CDeathfault::~CDeathfault()
{
    Release();
}

void CDeathfault::Initialize()
{
    m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
    Vec2 vPos = m_pPlayer->GetPos();
    m_iAttackCount = 10;

    m_fSkillAttackInfo = 1000;

    m_rtSkillRange = { 0,0,WINCX,WINCY };

    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y, WINCX , WINCY };

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Deathfault", L"../API/Skill/deathfault/effect/effect_final.png");
    GetAnimator()->CreateAnimation(L"Deathfault", pTex, Vec2(0.f, 0.f), Vec2(685.f, 384.f), Vec2(685.f, 0.f), 0.06f, 25);
    
    
    
    GetAnimator()->Play(L"Deathfault", false);

    CreateSkillEffect();
}


int CDeathfault::Update()
{
    m_fDelay += fDT;

    if (m_bActivate)
    {
        m_pPlayer->SetPlayerState(PLAYER_STATE::DEATHFAULT);

        if (m_bDead)
            return OBJ_DEAD;

        



        int iFrm = GetAnimator()->GetCurAnimation()->GetFrame();

        if (GetAnimator()->GetCurAnimation()->GetAllFrame().size() - 15 == iFrm)
        {
            Vec2 vPosCam = CCamera::CreateSingleTonInst()->GetLookAt();
            static bool bCheck = false;
            if (!bCheck)
            {
                vPosCam.y -= 27.f;
                bCheck = true;
            }
            else
            {
                vPosCam.y += 27.f;
                bCheck = false;
            }
            CCamera::CreateSingleTonInst()->SetLookAt(vPosCam);
        }


     

        if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(0.f, 0.f);
            GetAnimator()->Play(L"Deathfault", false);
        }
        else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
        {
            m_vOffset = Vec2(0.f, 0.f);
            GetAnimator()->Play(L"Deathfault", false);
        }

        PlaySkill();

        Vec2 vPos = m_pPlayer->GetPos();
        Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);

      
        __super::Update_Rect();
        

        return OBJ_NOEVENT;
    }
}

void CDeathfault::Late_Update()
{
    if (m_bActivate)
    {
        GetAnimator()->Update();
    }
}

void CDeathfault::Render(HDC hDC)
{
    if (m_bActivate)
    {
        GetAnimator()->GetCurAnimation()->Render(hDC);


       
    }

    

}


void CDeathfault::Release()
{
}


void CDeathfault::CreateSkillEffect()
{
    CSkillEffect* pEffect = new CSkillEffect();
    pEffect->Initialize(this);
    CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL_EFFECT, pEffect);
    m_pSkillEffect = pEffect;
}




void CDeathfault::PlaySkill()
{
    INFO playerInfo = m_pPlayer->Get_Info();
    
    // 데미지가 다 출력되기까지 0.1 * 15번 1.5초가걸림
    static float m_fCount(1.5f);

    if (m_fCount <= 0.f)
    {
        m_bActivate = false;
        m_pPlayer->SetCastingskill(false);
        GetAnimator()->GetCurAnimation()->SetFrame(0);
        m_pPlayer->GetAnimator()->GetCurAnimation()->SetFrame(0);

        m_pSkillEffect->GetAnimator()->GetCurAnimation()->SetFrame(0);
        m_fCount = 1.5f;
    }

    m_fCount -= fDT;


}
