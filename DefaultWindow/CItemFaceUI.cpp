#include "stdafx.h"
#include "CItemFaceUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "ObjMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CInventoryUI.h"
#include "CEquipUI.h"

#include "CQuickSlotUI.h"

#include "Player.h"
#include "CPet.h"

#include "CSound.h"

int CItemFaceUI::m_iCountStoreNum = -1;
int CItemFaceUI::m_iCountEquipNum = -1;
int CItemFaceUI::m_iCountSobiNum = -1;



CItemFaceUI::CItemFaceUI()
	: m_bEquip(false)
	, m_bClick(false)
{
	
}

CItemFaceUI::~CItemFaceUI()
{
}

void CItemFaceUI::Initialize(CTexture* _pTex, UI_TYPE _e, ITEM_TYPE _eItemType)
{
	m_tInfo = { 0.f, 0.f , 34.f , 34.f };
	

	m_eObjType = OBJID::OBJ_UI;
	m_eItemType = _eItemType;
	
	switch (_e)
	{
	case INVENTORY:
	{

		if (m_eItemType == ITEM_TYPE::PORTION
			|| m_eItemType == ITEM_TYPE::PET)
		{
			++m_iCountSobiNum;
			m_iSobiNum = m_iCountSobiNum;
		}
		else
		{
			++m_iCountEquipNum;
			m_iEquipNum = m_iCountEquipNum;
		}


	}
		break;

	case STORE:
		++m_iCountStoreNum;
		m_iStoreNum = m_iCountStoreNum;
		break;
	}


	m_eUItype = _e;				// 내 부모 유아이 타입임
	m_pUITex = _pTex;


}

int CItemFaceUI::Update()
{
	this;
	if (m_bActivate)
	{
		m_bMovement = true;

		if (m_bDead)
			return OBJ_DEAD;

		
		if (m_eUItype == UI_TYPE::STORE)
		{
			m_bMovement = false;

			RECT rt = m_pParentUI->Get_Rect();

			m_tRect =
			{
				rt.left + 285,
				rt.top + 125 + (42 * m_iStoreNum),
				rt.left + 319,
				rt.top + 158 + (42 * m_iStoreNum)
			};
		}

		else if (m_eUItype == UI_TYPE::INVENTORY)			// 다르게 처리 해줘야함 !  !  !
		{
			RECT rt = m_pParentUI->Get_Rect();

			this;
			if (m_bEquip || m_bClick)   //g_Check 가 개별적으로 들어가야함
				__super::Update_Rect();
			else
			{
				if ('E' == static_cast<CInventoryUI*>(m_pParentUI)->GetInvenCheck())
				{
					if (m_iEquipNum > 3)
					{
						int i = 4;		// 가로 최대 갯수에 도달했을 시점
						m_tRect =
						{
							rt.left + 14 + (42 * (m_iEquipNum - i)),
							rt.top + 94,
							rt.left + 14 + (42 * (m_iEquipNum - i) + 34),
							rt.top + 127
						};
					}
					else
					{
						m_tRect =
						{
							// 시작 위치   10, 51, 83       x차이 31  y차이 32   여분 픽셀 3픽셀 차이  
							rt.left + 14 + (42 * m_iEquipNum),
							rt.top + 52 ,
							rt.left + 14 + (42 * m_iEquipNum) + 34,
							rt.top + 85
						};
					}
				}
				else    // 소비창 
				{
					m_tRect =
					{
						rt.left + 14 + (42 * m_iSobiNum),
						rt.top + 52 ,
						rt.left + 14 + (42 * m_iSobiNum) + 34,
						rt.top + 85
					};
				}
			}
		}

		else if (m_eUItype == UI_TYPE::EQUIPMENT)
		{
			if (!m_bClick)
			{
				Vec2 vPos = m_pParentUI->GetPos();
				Vec2 vOffset = static_cast<CEquipUI*>(m_pParentUI)->GetItemOffset(m_eItemType);
				Set_Pos(vPos.x + vOffset.x, vPos.y + vOffset.y);
			}
			
			__super::Update_Rect();
		}

		else if (m_eUItype == UI_TYPE::QUICK_SLOT)
		{
			if (!m_bClick)
			{
				Vec2 vPos = m_pParentUI->GetPos();
				Vec2 vOffset = static_cast<CQuickSlotUI*>(m_pParentUI)->GetPortionOffset();
				Set_Pos(vPos.x + vOffset.x, vPos.y + vOffset.y);
			}
		
			__super::Update_Rect();
		}
			

		
		

		return OBJ_NOEVENT;
	}
	
}

void CItemFaceUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();			// 여기서 문제생김 
		MouseOn();
	}
}



// 20 / 34	( 사진픽셀 / 내 크기 ) 비율   ( 마깃안 때문.. )
// 내크기 * 비율

void CItemFaceUI::Render(HDC hDC)
{
	if (m_bActivate)
	{
		float fY = m_pUITex->Height() / m_tInfo.fCY;

		AlphaBlend(hDC
			, m_tRect.left		            // ( 고정위치 )						// 이미지를 출력할 x
			, m_tRect.top		            // ( 고정위치 )						// 이미지를 출력할 y
			, m_tInfo.fCX							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
			, m_tInfo.fCY * fY
			, m_pUITex->GetDC()
			, 0								// 가져올 이미지의 시작위치
			, 0
			, m_pUITex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
			, m_pUITex->Height()
			, this->GetBf());
	}
}

void CItemFaceUI::Release()
{
}

