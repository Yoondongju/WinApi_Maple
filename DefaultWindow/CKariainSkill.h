#pragma once
#include "Obj.h"
#include "CMonster.h"

class CKariainSkill :
    public CObj
{
public:
    CKariainSkill();
    ~CKariainSkill();

public:
    virtual void Initialize(){}

    virtual void Initialize(MONSTER_DIR _e);
   
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    MONSTER_DIR         m_eDir;

    
public:
    void    SetActive(bool _b) { m_bActive = _b; }
    bool    GetActive() { return m_bActive; }

private:
    bool        m_bActive;
};

