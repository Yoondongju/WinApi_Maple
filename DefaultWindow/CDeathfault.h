#pragma once
#include "CPlayerSkill.h"
class CDeathfault :
    public CPlayerSkill
{
public:
    CDeathfault();
    ~CDeathfault();

public:
    // CPlayerSkill��(��) ���� ��ӵ�
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

