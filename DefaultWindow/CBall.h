#pragma once
#include "Obj.h"
#include "CWill_Page1.h"


class CBall :
    public CObj
{
public:
    CBall();
    ~CBall();

public:
    virtual void Initialize(){}
    virtual void Initialize(Vec2 _v , MONSTER_DIR _e, WILL_PAGE _ePage);

    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    WILL_PAGE   GetCurPage() { return m_ePage; }

private:
    MONSTER_DIR     m_eDir;

    WILL_PAGE       m_ePage;

};

