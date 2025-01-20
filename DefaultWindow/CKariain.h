#pragma once
#include "CMonster.h"


enum KARIAIN_STATE
{
    ATTACK1,
    ATTACK2,
    TELEPOTE,

    KARIAIN_END,
};


class CAnimator;
class CKariainSkill;
class CAnimation;


class CKariain :
    public CMonster
{
public:
    CKariain();
    ~CKariain();

public:
    virtual void Initialize() { }
    virtual void Initialize(Vec2 _vPos);
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    void         StartAttack();
    void         StartTelepote();


private:
    float               m_fTelepoteDelay;
    KARIAIN_STATE       m_eState;

    CKariainSkill*      m_pMySkill;
    CAnimation*         m_pCreateAni;
};

