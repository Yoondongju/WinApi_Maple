#pragma once
#include "CPlayerSkill.h"
class CWarriorLeap : public CPlayerSkill
{
public:
    CWarriorLeap();
    ~CWarriorLeap();

public:
    // CPlayerSkill��(��) ���� ��ӵ�
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

public:
    virtual void PlaySkill(){}
    virtual void CreateSkillEffect(){}

};


