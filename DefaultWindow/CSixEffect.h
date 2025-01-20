#pragma once
#include "CEffect.h"
class CSixEffect :
    public CEffect
{
public:
	CSixEffect();
	~CSixEffect();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

