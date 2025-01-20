#include "stdafx.h"
#include "CStone.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "ObjMgr.h"
#include "CTimeMgr.h"

#include "Player.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CSound.h"

CStone::CStone()
{
    m_eObjType = OBJID::OBJ_BACKGROUD;
    CreateAnimator();
}

CStone::~CStone()
{
}

void CStone::Initialize()
{
    CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"player_die");
    pNewSound->Play(false);
    pNewSound->SetPosition(1.f); // 백분률 , 소리위치
    pNewSound->SetVolume(100.f); // 소리 볼륨 크기
    
    m_tInfo = { CObjMgr::Get_Instance()->Get_Player()->GetPos().x ,0.f, 50.f , 56.f };

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"die", L"../API/UI/die.png");
    GetAnimator()->CreateAnimation(L"die", pTex, Vec2(0.f, 0.f), Vec2(42.f, 48.f), Vec2(42.f, 0.f), 0.07f, 11);

    GetAnimator()->Play(L"die", true);
}

int CStone::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    CPlayer* pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();

    if(!pPlayer->GetFakeDead())
    {
        return OBJ_DEAD;
    }

    if(pPlayer->GetPos().y > m_tInfo.fY)
        m_tInfo.fY += 900 * fDT;


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CStone::Late_Update()
{
    GetAnimator()->Update();
}

void CStone::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CStone::Release()
{
}