void CItemFaceUI::MouseLBtnDown()
{
	if (m_bActivate)
	{
		CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"Item_Click");
		pNewSound1->Play(false);
		pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
		pNewSound1->SetVolume(100.f); // 소리 볼륨 크기



		if (m_bMovement)
		{
			m_tInfo.fX = CKeyMgr::CreateSingleTonInst()->GetMousePos().x;
			m_tInfo.fY = CKeyMgr::CreateSingleTonInst()->GetMousePos().y;

			m_bClick = true;
			m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
		}
		

		
	}
}

void CItemFaceUI::MouseLBtnUp()
{
	if (m_bMovement)			// 장비, 인벤토리에 해당하는 아이콘이라는 말
	{
		CEquipUI* pEquipUI = m_pPlayer->GetPlayerEquipUI();
		CQuickSlotUI* pQuickslotUI = m_pPlayer->GetPlayerQuickSlotUI();

		Vec2 vTargetPos = pEquipUI->GetItemTargetPos(m_eItemType);
		Vec2 vPortionTargetPos = pQuickslotUI->GetPortionTargetPos();


		if (abs(vTargetPos.x - GetPos().x) < 10
			&& abs(vTargetPos.y - GetPos().y) < 10)
		{
		
			list<CPlayerUI*>& childList = m_pParentUI->GetChildUI();
			for (auto iter = childList.begin(); iter != childList.end();)
			{
				if (true == static_cast<CItemFaceUI*>((*iter))->m_bClick)
				{
					m_bClick = false;

					m_bEquip = true;
					iter = childList.erase(iter);
					m_eUItype = UI_TYPE::EQUIPMENT;
					SetParentUI(pEquipUI);
					pEquipUI->GetChildUI().push_back(this);
					Set_Pos(vTargetPos.x, vTargetPos.y);  // 오프셋 위치 수정해야함
				}				
				else
					++iter;
			}
		}

		else if (abs(vPortionTargetPos.x - GetPos().x) < 10
			&& abs(vPortionTargetPos.y - GetPos().y) < 10)
		{

			list<CPlayerUI*>& childList = m_pParentUI->GetChildUI();
			for (auto iter = childList.begin(); iter != childList.end();)
			{
				if (true == static_cast<CItemFaceUI*>((*iter))->m_bClick)
				{
					m_bClick = false;

					m_bEquip = true;
					iter = childList.erase(iter);
					m_eUItype = UI_TYPE::QUICK_SLOT;
					SetParentUI(pQuickslotUI);
					pQuickslotUI->GetChildUI().push_back(this);
					Set_Pos(vPortionTargetPos.x, vPortionTargetPos.y);  // 오프셋 위치 수정해야함
				}
					
				else
					++iter;
			}		
		}

		else
		{
			if (m_eUItype == UI_TYPE::INVENTORY)
			{
				list<CPlayerUI*> childList = m_pParentUI->GetChildUI();
				for (auto iter = childList.begin(); iter != childList.end(); ++iter)
				{
					if (m_eUItype == (*iter)->GetUI_Type())		// 같은 인벤토리의 그룹내의 UI들만 체크
					{
						CItemFaceUI* pTargetUI = (CItemFaceUI*)(*iter);
						
						Vec2 vTargetPos = pTargetUI->GetPos();
						Vec2 vMyPos = GetPos();

						float fX = abs(vTargetPos.x - vMyPos.x);
						float fY = abs(vTargetPos.y - vMyPos.y);

						if (fX < 5 && fY < 5)
						{							
							int iTemp = pTargetUI->GetEquipNum();            //m_iEquipNum 를 바꿔줌
							((CItemFaceUI*)(*iter))->SetEquipNum(this->m_iEquipNum);
							this->SetEquipNum(iTemp);							
						}	
						m_bClick = false;
					}
				}
			}


			if (nullptr != dynamic_cast<CEquipUI*>(m_pParentUI))  // 장비창이면 들어옴
			{
				list<CPlayerUI*>& childList = m_pParentUI->GetChildUI();
				for (auto iter = childList.begin(); iter != childList.end();)
				{
					if (true == static_cast<CItemFaceUI*>((*iter))->m_bClick)
					{
						m_bClick = false;

						iter = childList.erase(iter);
						m_eUItype = UI_TYPE::INVENTORY;
						m_bEquip = false;
						SetParentUI(m_pPlayer->GetPlayerInventory());
						m_pPlayer->GetPlayerInventory()->GetChildUI().push_back(this);
					}					
					else
						++iter;
				}		
			}
			else
				m_bClick = false;
		}
	}
	
}

void CItemFaceUI::MouseClick()
{
	CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"Item_Drop");
	pNewSound1->Play(false);
	pNewSound1->SetPosition(1.f); // 백분률 , 소리위치
	pNewSound1->SetVolume(100.f); // 소리 볼륨 크기

	// 클릭했을때 상호작용이 다 달라야함 	
	// 펫만 여기서 처리	
	if (ITEM_TYPE::PET == m_eItemType)
	{
		this->Set_Dead();

		list<CPlayerUI*>& childList = m_pParentUI->GetChildUI();
		for (auto iter = childList.begin(); iter != childList.end();)
		{
			if (ITEM_TYPE::PET == static_cast<CItemFaceUI*>((*iter))->m_eItemType)
			{
				iter = childList.erase(iter);
			}
			else
				++iter;
		}

		CObj* pPet = new CPet;
		pPet->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_PET, pPet);
		m_pPlayer->SetMyPet(pPet);
	}
}


 
void CItemFaceUI::MouseOn()
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

void CItemFaceUI::MouseOut()
{
}