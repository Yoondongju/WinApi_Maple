#include "stdafx.h"
#include "CLevelUI.h"


#include "CResMgr.h"

#include "CTexture.h"

#include "Player.h"



CLevelUI::CLevelUI()
    : m_vOffset(-60.f, -25.f)
{
	CreateAnimator();
}

CLevelUI::~CLevelUI()
{
}

void CLevelUI::Initialize()
{
	Vec2 vPos = m_pParentUI->GetPos();
	m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y  , 10.f , 15.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::LEVEL;

	m_mapLevel.insert(make_pair('0', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_0", L"../API/Level/NoRed2.0.png")));
	m_mapLevel.insert(make_pair('1', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_1", L"../API/Level/NoRed2.1.png")));
	m_mapLevel.insert(make_pair('2', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_2", L"../API/Level/NoRed2.2.png")));
	m_mapLevel.insert(make_pair('3', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_3", L"../API/Level/NoRed2.3.png")));
	m_mapLevel.insert(make_pair('4', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_4", L"../API/Level/NoRed2.4.png")));
	m_mapLevel.insert(make_pair('5', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_5", L"../API/Level/NoRed2.5.png")));
	m_mapLevel.insert(make_pair('6', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_6", L"../API/Level/NoRed2.6.png")));
	m_mapLevel.insert(make_pair('7', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_7", L"../API/Level/NoRed2.7.png")));
	m_mapLevel.insert(make_pair('8', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_8", L"../API/Level/NoRed2.8.png")));
	m_mapLevel.insert(make_pair('9', CResMgr::CreateSingleTonInst()->LoadTexture(L"Level_9", L"../API/Level/NoRed2.9.png")));

}

int CLevelUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CLevelUI::Late_Update()
{
}

void CLevelUI::Render(HDC hDC)
{
	for (auto& iter : m_mapLevel)
	{
		auto tex = m_mapLevel.find(to_wstring(m_pPlayer->GetLevel())[0]);
	
		CTexture* pRenderTex = (*tex).second;

		AlphaBlend(hDC
			, m_tRect.left		// ( 고정위치 )						// 이미지를 출력할 x
			, m_tRect.top		// ( 고정위치 )						// 이미지를 출력할 y
			, m_tInfo.fCX 							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
			, m_tInfo.fCY
			, pRenderTex->GetDC()
			, 0								// 가져올 이미지의 시작위치
			, 0
			, pRenderTex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
			, pRenderTex->Height()
			, this->GetBf());
	}
}

void CLevelUI::Release()
{
}
