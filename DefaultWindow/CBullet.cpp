#include "stdafx.h"
#include "CBullet.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CTimeMgr.h"

#include "CPlayerSkill.h"

#include "CWill_Page1.h"

CBullet::CBullet()
{
	CreateAnimator();
}

CBullet::~CBullet()
{
}

void CBullet::Initialize(Vec2 _v, MONSTER_DIR _e)
{
	m_tInfo = { _v.x ,_v.y ,50.f,50.f };
	m_eObjType = OBJID::OBJ_BOSS_SKILL;
	m_eDir = _e;
	m_fSpeed = 100.f;

	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Bullet", L"../API/Boss/Bullet.png");
	GetAnimator()->CreateAnimation(L"Bullet", pTex, Vec2(0.f, 0.f), Vec2(57.f, 57.f), Vec2(57.f, 0.f), 0.06, 8);

	GetAnimator()->Play(L"Bullet", true);
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	switch (m_eDir)
	{
	case MONSTER_DIR::LEFT:
		m_tInfo.fX -= 400 * fDT;
		m_tInfo.fY += 400 * fDT;
		break;
	case MONSTER_DIR::RIGHT:
		m_tInfo.fX += 400 * fDT;
		m_tInfo.fY += 400 * fDT;
		break;
	case MONSTER_DIR::END:
		break;
	default:
		break;
	}






	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (m_tInfo.fX <= 0
		|| m_tInfo.fX >= WINCX)
	{
		// 삭제
		Set_Dead();     // 보스죽으면 CObj에서 관리하는 스레기들 삭제해줄예정		
	}


	GetAnimator()->Update();
}

void CBullet::Render(HDC hDC)
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

void CBullet::Release()
{
}
