#pragma once
#include "CPlayerSkill.h"
class COrablade :
    public CPlayerSkill
{
public:
    COrablade();
    ~COrablade();

public:
    // CPlayerSkill을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    virtual void CreateSkillEffect() override;
    virtual void PlaySkill() override;


private:
    Vec2    m_vStartPos;
    Vec2    m_vTargetPos;

};

