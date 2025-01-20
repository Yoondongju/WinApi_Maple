#pragma once
#include "Obj.h"
class CBoom :
    public CObj
{
public:
    CBoom();
    ~CBoom();

public:
    virtual void Initialize();


    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


private:
    int         m_iCount;

};

