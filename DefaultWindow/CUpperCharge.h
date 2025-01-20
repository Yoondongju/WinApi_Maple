#pragma once
#include "CPlayerSkill.h"
class CUpperCharge :
    public CPlayerSkill
{
public:
    CUpperCharge();
    ~CUpperCharge();

public:
    // CPlayerSkill을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;



public:
    virtual void PlaySkill();
    virtual void CreateSkillEffect();

private:


};

