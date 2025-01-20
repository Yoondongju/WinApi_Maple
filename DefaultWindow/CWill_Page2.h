#pragma once
#include "CWill_Page1.h"
class CWill_Page2 :
    public CWill_Page1
{
public:
    CWill_Page2();
    ~CWill_Page2();

public:
    virtual void Initialize() { }
    virtual void Initialize(Vec2 _vPos);
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    virtual void         StartAttack();
    virtual void         StartAttack2();
    virtual void         StartSkill();






private:
    float               m_fAttack2Delay;


};

