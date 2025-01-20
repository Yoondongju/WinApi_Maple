#include "stdafx.h"
#include "CWall.h"

#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CResMgr.h"

CWall::CWall()
{
    m_bAffectedCamera = false;
    CreateAnimator();
}

CWall::~CWall()
{
}

void CWall::Initialize()
{
    m_tInfo = { WINCX / 2.f ,WINCY / 2.f,  WINCX ,WINCY };
    m_eObjType = OBJID::OBJ_WALL;


   CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"wall", L"../API/Monster2/map_main_test.png");
   GetAnimator()->CreateAnimation(L"wall", pTex, Vec2(0.f, 0.f), Vec2(312.5f, 234.f), Vec2(312.5f, 0.f), 0.05, 16);

    GetAnimator()->Play(L"wall", true);
}

int CWall::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CWall::Late_Update()
{
    GetAnimator()->Update();
}

void CWall::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CWall::Release()
{
}
