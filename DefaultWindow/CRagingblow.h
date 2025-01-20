#pragma once
#include "CPlayerSkill.h"
class CRagingblow :
    public CPlayerSkill
{
public:
    CRagingblow();
    ~CRagingblow();

public:
    // CPlayerSkill을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


public:
    virtual void CreateSkillEffect();


public:
    virtual void PlaySkill();
};

