#include "stdafx.h"
#include "CBall.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CTimeMgr.h"

#include "CPlayerSkill.h"
#include "CDamageEffect.h"


#include "CWill_Page1.h"


CBall::CBall()
{
    CreateAnimator();
}

CBall::~CBall()
{
}

void CBall::Initialize(Vec2 _v, MONSTER_DIR _e, WILL_PAGE _ePage)
{ 
    m_eObjType = OBJID::OBJ_BOSS_SKILL;
    m_eDir = _e;
    m_ePage = _ePage;
    
    m_fSpeed = 100.f;


    if (WILL_PAGE::PAGE1 == m_ePage)
    {
        m_tInfo = { _v.x ,_v.y ,200.f,380.f };
        CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"ball_left", L"../API/Boss/page1/attack3_ball_left.png");
        GetAnimator()->CreateAnimation(L"ball_left", pTex, Vec2(0.f, 0.f), Vec2(344.f, 525.f), Vec2(344.f, 0.f), 0.07, 10);

        CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"ball_right", L"../API/Boss/page1/attack3_ball_right.png");
        GetAnimator()->CreateAnimation(L"ball_right", pTex1, Vec2(0.f, 0.f), Vec2(344.f, 525.f), Vec2(344.f, 0.f), 0.07, 10);

        GetAnimator()->Play(L"ball_left", true);
    }
    else if (WILL_PAGE::PAGE2 == m_ePage)
    {
        m_tInfo = { _v.x ,_v.y ,200.f,190.f };
        CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"ball2_left", L"../API/Boss/page2/attack3_ball_left.png");
        GetAnimator()->CreateAnimation(L"ball2_left", pTex, Vec2(0.f, 0.f), Vec2(290.f, 173.f), Vec2(290.f, 0.f), 0.05, 8);

        CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"ball2_right", L"../API/Boss/page2/attack3_ball_right.png");
        GetAnimator()->CreateAnimation(L"ball2_right", pTex1, Vec2(0.f, 0.f), Vec2(290.f, 173.f), Vec2(290.f, 0.f), 0.05, 8);

        GetAnimator()->Play(L"ball2_left", true);
    }
   
}

int CBall::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


    if (WILL_PAGE::PAGE1 == m_ePage)
    {
        switch (m_eDir)
        {
        case MONSTER_DIR::LEFT:
            m_tInfo.fX -= 400 * fDT;
            GetAnimator()->Play(L"ball_left", true);
            break;
        case MONSTER_DIR::RIGHT:
            m_tInfo.fX += 400 * fDT;
            GetAnimator()->Play(L"ball_right", true);
            break;
        case MONSTER_DIR::END:
            break;
        default:
            break;
        }
    }

    else if (WILL_PAGE::PAGE2 == m_ePage)
    {
        switch (m_eDir)
        {
        case MONSTER_DIR::LEFT:
            m_tInfo.fX -= 300 * fDT;
            GetAnimator()->Play(L"ball2_left", true);
            break;
        case MONSTER_DIR::RIGHT:
            m_tInfo.fX += 300 * fDT;
            GetAnimator()->Play(L"ball2_right", true);
            break;
        case MONSTER_DIR::END:
            break;
        default:
            break;
        }
    }

    



    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CBall::Late_Update()
{ 
    if (m_tInfo.fX <= 0
        || m_tInfo.fX >= WINCX)
    {
        // 삭제
        Set_Dead();     // 보스죽으면 CObj에서 관리하는 스레기들 삭제해줄예정
        ((CWill_Page1*)CObjMgr::Get_Instance()->Get_Will())->SetBall_NULL_INIT();
    }





    GetAnimator()->Update();
}

void CBall::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);



    //SelectGDI p1(hDC, PEN_TYPE::RED);
    //SelectGDI b1(hDC, BRUSH_TYPE::HOLLOW);
    //
    //
    //Vec2 vPos1 = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
    //
    //Rectangle(hDC
    //    , (int)(vPos1.x - m_tInfo.fCX * 0.5f)
    //    , (int)(vPos1.y - m_tInfo.fCY * 0.5f)
    //    , (int)(vPos1.x + m_tInfo.fCX * 0.5f)
    //    , (int)(vPos1.y + m_tInfo.fCY * 0.5f));
}

void CBall::Release()
{
}
