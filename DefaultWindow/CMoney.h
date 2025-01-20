#pragma once
#include "CItem.h"

class CPet;

class CMoney :
    public CItem
{
public:
    CMoney();
    ~CMoney();

public:
    virtual void Initialize(){}
    virtual void Initialize(Vec2 _v, int _iPrice);

    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


public:
    void SetMagnet(bool _b, CPet* _p) { m_bMagnetState = _b;  m_pPet = _p; }
    bool IsMagnet() { return m_bMagnetState; }



private:
    bool    m_bMagnetState;
    CPet*   m_pPet;
    int     m_iPrice;

};

