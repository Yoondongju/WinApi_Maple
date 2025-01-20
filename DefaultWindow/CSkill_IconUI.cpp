#include "stdafx.h"
#include "CSkill_IconUI.h"


#include "CResMgr.h"
#include "CTexture.h"

#include "ObjMgr.h"
#include "CKeyMgr.h"
#include "Player.h"


CSkill_IconUI::CSkill_IconUI()
    : m_vOffset(0.f, 0.f)
	, m_pLbtnClickTex(nullptr)
    , m_pRenderTex(nullptr)
{
}


CSkill_IconUI::~CSkill_IconUI()
{
}

void CSkill_IconUI::Initialize()
{
	// 매개변수없는 생성시 문제
	assert(nullptr);
}

void CSkill_IconUI::Initialize(CTexture* _pTex, CTexture* _pClickTex ,Vec2 _vOffset , SKILL_TYPE _e)
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player(); // Player가 ObjMgr에 등록되기 전에 이걸 불러서 문제가생김

	Vec2 vPos = m_pParentUI->GetPos();
	m_vOffset = _vOffset;
	m_tInfo = { vPos .x + m_vOffset.x , vPos.y + m_vOffset.y  , 35.f ,35.f };


	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::SKILL_ICON;
	m_eSkillType = _e;

	m_pUITex = _pTex;					// 비활성화
	m_pRenderTex = _pClickTex;			// 활성화
}

int CSkill_IconUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	

	Vec2 vPos = m_pParentUI->GetPos();
	Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSkill_IconUI::Late_Update()
{
	MouseOnCheck();
	MouseOn();


	if (nullptr != m_pPlayer->GetSkill(m_eSkillType))   // 스킬이 존재한다면
	{
		m_pUITex = m_pRenderTex;
	}
		
}

void CSkill_IconUI::Render(HDC hDC)
{
	AlphaBlend(hDC
		, m_tRect.left		            // ( 고정위치 )						// 이미지를 출력할 x
		, m_tRect.top		            // ( 고정위치 )						// 이미지를 출력할 y
		, m_tInfo.fCX							// 출력할 이미지의 가로 ( 이 크기만큼 이미지의 크기변경 )
		, m_tInfo.fCY
		, m_pUITex->GetDC()
		, 0								// 가져올 이미지의 시작위치
		, 0
		, m_pUITex->Width() 			// 잘라낼 크기니까 항상 800 이여야함
		, m_pUITex->Height()
		, this->GetBf());
}

void CSkill_IconUI::Release()
{
}

void CSkill_IconUI::MouseLBtnDown()
{

	
}

void CSkill_IconUI::MouseLBtnUp()
{
	
}

void CSkill_IconUI::MouseClick()
{
}

void CSkill_IconUI::MouseOn()
{
	

}

void CSkill_IconUI::MouseOut()
{
}
