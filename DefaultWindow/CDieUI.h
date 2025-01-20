#pragma once
#include "CPlayerUI.h"
class CDieUI :
    public CPlayerUI
{
public:
	CDieUI();
	~CDieUI();

	virtual void Initialize();



	virtual int	 Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void MouseLBtnDown();
	virtual void MouseLBtnUp();
	virtual void MouseClick();

	virtual void MouseOn();
	virtual void MouseOut();




};

