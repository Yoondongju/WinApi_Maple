#pragma once
#include "Obj.h"

class CPlayer;



class CPet :
    public CObj
{
public:
    CPet();
    ~CPet();
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


    void    FindMeso();



private:
    CPlayer*    m_pOwner;
   
    Vec2        m_vOffset;


    Vec2        m_vRecognizeSize;

};

