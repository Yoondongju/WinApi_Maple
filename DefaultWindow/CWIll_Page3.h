#pragma once
#include "CWill_Page1.h"

class CPoison;
class CWeb;

class CWIll_Page3 :
    public CWill_Page1
{
public:
    CWIll_Page3();
    ~CWIll_Page3();

public:
    virtual void Initialize() { }
    virtual void Initialize(Vec2 _vPos);
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    virtual void         StartAttack();

    virtual void         StartSkill();
    void                 StartSkill2();
    void                 StartSkill3();


    void SetPoison(void* _p) { m_pPoison = nullptr; }

    float GetSkill_2_Delay() { return m_fSkill_2_Delay; }
    float GetSkill_3_Delay() { return m_fSkill_3_Delay; }

private:  
    float               m_fSkill_2_Delay;
    float               m_fSkill_3_Delay;



    CPoison*            m_pPoison;
    float               m_fCreateWebDelay;

};

