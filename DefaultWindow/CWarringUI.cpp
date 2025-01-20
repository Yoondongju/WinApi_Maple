#include "stdafx.h"
#include "CWarringUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CMonster.h"
#include "ObjMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"

CWarringUI::CWarringUI()
	: m_byte(255)
{
	CreateAnimator();
	m_bAffectedCamera = false;
}

CWarringUI::~CWarringUI()
{
}

void CWarringUI::Initialize()
{

	m_tInfo = { WINCX / 2.f, 230.f, 700, 400 };
	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::UITYPE_NONE;


	// 544  224  6

	CTexture* pTex  = CResMgr::CreateSingleTonInst()->LoadTexture(L"warring", L"../API/kariain/warring.png");
	GetAnimator()->CreateAnimation(L"warring", pTex, Vec2(0.f, 0.f), Vec2(544.f, 224.f), Vec2(544.f, 0.f), 0.2, 6);
	GetAnimator()->Play(L"warring", true);

}

int CWarringUI::Update()
{
	if (CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS).size() > 0)
		return OBJ_DEAD;

	


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CWarringUI::Late_Update()
{
	GetAnimator()->Update();
}

void CWarringUI::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);

}

void CWarringUI::Release()
{
}
