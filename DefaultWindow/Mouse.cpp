#include "stdafx.h"
#include "Mouse.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CSound.h"

CMouse::CMouse()
	: m_pTexNon(nullptr)
	, m_pTexClick(nullptr)
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 37.f;
	m_tInfo.fCY = 37.f;

	m_pTexNon = CResMgr::CreateSingleTonInst()->LoadTexture(L"Mouse_Non", L"../API/UI/Mouse1.png");
	m_pTexClick = CResMgr::CreateSingleTonInst()->LoadTexture(L"Mouse_Click", L"../API/UI/Mouse2.png");
}

int CMouse::Update()
{
	m_tInfo.fX = CKeyMgr::CreateSingleTonInst()->GetMousePos().x;
	m_tInfo.fY = CKeyMgr::CreateSingleTonInst()->GetMousePos().y;

	__super::Update_Rect();

	ShowCursor(false);

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
}


void CMouse::Render(HDC hDC)
{
	CTexture* pTex = m_pTexNon;

	if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::TAP
		|| CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::HOLD)
	{
		CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"ui_click");
		pNewSound1->Play(false);
		pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
		pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��

		pTex = m_pTexClick;
	}
	else if (CKeyMgr::CreateSingleTonInst()->GetKeyState(KEY::LBUTTON) == KEY_STATE::AWAY)
	{
		pTex = m_pTexNon;
	}



	AlphaBlend(hDC
		, m_tInfo.fX		            // ( ������ġ )						// �̹����� ����� x
		, m_tInfo.fY					// ( ������ġ )						// �̹����� ����� y
		, m_tInfo.fCX					// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, m_tInfo.fCY
		, pTex->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, pTex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
		, pTex->Height()
		, this->GetBf());
}


void CMouse::Release()
{
}
