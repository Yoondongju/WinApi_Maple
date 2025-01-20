#include "stdafx.h"
#include "CSkillUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"

#include "CSkill_IconUI.h"
#include "CSkillBtnUI.h"

#include "Player.h"
#include "ObjMgr.h"


CSkillUI::CSkillUI()
	: m_vDragStart(Vec2(0.f, 0.f))
{
	m_bMovement = true;
	m_bActivate = false;


	BLENDFUNCTION bf = GetBf();
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 200;

	SetBf(bf);
}

CSkillUI::~CSkillUI()
{
	Release();
}

void CSkillUI::Initialize()
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player�� ObjMgr�� ��ϵǱ� ���� �̰� �ҷ��� ����������

	m_tInfo = { WINCX / 2.f + WINCX / 3.f, WINCY / 2.f, 400.f,400.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::SKILL;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_Skill_UI", L"../API/UI/Skill_Back_A.png");




	//  Skill Icon // 
	CSkill_IconUI* pUI = new CSkill_IconUI;     
	pUI->SetParentUI(this);
	CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_ragingblow_UI", L"../API/Skill/ragingblow/icon/icon_Disabled.png");
	CTexture* pTex_click = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_ragingblow_able_UI", L"../API/Skill/ragingblow/icon/icon_abled.png");
	pUI->Initialize(pTex, pTex_click,Vec2(-28.f,-23.f) , SKILL_TYPE::RAGINGBLOW );    // 40����
	m_childUI_List.push_back(pUI);


	CSkill_IconUI* pUI1 = new CSkill_IconUI;
	pUI1->SetParentUI(this);
	CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_deathfault_UI", L"../API/Skill/deathfault/icon/icon_Disabled.png");
	CTexture* pTex1_click = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_deathfault_able_UI", L"../API/Skill/deathfault/icon/icon_abled.png");
	pUI1->Initialize(pTex1, pTex1_click,Vec2(-28.f, 17.f), SKILL_TYPE::DEATHFAULT);
	m_childUI_List.push_back(pUI1);


	CSkill_IconUI* pUI2 = new CSkill_IconUI;
	pUI2->SetParentUI(this);
	CTexture* pTex2 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_rush_UI", L"../API/Skill/rush/icon/icon_Disabled.png");
	CTexture* pTex2_click = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_rush_able_UI", L"../API/Skill/rush/icon/icon_abled.png");
	pUI2->Initialize(pTex2, pTex2_click, Vec2(-28.f, 57.f), SKILL_TYPE::RUSH);
	m_childUI_List.push_back(pUI2);
	
	
	
	CSkill_IconUI* pUI3 = new CSkill_IconUI;
	pUI3->SetParentUI(this);
	CTexture* pTex3 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_orablade_UI", L"../API/Skill/orablade/icon/icon_Disabled.png");
	CTexture* pTex3_click = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_orablade_able_UI", L"../API/Skill/orablade/icon/icon_abled.png");
	pUI3->Initialize(pTex3, pTex3_click,Vec2(-28.f, 97.f), SKILL_TYPE::ORABLADE);
	m_childUI_List.push_back(pUI3);
	
	
	CSkill_IconUI* pUI4 = new CSkill_IconUI;
	pUI4->SetParentUI(this);
	CTexture* pTex4 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_uppercharge_UI", L"../API/Skill/uppercharge/icon/icon_Disabled.png");
	CTexture* pTex4_click = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_uppercharge_able_UI", L"../API/Skill/uppercharge/icon/icon_abled.png");
	pUI4->Initialize(pTex4, pTex4_click, Vec2(-28.f, 137.f), SKILL_TYPE::UPPERCHARGE);
	m_childUI_List.push_back(pUI4);
	
	
	CSkill_IconUI* pUI5 = new CSkill_IconUI;
	pUI5->SetParentUI(this);
	CTexture* pTex5 = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_warriorleap_UI", L"../API/Skill/warriorleap/icon/icon_Disabled.png");
	CTexture* pTex5_click = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_warriorleap_able_UI", L"../API/Skill/warriorleap/icon/icon_abled.png");
	pUI5->Initialize(pTex5, pTex5_click, Vec2(-28.f, 177.f), SKILL_TYPE::WARRIORLEAP);
	m_childUI_List.push_back(pUI5);
	//  Skill Icon // 




	//  Skill ȭ��ǥ��ư // 
	CSkillBtnUI* pUIBtn = new CSkillBtnUI;				// ����¡ ��ο�
	pUIBtn->SetParentUI(this);
	pUIBtn->Initialize(Vec2(35.f, -23.f), SKILL_TYPE::RAGINGBLOW);
	m_childUI_List.push_back(pUIBtn);

	CSkillBtnUI* pUIBtn1 = new CSkillBtnUI;				// ������Ʈ
	pUIBtn1->SetParentUI(this);
	pUIBtn1->Initialize(Vec2(35.f, 17.f), SKILL_TYPE::DEATHFAULT);
	m_childUI_List.push_back(pUIBtn1);

	CSkillBtnUI* pUIBtn2 = new CSkillBtnUI;				// ����
	pUIBtn2->SetParentUI(this);
	pUIBtn2->Initialize(Vec2(35.f, 57.f), SKILL_TYPE::RUSH);
	m_childUI_List.push_back(pUIBtn2);
	
	CSkillBtnUI* pUIBtn3 = new CSkillBtnUI;				// ���� ���̵�
	pUIBtn3->SetParentUI(this);
	pUIBtn3->Initialize(Vec2(35.f, 97.f), SKILL_TYPE::ORABLADE);
	m_childUI_List.push_back(pUIBtn3);
	
	CSkillBtnUI* pUIBtn4 = new CSkillBtnUI;				// ������¡
	pUIBtn4->SetParentUI(this);
	pUIBtn4->Initialize(Vec2(35.f, 137.f), SKILL_TYPE::UPPERCHARGE);
	m_childUI_List.push_back(pUIBtn4);
	
	CSkillBtnUI* pUIBtn5 = new CSkillBtnUI;				// 2������ ����������
	pUIBtn5->SetParentUI(this);
	pUIBtn5->Initialize(Vec2(35.f, 177.f), SKILL_TYPE::WARRIORLEAP);
	m_childUI_List.push_back(pUIBtn5);

	//  Skill ȭ��ǥ��ư // 
}

int CSkillUI::Update()
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

void CSkillUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();
		MouseOn();


		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Late_Update();
	}
}

void CSkillUI::Render(HDC hDC)
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



		wstring strSkillPoint = to_wstring(m_pPlayer->m_iSkillPoint);
		RECT rt = { (LONG)((float)m_tRect.left + 225.f), (LONG)((float)m_tRect.top + 133.f)  ,m_tRect.right,m_tRect.bottom };
		DrawTextW(hDC
			, strSkillPoint.c_str()		// ������ ������
			, -1
			, &rt
			, DT_LEFT | DT_WORDBREAK);



		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Render(hDC);
	}
		
	
}

void CSkillUI::Release()
{
	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		Safe_Delete<CPlayerUI*>(iter);


	m_childUI_List.clear();
}

void CSkillUI::MouseLBtnDown()
{
	m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
}

void CSkillUI::MouseLBtnUp()
{
}

void CSkillUI::MouseClick()
{
}

void CSkillUI::MouseOn()
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

void CSkillUI::MouseOut()
{
}
