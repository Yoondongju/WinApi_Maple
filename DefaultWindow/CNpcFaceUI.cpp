#include "stdafx.h"
#include "CNpcFaceUI.h"


#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "ObjMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"

CNpcFaceUI::CNpcFaceUI()
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

CNpcFaceUI::~CNpcFaceUI()
{
}

void CNpcFaceUI::Initialize()
{
	m_tInfo = { 0.f, 0.f , 100.f , 100.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::STORE;


	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"store_npc_stand_right", L"../API/UI/storeNpc_right.png");
	GetAnimator()->CreateAnimation(L"store_npc_stand_right", pTex, Vec2(0.f, 0.f), Vec2(84.f, 113.f), Vec2(84.f, 0.f), 0.3f, 4);
	GetAnimator()->Play(L"store_npc_stand_right",true);
}

int CNpcFaceUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	Vec2 vPos = m_pParentUI->GetPos();
	Set_Pos(vPos.x -190, vPos.y - 210.f);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CNpcFaceUI::Late_Update()
{
	GetAnimator()->Update();
}

void CNpcFaceUI::Render(HDC hDC)
{
	GetAnimator()->GetCurAnimation()->Render(hDC);
}

void CNpcFaceUI::Release()
{
}

void CNpcFaceUI::MouseLBtnDown()
{
}

void CNpcFaceUI::MouseLBtnUp()
{
}

void CNpcFaceUI::MouseClick()
{
}

void CNpcFaceUI::MouseOn()
{
}

void CNpcFaceUI::MouseOut()
{
}
