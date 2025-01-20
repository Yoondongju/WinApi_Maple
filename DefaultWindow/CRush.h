#pragma once
#include "CPlayerSkill.h"
class CRush :
    public CPlayerSkill
{
public:
    CRush();
    ~CRush();

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
    float     m_fPower;
    float     m_fTarGetX;

};

