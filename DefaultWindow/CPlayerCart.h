#pragma once
#include "Obj.h"



class CPlayerCart :
    public CObj
{
public:
    CPlayerCart();
    ~CPlayerCart();

public:
    virtual void Initialize();


    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


private:
    bool        m_bGameOver;

};

