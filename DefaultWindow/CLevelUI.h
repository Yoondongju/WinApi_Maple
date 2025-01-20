#pragma once
#include "CPlayerUI.h"
class CLevelUI :
    public CPlayerUI
{
public:
	CLevelUI();
	~CLevelUI();


	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


public:
	void	SetParentUI(CPlayerUI* _p) { m_pParentUI = _p; }

private:
	Vec2						m_vOffset;
	map<wchar_t, CTexture*>		m_mapLevel;
};

