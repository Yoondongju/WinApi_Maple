#include "stdafx.h"
#include "CMoney.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "ObjMgr.h"

#include "Player.h"
#include "CPet.h"

#include "CTimeMgr.h"

#include "CSound.h"

CMoney::CMoney()
    : m_pPet(nullptr)
    , m_bMagnetState(false)
{
    CreateAnimator();
}

CMoney::~CMoney()
{
}

void CMoney::Initialize(Vec2 _v, int _iPrice)
{
    m_tInfo = { _v.x , _v.y + 50.f , 40.f , 40.f };
    m_iPrice = _iPrice;
    m_eObjType = OBJID::OBJ_MESO;


    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Money", L"../API/UI/meso.png");
    GetAnimator()->CreateAnimation(L"Money", pTex, Vec2(0.f, 0.f), Vec2(35.f, 32.f), Vec2(35.f, 0.f), 0.15f, 4);

    GetAnimator()->Play(L"Money", true);
}

int CMoney::Update()
{
    if (m_bDead)
        return OBJ_DEAD;


    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CMoney::Late_Update()
{
    if (m_bMagnetState)
    {
        Vec2 vPos = m_pPet->GetPos();

        float fWid = (vPos.x - m_tInfo.fX);
        float fHei = (vPos.y - m_tInfo.fY);
        float fDistance = sqrt((fWid * fWid) + (fHei * fHei));

        float fRadian = acos(fWid / fDistance);

        

        if (abs(vPos.x - m_tInfo.fX) < 10
            && abs(vPos.y - m_tInfo.fY) < 10)
        {
            CPlayer* pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
            pPlayer->SetMeso(pPlayer->GetMeso() + m_iPrice);

            CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"meso");
            pNewSound->Play(false);
            pNewSound->SetPosition(1.f); // 백분률 , 소리위치
            pNewSound->SetVolume(50.f); // 소리 볼륨 크기

            Set_Dead();
        }

        if (abs(vPos.x - m_tInfo.fX) > 10)
            m_tInfo.fX += 1100 * cos(fRadian) * fDT;        // 방향이 갱신안되고잇구나
        else
            m_tInfo.fX = vPos.x;


        if (vPos.y > m_tInfo.fY)
            fRadian = (2 * PI) - fRadian;

        if (abs(vPos.y - m_tInfo.fY) > 10)
            m_tInfo.fY -= 1100 * sin(fRadian) * fDT;
        else
            m_tInfo.fY = vPos.y;
    }


    GetAnimator()->Update();
}

void CMoney::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);

}

void CMoney::Release()
{
}
