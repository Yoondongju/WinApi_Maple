#include "stdafx.h"
#include "CMonster.h"

#include "ObjMgr.h"
#include "CResMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CTimeMgr.h"


CMonster::CMonster()
	: m_bLineCol(false)
	, m_fLadningTime(0.f)
	, m_bArrival(false)
	, m_fTargetX(0.f)
	, m_pPreLine(nullptr)
	, m_fMoveDelay(1.f)
	, m_fZenDelay(2.f)
	, m_fMaxHp(100.f)
	, m_fHp(m_fMaxHp)
	, m_fAttackInfo(10.f)
	, m_bDeadAniPlay(false)
	, m_pCollisonObj(nullptr)
	, m_iDamageCount(0)
	, m_fDamageCreateDelay(0.08f)
	, m_bHit(false)
	, m_bAttacking(false)

{
    
}




CMonster::~CMonster()
{
}

void CMonster::Initialize()
{


}

int CMonster::Update()
{
	return 0;
}

void CMonster::Late_Update()
{
	
}

void CMonster::Render(HDC hDC)
{
   
}

void CMonster::Release()
{
}
