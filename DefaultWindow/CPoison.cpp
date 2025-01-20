#include "stdafx.h"
#include "CPoison.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CTimeMgr.h"
#include <ctime>

#include "CPlayerSkill.h"

#include "CWIll_Page3.h"

CPoison::CPoison()
{
	srand(time(nullptr));
    CreateAnimator();
}

CPoison::~CPoison()
{
}

void CPoison::Initialize(Vec2 _v)
{
	m_tInfo = { _v.x ,_v.y ,250.f,250.f };
	m_eObjType = OBJID::OBJ_BOSS_SKILL;
	m_fSpeed = 100.f;
	m_fAngle = rand() % 361;
	m_fSurvivalTime = 4.f;

	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"poison", L"../API/Boss/page3/Poison.png");
	GetAnimator()->CreateAnimation(L"poison", pTex, Vec2(0.f, 0.f), Vec2(274.f, 252.f), Vec2(0.f, 252.f), 0.06, 16);

	GetAnimator()->Play(L"poison", true);
}

int CPoison::Update()
{
	m_fSurvivalTime -= fDT;

	if (m_bDead)
		return OBJ_DEAD;


	if ((m_tInfo.fX + m_tInfo.fCX / 2.f) > WINCX
		|| (m_tInfo.fX - m_tInfo.fCX / 2.f) < 0  
		|| (m_tInfo.fY - m_tInfo.fCY / 2.f) < 0  
		|| (m_tInfo.fY + m_tInfo.fCY / 2.f) > WINCY)  // 클라이언트에 충돌했을 시점  
	{
		// 방향을 랜덤하게 줘야하고 
		m_fAngle = rand() % 361;   // 0 ~ 360도 
	}


	m_tInfo.fX += 500 * cos(m_fAngle * PI / 180.f) * fDT;
	m_tInfo.fY -= 500 * sin(m_fAngle * PI / 180.f) * fDT;





	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPoison::Late_Update()
{
	if (m_fSurvivalTime <= 0.f)		
	{
		Set_Dead();   
		((CWIll_Page3*)CObjMgr::Get_Instance()->Get_Will())->SetPoison(nullptr);
	}


	GetAnimator()->Update();
}

void CPoison::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);



	//SelectGDI p1(hDC, PEN_TYPE::RED);
	//SelectGDI b1(hDC, BRUSH_TYPE::HOLLOW);
	//
	//
	//Vec2 vPos1 = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
	//
	//Rectangle(hDC
	//	, (int)(vPos1.x - m_tInfo.fCX * 0.5f)
	//	, (int)(vPos1.y - m_tInfo.fCY * 0.5f)
	//	, (int)(vPos1.x + m_tInfo.fCX * 0.5f)
	//	, (int)(vPos1.y + m_tInfo.fCY * 0.5f));
}

void CPoison::Release()
{
}
