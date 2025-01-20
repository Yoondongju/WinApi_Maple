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


	for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
		iter->Late_Update();

}

void CConversationBtn::Render(HDC hDC)
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


	for (auto& iter : m_childUI_List)			// 자식은 항상 부모 위에 그려져야하니까 !
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
	// 대화를 넘겨줘야겟지
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
