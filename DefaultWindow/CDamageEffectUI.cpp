#include "stdafx.h"
#include "CDamageEffectUI.h"

#include "CKeyMgr.h"
#include "ObjMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CStatBtnUI.h"

#include "MainGame.h"

#include "CSound.h"

CDamageEffectUI::CDamageEffectUI()
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

CDamageEffectUI::~CDamageEffectUI()
{
}

void CDamageEffectUI::Initialize()
{
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();

	m_tInfo = { WINCX / 3.f, WINCY / 2.f, 350.f,350.f };

	m_eObjType = OBJID::OBJ_UI;
	m_eUItype = UI_TYPE::DAMAGE_EFFECT;


	m_pUITex = CResMgr::CreateSingleTonInst()->LoadTexture(L"player_damageEffect_UI", L"../API/UI/damageEffectUI.png");

}

int CDamageEffectUI::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_bActivate)
	{
	
		__super::Update_Rect();

	}
	return OBJ_NOEVENT;
}

void CDamageEffectUI::Late_Update()
{
	if (m_bActivate)
	{
		MouseOnCheck();
		MouseOn();

	}
}

void CDamageEffectUI::Render(HDC hDC)
{
	if (m_bActivate)
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

}

void CDamageEffectUI::Release()
{
}

void CDamageEffectUI::MouseLBtnDown()
{
	m_vDragStart = CKeyMgr::CreateSingleTonInst()->GetMousePos();
}

void CDamageEffectUI::MouseLBtnUp()
{
}

void CDamageEffectUI::MouseClick()
{
	RECT rtNone =
	{
		m_tRect.left + 50,
		m_tRect.top + 60,
		m_tRect.left + 210,
		m_tRect.top + 84
	};

	RECT rtVolcano =
	{
		m_tRect.left + 48,
		m_tRect.top + 148,
		m_tRect.left + 207,
		m_tRect.top + 173
	};

	RECT rtParticle =
	{
		m_tRect.left + 40,
		m_tRect.top + 247,
		m_tRect.left + 217,
		m_tRect.top + 276
	};

	
	Vec2 vMousePos = CKeyMgr::CreateSingleTonInst()->GetMousePos();

	if (vMousePos.x > rtNone.left						// Info 로 계산하지않고 Rect로 계산함 !!! 
		&& vMousePos.x < rtNone.right
		&& vMousePos.y > rtNone.top
		&& vMousePos.y < rtNone.bottom)
	{
		m_pPlayer->SetDamageEffect(DamageEffectType::NONE);
	}

	else if (vMousePos.x > rtVolcano.left						// Info 로 계산하지않고 Rect로 계산함 !!! 
		&& vMousePos.x < rtVolcano.right
		&& vMousePos.y > rtVolcano.top
		&& vMousePos.y < rtVolcano.bottom)
	{
		m_pPlayer->SetDamageEffect(DamageEffectType::VOLCANO);
	}

	else if (vMousePos.x > rtParticle.left						// Info 로 계산하지않고 Rect로 계산함 !!! 
		&& vMousePos.x < rtParticle.right
		&& vMousePos.y > rtParticle.top
		&& vMousePos.y < rtParticle.bottom)
	{
		m_pPlayer->SetDamageEffect(DamageEffectType::PATICLE);
	}


}

void CDamageEffectUI::MouseOn()
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

void CDamageEffectUI::MouseOut()
{
}
