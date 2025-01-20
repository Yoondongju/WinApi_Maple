#pragma once
#include "Obj.h"
class CWeb :
    public CObj
{
public:
    CWeb();
    ~CWeb();

public:
    virtual void Initialize();

    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

private:

};

