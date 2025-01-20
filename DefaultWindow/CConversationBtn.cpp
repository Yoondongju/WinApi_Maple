#include "stdafx.h"
#include "CConversationBtn.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CKeyMgr.h"

#include "Player.h"
#include "ObjMgr.h"

CConversationBtn::CConversationBtn()
	:m_vOffset(200.f,48.f)
	, m_pLbtnClickTex(nullptr)
	, m_pRenderTex(nullptr)
{
	
}

CConversationBtn::~CConversationBtn()
{

}

void CConversationBtn::Initialize()
{
	Vec2 vPos = m_pParentUI->GetPos();

	m_tInfo = { vPos.x + m_vOffset.x,vPos.y + m_vOffset.y   , 80.f ,18.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::BUTTON;

	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Btn_None", L"../API/UI/Button_NextNone.png");
	m_pLbtnClickTex= CResMgr::CreateSingleTonInst()->LoadTexture(L"Btn_Click", L"../API/UI/Button_NextClick.png");


	m_pRenderTex = m_pUITex;
}

int CConversationBtn::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	Vec2 vPos = m_pParentUI->GetPos();
	Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);


	__super::Update_Rect();
	return OBJ_NOEVENT;


}

void CConversationBtn::Late_Update()
{
	MouseOnCheck();


	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		iter->Late_Update();

}

void CConversationBtn::Render(HDC hDC)
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


	for (auto& iter : m_childUI_List)			// �ڽ��� �׻� �θ� ���� �׷������ϴϱ� !
		iter->Render(hDC);

}

void CConversationBtn::Release()
{
}

void CConversationBtn::MouseLBtnDown()
{
}

void CConversationBtn::MouseLBtnUp()
{
}

void CConversationBtn::MouseClick()
{
	// ��ȭ�� �Ѱ���߰���
	CConversationUI* pUI = static_cast<CConversationUI*>(m_pParentUI);

	BYTE count = pUI->GetCount();
	BYTE Maxcount = pUI->GetMaxCount();

	
	if (Maxcount > count)
	{
		++count;
		pUI->SetCount(count);
	}

}

void CConversationBtn::MouseOn()
{
	m_pRenderTex = m_pLbtnClickTex;
}

void CConversationBtn::MouseOut()
{
	m_pRenderTex = m_pUITex;
}
