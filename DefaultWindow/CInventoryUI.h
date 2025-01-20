#pragma once
#include "CPlayerUI.h"
class CInventoryUI : public CPlayerUI
{
public:
	CInventoryUI();
	~CInventoryUI();

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
	char GetInvenCheck() { return m_cCheck; }


private:
	Vec2			m_vDragStart;


	CTexture*		m_pRenderTex;
	CTexture*		m_pPortion;

	char			m_cCheck;
	
	

};

