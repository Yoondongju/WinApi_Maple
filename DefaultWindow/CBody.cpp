#include "stdafx.h"
#include "CBody.h"

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

#include "CBullet.h"

CBody::CBody()
{
    CreateAnimator();
}

CBody::~CBody()
{
}

void CBody::Initialize(Vec2 _v)
{
	m_tInfo = { _v.x ,_v.y ,600.f,300.f };
	m_eObjType = OBJID::OBJ_BOSS_SKILL;

	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Body", L"../API/Boss/Body.png");
	GetAnimator()->CreateAnimation(L"Body", pTex, Vec2(0.f, 0.f), Vec2(512.f, 269.f), Vec2(512.f, 0.f), 0.1, 16);

	GetAnimator()->Play(L"Body", true);
}

int CBody::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	if (3 > CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS_SKILL).size())
	{
		CBullet* pBullet = new CBullet;
		pBullet->Initialize(this->GetPos(),MONSTER_DIR::LEFT);
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS_SKILL, pBullet);

		CBullet* pBullet1 = new CBullet;
		pBullet1->Initialize(this->GetPos(), MONSTER_DIR::RIGHT);
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_BOSS_SKILL, pBullet1);
	}
	




	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBody::Late_Update()
{
	GetAnimator()->Update();
}

void CBody::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CBody::Release()
{
}
