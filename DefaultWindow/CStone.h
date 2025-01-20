#pragma once
#include "Obj.h"
class CStone :
    public CObj
{
public:
    CStone();
    ~CStone();
  
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
};

