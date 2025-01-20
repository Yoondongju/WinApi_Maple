#pragma once
#include "CEffect.h"
class CMoveEffect :
    public CEffect
{
public:
	CMoveEffect();
	~CMoveEffect();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	BYTE		m_BYTE;
};

