#pragma once
#include "CPlayerSkill.h"
class CSixSkill :
    public CPlayerSkill
{
public:
    CSixSkill();
    ~CSixSkill();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Release() override;
    virtual void CreateSkillEffect() override;
    virtual void PlaySkill() override;
    virtual void Render(HDC hDC);
    

};

