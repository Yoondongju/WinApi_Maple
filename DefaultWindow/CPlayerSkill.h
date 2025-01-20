#pragma once
#include "Obj.h"

class CPlayer;
class CSkillEffect;


#define     ORABLADE_DELAY 1.f
#define     RUSH_DELAY 1.f
#define     UPPERCHARGE_DELAY 1.f
#define     RAGINGBLOW_DELAY 0.5f
#define     DEATHDAULT_DELAY 1.f


class CPlayerSkill abstract : public CObj
{
public:
    CPlayerSkill();
    virtual ~CPlayerSkill();

public:
    virtual void Initialize() PURE;
    virtual int Update() PURE;
    virtual void Late_Update() PURE;
    virtual void Render(HDC hDC);

    virtual void Release() PURE;


public:
    virtual void CreateSkillEffect()PURE;


public:
    virtual void PlaySkill() PURE;


public:
    void SetSkillActivate(bool _b) { m_bActivate = _b; }
    bool GetSkillActivate() { return m_bActivate; }


    void SetSkillDelay(float _f) { m_fDelay = _f; }
    float GetSkillDelay() { return m_fDelay; }

public:
    float   GetSkillAttackInfo() { return m_fSkillAttackInfo; }
    RECT    GetSkillRange() { return m_rtSkillRange; }

    int     GetAttackCount() { return m_iAttackCount; }


public:
    bool    IsFirstAttack() { return m_bFirstAttack; }
    void    SetFirstAttack(bool _b) { m_bFirstAttack = _b; }


    SKILL_TYPE  GetSkillType() { return m_eSkillType; }

protected:
    Vec2        m_vOffset;
    CPlayer*    m_pPlayer;

    SKILL_TYPE  m_eSkillType;

    float       m_fDelay;
    float       m_fTime;
    float       m_fCoolTime;

    
    bool        m_bFirstAttack;


    
    float       m_fSkillAttackInfo;
    RECT        m_rtSkillRange;
    int         m_iAttackCount;
    

    bool        m_bActivate;
    CSkillEffect*  m_pSkillEffect;

    friend class CSkillEffect;
};






// 스킬은 범위,시간,비용등 여러 부가정보를 가져야하고
// 스킬이 나가는 이펙트도 있어야함