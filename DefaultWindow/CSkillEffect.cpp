#include "stdafx.h"
#include "CSkillEffect.h"

#include "ObjMgr.h"
#include "Player.h"
#include "CPlayerSkill.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"

CSkillEffect::CSkillEffect()
    : m_pOwnerSkill(nullptr)
    , m_vOffset(0.f,0.f)
{
	m_eObjType = OBJID::OBJ_PLAYER_SKILL_EFFECT;

	CreateAnimator();
}

CSkillEffect::~CSkillEffect()
{
}


void CSkillEffect::Initialize(CPlayerSkill* _pOwner)
{
    m_pOwnerSkill = _pOwner; 
	m_pPlayer = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();

	Vec2 vSize;

    switch (_pOwner->m_eSkillType)
    {
	case DEATHFAULT:
	{
		vSize = Vec2(1000.f,600.f);

		CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Deathfault_Effect_left", L"../API/Skill/deathfault/effect1/effect_motion_left.png");
		GetAnimator()->CreateAnimation(L"Deathfault_Effect_left", pTex, Vec2(0.f, 0.f), Vec2(1311.f, 489.f), Vec2(0.f, 489.f), 0.05f, 23);

		CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Deathfault_Effect_right", L"../API/Skill/deathfault/effect1/effect_motion_right.png");
		GetAnimator()->CreateAnimation(L"Deathfault_Effect_right", pTex1, Vec2(0.f, 0.f), Vec2(1311.f, 489.f), Vec2(0.f, 489.f), 0.05f, 23);
	}	
		break;

	case ORABLADE:
	{
		vSize = Vec2(200.f, 200.f);

		CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_Effect_left", L"../API/Skill/orablade/effect1/effect_motion_left.png");
		GetAnimator()->CreateAnimation(L"Orablade_Effect_left", pTex, Vec2(0.f, 0.f), Vec2(601.f, 494.f), Vec2(0.f, 494.f), 0.04f, 15);

		CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Orablade_Effect_right", L"../API/Skill/orablade/effect1/effect_motion_right.png");
		GetAnimator()->CreateAnimation(L"Orablade_Effect_right", pTex1, Vec2(0.f, 0.f), Vec2(601.f, 494.f), Vec2(0.f, 494.f), 0.04f, 15);
	}

		break;
	case RAGINGBLOW:
	{

	}
		break;
	case RUSH:
	{
		vSize = Vec2(200.f,200.f);

		CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"Rush_Effect_left", L"../API/Skill/rush/effect1/effect_motion_left.png");
		GetAnimator()->CreateAnimation(L"Rush_Effect_left", pTex, Vec2(0.f, 0.f), Vec2(258.f, 278.8f), Vec2(0.f, 278.8f), 0.03f, 7);

		CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"Rush_Effect_right", L"../API/Skill/rush/effect1/effect_motion_right.png");
		GetAnimator()->CreateAnimation(L"Rush_Effect_right", pTex1, Vec2(0.f, 0.f), Vec2(258.f, 278.8f), Vec2(0.f, 278.8f), 0.03f, 7);
	}	
		break;

	case UPPERCHARGE:
	{
		vSize = Vec2(200.f, 200.f);

		CTexture* pTex = CResMgr::CreateSingleTonInst()->LoadTexture(L"UpperCharge_Effect_left", L"../API/Skill/uppercharge/effect1/effect_motion_left.png");
		GetAnimator()->CreateAnimation(L"UpperCharge_Effect_left", pTex, Vec2(0.f, 0.f), Vec2(340.f, 209.f), Vec2(0.f, 209.f), 0.06f, 14);

		CTexture* pTex1 = CResMgr::CreateSingleTonInst()->LoadTexture(L"UpperCharge_Effect_right", L"../API/Skill/uppercharge/effect1/effect_motion_right.png");
		GetAnimator()->CreateAnimation(L"UpperCharge_Effect_right", pTex1, Vec2(0.f, 0.f), Vec2(340.f, 209.f), Vec2(0.f, 209.f), 0.06f, 14);
	}	
		break;

	case WARRIORLEAP:
		
		break;
	case SKILL_END:

		break;
	default:
		break;
    }

    
    Vec2 vPos = m_pPlayer->GetPos();
	m_tInfo = { vPos.x + m_vOffset.x , vPos.y + m_vOffset.y, vSize.x,vSize.y };


	

}

int CSkillEffect::Update()
{
	if (m_pOwnerSkill->GetSkillActivate())
	{
		if (m_bDead)
			return OBJ_DEAD;


		switch (m_pOwnerSkill->m_eSkillType)
		{
		case DEATHFAULT:
		{
			if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
			{
				m_vOffset = Vec2(0.f, 10.f);
				GetAnimator()->Play(L"Deathfault_Effect_left", false);
			}
			else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
			{
				m_vOffset = Vec2(0.f, 10.f);
				GetAnimator()->Play(L"Deathfault_Effect_right", false);
			}
			
		}
		break;

		case ORABLADE:
		{
			if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
			{
				m_vOffset = Vec2(0.f, 30.f);
				GetAnimator()->Play(L"Orablade_Effect_left", false);			
			}
			else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
			{
				m_vOffset = Vec2(0.f, 30.f);
				GetAnimator()->Play(L"Orablade_Effect_right", false);
			}
		}

			break;
		case RAGINGBLOW:
		{

		}
			break;
		case RUSH:
		{
			if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
			{
				m_vOffset = Vec2(150.f, 30.f);
				GetAnimator()->Play(L"Rush_Effect_left", false);
			}
			else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
			{
				m_vOffset = Vec2(-150.f, 30.f);
				GetAnimator()->Play(L"Rush_Effect_right", false);
			}
		}
		break;
		case UPPERCHARGE:
		{
			if (PLAYER_DIR::LEFT == m_pPlayer->GetPlayerDir())
			{		
				m_vOffset = Vec2(0.f, 20.f);
				GetAnimator()->Play(L"UpperCharge_Effect_left", false);
			}
			else if (PLAYER_DIR::RIGHT == m_pPlayer->GetPlayerDir())
			{
				m_vOffset = Vec2(0.f, 30.f);
				GetAnimator()->Play(L"UpperCharge_Effect_right", false);
			}
		}
		break;

		case WARRIORLEAP:

			break;
		case SKILL_END:

			break;
		default:
			break;
		}


		Vec2 vPos = m_pPlayer->GetPos();
		Set_Pos(vPos.x + m_vOffset.x, vPos.y + m_vOffset.y);

		__super::Update_Rect();
		return OBJ_NOEVENT;
	}

    
}

void CSkillEffect::Late_Update()
{
	if (m_pOwnerSkill->GetSkillActivate())
	{
		GetAnimator()->Update();
	}

}

void CSkillEffect::Render(HDC hDC)
{
	if (m_pOwnerSkill->GetSkillActivate())
	{
		GetAnimator()->GetCurAnimation()->Render(hDC);
	}
}

void CSkillEffect::Release()
{
}
