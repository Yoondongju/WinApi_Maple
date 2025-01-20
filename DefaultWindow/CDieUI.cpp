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
		, m_tRect.left		            // ( ������ġ )						// �̹����� ����� x
		, m_tRect.top		            // ( ������ġ )						// �̹����� ����� y
		, m_tInfo.fCX							// ����� �̹����� ���� ( �� ũ�⸸ŭ �̹����� ũ�⺯�� )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// ������ �̹����� ������ġ
		, 0
		, m_pUITex->Width() 			// �߶� ũ��ϱ� �׻� 800 �̿�����
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
