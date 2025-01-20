#include "stdafx.h"
#include "CKariainSkill.h"


#include "ObjMgr.h"
#include "CResMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "Player.h"

#include "CTimeMgr.h"

#include "CPlayerSkill.h"

#include "CSound.h"

CKariainSkill::CKariainSkill()
	: m_bActive(false)
{
    CreateAnimator();
}

CKariainSkill::~CKariainSkill()
{
}



void CKariainSkill::Initialize(MONSTER_DIR _e)
{
	m_tInfo = { 0.f,0.f ,WINCX, WINCY};
	m_eObjType = OBJID::OBJ_BOSS_SKILL;
	m_fSpeed = 100.f;
	m_eDir = _e;


	// 이미지가 큰걸 로드하는부분에서 렉이 많이걸리네


	CTexture* pTex7 = CResMgr::CreateSingleTonInst()->LoadTexture(L"kariain_attack2_effect", L"../API/kariain/attack2_effect.png");
	GetAnimator()->CreateAnimation(L"kariain_attack2_effect", pTex7, Vec2(0.f, 0.f), Vec2(1184.f, 844.f), Vec2(0.f, 844.f), 0.04, 30);

	GetAnimator()->Play(L"kariain_attack2_effect", false);
}

int CKariainSkill::Update()
{
	if (m_bDead)
		return OBJ_DEAD; 


	


	if (m_bActive)
	{
		m_tInfo.fX = CObjMgr::Get_Instance()->Get_Player()->GetPos().x;
		m_tInfo.fY = CObjMgr::Get_Instance()->Get_Player()->GetPos().y;

		
		
		GetAnimator()->Play(L"kariain_attack2_effect", false);
		
			

		__super::Update_Rect();

		return OBJ_NOEVENT;
	}

	
}

void CKariainSkill::Late_Update()
{
	if (GetAnimator()->GetCurAnimation()->GetFinish())
	{
		GetAnimator()->GetCurAnimation()->SetFrame(0);

	}

	GetAnimator()->Update();
}

void CKariainSkill::Render(HDC hDC)
{
	if (m_bActive)
	{
		GetAnimator()->GetCurAnimation()->Render(hDC);
	}
}

void CKariainSkill::Release()
{
}
