#pragma once
#include "CPlayerUI.h"
class CWarringUI :
    public CPlayerUI
{
public:
	CWarringUI();
	~CWarringUI();


	virtual void Initialize();


	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


private:
	BYTE		m_byte;
};

