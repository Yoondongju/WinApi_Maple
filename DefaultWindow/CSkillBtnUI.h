#pragma once
#include "CSkillUI.h"


class CSkillBtnUI :
    public CPlayerUI
{
public:
	CSkillBtnUI();
	~CSkillBtnUI();


	virtual void Initialize(){}

	virtual void Initialize(Vec2 _vOffset , SKILL_TYPE _e);

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
	void	SetParentUI(CPlayerUI* _p) { m_pParentUI = _p; }


private:
	Vec2		m_vOffset;



	CTexture*	m_pLbtnClickTex;
	CTexture*	m_pRenderTex;

	
	SKILL_TYPE	m_eSkillType;
};

