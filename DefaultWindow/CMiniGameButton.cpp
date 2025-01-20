#include "stdafx.h"
#include "CMiniGameButton.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"

#include "CSceneMgr.h"
#include "CMiniGameScene.h"

CMiniGameButton::CMiniGameButton()
	: m_pLbtnClickTex(nullptr)
	, m_pRenderTex(nullptr)
{

}

CMiniGameButton::~CMiniGameButton()
{

}

void CMiniGameButton::Initialize()
{
	m_tInfo = { WINCX/2.f, WINCY/2.f   , 155.f ,50.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::BUTTON;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"MiniBtn", L"../API/UI/MiniBtn.png");
	m_pLbtnClickTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"MiniBtnClick", L"../API/UI/MiniBtnClick.png");


	m_pRenderTex = m_pUITex;
}

int CMiniGameButton::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CMiniGameButton::Late_Update()
{
	MouseOnCheck();


}

void CMiniGameButton::Render(HDC hDC)
{

	AlphaBlend(hDC
		, m_tRect.left		            // ( 고정위치 )						// 이미지를 출력할 x
		, m_tRect.top		            // ( 고정위치 )						// 이미지를 출력할 y
		, m_tInfo.fCX							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, m_pRenderTex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pRenderTex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
		, m_pRenderTex->Height()
		, this->GetBf());

}

void CMiniGameButton::Release()
{
}

void CMiniGameButton::MouseLBtnDown()
{
}

void CMiniGameButton::MouseLBtnUp()
{
}

void CMiniGameButton::MouseClick()
{
	// 게임시작
	((CMiniGameScene*)CSceneMgr::CreateSingleTonInst()->GetCurScene())->SetGameStart(true);
	Set_Dead();
}

void CMiniGameButton::MouseOn()
{
	m_pRenderTex = m_pLbtnClickTex;
}

void CMiniGameButton::MouseOut()
{
	m_pRenderTex = m_pUITex;
}
