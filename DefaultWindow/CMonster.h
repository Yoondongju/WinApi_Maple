#pragma once
#include "Obj.h"

#include "LineMgr.h"

class CLine;



enum class MONSTER_DIR
{
    LEFT,
    RIGHT,
    END,
};


class CMonster abstract : public CObj
{
public:
    CMonster();
    ~CMonster();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


public:
    void SetArrival(bool _b) { m_bArrival = _b; }
    bool GetArrival() { return m_bArrival; }

public:
    void SetPreLine(CLine* _p) { m_pPreLine = _p; }
    CLine* GetPreLine() { return m_pPreLine; }


    friend bool CLineMgr::Collision_LineMonster(CMonster * _p, float& fX, float& fY, float* pY, float* pX);





public:
    void SetMaxHP(float _f) { m_fMaxHp = _f; }
    void SetHp(float _f) { m_fHp = _f; }
    void SetAttackInfo(float _f) { m_fAttackInfo = _f; }

    float GetMaxHP() { return m_fMaxHp; }
    float GetHp() { return m_fHp; }
    float GetAttackInfo() { return m_fAttackInfo; }


    void SetZenDelay(float _f) { m_fZenDelay = _f; }
    float GetZenDelay() { return m_fZenDelay; }


    void SetDeadAniPlay(bool _b) { m_bDeadAniPlay = _b; }
    bool GetDeadAniPlay() { return m_bDeadAniPlay; }

    void SetHit(bool _b) { m_bHit = _b; }
    bool GetHit() { return m_bHit; }

public:
    virtual void StartAttack(){}

public:
    int GetDropExp() { return m_iDropExp; }
    int GetDropMoney() { return m_iDropMoney; }

    void  SetCollisionObj(CObj* _p) { m_pCollisonObj = _p; }
    CObj* GetCollisionObj() { return m_pCollisonObj; }


    Vec2    GetAttackRangePos() { return m_vAttack1RangePos; }
    Vec2    GetAttackRangeSize() { return m_vAttack1RangeSize; }

    bool    GetAttacking() { return m_bAttacking; }


public:
    MONSTER_DIR     GetDir() { return m_eDir; }

public:
    SKILL_TYPE  GetCurColliSkillType() { return m_eColliSkillType; }
    void SetCurColliSkillType(SKILL_TYPE _e) { m_eColliSkillType = _e; }

protected:


    bool		        m_bLineCol;
    float		        m_fLadningTime;
    bool				m_bArrival;
    float				m_fTargetX;

    CLine*              m_pPreLine;

    MONSTER_DIR         m_eDir;


    float               m_fMoveDelay;
    float               m_fZenDelay;

    float               m_fMaxHp;
    float               m_fHp;

    float               m_fAttackInfo;
    float               m_fAttackDelay;

    float               m_fAllAttackDelay;

    bool                m_bAttacking;


    bool                m_bDeadAniPlay;
    bool                m_bHit;

    int                 m_iDropExp;
    int                 m_iDropMoney;
    CObj*               m_pCollisonObj;



   int                  m_iDamageCount;
   float                m_fDamageCreateDelay;


   Vec2        m_vAttack1RangePos;
   Vec2        m_vAttack1RangeSize;

 

   Vec2        m_vAttack3RangePos;
   Vec2        m_vAttack3RangeSize;


   SKILL_TYPE   m_eColliSkillType;
};

