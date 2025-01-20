#include "stdafx.h"
#include "CPlayerFaceUI.h"


#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "ObjMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"


CPlayerFaceUI::CPlayerFaceUI()
{
	BLENDFUNCTION bf = GetBf();
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	SetBf(bf);

	CreateAnimator();

	m_bAffectedCamera = false;
}

CPlayerFaceUI::~CPlayerFaceUI()
{
}

void CPlayerFaceUI::Initialize()
{
	m_tInfo = { 0.f, 0.f , 100.f , 100.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::STORE;


	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_stand_left", L"../API/Player/stand/player_stand_left.png");
	GetAnimator()->CreateAnimation(L"player_stand_left", pTex, Vec2(0.f, 0.f), Vec2(92.f, 96.f), Vec2(92.f, 0.f), 0.5f, 3);
	GetAnimator()->Play(L"player_stand_left",true);
}

int CPlayerFaceUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	Vec2 vPos = m_pParentUI->GetPos();
	Set_Pos(vPos.x + 85, vPos.y - 200.f);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayerFaceUI::Late_Update()
{
	GetAnimator()->Update();
}

void CPlayerFaceUI::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CPlayerFaceUI::Release()
{
}

void CPlayerFaceUI::MouseLBtnDown()
{
}

void CPlayerFaceUI::MouseLBtnUp()
{
}

void CPlayerFaceUI::MouseClick()
{
}

void CPlayerFaceUI::MouseOn()
{
}

void CPlayerFaceUI::MouseOut()
{
}
