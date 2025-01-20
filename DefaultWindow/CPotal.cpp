#include "stdafx.h"
#include "CPotal.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"

#include "CResMgr.h"
#include "SelectGDI.h"

CPotal::CPotal()
{
    CreateAnimator();
}

CPotal::~CPotal()
{
}



void CPotal::Initialize(Vec2 _vPos , SCENE_TYPE _e)
{ // 씬마다 위치가 달라야함 

    m_tInfo = { _vPos.x, _vPos.y ,100.f,200.f };
    m_eObjType = OBJID::OBJ_POTAL;
    m_eMoveSceneType = _e;

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Potal", L"../API/UI/Potal.png");
    GetAnimator()->CreateAnimation(L"Potal", pTex, Vec2(0.f, 0.f), Vec2(89.f, 257.f), Vec2(89.f, 0.f), 0.05, 7);

    GetAnimator()->Play(L"Potal", true);

}


int CPotal::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CPotal::Late_Update()
{
    GetAnimator()->Update();
}

void CPotal::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);

    //SelectGDI p(hDC, PEN_TYPE::GREEN);
    //SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);
    //
    //
    //
    //
    //Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY+150));
    //
    //Rectangle(hDC
    //    , (int)(vPos.x - m_tInfo.fCX / 2.f)
    //    , (int)(vPos.y - m_tInfo.fCY / 2.f)
    //    , (int)(vPos.x + m_tInfo.fCX / 2.f)
    //    , (int)(vPos.y + m_tInfo.fCY / 2.f));
}

void CPotal::Release()
{
}
