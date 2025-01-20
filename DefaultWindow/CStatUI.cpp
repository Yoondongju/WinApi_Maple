#include "stdafx.h"
#include "CStatUI.h"

#include "CKeyMgr.h"
#include "ObjMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CStatBtnUI.h"

#include "MainGame.h"

#include "CSound.h"

CStatUI::CStatUI()
	: m_vDragStart(Vec2(0.f,0.f))
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

CStatUI::~CStatUI()
{
	Release();
}


void CStatUI::Initialize()
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player�� ObjMgr�� ��ϵǱ� ���� �̰� �ҷ��� ����������


	
	// Stat ���ڿ� ���� //
	m_strStat[0] = L"������";
	m_strStat[1] = L"�����";
	m_strStat[2] = L"���Ҽ�";
	m_strStat[3] = L"-999";
	m_strStat[4] = L"1999_11_09";
	m_strStat[5] = L"2024_04_05";
	m_strStat[6] = L"100";
	m_strStat[7] = L"100";





	m_tInfo = { WINCX / 3.f, WINCY / 2.f, 200.f,350.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::STAT;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_Stat_UI", L"../API/UI/stat.png");


	CStatBtnUI* pUI = new CStatBtnUI;
	pUI->SetParentUI(this);
	pUI->Initialize();
	m_childUI_List.push_back(pUI);

}

	

int CStatUI::Update()
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

void CStatUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();
		MouseOn();

		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Late_Update();
	}
	
}

void CStatUI::Render(HDC hDC)
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

		

		for (size_t i = 0; i < 8; ++i)
		{
			m_ptText = { (LONG)((float)m_tRect.left + 90.f), (LONG) ((float)m_tRect.top + 31.5f + (19*i))  ,m_tRect.right,m_tRect.bottom};
			DrawTextW(hDC
				, m_strStat[i].c_str()		// ������ ������
				, -1
				, &m_ptText
				, DT_LEFT | DT_WORDBREAK);
		}




		m_strAbility = to_wstring(m_pPlayer->m_iAbilityPoint); 
		m_ptText = { (LONG)((float)m_tRect.left + 70.f), (LONG)((float)m_tRect.top + 31.5f + 176.f)  ,m_tRect.right,m_tRect.bottom };
		DrawTextW(hDC
			, m_strAbility.c_str()		// ������ ������
			, -1
			, &m_ptText
			, DT_LEFT | DT_WORDBREAK);
		






		m_strSDIL[0] = to_wstring(m_pPlayer->m_iSTR);
		m_strSDIL[1] = to_wstring(m_pPlayer->m_iDEX);
		m_strSDIL[2] = to_wstring(m_pPlayer->m_iINT);
		m_strSDIL[3] = to_wstring(m_pPlayer->m_iLUK);
		for (size_t i = 0; i < 4; ++i)
		{
			m_ptText = { (LONG)((float)m_tRect.left + 80.f), (LONG)((float)m_tRect.top + 236.5f + (19*i))  ,m_tRect.right,m_tRect.bottom };
			DrawTextW(hDC
				, m_strSDIL[i].c_str()		// ������ ������
				, -1
				, &m_ptText
				, DT_LEFT | DT_WORDBREAK);

		}
		



		for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
			iter->Render(hDC);

	}
		
}

void CStatUI::Release()
{
	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		Safe_Delete<CPlayerUI*>(iter);


	m_childUI_List.clear();

}


void CStatUI::MouseOn()
{
	if (m_bMovement)
	{
		if(IsLbtnDown())
		{
			Vec2 vCurMousePos = CKeyMgr::CreateSingleTonInst()->GetMousePos();
			Vec2 vDiff = m_vDragStart - vCurMousePos;
			Set_Pos(m_tInfo.fX - vDiff.x, m_tInfo.fY - vDiff.y);


			m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
		}
				
	}
}



void CStatUI::MouseOut()
{
}


void CStatUI::MouseLBtnDown()
{
	m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();

}



void CStatUI::MouseLBtnUp()
{

}



void CStatUI::MouseClick()
{
	


}


