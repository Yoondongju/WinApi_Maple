#include "stdafx.h"
#include "CBoom.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CResMgr.h"

#include <random>

#include "CTimeMgr.h"


CBoom::CBoom()
{
    m_bAffectedCamera = false;
    
    srand(time(nullptr));
    CreateAnimator();
}

CBoom::~CBoom()
{
}

void CBoom::Initialize()
{
    m_tInfo = { WINCX / 2.f , 0 ,  1 ,1 };

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> distX(0, 2);
    float randNumX = distX(mt);


    m_iCount = randNumX;

    if (m_iCount == 0)
    {
        m_tInfo.fX = 600;
    }
    else if (m_iCount == 1)
    {
        m_tInfo.fX = 640;
    }

    else if (m_iCount == 2)
    {
        m_tInfo.fX = 680;
    }


    m_eObjType = OBJID::OBJ_MINIGAMEOBJ;


    

    CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"boom", L"../API/Monster2/monster.png");
    GetAnimator()->CreateAnimation(L"boom", pTex, Vec2(0.f, 0.f), Vec2(57.f, 85.16f), Vec2(0.f, 85.16f), 0.05, 6);

    GetAnimator()->Play(L"boom", true);
}

int CBoom::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    static float leftX = 640 - 213;
    static float middleX = 640;
    static float rightX = 640 + 213;

    if (m_iCount == 0)
    {
        m_tInfo.fX -= 230 * cos(5 * PI / 180.f) * fDT;
        m_tInfo.fY += 400 * fDT;


        m_tInfo.fCX += 100 * fDT;
        m_tInfo.fCY += 100 * fDT;
    }
       
  else if (m_iCount == 1)
  {
      m_tInfo.fX = middleX;
      m_tInfo.fY += 400 * fDT;


      m_tInfo.fCX += 100 * fDT;
      m_tInfo.fCY += 100 * fDT;
  }
      
  else if (m_iCount == 2)
  {
      m_tInfo.fX += 230 * cos(5 * PI / 180.f) * fDT;
      m_tInfo.fY += 400 * fDT;


      m_tInfo.fCX += 100 * fDT;
      m_tInfo.fCY += 100 * fDT;
  }
       

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CBoom::Late_Update()
{
    if (m_tInfo.fY > WINCY)
        Set_Dead();



    GetAnimator()->Update();
}

void CBoom::Render(HDC hDC)
{
    GetAnimator()->GetCurAnimation()->Render(hDC);

}

void CBoom::Release()
{
}
