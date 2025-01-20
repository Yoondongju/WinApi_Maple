#pragma once
#include "Obj.h"
class CBody :
    public CObj
{
public:
    CBody();
    ~CBody();

public:
    virtual void Initialize() {}
    virtual void Initialize(Vec2 _v);

    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

};

