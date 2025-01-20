#pragma once
#include "CPlayerUI.h"
class CSelect :
    public CPlayerUI
{
public:
	CSelect();
	~CSelect();

	virtual void Initialize(){}
	virtual void Initialize(Vec2 _vPos);
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
	void		SetOffset (Vec2 _v) { m_vOffset = _v; }


private:
	Vec2			m_vOffset;
};

