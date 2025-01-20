#include "stdafx.h"
#include "CPlayerSkill.h"
#include "SelectGDI.h"

CPlayerSkill::CPlayerSkill()
	: m_vOffset(0.f,0.f)
	, m_pPlayer(nullptr)
	, m_fDelay(0.f)
	, m_fTime(0.f)
	, m_fCoolTime(0.f)
	, m_bActivate(false)
	, m_pSkillEffect(nullptr)
	, m_bFirstAttack(true)
{

}

CPlayerSkill::~CPlayerSkill()
{

}


void CPlayerSkill::Render(HDC hDC)
{
	//SelectGDI p(hDC, PEN_TYPE::GREEN);
	//SelectGDI b(hDC, BRUSH_TYPE::HOLLOW);
	//
	//
	//
	//Vec2 vPos = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
	//
	//Rectangle(hDC
	//	, (int)(vPos.x - m_tInfo.fCX / 2.f)
	//	, (int)(vPos.y - m_tInfo.fCY / 2.f)
	//	, (int)(vPos.x + m_tInfo.fCX / 2.f)
	//	, (int)(vPos.y + m_tInfo.fCY / 2.f));
	//
	//
	//
	//SelectGDI p1(hDC, PEN_TYPE::RED);
	//SelectGDI b1(hDC, BRUSH_TYPE::HOLLOW);
	//
	//
	//
	//
	//float fX = m_rtSkillRange.left + (m_rtSkillRange.right - m_rtSkillRange.left) / 2.f;
	//float fY = m_rtSkillRange.top + (m_rtSkillRange.bottom - m_rtSkillRange.top) / 2.f;
	//Vec2 vPos1 = CCamera::CreateSingleTonInst()->GetRenderPos(Vec2(fX,fY));
	//
	//
	//Rectangle(hDC
	//	, (int)(vPos1.x - (m_rtSkillRange.right - m_rtSkillRange.left) / 2.f)
	//	, (int)(vPos1.y - (m_rtSkillRange.bottom - m_rtSkillRange.top) / 2.f)
	//	, (int)(vPos1.x + (m_rtSkillRange.right - m_rtSkillRange.left) / 2.f)
	//	, (int)(vPos1.y + (m_rtSkillRange.bottom - m_rtSkillRange.top) / 2.f));

}
