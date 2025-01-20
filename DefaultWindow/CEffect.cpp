#include "stdafx.h"
#include "CEffect.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "ObjMgr.h"
#include "CTimeMgr.h"

#include "Player.h"
#include "CAnimation.h"
#include "CAnimator.h"

CEffect::CEffect()
{
    m_eObjType = OBJID::OBJ_EFFECT;
    CreateAnimator();
}

CEffect::~CEffect()
{
}

void CEffect::Initialize()
{
    m_tInfo = { 0.f,0.f, 150.f , 200.f };

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"LEVEL_UP", L"../API/UI/Level_up_A.png");
    GetAnimator()->CreateAnimation(L"LEVEL_UP", pTex, Vec2(0.f, 0.f), Vec2(301.f, 362.f), Vec2(301.f, 0.f), 0.1f, 21);

    GetAnimator()->Play(L"LEVEL_UP", false);
}

int CEffect::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    if (GetAnimator()->GetCurAnimation()->GetFinish())
    {
        return OBJ_DEAD;
    }

    Vec2 vPos = CObjMgr::Get_Instance()->Get_Player()->GetPos();
    Set_Pos(vPos.x, vPos.y - 40.f);


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
    GetAnimator()->Update();
}

void CEffect::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CEffect::Release()
{
}
