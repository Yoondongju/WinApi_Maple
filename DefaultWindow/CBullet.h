#pragma once
#include "Obj.h"
#include "CMonster.h"

class CBullet :
    public CObj
{
public:
    CBullet();
    ~CBullet();

public:
    virtual void Initialize() {}
    virtual void Initialize(Vec2 _v, MONSTER_DIR _e);

    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

private:
    MONSTER_DIR     m_eDir;
        
};

