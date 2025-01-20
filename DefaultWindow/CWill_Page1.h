#pragma once
#include "CMonster.h"


class CBall;
class CBody;



enum class WILL_PAGE
{
    PAGE1,
    PAGE2,
    PAGE3,

    WILL_PAGE_END,
};


enum class WILL_ATTACK_TYPE
{
    ATTACK1,
    ATTACK2,
    SKILL,
    SKILL2,
    SKILL3,


    WILL_ATTACK_END,
};



class CWill_Page1 :
    public CMonster
{
public:
    CWill_Page1();
    ~CWill_Page1();

public:
    virtual void Initialize() { }
    virtual void Initialize(Vec2 _vPos);
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    virtual void         StartAttack();
    virtual void         StartSkill();

public:
    WILL_ATTACK_TYPE  GetAttackType() { return m_eAttackType; }
    WILL_PAGE         GetCurPage() { return m_ePage; }

public:
    void    SetBall_NULL_INIT() { m_pBall = nullptr; }


public:
    Vec2    GetAttack2RangePos() { return m_vAttack2RangePos; }
    Vec2    GetAttack2RangeSize() { return m_vAttack2RangeSize; }


protected:
    float                m_fCreateBodyDelay;
    float                m_fSkillDelay;

    bool                 m_bSkillUsing;

    CBall*               m_pBall;
    CBody*               m_pBody;


    WILL_ATTACK_TYPE     m_eAttackType;



    Vec2                m_vAttack2RangePos;
    Vec2                m_vAttack2RangeSize;

public:
    WILL_PAGE   m_ePage;

};

