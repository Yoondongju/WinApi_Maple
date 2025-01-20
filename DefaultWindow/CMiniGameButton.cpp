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
		, m_tRect.left		            // ( ������ġ )						// �̹����� ����� x
		, m_tRect.top		            // ( ������ġ )						// �̹����� ����� y
		, m_tInfo.fCX							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, m_tInfo.fCY
		, m_pRenderTex->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pRenderTex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
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
	// ���ӽ���
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
