#pragma once
#include "CSkillUI.h"

class CTexture;

class CSkill_IconUI :
    public CPlayerUI
{
public:
	CSkill_IconUI();
	~CSkill_IconUI();

	virtual void Initialize() override;
	virtual void Initialize(CTexture* _pTex, CTexture* _pClickTex , Vec2 _vOffset, SKILL_TYPE _e);


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
	Vec2				m_vDragStart;
	Vec2				m_vOffset;
	SKILL_TYPE			m_eSkillType;

	CTexture*			m_pLbtnClickTex;
	CTexture*			m_pRenderTex;

};

