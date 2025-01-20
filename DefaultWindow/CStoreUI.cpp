#include "stdafx.h"
#include "CStoreUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"
#include "CUIMgr.h"

#include "CNpcFaceUI.h"
#include "CPlayerFaceUI.h"
#include "CItemFaceUI.h"
#include "CNoGoldUI.h"

#include "CItem.h"

#include "CInventoryUI.h"

#include "CSelect.h"

#include "CSound.h"


CStoreUI::CStoreUI()
	: m_vDragStart(Vec2(0.f, 0.f))
	, m_pSelectUI(nullptr)
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

CStoreUI::~CStoreUI()
{
	m_pSelectUI = nullptr;
}

void CStoreUI::Initialize()
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player�� ObjMgr�� ��ϵǱ� ���� �̰� �ҷ��� ����������
	



	m_tInfo = { WINCX / 2.f , WINCY / 2.f, 508.f , 505.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::STORE;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"shopUI", L"../API/UI/shopitem_test.png");		// ���� ����


	CNpcFaceUI* pUI = new CNpcFaceUI;
	pUI->SetParentUI(this);
	pUI->Initialize();
	m_childUI_List.push_back(pUI);


	CPlayerFaceUI* pUI1 = new CPlayerFaceUI;
	pUI1->SetParentUI(this);
	pUI1->Initialize();
	m_childUI_List.push_back(pUI1);

	
}

int CStoreUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bActivate)
	{
		m_bMovement = true;

		__super::Update_Rect();

		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Update();
	}


	return OBJ_NOEVENT;
}

void CStoreUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();
		MouseOn();


		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Late_Update();
	}
}

void CStoreUI::Render(HDC hDC)
{
	if (m_bActivate)
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


		RECT rt = {
			  m_tRect.left + 460.f							
			, m_tRect.top + 55.f
			, m_tRect.right
			, m_tRect.bottom
			};


		
		DrawTextW(hDC
			, to_wstring(m_pPlayer->GetMeso()).c_str()		// ������ ������
			, -1
			, &rt
			, DT_LEFT | DT_WORDBREAK);




		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Render(hDC);
	}


}

void CStoreUI::Release()
{
}


void CStoreUI::MouseLBtnDown()
{
	m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
}


void CStoreUI::MouseLBtnUp()
{
}


