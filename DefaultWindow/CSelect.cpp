#include "stdafx.h"
#include "CSelect.h"

#include "CTexture.h"
#include "CResMgr.h"

#include "CKeyMgr.h"

CSelect::CSelect()
{
	BLENDFUNCTION bf = GetBf();
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 70;

	SetBf(bf);
}

CSelect::~CSelect()
{
}


void CSelect::Initialize(Vec2 _vPos)
{
	m_tInfo = { 0.f,0.f, 209,40.f };
	m_vOffset = _vPos;


	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::BUTTON;

	__super::Update_Rect();

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Select", L"../API/UI/shop_select.png");
}

int CSelect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	Vec2 vPos = m_pParentUI->GetPos();
	Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);



	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CSelect::Late_Update()
{
	
}

void CSelect::Render(HDC hDC)
{
	AlphaBlend(hDC
		, m_tRect.left		            // ( 고정위치 )						// 이미지를 출력할 x
		, m_tRect.top		            // ( 고정위치 )						// 이미지를 출력할 y
		, m_tInfo.fCX							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pUITex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
		, m_pUITex->Height()
		, this->GetBf());
}

void CSelect::Release()
{
}

void CSelect::MouseLBtnDown()
{
}

void CSelect::MouseLBtnUp()
{
}

void CSelect::MouseClick()
{
}

void CSelect::MouseOn()
{
}

void CSelect::MouseOut()
{
}
