#pragma once
#include "CScene.h"
class CBoss_Page2 :
    public CScene
{
public:
    CBoss_Page2();
    ~CBoss_Page2();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Enter() override;
    virtual void Exit() override;
};

