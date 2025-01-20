#include "stdafx.h"
#include "CSixEffect.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "ObjMgr.h"
#include "CTimeMgr.h"

#include "Player.h"
#include "CAnimation.h"
#include "CAnimator.h"

CSixEffect::CSixEffect()
{
    m_bAffectedCamera = false;
    m_eObjType = OBJID::OBJ_EFFECT;
    CreateAnimator();
}

CSixEffect::~CSixEffect()
{
}

void CSixEffect::Initialize()
{
    m_tInfo = { 0.f,0.f, WINCX , WINCY };

    
    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"sixEffect", L"../API/SKill/six/test_A.png");
    GetAnimator()->CreateAnimation(L"sixEffect_1", pTex, Vec2(0.f, 0.f), Vec2(1400.f, 800.f), Vec2(1400.f, 0.f), 0.07f, 8);
    GetAnimator()->CreateAnimation(L"sixEffect_2", pTex, Vec2(0.f, 800.f), Vec2(1400.f, 800.f), Vec2(1400.f, 0.f), 0.07f, 8);
    GetAnimator()->CreateAnimation(L"sixEffect_3", pTex, Vec2(0.f, 1600.f), Vec2(1400.f, 800.f), Vec2(1400.f, 0.f), 0.07f, 8);
    GetAnimator()->CreateAnimation(L"sixEffect_4", pTex, Vec2(0.f, 2400.f), Vec2(1400.f, 800.f), Vec2(1400.f, 0.f), 0.07f, 8);
    GetAnimator()->CreateAnimation(L"sixEffect_5", pTex, Vec2(0.f, 3200.f), Vec2(1400.f, 800.f), Vec2(1400.f, 0.f), 0.07f, 8);

    GetAnimator()->Play(L"sixEffect_1", false);
}

int CSixEffect::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


    if (GetAnimator()->GetCurAnimation()->GetFinish())
    {
        if (L"sixEffect_1" == GetAnimator()->GetCurAnimation()->GetKey())
        {
            GetAnimator()->GetCurAnimation()->SetFrame(0);
            GetAnimator()->Play(L"sixEffect_2", false);
        }

        else  if (L"sixEffect_2" == GetAnimator()->GetCurAnimation()->GetKey())
        {
            GetAnimator()->GetCurAnimation()->SetFrame(0);
            GetAnimator()->Play(L"sixEffect_3", false);
        }

        else  if (L"sixEffect_3" == GetAnimator()->GetCurAnimation()->GetKey())
        {
            GetAnimator()->GetCurAnimation()->SetFrame(0);
            GetAnimator()->Play(L"sixEffect_4", false);
        }

        else  if (L"sixEffect_4" == GetAnimator()->GetCurAnimation()->GetKey())
        {
            GetAnimator()->GetCurAnimation()->SetFrame(0);
            GetAnimator()->Play(L"sixEffect_5", false);
        }

        else  if (L"sixEffect_5" == GetAnimator()->GetCurAnimation()->GetKey())
        {
            return OBJ_DEAD;
        }

    }


    __super::Update_Rect();

    return OBJ_NOEVENT;

}


void CSixEffect::Late_Update()
{
    GetAnimator()->Update();
}

void CSixEffect::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CSixEffect::Release()
{
}