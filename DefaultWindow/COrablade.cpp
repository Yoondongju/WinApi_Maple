#include "stdafx.h"
#include "COrablade.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CSkillEffect.h"

COrablade::COrablade()
    : m_vTargetPos(0.f,0.f)
{
    m_eObjType = OBJID::OBJ_PLAYER_SKILL;
    m_eSkillType = SKILL_TYPE::ORABLADE;
    CreateAnimator();
}

COrablade::~COrablade()
{
    Release();
}

void COrablade::Initialize()
{
    m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
    Vec2 vPos = m_pPlayer->GetPos();
    m_iAttackCount = 3;

    m_fSkillAttackInfo = 100;
  

    m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y, 400.f , 300.f };

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_left", L"../API/Skill/orablade/effect/effect_left.png");
    GetAnimator()->CreateAnimation(L"Orablade_left", pTex, Vec2(0.f, 0.f), Vec2(501.f, 357.f), Vec2(501.f, 0.f), 0.03f, 6);

    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_right", L"../API/Skill/orablade/effect/effect_right.png");
    GetAnimator()->CreateAnimation(L"Orablade_right", pTex1, Vec2(0.f, 0.f), Vec2(501.f, 357.f), Vec2(501.f, 0.f), 0.03f, 6);



    CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_up", L"../API/Skill/orablade/effect/effect_up.png");
    GetAnimator()->CreateAnimation(L"Orablade_up", pTex2, Vec2(0.f, 0.f), Vec2(357.f, 501.f), Vec2(0.f, 501.f), 0.03f, 6);

    CTexture* pTex3 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_down", L"../API/Skill/orablade/effect/effect_down.png");
    GetAnimator()->CreateAnimation(L"Orablade_down", pTex3, Vec2(0.f, 0.f), Vec2(357.f, 501.f), Vec2(0.f, 501.f), 0.03f, 6);



    CTexture* pTex4 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_lu", L"../API/Skill/orablade/effect/effect_lu.png");
    GetAnimator()->CreateAnimation(L"Orablade_lu", pTex4, Vec2(0.f, 0.f), Vec2(501.f, 357.f), Vec2(501.f, 0.f), 0.03f, 6);

    CTexture* pTex5 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_ru", L"../API/Skill/orablade/effect/effect_ru.png");
    GetAnimator()->CreateAnimation(L"Orablade_ru", pTex5, Vec2(0.f, 0.f), Vec2(501.f, 357.f), Vec2(501.f, 0.f), 0.03f, 6);



    CTexture* pTex6 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_ld", L"../API/Skill/orablade/effect/effect_ld.png");
    GetAnimator()->CreateAnimation(L"Orablade_ld", pTex6, Vec2(0.f, 0.f), Vec2(501.f, 357.f), Vec2(501.f, 0.f), 0.03f, 6);

    CTexture* pTex7 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_rd", L"../API/Skill/orablade/effect/effect_rd.png");
    GetAnimator()->CreateAnimation(L"Orablade_rd", pTex7, Vec2(0.f, 0.f), Vec2(501.f, 357.f), Vec2(501.f, 0.f), 0.03f, 6);



    GetAnimator()->Play(L"Orablade_left", true);

    CreateSkillEffect();
}


int COrablade::Update()
{
    m_fDelay += fDT;


    if (m_bActivate)
    {
        m_pPlayer->SetPlayerState(PLAYER_STATE::ORABLADE);

        if (m_bDead)
            return OBJ_DEAD;

       

        Vec2 vPos = m_pPlayer->GetPos();
        m_vStartPos = Vec2(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);
        PlaySkill();
       


        m_rtSkillRange =
        {
            (LONG)((m_tInfo.fX - (m_tInfo.fCX / 2.f) + 40.f)),
            (LONG)((m_tInfo.fY - (m_tInfo.fCY / 2.f) + 40.f)),
            (LONG)((m_tInfo.fX + (m_tInfo.fCX / 2.f) - 40.f)),
            (LONG)((m_tInfo.fY + (m_tInfo.fCY / 2.f) - 40.f)),

        };

        __super::Update_Rect();

        return OBJ_NOEVENT;
    }


}

void COrablade::Late_Update()
{
    if (m_bActivate)
    {
        GetAnimator()->Update();
    }
}

void COrablade::Render(HDC hDC)
{
    if (m_bActivate)
    {
        GetAnimator()->GetCurAnimation()->Render(hDC);


        //CPlayerSkill::Render(hDC);    범위그려주는거 지울거임 이제
    }

    

}


void COrablade::Release()
{
}


void COrablade::CreateSkillEffect()
{
    CSkillEffect* pEffect = new CSkillEffect();
    pEffect->Initialize(this);
    CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PLAYER_SKILL_EFFECT, pEffect);
    m_pSkillEffect = pEffect;
}




void COrablade::PlaySkill()
{
    INFO playerInfo = m_pPlayer->Get_Info();
   
  
    if (0.f == m_vTargetPos.x
        && 0.f == m_vTargetPos.y)
    {
        m_fAngle = m_pPlayer->GetAngle();

        switch ((int)m_fAngle)
        {
        case 0:
            GetAnimator()->Play(L"Orablade_right", true);
            break;

        case 45:
            GetAnimator()->Play(L"Orablade_ru", true);
            break;

        case 90:
            GetAnimator()->Play(L"Orablade_up", true);
            break;

        case 135:
            GetAnimator()->Play(L"Orablade_lu", true);
            break;

        case 180:
            GetAnimator()->Play(L"Orablade_left", true);
            break;

        case 225:
            GetAnimator()->Play(L"Orablade_ld", true);
            break;

        case 270:
            GetAnimator()->Play(L"Orablade_down", true);
            break;

        case 315:
            GetAnimator()->Play(L"Orablade_rd", true);
            break;

        default:
            break;
        }
        

        m_tInfo.fX = m_vStartPos.x;
        m_tInfo.fY = m_vStartPos.y;

        m_vTargetPos.x = m_tInfo.fX + 700 * cos(m_fAngle * PI / 180.f);
        m_vTargetPos.y = m_tInfo.fY - 700 * sin(m_fAngle * PI / 180.f);
    }
    
    if (abs(m_tInfo.fX - m_vTargetPos.x) > 5)
    {
        m_tInfo.fX += 700 * cos(m_fAngle * PI / 180.f) * fDT*2;
    }
    if (abs(m_tInfo.fY - m_vTargetPos.y) > 5)
    {       
        m_tInfo.fY -= 700 * sin(m_fAngle * PI / 180.f) * fDT*2;
    }
   
    if (abs(m_tInfo.fX - m_vTargetPos.x) < 5
        && abs(m_tInfo.fY - m_vTargetPos.y) < 5) 
    {
        m_vTargetPos = 0.f;
        m_bActivate = false;
        m_pPlayer->SetCastingskill(false);
        GetAnimator()->GetCurAnimation()->SetFrame(0);
        m_pPlayer->GetAnimator()->GetCurAnimation()->SetFrame(0);

        m_pSkillEffect->GetAnimator()->GetCurAnimation()->SetFrame(0);
    }

    Set_Pos(m_tInfo.fX, m_tInfo.fY);

}