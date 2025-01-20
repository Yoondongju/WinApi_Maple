#pragma once
#include "CPlayerUI.h"


class CTexture;


class CExpUI :
    public CPlayerUI
{
public:
	CExpUI();
	~CExpUI();


	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void	SetParentUI(CPlayerUI* _p) { m_pParentUI = _p; }

private:
	Vec2				m_vOffset;
	

};

