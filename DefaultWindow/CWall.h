#pragma once
#include "Obj.h"
class CWall :
    public CObj
{
public:
    CWall();
    ~CWall();

public:
    virtual void Initialize();


    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
};

