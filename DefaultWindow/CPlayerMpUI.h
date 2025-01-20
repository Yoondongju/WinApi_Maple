#pragma once
#include "CPlayerUI.h"
class CPlayerMpUI :
    public CPlayerUI
{
public:
	CPlayerMpUI();
	~CPlayerMpUI();


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

