#include "stdafx.h"
#include "CMoveEffect.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "ObjMgr.h"
#include "CTimeMgr.h"

#include "Player.h"
#include "CAnimation.h"
#include "CAnimator.h"

CMoveEffect::CMoveEffect()
    : m_BYTE(255)
{
    m_bAffectedCamera = false;
    m_eObjType = OBJID::OBJ_EFFECT;
    CreateAnimator();

}

CMoveEffect::~CMoveEffect()
{
}

void CMoveEffect::Initialize()
{
    m_tInfo = { 0.f,0.f, 150 , 250 };


    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"moveEffect", L"../API/Monster2/moveEffect.png");
    GetAnimator()->CreateAnimation(L"moveEffect", pTex, Vec2(0.f, 0.f), Vec2(197.f, 208.f), Vec2(197.f, 0.f), 0.03f, 6);

    GetAnimator()->Play(L"moveEffect", false);
}

int CMoveEffect::Update()
{
    if (m_bDead || m_BYTE <= 0.f)
        return OBJ_DEAD;



    


    m_BYTE -= 5.f * fDT;
    BLENDFUNCTION bf = GetBf();
    bf.SourceConstantAlpha = m_BYTE;

    SetBf(bf);


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CMoveEffect::Late_Update()
{
    GetAnimator()->Update();
}

void CMoveEffect::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CMoveEffect::Release()
{
}
