#include "stdafx.h"
#include "CWeb.h"


#include "ObjMgr.h"
#include "CResMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CTimeMgr.h"

#include "CPlayerSkill.h"

#include <random>

CWeb::CWeb()
{
	CreateAnimator();
}

CWeb::~CWeb()
{
}

void CWeb::Initialize()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> distX(0, WINCX);
	float randNumX = distX(mt);
	std::uniform_int_distribution<int> distY(0, WINCY);
	float randNumY = distY(mt);


	m_tInfo = { randNumX, randNumY ,200.f,200.f };
	m_eObjType = OBJID::OBJ_BOSS_SKILL;
	m_fSpeed = 100.f;

	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"web", L"../API/Boss/page3/web.png");
	GetAnimator()->CreateAnimation(L"web", pTex, Vec2(0.f, 0.f), Vec2(368.f, 372.f), Vec2(0.f, 372.f), 0.06, 14);

	GetAnimator()->Play(L"web", true);
}

int CWeb::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	//switch (m_eDir)
	//{
	//case MONSTER_DIR::LEFT:
	//	m_tInfo.fX -= 400 * fDT;
	//	m_tInfo.fY += 400 * fDT;
	//	break;
	//case MONSTER_DIR::RIGHT:
	//	m_tInfo.fX += 400 * fDT;
	//	m_tInfo.fY += 400 * fDT;
	//	break;
	//case MONSTER_DIR::END:
	//	break;
	//default:
	//	break;
	//}






	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CWeb::Late_Update()
{
	if (m_tInfo.fX <= 0				// 조건 다르게 해야하고 
		|| m_tInfo.fX >= WINCX)		// 조건 다르게 해야하고 
	{
		// 삭제
		Set_Dead();     // 보스죽으면 CObj에서 관리하는 스레기들 삭제해줄예정		
	}


	GetAnimator()->Update();
}

void CWeb::Render(HDC hDC)
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

void CWeb::Release()
{
}