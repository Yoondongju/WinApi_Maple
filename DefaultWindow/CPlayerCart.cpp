#include "stdafx.h"
#include "CPlayerCart.h"

#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CResMgr.h"

#include "CKeyMgr.h"
#include "ObjMgr.h"

#include "CCamera.h"
#include "CBoom.h"

#include "CSound.h"

#include "CMoveEffect.h"

CPlayerCart::CPlayerCart()
    : m_bGameOver(false)
{
    m_bAffectedCamera = false;
    CreateAnimator();
}

CPlayerCart::~CPlayerCart()
{
}

void CPlayerCart::Initialize()
{
    m_tInfo = { WINCX / 2.f ,600,  200 ,300 };
    m_eObjType = OBJID::OBJ_MINIGAMEOBJ;


    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"cart", L"../API/Monster2/cart_test.png");
    GetAnimator()->CreateAnimation(L"cart", pTex, Vec2(0.f, 0.f), Vec2(110.f, 185.f), Vec2(0.f, 0.f), 0.1, 1);

    CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"cart_left", L"../API/Monster2/cart_test_left.png");
    GetAnimator()->CreateAnimation(L"cart_left", pTex1, Vec2(0.f, 0.f), Vec2(110.f, 185.f), Vec2(0.f, 0.f), 0.1, 1);

    CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"cart_right", L"../API/Monster2/cart_test_right.png");
    GetAnimator()->CreateAnimation(L"cart_right", pTex2, Vec2(0.f, 0.f), Vec2(110.f, 185.f), Vec2(0.f, 0.f), 0.1, 1);


    GetAnimator()->Play(L"cart", true);
}

int CPlayerCart::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    
    static float leftX = 238;
    static float middleX = 640;
    static float rightX = 1042;


    if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
    {
        if (m_tInfo.fX == rightX)
            m_tInfo.fX = middleX;
        else
            m_tInfo.fX = leftX;



        CMoveEffect* pEffect = new CMoveEffect;
        pEffect->Initialize();
        pEffect->Set_Pos(m_tInfo.fX, m_tInfo.fY);
        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_EFFECT, pEffect);


        CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"railmove");
        pNewSound->Play(false);
        pNewSound->SetPosition(1.f); // 백분률 , 소리위치
        pNewSound->SetVolume(60.f); // 소리 볼륨 크기

    }

    if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
    {
        if (m_tInfo.fX == leftX)
            m_tInfo.fX = middleX;
        else
            m_tInfo.fX = rightX;


        CMoveEffect* pEffect = new CMoveEffect;
        pEffect->Initialize();
        pEffect->Set_Pos(m_tInfo.fX, m_tInfo.fY);
        CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_EFFECT, pEffect);



        CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"railmove");
        pNewSound->Play(false);
        pNewSound->SetPosition(1.f); // 백분률 , 소리위치
        pNewSound->SetVolume(60.f); // 소리 볼륨 크기

    }
    
 
    if(m_tInfo.fX == middleX)
        GetAnimator()->Play(L"cart", true);
    else if (m_tInfo.fX == leftX)
        GetAnimator()->Play(L"cart_left", true);
    else if (m_tInfo.fX == rightX)
        GetAnimator()->Play(L"cart_right", true);

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CPlayerCart::Late_Update()
{
    if (m_bGameOver && CCamera::CreateSingleTonInst()->IsEffectEnd())
    {
        ChangeScene(SCENE_TYPE::LOBBY);
    }


   CBoom* pBoom = dynamic_cast<CBoom*>(CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MINIGAMEOBJ).back());

   if (pBoom)
   {
       INFO vBoomPos = pBoom->Get_Info();

       float	fWidth = abs(m_tInfo.fX - vBoomPos.fX);
       float	fHeight = abs(m_tInfo.fY - vBoomPos.fY);

       float	fRadiusX = (m_tInfo.fCX + vBoomPos.fCX) * 0.5f;
       float	fRadiusY = (m_tInfo.fCY + vBoomPos.fCY) * 0.5f;


       if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))	// 충돌
       {
           m_bGameOver = true;

           CSound* pNewSound = CResMgr::CreateSingleTonInst()->FindSound(L"collboom");
           pNewSound->Play(false);
           pNewSound->SetPosition(1.f);
           pNewSound->SetVolume(60.f); 

           CCamera::CreateSingleTonInst()->FadeOut(3.f);
       }
   }


  

    GetAnimator()->Update();
}

void CPlayerCart::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CPlayerCart::Release()
{
}
