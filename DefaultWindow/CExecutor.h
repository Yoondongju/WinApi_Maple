#pragma once
#include "CMonster.h"
class CExecutor :
    public CMonster
{
public:
    CExecutor();


    ~CExecutor();

public:
    virtual void Initialize() { }
    virtual void Initialize(Vec2 _vPos);
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;




private:
};