void CStoreUI::MouseClick()
{

	// init�� �Ʒ� ������ ������ ���� ������ �ٸ����ٰ���
	
	Vec2 vMousePos = CKeyMgr::CreateSingleTonInst()->GetMousePos();

	for (UINT i = 0; i < (UINT)ITEM_TYPE::ITEM_END; ++i)
	{
		if (vMousePos.x > m_tRect.left + 10
			&& vMousePos.x < m_tRect.left + 44
			&& vMousePos.y > m_tRect.top + 124 + (i * 42)
			&& vMousePos.y < m_tRect.top + 124 + (i * 42) + 34)
		{	
			
			if (!m_pSelectUI)
			{
				CSelect* pSelectUI = new CSelect;
				pSelectUI->SetParentUI(this);
				m_pSelectUI = pSelectUI;
				m_childUI_List.push_back(pSelectUI);
			}


			int iPlayerMeso = m_pPlayer->GetMeso();

			switch ((ITEM_TYPE)i)
			{
			case ITEM_TYPE::RING:
			{			
				m_pSelectUI->Initialize(Vec2(-102.f, -115.f));
				if (iPlayerMeso < 10000)
				{
					CNoGoldUI* pUI = new CNoGoldUI;
					pUI->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
				}
				else
				{
					// ������ ����
					// ���� ���� ������ Ÿ�Կ� �°� �� �������� �κ��丮�� ��ġ�ؾ���

					if (nullptr == m_pPlayer->GetItemType(ITEM_TYPE::RING))
					{
						m_pPlayer->SetMeso(iPlayerMeso -= 10000);

						CItem* pItem = new CItem;
						CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"ring", L"../API/UI/Item/Item_1000.png");
						pItem->Initialize(ITEM_TYPE::RING, 10000, pTex);
						CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_ITEM, pItem);
						m_pPlayer->SetItemType(pItem, ITEM_TYPE::RING);


						CItemFaceUI* pUI = new CItemFaceUI;
						pUI->SetParentUI(this);
						pUI->Initialize(pTex, UI_TYPE::STORE ,ITEM_TYPE::RING);
						m_childUI_List.push_back(pUI);



						
						
						CInventoryUI* pInventory = m_pPlayer->GetPlayerInventory();
						CItemFaceUI* pUI1 = new CItemFaceUI;
						pUI1->SetParentUI(pInventory);
						pUI1->Initialize(pTex, UI_TYPE::INVENTORY, ITEM_TYPE::RING);
						pInventory->GetChildUI().push_back(pUI1);


						// �κ��丮���� ������ ������������ ���� �� �������
						// ���ÿ� �������� ������� �Һ������� ������ �����ؾ���


						


						CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"nomeso");
						pNewSound1->Play(false);
						pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
						pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��


					}
					
				}
			}
				break;
			case ITEM_TYPE::BELT:
			{
				m_pSelectUI->Initialize(Vec2(-102.f, -73.f)); 
				if (iPlayerMeso < 10000)
				{
					CNoGoldUI* pUI = new CNoGoldUI;
					pUI->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
				}
				else
				{
					// ������ ����
					// ���� ���� ������ Ÿ�Կ� �°� �� �������� �κ��丮�� ��ġ�ؾ���

					
					if (nullptr == m_pPlayer->GetItemType(ITEM_TYPE::BELT))
					{
						m_pPlayer->SetMeso(iPlayerMeso -= 10000);

						CItem* pItem = new CItem;
						CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"belt", L"../API/UI/Item/Item_1001.png");
						pItem->Initialize(ITEM_TYPE::BELT, 10000, pTex);
						CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_ITEM, pItem);
						m_pPlayer->SetItemType(pItem, ITEM_TYPE::BELT);


						CItemFaceUI* pUI = new CItemFaceUI;
						pUI->SetParentUI(this);
						pUI->Initialize(pTex, UI_TYPE::STORE, ITEM_TYPE::BELT);
						m_childUI_List.push_back(pUI);





						CInventoryUI* pInventory = m_pPlayer->GetPlayerInventory();
						CItemFaceUI* pUI1 = new CItemFaceUI;
						pUI1->SetParentUI(pInventory);
						pUI1->Initialize(pTex, UI_TYPE::INVENTORY, ITEM_TYPE::BELT);
						pInventory->GetChildUI().push_back(pUI1);


					


						CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"nomeso");
						pNewSound1->Play(false);
						pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
						pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��
					}

					
				}
			}	
				break;
			case ITEM_TYPE::EYE_PATCH:
			{
				m_pSelectUI->Initialize(Vec2(-102.f, -31.f));
				if (iPlayerMeso < 10000)
				{
					CNoGoldUI* pUI = new CNoGoldUI;
					pUI->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
				}
				else
				{
					// ������ ����
					// ���� ���� ������ Ÿ�Կ� �°� �� �������� �κ��丮�� ��ġ�ؾ���



					if (nullptr == m_pPlayer->GetItemType(ITEM_TYPE::EYE_PATCH))
					{
						m_pPlayer->SetMeso(iPlayerMeso -= 10000);


						CItem* pItem = new CItem;
						CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"eye_patch", L"../API/UI/Item/Item_1002.png");
						pItem->Initialize(ITEM_TYPE::EYE_PATCH, 10000, pTex);
						CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_ITEM, pItem);
						m_pPlayer->SetItemType(pItem, ITEM_TYPE::EYE_PATCH);


						CItemFaceUI* pUI = new CItemFaceUI;
						pUI->SetParentUI(this);
						pUI->Initialize(pTex, UI_TYPE::STORE, ITEM_TYPE::EYE_PATCH);
						m_childUI_List.push_back(pUI);





						CInventoryUI* pInventory = m_pPlayer->GetPlayerInventory();
						CItemFaceUI* pUI1 = new CItemFaceUI;
						pUI1->SetParentUI(pInventory);
						pUI1->Initialize(pTex, UI_TYPE::INVENTORY, ITEM_TYPE::EYE_PATCH);
						pInventory->GetChildUI().push_back(pUI1);



					

						CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"nomeso");
						pNewSound1->Play(false);
						pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
						pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��

					}

					
				}
			}
				break;
			case ITEM_TYPE::NECKLACE:
			{
				m_pSelectUI->Initialize(Vec2(-102.f, 11.f));
				if (iPlayerMeso < 10000)
				{
					CNoGoldUI* pUI = new CNoGoldUI;
					pUI->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
				}
				else
				{
					// ������ ����
					// ���� ���� ������ Ÿ�Կ� �°� �� �������� �κ��丮�� ��ġ�ؾ���

				

					if (nullptr == m_pPlayer->GetItemType(ITEM_TYPE::NECKLACE))
					{
						m_pPlayer->SetMeso(iPlayerMeso -= 10000);


						CItem* pItem = new CItem;
						CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"necklace", L"../API/UI/Item/Item_1003.png");
						pItem->Initialize(ITEM_TYPE::NECKLACE, 10000, pTex);
						CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_ITEM, pItem);
						m_pPlayer->SetItemType(pItem, ITEM_TYPE::NECKLACE);


						CItemFaceUI* pUI = new CItemFaceUI;
						pUI->SetParentUI(this);
						pUI->Initialize(pTex, UI_TYPE::STORE, ITEM_TYPE::NECKLACE);
						m_childUI_List.push_back(pUI);





						CInventoryUI* pInventory = m_pPlayer->GetPlayerInventory();
						CItemFaceUI* pUI1 = new CItemFaceUI;
						pUI1->SetParentUI(pInventory);
						pUI1->Initialize(pTex, UI_TYPE::INVENTORY, ITEM_TYPE::NECKLACE);
						pInventory->GetChildUI().push_back(pUI1);





						CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"nomeso");
						pNewSound1->Play(false);
						pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
						pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��

					}


					
				}
			}
				break;
			case ITEM_TYPE::EARRING:
			{	
				m_pSelectUI->Initialize(Vec2(-102.f, 53.f));
				if (iPlayerMeso < 10000)
				{
					CNoGoldUI* pUI = new CNoGoldUI;
					pUI->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
				}
				else
				{
					// ������ ����
					// ���� ���� ������ Ÿ�Կ� �°� �� �������� �κ��丮�� ��ġ�ؾ���


					
					if (nullptr == m_pPlayer->GetItemType(ITEM_TYPE::EARRING))
					{
						m_pPlayer->SetMeso(iPlayerMeso -= 10000);


						CItem* pItem = new CItem;
						CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"earring", L"../API/UI/Item/Item_1004.png");
						pItem->Initialize(ITEM_TYPE::EARRING, 10000, pTex);
						CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_ITEM, pItem);
						m_pPlayer->SetItemType(pItem, ITEM_TYPE::EARRING);


						CItemFaceUI* pUI = new CItemFaceUI;
						pUI->SetParentUI(this);
						pUI->Initialize(pTex, UI_TYPE::STORE, ITEM_TYPE::EARRING);
						m_childUI_List.push_back(pUI);





						CInventoryUI* pInventory = m_pPlayer->GetPlayerInventory();
						CItemFaceUI* pUI1 = new CItemFaceUI;
						pUI1->SetParentUI(pInventory);
						pUI1->Initialize(pTex, UI_TYPE::INVENTORY, ITEM_TYPE::EARRING);
						pInventory->GetChildUI().push_back(pUI1);



						

						CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"nomeso");
						pNewSound1->Play(false);
						pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
						pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��
					}

				
				}
			}
				break;
			case ITEM_TYPE::PORTION:
			{
				m_pSelectUI->Initialize(Vec2(-102.f, 95.f));
				if (iPlayerMeso < 100)
				{
					CNoGoldUI* pUI = new CNoGoldUI;
					pUI->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
				}
				else
				{
					// ������ ����
					// ���� ���� ������ Ÿ�Կ� �°� �� �������� �κ��丮�� ��ġ�ؾ���


				
					if (nullptr == m_pPlayer->GetItemType(ITEM_TYPE::PORTION))
					{
						m_pPlayer->SetMeso(iPlayerMeso -= 100);

						CItem* pItem = new CItem;
						CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"portion", L"../API/UI/Item/Item_1005.png");
						pItem->Initialize(ITEM_TYPE::PORTION, 100, pTex);
						CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_ITEM, pItem);
						m_pPlayer->SetItemType(pItem, ITEM_TYPE::PORTION);


						CItemFaceUI* pUI = new CItemFaceUI;
						pUI->SetParentUI(this);
						pUI->Initialize(pTex, UI_TYPE::STORE, ITEM_TYPE::PORTION);
						m_childUI_List.push_back(pUI);





						CInventoryUI* pInventory = m_pPlayer->GetPlayerInventory();
						CItemFaceUI* pUI1 = new CItemFaceUI;
						pUI1->SetParentUI(pInventory);
						pUI1->Initialize(pTex, UI_TYPE::INVENTORY, ITEM_TYPE::PORTION);
						pInventory->GetChildUI().push_back(pUI1);




						


						CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"nomeso");
						pNewSound1->Play(false);
						pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
						pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��

					}

					
				}
			}
				break;
			case ITEM_TYPE::PET:
			{
				m_pSelectUI->Initialize(Vec2(-102.f, 137.f));
				if (iPlayerMeso < 10000)
				{
					CNoGoldUI* pUI = new CNoGoldUI;
					pUI->Initialize();
					CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_UI, pUI);
				}
				else
				{
					// ������ ����
					// ���� ���� ������ Ÿ�Կ� �°� �� �������� �κ��丮�� ��ġ�ؾ���


					
					if (nullptr == m_pPlayer->GetItemType(ITEM_TYPE::PET))
					{
						m_pPlayer->SetMeso(iPlayerMeso -= 10000);

						CItem* pItem = new CItem;
						CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"pet", L"../API/UI/Item/Item_1006.png");
						pItem->Initialize(ITEM_TYPE::PET, 10000, pTex);
						CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_ITEM, pItem);
						m_pPlayer->SetItemType(pItem, ITEM_TYPE::PET);


						CItemFaceUI* pUI = new CItemFaceUI;
						pUI->SetParentUI(this);
						pUI->Initialize(pTex, UI_TYPE::STORE, ITEM_TYPE::PET);
						m_childUI_List.push_back(pUI);





						CInventoryUI* pInventory = m_pPlayer->GetPlayerInventory();
						CItemFaceUI* pUI1 = new CItemFaceUI;
						pUI1->SetParentUI(pInventory);
						pUI1->Initialize(pTex, UI_TYPE::INVENTORY, ITEM_TYPE::PET);
						pInventory->GetChildUI().push_back(pUI1);




						


						CSound* pNewSound1 = CResMgr::CreateSingleTonInst()->FindSound(L"nomeso");
						pNewSound1->Play(false);
						pNewSound1->SetPosition(1.f); // ��з� , �Ҹ���ġ
						pNewSound1->SetVolume(100.f); // �Ҹ� ���� ũ��

					}

					
				}
			}
				break;
			case ITEM_TYPE::ITEM_END:
				break;
			default:
				break;
			}

		}
	}

	
	

}


void CStoreUI::MouseOn()
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


void CStoreUI::MouseOut()
{

}
