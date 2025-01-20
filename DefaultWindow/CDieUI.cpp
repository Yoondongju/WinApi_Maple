#include "stdafx.h"
#include "CDieUI.h"

#include "CResMgr.h"
#include "CTexture.h"


CDieUI::CDieUI()
{
}

CDieUI::~CDieUI()
{
}

void CDieUI::Initialize()
{
	m_tInfo = { WINCX / 2.f  , WINCY / 2.f   , 300.f ,131.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::DIE;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"DeadUI", L"../API/UI/NoticeDead.png");
}

int CDieUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CDieUI::Late_Update()
{
	MouseOnCheck();

}

void CDieUI::Render(HDC hDC)
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

void CDieUI::Release()
{
}

void CDieUI::MouseLBtnDown()
{
}

void CDieUI::MouseLBtnUp()
{
}

void CDieUI::MouseClick()
{
}

void CDieUI::MouseOn()
{
}

void CDieUI::MouseOut()
{
}
