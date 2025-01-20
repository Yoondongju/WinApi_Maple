#pragma once
#include "CPlayerUI.h"


class CITem;
class CSelect;

class CStoreUI :
    public CPlayerUI
{
public:
	CStoreUI();
	~CStoreUI();

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


private:
	Vec2			m_vDragStart;


	CSelect*		m_pSelectUI;
};

