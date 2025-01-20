#include "stdafx.h"
#include "CRail.h"

#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CResMgr.h"

CRail::CRail()
{
    m_bAffectedCamera = false;
    CreateAnimator();
}

CRail::~CRail()
{
}

void CRail::Initialize()
{
    m_tInfo = { WINCX / 2.f ,WINCY / 2.f,  WINCX ,WINCY };
    m_eObjType = OBJID::OBJ_WALL;


    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"rail", L"../API/Monster2/rail_main_test.png");
    GetAnimator()->CreateAnimation(L"rail", pTex, Vec2(0.f, 0.f), Vec2(795.f, 388.f), Vec2(795.f, 0.f), 0.05, 4);

    GetAnimator()->Play(L"rail", true);
}

int CRail::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CRail::Late_Update()
{
    GetAnimator()->Update();
}

void CRail::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CRail::Release()
{
}
