#pragma once
#include "Obj.h"
class CEffect :
    public CObj
{
public:
	CEffect();
	~CEffect();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:

};

