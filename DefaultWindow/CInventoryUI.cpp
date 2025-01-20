#include "stdafx.h"
#include "CInventoryUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"

#include "CItemFaceUI.h"


CInventoryUI::CInventoryUI()
	: m_vDragStart(Vec2(0.f, 0.f))
	, m_pPortion(nullptr)
	, m_pRenderTex(nullptr)
{
	m_bMovement = true;
	m_bActivate = false;


	BLENDFUNCTION bf = GetBf();
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	SetBf(bf);
}


CInventoryUI::~CInventoryUI()
{
	Release();
}


void CInventoryUI::Initialize()
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player가 ObjMgr에 등록되기 전에 이걸 불러서 문제가생김

	m_tInfo = { WINCX / 2.f + WINCX / 3.f, WINCY / 2.f, 200.f , 350.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::INVENTORY;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_inven_Equip_UI", L"../API/UI/Inventory_Equip.png");		// 장비로 쓸거
	m_pPortion = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_inven_Portion_UI", L"../API/UI/Inventory_Portion.png");	// 소비로 쓸거

	m_cCheck = 'E';
	m_pRenderTex = m_pUITex;
}

int CInventoryUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bActivate)
	{
		m_bMovement = true;

		__super::Update_Rect();

		for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
			iter->Update();
	}


	return OBJ_NOEVENT;
}

void CInventoryUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();
		MouseOn();


		for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
			iter->Late_Update();
	}
}

void CInventoryUI::Render(HDC hDC)
{
	if (m_bActivate)
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



		RECT rt = {
			  m_tRect.left + 90.f
			, m_tRect.top + 280.f
			, m_tRect.right
			, m_tRect.bottom
		};


		DrawTextW(hDC
			, to_wstring(m_pPlayer->GetMeso()).c_str()		// 변수가 들어가야함
			, -1
			, &rt
			, DT_LEFT | DT_WORDBREAK);


		for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
			iter->Render(hDC);
	}


}

void CInventoryUI::Release()
{
	for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
		Safe_Delete<CPlayerUI*>(iter);


	m_childUI_List.clear();
}


void CInventoryUI::MouseLBtnDown()
{
	m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
}


void CInventoryUI::MouseLBtnUp()
{
}


void CInventoryUI::MouseClick()
{
	Vec2 vMousePos = CKeyMgr::CreateSingleTonInst()->GetMousePos();

	if (vMousePos.x > m_tRect.left + 40
		&& vMousePos.x < m_tRect.left + 70
		&& vMousePos.y > m_tRect.top + 25
		&& vMousePos.y < m_tRect.top + 45)
	{
		m_cCheck = 'S';
		m_pRenderTex = m_pPortion;

		for(auto& iter : m_childUI_List)
		{ 
			ITEM_TYPE _eType = static_cast<CItemFaceUI*>(iter)->GetItemType();

			if (ITEM_TYPE::PET != _eType && ITEM_TYPE::PORTION != _eType)
			{
				iter->SetActivate(false);
			}
			else
				iter->SetActivate(true);
		}
		
	}
	else if (vMousePos.x > m_tRect.left 
		&& vMousePos.x < m_tRect.left + 40
		&& vMousePos.y > m_tRect.top + 25
		&& vMousePos.y < m_tRect.top + 45)
	{
		m_cCheck = 'E';
		m_pRenderTex = m_pUITex;

		for (auto& iter : m_childUI_List)
		{
			ITEM_TYPE _eType = static_cast<CItemFaceUI*>(iter)->GetItemType();

			if (ITEM_TYPE::PET != _eType && ITEM_TYPE::PORTION != _eType)
			{
				iter->SetActivate(true);
			}
			else
				iter->SetActivate(false);
		}
	}
		


}


void CInventoryUI::MouseOn()
{
	if (m_bMovement)
	{
		if (IsLbtnDown())
		{
			Vec2 vCurMousePos = CKeyMgr::CreateSingleTonInst()->GetMousePos();
			Vec2 vDiff = m_vDragStart - vCurMousePos;
			Set_Pos(m_tInfo.fX - vDiff.x, m_tInfo.fY - vDiff.y);

			m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
		}


	}
}


void CInventoryUI::MouseOut()
{

}
