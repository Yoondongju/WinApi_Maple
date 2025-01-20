#pragma once
#include "CPlayerUI.h"
class CQuickSlotUI :
    public CPlayerUI
{
public:
	CQuickSlotUI();
	~CQuickSlotUI();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void MouseLBtnDown();
	virtual void MouseLBtnUp();
	virtual void MouseClick();

	virtual void MouseOn();
	virtual void MouseOut();

public:
	Vec2	GetPortionOffset() { return m_vPortionOffset; }
	Vec2	GetPortionTargetPos() { return m_vPortionTargetPos; }


	Vec2	GetSkillOffset(SKILL_TYPE _e) { return m_vSkillOffset[(UINT)_e]; }


public:
	void	SetParentUI(CPlayerUI* _p) { m_pParentUI = _p; }

private:
	Vec2				m_vOffset;

	Vec2			    m_vSkillOffset[(UINT)SKILL_TYPE::SKILL_END];

	Vec2				m_vPortionOffset;
	Vec2				m_vPortionTargetPos;
};

