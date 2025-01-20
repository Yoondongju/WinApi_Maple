#pragma once
#include "CPlayerUI.h"

class CTexture;

class CStatBtnUI :
    public CPlayerUI
{
public:
	CStatBtnUI();
	~CStatBtnUI();


public:
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
	void	SetParentUI(CPlayerUI* _p) { m_pParentUI = _p; }

private:
	Vec2				m_vOffset;
	
	
	CTexture*			m_pLbtnDownTex;
	CTexture*			m_pLbtnClickTex;
	CTexture*			m_pRenderTex;


};

